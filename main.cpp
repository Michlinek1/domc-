#include <iostream>
#include <fstream>
using namespace std;


void menu(){
    cout << "Witam w 'lista zakupow'" << endl;
    cout << "Co chcesz zrobic?" << endl;
    cout << "1.Dla kogo ma byc lista zakupow" << endl;
    cout << "2.Dodaj rzecz do listy zakupow" << endl;
    cout << "3.Usun rzecz z listy" << endl;
    cout << "4.Usun osobe" << endl;
    cout << "5.Wyjdz";
}

int main(){
    string imie = "";
    fstream plik;
    int wybor {};
    menu();
    cin >> wybor;
    switch (wybor)
    {
    case 0:
        break;
    case 1:
        cout << "Jak ma sie nazywqac ta osoba" << endl;
        cin >> imie;
        cout << "Utworzono plik";
        ofstream(imie + ".txt");
        menu();
    case 2:
        plik.open(imie + ".txt", ios::app);
        int liczba = 0;
        struct Produkt{
            string nazwa;
            int liczba;
        };
        if(!plik.is_open()){
            cout << "Plik nie został otworzony, najprawdopodobniej nie został on utworzony!" << endl;
            return -1;
        }
        cout << "Ile chcesz dodac przedmiotow?" << endl;
        cin >> liczba;
        Produkt osoba [liczba];
        for(int i = 0; i < liczba; i++){
            cout << "Co chcesz dodac?" << endl;
            cin >> osoba[i].nazwa;
            cout << osoba[i].nazwa;
            if(osoba[i].nazwa == ""){
                cout << "Nazwa nie moze byc pusta!" << endl;
                exit(1);
            }
            cout << "Ile sztuk chcesz dodac?" << endl;
            cin >> osoba[i].liczba;
            if(osoba[i].liczba <= 0){
                cout << "Nie mozna dodac przedmiotu o liczbe sztuk mniejsza niz 0" << endl;
                exit(1);
            }
            plik <<"Nazwa:" <<  osoba[i].nazwa << " " << "liczba sztuk:" << osoba[i].liczba << endl;
            //system("cls");
        }
        break;
   
    }
    return 0;
}   
