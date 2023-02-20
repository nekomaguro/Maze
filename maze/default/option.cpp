#include"standard.h"
#include"option.h"
#include"YNquestion.h"

void Option::fullFill(char select){
    Default::fullFill(dialog,xleng*yleng,select);
}

void Option::frame(char select){
    Default::frame(dialog,xleng,yleng,select);
}

void Option::place(int x,int y,char select){
    Default::place(dialog,xleng,yleng,x,y,select);
}

Option::Option(int optleng,int xlen,int ylen){
    xleng = xlen;
    yleng = ylen;

    leng = optleng;

    dialog = (char*)malloc(sizeof(char)*xlen*ylen);
    if(dialog == NULL){
        throw std::runtime_error("malloc error");
    }

    options = (char**)malloc(sizeof(char*)*optleng);
    if(options == NULL){
        throw std::runtime_error("malloc error");
    }

    optionsX = (int*)malloc(sizeof(int)*optleng);
    if(optionsX == NULL){
        throw std::runtime_error("malloc error");
    }

    optionsY = (int*)malloc(sizeof(int)*optleng);
    if(optionsY == NULL){
        throw std::runtime_error("malloc error");
    }

    optionsLeng = (int*)malloc(sizeof(int)*optleng);
    if(optionsLeng == NULL){
        throw std::runtime_error("malloc error");
    }

    which = 1;

    Option::fullFill(' ');
    Option::frame('O');
}

Option::~Option(){
    for(int count;count<leng;count++){
        free(options[count]);
    }
    free(dialog);
    free(optionsX);
    free(optionsY);
    free(optionsLeng);
}

void Option::optionSet(int num,char* option,int optleng,int x,int y){
    if(num > leng){
        throw std::logic_error("option error");
    }

    optionsX[num-1] = x;
    optionsY[num-1] = y;
    optionsLeng[num-1] = optleng;

    if((x > xleng) || (y > yleng)){
        throw std::logic_error("option error");
    }
    if(x + (optleng - 1) + 2 > xleng){
        throw std::logic_error("option error");
    }

    options[num-1] = (char*)malloc(sizeof(char)*optleng);
    if(options[num-1] == NULL){
        throw std::runtime_error("malloc error");
    }

    options[num-1] = option;

    for(int countX=0;countX<optionsLeng[num-1];countX++){
        place(countX+optionsX[num-1],optionsY[num-1],*(options[num-1]+countX));
    }

    if(num==1){
        place(optionsX[num-1]+(optionsLeng[num-1]-1)+1,optionsY[num-1],'<');
        place(optionsX[num-1]+(optionsLeng[num-1]-1)+2,optionsY[num-1],'-');

    }
}

void Option::setDown(){
    if(which == leng){
        return;
    }
    place(optionsX[which-1]+(optionsLeng[which-1]-1)+1,optionsY[which-1],' ');
    place(optionsX[which-1]+(optionsLeng[which-1]-1)+2,optionsY[which-1],' ');

    which++;
    place(optionsX[which-1]+(optionsLeng[which-1]-1)+1,optionsY[which-1],'<');
    place(optionsX[which-1]+(optionsLeng[which-1]-1)+2,optionsY[which-1],'-');

}

void Option::setUp(){
    if(which == 1){
        return;
    }
    place(optionsX[which-1]+(optionsLeng[which-1]-1)+1,optionsY[which-1],' ');
    place(optionsX[which-1]+(optionsLeng[which-1]-1)+2,optionsY[which-1],' ');

    which--;
    place(optionsX[which-1]+(optionsLeng[which-1]-1)+1,optionsY[which-1],'<');
    place(optionsX[which-1]+(optionsLeng[which-1]-1)+2,optionsY[which-1],'-');

}

int Option::getWhich(){
    return which;
}

char* Option::getDialog(){
    return dialog;
}

int Option::getXleng(){
    return xleng;
}

int Option::getYleng(){
    return yleng;
}
