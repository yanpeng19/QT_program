#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <unordered_map>
#include <memory>
#include <QCloseEvent>
#include <deque>

using namespace std;

class MyTextEdit;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Load_menu();
   // void set_connect();
    QAction *add_sep();
    bool stop_close = 0;

signals:
    void close_submidwindow(QWidget* window);

public slots:

    // 文件栏
    MyTextEdit* creat_new_file();
    MyTextEdit* creat_new_file(const QString& file_name);
    MyTextEdit* fun_open_file();
    bool fun_save_file();
    bool fun_save_file_as();
    bool fun_close_file();
    bool fun_close_all();

    // 编辑栏
    void fun_undo();
    void fun_regain();
    void fun_copy();
    void fun_cut();
    void fun_pasted();

    // 功能函数
    QString get_default_title();
    bool do_close_file(MyTextEdit* window);
    void erase_window_from_map(MyTextEdit* window);
    void record_action();

private:
    Ui::MainWindow *ui;
    unordered_map<QWidget*,QString> url_map;
    map<QString,QWidget*> path_map;
    QString clipboard;  // 全局剪切板

};

class MyTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    MyTextEdit() =delete;
    MyTextEdit(QWidget *par = nullptr):QTextEdit(par),p(dynamic_cast<MainWindow*>(par)){c_stack_pos=0;content_stack.push_back("");}

    ~MyTextEdit();

protected:
    void closeEvent(QCloseEvent *even);

public slots:
    //void closeEvetn(QCloseEvent *event);

    // QString windowTitle(){return QTextEdit::windowTitle();}
    void setWindowTitle(const QString& t){QTextEdit::setWindowTitle(t);title=t;}
    void fun_content_changed();
    void fun_content_dechanged();
    bool have_path(){return !path.isEmpty();}
    bool changed() {return content_changed;}

    void record_action(const QString& content);  // 记录内容
    void undo_action();    // 撤销一步修改
    void regain_action();  // 前进一步

private:
   MainWindow *p;
   bool content_changed = 0;
   QString title;
   QString path;
   deque<QString> content_stack; // 记录栈，内容最大为20
   size_t c_stack_pos; // 记录栈指针，记录上一次操作的下标
};

#endif // MAINWINDOW_H
