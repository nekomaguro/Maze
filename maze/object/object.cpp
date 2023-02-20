#include"../standard.h"
#include"Object.h"

Object::Object(char input){
    charac = input;
    x = 1;
    y = 1;
    characP = &charac;
}

/**
 * @brief 座標を指定する
 * 
 * @param X X座標
 * @param Y Y座標
 */
void Object::setCodinat(int X,int Y){
    x = X;
    y = Y;
}

/**
 * @brief 文字を取得する
 * 
 * @return char 文字
 */
char Object::getCharac(){
    return charac;
}

/**
 * @brief 文字のポインタを取得する
 * 
 * @return char* 文字のポインタ
 */
char* Object::getCharacP(){
    return characP;
}

/**
 * @brief X座標を指定する
 * 
 * @return int X座標
 */
int Object::getX(){
    return x;
}

/**
 * @brief Y座標を指定する
 * 
 * @return int Y座標
 */
int Object::getY(){
    return y;
}