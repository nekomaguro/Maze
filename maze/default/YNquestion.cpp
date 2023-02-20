#include"../standard.h"
#include"YNquestion.h"

void YNQuestion::fullFill(char select){
    Default::fullFill(question,size,select);
}

void YNQuestion::frame(char select){
    Default::frame(question,xLength,yLength,select);
}

void YNQuestion::place(int x,int y,char select){
    Default::place(question,xLength,yLength,x,y,select);
}

YNQuestion::YNQuestion(int xleng,int yleng,int lin,int spac){
    xLength = xleng;
    yLength = yleng;
    size = xleng * yleng;
    line = lin;
    space = spac;

    question = (char*)malloc(sizeof(char)*size);
    if(question==NULL){
        throw std::runtime_error("malloc error");
    }

    YNQuestion::fullFill(' ');
    YNQuestion::frame('O');

    if(xLength-2 < space+2+3+2){
        throw std::logic_error("question error");
    }
    if((line <= 1) || (line >= yLength)){
        throw std::logic_error("question error");
    }

    int middle;
    int spaceNum = space/2;
    if(xLength%2 == 0){
        middle = xLength/2;
    }
    else if(xLength%2 == 1){
        middle = xLength/2 + 1;
    }

    Npoint = middle+spaceNum;
    place(Npoint+1,line,'N');
    place(Npoint+2,line,'O');

    if(spac%2 == 0){
        spaceNum -=1;
    }

    Ypoint = middle-spaceNum;
    place(Ypoint-1,line,'S');
    place(Ypoint-2,line,'E');
    place(Ypoint-3,line,'Y');

    setNo();
}

YNQuestion::~YNQuestion(){
    free(question);
    free(string);
}

void YNQuestion::setNo(){
    place(Npoint,line,'<');
    place(Npoint+3,line,'>');

    place(Ypoint,line,' ');
    place(Ypoint-4,line,' ');

    YesOrNo = 'N';
}

void YNQuestion::setYes(){
    place(Ypoint,line,'>');
    place(Ypoint-4,line,'<');

    place(Npoint,line,' ');
    place(Npoint+3,line,' ');

    YesOrNo = 'Y';
}

void YNQuestion::stringSet(char* str,int leng,int x,int y){
    if((x > xLength) || (y > yLength)){
        throw std::logic_error("option error");
    }
    if(x + (leng - 1) > xLength){
        throw std::logic_error("option error");
    }
    
    stringLeng = leng;
    stringX = x;
    stringY = y;

    string = (char*)malloc(sizeof(char)*stringLeng);
    if(string == NULL){
        throw std::runtime_error("malloc error");
    }

    string = str;

    for(int countX=0;countX<stringLeng;countX++){
        place(countX+stringX,stringY,*(string+countX));
    }
}


char * YNQuestion::getQue(){

    return question;
}

int YNQuestion::getXleng(){
    return xLength;
}

int YNQuestion::getYleng(){
    return yLength;
}

int YNQuestion::getLine(){
    return line;
}

int YNQuestion::getSpace(){
    return space;
}

int YNQuestion::getYorN(){
    return YesOrNo;
}