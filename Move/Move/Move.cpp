using namespace std;

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

const int NUM_POCKETS = 6;


struct Vector2D
{
    double x, y;
};

struct Ball
{
    Vector2D position;
    Vector2D velocity;
};

struct Pocket
{
    Vector2D position;
};

//----------------------------------------------------
//                  Zmienne
//----------------------------------------------------

Ball ball;
Pocket pockets[NUM_POCKETS];

string pocketNames[6] = {"DL", "GL", "DP", "GP","DS","GS"};

vector<Vector2D> allPoints;
double tableWidth, tableHeight;
int pocketID;
int testSize = 1;
vector<vector<int>> args;

Vector2D findColision() {

    Vector2D returnValue;

    if (ball.velocity.x != 0) {

        if (ball.velocity.x > 0) {

            double tempT = (tableWidth - ball.position.x) / ball.velocity.x;
            double tempY = ball.position.y + tempT * ball.velocity.y;

            if (tempY > tableHeight) {
                tempT = (tableHeight - ball.position.y) / ball.velocity.y;
                tempY = ball.position.x + tempT * ball.velocity.x;
                returnValue = { tempY, tableHeight };
                ball.velocity.y = -ball.velocity.y;

            }

            else if (tempY < 0) {
                tempT = (0 - ball.position.y) / ball.velocity.y;
                tempY = ball.position.x + tempT * ball.velocity.x;
                returnValue = { tempY, 0 };
                ball.velocity.y= -ball.velocity.y;
            }

            else{
                
                returnValue = { tableWidth, tempY };
                ball.velocity.x = -ball.velocity.x;
                
            }

        }
        else{

            // x = x0 + t * xv 
            double tempT = (0 - ball.position.x) / ball.velocity.x;
            double tempY = ball.position.y + tempT * ball.velocity.y;
            if (tempY < 0 ) {
                tempT = (0 - ball.position.y) / ball.velocity.y;
                tempY = ball.position.x + tempT * ball.velocity.x;
                returnValue = { tempY, 0 };
                ball.velocity.y = -ball.velocity.y;
               
            }
            else if (tempY > tableHeight) {
                tempT = (tableHeight - ball.position.y) / ball.velocity.y;
                tempY = ball.position.x + tempT * ball.velocity.x;
                returnValue = { tempY, tableHeight };
                ball.velocity.y = -ball.velocity.y;
            }
            else {

                returnValue = { 0, tempY };
                ball.velocity.x = -ball.velocity.x;
            }
        }
        ball.position = {returnValue.x, returnValue.y};


        return returnValue;

    }
    else {
        if (ball.velocity.y > 0) {
            returnValue = { ball.position.x, tableHeight };
            
        }
        else {
            returnValue = { ball.position.x, 0 };
        }
        return returnValue;
    }
}

bool lookForHole(Vector2D input) {
    
    for (int i = 0; i < 6; i++) {
        if (abs(input.x - pockets[i].position.x) <= 1e-7 && abs(input.y - pockets[i].position.y) <= 1e-7) {
            pocketID = i;
            return true;
        }
    }
    return false;

}

void split(string text, int id) {

    vector<int> tempArgs;

    string current_number;
    for (char c : text) {
        if (c == ' ') {
            tempArgs.push_back(stoi(current_number));
            current_number.clear();
        }
        else {

            current_number += c;
        }
    }

    if (!current_number.empty()) {
        tempArgs.push_back(stoi(current_number));
    }
    
    args.push_back(tempArgs);
}


int main()
{
    cin >> testSize;
    cin.ignore();
    for (int i = 0; i < testSize; i++) {

        // Wczytanie wymiarów stołu bilardowego
        string input;
        getline(cin,input);

        split(input, i);
    }
    for (int i = 0; i < testSize; i++) {
        allPoints.clear();
        tableWidth = args[i][0];
        tableHeight = args[i][1];

        ball.position = { (double)args[i][2],(double)args[i][3] };
        ball.velocity = { (double)args[i][4],(double)args[i][5] };

        // Stworzenie tablicy zawierającej pozycje łuz

        pockets[0].position = { 0, 0 };
        pockets[1].position = { 0, tableHeight };
        pockets[2].position = { tableWidth, 0 };
        pockets[3].position = { tableWidth, tableHeight };
        pockets[4].position = { tableWidth / 2, 0 };
        pockets[5].position = { tableWidth / 2, tableHeight };

        // Przyjmujemy, że kula nie wpadnie do żadnej łuzy
        int pocketIndex = -1;
        int numBounces = 0;

        // Obliczamy, czy kula wpadnie do łuzy i ile razy odbiła się od band
        Vector2D tempXY;
        bool execute = true;
        if (ball.velocity.x != 0 || ball.velocity.y != 0) {

            while (execute)
            {
                tempXY = findColision();

                for (Vector2D p : allPoints) {
                    if (p.x == tempXY.x && p.y == tempXY.y) {
                        cout << "NIE" << endl;
                        execute = false;
                        break;
                    }
                }
                if (!execute) {
                    break;
                }

                allPoints.push_back(tempXY);

                if (lookForHole(tempXY)) {
                    cout << pocketNames[pocketID] << " " << numBounces << endl;
                    break;
                }

                numBounces++;
            }
        }

        else
        {
            cout << "NIE" << endl;
        }

    }
        
    
        
    

    

}