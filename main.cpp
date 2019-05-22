#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct fraza {
    string tresc = "";
    int ilosc = 0;
};

struct wyrazElement {
    string wartosc = "";
    wyrazElement *nastepny = nullptr;
};

struct zdanieElement {
    string tresc = "";
    zdanieElement *next = nullptr;

    bool czyZawieraJakakolwiekFraze = false;
    fraza *frazy = nullptr;
};

struct kolejkaZdan {
    zdanieElement *head = nullptr;
    zdanieElement *tail = nullptr;
};

//Funkcja tworzaca oraz uzupelniajaca strukture 'fraza', wykorzystywana w zadaniu 3

void wypelnijZdanieElStrukturaFrazy(zdanieElement *&zdanieEl) {

    fraza *fraza = new struct fraza[5];
    zdanieEl->frazy = fraza;
    zdanieEl->czyZawieraJakakolwiekFraze = false;

    string wzorce[5] = {"unique offer", "mega discounts", "super promotion", "low prices", "great sale"};
    for (int i = 0; i < 5; i++) {
        fraza[i].tresc = wzorce[i];
        fraza[i].ilosc = 0;
    }
}

//Funkcje stosu

bool czyStosWyrazowPusty(wyrazElement *wyrazy) {
    return wyrazy == nullptr;
}

void dodajWyrazDoStosu(wyrazElement *&stos, string &wartosc) {
    wyrazElement *nowyWyraz = new wyrazElement;

    nowyWyraz->wartosc = wartosc;
    nowyWyraz->nastepny = stos;
    stos = nowyWyraz;
}

string pobierzWyrazZeStosu(wyrazElement *&wyrazy) {
    if (!czyStosWyrazowPusty(wyrazy)) {
        return wyrazy->wartosc;
    }else{
        return "";
    }
}

//Funkcje pomocnicze do tworzenia zdania jako string

bool czyKoniecZdania(char &znak) {
    return znak == '.' || znak == '!' || znak == '?';
}

void utworzZdanieJakoString(wyrazElement *&wyrazy, string &zdanie) {
    while (!czyStosWyrazowPusty(wyrazy)) {
        zdanie += pobierzWyrazZeStosu(wyrazy);
        wyrazy = wyrazy->nastepny;
        if (wyrazy != nullptr) {
            zdanie += " ";
        }
    }
}

void dodajZnakKoncaDoZdania(string &zdanie, char &znakKonca) {
    zdanie += string(1, znakKonca);
}

void wczytajSpacjePoZnakuKonca(ifstream &plik, char &znak) { plik >> znak; }

//Funkcje kolejki

bool czyKolejkaZdanPusta(kolejkaZdan kolejka) {
    return kolejka.head == nullptr;
}

void dodajZdanieDoKolejki(kolejkaZdan &kolejka, string &tresc) {
    zdanieElement *noweZdanie = new zdanieElement;
    noweZdanie->tresc = tresc;
    noweZdanie->next = nullptr;

    if (kolejka.tail != nullptr) {
        kolejka.tail->next = noweZdanie;
    }
    kolejka.tail = noweZdanie;

    if (kolejka.head == nullptr) {
        kolejka.head = noweZdanie;
    }
}

zdanieElement *pobierzZdanie(kolejkaZdan &kolejka) {
    if (kolejka.head != nullptr) {
        return kolejka.head;
    } else {
        return nullptr;
    }
}

void usunZdanieZKolejki(kolejkaZdan &kolejka) {

    if (kolejka.head != nullptr) {
        zdanieElement *temp = kolejka.head;
        kolejka.head = kolejka.head->next;
        delete temp;

        if (kolejka.head == nullptr) {
            kolejka.tail = nullptr;
        }
    }
}

void usunWszystkieZdania(kolejkaZdan &kolejka) {
    while (!czyKolejkaZdanPusta(kolejka)) {
        usunZdanieZKolejki(kolejka);
    }
}

void wyswietlZdania(kolejkaZdan kolejka) {
    zdanieElement *temp = pobierzZdanie(kolejka);
    while (temp != nullptr) {
        cout << temp->tresc << endl;
        temp = temp->next;
    }
}

//Wzorzec tekstu - zadanie 3

void zmienNaMaleLitery(string &zdanieSprawdzane) {
    transform(zdanieSprawdzane.begin(), zdanieSprawdzane.end(), zdanieSprawdzane.begin(), ::tolower);
}

void zbudujTabliceDopasowan(zdanieElement *zdanieEl, int *&tabDopasowan) {
    string zdanieTresc = zdanieEl->tresc;
    zmienNaMaleLitery(zdanieTresc);

    int dlugosc = zdanieTresc.length();
    tabDopasowan[0] = 0;
    tabDopasowan[1] = 0;
    int t = 0;
    for (int i = 1; i < dlugosc; i++) {
        while (t > 0 && zdanieTresc.at(t) != zdanieTresc.at(i)) {
            t = tabDopasowan[t];
        }
        if (zdanieTresc.at(t) == zdanieTresc.at(i)) {
            t++;
        }
        tabDopasowan[i + 1] = t;
    }
}

void znajdzFrazyKMP(zdanieElement *zdanieEl, int *&tabDopasowan) {
    wypelnijZdanieElStrukturaFrazy(zdanieEl);

    fraza *frazy = zdanieEl->frazy;
    string zdanie = zdanieEl->tresc;
    zmienNaMaleLitery(zdanie);
    int dlugoscZdania = zdanie.length();

    for (int iFraza = 0; iFraza < 5; iFraza++) {
        string wzorzec = frazy[iFraza].tresc;
        int dlugoscFrazy = wzorzec.length();
        int i = 0;
        int j = 0;
        while (i < dlugoscZdania - dlugoscFrazy + 1) {
            while (wzorzec.at(j) == zdanie.at(i + j) && j < dlugoscFrazy) {
                j++;
                if (j == dlugoscFrazy) {
                    zdanieEl->czyZawieraJakakolwiekFraze = true;
                    frazy[iFraza].ilosc++;
                    break;
                }
            }
            i = i + max(1, j - tabDopasowan[j]);
            j = tabDopasowan[j + 1];
        }
    }
}

//Główne rozwiązania

void wczytajDane(string nazwaPliku, kolejkaZdan &kolejka) {
    ifstream plik;

    char znak;
    string tempSlowo;
    string zdanieString;

    wyrazElement *wyrazyStos = nullptr;

    plik.open(nazwaPliku);
    while (!plik.eof()) {
        plik >> noskipws >> znak;

        if (czyKoniecZdania(znak)) {
            dodajWyrazDoStosu(wyrazyStos, tempSlowo);
            utworzZdanieJakoString(wyrazyStos, zdanieString);
            dodajZnakKoncaDoZdania(zdanieString, znak);
            dodajZdanieDoKolejki(kolejka, zdanieString);
            wczytajSpacjePoZnakuKonca(plik, znak);
            tempSlowo = "";
            zdanieString = "";
            continue;
        }

        if (znak != ' ' && !plik.eof()) {
            tempSlowo += znak;
        } else if (znak == ' ') {
            dodajWyrazDoStosu(wyrazyStos, tempSlowo);
            tempSlowo = "";
        }
    }

    //Dla ostatniego zdania w pliku
    dodajWyrazDoStosu(wyrazyStos, tempSlowo);
    utworzZdanieJakoString(wyrazyStos, zdanieString);
    dodajZdanieDoKolejki(kolejka, zdanieString);

    plik.close();
}

bool czyMaDaneSlowo(string zdanieSprawdzane, string slowo) {
    zmienNaMaleLitery(zdanieSprawdzane);
    return zdanieSprawdzane.find(slowo) != string::npos;
}

void zadanie1(kolejkaZdan kolejka) {
    wyswietlZdania(kolejka);
}

void zadanie2(kolejkaZdan &kolejka) {

    kolejkaZdan tempKolejkaZZakazanymi;

    while (kolejka.tail != nullptr) {
        string zdanieSprawdzane = pobierzZdanie(kolejka)->tresc;
        bool czyMaZakazane =
                czyMaDaneSlowo(zdanieSprawdzane, "promotion")
                || czyMaDaneSlowo(zdanieSprawdzane, "sale")
                || czyMaDaneSlowo(zdanieSprawdzane, "discount")
                || czyMaDaneSlowo(zdanieSprawdzane, "offer");

        if (czyMaZakazane) {
            dodajZdanieDoKolejki(tempKolejkaZZakazanymi, zdanieSprawdzane);
        }
        usunZdanieZKolejki(kolejka);
    }
    kolejka = tempKolejkaZZakazanymi;
    wyswietlZdania(kolejka);
}

void zadanie3(kolejkaZdan kolejka) {

    int *tabDopasowan;

    while (!czyKolejkaZdanPusta(kolejka)) {
        zdanieElement *zdanie = kolejka.head;

        tabDopasowan = new int[zdanie->tresc.length()];
        zbudujTabliceDopasowan(zdanie, tabDopasowan);
        znajdzFrazyKMP(zdanie, tabDopasowan);

        if (zdanie->czyZawieraJakakolwiekFraze) {
            fraza *frazy = zdanie->frazy;
            cout << pobierzZdanie(kolejka)->tresc << endl;
            for (int i = 0; i < 5; i++) {
                cout << frazy[i].tresc << " " << frazy[i].ilosc << endl;
            }
        }
        kolejka.head = kolejka.head->next;
    }
    delete tabDopasowan;
}

int main() {
    kolejkaZdan zdaniaPodejrzane;

    wczytajDane("dane.txt", zdaniaPodejrzane);

    zadanie1(zdaniaPodejrzane);
    cout << "------------------------------------------------------------" << endl;
    zadanie2(zdaniaPodejrzane);
    cout << "------------------------------------------------------------" << endl;
    zadanie3(zdaniaPodejrzane);

    return 0;
}
