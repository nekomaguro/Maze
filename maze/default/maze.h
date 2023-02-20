#ifndef MAZE_H
#define MAZE_H

#include"default.h"

class Maze : public Default
{
    private:
        int length;
        int size;
        int x;
        int y;
        int startX;
        int startY;
        int goalX;
        int goalY;
        int sliceX;
        int sliceY;
        int sliceXLength;
        int sliceYLength;
        int rangeX;
        int rangeY;
        int rangePointX;
        int rangePointY;
        int rangeXleng;
        int rangeYleng;
        char* maze;
        char* event;
        char* sliceMaze;

        void fullFill(char* type,char select);
        void frame(char* type,char select);
        void place(char* type,int x,int y,char select);
        void line(char* type,int x,int y,int direction,int length,char select);
        int scan(char* type,char scan);
        void mazeSet();
        void grid(char* type,char selet);
        void start();
        void snake();
        
    public:
        Maze(int n);
        ~Maze();
        void createMaze();
        void sliceMazeSet(int sx,int sy,int xleng,int yleng);
        void rangeSet(int xleng,int yleng,int px,int py);
        void rangeCodinatSet(int x,int y);
        char* getMaze();
        char* getEvent();
        char* getSliceMaze();
        int getStartX();
        int getStartY();
        int getGoalX();
        int getGoalY();
        int getRangeX();
        int getRangeY();
        int getRangeXleng();
        int getRangeYleng();
        int getSliceXleng();
        int getSliceYleng();
        int getSliceX();
        int getSliceY();
        char search(char* type,int x,int y);
};

#endif