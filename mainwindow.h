#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QSlider>
#include <QFile>
#include <QVideoFrame>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_pause_clicked();
    void on_saveButton_clicked();
    void on_actionAdd_Sub_triggered();
    void on_skipButton_clicked();
    void on_replayButton_clicked();

    void on_extractButton_clicked();

    void on_faceButton_clicked();
    
private:
    Ui::MainWindow *ui;
    QMediaPlayer * player;
    QVideoWidget *vw;
    QSlider * slid;
    bool current_state = 1;
    void setEnable();

};



#endif // MAINWINDOW_H
