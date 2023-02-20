#ifndef DEFAULT_H
#define DEFAULT_H

class Default
{
    public:
        virtual void fullFill(char* input,int size,char select);
        virtual void frame(char* input,int xlength,int ylength,char select);
        virtual void place(char* input,int xlength,int Ylength,int x,int y,char select);
        virtual char search(char* input,int xlength,int Ylength,int x,int y);
        virtual void line(char* input,int xlength,int Ylength,int x,int y,int direction,int length,char select);
        virtual int scan(char* input,int size,char scan);
};

#endif