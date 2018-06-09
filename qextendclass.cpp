#include "qextend.h"
#include "parser.cpp"

void Qextend::subreturn(qint64 currtime)
{
    std:: vector <long long int> :: iterator pointer = lower_bound(startTime.begin(),startTime.end(),currtime);
    int index = pointer - startTime.begin();
    this->setText(QString::fromUtf8(subtitle[index].c_str()));

}
