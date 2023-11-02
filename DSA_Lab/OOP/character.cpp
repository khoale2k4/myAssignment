#include <iostream>

using namespace std;

class Character {
protected:
    int hp;
    int x;
    int y;
public:
    Character() {
        hp = x = y = 0;
    }

    Character(int hp, int x, int y) {
        this->hp = hp;
        this->x = x;
        this->y = y;
    }

    int getHp() {
        return hp;
    }

    void setHp(int hp) {
        this->hp = hp;
    }

    int getX() {
        return x;
    }

    void setX(int x) {
        this->x = x;
    }

    int getY() {
        return y;
    }

    void setY(int y) {
        this->y = y;
    }

    int getManhattanDistTo(Character* other) {
        int dx = (this->x - other->getX());
        int dy = (this->y - other->getY());
        dx = (dx < 0 ? -dx : dx);
        dy = (dy < 0 ? -dy : dy);
        return dx + dy;
    }

    void operator=(const Character& other) {
        this->hp = other.hp;
        this->x = other.x;
        this->y = other.y;
    }

    bool operator<(const Character& other) {
        return (this->hp <= other.hp);
    }

    void operator()() {
        cout << this->hp << "-" << this->x << "-" << this->y;
    }
};

class Player : private Character {
public:
    Player() {}

    Player(int hp, int x, int y) : Character(hp, x, y) {}

    void printPlayerData() {
        cout << hp << "-" << getX() << "-" << getY() << endl;
    }

    void moveTo(int x, int y) {
        setX(x);
        setY(y);
    }
};

int main()
{
}
