#include"standard.h"
#include"random.h"

Random::Random(){
    t = (unsigned int)time(NULL);
    srand(t);
}

unsigned int Random::getT(){
    return t;
}

int Random::randef(int min,int max){
    return (rand()%(max-min+1))+min;
}