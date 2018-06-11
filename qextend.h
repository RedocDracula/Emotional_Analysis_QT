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
extern bool parsed;



class Qextend : public QLabel
{
    Q_OBJECT

    public:
    explicit Qextend(QWidget *parent) : QLabel()
    {}

    public slots:

        void timefunc(qint64 milliseconds)
        {
            milliseconds/=1000; // convert
            this->setText(QDateTime::fromTime_t(milliseconds).toUTC().toString("hh:mm:ss"));
        }

        void setSubtitle (qint64 currtime) {
            if (subLoaded && parsed) {
                    std:: vector <long long int> :: iterator pointer = lower_bound(startTime.begin(),startTime.end(),currtime);
                    int index = pointer - startTime.begin();
                    if (currtime<endTime[index-1]) {
                        this->setText(QString::fromUtf8(subtitle[index-1].c_str()));
                    } else {
                        this->setText("\0");
                    }
            }
         }



};

#endif // QEXTEND_H
