#include "squidgame.h"  // 구현 파일

Player::Player() {  // 기본 생성자
    name = "";
    id = 0;
}
Player::~Player() {

}
void Player::setName(string name) {
    this->name = name;
}
void Player::setId(int id) {
    this->id = id;
}
string Player::getName() const {
    return name;
}
int Player::getId() const {
    return id;
}

void Player::incPrize() {
    prize++;
}
void Player::decAlive() {
    alive--;
}

int Player::getAlive() {
    return alive;
}
int Player::getPrize() {
    return prize;
}

void Player::setAlive(int a) {
    alive = a;
}
void Player::setPrize(int p) {
    prize = p;
}
int Player::alive = 55;
int Player::prize = 0;