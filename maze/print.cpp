#include"print.h"
#include"standard.h"

Print::Print(){
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Print::printdisp(char* input,int xlength,int ylength){
    for(int count1=0;count1<ylength;count1++){
        for(int count2=0;count2<xlength;count2++){
            printf("%c",*(input+xlength*count1+count2));
        }
        printf("\n");
        fflush(stdout);
    }
    fflush(stdout);
}

void Print::printdispd(char* input,int xlength,int ylength){
    for(int count1=0;count1<ylength;count1++){
        for(int count2=0;count2<xlength;count2++){
            printf("%d",*(input+xlength*count1+count2));
        }
        printf("\n");
        fflush(stdout);
    }
    fflush(stdout);
}

void Print::printDisp(char* input,int xlength,int ylength){
    SetConsoleCursorPosition(hStdout, (COORD){0,0} );
    printdisp(input,xlength,ylength);
}
