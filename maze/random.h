#ifndef RANDOM_H
#define RANDOM_H

class Random
{
    private:
        unsigned int t;
    public:
        Random();
        unsigned int getT();
        static int randef(int min,int max); 
};

#endif