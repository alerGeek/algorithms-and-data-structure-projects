#include <iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
struct element {
    int liczba = 0;
    element *next = nullptr;
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
    el->liczba = wartosc;
    el->next = nullptr;

    if (lista.tail != nullptr) {
        lista.tail->next = el;
    }

    lista.tail = el;

    if (lista.head == nullptr) {
        lista.head = lista.tail;
    }

    lista.liczbaEl++;
}

void dodaj_poczatek(lista &lista, int wartosc) {
    element *el = new element;
    el->liczba = wartosc;
    el->next = lista.head;
    lista.head = el;

    if (lista.tail == nullptr) {
        lista.tail = el;
    }
    lista.liczbaEl++;
}

void dodaj_pozycja(lista &lista, int pos, int wartosc) {
    if (pos == 1) {
        dodaj_poczatek(lista, wartosc);
        return;

    }

    if (pos == lista.liczbaEl + 1) {
        dodaj_koniec(lista, wartosc);
        return;
    }

    element *el = new element;
    el->liczba = wartosc;
    element *temp = lista.head;
    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    el->next = temp->next;
    temp->next = el;

    lista.liczbaEl++;
}

void usun_ostatni(lista &lista) {
    if (czy_pusty(lista)) {
        cout << "Nie mozna usunac, lista jest juz pusta" << endl;
        return;
    }

    element *temp = lista.tail;
    if (lista.liczbaEl == 1) {
        lista.tail = nullptr;
        lista.head = nullptr;
    } else {
        element *bef_temp = lista.head;
        for (int i = 1; i < lista.liczbaEl - 1; i++) {
            bef_temp = bef_temp->next;
        }
        lista.tail = bef_temp;
        lista.tail->next = nullptr;
    }
    delete temp;
    lista.liczbaEl--;
}

void usun_pierwszy(lista &lista) {
    if (czy_pusty(lista)) {
        cout << "Nie mozna usunac, lista jest juz pusta" << endl;
        return;
    }

    element *temp = lista.head;

    lista.head = lista.head->next;
    delete temp;
    if (lista.head == nullptr) {
        lista.tail = nullptr;
    }

    lista.liczbaEl--;
}

void usun_pozycja(lista &lista, int pos) {
    if (pos <= 0) {
        cout << "Nie mozna usunac, nie ma ujemnych pozycji" << endl;
        return;
    } else if (pos == 0) {
        usun_pierwszy(lista);
        return;
    } else if (pos == lista.liczbaEl) {
        usun_ostatni(lista);
        return;
    }

    element *temp = lista.head;

    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    element *temp_us = temp->next;
    temp->next = temp_us->next;
    delete temp_us;
    lista.liczbaEl--;
}

int pobierz_pierwszy(lista &lista) {
    if (!czy_pusty(lista)) {
        return lista.head->liczba;
    }
}

int pobierz_ostatni(lista &lista) {
    if (!czy_pusty(lista)) {
        return lista.tail->liczba;
    }
}

void wyswietl(lista lista) {
    while (!czy_pusty(lista)) {
        cout << lista.head->liczba << endl;
        lista.head = lista.head->next;
    }
}

void usun_liste(lista &lista) {
    while (!czy_pusty(lista)) {
        lista.head = lista.head->next;
    }
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

double oblicz_srednia(lista lista) {
    int suma = 0;
    while (!czy_pusty(lista)) {
        suma += pobierz_pierwszy(lista);
        lista.head = lista.head->next;
    }
    return (double) suma / lista.liczbaEl;
}

int main() {
    lista lista;
    lista.head = nullptr;
    lista.tail = nullptr;
    lista.liczbaEl = 0;

    string komunikat;
    int wartosc, pos;
    srand(time(nullptr));

    int menu = -1;
    cout << "Menu:" << endl;
    cout << "1 - Sprawdzenie czy kolejka jest pusta" << endl;
    cout << "2 - Dodanie elementu na koniec listy" << endl;
    cout << "3 - Dodanie elementu na poczatek listy" << endl;
    cout << "4 - Dodanie elementu na pozycje " << endl;
    cout << "5 - Usuniecie elementu z konca listy" << endl;
    cout << "6 - Usuniecie elementu z poczatku listy" << endl;
    cout << "7 - Usuniecie elementu z pozycji" << endl;
    cout << "8 - Pobierz pierwszy element" << endl;
    cout << "9 - Pobierz ostatni element" << endl;
    cout << "10 - Policzenie srednia arytmetyczna" << endl;
    cout << "11 - Wyswietlenie calej liste" << endl;
    cout << "12 - Usuniecie calej listy wraz ze zwolnieniem pamieci" << endl;
    cout << "13 - Wyjscie z programu" << endl;

    while (menu != 13) {
        cin >> menu;
        switch (menu) {
            case 1:
                komunikat = czy_pusty(lista) ? "Pusty" : "Niepusty";
                cout << komunikat << endl;
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
                    dodaj_pozycja(lista, pos, wartosc);
                }
                break;
            case 5:
                if (!czy_pusty(lista)) {
                    cout << "Usuwam ostatni element: " << lista.tail->liczba << endl;
                    usun_ostatni(lista);
                } else {
                    cout << "Lista pusta, nie da się usunac" << endl;
                }
                break;
            case 6:
                if (!czy_pusty(lista)) {
                    cout << "Usuwam pierwszy element: " << lista.head->liczba << endl;
                    usun_pierwszy(lista);
                } else {
                    cout << "Lista pusta, nie da się usunac" << endl;
                }
                break;
            case 7:
                pos = 2;
                if (sprawdz_pozycje(lista, pos)) {
                    cout << "Usuwam element z pozycji " << pos << endl;
                    usun_pozycja(lista, pos);
                }
                break;
            case 8:
                cout << "Pierwszy element to: " <<
                     pobierz_pierwszy(lista) << endl;
                break;
            case 9:
                cout << "Ostatni element to: " <<
                     pobierz_ostatni(lista) << endl;
                break;
            case 10:
                cout << "Sredni arytmetyczna = ";
                cout << oblicz_srednia(lista) << endl;
                break;
            case 11:
                cout << "Lista: " << endl;
                wyswietl(lista);
                break;
            case 12:
                cout << "Usunieto liste" << endl;
                usun_liste(lista);
                break;

        }
    }
}