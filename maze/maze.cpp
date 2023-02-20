#include"standard.h"
#include"maze.h"
#include"random.h"

Maze::Maze(int n){
    length = n;
    size = n*n;

    maze = (char*)malloc(sizeof(char)*size);
    if(maze==NULL){
        throw std::runtime_error("malloc error");
    }

    event = (char*)malloc(sizeof(char)*size);
    if(event==NULL){
        throw std::runtime_error("malloc error");
    }

    sliceMaze = (char*)malloc(sizeof(char)*1);
    if(sliceMaze==NULL){
        throw std::runtime_error("malloc error");
    }

    sliceXLength = 1;
    sliceYLength = 1;

    startX = 1; startY = 1;
    rangeX = 1; rangeY = 1;
    rangePointX = 1; rangePointY = 1;
    rangeXleng =1; rangeYleng = 1;
}

Maze::~Maze(){
    free(maze);
    free(event);
}

/**
 * @brief 二次元配列を指定した文字で埋める
 * 
 * @param type 二次元配列のタイプ
 * @param select 指定する文字
 */
void Maze::fullFill(char* type,char select){
    Default::fullFill(type,size,select);
}

/**
 * @brief 二次元配列を指定した文字で囲む
 * 
 * @param type 二次元配列のタイプ
 * @param select 指定する文字
 */
void Maze::frame(char* type,char select){
    Default::frame(type,length,length,select);
}

/**
 * @brief 二次元配列の指定した場所に指定した文字を置く
 * 
 * @param type 二次元配列のタイプ
 * @param x X座標
 * @param y Y座標
 * @param select 指定する文字
 */
void Maze::place(char* type,int x,int y,char select){
    Default::place(type,length,length,x,y,select);
}

/**
 * @brief 二次元配列の指定した場所の文字を取得する
 * 
 * @param type 二次元配列のタイプ
 * @param x X座標
 * @param y Y座標
 * @return char 指定した場所の文字
 */
char Maze::search(char* type,int x,int y){
    return Default::search(type,length,length,x,y);
}

/**
 * @brief 二次元配列の指定した場所から指定した数だけ指定した方向に指定した文字を伸ばす
 * 
 * @param type 二次元配列のタイプ
 * @param x X座標
 * @param y Y座標
 * @param direction 方向 
 * @param length 長さ
 * @param select 指定する文字
 */
void Maze::line(char* type,int x,int y,int direction,int length,char select){
    Default::line(type,length,length,x,y,direction,length,select);
}

/**
 * @brief 二次元配列の指定した文字の数を取得する
 * 
 * @param type 二次元配列のタイプ
 * @param scan 指定する文字
 * @return int 指定した文字の数
 */
int Maze::scan(char* type,char scan){
   return Default::scan(type,size,scan);
}

/**
 * @brief 二次元配列に指定した文字をグリッドにして配置する
 * 
 * @param type 二次元配列のタイプ
 * @param select 指定する文字
 */
void Maze::grid(char* type,char select){
    for(int count=1;count<=length;count+=2){
        Maze::line(type,count,1,DOWN,length,select );
        Maze::line(type,1,count,RIGHT,length,select);
    }
}

/**
 * @brief すでに道が通っているところまで道を伸ばす
 * 
 */
void Maze::snake(){
    int direction = DOWN;
    int dirList[4] ={0,0,0,0};
    int dirListLeng = 0, orderLeng = 0;
    int* orders;

    //ordersにメモリ割り当て
    orders = (int*)malloc(sizeof(int)*(length/2)*(length/2)*2);
    if(orders == NULL){
        throw std::runtime_error("malloc error");
    }

    while(1){

        if(Maze::search(event,x,y) == PASSED){
            break;
        }

        Maze::place(event,x,y,NOPASSED);
        orders[orderLeng*2] = x;
        orders[orderLeng*2+1] = y;
        orderLeng++;
        
        while(1){

            if(y-1 != 1){
                if(Maze::search(event,x,y-2) != NOPASSED){//up
                    dirList[dirListLeng] = UP;
                    dirListLeng++;
                }
            }
            if(y+1 != length){
                if(Maze::search(event,x,y+2) != NOPASSED){//down
                    dirList[dirListLeng] = DOWN;
                    dirListLeng++;
                } 
            }
            if(x+1 != length){
                if(Maze::search(event,x+2,y) != NOPASSED){//right
                    dirList[dirListLeng] = RIGHT;
                    dirListLeng++;
                }
            } 
            if(x-1 != 1){
                if(Maze::search(event,x-2,y) != NOPASSED){//left
                    dirList[dirListLeng] = LEFT;
                    dirListLeng++;
                }
            }

            if(dirListLeng > 0) break;

            if(orderLeng<=0){
                printf("order error\n");
                free(orders);
                return;
            }

            int randNumber = Random::randef(0,orderLeng-1);
            x = orders[randNumber*2];
            y = orders[randNumber*2+1];
        }

        direction = dirList[Random::randef(0,dirListLeng-1)];

        switch(direction){
            case UP:
            Maze::place(maze,x,y-1,' ');
            Maze::place(event,x,y-1,PASSED);
            y -= 2;
            break;

            case DOWN:
            Maze::place(maze,x,y+1,' ');
            Maze::place(event,x,y+1,PASSED);
            y += 2;
            break;

            case RIGHT:
            Maze::place(maze,x+1,y,' ');
            Maze::place(event,x+1,y,PASSED);
            x += 2;
            break;

            case LEFT:
            Maze::place(maze,x-1,y,' ');
            Maze::place(event,x-1,y,PASSED);
            x -= 2;
            break;
            
            default:
            puts("snake error");
        }
        dirListLeng = 0;
    }
    
    for(int count=0;count<orderLeng;count++){
        Maze::place(event,orders[count*2],orders[count*2+1],PASSED);
    }
    free(orders);
}

/**
 * @brief スタートとゴールの位置を決め、PASSEDをランダムな場所に置く
 * 
 */
void  Maze::start(){
    //startの位置を決める
    x = 2*Random::randef(1,(length-3)/2);
    y = 2;

    startX = x;
    startY = y;

    Maze::place(maze,x,1,' ');
    Maze::place(event,x,1,START);

    //goalの位置を決める
    int goal = 2*Random::randef(1,(length-3)/2);

    goalX = goal;
    goalY = length-1;

    Maze::place(maze,goal,length,' ');
    Maze::place(event,goal,length,GOAL);

    //ランダムな場所にPASSEDを置く

    int sx = Random::randef(1,length/2)*2;
    int sy = Random::randef(1,length/2)*2;
    Maze::place(event,sx,sy,PASSED);
}

/**
 * @brief CLOSEDがなくなるまでsnakeを繰り返す
 * 
 */
void Maze::mazeSet(){
    int closed = Maze::scan(event,CLOSED);
    int length, closeCount;

    while(closed>0){
        x = 2;
        y = 2;
        length = Random::randef(1,closed);
        closeCount = 1;

        while(1){
            //指定された番目のCLOSEDを探す

            if(Maze::search(event,x,y)==CLOSED){
                if(closeCount==length) break;
                closeCount++;
            }

            x += 2;
            if(x >= Maze::length){
                y += 2;
                x = 2;
            }
        }
                
        Maze::snake();
        closed = Maze::scan(event,CLOSED);
    }
}

/**
 * @brief 迷路を作成する
 * 
 */
void Maze::createMaze(){
    Maze::fullFill(event,CLOSED);
    Maze::frame(event,BLOCK);
    Maze::grid(event,BLOCK);

    Maze::fullFill(maze,' ');
    Maze::grid(maze,'*');
    Maze::frame(maze,'*');

    Maze::start();
    
    Maze::mazeSet();
}

void Maze::sliceMazeSet(int sx,int sy,int xleng,int yleng){
    if((sx > length)||(sy > length)||(sx < 1)||(sy < 1)){
        throw std::logic_error("slice error");
    }

    if((sx + (xleng - 1) > length) || (sy + (yleng - 1) > length)){
        throw std::logic_error("slice error");
    }

    sliceX = sx;
    sliceY = sy;

    if((xleng != sliceXLength) || (yleng != sliceYLength)){
        sliceXLength = xleng;
        sliceYLength = yleng;

        free(sliceMaze);
        sliceMaze = (char*)malloc(sizeof(char)*xleng*yleng);
        if(sliceMaze == NULL){
            throw std::runtime_error("malloc error");
        }
    }

    int countX;
    int countY;
    for(countY = 0;countY < yleng;countY++){
        for(countX = 0;countX < xleng;countX++){
            *(sliceMaze+xleng*(countY)+countX) = *(maze+length*(countY+(sy-1))+countX+(sx-1));
        }
    }
}

void Maze::rangeSet(int xleng,int yleng,int px,int py){
    if((xleng > length)||(yleng > length)||(xleng < 1)||(yleng < 1)){
        throw std::logic_error("range set error");
    }
    if((px > xleng)||(py > yleng)||(px < 1)||(py < 1)){
        throw std::logic_error("range set error");
    }

    rangeXleng = xleng; rangeYleng = yleng;
    rangePointX = px; rangePointY = py;
}

void Maze::rangeCodinatSet(int x,int y){
    if((x > length)||(y > length)||(x < 1)||(y < 1)){
        throw std::logic_error("range error");
    }

    rangeX = x - (rangePointX - 1);
    rangeY = y - (rangePointY - 1);

    if(rangeX < 1){
        rangeX = 1;
    }
    if(rangeY < 1){
        rangeY = 1;
    }
    if(rangeX + (rangeXleng - 1) > length){
        rangeX = length - (rangeXleng - 1);
    }
    if(rangeY + (rangeYleng - 1) > length){
        rangeY = length - (rangeYleng - 1);
    }
}

/**
 * @brief 迷路を取得する
 * 
 * @return char* 迷路
 */
char* Maze::getMaze(){
    return maze;
}

/**
 * @brief 迷路のイベントを取得する
 * 
 * @return char* イベント
 */
char* Maze::getEvent(){
    return event;
}

char* Maze::getSliceMaze(){
    return sliceMaze;
}

/**
 * @brief スタート地点のX座標を取得する
 * 
 * @return int X座標
 */
int Maze::getStartX(){
    return startX;
}

/**
 * @brief スタート地点のY座標を取得する
 * 
 * @return int Y座標
 */
int Maze::getStartY(){
    return startY;
}

int Maze::getGoalX(){
    return goalX;
}

int Maze::getGoalY(){
    return goalY;
}

int Maze::getRangeX(){
    return rangeX;
}

int Maze::getRangeY(){
    return rangeY;
}

int Maze::getRangeXleng(){
    return rangeXleng;
}

int Maze::getRangeYleng(){
    return rangeYleng;
}

int Maze::getSliceXleng(){
    return sliceXLength;
}

int Maze::getSliceYleng(){
    return sliceYLength;
}

int Maze::getSliceX(){
    return sliceX;
}

int Maze::getSliceY(){
    return sliceY;
}