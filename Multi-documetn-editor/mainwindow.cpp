#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <QKeySequence>
#include <QTextEdit>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QByteArray>
#include <unordered_map>
#include <QMdiSubWindow>
#include <memory>
#include <QMessageBox>
#include <QPushButton>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Load_menu();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Load_menu()
{
    QMenuBar * menubar = new QMenuBar(this);

    QMenu *menu_file = new QMenu;
    QMenu *menu_edit = new QMenu;
    QMenu *menu_window = new QMenu;
    QMenu *menu_help = new QMenu;

    menu_file->setTitle("文件(&F)");
    menu_edit->setTitle("编辑(&E)");
    menu_window->setTitle("窗口(&W)");
    menu_help->setTitle("帮助(&H)");

    menubar->addMenu(menu_file);
    menubar->addMenu(menu_edit);
    menubar->addMenu(menu_window);
    menubar->addMenu(menu_help);

    // 文件-动作
    QAction *add_file = new QAction(QIcon("d:\\1.png"),"新建文件(&N)",this);
    QAction *open_file = new QAction(QIcon("d:\\openfile.png"),"打开文件(&O)",this);
    QAction *save_file = new QAction(QIcon(""),("保存(&S)"),this);
    QAction *save_file_as = new QAction(QIcon(""),("另存为(&A)..."),this);
    QAction *exit = new QAction(QIcon(""),"退出(&X)",this);
    menu_file->addAction(add_file);
    menu_file->addAction(open_file);
    menu_file->addAction(add_sep());
    menu_file->addAction(save_file);
    menu_file->addAction(save_file_as);
    menu_file->addAction(add_sep());
    menu_file->addAction(exit);
    add_file->setShortcut(tr("Ctrl+N"));

    //编辑-动作
    QAction *undo = new QAction(QIcon(""),"撤销(&U)",this);
    QAction *restore = new QAction(QIcon(""),"恢复(&E)",this);
    QAction *shear = new QAction(QIcon(""),"剪切(&T)",this);
    QAction *copy = new QAction(QIcon(""),"复制(&C)",this);
    QAction *paste = new QAction(QIcon(""),"粘贴(&P)",this);
    menu_edit->addAction(undo);
    menu_edit->addAction(restore);
    menu_edit->addAction(add_sep());
    menu_edit->addAction(shear);
    menu_edit->addAction(copy);
    menu_edit->addAction(paste);
    undo->setShortcut(tr("Ctrl+Z"));
    copy->setShortcut(tr("Crtl+c"));
    paste->setShortcut(tr("Ctrl+v"));
    shear->setShortcut(tr("Ctrl+X"));

    //窗口-动作
    QAction *close = new QAction(QIcon(""),"关闭(&O)",this);
    QAction *close_all = new QAction(QIcon(""),"关闭所有窗口(&A)",this);
    QAction *tail = new QAction(QIcon(""),"平铺（&T)",this);
    QAction *stack = new QAction(QIcon(""),"层叠(&C)",this);
    QAction *next = new QAction(QIcon(""),"下一个(&X)",this);
    QAction *last = new QAction(QIcon(""),"上一个(&V)",this);
    menu_window->addAction(close);
    menu_window->addAction(close_all);
    menu_window->addAction(add_sep());
    menu_window->addAction(tail);
    menu_window->addAction(stack);
    menu_window->addAction(add_sep());
    menu_window->addAction(next);
    menu_window->addAction(last);

    //帮助-动作
    QAction *about = new QAction(QIcon(""),"关于(&A)",this);
    QAction *about_qt = new QAction(QIcon(""),"关于Qt(&Q)",this);
    menu_help->addAction(about);
    menu_help->addAction(about_qt);

    //信号槽机制
    qDebug()<<connect(add_file,&QAction::triggered,this,[=](){creat_new_file();});
    qDebug()<<connect(open_file,&QAction::triggered,this,[=](){fun_open_file();});
    qDebug()<<connect(save_file,&QAction::triggered,this,[=](){fun_save_file();});
    qDebug()<<connect(save_file_as,&QAction::triggered,this,[=](){fun_save_file_as();});
    qDebug()<<connect(exit,&QAction::triggered,this,[=](){fun_save_file_as();if(!ui->mdiArea->currentSubWindow()) this->close();});
    qDebug()<<connect(close,&QAction::triggered,this,[=](){ui->mdiArea->closeActiveSubWindow();});
    qDebug()<<connect(close_all,&QAction::triggered,this,[=]()
    {
        stop_close = 0;
        while(ui->mdiArea->currentSubWindow()&&!stop_close)
            ui->mdiArea->closeActiveSubWindow();
    });
    qDebug()<<connect(copy,&QAction::triggered,this,[=](){fun_copy();});
    qDebug()<<connect(paste,&QAction::triggered,this,[=](){fun_pasted();});
    qDebug()<<connect(shear,&QAction::triggered,this,[=](){fun_cut();});
    qDebug()<<connect(undo,&QAction::triggered,this,[=](){fun_undo();});
    qDebug()<<connect(restore,&QAction::triggered,this,[=](){fun_regain();});

    this->setMenuBar(menubar);
}

QAction *MainWindow::add_sep()
{
    QAction *sep = new QAction(this);
    sep->setSeparator(true);
    return sep;
}

MyTextEdit* MainWindow::creat_new_file()
{
    // 在MDW 中新建一个 TEXT-EDIT
    QString title = get_default_title();
    MyTextEdit* new_window = creat_new_file(title);
    return new_window;
}

MyTextEdit* MainWindow::creat_new_file(const QString &file_title)
{
    MyTextEdit* new_window = new MyTextEdit(this);
    new_window->setWindowTitle(file_title);
    ui->mdiArea->addSubWindow(new_window);

    qDebug() << connect(new_window,&QTextEdit::textChanged,new_window,[=]()
    {
        new_window->fun_content_changed();
        record_action();
    });
    new_window->show();

    url_map[new_window] = file_title;
    path_map[file_title] = new_window;

    return new_window;
}

MyTextEdit* MainWindow::fun_open_file()
{
    // 打开某个文件
    // 调用系统获取文件名 -> 限定格式txt-> 非空则打开文件获取内-> 新建QTextEdit("文件名"+导入内容） 文件名如果重复，后面自动
    QString file_path = QFileDialog::getOpenFileName(this,tr("打开文本文件"),QString(),"*.txt");
    if(file_path.isEmpty()) return NULL;

    //文件名有效则获取其内容，并写入QTextEdit中
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
        return NULL;
    }

    MyTextEdit* new_window = creat_new_file( QFileInfo(file_path).fileName());
    new_window->blockSignals(1);
    url_map[new_window] = file_path;
    path_map[file_path] = new_window;

    QTextStream file_stream(&file);
    QByteArray file_all;

    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        file_all.append(line);
        qDebug()<< line <<endl;
    }
    new_window->setText(file_all);
    new_window->blockSignals(0);

    qDebug() << connect(new_window,&QTextEdit::textChanged,new_window,[=]()
    {
        new_window->fun_content_changed();
        record_action();
    });

    return new_window;
}

QString MainWindow::get_default_title()
{
    QString title("新建文件");
    int n = 1;
    while(path_map.find(title)!=path_map.end())
    {
        title = "新建文件("+QString::number(n)+")";
        n++;
    }
    return title;
}

bool MainWindow::fun_save_file()
{
    // 获取当前窗口-> 新建的还是打开的？-> 通过url_map查询
    // 如果是新建的 -> 调用系统函数 获得存储名称和路径-> 进行存储
    // 如果是打开的 -> 没有修改符的话,return
    //            -> 有修改符的话，根据url_map 获得路径，进行存储，并且更新文件名称去掉星

    QMdiSubWindow * curren_window = ui->mdiArea->currentSubWindow();
    if(!curren_window) return 0;

    MyTextEdit* window = dynamic_cast<MyTextEdit*>(curren_window->widget());

    if(window->have_path())
    {
        // 如果文件是打开的，存在路径的；
        // 如果文件未改动，直接返回
        if(!window->changed()) return 1;

        // 否则，将新内容存储到文件中去
        QString file_path = url_map[window];
        QString content = window->toPlainText();
        QFile file(file_path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug()<<"open file fail!"<<endl;
            return 0;
        }
        QTextStream out(&file);
        out << content;
        file.close();
        window->fun_content_dechanged();
        return 1;
    }
    else
    {
        // 新文件情况
        // 选择文件路径和名称->存储-> 添加到url_map中-> 去掉星星
        QString title = window->windowTitle();
        if(window->changed()) title.chop(1);
        title.append(".txt");

        // 获取路径 存储文件
        QString file_path = QFileDialog::getSaveFileName(this,tr("存储为"),title,"*.txt");
        if(file_path.isEmpty()) return 0;

        qDebug()<<file_path<<endl;

        QString content = window->toPlainText();
        QFile file(file_path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug()<<"open file fail!"<<endl;
            return 0;
        }
        QTextStream out(&file);
        out << content;
        file.close();

        // 更新path 和 title 并且去掉改动状态
        url_map[window] = file_path;
        path_map.erase(title);
        path_map[file_path] = window;

        title = QFileInfo(file_path).fileName();
        window->setWindowTitle(title);
        window->fun_content_dechanged();
        return 1;
    }
}

bool MainWindow::fun_save_file_as()
{
    // 某个文件另存为  1表示已经存储 0表示取消本次操作

    // 如果某个文件已经打开，则提示错误，要求重新选择
    // 如果是本身，那么提示对话框 “已存在，是否覆盖”
    // 如果是 未打开/不存在文件，则 声明文件-> 写入 -> 改名 -> 更新表格
    // 如果是存在文件，存储前进行提示

    if(!ui->mdiArea->currentSubWindow()) return 1;

    MyTextEdit *window = dynamic_cast<MyTextEdit*>(ui->mdiArea->currentSubWindow()->widget());
    QString title = window->windowTitle();
    if(*(title.end()-1)=="*") title.chop(1);

    // 另存为路径
    QString file_path = QFileDialog::getSaveFileName(this,tr("另存为"),title,"*.txt");
    if(file_path.isEmpty()) return 0;

    // 文件被其他窗口打开了 || 选择的路径存在文件， 需要询问
    QFileInfo f(file_path);
    while((path_map.find(file_path)!=path_map.end()&&path_map[file_path]!=ui->mdiArea->currentSubWindow()->widget())
          ||(path_map.find(file_path)!=path_map.end()&&f.isFile()))
    {
        if(path_map.find(file_path)!=path_map.end()&&path_map[file_path]!=ui->mdiArea->currentSubWindow()->widget())
        {
            QMessageBox error(this);
            error.setWindowTitle("文件已被打开");
            error.setText("给定文档所定的名称不能与打开的文档名称相同。\n请为需要保存的文档键入其他名称。\n");
            error.setIcon(QMessageBox::Information);
            error.setStandardButtons(QMessageBox::Ok);
            error.exec();

            file_path = QFileDialog::getSaveFileName(this,tr("另存为"),title,"*.txt");
            qDebug()<<file_path<<endl;
        }
        else
        {
            //如果文件已经存在，进行提示是否覆盖，不覆盖就继续选择其他路径

            QMessageBox mes(this);
            mes.setWindowTitle("文件已存在");
            mes.setText("给定文档已经存在，是否覆盖？");
            mes.setIcon(QMessageBox::Information);
            mes.setStandardButtons(QMessageBox::Ok);
            mes.setStandardButtons(QMessageBox::No);
            int r = mes.exec();
            if(r==QMessageBox::Ok) break;
            else if(r==QMessageBox::No)
            {
                file_path = QFileDialog::getSaveFileName(this,tr("另存为"),title,"*.txt");
                if(file_path.isEmpty()) return 0;
            }
            else return 0;
        }

    }
    // 放弃存储
    if(file_path.isEmpty()) return 0;
    else if(!window->have_path())          //到此路径已经合法
    {
        // 未被本应用打开情况，打开文件并且写入，然后更新路径和标题
        QString content = window->toPlainText();

        QFile file(file_path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug()<<"open file fail!"<<endl;
            return 0;
        }
        QTextStream out(&file);
        out << content;
        file.close();

        // 更新path_map 和 标题 以及窗口状态
        url_map[window]=file_path;
        path_map.erase(title);
        path_map[file_path]=window;
        title = QFileInfo(file_path).fileName();
        window->setWindowTitle(title);
        window->fun_content_dechanged();
        return 1;
    }
    else
    {
        // 已经被打开，且就是本身,写入文件，更改状态即可
         QString content = window->toPlainText();
         QFile file(file_path);
         if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         {
             qDebug()<<"open file fail!"<<endl;
             return 0;
         }
         QTextStream out(&file);
         out << content;
         file.close();
         window->fun_content_dechanged();
         return 1;
    }
}

void MainWindow::erase_window_from_map(MyTextEdit *window)
{
    if(url_map.find(window)==url_map.end()) return;

    QString path = url_map[window];
    url_map.erase(window);
    path_map.erase(path);
}

void MainWindow::record_action()
{
    if(!ui->mdiArea->currentSubWindow()) return;
    MyTextEdit* window = dynamic_cast<MyTextEdit*>(ui->mdiArea->currentSubWindow()->widget());
    window->record_action(window->toPlainText());
}

bool MainWindow::fun_close_file()
{
    if(!ui->mdiArea->currentSubWindow()) return 1;
    MyTextEdit* window = dynamic_cast<MyTextEdit*>(ui->mdiArea->currentSubWindow()->widget());
    return do_close_file(window);
}

void MainWindow::fun_undo()
{
    if(!ui->mdiArea->currentSubWindow()) return;
    MyTextEdit* window = dynamic_cast<MyTextEdit*>(ui->mdiArea->currentSubWindow()->widget());
    window->undo_action();
}

void MainWindow::fun_regain()
{
    if(!ui->mdiArea->currentSubWindow()) return;
    MyTextEdit* window = dynamic_cast<MyTextEdit*>(ui->mdiArea->currentSubWindow()->widget());
    window->regain_action();
}

void MainWindow::fun_copy()
{
    if(!ui->mdiArea->currentSubWindow()) return;
    MyTextEdit* window = dynamic_cast<MyTextEdit*>(ui->mdiArea->currentSubWindow()->widget());
    if(!window->textCursor().selectedText().isEmpty()) clipboard = window->textCursor().selectedText();
}

void MainWindow::fun_cut()
{
    if(!ui->mdiArea->currentSubWindow()) return;
    MyTextEdit* window = dynamic_cast<MyTextEdit*>(ui->mdiArea->currentSubWindow()->widget());
    if(!window->textCursor().selectedText().isEmpty())
    {
        clipboard = window->textCursor().selectedText();
        window->textCursor().removeSelectedText();
    }
}

void MainWindow::fun_pasted()
{
    // 粘贴
    if(!ui->mdiArea->currentSubWindow()||clipboard.isEmpty()) return;
    MyTextEdit* window = dynamic_cast<MyTextEdit*>(ui->mdiArea->currentSubWindow()->widget());
    window->textCursor().insertText(clipboard);
}


bool MainWindow::do_close_file(MyTextEdit *window)
{
    // 关闭某个窗口的实际步骤

    // 如果是新建文件-> 询问是否保存 ->
    // 1.不保存-> 关闭
    // 2.保存-> 保存函数 -> 关闭

    // 如果是存在路径文件 -> 如果有修改，则询问是否保存

    if(!window->have_path())
    {
        // 新建文件情况
        QMessageBox mes(this);
        QString title = window->windowTitle();
        if(*(title.end()-1)=="*") title.chop(1);

        mes.setWindowTitle("多文档编辑器");
        mes.setText(QString("是否保存"+title+".txt"));
        mes.setIcon(QMessageBox::Icon::Warning);

        mes.setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        mes.setButtonText(QMessageBox::Yes,QString("是"));
        mes.setButtonText(QMessageBox::No,QString("否"));
        mes.setButtonText(QMessageBox::Cancel,QString("取消"));

        int f = mes.exec();

        if(f==QMessageBox::Yes)
        {
            // 调用存储函数，并且退出
            qDebug()<<"Yes"<<endl;
            if(!fun_save_file()) return 0;
            erase_window_from_map(window);
            ui->mdiArea->closeActiveSubWindow();
            return 1;
        }
        else if(f==QMessageBox::No)
        {
            //直接退出
            erase_window_from_map(window);
            ui->mdiArea->closeActiveSubWindow();
            qDebug()<<"No"<<endl;
            return 1;
        }
        else return 0; // 取消则什么都不做
    }
    else
    {
        // 被打开文件情况 没修改过的文件则直接关闭，否则询问是否

        if(!window->changed())
        {
             ui->mdiArea->closeActiveSubWindow();
             return 1;
        }
        else
        {
            QMessageBox mes(this);
            QString title = window->windowTitle();
            if(*(title.end()-1)=="*") title.chop(1);

            mes.setWindowTitle("多文档编辑器");
            mes.setText(QString("是否保存对("+title+")的更改？"));
            mes.setIcon(QMessageBox::Icon::Warning);

            mes.setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
            mes.setButtonText(QMessageBox::Yes,QString("是"));
            mes.setButtonText(QMessageBox::No,QString("否"));
            mes.setButtonText(QMessageBox::Cancel,QString("取消"));

            int f = mes.exec();

            if(f==QMessageBox::Yes)
            {
                // 调用存储函数，并且退出
                if(!fun_save_file()) return 0;

                erase_window_from_map(window);
                ui->mdiArea->closeActiveSubWindow();
                return 1;
            }
            else if(f==QMessageBox::No)
            {
                //直接退出
                erase_window_from_map(window);
                ui->mdiArea->closeActiveSubWindow();
                return 1;
            }
            else return 0; // 取消则什么都不做
        }
    }
}

bool MainWindow::fun_close_all()
{
    while(ui->mdiArea->currentSubWindow())
    {
        if(fun_close_file()) continue;
        else return 0;
    }
    return 1;
}


MyTextEdit::~MyTextEdit()
{
    p->erase_window_from_map(this);
}

void MyTextEdit::closeEvent(QCloseEvent *even)
{
    if(p->do_close_file(this))
    {
        even->accept();
    }
    else
    {
        even->ignore();
        p->stop_close = 1;
    }
}

void MyTextEdit::fun_content_dechanged()
{
    if(!content_changed) return;
    content_changed = 0;
    if(*(title.end()-1)=="*")
    {
        title.chop(1);
        setWindowTitle(title);
    }
}


void MyTextEdit::record_action(const QString &content)
{
    // 记录某次的操作
    // 最多记录20次
    if(c_stack_pos<20)
    {
        if(c_stack_pos!=content_stack.size()-1)
            content_stack.erase(content_stack.begin()+c_stack_pos+1,content_stack.end());

        content_stack.push_back(content);
        c_stack_pos++;
    }
    else
    {
        //c_stack_pos =20;
        content_stack.pop_front();
        content_stack.push_back(content);
    }
}

void MyTextEdit::undo_action()
{
    // 撤销一步
    if(c_stack_pos==0) return;
    else
    {
        this->blockSignals(1);
        setText(content_stack[c_stack_pos-1]);
        c_stack_pos--;
        this->blockSignals(0);
    }
}

void MyTextEdit::regain_action()
{
    // 恢复一步
    if(c_stack_pos>=content_stack.size()-1)
        return;
    else
    {
        this->blockSignals(1);
        setText(content_stack[c_stack_pos+1]);
        c_stack_pos++;
        this->blockSignals(0);
    }
}

void MyTextEdit::fun_content_changed()
{
    if(content_changed) return;
    content_changed =1;
    title+="*";
    setWindowTitle(title);
}
