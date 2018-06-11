#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QMenuBar>
#include <QLabel>
#include <QDebug>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <QMessageBox>
#include <QProcess>
#include "qextend.h"
#include "parser.cpp"


extern std:: vector <long long int> startTime;
extern std:: vector <long long int> endTime;
int snip_number = 0;
void write();
bool vidLoaded = false;
bool subLoaded = false;



char *sourceVid =  new char[100];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->semanticBox->setEnabled(false);
    ui->ageBox->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->skipButton->setEnabled(false);
    ui->genderBox->setEnabled(false);
    ui->identityBox->setEnabled(false);
    ui->semanticLabel->setEnabled(false);
    ui->identityLabel->setEnabled(false);
    ui->genderLabel->setEnabled(false);
    ui->ageLabel->setEnabled(false);
    ui->pause->setEnabled(false);
    ui->replayButton->setEnabled(false);



    /* Player Codes*/
    player= new QMediaPlayer;
    vw = new QVideoWidget;
    player->setVideoOutput(vw);
    ui->videoArea->addWidget(vw);
    slid = new QSlider(this);
    slid->setOrientation(Qt::Horizontal);
    ui->slider->addWidget(slid);

    connect(player,&QMediaPlayer::durationChanged,slid,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slid,&QSlider::setValue); // if mediaplayer's position changes, reflect the change in the slider
    connect(slid,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);// if the slider's position changes (if user drags it ) , then reflect the change in the mediaplayer.
    slid->setEnabled(false);

    connect(player,&QMediaPlayer::positionChanged,ui->subbox,&Qextend::timefunc);

    ui->subbox->setVisible(true);
    ui->timeLayout->addWidget(ui->subbox);

    connect(player,&QMediaPlayer::positionChanged,ui->subText,&Qextend::setSubtitle);
    ui->subText->setVisible(true);
    ui->subLayout->addWidget(ui->subText);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setEnable() {
    ui->semanticBox->setEnabled(true);
    ui->ageBox->setEnabled(true);
    ui->saveButton->setEnabled(true);
    ui->skipButton->setEnabled(true);
    ui->genderBox->setEnabled(true);
    ui->identityBox->setEnabled(true);
    ui->semanticLabel->setEnabled(true);
    ui->identityLabel->setEnabled(true);
    ui->genderLabel->setEnabled(true);
    ui->ageLabel->setEnabled(true);
    ui->pause->setEnabled(true);
    ui->slider->setEnabled(true);
    slid->setEnabled(true);
    ui->replayButton->setEnabled(true);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open a file","","Video File (*.mp4)");
    qDebug()<<"filename: " <<filename<<"\n";

    QByteArray ba = filename.toLatin1();


    sourceVid = strcpy(sourceVid,ba.data());

    player->setMedia(QUrl::fromLocalFile(filename));
    player->play();
    vidLoaded=true;

    if (vidLoaded && subLoaded ) {
        setEnable();
    }

}

void MainWindow::on_actionQuit_triggered()

{
    qDebug()<<"Quit Triggered";
    QApplication::quit();
}

void write() {
    qDebug()<<"Xml Write Function Called";

}

void MainWindow::on_pause_clicked()
{

    if(current_state == true)
    {
        player->pause();
        current_state = false;
        ui->pause->setText("Play");
        qDebug()<<"The videoplayer has been paused \n";
    }
    else if(current_state == false)
    {
        player->play();
        current_state = true;
        ui->pause->setText("Pause");
       qDebug()<<"The videoplayer is currently playing\n";
    }

}

bool validate ()  {
    return true;

}

void MainWindow::on_saveButton_clicked()
{
    /*QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();*/
    bool validated = false;


    validated = validate();

    if (validated) {
        snip_number++;

        qDebug() <<player->position()<< "\n";
        qDebug()<<"Save Triggered";
        qint64 currPos = player->position(); //get the current position in video
        std:: string startsnip, endsnip,command, source(sourceVid); // stores the range of where to cut.
        std:: vector <long long int> :: iterator myveciterator;
        myveciterator = lower_bound(startTime.begin(),startTime.end(),currPos);
        int index = myveciterator - startTime.begin();
        startsnip = sstarttime[index], endsnip = sendtime[index];

        startsnip.erase(startsnip.end()-4 ,startsnip.end());
        endsnip.erase(endsnip.end()-4 ,endsnip.end());

        std::string destination = source;
       // std::stringForce = "ffmpeg -i " + source + "-force_key_frames"
        destination.erase(destination.end()-4 ,destination.end() );
        command = "ffmpeg -i " + source + " -ss " + startsnip + " -to " + endsnip + " -async 1 -strict -2 " + "-preset ultrafast " + "-y "  + destination + "_cut" + std::to_string(snip_number) +".mp4" ;
        std::cout<<command<<"\n\n";

        int cmdReturn = 1;
        player->pause();

        QMessageBox *mbox = new QMessageBox;
        mbox->setWindowTitle(tr("Please Wait..."));
        mbox->setText("Please wait while the snip is being processed...");
        mbox->show();
        mbox->setStandardButtons(0);

        cmdReturn = system(command.c_str());
        if (cmdReturn==0) {
            player->play();
            mbox->hide();
        }

        qDebug()<<cmdReturn;

        std::string xmldestination = destination + ".xml";


            xmlUpdate (snip_number, startsnip, endsnip,ui->ageBox->toPlainText().toStdString(), ui->genderBox->currentText().toStdString(), ui->identityBox->toPlainText().toStdString(),ui->semanticBox->currentText().toStdString(), xmldestination.c_str() );

    } else {
        QMessageBox msg;
        msg.setText("Sorry, Age is not valid " );
        msg.exec();
    }

}




void MainWindow::on_actionAdd_Sub_triggered()
{
    QString subname = QFileDialog::getOpenFileName(this,"Open a file","","Subtitle File (*.srt)");
    qDebug()<<subname<<"\n";
    QByteArray ba = subname.toLatin1();
    char *c_subname = ba.data();
    getTime(c_subname);
    qDebug() << "startTime Count in " <<startTime.size() <<"\n";
    subLoaded = true;
    if (subLoaded && vidLoaded ) {
        setEnable();
    }

}

void MainWindow::on_skipButton_clicked()
{
    qint64 current_time = player->position();
    std:: vector <long long int> :: iterator gotonext;
    gotonext = lower_bound(startTime.begin(),startTime.end(),current_time);
    player->setPosition(*gotonext);
}

void MainWindow::on_replayButton_clicked()
{
    qint64 currPosition = player->position();
    std:: vector <long long int> :: iterator myveciterator = lower_bound (startTime.begin(), startTime.end(), currPosition);
    myveciterator--;
    player->setPosition(*myveciterator);

}
