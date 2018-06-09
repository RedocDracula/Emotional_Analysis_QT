#ifndef QEXTEND_H
#define QEXTEND_H
#include <QLabel>
#include <QDateTime>
#include <algorithm>

extern std::vector <long long int> startTime;
extern std::vector <long long int> endTime;
extern std::vector <std::string> sstarttime;
extern std::vector <std::string> sendtime;
extern std::vector <std::string > subtitle;
extern bool subLoaded;



class Qextend : public QLabel
{
    Q_OBJECT

    public:
    Qextend(QWidget *parent ) : QLabel()
    {}

    public slots:

        void timefunc(qint64 micro)
        {
            micro = micro/1000;
            this->setText(QDateTime::fromTime_t(micro).toUTC().toString("hh:mm:ss"));
        }

        void setSubtitle (qint64 currtime) {
            if (subLoaded) {
                    std:: vector <long long int> :: iterator pointer = lower_bound(startTime.begin(),startTime.end(),currtime);
                    int index = pointer - startTime.begin();
                    //auto pEnd  = upper_bound (endTime.begin(),endTime.end(),currtime);
                    if (currtime<endTime[index-1]) {
                        this->setText(QString::fromUtf8(subtitle[index-1].c_str()));
                    } else {
                        this->setText("\0");
                    }
            }
         }



};

#endif // QEXTEND_H
