#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct region {
    int pierwszy_indeks;
    int ost_indeks;
    int ilosc_bankomatow;
    int mediana;
    int czy_jakis_wyda;
};

struct bankomat {
    string id;
    int lokalizacja_id;
    string miasto;
    int czy_aktywny;

    int ilosc_10;
    int ilosc_20;
    int ilosc_50;
    int ilosc_100;
    int ilosc_200;

    int suma_gotowki;
    int kwota_wyplacona;
};

bankomat *stworz_tab(int ilosc_bankow) {
    return new bankomat[ilosc_bankow];
}

void wczytaj_dane(string nazwa_pliku, ifstream &file, int &ilosc_bankow, int &srednia_wyplacana) {
    file.open(nazwa_pliku);
    file >> ilosc_bankow;

    char sredniki;
    for (int i = 0; i < 8; i++) {
        file >> sredniki;
    }

    file >> srednia_wyplacana;
    for (int i = 0; i < 8; i++) {
        file >> sredniki;
    }
}

void wypelnij_tab(ifstream &file, bankomat *tab, int ilosc_bankow) {
    string linia;
    string temp_lokacja_id, temp_czy_aktywna;
    string temp_ilosc_10, temp_ilosc_20, temp_ilosc_50, temp_ilosc_100, temp_ilosc_200;

    for (int i = 0; i < ilosc_bankow; i++) {
        file >> linia;
        istringstream ss(linia);
        getline(ss, tab[i].id, ';');
        getline(ss, temp_lokacja_id, ';');
        getline(ss, tab[i].miasto, ';');
        getline(ss, temp_czy_aktywna, ';');
        getline(ss, temp_ilosc_10, ';');
        getline(ss, temp_ilosc_20, ';');
        getline(ss, temp_ilosc_50, ';');
        getline(ss, temp_ilosc_100, ';');
        getline(ss, temp_ilosc_200, ';');

        tab[i].lokalizacja_id = atoi(temp_lokacja_id.c_str());
        tab[i].czy_aktywny = atoi(temp_czy_aktywna.c_str());

        tab[i].ilosc_10 = atoi(temp_ilosc_10.c_str());
        tab[i].ilosc_20 = atoi(temp_ilosc_20.c_str());
        tab[i].ilosc_50 = atoi(temp_ilosc_50.c_str());
        tab[i].ilosc_100 = atoi(temp_ilosc_100.c_str());
        tab[i].ilosc_200 = atoi(temp_ilosc_200.c_str());
    }
    file.close();
}

void usun_tab(bankomat *&tab) {
    delete[] tab;
}

region *stworz_tab_reg() {
    return new region[3];
}

void usun_tab_reg(region *&tab) {
    delete tab;
}

void flaga_francuska(bankomat *tab, int pierwszy_indeks, int ilosc_bankow, region *reg) {
    int i = pierwszy_indeks - 1, j = pierwszy_indeks, k = ilosc_bankow;
    while (j < k) {
        if (tab[j].lokalizacja_id % 3 == 1) {
            i += 1;
            swap(tab[i], tab[j]);
            j += 1;
        } else if (tab[j].lokalizacja_id % 3 == 2) {
            j += 1;
        } else {
            k -= 1;
            swap(tab[k], tab[j]);
        }
    }
    reg[0].pierwszy_indeks = pierwszy_indeks;
    reg[1].pierwszy_indeks = i + 1;
    reg[2].pierwszy_indeks = k;

    reg[0].ost_indeks = i;
    reg[1].ost_indeks = k - 1;
    reg[2].ost_indeks = ilosc_bankow - 1;
}

int flaga_polska(bankomat *tab, int pierwszy_indeks, int ost_indeks) {
    int i = pierwszy_indeks;
    int j = ost_indeks - 1;
    while (i < j) {
        while (tab[i].czy_aktywny <= 0 && i < j) {
            i++;
        }
        while (tab[j].czy_aktywny > 0 && i < j) {
            j--;
        }
        if (i < j) {
            swap(tab[i], tab[j]);
            i++;
            j--;
        }
    }
    if (tab[i].czy_aktywny <= 0) {
        return i++;
    } else {
        return i;
    }
}

int guicksort_podzial(bankomat *tab, int pierwszy_indeks, int ost_indeks) {
    int pivot = tab[ost_indeks].suma_gotowki;
    int i = (pierwszy_indeks - 1);

    for (int j = pierwszy_indeks; j < ost_indeks; j++) {
        if (tab[j].suma_gotowki <= pivot) {
            i++;
            swap(tab[i], tab[j]);
        }
    }
    swap(tab[i + 1], tab[ost_indeks]);
    return i + 1;
}

void quicksort(bankomat *tab, int pierwszy_indeks, int ost_indeks) {
    if (pierwszy_indeks < ost_indeks) {
        int partitionIndex = guicksort_podzial(tab, pierwszy_indeks, ost_indeks);

        quicksort(tab, pierwszy_indeks, partitionIndex - 1);
        quicksort(tab, partitionIndex + 1, ost_indeks);
    }
}

void ile_bankow_w_regionie(region *reg) {
    for (int i = 0; i < 3; i++) {
        reg[i].ilosc_bankomatow = reg[i].ost_indeks - reg[i].pierwszy_indeks + 1;
    }
}

int oblicz_mediane_w_reg(bankomat *tab, int ilosc_bankow_w_reg, int pierwszy_indeks, int ost_indeks) {
    int srodek, mediana;

    srodek = (pierwszy_indeks + ost_indeks) / 2;
    if (ilosc_bankow_w_reg % 2 == 0) {
        mediana = (tab[srodek].suma_gotowki + tab[srodek + 1].suma_gotowki) / 2;
    } else {
        mediana = tab[srodek].suma_gotowki;
    }
    return mediana;
}

void oblicz_gotowke_w_bankomatach(bankomat *tab, int pierwszy_aktywny_index, int ilosc_bankow) {
    for (int i = pierwszy_aktywny_index; i < ilosc_bankow; i++) {
        tab[i].suma_gotowki =
                tab[i].ilosc_10 * 10
                + tab[i].ilosc_20 * 20
                + tab[i].ilosc_50 * 50
                + tab[i].ilosc_100 * 100
                + tab[i].ilosc_200 * 200;
    }
}

void wyswietl_nazwe_regionu(string &region, int i) {
    switch (i) {
        case 0:
            region = "Polnoc";
            break;
        case 1:
            region = "Centrum i zachod";
            break;
        case 2:
            region = "Wschod i poludnie";
            break;
    }
    cout << region << endl;
}

int przypiszIloscNominalowDoTymczasowej(bankomat *tab, int &nrBankWReg, int nominal) {
    int temp_iloscNominalowWDanymBanku;
    switch (nominal) {
        case 200:
            temp_iloscNominalowWDanymBanku = tab[nrBankWReg].ilosc_200;
            break;
        case 100:
            temp_iloscNominalowWDanymBanku = tab[nrBankWReg].ilosc_100;
            break;
        case 50:
            temp_iloscNominalowWDanymBanku = tab[nrBankWReg].ilosc_50;
            break;
        case 20:
            temp_iloscNominalowWDanymBanku = tab[nrBankWReg].ilosc_20;
            break;
        case 10:
            temp_iloscNominalowWDanymBanku = tab[nrBankWReg].ilosc_10;
            break;
    }
    return temp_iloscNominalowWDanymBanku;
}

int pobierz_max_liczbe_danego_nominalu(bankomat *tab, int &nrBankWReg,
                                       int &liczba_nominalow, int nominal, int &do_wyplaty) {

    int temp_iloscNominaluWDanymBanku = przypiszIloscNominalowDoTymczasowej(tab, nrBankWReg, nominal);

    while (temp_iloscNominaluWDanymBanku > 0 && tab[nrBankWReg].kwota_wyplacona + nominal <= do_wyplaty) {
        tab[nrBankWReg].ilosc_200 -= 1;
        switch (nominal) {
            case 200:
                tab[nrBankWReg].ilosc_200 -= 1;
                temp_iloscNominaluWDanymBanku = tab[nrBankWReg].ilosc_200;
                break;
            case 100:
                tab[nrBankWReg].ilosc_100 -= 1;
                temp_iloscNominaluWDanymBanku = tab[nrBankWReg].ilosc_100;
                break;
            case 50:
                tab[nrBankWReg].ilosc_50 -= 1;
                temp_iloscNominaluWDanymBanku = tab[nrBankWReg].ilosc_50;
                break;
            case 20:
                tab[nrBankWReg].ilosc_20 -= 1;
                temp_iloscNominaluWDanymBanku = tab[nrBankWReg].ilosc_20;
                break;
            case 10:
                tab[nrBankWReg].ilosc_10 -= 1;
                temp_iloscNominaluWDanymBanku = tab[nrBankWReg].ilosc_10;
                break;
        }

        liczba_nominalow++;
        tab[nrBankWReg].kwota_wyplacona += nominal;
    }
    return liczba_nominalow;
}

void wyswietlKombinacje(int liczbaNominalow, int nominal) {
    if (liczbaNominalow > 0) {
        cout << liczbaNominalow << " x " << nominal << ", ";
    }
}

void zadanie1(bankomat *tab, int ilosc_bankow, region *reg) {
    string region;
    int max_region = 0;
    int ile_bankomatow_w_max_regionie = 0;

    flaga_francuska(tab, 0, ilosc_bankow, reg);
    ile_bankow_w_regionie(reg);

    for (int i = 0; i < 3; i++) {
        if (reg[i].ilosc_bankomatow > ile_bankomatow_w_max_regionie) {
            max_region = i + 1;
            ile_bankomatow_w_max_regionie = reg[i].ilosc_bankomatow;
        }
    }

    cout << "Region z najwieksza iloscia bankomatow: " << max_region << "\t"
         << "Liczba bankomatow: " << ile_bankomatow_w_max_regionie << endl;

    for (int i = 0; i < 3; i++) {
        wyswietl_nazwe_regionu(region, i);

        for (int j = reg[i].pierwszy_indeks; j < reg[i].ost_indeks + 1; j++) {
            cout << tab[j].id << " w " << tab[j].miasto << endl;
        }
    }
}

void zadanie2(bankomat *tab, int ilosc_bankow, int &pierwszy_aktywny, region *reg) {
    string region;
    string max_bank_w_reg_id, min_bank_w_reg_id;

    pierwszy_aktywny = flaga_polska(tab, 0, ilosc_bankow);
    flaga_francuska(tab, pierwszy_aktywny, ilosc_bankow, reg);

    oblicz_gotowke_w_bankomatach(tab, pierwszy_aktywny, ilosc_bankow);

    for (int i = 0; i < 3; i++) {
        quicksort(tab, reg[i].pierwszy_indeks, reg[i].ost_indeks);
        reg[i].mediana = oblicz_mediane_w_reg(tab, reg[i].ilosc_bankomatow, reg[i].pierwszy_indeks, reg[i].ost_indeks);
        max_bank_w_reg_id = tab[reg[i].ost_indeks].id;
        min_bank_w_reg_id = tab[reg[i].pierwszy_indeks].id;

        wyswietl_nazwe_regionu(region, i);

        cout << "Najmniej pieniedzy: " << min_bank_w_reg_id << endl;
        cout << "Najwiecej pieniedzy: " << max_bank_w_reg_id << endl;
        cout << "Mediana: " << reg[i].mediana << " zl" << endl;
    }
}

void zadanie3(bankomat *tab, int srednia_wyplacana, region *reg) {

    int temp_liczba_10;
    int temp_liczba_20;
    int temp_liczba_50;
    int temp_liczba_100;
    int temp_liczba_200;

    int temp_czy_wyda;
    string region;

    for (int nrReg = 0; nrReg < 3; nrReg++) {

        wyswietl_nazwe_regionu(region, nrReg);

        for (int nrBankWReg = reg[nrReg].pierwszy_indeks; nrBankWReg < reg[nrReg].ost_indeks + 1; nrBankWReg++) {
            int do_wyplacenia = srednia_wyplacana * 100;
            temp_czy_wyda = 0;

            temp_liczba_10 = 0;
            temp_liczba_20 = 0;
            temp_liczba_50 = 0;
            temp_liczba_100 = 0;
            temp_liczba_200 = 0;

            while (tab[nrBankWReg].kwota_wyplacona <= do_wyplacenia && temp_czy_wyda == 0) {
                temp_liczba_200 = pobierz_max_liczbe_danego_nominalu(tab, nrBankWReg,
                                                                     temp_liczba_200, 200, do_wyplacenia);
                temp_liczba_100 = pobierz_max_liczbe_danego_nominalu(tab, nrBankWReg,
                                                                     temp_liczba_100, 100, do_wyplacenia);
                temp_liczba_50 = pobierz_max_liczbe_danego_nominalu(tab, nrBankWReg,
                                                                    temp_liczba_50, 50, do_wyplacenia);
                temp_liczba_20 = pobierz_max_liczbe_danego_nominalu(tab, nrBankWReg,
                                                                    temp_liczba_20, 20, do_wyplacenia);
                temp_liczba_10 = pobierz_max_liczbe_danego_nominalu(tab, nrBankWReg,
                                                                    temp_liczba_10, 10, do_wyplacenia);

                if (tab[nrBankWReg].kwota_wyplacona == do_wyplacenia) {
                    temp_czy_wyda = 1;
                    reg[nrReg].czy_jakis_wyda = 1;
                    cout << tab[nrBankWReg].id
                         << " w " << tab[nrBankWReg].miasto
                         << ": ";

                    wyswietlKombinacje(temp_liczba_200, 200);
                    wyswietlKombinacje(temp_liczba_100, 100);
                    wyswietlKombinacje(temp_liczba_50, 50);
                    wyswietlKombinacje(temp_liczba_20, 20);
                    wyswietlKombinacje(temp_liczba_10, 10);
                    cout << endl;
                } else {
                    temp_czy_wyda = -1;
                }
            }
        }
        if (reg[nrReg].czy_jakis_wyda != 1) {
            cout << "nie mozna" << endl;
        }
    }
}

int main() {
    ifstream file;
    int ilosc_bankow;
    int srednia_wyplacana;

    int pierwszy_aktywny;

    wczytaj_dane("dane.csv", file, ilosc_bankow, srednia_wyplacana);
    bankomat *tab = stworz_tab(ilosc_bankow);
    wypelnij_tab(file, tab, ilosc_bankow);

    region *reg = stworz_tab_reg();

    cout << "----------------------------------------------" << endl;
    zadanie1(tab, ilosc_bankow, reg);
    cout << "----------------------------------------------" << endl;
    zadanie2(tab, ilosc_bankow, pierwszy_aktywny, reg);
    cout << "----------------------------------------------" << endl;
    zadanie3(tab, srednia_wyplacana, reg);

    usun_tab(tab);
    usun_tab_reg(reg);
}