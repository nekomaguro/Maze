#include"../standard.h"
#include"buf.h"

Buf::Buf(int xLeng,int yleng){
    xLength = xLeng;
    yLength = yleng;
    size = xLeng * yleng;

    buf = (char*)malloc(sizeof(char)*size);
    if(buf == NULL){
        throw std::runtime_error("malloc error");
    }
}

Buf::~Buf(){
    free(buf);
}

void Buf::fullFill(char select){
    Default::fullFill(buf,size,select);
}

void Buf::frame(char select){
    Default::frame(buf,xLength,yLength,select);
}

void Buf::place(int x,int y,char select){
    Default::place(buf,xLength,yLength,x,y,select);
}

char Buf::search(int x,int y){
    return Default::search(buf,xLength,yLength,x,y);
}

void Buf::line(int x,int y,int direction,int length,char select){
    Default::line(buf,xLength,yLength,x,y,direction,length,select);
}

int Buf::scan(char scan){
    return Default::scan(buf,size,scan);
}

char* Buf::getBuf(){
    return buf;
}

void Buf::input(char* in,int xleng,int yleng,int x,int y){
    if((x > xLength)||(y > yLength)||(x < 1)||(y < 1)) {
        throw std::logic_error("input error");
    }

    if((x + xleng - 1 > xLength) || (y + yleng - 1 > yLength)){
        throw std::logic_error("input error");
    }

    int countY;
    int countX;
    for(countY = 0;countY < yleng;countY++){
        for(countX = 0;countX < xleng;countX++){
            *(buf+xLength*(countY+(y-1))+countX+(x-1)) = *(in+xleng*(countY)+countX);
        }
    }
}