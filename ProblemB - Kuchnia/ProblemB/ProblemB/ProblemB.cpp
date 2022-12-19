#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<int>> moc;
int n;


void split(string text);
int findBiggestNumber(vector<int> moc);

int main()
{

    // Pobierz wartosc n oznaczającą ilość elementow grzejacych

    //cout<<"Podaj ilosc elementow grzejacych: ";
    cin >> n;
    // Zdefiniuj potrzebne zmienne 
    vector<int> biggestID; // <- Tablica wartości pozycji największej liczby
    int obroty = n;  // Maksymalna liczba obrotów

    string input; // Czasowa zmiena do pobrania znaków z klawiatury


    // ------------------------------------------------------------------

    // Pętla przez wszystkie elementy grzejące
    for (int i = 0; i < n; i++) {

        // Pobranie danych od użytkownika
        //cout<<"Podaj wartosc elementow grzejacych: ";
        cin >> input;

        //Funkcja tworzaca tablice wartosc elementu grzejącego
        split(input);

        //Znalezienie pozycji najwekszej liczby
        biggestID.push_back(findBiggestNumber(moc[i]));


        // Sprawdzenie tablicy pod kątem ilości obrotow
        if (biggestID[i] == 0) {
            obroty--;
            continue;
        }
        if (i == 0) {
            continue;
        }
        else {
            if (biggestID[i - 1] == biggestID[i]) {
                obroty--;
            }
        }

    }

    cout << obroty << endl;

    return 0;
}


void split(string text) {
    //potrzebne zmienne
    int index = 0;
    vector<int> tempMoc;

    //podział wejścia na pojedyncze liczby
    for (char letter : text) {
        tempMoc.push_back((int)letter - 48);

        index++;
    }
    // zapisanie wyniku
    moc.push_back(tempMoc);
}

int findBiggestNumber(vector<int> moc) {

    vector<short> ID;
    int biggestNumer = 0;
    short index = 0;

    //Znalezienie pozycji z największą liczbą
    for (int i : moc) {
        if (i > biggestNumer) {
            biggestNumer = i;
            ID.clear();
            ID.push_back(index);
        }
        else if (i == biggestNumer) {
            ID.push_back(index);
        }
        index++;
    }

    vector<int> returnValues;
    int temp = 0;
    biggestNumer = 0;

    // W przypadku wiekszej ilości największych liczb: Znajdź największą liczbe po przesunięciu
    if (ID.size() > 1) {
        for (int i = 0; i < ID.size(); i++) {
            short indexer = ID[i];
            temp = 0;
            for (int j = moc.size() - 1; j >= 0; j--) {

                if (indexer >= moc.size()) {
                    indexer = 0;
                }
                temp += moc[indexer] * pow(10, j);

                indexer++;
            }

            returnValues.push_back(temp);
        }
        for (int i = 0; i < returnValues.size(); i++) {
            if (returnValues[i] > biggestNumer) {
                biggestNumer = returnValues[i];
                index = i;
            }

        }
        ID[0] = ID[index];

    }

    return ID[0];




}