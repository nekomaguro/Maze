#include"../standard.h"
#include"default.h"
#include"../random.h"

void Default::fullFill(char* input,int size,char select){
    for(int count=0;count<size;count++){
        *(input+count)=select;
    }
}

void Default::frame(char* input,int xlength,int ylength,char select){
    for(int count=0;count<xlength;count++){
        *(input+xlength*0+count)=select;
    }
    for(int count=1;count<ylength-1;count++){
        *(input+xlength*count+0)=select;
        *(input+xlength*count+(xlength-1))=select;
    }
    for(int count=0;count<xlength;count++){
        *(input+xlength*(ylength-1)+count)=select;
    }
}

void Default::place(char* input,int xlength,int ylength,int x,int y,char select){
    if((x > xlength)||(y > ylength)||(x < 1)||(y < 1)) {
        throw std::logic_error("place error");
    }
    *(input+xlength*(y-1)+(x-1))=select;
}

char Default::search(char* input,int xlength,int ylength,int x,int y){
    if((x > xlength)||(y > ylength)||(x < 1)||(y < 1)) {
        printf("(%d,%d)",x,y);
        throw std::logic_error("search error");
    }
    return *(input+xlength*(y-1)+(x-1));
}

void Default::line(char* input,int xlength,int ylength,int x,int y,int direction,int length,char select){
    if((x > xlength)||(y > ylength)||(x < 1)||(y < 1)) {
        throw std::logic_error("line error");
    }
    switch(direction){
        case UP:
        if(y < length){
            throw std::logic_error("line error");
        }
        for(int count=0;count<length;count++) *(input+xlength*(y-1-count)+(x-1))=select;
        break;

        case DOWN:                
        if(ylength-y+1 < length){
            throw std::logic_error("line error");
        }
        for(int count=0;count<length;count++) *(input+xlength*(y-1+count)+(x-1))=select;
        break;

        case RIGHT:
        if(xlength-x+1 < length){
            throw std::logic_error("line error");
        }
        for(int count=0;count<length;count++) *(input+xlength*(y-1)+(x-1)+count)=select;
        break;

        case LEFT:
        if(x < length){
            throw std::logic_error("line error");
        }
        for(int count=0;count<length;count++) *(input+xlength*(y-1)+(x-1)-count)=select;
        break;

        default:
        return;
    }
}

int Default::scan(char* input,int size,char scan){
    int amount = 0;
    for(int count=0;count<size;count++){
        if(*(input+count) == scan){
            amount++;
        }
    }
    return amount;
}