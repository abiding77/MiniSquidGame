#pragma once    // 헤더 파일
#include <iostream>
#include <random>
#include <iomanip>
#include <string>
using namespace std;

class Player {
private:
    string name; // 이름
    int id; // 참가 번호
    static int alive; // 참가인원
    static int prize; // 총 상금
public:
    Player();
    virtual ~Player();
    void setName(string);
    void setId(int);
    string getName() const;
    int getId() const;
    static void incPrize();
    static void decAlive();
    static int getAlive();
    static int getPrize();
    static void setAlive(int);
    static void setPrize(int);
};
