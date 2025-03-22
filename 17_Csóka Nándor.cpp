//Csóka Nándor 17. feladat

/*14 kérdés, ABCD válaszok, 1 helyes válasz, versenyzõk betûkbõl és számokból álló kóddal azonosítva
(max 500 fõ, legfeljebb 5 karakteres azonosító)
A fájl elsõ sorában a helyes válaszok szerepelnek. A fájl többi sora a versenyzõk kódjával kezdõdik,
ezt egy szóköz, majd az adott versenyzõ által adott válaszok sorozata követi.
Ha a versenyzõ egy kérdésre nem válaszolt, akkor annak helyén X betû szerepel. Például:

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

//fájbeolvasás, adatok tárolása

struct Versenyzo {
    string kod;
    string valaszok;
};

class Teszt {
private:
    int db; //fájlban lévõ sorok száma
    Versenyzo* tmb; //adatokat tárolja
    string helyesValaszok;

public:
    Teszt(const string& fnev); //fájlnév fix
    ~Teszt();
    void versenyzokSzamaKiir() const; //függvények deklarálása, meghívni a main függvénybõl
    void valaszokMegjelenitese(const string& kod) const;
    void helyesMegoldasok(const string& kod) const;
    void feladatStatisztika(int feladatIndex) const;
    void pontszamitas(const string& kimenet) const;
};

int main() { //tv a Teszt segédváltozója
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

    getline(be, helyesValaszok); //helyes válaszok, elsõ sor beolvasása

    int maxVersenyzokSzama = 500; //legfeljebb 500 fõ
    tmb = new Versenyzo[maxVersenyzokSzama];
    db = 0;

    while (be >> tmb[db].kod >> tmb[db].valaszok) { //beolvas a tömbbe
        db++;
    }
    cout << "1. feladat: Fajl beolvasas es adatok tarolasa sikeres. " << endl;
    be.close();
}

Teszt::~Teszt() { //destruktor
    delete[] tmb;
}

void Teszt::versenyzokSzamaKiir() const { //2. feladat, kiiratás
    cout << "2. feladat: A versenyen " << db << " versenyzo vett reszt." << endl;
}

void Teszt::valaszokMegjelenitese(const string& kod) const { //3. feladat, bekér, kiír (feltételezzük, hogy létezõ és helyes azonosítót adnak meg)
    cout << "3. feladat: A " << kod << " kodu versenyzo valaszai: ";
    for (int i = 0; i < db; ++i) {
        if (tmb[i].kod == kod) {
            cout << tmb[i].valaszok << endl;
            return;
        }
    }
}

void Teszt::helyesMegoldasok(const string& kod) const { //4. feladat, helyes válasz kiír, + ahol helyes
    cout << "4. feladat: Helyes valaszok: " << helyesValaszok << endl;
    cout << kod << " helyes valaszai:  ";

    for (int i = 0; i < db; ++i) {
        if (tmb[i].kod == kod) {
            for (size_t j = 0; j < helyesValaszok.size(); ++j) { //size_t = elõjel nélküli egész típus
                cout << (tmb[i].valaszok[j] == helyesValaszok[j] ? '+' : ' ');
            }
            cout << endl;
            return;
        }
    }
}

void Teszt::feladatStatisztika(int feladatIndex) const { //5. feladat, sorszám/index bekérése, hány jó, ez hány%
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

void Teszt::pontszamitas(const string& kimenet) const { //6. feladat, pontszám meghatározás és kiiratás a "pontok.txt" fájlba
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
        for (size_t j = 0; j < helyesValaszok.size(); ++j) { //size_t = elõjel nélküli egész típus
            if (tmb[i].valaszok[j] == helyesValaszok[j]) {
                pontszam += pontErtekek[j];
            }
        }
        pontok[i] = { tmb[i].kod, pontszam }; //pontszámok kiírása új fájlba
        ki << tmb[i].kod << " " << pontszam << endl; //kód-szóköz-pontszám
    }
    cout << "6. feladat: A pontszamok kiirasa megtortent a pontok.txt fajlba." << endl; //ideírtam, hogy látszódjon a konzolon
    ki.close();

    sort(pontok, pontok + db, [](const Pontszam& a, const Pontszam& b) { //rendezõ algoritmus, hogy a legnagyobb pontszámúak kerüljenek elõre a tömbben
        return a.pont > b.pont;
        });

    cout << "7. feladat: A dijazottak:" << endl;

    int maxPontok[3] = { pontok[0].pont, 0, 0 }; //tárolja az elsõ 3 legnagyobb pontszámot
    int count = 1;
    for (int i = 1; i < db && count < 3; ++i) { //2. elemtõl indul
        if (pontok[i].pont < maxPontok[count - 1]) {
            maxPontok[count] = pontok[i].pont;
            ++count; //új érték ha bekerül növeljük
        }
    }

    for (int i = 0; i < db; ++i) {
        for (int j = 0; j < count; ++j) {
            if (pontok[i].pont == maxPontok[j]) { //versenyzõk pontjainak összehas. a 3 legnagyobb pontszámmal
                cout << pontok[i].kod << " " << pontok[i].pont << endl;
                break; //egy versenyzõ csak egyszer legyen kiírva
            }
        }
    }

    delete[] pontok; //pontok tömb felszabadítása
}

