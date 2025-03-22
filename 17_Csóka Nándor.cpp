//Cs�ka N�ndor 17. feladat

/*14 k�rd�s, ABCD v�laszok, 1 helyes v�lasz, versenyz�k bet�kb�l �s sz�mokb�l �ll� k�ddal azonos�tva
(max 500 f�, legfeljebb 5 karakteres azonos�t�)
A f�jl els� sor�ban a helyes v�laszok szerepelnek. A f�jl t�bbi sora a versenyz�k k�dj�val kezd�dik,
ezt egy sz�k�z, majd az adott versenyz� �ltal adott v�laszok sorozata k�veti.
Ha a versenyz� egy k�rd�sre nem v�laszolt, akkor annak hely�n X bet� szerepel. P�ld�ul:

BCCCDBBBBCDAAA
AB123 BXCDBBACACADBC
AH97 BCACDBDDBCBBCA
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

//f�jbeolvas�s, adatok t�rol�sa

struct Versenyzo {
    string kod;
    string valaszok;
};

class Teszt {
private:
    int db; //f�jlban l�v� sorok sz�ma
    Versenyzo* tmb; //adatokat t�rolja
    string helyesValaszok;

public:
    Teszt(const string& fnev); //f�jln�v fix
    ~Teszt();
    void versenyzokSzamaKiir() const; //f�ggv�nyek deklar�l�sa, megh�vni a main f�ggv�nyb�l
    void valaszokMegjelenitese(const string& kod) const;
    void helyesMegoldasok(const string& kod) const;
    void feladatStatisztika(int feladatIndex) const;
    void pontszamitas(const string& kimenet) const;
};

int main() { //tv a Teszt seg�dv�ltoz�ja
    Teszt tv("valaszok.txt");

    tv.versenyzokSzamaKiir();

    string kod;
    cout << "3. feladat: Kerem egy versenyzo kodjat (legfeljebb 5 karakteres szam-betu azonosito) : ";
    cin >> kod;
    tv.valaszokMegjelenitese(kod);

    tv.helyesMegoldasok(kod);

    int feladatIndex;
    cout << "5. feladat: Kerem egy feladat sorszamat (1-14.-ig terjedo szam): ";
    cin >> feladatIndex;
    tv.feladatStatisztika(feladatIndex);

    tv.pontszamitas("pontok.txt");

    return 0;
}

Teszt::Teszt(const string& fnev) { //konstruktorban beolvas
    ifstream be(fnev);
    if (be.fail()) {cout << "Hibas file megnyitas"; system("pause"); exit(1);}

    getline(be, helyesValaszok); //helyes v�laszok, els� sor beolvas�sa

    int maxVersenyzokSzama = 500; //legfeljebb 500 f�
    tmb = new Versenyzo[maxVersenyzokSzama];
    db = 0;

    while (be >> tmb[db].kod >> tmb[db].valaszok) { //beolvas a t�mbbe
        db++;
    }
    cout << "1. feladat: Fajl beolvasas es adatok tarolasa sikeres. " << endl;
    be.close();
}

Teszt::~Teszt() { //destruktor
    delete[] tmb;
}

void Teszt::versenyzokSzamaKiir() const { //2. feladat, kiirat�s
    cout << "2. feladat: A versenyen " << db << " versenyzo vett reszt." << endl;
}

void Teszt::valaszokMegjelenitese(const string& kod) const { //3. feladat, bek�r, ki�r (felt�telezz�k, hogy l�tez� �s helyes azonos�t�t adnak meg)
    cout << "3. feladat: A " << kod << " kodu versenyzo valaszai: ";
    for (int i = 0; i < db; ++i) {
        if (tmb[i].kod == kod) {
            cout << tmb[i].valaszok << endl;
            return;
        }
    }
}

void Teszt::helyesMegoldasok(const string& kod) const { //4. feladat, helyes v�lasz ki�r, + ahol helyes
    cout << "4. feladat: Helyes valaszok: " << helyesValaszok << endl;
    cout << kod << " helyes valaszai:  ";

    for (int i = 0; i < db; ++i) {
        if (tmb[i].kod == kod) {
            for (size_t j = 0; j < helyesValaszok.size(); ++j) { //size_t = el�jel n�lk�li eg�sz t�pus
                cout << (tmb[i].valaszok[j] == helyesValaszok[j] ? '+' : ' ');
            }
            cout << endl;
            return;
        }
    }
}

void Teszt::feladatStatisztika(int feladatIndex) const { //5. feladat, sorsz�m/index bek�r�se, h�ny j�, ez h�ny%
    int helyesDb = 0;
    for (int i = 0; i < db; ++i) {
        if (tmb[i].valaszok[feladatIndex - 1] == helyesValaszok[feladatIndex - 1]) {
            ++helyesDb;
        }
    }
    double szazalek = (double)helyesDb / db * 100;
    cout << "5. feladat: " << helyesDb << " versenyzo adott helyes valaszt, ez a versenyzok "
        << fixed << setprecision(2) << szazalek << "%-a." << endl;
}

void Teszt::pontszamitas(const string& kimenet) const { //6. feladat, pontsz�m meghat�roz�s �s kiirat�s a "pontok.txt" f�jlba
    ofstream ki(kimenet);
    if (ki.fail()) { cout << "Hibas file megnyitas"; system("pause"); exit(1); }

    struct Pontszam {
        string kod;
        int pont;
    };

    Pontszam* pontok = new Pontszam[db];
    int pontErtekek[] = { 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 6 }; //1-5. 3 pont, 6-10. 4 pont, 11-13. feladat 5 pont, 14. feladat 6 pont

    for (int i = 0; i < db; ++i) {
        int pontszam = 0;
        for (size_t j = 0; j < helyesValaszok.size(); ++j) { //size_t = el�jel n�lk�li eg�sz t�pus
            if (tmb[i].valaszok[j] == helyesValaszok[j]) {
                pontszam += pontErtekek[j];
            }
        }
        pontok[i] = { tmb[i].kod, pontszam }; //pontsz�mok ki�r�sa �j f�jlba
        ki << tmb[i].kod << " " << pontszam << endl; //k�d-sz�k�z-pontsz�m
    }
    cout << "6. feladat: A pontszamok kiirasa megtortent a pontok.txt fajlba." << endl; //ide�rtam, hogy l�tsz�djon a konzolon
    ki.close();

    sort(pontok, pontok + db, [](const Pontszam& a, const Pontszam& b) { //rendez� algoritmus, hogy a legnagyobb pontsz�m�ak ker�ljenek el�re a t�mbben
        return a.pont > b.pont;
        });

    cout << "7. feladat: A dijazottak:" << endl;

    int maxPontok[3] = { pontok[0].pont, 0, 0 }; //t�rolja az els� 3 legnagyobb pontsz�mot
    int count = 1;
    for (int i = 1; i < db && count < 3; ++i) { //2. elemt�l indul
        if (pontok[i].pont < maxPontok[count - 1]) {
            maxPontok[count] = pontok[i].pont;
            ++count; //�j �rt�k ha beker�l n�velj�k
        }
    }

    for (int i = 0; i < db; ++i) {
        for (int j = 0; j < count; ++j) {
            if (pontok[i].pont == maxPontok[j]) { //versenyz�k pontjainak �sszehas. a 3 legnagyobb pontsz�mmal
                cout << pontok[i].kod << " " << pontok[i].pont << endl;
                break; //egy versenyz� csak egyszer legyen ki�rva
            }
        }
    }

    delete[] pontok; //pontok t�mb felszabad�t�sa
}

