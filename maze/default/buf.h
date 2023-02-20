#ifndef BUF_H
#define BUF_H

#include"default.h"

class Buf : public Default
{
    private:
        char* buf;
        int size;
        int xLength;
        int yLength;

    public:
        Buf(int xleng,int yleng);
        ~Buf();
        void fullFill(char select);
        void frame(char select);
        void place(int x,int y,char select);
        char search(int x,int y);
        void line(int x,int y,int direction,int length,char select);
        int scan(char scan);
        char* getBuf();
        void input(char* in,int xleng,int yleng,int x,int y);
};

#endif