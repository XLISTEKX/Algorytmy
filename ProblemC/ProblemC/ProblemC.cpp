#include <iostream>
#include <vector>
#include <cmath>
#include<sstream>

using namespace std;

float m, c;

float odleglosc(vector<float> pozycja_balonika);
float tor_lotu(float x);
void split(string text);
vector<int> args;

int main()
{
    short loops;

    int n = 0;
    float x = 0, y =0;
    string input;


    //cout << "Podaj  ilość testów: ";
    cin >> loops;
    vector<int> iloscTrafien;
    for (int i = 0; i < loops; i++)
    {
        iloscTrafien.push_back(0);
        //cout << "Podaj ilość baloników, wartość x i wartość y: " << endl;
        getline(cin >> ws, input);
        vector<float> kierunek_rzutu = { x, y };

        split(input);
        n = args[0];
        kierunek_rzutu[0] = args[1];
        kierunek_rzutu[1] = args[2];


        if (x != 0) {
            m = kierunek_rzutu[1] / kierunek_rzutu[0]; // m = dy / dx
        }


        vector<vector<float>> pozycja_balonika;
        vector<int> r;

        for (int j = 0; j < n; j++)
        {
            r.push_back(0);
            vector<float> tempV = {0,0};
            pozycja_balonika.push_back(tempV);
            //cout << "\n Podaj pozycje oraz średnice balonika nr: " << j + 1 << endl;
            getline(cin >> ws, input);

            split(input);
            r[j] = args[2];
            x = args[0];
            y = args[1];
            pozycja_balonika[j] = { x, y };
        }



        if (kierunek_rzutu[0] != 0) {

            for (int j = 0; j < n; j++) {

                if (kierunek_rzutu[0] * pozycja_balonika[j][0] > 0) {
                    if (odleglosc(pozycja_balonika[j]) <= r[j]) {
                        iloscTrafien[i]++;
                    }
                    else if (pozycja_balonika[j][0] == 0) {

                        if (kierunek_rzutu[1] * pozycja_balonika[j][1] > 0) {
                            if (odleglosc(pozycja_balonika[j]) <= r[j]) {
                                iloscTrafien[i]++;
                            }
                        }

                    }
                }

            }
        }
        else {
            for (int j = 0; j < n; j++) {

                if (pozycja_balonika[j][1] * kierunek_rzutu[1] > 0) {
                    if (abs(pozycja_balonika[j][0]) <= r[j]) {
                        iloscTrafien[i]++;
                    }
                }
            }
        }



    }
    for (int i = 0; i < loops; i++) {
        cout << iloscTrafien[i] << endl;
    }
}

float tor_lotu(float x) {
    return m * x;
}

float odleglosc(vector<float> pozycja_balonika) {
    if (m != 0) {
        c = (pozycja_balonika[0] + m * pozycja_balonika[1]) / m; // c = (x + my) / m

        float tempX = (c * m) / (m * m + 1);
        float tempY = tor_lotu(tempX);

        vector<float> location = { tempX, tempY };

        tempX = location[0] - pozycja_balonika[0];
        tempY = location[1] - pozycja_balonika[1];

        return sqrt((tempX * tempX) + (tempY * tempY));

    }
    else {
        return pozycja_balonika[1];
    }

}

void split(string text) {

    args.clear();
    string current_number;
    for (char c : text) {
        if (c == ' ') {
            args.push_back(stoi(current_number));
            current_number.clear();
        }
        else {

            current_number += c;
        }
    }

    if (!current_number.empty()) {
        args.push_back(stoi(current_number));
    }

}