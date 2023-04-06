#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

inline bool czyIstnieje(const string& nazwa) {
    //Sprawdza czy plik o danej nazwie istnieje (pomogl mi stackoverflow)
    struct stat buffer;
    return (stat(nazwa.c_str(), &buffer) == 0);
}

void menu() {
    cout << "Witam w 'lista zakupow'" << endl;
    cout << "Co chcesz zrobic?" << endl;
    cout << "1. Dla kogo ma byc lista zakupow" << endl;
    cout << "2. Dodaj rzecz do listy zakupow" << endl;
    cout << "3. Wyswietl liste rzeczy danej osoby" << endl;
    cout << "4. Usun rzecz z listy" << endl;
    cout << "5. Usun osobe" << endl;
    cout << "6. Wyjdz" << endl;
}

int main() {
    struct Produkt {
        string nazwa;
        int liczba;
    };
    int liczba = 0;
    string imie = "";
    string tekst = "";
    fstream plik;
    int wybor = 0;
    Produkt* produkt = nullptr;
    bool dziala = true;
    vector<string> vektorSlow; //uzylem tu vektora, poniewaz vektory sa szybsze w moim przypadku (uzylem tego w usuwaniu z listy)
    while (dziala) {
        menu();
        cin >> wybor;
        switch (wybor) {
        case 1:
            cout << "Jak ma sie nazwywac ta osoba?" << endl;
            cin >> imie;
            if (czyIstnieje(imie + ".txt")) {
                cout << "Taki czlowiek juz istnieje! Wracam do menu." << endl;
                Sleep(2000);
                system("cls");
            }
            else {
                cout << "Utworzono plik" << endl;
                plik.open(imie + ".txt", ios::out);
                plik.close();
                Sleep(2000);
                system("cls");
            }
            break;
        case 2:
            imie = "";
            cout << "Podaj imie osoby" << endl;
            cin >> imie;
            if (!czyIstnieje(imie + ".txt")) {
                cout << "Taka osoba nie istnieje, wracam do menu" << endl;
                Sleep(2000);
                system("cls");
                break;
            }
            plik.open(imie + ".txt", ios::app);
            if (!plik.is_open()) {
                cout << "Plik nie zostal otworzony, najprawdopodobniej nie zostal on utworzony!" << endl;
                break;
            }
            cout << "Ile chcesz dodac przedmiotow?" << endl;
            cin >> liczba;
            produkt = new Produkt[liczba];
            for (int i = 0; i < liczba; i++) {
                cout << "Co chcesz dodac? " << endl;
                cin >> produkt[i].nazwa;
                if (produkt[i].nazwa == "") {
                    cout << "Nazwa nie moze byc pusta! " << endl;
                    delete[] produkt;
                    exit(1);
                }
                cout << "Ile sztuk chcesz dodac?" << endl;
                cin >> produkt[i].liczba;
                if (produkt[i].liczba <= 0) {
                    cout << "Nie mozna dodac przedmiotu o liczbe sztuk mniejsza niz 0 " << endl;
                    delete[] produkt;
                    exit(1);
                }
                cout << "Dodano!" << endl;
                plik << "Nazwa:" << produkt[i].nazwa << "," << "liczba sztuk:" << produkt[i].liczba << endl;
                Sleep(2000);
            }
            delete[] produkt;
            plik.close();
            system("cls");
            break;
        case 3:
            imie = "";
            cout << "Podaj imie osoby" << endl;
            cin >> imie;
            if (!czyIstnieje(imie + ".txt")) {
                cout << "Taka osoba nie istnieje, wracam do menu" << endl;
                Sleep(2000);
                system("cls");
                break;
            }
            plik.open(imie + ".txt", ios::in);
            cout << "Lista:" << endl;
            cout << "----------" << endl;
            while (getline(plik, tekst)) {
                cout << tekst << endl;
            }
            cout << "----------" << endl;
            plik.close();
            tekst = "";
            cout << "Nacisnij dowolny klawisz, aby powrocic do menu." << endl;
            getchar();
            cin.ignore();
            system("cls");
            break;

        case 4:
            imie = "";
            cout << "Podaj imie osoby" << endl;
            cin >> imie;
            if (!czyIstnieje(imie + ".txt")) {
                cout << "Taka osoba nie istnieje, wracam do menu" << endl;
                Sleep(2000);
                system("cls");
                break;
            }
            plik.open(imie + ".txt", ios::in);
            while (getline(plik, tekst)) {
                vektorSlow.push_back(tekst);
            }
            tekst = "";
            plik.close();
            cout << "Lista:" << endl;
            cout << "----------" << endl;
            for (int i = 0; i < vektorSlow.size(); i++)
            {
                cout << i + 1 << "." << vektorSlow[i] << endl;
            }
            cout << "----------" << endl;
            int index;
            cout << "Podaj indeks, ktory chcesz usunac" << endl;
            cin >> index;
            if (index > 0 && index <= vektorSlow.size()) {
                vektorSlow.erase(vektorSlow.begin() + index - 1);
            }
            else {
                cout << "Wybrales zly indeks, sprobuj jeszcze raz" << endl;
                vektorSlow.clear();
                break;
            }
            plik.open(imie + ".txt", ios::out | ios::trunc);
            for (int i = 0; i < vektorSlow.size(); i++) {
                plik << vektorSlow[i] << endl;
            }
            plik.close();
            cout << "Usunieto pomyslnie!" << endl;
            vektorSlow.clear();
            Sleep(2000);
            system("cls");
            break;
        case 5:
            imie = "";
            cout << "Podaj osobe ktora chcesz usunac" << endl;
            cin >> imie;
            if (!czyIstnieje(imie + ".txt")) {
                cout << "Taka osoba nie istnieje, wracam do menu" << endl;
                Sleep(2000);   
                system("cls");
            }
            int usuwanie;
            usuwanie = remove((imie + ".txt").c_str());
            if (usuwanie == 0) {
                cout << "Osoba zostala usunieta!" << endl;
                Sleep(2000);
                system("cls");
            }
            else {
                cout << "Wystapil bład, sprobuj ponownie!" << endl;
                Sleep(2000);
                system("cls");
            }
            plik.close();
            break;
        case 6:
            exit(1);
        default:
            cout << "Niepoprawna komenda" << endl;
            Sleep(1000);
            system("cls");
            break;
        }
    }
    return 0;
}
