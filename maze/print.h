#ifndef PRINT_H
#define PRINT_H

#include"standard.h"

class Print{
    private:
        HANDLE hStdout;
    public:
        Print();
        void printDisp(char* input,int xlength,int ylength);
        static void printdisp(char* input,int xlength,int ylength);
        static void printdispd(char* input,int xlength,int ylength);


};

#endif