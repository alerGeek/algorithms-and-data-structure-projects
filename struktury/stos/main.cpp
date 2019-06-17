#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct element {
    int liczba = 0;
    element *next = nullptr;
};

bool czyPusty(element *stos) {
    bool wynik = stos == nullptr ? true : false;
    return wynik;
}

void dodajElement(element *&stos, int wartosc) {
    element *el = new element;
    el->liczba = wartosc;
    el->next = stos;
    stos = el;

}

void usunElement(element *&stos) {
    if (stos != nullptr) {
        element *temp = stos;
        stos = stos->next;
        delete temp;
    } else {
        cout << "Stos jesy juz pusty" << endl;
    }
}

int pobierzElement(element *stos) {
    if (stos != nullptr) {
        return stos->liczba;
    } else {
        cout << "Stos jest pusty" << endl;
    };
}

void usunWszystkieElementy(element *&stos) {
    while (!czyPusty(stos)) {
        usunElement(stos);
    }
}

int losuj_wartosc() {
    int wartosc;
    wartosc = rand() % 100 + 0;
    return wartosc;
}

int main() {
    string komunikat;
    int wylosowana;

    srand(time(nullptr));


    cout << "Menu:" << "\n"
         << "1 - sprawdzenie czy stos jest pusty" << "\n"
         << "2 - dodanie elementu na stos" << "\n"
         << "3 - usuniecie elementu ze stosu" << "\n"
         << "4 - pobranie elementu ze stosu" << "\n"
         << "5 - usuniecie wszystkich elementow ze stosu" << "\n"
         << "6 - wyjscie z programu" << "\n"
         << endl;

    element *stosZNullPnt = nullptr;

    int menu = -1;
    while (menu != 6) {
        cin >> menu;
        switch (menu) {
            case 1:
                komunikat = czyPusty(stosZNullPnt) ? "Pusty" : "Niepusty";
                cout << komunikat << endl;
                break;
            case 2:
                wylosowana = losuj_wartosc();
                cout << "Dodaje element " << wylosowana << " na stos" << endl;
                dodajElement(stosZNullPnt, wylosowana);
                break;
            case 3:
                if (!czyPusty(stosZNullPnt)) {
                    cout << "Usuwam pierwszy element " << stosZNullPnt->liczba << " ze stosu" << endl;
                }
                usunElement(stosZNullPnt);
                break;
            case 4:
                if (!czyPusty(stosZNullPnt)) {
                    cout << "Ostatni element to: " << pobierzElement(stosZNullPnt) << endl;
                }
                break;
            case 5:
                cout << "Usuwam wszystkie elementy" << endl;
                usunWszystkieElementy(stosZNullPnt);
                break;
            case 6:
                return 0;
        }
    }
}
