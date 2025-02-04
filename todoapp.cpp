#include "todoapp.h"
#include "ui_todoapp.h"
#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>
#include <QLineEdit>
ToDoApp::ToDoApp(QWidget *parent): QMainWindow(parent), ui(new Ui::ToDoApp){
    ui->setupUi(this);

    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\toDoFile.txt"); // dosya islemleri icin qfile ve standardpaths include edilmeli
    // bu konuma dayali bir dosya nesnesi olusturur \\toDoFile.txt
    if(!file.open(QIODevice::ReadWrite)){                        // dosya acik degilse veya yoksa error verir
        QMessageBox::information(0,"error", file.errorString()); // 0 QMainWindow'dur
    }

    QTextStream in(&file); // dosyadan veriyi alip listeye yerlestirir
    while(!in.atEnd()){
        QListWidgetItem* item = new QListWidgetItem(in.readLine(),ui->listWidget); // metin dizesindeki her satira dayali bir oge olusturur
        ui->listWidget->addItem(item);
        item->setFlags(item->flags()| Qt::ItemIsEditable);
    }
    file.close(); // kapamazsak daha sonra erisemeyiz
}

ToDoApp::~ToDoApp()
{
    delete ui;

    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\\toDoFile.txt");
    if(!file.open(QIODevice::ReadWrite)){
        QMessageBox::information(0,"error", file.errorString());
    }

    QTextStream out(&file);
    for(int i = 0; i < ui -> listWidget->count(); i++) { // listWidget'daki oge sayisini verir
        out << ui->listWidget->item(i)->text() << "\n";  // item(i) listedeki i. ogeyi verir, text metni verir
    }
    file.close();
}

void ToDoApp::on_btnAdd_clicked()
{
    QListWidgetItem* item = new QListWidgetItem(ui->txtTask->text(), ui->listWidget);
    ui->listWidget->addItem(item);
    item->setFlags(item->flags()| Qt::ItemIsEditable); // yazılanı editletir
    ui->txtTask->clear();    // yazılanı ekledikten sonra siler
    ui->txtTask->setFocus(); // kelime eklendikten sonra diger sey icin otomatik odaklar
}


void ToDoApp::on_btnRemove_clicked()
{
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item; // yukarda mevcut yazıyı başka bir yere pointerla belleğe kaydeder aslında gitmez ve burda da sileriz
}


void ToDoApp::on_btnRemoveAll_clicked()
{
    ui->listWidget->clear(); // hepsini sil
}
