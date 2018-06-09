#ifndef PARSER_CPP
#define PARSER_CPP
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QDebug>
#include <vector>
#include <string>
#include <ctype.h>
#define maxCharacters 500


std::vector <long long int> startTime;
std::vector <long long int> endTime;
std::vector <std::string> sstarttime;
std::vector <std::string> sendtime;
std::vector <std::string > subtitle;
bool parsed = false;

long long int convert (char * temp) {
    int hh,mm,ss,ms;
    char tim [4];
    tim[0] = temp[0];
    tim[1] = temp[1];
    tim[2] = '\0';
    hh = atoi(tim);

    tim[0] = temp[3];
    tim[1] = temp[4];
    tim[2] = '\0';
    mm = atoi(tim);

    tim[0] = temp[6];
    tim[1] = temp[7];
    tim[2] = '\0';
    ss = atoi(tim);

    tim[0] = temp[9];
    tim[1] = temp[10];
    tim[2] = temp[11];
    tim[3] = '\0';

    ms = atoi(tim);

    return hh*60*60*1000+mm*60*1000+ss*1000+ms;
}


void getTime (char * file) {
    char  tempString [maxCharacters+1];
    FILE * fp = fopen(file,"r");
    FILE * fout = fopen ("output.txt","w");
    char string1[25];
    char string2[25];
    char string3[25];

    while (!feof(fp)) {
        fgets (tempString,maxCharacters,fp);

          if (tempString[2]==':' && tempString[5]==':') {

            sscanf (tempString,"%s %s %s", string1, string2, string3);

            startTime.push_back(convert(string1));
            sstarttime.push_back(string1);
            sendtime.push_back(string3);
            endTime.push_back(convert(string3));
            fgets (tempString,maxCharacters,fp);
            std::string copyStr = tempString;
            subtitle.push_back(copyStr);

         }

        }

        qDebug() << "Total Lines Extracted "<<subtitle.size();


    qDebug() << subtitle.size();
    parsed = true;

    fclose(fp);
    fclose(fout);

}

using namespace std;


void xmlUpdate ( int snipNo, string timeBegin, string timeEnd, string age, string gender, string identity,string semantic ,const char * fd) {
    FILE * fp = fopen (fd,"r+");
    if (fp==NULL) { //FILE is EMPTY
        fp = fopen(fd,"w+"); // Create File
        fprintf(fp,"<xml>\n");
        fprintf(fp,"</xml>\n");
        fclose(fp);
    }
    fp = fopen (fd,"r+");
    fseek(fp,-7,SEEK_END);
    fprintf(fp,"\n\t<snip%d>\n",snipNo);
    fprintf(fp,"\t\t<durationStart> %s  </durationStart>\n",timeBegin.c_str());
    fprintf(fp,"\t\t<durationEnd> %s  </durationEnd>\n",timeEnd.c_str());
    fprintf(fp,"\t\t<identity> %s  </identity>\n",identity.c_str());
    fprintf(fp,"\t\t<gender> %s  </gender>\n",gender.c_str());
    fprintf(fp,"\t\t<age> %s  </age>\n",age.c_str());
    fprintf(fp,"\t\t<semantic> %s  </semantic>\n",semantic.c_str());
    fprintf(fp,"\t</snip%d>\n",snipNo);
    fprintf(fp,"</xml>\n");
    fclose(fp);
}

#endif








