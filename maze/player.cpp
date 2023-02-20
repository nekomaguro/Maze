#include"standard.h"
#include"player.h"

Player::Player(char input) : Object::Object(input){}

/**
 * @brief 指定した方向にプレイヤーを動かす
 * 
 * @param direction 方向
 */
void Player::move(int direction){
    switch(direction){
        case UP:
            y -= 1;
            break;

        case DOWN:
            y += 1;
            break;

        case RIGHT:
            x += 1;
            break;

        case LEFT:
            x -= 1;
            break;
    }
}