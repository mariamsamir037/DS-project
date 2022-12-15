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
 }



void MainWindow::on_Browse_btn_clicked()
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


void MainWindow::on_Save_btn_clicked()
{
    QFile file("/home/smile/GUI/Savedas.txt");

    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream out(&file);
    QString text = ui->input_text->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

