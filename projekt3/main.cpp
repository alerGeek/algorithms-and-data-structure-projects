#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

struct bankomat {
    string id;
    int lokalizacja_id;
    string miasto;
    bool czy_aktywny;

    int ilosc_10;
    int ilosc_20;
    int ilosc_50;
    int ilosc_100;
    int ilosc_200;

    int suma_gotowki;
};

struct element {
    bankomat *bankomat = nullptr;
    element *next = nullptr;
    element *previous = nullptr;
};

struct lista {
    element *head = nullptr;
    element *tail = nullptr;
    int liczbaEl = 0;
};

struct element_jedno {
    bankomat *bankomat = nullptr;
    element_jedno *next = nullptr;
};

struct lista_jedno {
    element_jedno *head = nullptr;
    element_jedno *tail = nullptr;
    bankomat *baknomat = nullptr;
};

//bankomat - pomocnicze

int oblicz_gotowke_w_banku(bankomat *bankomat) {
    return bankomat->suma_gotowki =
                   bankomat->ilosc_10 * 10
                   + bankomat->ilosc_20 * 20
                   + bankomat->ilosc_50 * 50
                   + bankomat->ilosc_100 * 100
                   + bankomat->ilosc_200 * 200;
}

void wyswietl_bankomat(bankomat *bankomat) {
    cout << "id: " << bankomat->id << "\t aktywny: " << bankomat->czy_aktywny
         << "\t suma:" << bankomat->suma_gotowki << "\t il. 10: " << bankomat->ilosc_10 << endl;
}

//lista dwukierunkowa - metody glowne

void dodaj_poczatek_2K(lista &lista, bankomat *bankomat) {
    element *el = new element;

    el->bankomat = bankomat;
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

void dodaj_koniec_2K(lista &lista, bankomat *bankomat) {
    element *el = new element;

    el->bankomat = bankomat;
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

void dodaj_pozycja_2k(lista &lista, bankomat *bankomat, int pos) {

    if (pos <= 0) {
        cout << "Bledna pozycja - lista zaczyna sie od pozycji 1 " << endl;
        return;
    }

    if (pos > lista.liczbaEl + 1) {
        cout << "Bledna pozycja - lista ma " << lista.liczbaEl << " elementow " << endl;
        return;
    }

    if (pos == 1) {
        dodaj_poczatek_2K(lista, bankomat);
        cout << "Dodano element " << bankomat->id << " na pozycje " << pos << endl;
        return;
    }

    if (pos == lista.liczbaEl + 1) {
        dodaj_koniec_2K(lista, bankomat);
        cout << "Dodano element " << bankomat->id << " na pozycje " << pos << endl;
        return;
    }

    element *temp = lista.head;
    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    element *el = new element;
    el->bankomat = bankomat;
    el->previous = temp;
    el->next = temp->next;
    temp->next->previous = el;
    temp->next = el;
    cout << "Dodano element " << bankomat->id << " na pozycje " << pos << endl;

    lista.liczbaEl++;
}

void usun_pierwszy_2K(lista &lista) {
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

void usun_ostatni_2k(lista &lista) {
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

void usun_pozycja_2k(lista &lista, int pos) {

    if (pos > lista.liczbaEl || pos <= 0) {
        cout << "Nie mozna usunac, nie ma takiej pozycji" << endl;
        return;
    }

    if (pos == 1) {
        cout << "Usunieto element " << lista.head->bankomat->id << " z pozycji " << pos << endl;
        usun_pierwszy_2K(lista);
        return;
    }

    if (pos == lista.liczbaEl) {
        cout << "Usunieto element " << lista.tail->bankomat->id << " z pozycji " << pos << endl;
        usun_ostatni_2k(lista);
        return;
    }

    element *temp = lista.head;

    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    element *temp_us = temp->next;
    temp->next = temp_us->next;
    temp->next->previous = temp;

    cout << "Usunieto element z pozycji: " << temp_us->bankomat->id << " z pozycji " << pos << endl;
    lista.liczbaEl--;
    delete temp_us;
}

//lista jednokierunkowa - metody glowne

void wyswietl_1K(lista_jedno lista_jedno) {
    while (lista_jedno.head != nullptr) {
        wyswietl_bankomat(lista_jedno.head->bankomat);
        lista_jedno.head = lista_jedno.head->next;
    }
}

void dodaj_1K(lista_jedno &lista_jedno, bankomat *bankomat) {
    element_jedno *el = new element_jedno;
    el->bankomat = bankomat;
    el->next = nullptr;

    if (lista_jedno.tail != nullptr) {
        lista_jedno.tail->next = el;
    }

    lista_jedno.tail = el;

    if (lista_jedno.head == nullptr) {
        lista_jedno.head = lista_jedno.tail;
    }
}

void usun_1K(lista_jedno &lista_jedno) {
    element_jedno *temp = lista_jedno.head;

    lista_jedno.head = lista_jedno.head->next;
    delete temp;
    if (lista_jedno.head == nullptr) {
        lista_jedno.tail = nullptr;
    }
}


//wczytanie danych

void wczytaj_banki_do_listy(string nazwa_pliku, lista &lista, int &ilosc_bankow, int &srednia_wyplacana) {

    ifstream plik;
    string linia;
    string temp_id, temp_lokalizacja, temp_miasto, temp_czy_aktywny, temp_10, temp_20, temp_50, temp_100, temp_200;

    plik.open(nazwa_pliku);
    plik >> ilosc_bankow;

    char sredniki;
    for (int i = 0; i < 8; i++) {
        plik >> sredniki;
    }

    plik >> srednia_wyplacana;
    for (int i = 0; i < 8; i++) {
        plik >> sredniki;
    }

    while (!plik.eof()) {
        bankomat *temp_bankomat = new bankomat;
        plik >> linia;
        if (plik.eof()) {
            break;
        }
        istringstream ss(linia);
        getline(ss, temp_id, ';');
        getline(ss, temp_lokalizacja, ';');
        getline(ss, temp_miasto, ';');
        getline(ss, temp_czy_aktywny, ';');
        getline(ss, temp_10, ';');
        getline(ss, temp_20, ';');
        getline(ss, temp_50, ';');
        getline(ss, temp_100, ';');
        getline(ss, temp_200, ';');

        temp_bankomat->id = temp_id;
        temp_bankomat->lokalizacja_id = atoi(temp_lokalizacja.c_str());
        temp_bankomat->miasto = temp_miasto;
        temp_bankomat->czy_aktywny = atoi(temp_czy_aktywny.c_str());
        temp_bankomat->ilosc_10 = atoi(temp_10.c_str());
        temp_bankomat->ilosc_20 = atoi(temp_20.c_str());
        temp_bankomat->ilosc_50 = atoi(temp_50.c_str());
        temp_bankomat->ilosc_100 = atoi(temp_100.c_str());
        temp_bankomat->ilosc_200 = atoi(temp_200.c_str());
        temp_bankomat->suma_gotowki = oblicz_gotowke_w_banku(temp_bankomat);

        dodaj_koniec_2K(lista, temp_bankomat);
    }
    plik.close();
}

//zadanie 1

bool czy_bankomat_istnieje(lista lista, bankomat *bankomat) {
    while (lista.head != nullptr) {
        if (lista.head->bankomat->id == bankomat->id) {
            return true;
        }
        lista.head = lista.head->next;
    }
    return false;
}

void utworz_nowy_bankomat(lista &lista, bankomat *bankomat) {

    cout << "Podaj id lokalizacji" << endl;
    cin >> bankomat->lokalizacja_id;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Nieprawidlowe id lokalizacji." << endl;
        cin >> bankomat->lokalizacja_id;
    }

    cout << "Podaj miasto" << endl;
    cin >> bankomat->miasto;

    cout << "Podaj czy aktywny" << endl;
    cin >> bankomat->czy_aktywny;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Wpisz 0 -niekatywny albo 1 - aktywny." << endl;
        cin >> bankomat->czy_aktywny;
    }

    cout << "Podaj ilosc 10 w bankomacie" << endl;
    cin >> bankomat->ilosc_10;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Kwota nie jest cyfra." << endl;
        cin >> bankomat->ilosc_10;
    }

    cout << "Podaj ilosc 20 w bankomacie" << endl;
    cin >> bankomat->ilosc_20;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Kwota nie jest cyfra." << endl;
        cin >> bankomat->ilosc_20;
    }

    cout << "Podaj ilosc 50 w bankomacie" << endl;
    cin >> bankomat->ilosc_50;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Kwota nie jest cyfra." << endl;
        cin >> bankomat->ilosc_50;
    }

    cout << "Podaj ilosc 100 w bankomacie" << endl;
    cin >> bankomat->ilosc_100;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Kwota nie jest cyfra." << endl;
        cin >> bankomat->ilosc_100;
    }

    cout << "Podaj ilosc 200 w bankomacie" << endl;
    cin >> bankomat->ilosc_200;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Kwota nie jest cyfra." << endl;
        cin >> bankomat->ilosc_200;
    }

    bankomat->suma_gotowki = oblicz_gotowke_w_banku(bankomat);

    cout << "Utworzono nowy bankomat:" << endl;
    wyswietl_bankomat(bankomat);
}

//zadanie 2

void usun_nieaktywne(lista &lista) {
    struct lista lista_z_aktywnymi;

    while (lista.head != nullptr) {
        bankomat *bankomat = lista.head->bankomat;
        if (bankomat->czy_aktywny) {
            dodaj_koniec_2K(lista_z_aktywnymi, bankomat);
        }
        usun_pierwszy_2K(lista);
    }
    lista = lista_z_aktywnymi;
}

void usun_po_id(lista &lista, string bankomat_id) {
    element *temp = lista.head;
    for (int i = 1; i < lista.liczbaEl + 1; i++) {
        if (bankomat_id == temp->bankomat->id) {
            wyswietl_bankomat(temp->bankomat);
            usun_pozycja_2k(lista, i);
            return;
        }
        temp = temp->next;
    }
    cout << "numer id bankomatu nie istnieje, nie da sie usunac." << endl;
}

void wyswietl_od_poczatek(lista lista) {
    while (lista.head != nullptr) {
        wyswietl_bankomat(lista.head->bankomat);
        lista.head = lista.head->next;
    }
}

//zadanie 3 - lista jednokierunkowa

void utworz_liste_1K_z_kwota_do_wyplaty(lista lista, lista_jedno &lista_jedno, int srendnia_wyplacana) {

    while (lista.head != nullptr) {
        if (lista.head->bankomat->suma_gotowki > srendnia_wyplacana * 100) {
            dodaj_1K(lista_jedno, lista.head->bankomat);
        }
        lista.head = lista.head->next;
    }
}

void usun_gdy_malo_10(lista_jedno &lista_jedno) {
    struct lista_jedno lista_spelnia_ilosc;

    while (lista_jedno.head != nullptr) {
        bankomat *bankomat = lista_jedno.head->bankomat;
        if (lista_jedno.head->bankomat->ilosc_10 >= 100) {
            dodaj_1K(lista_spelnia_ilosc, bankomat);
        }
        usun_1K(lista_jedno);
    }
    lista_jedno = lista_spelnia_ilosc;
}

//glowne rozwiazania

void zadanie1(lista &lista) {

    int menu = -1;
    wyswietl_od_poczatek(lista);

    do {
        cout << endl;
        cout << "Zadanie 1 - opcje\n"
             << "\t1 - dodaj nowy bankomat\n"
             << "\t2 - wyswietl baze bankomatow\n"
             << "\t3 - wyjscie z zadania 1" << endl;

        cin >> menu;

        switch (menu) {
            case 1: {
                int pozycja;
                bankomat *bankomat = new struct bankomat;

                cout << "Podaj id bankomatu" << endl;
                cin >> bankomat->id;
                if (czy_bankomat_istnieje(lista, bankomat)) {
                    cout << "Istnieje bankomat o podanym id!" << endl;
                    break;
                }

                utworz_nowy_bankomat(lista, bankomat);
                cout << "Na ktora pozycje chcesz dodac bankomat?" << endl;
                cin >> pozycja;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                    cout << "Pozycja musi byc liczba!" << endl;
                    cin >> pozycja;
                }
                dodaj_pozycja_2k(lista, bankomat, pozycja);
            }
                break;
            case 2:
                wyswietl_od_poczatek(lista);
                break;
            case 3:
                return;
        }
    } while (menu != 3);
}

void zadanie2(lista &lista) {

    usun_nieaktywne(lista);
    wyswietl_od_poczatek(lista);

    string id;
    int menu;

    do {
        cout << endl;
        cout << "Zadanie 2 - opcje:\n"
             << "\t1 - usun bankomat po id\n"
             << "\t2 - wyswietl baze bankomatow\n"
             << "\t3 - wyjscie z zadania" << endl;

        cin >> menu;

        switch (menu) {
            case 1: {
                string bankomat_id;
                cin >> bankomat_id;
                usun_po_id(lista, bankomat_id);
            }
                break;
            case 2:
                wyswietl_od_poczatek(lista);
                break;
            case 3:
                return;
        }
    } while (menu != 3);
}

void zadanie3(lista lista, lista_jedno &lista_jedno, int srednia_wyplacana) {
    int menu = -1;

    do {
        cout << endl;
        cout << "Zadanie 3 - opcje:\n"
             << "\t1 - utworz liste zdolnych do wyplaty\n"
             << "\t2 - usun bankomaty, gdzie liczba bankotu 10 jest mniejsza niz 100\n"
             << "\t3 - wyjscie z zadania 3" << endl;

        cin >> menu;

        switch (menu) {
            case 1:
                utworz_liste_1K_z_kwota_do_wyplaty(lista, lista_jedno, srednia_wyplacana);
                wyswietl_1K(lista_jedno);
                break;
            case 2:
                usun_gdy_malo_10(lista_jedno);
                wyswietl_1K(lista_jedno);
                break;
            case 3:
                return;
        }
    } while (menu != 3);
}


int main() {
    ifstream plik;

    lista lista;
    lista_jedno lista_jedno;

    int ilosc_bankow, srednia_wyplacana;

    wczytaj_banki_do_listy("dane.csv", lista, ilosc_bankow, srednia_wyplacana);

    cout << "-----------ZADANIE 1---------------" << endl;
    zadanie1(lista);
    cout << "-----------ZADANIE 2---------------" << endl;
    zadanie2(lista);
    cout << "-----------ZADANIE 3---------------" << endl;
    zadanie3(lista, lista_jedno, srednia_wyplacana);

    return 0;
}

