#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_Clear_btn_clicked();
    void on_actionClear_triggered();

    void on_actionFull_Screen_triggered();
    void on_actionExit_triggered();
    void on_Exit_Button_clicked();

    void on_Browse_btn_clicked();
    void on_actionbrowse_triggered();

    void on_Save_btn_clicked();
    void on_actionSave_as_triggered();

    void on_CheckErr_btn_clicked();
    void on_actionCheck_for_Errors_triggered();

    void on_Correct_btn_clicked();
    void on_actionCorrect_Errors_triggered();

    void on_Minify_btn_clicked();
    void on_actionMinify_triggered();

    void on_Convert_btn_clicked();
    void on_actionConver_to_Json_triggered();

    void on_Compress_btn_clicked();
    void on_actionCompress_triggered();

    void on_decompress_btn_clicked();
    void on_actionDecompress_triggered();

    void on_Prettify_btn_clicked();
    void on_actionPrettify_triggered();

    void on_Most_followed_clicked();
    void on_actionMost_Followed_triggered();

    void on_Most_Active_clicked();
    void on_actionMost_Active_triggered();

    void on_Mutual_friends_clicked();
    void on_actionMutual_Friends_triggered();

    void on_Recommend_friends_clicked();
    void on_actionSuggest_Friends_triggered();

    void on_Search_btn_clicked();
    void on_actionPost_Search_triggered();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
