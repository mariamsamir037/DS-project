#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Clear_btn_clicked()
{
    ui->input_text->clear();
    //ui->statusbar->clearMessage();
 }



void MainWindow::on_Browse_btn_clicked()
{
    //QFile file("/home/smile/GUI/sample.xml");
    QString extn = ".xml (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file", QDir::homePath(),extn);
    QFile file (file_name);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->input_text->setPlainText(text);
    file.close();
    //ui->input_text->insertPlainText("World ");
}


void MainWindow::on_Save_btn_clicked()
{
     //ui->input_text->insertPlainText("hello ");
    QString file_name = QFileDialog::getSaveFileName(this,"Save As", QDir::homePath());
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","file not open");
    }
    else{
    QTextStream out(&file);
    QString text = ui->input_text->toPlainText();
    out<<text;
    file.flush();
    file.close();
    ui->statusbar->showMessage("Successfully saved",5000);
    }
}



void MainWindow::on_actionbrowse_triggered()
{
    QString extn = ".xml (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file", QDir::homePath(),extn);
    QFile file (file_name);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","file not open");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->input_text->setPlainText(text);
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Save As", QDir::homePath());
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"Warning","file not open");
    }
    else{
    QTextStream out(&file);
    QString text = ui->input_text->toPlainText();
    out<<text;
    file.flush();
    file.close();
    ui->statusbar->showMessage("Successfully saved",5000);
    }
}


void MainWindow::on_actionClear_triggered()
{
    ui->input_text->clear();
}


void MainWindow::on_CheckErr_btn_clicked()
{
//    QString qstr = ui->input_text->toPlainText();
//    std:: string str=qstr.toStdString();
//    //str.erase(std::remove_if(str.begin(), str.end(), ::isspace));
//    //str=str.substr(0,100);
//    //ashuf howa kam kelma mesh sha8ala mzbut
//    std:: stringstream s(str);
//    std::string word;
//    int count = 0;
//    while (s >> word)
//        count++;
//    if(str.find("</")){
//    ui->statusbar->showMessage("Oba closing tag",1000);
//    }
//    QString qstr2 = QString::fromStdString(std::to_string(count));
//    //QString qstr2 = QString::fromStdString(str);
//    ui->output_text->setPlainText(qstr2);
}


void MainWindow::on_actionFull_Screen_triggered()
{

    if (isFullScreen()) {

        showNormal();
        }
    else {
        showFullScreen();
        ui->statusbar->showMessage("Click again on FullScreen to return to normal",5000);

    }
}


void MainWindow::on_actionExit_triggered()
{
   close();
}

