#include "squidgame.h"

int main()
{
    // 메르센 트위스트 기법을 통해 난수 형성
    // ->정규분포를 만족함
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 54);

    const int TOTAL_PLAYER = 55;
    int ns[TOTAL_PLAYER] = { 0, };
    Player* players = new Player[TOTAL_PLAYER];
    int line = 0;

    string students[TOTAL_PLAYER] = { "이정재", "정호연", "허성태", "박해수", "오영수", "김주령", "아누팜", "이유미", "유성주", "이상희",
                         "윤돈선", "임기홍", "김태영", "이병헌", "문병주", "김하영", "윤영균", "이두석", "원춘규", "김윤태",
                         "이지하", "박정언", "장현진", "정우혁", "박선아", "홍우진", "김윤", "문정대", "나조은", "우영택",
                         "김동현", "김희서", "현진", "김서현", "김원중", "박지훈", "민태율", "정미경", "라가힛", "곽자형",
                         "김동원", "양미선", "황연희", "이한솔", "박종범", "손원경", "윤승훈", "고병택", "이세훈", "양말복",
                         "정지원", "홍길동", "김용석", "박연우", "김정제"
    };

    for (int k = 0; k < TOTAL_PLAYER; k++)
        ns[k] = k + 1;

    // print
    auto printPlayer = [&](int k)->void {
        if (line++ % 5 == 0)
            cout << "\n";
        cout << setw(2) << players[k].getId() << "번: " << setw(6) << players[k].getName() << " | ";
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
    auto disp = []() {cout << "\n\n=============================== 참가인원 : " << Player::getAlive() << "명 =============================== \n=============================== 총  상금 \\ " << Player::getPrize() << "억 =============================== \n"; };

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
    cout << "I. 주사위(2 ~ 7) 게임 :  " << dice << "\n";

    for (int k = 0; k < TOTAL_PLAYER; k++) {
        if (players[k].getId() % dice == 0) {
            //players[k].name = to_string(players[k].id) + "탈락";
            players[k].setName("  탈락");
            Player::decAlive();
            Player::incPrize();
        }
    }

    for (int k = 0; k < TOTAL_PLAYER; k++) {
        printPlayer(k);
    }

    disp();
    string select;
    cout << "II. 프라임 게임 : 소수 or 합성수\n";
    while (1) {
        cout << "\n다음 중 선택하세요\n1) 소수 2) 합성수 : ";
        cin >> select;
        if (select == "1") {
            for (int k = 0; k < TOTAL_PLAYER; k++) {
                if (players[k].getId() % dice != 0) {
                    if (isPrime(players[k].getId())) {
                        players[k].setName("  탈락");
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
                        players[k].setName("  탈락");
                        Player::decAlive();
                        Player::incPrize();
                    }
                }
            }
            break;
        }
        else {
            cout << "메뉴에서 고르세요\n";
        }
    }

    for (int k = 0; k < TOTAL_PLAYER; k++) {
        printPlayer(k);
    }

    disp();
    cout << "III. 제비뽑기 게임 : 단 한명\n";
    int final_winner;
    for (int k = 0; k < TOTAL_PLAYER; k++) {
        final_winner = dis(gen);
        if (players[final_winner].getName() != "  탈락")
            break;
    }
    for (int k = 0; k < TOTAL_PLAYER; k++) {
        if (players[k].getName() != players[final_winner].getName()) {
            players[k].getName() = "  탈락";
        }
    }
    for (int k = 0; k < TOTAL_PLAYER; k++) {
        printPlayer(k);
    }
    cout << "\n\n최종우승자 : " << players[final_winner].getId() << "번 " << players[final_winner].getName() << "\n";
    Player::setPrize(55);
    Player::setAlive(1);
    disp();

    delete[] players;
    players = nullptr;

    return 0;
}