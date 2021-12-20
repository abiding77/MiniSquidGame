#pragma once    // ��� ����
#include <iostream>
#include <random>
#include <iomanip>
#include <string>
using namespace std;

class Player {
private:
    string name; // �̸�
    int id; // ���� ��ȣ
    static int alive; // �����ο�
    static int prize; // �� ���
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
