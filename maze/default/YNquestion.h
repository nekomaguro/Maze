#ifndef YN_QUESTION_H
#define YN_QUESTION_H

#include"default.h"

class YNQuestion : Default
{
    private:
        char* question;
        int xLength;
        int yLength;
        int size;
        int line;
        int space;
        int Ypoint;
        int Npoint;
        char YesOrNo;
        char* string;
        int stringX;
        int stringY;
        int stringLeng;

    public:
        YNQuestion(int xleng,int yleng,int line,int space);
        ~YNQuestion();
        void fullFill(char select);
        void frame(char select);
        void place(int x,int y,char select);
        void stringSet(char* str,int leng,int x,int y);
        char* getQue();
        int getXleng();
        int getYleng();
        int getLine();
        int getSpace();
        int getYorN();
        void setNo();
        void setYes();
};

#endif