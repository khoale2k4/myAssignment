#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

//Le Vo Dang Khoa
//2211606
bool isPrime(int n);
bool isPythagoras(int n);

class Events {
public:
    int c;
    int* EventsArray;
    Events(const string& file_events);
    int count() const;
    int get(int i) const;
    ~Events();
};
class BaseKnight;

enum ItemType {
    antidote = 0,
    phoenixI,
    phoenixII,
    phoenixIII,
    phoenixIV
};
class BaseItem {
public:
    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
    ItemType itemType;
};
class Antidote : public BaseItem {
public:
    Antidote();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownI : public BaseItem {
public:
    PhoenixDownI();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownII : public BaseItem {
public:
    PhoenixDownII();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownIII : public BaseItem {
public:
    PhoenixDownIII();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};
class PhoenixDownIV : public BaseItem {
public:
    PhoenixDownIV();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};

struct Node {
    BaseItem* data;
    Node* next;
};
class BaseBag {
public:
    int maxitem;
    BaseKnight* knight;
    int numPhoenixDownI;
    int numAntidote;
    int numCurItem;
    Node* head;


    BaseBag() {};
    virtual bool insertFirst(BaseItem* item) { return 0; };
    virtual BaseItem* get(ItemType itemType);
    virtual string toString() const;
    BaseItem* searchForFirstCanUse(BaseKnight* knight);
    void removeItem(BaseItem* item);
    void dropitem();
    ~BaseBag() {};
};

class BaseOpponent;

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id, maxhp, level, gil, hp;
    enum KnightType { PALADIN, LANCELOT, DRAGON, NORMAL };
    BaseBag* bag;
    KnightType knightType;
    double BaseDamge;
public:
    int maxitem;
    bool poisoned = false;
    int getHP() { return hp; }
    int getMaxHP() { return maxhp; }
    int getLevel() { return level; }
    KnightType getKnightType() { return knightType; }
    int getGil() { return gil; }
    void addHP(int ahp) {
        hp += ahp;
        if (hp + ahp > maxhp) {
            hp = maxhp;
        }
    }
    void setHP(int shp) { hp = shp; }
    void setGil(int sg) { gil = sg; }
    void addGil(int ag) { gil += ag; }
    void addLevel() {
        if (level < 10)
            level++;
    }
    void addLevel(int ahp) {
        level += ahp;
        if (level > 10)
            level = 10;
    }
    double baseDamge() { return this->BaseDamge; }
    int limitBag() { return maxitem; }
    BaseBag* getBag() { return bag; }
    bool addBag(BaseItem* item) { return bag->insertFirst(item); };
    int dealDamge(BaseKnight* knight);
    string toString() const;
    static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class DragonBag : public BaseBag {
public:
    DragonBag(int antidote, int phoenixdownI);
    bool insertFirst(BaseItem* item);
};
class LancelotBag : public BaseBag {
public:
    LancelotBag(int antidote, int phoenixdownI);
    bool insertFirst(BaseItem* item);
};
class PaladinBag : public BaseBag {
public:
    PaladinBag(int antidote, int phoenixdownI);
    bool insertFirst(BaseItem* item);
};
class NormalBag : public BaseBag {
public:
    NormalBag(int antidote, int phoenixdownI);
    bool insertFirst(BaseItem* item);
};

class PaladinKnight : public BaseKnight {
public:
    PaladinKnight(int antidote, int phoenixdownI);
};
class LancelotKnight : public BaseKnight {
public:
    LancelotKnight(int antidote, int phoenixdownI);
};
class DragonKnight : public BaseKnight {
public:
    DragonKnight(int antidote, int phoenixdownI);
};
class NormalKnight : public BaseKnight {
public:
    NormalKnight(int antidote, int phoenixdownI);
};

class BaseOpponent {
public:
    int hp, id, basedamge, turn, gilreceive;
    int calLevel0(int t);
    int remainHP(BaseKnight* knight);
};

class MadBear : public BaseOpponent {
public:
    MadBear();
};
class Bandit : public BaseOpponent {
public:
    Bandit();
};
class LordLupin : public BaseOpponent {
public:
    LordLupin();
};
class Elf : public BaseOpponent {
public:
    Elf();
};
class Troll : public BaseOpponent {
public:
    Troll();
};
class Tornbery : public BaseOpponent {
public:
    Tornbery() {
        id = 6;
    };
};
class QueenOfCards : public BaseOpponent {
public:
    QueenOfCards() {
        id = 7;
    };
};
class NinaDeRings : public BaseOpponent {
    NinaDeRings() {};
};
class DurianGarden : public BaseOpponent {
    DurianGarden() {};
};
class OmegaWeapon : public BaseOpponent {
    OmegaWeapon() {};
};
class Hades : public BaseOpponent {
    Hades() {};
};

class ArmyKnights {
public:
    BaseKnight* knights;
    int c = 0;
    bool metOmega = false, metHades = false, fightingUltimecia = false;
    bool Shield = false, Spear = false, Hair = false, Sword = false;
    int UltiHP = 5000;
    ArmyKnights(const string& file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent* opponent);
    bool adventure(Events* events);
    int count() const;
    BaseKnight* lastKnight() const;

    bool hasPaladinShield() const { return Shield; };
    bool hasLancelotSpear() const { return Spear; };
    bool hasGuinevereHair() const { return Hair; };
    bool hasExcaliburSword() const { return Sword; };

    void printInfo() const;
    void printResult(bool win) const;
};

class KnightAdventure {
private:
    ArmyKnights* armyKnights;
    Events* events;
public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string&);
    void loadEvents(const string&);
    void run();
};

#endif // __KNIGHT2_H__
