// Cross_Road_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <vector>
#include <conio.h>
using namespace std;

class cPlayer {
private:
    int x, y;
public:
    cPlayer(int width) {
        x = width / 2;
        y = 0;
    }
    int getX() { return x; }
    int getY() { return y; }
    void moveLeft() { x--; }
    void moveRight() { x++; }
    void moveUp() { y--; }
    void moveDown() { y++; }
    void reset() { y = 0; };
};

class cLane {
private:
    int width;
    deque<bool> d;
    bool right;
public:
    cLane(int width_) {
        width = width_;
        for (int i = 0; i < width; i++) {
            d.push_front(true);
        }
        right = rand() % 2;
    }

    void Move() {

        if (right == 1) {
            if (rand() % 10 == 1) {
                d.push_front(true);
            }
            else {
                d.push_front(false);
            }
            d.pop_back();
        }
        else {
            if (rand() % 10 == 1) {
                d.push_back(true);
            }
            else {
                d.push_back(false);
            }
            d.pop_front();
        }
    }

    bool getPos(int i) { return d[i]; }

    void changeDirection() {
        right = !right;
    }
};

class cGame {
private:
    bool quit = false;
    int height;
    int width;
    int score;
    cPlayer* player;
    vector<cLane*> lane;
public:
    cGame(int width_, int height_) {
        width = width_;
        height = height_;
        score = 0;
        for (int i = 0; i < height; i++) {
            lane.push_back(new cLane(width));
        }

        player = new cPlayer(width);
    }

    ~cGame() {
        delete player;
        for (int i = 0; i < lane.size(); i++) {
            cLane* cur = lane.back();
            lane.pop_back();
            delete cur;
        }
    }

    void Draw() {
        system("cls");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (lane[i]->getPos(j) && i != 0 && i != height - 1)
                    cout << "#";
                else if (player->getX() == j && player->getY() == i)
                    cout << "V";
                else
                    cout << " ";
            }
            cout << endl;
        }
        if (player->getY() == height - 1) {
            score++;
            player->reset();
            lane[rand() % height]->changeDirection();
            cout << "\x07";
        }
        cout << "Score: " << score << endl;
    }
    void Input() {
        if (_kbhit()) {
            switch (_getch())
            {
            case 'a':
                player->moveLeft();
                break;
            case 'd':
                player->moveRight();
                break;
            case 'w':
                player->moveUp();
                break;
            case 's':
                player->moveDown();
                break;
            case 'x':
                quit = true;
                break;
            }
        }
        else return;
    }
    void Logic() {
        for (int i = 1; i < height - 1; i++) {
            if (rand()%10 <= 3) {
                lane[i]->Move();
            }
            if (lane[i]->getPos(player->getX()) && player->getY() == i)
                quit = true;
        }
    }
    void Run() {
        while (!quit) {
            Input();
            Draw();
            Logic();
        }
    }
};

int main()
{
    srand(time(0));
    cGame Game(20, 5);
    Game.Run();
    cout << "Game Over!" << endl;
}
