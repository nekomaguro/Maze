#ifndef OPTION_H
#define OPTION_H

#include"YNquestion.h"
#include"default.h"

class Option : Default
{
    private:
        char* dialog;
        int xleng;
        int yleng;
        char** options;
        int leng;
        int* optionsX;
        int* optionsY;
        int* optionsLeng;
        int which;

    public:
        Option(int optleng,int xlen,int ylen);
        ~Option();
        void fullFill(char select);
        void frame(char select);
        void place(int x,int y,char select);
        void optionSet(int num,char* option,int optleng,int x,int y);
        void setDown();
        void setUp();
        int getWhich();
        char* getDialog();
        int getXleng();
        int getYleng();

};

#endif