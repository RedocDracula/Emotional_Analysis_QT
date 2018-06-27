#ifndef QEXTEND_H
#define QEXTEND_H
#include <QLabel>
#include <QDateTime>
#include <algorithm>
#include <QComboBox>

extern std::vector <long long int> startTime;
extern std::vector <long long int> endTime;
extern std::vector <std::string> sstarttime;
extern std::vector <std::string> sendtime;
extern std::vector <std::string > subtitle;
extern std::vector<int> emotion;
extern bool subLoaded;
extern bool parsed;
extern bool detect( cv::Mat& img);



class Qextend : public QLabel
{
    Q_OBJECT

    public:
    explicit Qextend(QWidget *parent) : QLabel(parent)
    {}

    public slots:
    void takeSnip(qint64 milliseconds) {
        //
        milliseconds/=1000;
        std::string currTime =  QDateTime::fromTime_t(milliseconds).toUTC().toString("hh:mm:ss").toStdString();
        // take snip...save snip open
        // if face not fou


    }

        void setSubtitle (qint64 currtime) {
            if (subLoaded && parsed) {
                    bool detect( cv::Mat& img)std:: vector <long long int> :: iterator pointer = lower_bound(startTime.begin(),startTime.end(),currtime);
                    int index = pointer - startTime.begin();

                    if (currtime<endTime[index-1]) {
                        this->setText(QString::fromUtf8(subtitle[index-1].c_str()));
                    } else {
                        this->setText("\0");
                    }
            }
         }



};


class QComboExtend : public QComboBox
{
    Q_OBJECT

    public:
    explicit QComboExtend(QWidget *parent) : QComboBox(parent)
    {}

    public slots:
    void setValue(qint64 currtime) {
        if (subLoaded && parsed) {
        std:: vector <long long int> :: iterator pointer = lower_bound(startTime.begin(),startTime.end(),currtime);
        int index = pointer - startTime.begin();
        int emot = emotion[index];
        this->setCurrentIndex(emot-1);
        }
    }




};
#endif // QEXTEND_H
