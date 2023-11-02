#include "knight2.h"


//Le Vo Dang Khoa
//2211606
bool isPrime(int n) {
    if (n <= 1)
        return false;
    for (int i = 2; i < n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}
bool isPythagoras(int n) {
    int a = n / 100;
    int b = n % 100 / 10;
    int c = n % 10;
    if (a == 0 || b == 0 || c == 0)
        return false;
    if (a * a == b * b + c * c || b * b == c * c + a * a || c * c == a * a + b * b)
        return true;
    else
        return false;
}

Events::Events(const string& file_events) {
    int n, i = 1;
    ifstream ifs(file_events);
    ifs >> c;
    EventsArray = new int[c];
    while (ifs >> n) {
        EventsArray[i - 1] = n;
        i++;
    }
};
int Events::count() const {
    return this->c;
};
int Events::get(int i) const {
    return this->EventsArray[i];
};
Events::~Events() {
    delete[] EventsArray;
};
/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
class BaseKnight;

Antidote::Antidote() {
    itemType = antidote;
}
PhoenixDownI::PhoenixDownI() {
    itemType = phoenixI;
}
PhoenixDownII::PhoenixDownII() {
    itemType = phoenixII;
}
PhoenixDownIII::PhoenixDownIII() {
    itemType = phoenixIII;
}
PhoenixDownIV::PhoenixDownIV() {
    itemType = phoenixIV;
}
void BaseBag::dropitem() {
    int i = 0;
    while (head != nullptr && i < 3) {
        Node* deletedNode = head;
        head = head->next;
        numCurItem--;
        delete deletedNode;
        i++;
    }
}

void BaseBag::removeItem(BaseItem* item) { //hàm chuyển item lên đầu và xóa
    Node* curr = head, * prev = nullptr;
    if (curr != nullptr && curr->data->itemType == item->itemType) {
        head = curr->next;
        delete curr;
        numCurItem--;
        return;
    }
    while (curr != nullptr) {
        if (curr->data->itemType == item->itemType) {
            prev->next = curr->next;
            curr->next = head;
            numCurItem--;
            head = curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    //xoas
    head = curr->next;
    delete curr;
}

BaseItem* BaseBag::get(ItemType itemType) {
    if (numCurItem == 0 || head == nullptr)
        return nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data != nullptr && curr->data->itemType == itemType)
            return curr->data;
        curr = curr->next;
    }
    return nullptr;
}

DragonBag::DragonBag(int antidote, int phoenixdownI) {
    maxitem = 99999;
    numAntidote = 0;
    numPhoenixDownI = (phoenixdownI > 5 ? 5 : phoenixdownI);
    numCurItem = 0;
}
bool DragonBag::insertFirst(BaseItem* item) {
    if (item->itemType == 0) {
        return 0;
    }
    else
    {
        Node* newNode = new Node;
        newNode->data = item;
        newNode->next = head;
        head = newNode;
        numCurItem++;
        return 1;
    }
};

LancelotBag::LancelotBag(int antidote, int phoenixdownI) {
    maxitem = 16;
    numAntidote = (antidote > 5 ? 5 : antidote);
    numPhoenixDownI = (phoenixdownI > 5 ? 5 : phoenixdownI);
    numCurItem = 0;
}
bool LancelotBag::insertFirst(BaseItem* item) {
    if (numCurItem >= maxitem) {
        return 0;
    }
    else
    {
        Node* newNode = new Node;
        newNode->data = item;
        newNode->next = head;
        head = newNode;
        numCurItem++;
        return 1;
    }
};
PaladinBag::PaladinBag(int antidote, int phoenixdownI) {
    maxitem = 14;
    numAntidote = (antidote > 5 ? 5 : antidote);
    numPhoenixDownI = (phoenixdownI > 5 ? 5 : phoenixdownI);
    numCurItem = 0;
}
bool PaladinBag::insertFirst(BaseItem* item) {
    if (numCurItem >= maxitem) {
        return 0;
    }
    else
    {
        Node* newNode = new Node;
        newNode->data = item;
        newNode->next = head;
        head = newNode;
        numCurItem++;
        return 1;
    }
};
NormalBag::NormalBag(int antidote, int phoenixdownI) {
    maxitem = 19;
    numAntidote = (antidote > 5 ? 5 : antidote);
    numPhoenixDownI = (phoenixdownI > 5 ? 5 : phoenixdownI);
    numCurItem = 0;
}
bool NormalBag::insertFirst(BaseItem* item) {
    if (numCurItem >= maxitem) {
        return 0;
    }
    else
    {
        Node* newNode = new Node;
        newNode->data = item;
        newNode->next = head;
        head = newNode;
        numCurItem++;
        return 1;
    }
};


bool Antidote::canUse(BaseKnight* knight) {
    if (knight->poisoned == true)
        return true;
    return false;
}
void Antidote::use(BaseKnight* knight) {
    knight->poisoned = false;
}
bool PhoenixDownI::canUse(BaseKnight* knight) {
    if (knight->getHP() <= 0)
        return true;
    return false;
}
void PhoenixDownI::use(BaseKnight* knight) {
    knight->setHP(knight->getMaxHP());
}
bool PhoenixDownII::canUse(BaseKnight* knight) {
    if (knight->getHP() < (knight->getMaxHP() / 4) && knight->getMaxHP() >= 4)
        return true;
    return false;
}
void PhoenixDownII::use(BaseKnight* knight) {
    knight->setHP(knight->getMaxHP());
}
bool PhoenixDownIII::canUse(BaseKnight* knight) {
    if (knight->getHP() <= knight->getMaxHP() / 3 && knight->getMaxHP() >= 3)
        return true;
    return false;
}
void PhoenixDownIII::use(BaseKnight* knight) {
    if (knight->getHP() <= 0) {
        knight->setHP(knight->getMaxHP() / 3);
    }
    else
    {
        knight->addHP(knight->getMaxHP() / 4);
    }
}
bool PhoenixDownIV::canUse(BaseKnight* knight) {
    if (knight->getHP() <= knight->getMaxHP() / 2 && knight->getMaxHP() >= 2)
        return true;
    return false;
}
void PhoenixDownIV::use(BaseKnight* knight) {
    if (knight->getHP() <= 0) {
        knight->setHP(knight->getMaxHP() / 2);
    }
    else
        knight->addHP(knight->getMaxHP() / 5);
}
BaseItem* BaseBag::searchForFirstCanUse(BaseKnight* knight) {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data->canUse(knight)) {
            if (curr->data->itemType == 1)
                return new PhoenixDownI();
            else if (curr->data->itemType == 2)
                return new PhoenixDownII();
            else if (curr->data->itemType == 3)
                return new PhoenixDownIII();
            else if (curr->data->itemType == 4)
                return new PhoenixDownIV();
        }
        curr = curr->next;
    }
    return nullptr;
}


PaladinKnight::PaladinKnight(int antidote, int phoenixdownI) {
    BaseDamge = 0.06;
    maxitem = 14;
    this->bag = new PaladinBag(antidote, phoenixdownI);
    this->knightType = PALADIN;
    for (int i = 0; i < phoenixdownI; i++) {
        BaseItem* phoeI = new PhoenixDownI();
        addBag(phoeI);
    }
    for (int i = 0; i < antidote; i++) {
        BaseItem* anti = new Antidote();
        addBag(anti);
    }
}
LancelotKnight::LancelotKnight(int antidote, int phoenixdownI) {
    BaseDamge = 0.05;
    maxitem = 16;
    this->bag = new LancelotBag(antidote, phoenixdownI);
    this->knightType = LANCELOT;
    for (int i = 0; i < phoenixdownI; i++) {
        BaseItem* phoeI = new PhoenixDownI();
        addBag(phoeI);
    }
    for (int i = 0; i < antidote; i++) {
        BaseItem* anti = new Antidote();
        addBag(anti);
    }
}
DragonKnight::DragonKnight(int antidote, int phoenixdownI) {
    BaseDamge = 0.075;
    maxitem = 999999;
    this->bag = new DragonBag(antidote, phoenixdownI);
    this->knightType = DRAGON;
    for (int i = 0; i < phoenixdownI; i++) {
        BaseItem* phoeI = new PhoenixDownI();
        addBag(phoeI);
    }
}
NormalKnight::NormalKnight(int antidote, int phoenixdownI) {
    maxitem = 19;
    this->bag = new NormalBag(antidote, phoenixdownI);
    this->knightType = NORMAL;
    for (int i = 0; i < phoenixdownI; i++) {
        BaseItem* phoeI = new PhoenixDownI();
        addBag(phoeI);
    }
    for (int i = 0; i < antidote; i++) {
        BaseItem* anti = new Antidote();
        addBag(anti);
    }
}

BaseKnight* BaseKnight::create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote) {
    BaseKnight* knight;
    if (maxhp == 888) {
        knight = new LancelotKnight(antidote, phoenixdownI);
    }
    else if (isPrime(maxhp)) {
        knight = new PaladinKnight(antidote, phoenixdownI);
    }
    else if (isPythagoras(maxhp)) {
        knight = new DragonKnight(antidote, phoenixdownI);
    }
    else {
        knight = new NormalKnight(antidote, phoenixdownI);
    }
    knight->id = id;
    knight->hp = maxhp;
    knight->maxhp = maxhp;
    knight->level = level;
    knight->gil = gil;
    return knight;
}

int BaseKnight::dealDamge(BaseKnight* knight) {
    int rs = knight->getHP() * knight->getLevel() * knight->baseDamge();
    return rs;
}


string BaseKnight::toString() const {
    string typeString[4] = { "PALADIN", "LANCELOT", "DRAGON", "NORMAL" };
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id)
        + ",hp:" + to_string(hp)
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
/* * * END implementation of class BaseKnight * * */

string BaseBag::toString() const {
    Node* curr = head;
    bool f = false;
    string potion[5] = { "Antidote","PhoenixI","PhoenixII","PhoenixIII","PhoenixIV" };
    string s = "Bag[count=";
    s += to_string(this->numCurItem) + ";";
    while (curr != nullptr) {
        if (!f) {
            f = true;
        }
        else
            s += ",";
        s += potion[curr->data->itemType];
        curr = curr->next;
    }
    s += "]";
    return s;
}

int BaseOpponent::calLevel0(int t) {
    this->turn = t;
    int kq = (t + this->id) % 10 + 1;
    return kq;
};
int BaseOpponent::remainHP(BaseKnight* knight) {
    int HP = knight->getHP();
    HP = HP - this->basedamge * (calLevel0(turn) - knight->getLevel());
    return HP;
};
MadBear::MadBear() {
    id = 1;
    basedamge = 10;
    gilreceive = 100;
};
Bandit::Bandit() {
    id = 2;
    basedamge = 15;
    gilreceive = 150;
};
LordLupin::LordLupin() {
    id = 3;
    basedamge = 45;
    gilreceive = 450;
};
Elf::Elf() {
    id = 4;
    basedamge = 75;
    gilreceive = 750;
};
Troll::Troll() {
    id = 5;
    basedamge = 95;
    gilreceive = 800;
};
/* * * BEGIN implementation of class ArmyKnights * * */
int ArmyKnights::count() const {
    for (int i = 0; i < this->c; i++) {
        if (knights[i].getHP() <= 0)
            return i;
    }
}; // count knights that still alive
BaseKnight* ArmyKnights::lastKnight() const {
    if (this->count() == 0)
        return nullptr;
    else {
        return &knights[this->count() - 1];
    }
};
ArmyKnights::ArmyKnights(const string& file_armyknights) {// first id = 1
    int maxhp, level, gil, antidote, phoenixdownI;
    ifstream ifs(file_armyknights);
    ifs >> c;
    knights = new BaseKnight[c];
    for (int i = 0; i < c; i++) {
        ifs >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        knights[i] = *BaseKnight::create(i + 1, maxhp, level, phoenixdownI, gil, antidote);
    }
    ifs.close();
}
ArmyKnights::~ArmyKnights() {
    delete[] knights;
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight* lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

bool ArmyKnights::fight(BaseOpponent* opponent) {
    return false;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
};
void KnightAdventure::loadArmyKnights(const string& FileKnights) {
    armyKnights = new ArmyKnights(FileKnights);
}

void KnightAdventure::loadEvents(const string& FileEvents) {
    events = new Events(FileEvents);
}
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

void KnightAdventure::run() {
    int turn = -1;
    for (int i = 0; i < events->count(); i++) {
        turn++;
        if (armyKnights->ArmyKnights::lastKnight() == nullptr) {
            armyKnights->printInfo();
            armyKnights->printResult(0);
            return;
        }
        BaseKnight* lKnight = armyKnights->ArmyKnights::lastKnight();
        if (events->EventsArray[i] <= 5 && events->EventsArray[i] >= 1) {
            BaseOpponent* oppo = nullptr;
            if (events->EventsArray[i] == 1)
                oppo = new MadBear();
            else if (events->EventsArray[i] == 2)
                oppo = new Bandit();
            else if (events->EventsArray[i] == 3)
                oppo = new LordLupin();
            else if (events->EventsArray[i] == 4)
                oppo = new Elf();
            else if (events->EventsArray[i] == 5)
                oppo = new Troll();
            if (lKnight->getLevel() >= oppo->calLevel0(turn) || lKnight->getKnightType() == 1 || lKnight->getKnightType() == 0)
                lKnight->addGil(oppo->gilreceive);
            else if (lKnight->getLevel() < oppo->calLevel0(turn))
                lKnight->setHP(oppo->remainHP(lKnight));
            if (lKnight->getGil() > 999)
                lKnight->setGil(999);
            delete oppo;
        }
        else if (events->EventsArray[i] == 6) {
            BaseOpponent* oppo = new Tornbery();
            if (lKnight->getLevel() < oppo->calLevel0(turn)) {
                if (lKnight->getKnightType() != 2) {
                    BaseItem* anti = new Antidote();
                    lKnight->poisoned = true;
                    if (lKnight->getBag()->get(anti->itemType) != nullptr) {
                        anti->use(lKnight);
                        lKnight->getBag()->removeItem(lKnight->getBag()->get(anti->itemType));
                    }
                    else {
                        lKnight->getBag()->dropitem();
                        lKnight->poisoned = false;
                        lKnight->addHP(-10);
                    }
                    delete anti;
                }
            }
            else if (lKnight->getLevel() >= oppo->calLevel0(turn)) {
                lKnight->addLevel();
            }
            delete oppo;
        }
        else if (events->EventsArray[i] == 7) {
            BaseOpponent* oppo = new QueenOfCards();
            int gil1000 = 0, t = 2;
            if (lKnight->getLevel() < oppo->calLevel0(turn) && lKnight->getKnightType() != 0)
                lKnight->setGil(lKnight->getGil() / 2);
            else if (lKnight->getLevel() >= oppo->calLevel0(turn)) {
                lKnight->setGil(lKnight->getGil() * 2);
                if (lKnight->getGil() >= 1000) {
                    gil1000 = lKnight->getGil() - 999;
                    lKnight->setGil(999);
                }
            }
            while (gil1000 > 0) {
                if (armyKnights->count() - t < 0)
                    break;
                if (armyKnights->knights[armyKnights->count() - t].getGil() + gil1000 > 999) {
                    gil1000 = gil1000 - (999 - armyKnights->knights[armyKnights->count() - t].getGil());
                    armyKnights->knights[armyKnights->count() - t].setGil(999);
                }
                else {
                    armyKnights->knights[armyKnights->count() - t].addGil(gil1000);
                }
                t++;
            }
            delete oppo;
        }
        else if (events->EventsArray[i] == 8 && lKnight->getGil() >= 50 && lKnight->getHP() <= lKnight->getMaxHP() / 3) {
            if (lKnight->getKnightType() == 0)
                lKnight->addHP(lKnight->getMaxHP() / 5);
            else {
                lKnight->addGil(-50);
                lKnight->addHP(lKnight->getMaxHP() / 5);
            }
        }
        else if (events->EventsArray[i] == 9) {
            lKnight->setHP(lKnight->getMaxHP());
        }
        else if (events->EventsArray[i] == 10 && !armyKnights->metOmega) {
            if (lKnight->getKnightType() == 2 || (lKnight->getHP() == lKnight->getMaxHP() && lKnight->getLevel() == 10)) {
                lKnight->setGil(999);
                lKnight->addLevel(10);
                armyKnights->metOmega = true;
            }
            else {
                lKnight->setHP(0);
            }
        }
        else if (events->EventsArray[i] == 11 && !armyKnights->metHades) {
            if ((lKnight->getKnightType() == 0 && lKnight->getLevel() >= 8) || (lKnight->getLevel() == 10)) {
                armyKnights->Shield = true;
                armyKnights->metHades = true;
            }
            else {
                lKnight->setHP(0);
            }
        }
        else if (events->EventsArray[i] == 95 && armyKnights->Shield != true) {
            armyKnights->Shield = true;
        }
        else if (events->EventsArray[i] == 96) {
            armyKnights->Spear = true;
        }
        else if (events->EventsArray[i] == 97) {
            armyKnights->Hair = true;
        }
        else if (events->EventsArray[i] == 98) {
            if (armyKnights->Shield == true && armyKnights->Spear == true && armyKnights->Hair == true)
                armyKnights->Sword = true;
        }
        else if (events->EventsArray[i] == 99) {
            armyKnights->fightingUltimecia = true;
            if (armyKnights->Sword == true) {
                armyKnights->printInfo();
                armyKnights->printResult(1);
                return;
            }
            if (armyKnights->Shield == true && armyKnights->Spear == true &&
                armyKnights->Hair == true) {
                if (lKnight->getKnightType() == 3) {
                    lKnight->setHP(0);
                    i--;
                    continue;
                }
                else {
                    int damge = lKnight->dealDamge(lKnight);
                    armyKnights->UltiHP -= damge;
                    if (armyKnights->UltiHP > 0) {
                        lKnight->setHP(0);
                    }
                    else {
                        armyKnights->printInfo();
                        armyKnights->printResult(1);
                        return;
                    }
                }
            }
            else {
                for (int i = 0; i < armyKnights->count(); i++)
                    lKnight->setHP(0);
                armyKnights->printInfo();
                armyKnights->printResult(0);
                return;
            }
        }
        else if (events->EventsArray[i] == 112) {
            BaseItem* PII = new PhoenixDownII();
            bool canAdd = true;
            int tem = armyKnights->count() - 1;
            while (canAdd) {
                if (!armyKnights->knights[tem].addBag(PII)) {
                    tem--;
                }
                else {
                    canAdd = false;
                }
            }
        }
        else if (events->EventsArray[i] == 113) {
            BaseItem* PIII = new PhoenixDownIII(); bool canAdd = true;
            int tem = armyKnights->count() - 1;
            while (canAdd) {
                if (!armyKnights->knights[tem].addBag(PIII)) {
                    tem--;
                }
                else {
                    canAdd = false;
                }
            }
        }
        else if (events->EventsArray[i] == 114) {
            BaseItem* PIV = new PhoenixDownIV(); bool canAdd = true;
            int tem = armyKnights->count() - 1;
            while (canAdd) {
                if (!armyKnights->knights[tem].addBag(PIV)) {
                    tem--;
                }
                else {
                    canAdd = false;
                }
            }
        }

        if (lKnight->getBag()->searchForFirstCanUse(lKnight) != nullptr && events->EventsArray[i] <= 11
            && !armyKnights->fightingUltimecia) {
            BaseItem* item = lKnight->getBag()->searchForFirstCanUse(lKnight);
            if (lKnight->getBag()->get(item->itemType)->canUse(lKnight)) {
                lKnight->getBag()->get(item->itemType)->use(lKnight);
                lKnight->getBag()->removeItem(item);
            }
            delete item;
        }
        if (lKnight->getLevel() > 10)
            lKnight->addLevel(10);
        if (lKnight->getHP() > lKnight->getMaxHP())
            lKnight->setHP(lKnight->getMaxHP());
        if (lKnight->getHP() <= 0) {
            if (lKnight->getGil() >= 100 && !armyKnights->fightingUltimecia) {
                lKnight->addGil(-100);
                lKnight->setHP(lKnight->getMaxHP() / 2);
            }
            if (armyKnights->count() == 0) {
                armyKnights->printInfo();
                armyKnights->printResult(0);
                return;
            }
            if (armyKnights->fightingUltimecia) {
                i--;
                continue;
            }
        }
        if (armyKnights->count() == 0) {
            armyKnights->printInfo();
            armyKnights->printResult(0);
            return;
        }
        armyKnights->printInfo();
    }
    armyKnights->printResult(1);
};
