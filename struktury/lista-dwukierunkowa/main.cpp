#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct element {
    int wartosc = 0;
    element *next = nullptr;
    element *previous = nullptr;
};

struct lista {
    element *head = nullptr;
    element *tail = nullptr;
    int liczbaEl = 0;
};

bool czy_pusty(lista lista) {
    return lista.head == nullptr;
}

void dodaj_koniec(lista &lista, int wartosc) {
    element *el = new element;

    el->wartosc = wartosc;
    el->next = nullptr;
    el->previous = nullptr;

    if (lista.tail != nullptr) {
        lista.tail->next = el;
        el->previous = lista.tail;
    }

    lista.tail = el;

    if (lista.head == nullptr) {
        lista.head = el;
    }

    lista.liczbaEl++;
}

void dodaj_poczatek(lista &lista, int wartosc) {
    element *el = new element;

    el->wartosc = wartosc;
    el->next = nullptr;
    el->previous = nullptr;

    if (lista.head != nullptr) {
        lista.head->previous = el;
        el->next = lista.head;
    }
    lista.head = el;
    if (lista.tail == nullptr) {
        lista.tail = el;
    }
    lista.liczbaEl++;
}

void dodaj_pozycja(lista &lista, int wartosc, int pos) {

    if (pos == 1) {
        dodaj_poczatek(lista, wartosc);
        return;
    }

    if (pos == lista.liczbaEl + 1) {
        dodaj_koniec(lista, wartosc);
        return;
    }

    element *temp = lista.head;
    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    element *el = new element;
    el->wartosc = wartosc;
    el->previous = temp;
    el->next = temp->next;
    temp->next->previous = el;
    temp->next = el;

    lista.liczbaEl++;
}

void usun_ostatni_2k(lista &lista) {
    if (czy_pusty(lista)) {
        cout << "Nie mozna usunac, lista jest juz pusta" << endl;
        return;
    }
    element *temp = lista.tail;
    if (lista.liczbaEl == 1) {
        lista.tail = nullptr;
        lista.head = nullptr;
    } else {
        lista.tail = lista.tail->previous;
        lista.tail->next = nullptr;
    }
    lista.liczbaEl--;
    delete temp;
}

void usun_pierwszy_2K(lista &lista) {

    if (czy_pusty(lista)) {
        cout << "Nie mozna usunac, lista jest juz pusta" << endl;
        return;
    }

    element *temp = lista.head;

    if (lista.liczbaEl == 1) {
        lista.head = nullptr;
        lista.tail = nullptr;
    } else {
        lista.head = lista.head->next;
        lista.head->previous = nullptr;
    }
    lista.liczbaEl--;
    delete temp;
}

void usun_pozycja_2k(lista &lista, int pos) {

    if (pos > lista.liczbaEl) {
        cout << "Nie mozna usunac, nie ma takiej pozycji" << endl;
        return;
    }

    element *temp = lista.head;
    cout << "Usuwam element: " << temp->wartosc << " z pozycji " << pos << endl;

    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    element *temp_us = temp->next;
    temp->next = temp_us->next;
    temp->next->previous = temp;

    lista.liczbaEl--;
    delete temp_us;
}

void wyswietl_od_poczatku(lista lista) {
    while (lista.head != nullptr) {
        cout << lista.head->wartosc << endl;
        lista.head = lista.head->next;

    }
}

void wyswietl_od_konca(lista lista) {
    while (lista.tail != nullptr) {
        cout << lista.tail->wartosc << endl;
        lista.tail = lista.tail->previous;
    }
}

void usun_liste(lista &lista) {
    while (!czy_pusty(lista)) {
        usun_pierwszy_2K(lista);
    }

    delete lista.head;
    delete lista.tail;
}

int losuj_wartosc() {
    int wartosc;
    wartosc = rand() % 100 + 0;
    return wartosc;
}

bool sprawdz_pozycje(lista lista, int pos) {
    if (pos <= 0) {
        cout << "Lista nie ma ujemnych pozycji" << endl;
        return false;
    }
    if (pos > lista.liczbaEl + 1) {
        cout << "Lista nie ma tylu elementow." << endl;
        return false;
    }
    return true;
}

int main() {
    lista lista;
    lista.head = nullptr;
    lista.tail = nullptr;
    lista.liczbaEl = 0;

    srand(time(nullptr));
    int wartosc, pos;

    int menu = -1;
    cout << "Menu:" << endl;
    cout << "1 - Sprawdzenie czy kolejka jest pusta" << endl;
    cout << "2 - Dodanie elementu na koniec listy" << endl;
    cout << "3 - Dodanie elementu na poczatek listy" << endl;
    cout << "4 - Dodanie elementu na pozycje " << endl;
    cout << "5 - Usuniecie elementu z konca listy" << endl;
    cout << "6 - Usuniecie elementu z poczatku listy" << endl;
    cout << "7 - Usuniecie elementu z pozycji" << endl;
    cout << "8 - Wyswietl od poczatku do konca" << endl;
    cout << "9 - Wyswietl od konca do poczatku" << endl;
    cout << "10 - Usun cala liste wraz ze zwolnieniem pamieci" << endl;
    cout << "11 - Wyjscie z programu" << endl;

    while (menu != 11) {
        cin >> menu;
        switch (menu) {
            case 1: {
                czy_pusty(lista);
                string komunikat = czy_pusty(lista) ? "Pusty" : "Niepusty";
                cout << komunikat << endl;
            }
                break;
            case 2:
                wartosc = losuj_wartosc();
                cout << "Dodaje " << wartosc << " na koniec" << endl;
                dodaj_koniec(lista, wartosc);
                break;
            case 3:
                wartosc = losuj_wartosc();
                cout << "Dodaje " << wartosc << " na poczatek" << endl;
                dodaj_poczatek(lista, wartosc);
                break;
            case 4:
                pos = 2;
                wartosc = losuj_wartosc();

                if (sprawdz_pozycje(lista, pos)) {
                    cout << "Dodaje " << wartosc << " na pozycje " << pos << endl;
                    dodaj_pozycja(lista, wartosc, pos);
                }
                break;
            case 5:
                cout << "Usuwam ostatni element: " << lista.tail->wartosc << endl;
                usun_ostatni_2k(lista);
                break;
            case 6:
                cout << "Usuwam pierwszy element: " << lista.head->wartosc << endl;
                usun_pierwszy_2K(lista);
                break;
            case 7:
                pos = 2;
                if (sprawdz_pozycje(lista, pos)) {
                    cout << "Usuwam element z pozycji " << pos << endl;
                    usun_pozycja_2k(lista, pos);
                }
                break;
            case 8:
                cout << "Elementy listy od pierwszego:" << endl;
                wyswietl_od_poczatku(lista);
                break;
            case 9:
                cout << "Elementy listy od ostatniego:" << endl;
                wyswietl_od_konca(lista);
                break;
            case 10:
                cout << "Usuwam cala liste" << endl;
                usun_liste(lista);
                break;
        }
    }

    return 0;
}

