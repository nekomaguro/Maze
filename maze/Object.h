#ifndef OBJECT_H
#define OBJECT_H

class Object
{
    protected:
        int x;
        int y;
        char charac;
        char* characP;
    public:
        Object(char input);
        virtual void setCodinat(int X,int Y);
        char getCharac();
        char* getCharacP();
        int getX();
        int getY();
};
#endif