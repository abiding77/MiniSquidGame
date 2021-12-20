#include "squidgame.h"

int main()
{
    // �޸��� Ʈ����Ʈ ����� ���� ���� ����
    // ->���Ժ����� ������
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 54);

    const int TOTAL_PLAYER = 55;
    int ns[TOTAL_PLAYER] = { 0, };
    Player* players = new Player[TOTAL_PLAYER];
    int line = 0;

    string students[TOTAL_PLAYER] = { "������", "��ȣ��", "�㼺��", "���ؼ�", "������", "���ַ�", "�ƴ���", "������", "������", "�̻���",
                         "������", "�ӱ�ȫ", "���¿�", "�̺���", "������", "���Ͽ�", "������", "�̵μ�", "�����", "������",
                         "������", "������", "������", "������", "�ڼ���", "ȫ����", "����", "������", "������", "�쿵��",
                         "�赿��", "����", "����", "�輭��", "�����", "������", "������", "���̰�", "����", "������",
                         "�赿��", "��̼�", "Ȳ����", "���Ѽ�", "������", "�տ���", "������", "����", "�̼���", "�縻��",
                         "������", "ȫ�浿", "��뼮", "�ڿ���", "������"
    };

    for (int k = 0; k < TOTAL_PLAYER; k++)
        ns[k] = k + 1;

    // print
    auto printPlayer = [&](int k)->void {
        if (line++ % 5 == 0)
            cout << "\n";
        cout << setw(2) << players[k].getId() << "��: " << setw(6) << players[k].getName() << " | ";
    };

    // prime
    auto isPrime = [](int n)->int {
        if (n == 1)
            return 0;

        for (int k = 2; k < n; k++) {
            if (n % k == 0) {
                return 0;
            }
        }
        return 1;
    };

    // display
    auto disp = []() {cout << "\n\n=============================== �����ο� : " << Player::getAlive() << "�� =============================== \n=============================== ��  ��� \\ " << Player::getPrize() << "�� =============================== \n"; };

    // shuffle
    [=](int* arr)->void {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, 54);

        int temp, rn;
        for (int i = 0; i < TOTAL_PLAYER; i++) {
            rn = dis(gen);
            temp = arr[i];
            arr[i] = arr[rn];
            arr[rn] = temp;
        }
    }(ns);

    cout << "\n\n================================= Game Start ================================= \n";
    for (int k = 0; k < TOTAL_PLAYER; k++) {
        players[k].setId(ns[k]);
        players[k].setName(students[k]);
        printPlayer(k);
    }

    disp();
    int dice = dis(gen) % 6 + 1;
    if (dice == 1)
        dice = dice + 6;
    cout << "I. �ֻ���(2 ~ 7) ���� :  " << dice << "\n";

    for (int k = 0; k < TOTAL_PLAYER; k++) {
        if (players[k].getId() % dice == 0) {
            //players[k].name = to_string(players[k].id) + "Ż��";
            players[k].setName("  Ż��");
            Player::decAlive();
            Player::incPrize();
        }
    }

    for (int k = 0; k < TOTAL_PLAYER; k++) {
        printPlayer(k);
    }

    disp();
    string select;
    cout << "II. ������ ���� : �Ҽ� or �ռ���\n";
    while (1) {
        cout << "\n���� �� �����ϼ���\n1) �Ҽ� 2) �ռ��� : ";
        cin >> select;
        if (select == "1") {
            for (int k = 0; k < TOTAL_PLAYER; k++) {
                if (players[k].getId() % dice != 0) {
                    if (isPrime(players[k].getId())) {
                        players[k].setName("  Ż��");
                        Player::decAlive();
                        Player::incPrize();
                    }
                }
            }
            break;
        }
        else if (select == "2")
        {
            for (int k = 0; k < TOTAL_PLAYER; k++) {
                if (players[k].getId() % dice != 0) {
                    if (!isPrime(players[k].getId())) {
                        if (players[k].getId() == 1)
                            continue;
                        players[k].setName("  Ż��");
                        Player::decAlive();
                        Player::incPrize();
                    }
                }
            }
            break;
        }
        else {
            cout << "�޴����� ������\n";
        }
    }

    for (int k = 0; k < TOTAL_PLAYER; k++) {
        printPlayer(k);
    }

    disp();
    cout << "III. ����̱� ���� : �� �Ѹ�\n";
    int final_winner;
    for (int k = 0; k < TOTAL_PLAYER; k++) {
        final_winner = dis(gen);
        if (players[final_winner].getName() != "  Ż��")
            break;
    }
    for (int k = 0; k < TOTAL_PLAYER; k++) {
        if (players[k].getName() != players[final_winner].getName()) {
            players[k].getName() = "  Ż��";
        }
    }
    for (int k = 0; k < TOTAL_PLAYER; k++) {
        printPlayer(k);
    }
    cout << "\n\n��������� : " << players[final_winner].getId() << "�� " << players[final_winner].getName() << "\n";
    Player::setPrize(55);
    Player::setAlive(1);
    disp();

    delete[] players;
    players = nullptr;

    return 0;
}