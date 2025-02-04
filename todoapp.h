#ifndef TODOAPP_H
#define TODOAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ToDoApp;
}
QT_END_NAMESPACE

class ToDoApp : public QMainWindow
{
    Q_OBJECT

public:
    ToDoApp(QWidget *parent = nullptr);
    ~ToDoApp();

private slots:
    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

    void on_btnRemoveAll_clicked();

private:
    Ui::ToDoApp *ui;
};
#endif // TODOAPP_H
