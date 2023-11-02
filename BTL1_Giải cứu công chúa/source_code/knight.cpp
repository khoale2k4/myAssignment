#include "knight.h"

// Le Vo Dang Khoa 2211606
void maxmin(int arr[], int& x, int& y) {
    x = arr[0];
    y = arr[0];
    for (int i = 0; i < 3; i++) {
        if (arr[i] > x)
            x = arr[i];
        if (arr[i] < y)
            y = arr[i];
    }
}
int mu(int x, int y) {
    int pro = 1;
    for (int i = 0; i < y; i++) {
        pro *= x;
    }
    return pro;
}
void takefile(string filein, string& mush, string& acle, string& merl) {
    int counti = 0, k = 0, meri = 0;
    for (int i = 0; i < filein.length(); i++) {
        if (filein[i] == ',') {
            if (k == 0) mush += filein.substr(i - counti, counti);
            else if (k == 1) {
                acle += filein.substr(i - counti, counti);
                meri = i + 1;
            }
            counti = 0;
            k++;
        }
        else if (i == filein.length() - 1) {
            merl += filein.substr(meri, filein.length() - meri);
        }
        else {
            counti++;
        }
    }
}
int lm(string event) {
    istringstream se(event);
    int num, i = 0;
    while (se >> num) {
        i++;
    }
    return i;
}
void Mu1(string fi, int& HP) {
    ifstream ifs(fi);
    string str, n;
    getline(ifs, str);
    int i = 0;
    bool f=true;
    int maxi, mini, vtma = 0, vtmi = 0;
    while (getline(ifs, n, ',')) {
        int num = stoi(n);
        if(f){
            maxi=num;
            mini=num;
            f=false;
        }
        if (num >= maxi) {
            maxi = num;
            vtma = i;
        }
        if (num <= mini) {
            mini = num;
            vtmi = i;
        }
        i++;
    }
    HP = HP - (vtma + vtmi);
}
void Mu2(string fi, int& HP) {
    ifstream ifs(fi);
    string str, num;
    getline(ifs, str);
    bool giam = false, tang = true;
    int mtx = -2, mti = -3, temp=-10000, i = 0;
    while (getline(ifs, num, ',')) {
        int n = stoi(num);
        if (tang) {
            if (n > temp && !giam) {
                temp = n;
                mtx = n;
                mti = i;
            }
            else if(temp==n){
                mtx = -2;
                mti = -3;
                break;
            }
            else {
                giam = true;
                tang = false;
            }
        }
        if (giam) {
            if (n < temp && !tang) {
                temp = n;
            }
            else {
                mtx = -2;
                mti = -3;
                break;
            }
        }
        i++;
    }
    if(i==1){
        mtx = temp;
        mti = 0;
    }
    HP = HP - (mtx + mti);
}
void Mu3(string fi, int& HP) {
    ifstream ifs(fi);
    string str;
    string num;
    getline(ifs, str);
    int maxi = -1000, mini = 1000, i = 0, vtmax = 0, vtmin = 0;
    while (getline(ifs, num, ',')) {
        int n = stoi(num);
        if (n < 0) {
            n = -n;
        }
        n = (17 * n + 9) % 257;
        if (n > maxi) {
            vtmax = i;
            maxi = n;
        }
        if (n < mini) {
            vtmin = i;
            mini = n;
        }
        i++;
    }
    HP = HP - (vtmax + vtmin);
}
void Mu4(string fi, int& HP) {
    ifstream ifs(fi);
    string str, num;
    ifs >> str;
    getline(ifs, str);
    int arr[3], a = 0, max2_3i = 0, max2_3x = -1000;
    bool found = false;
    while (getline(ifs, num, ',')) {
        int n = stoi(num);
        if (n < 0) {
            n = -n;
        }
        n = (17 * n + 9) % 257;
        arr[a] = n;
        a++;
        if (a == 3) {
            break;
        }
    }
    if(a==1){
        max2_3i = -7;
        max2_3x = -5;
        HP = HP - (max2_3i + max2_3x);
        return;
    }
    if(a==2){
        if(arr[0]<arr[1]){
            max2_3i = 0;
            max2_3x = arr[0];
            HP = HP - (max2_3i + max2_3x);
            return;
        }
        else if(arr[1]<arr[0]){
            max2_3i = 1;
            max2_3x = arr[1];
            HP = HP - (max2_3i + max2_3x);
            return;
        }
        else{
            max2_3i = -7;
            max2_3x = -5;
            HP = HP - (max2_3i + max2_3x);
            return;
        }
    }
    int max3, min3;
    maxmin(arr, max3, min3);
    if (max3 == min3) {
        max2_3i = -7;
        max2_3x = -5;
    }
    else {
        for (int i = 0; i < 3; i++) {
            if (arr[i]<max3 && arr[i]>min3) {
                max2_3i = i;
                max2_3x = arr[i];
                found = true;
            }
        }
        if (!found) {
            for (int i = 0; i < 3; i++) {
                if (arr[i] < max3) {
                    max2_3i = i;
                    max2_3x = arr[i];
                }
            }
        }
    }
    HP = HP - (max2_3i + max2_3x);
}
int fibo(int n) {
    if (n == 1 || n == 2)
        return 1;
    else
        return fibo(n - 1) + fibo(n - 2);
}
int lenint(int n) {
    for (int i = 1; 1; i++) {
        n /= 10;
        if (n == 0)
            return i;
    }
}
bool chNT(int n) {
    if (n < 2)
        return false;
    for (int i = 2; i < n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}
void Asclepius(string f_i, int& re, int& mai, int& pho) {
    int n1, n2, n;
    ifstream file(f_i);
    string l1, l2, ln;
    getline(file, l1); istringstream s1(l1); s1 >> n1;
    getline(file, l2); istringstream s2(l2); s2 >> n2;
    for (int i = 0; i < n1; i++) {
        int sothuoc = 0;
        getline(file, ln);
        istringstream ss(ln);
        while (ss >> n) {
            if (n == 16) {
                re += 1;
                sothuoc++;
            }
            else if (n == 17) {
                mai += 1;
                sothuoc++;
            }
            else if (n == 18) {
                pho += 1;
                sothuoc++;
            }
            if (sothuoc == 3)
                break;
        }
    }
}
int sumP(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + 99 - 2 * i;
    }
    return sum;
}
float baseDamge(int stage) {
    if (stage == 1)
        return 1.0;
    if (stage == 2)
        return 1.5;
    if (stage == 3)
        return 4.5;
    if (stage == 4)
        return 7.5;
    if (stage == 5)
        return 9.5;
}
void countDamge15(int& level, int lvl0, int stage, int& HP, bool lan, bool king) {
    if (level > lvl0 || lan || king) {
        if (level < 10)
            level++;
    }
    else if (level == lvl0) {}
    else {
        float dmg = baseDamge(stage) * lvl0 * 10;
        HP = HP - dmg;
    }
}
void Melin(string f_i, int& HP) {
    ifstream file(f_i);
    string l1, ln;
    int n1;
    getline(file, l1); istringstream s1(l1); s1 >> n1;
    for (int i = 0; i < n1; i++) {
        getline(file, ln);
        string LN=ln;
        for (int i = 0; i < ln.length(); i++) {
            LN[i] = toupper(ln[i]);
        }
        if (ln.find("Merlin")!=string::npos || ln.find("merlin")!=string::npos){
            HP += 3;
        }
        else if (LN.find("M")!=string::npos && LN.find("E")!=string::npos && LN.find("R")!=string::npos
                 && LN.find("L")!=string::npos && LN.find("I")!=string::npos && LN.find("N")!=string::npos){
            HP += 2;
        }
        else {}
    }
}
void running(int turn, int stage, int& HP, int maxHP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, bool& tiny,
    int& tet, int& culvl, int& tef, bool& frog, bool& asc, bool lan, bool& mer, string filein, bool isking, int& rescue) {
    if (stage <= 5 && stage >= 1) {
        int b = turn % 10;
        int lvl0 = (turn > 6 ? (b > 5 ? b : 5) : b);
        countDamge15(level, lvl0, stage, HP, lan, isking);
    }
    else if (stage == 6 && !tiny && !frog) {
        int b = turn % 10;
        int lvl0 = (turn > 6 ? (b > 5 ? b : 5) : b);
        if (level > lvl0 || lan || isking) {
            if (level < 10)
                if (level == 9)
                    level++;
                else
                    level += 2;
        }
        else if (level == lvl0);
        else {
            if (remedy >= 1) {
                remedy--;
            }
            else {
                if (HP <= 5)
                    HP = 1;
                else
                    HP = HP / 5;
                tiny = true;
                tet = turn + 3;

            }
        }
    }
    else if (stage == 7 && !frog && !tiny) {
        float b = turn % 10;
        float lvl0 = (turn > 6 ? (b > 5 ? b : 5) : b);
        if (level > lvl0 || lan || isking) {
            if (level < 10)
                if (level == 9)
                    level++;
                else
                    level += 2;
        }
        else if (level == lvl0);
        else {
            culvl = level;
            if (maidenkiss >= 1) {
                maidenkiss--;
                frog = false;
            }
            else {
                frog = true;
                tef = turn + 3;
                level = 1;
            }
        }
    }
    else if (stage == 11) {
        int n1 = (((level + phoenixdown) % 5 + 1) * 3);
        int HP2 = HP + (sumP(n1) % 100);
        if (HP2 > maxHP)
            HP = maxHP;
        else {
            HP = HP2;
            for (int i = 2; 1; i++) {
                if (i > maxHP) {
                    HP = maxHP;
                    break;
                }
                else if (chNT(i) && i > HP2) {
                    HP = i;
                    break;
                }
            }
        }
    }
    else if (stage == 12) {
        if (HP > 1) {
            for (int i = 1; 1; i++) {
                if (fibo(i + 1) >= HP) {
                    HP = fibo(i);
                    break;
                }
            }
        }
    }
    else if (stage == 15) {
        remedy++;
    }
    else if (stage == 16) {
        maidenkiss++;
    }
    else if (stage == 17) {
        phoenixdown++;
    }
    else if (stage == 19 && !asc) {
        asc = true;
        string fi = "", tem1, tem2;
        takefile(filein, tem1, fi, tem2);
        int red = 0, maid = 0, phoe = 0;
        Asclepius(fi, red, maid, phoe);
        if (red)
            remedy += red;
        if (maid)
            maidenkiss += maid;
        if (phoe)
            phoenixdown += phoe;
    }
    else if (stage == 99) {
        if (lan && level >= 8) {
            level = 10;
        }
        else if (level >= 10) {}
        else if (isking) { level = 10; }
        else
            rescue = 0;
    }
    else if (stage == 18 && !mer) {
        mer = true;
        string fi = "", temp1, temp2;
        takefile(filein, temp1, temp2, fi);
        Melin(fi, HP);
    }
    else if ((stage / mu(10, lenint(stage) - 2)) == 13) {    // Mushroom
        int lvl;
        string fi = "", temp1, temp2;
        takefile(filein, fi, temp1, temp2);
        for (int i = lenint(stage) - 3; i >= 0; i--) {
            lvl = (stage / mu(10, i)) % 10;
            if (lvl == 1) {
                Mu1(fi, HP);
            }
            else if (lvl == 2) {
                Mu2(fi, HP);
            }
            else if (lvl == 3) {
                Mu3(fi, HP);
            }
            else if (lvl == 4) {
                Mu4(fi, HP);
            }
            if (HP <= 0) {
                if (phoenixdown >= 1 && tiny && frog) {
                    frog = false;
                    tiny = false;
                    HP = maxHP;
                    phoenixdown--;
                }
                else if (phoenixdown >= 1 && tiny) {
                    tiny = false;
                    HP = maxHP;
                    phoenixdown--;
                }
                else if (phoenixdown >= 1 && frog) {
                    frog = false;
                    HP = maxHP;
                    phoenixdown--;
                }
                else if (phoenixdown >= 1) {
                    HP = maxHP;
                    phoenixdown--;
                }
                else {
                    rescue = 0;
                    break;
                }
            }
            if(HP>maxHP)
                HP=maxHP;
        }
    }
}

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}
void adventureToKoopa(string file_input, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue) {
    ifstream file(file_input);
    string line;
    getline(file, line);
    istringstream ss(line);
    int num;
    ss >> num; HP = num;
    ss >> num; level = num;
    ss >> num; remedy = num;
    ss >> num; maidenkiss = num;
    ss >> num; phoenixdown = num;

    int maxHP = HP, kinglvl = level;
    bool tiny = false, frog = false, asc = false, Lancelot = false, merlin = false, isking = false;

    string event;
    getline(file, event); istringstream se(event);

    string speceve;
    getline(file, speceve);

    int t = 1;
    int tet = 0, curlvl = 1, tef = 0;
    int lam = lm(event);
    if (chNT(HP))
        Lancelot = true;
    if (HP == 999)
        isking = true;
    while (se >> num) {
        rescue = -1;
        if (num == 0) {
            rescue = 1;
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            break;
        }
        running(t, num, HP, maxHP, level, remedy, maidenkiss, phoenixdown, tiny, tet, curlvl, tef, frog, asc,
            Lancelot, merlin, speceve, isking, rescue);
        if (HP > maxHP) {
            HP = maxHP;
        }
        if (maidenkiss >= 1 && frog) {
            maidenkiss--;
            frog = false;
            level = curlvl;
        }
        if (remedy >= 1 && tiny) {
            tiny = false;
            remedy--;
            if (5 * HP >= maxHP)
                HP = maxHP;
            else
                HP = HP * 5;
        }
        if (remedy > 99)
            remedy = 99;
        if (maidenkiss > 99)
            maidenkiss = 99;
        if (phoenixdown > 99)
            phoenixdown = 99;
        if (rescue == 0) {
            break;
        }
        if (HP <= 0) {
            if (phoenixdown >= 1 && tiny && frog) {
                frog = false;
                tiny = false;
                HP = maxHP;
                phoenixdown--;
            }
            else if (phoenixdown >= 1 && tiny) {
                tiny = false;
                HP = maxHP;
                phoenixdown--;
            }
            else if (phoenixdown >= 1 && frog) {
                frog = false;
                HP = maxHP;
                phoenixdown--;
            }
            else if (phoenixdown >= 1) {
                HP = maxHP;
                phoenixdown--;
            }
            else {
                rescue = 0;
                break;
            }
        }
        if (t == tet && tiny) {
            tiny = false;
            if (5 * HP >= maxHP)
                HP = maxHP;
            else
                HP = HP * 5;
        }
        if (t == tef && frog) {
            frog = false;
            level = curlvl;
        }
        if (HP > 0) {
            if (t == lam) {
                rescue = 1;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            }
            else
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        t++;
    }
    if (rescue != 1)
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
}
