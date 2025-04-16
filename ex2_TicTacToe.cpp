#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

//TicTacToe

#define BOARD_SIZE 3
char BOARD[BOARD_SIZE][BOARD_SIZE];
const char PlayerOneSign = 'X';
const char PlayerTwoSign = 'O';
char CurrentPlayerSign;
bool IsDraw = false;
void Initialize() {
    //Deklaracja planszy do gry 3x3 o indeksach {0;1;2}
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            BOARD[i][j] = '_';
        }
    }

}

void Print() {
    //Wyswietlanie planszy do gry
    cout << ' ';
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i;
    }
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i;
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << BOARD[i][j];
        }
        cout << endl;
    }
}

void GetPlayerInput(char playerSign) {
    //Wczytywanie koordynatow punktu przez gracza
    bool inputOk = false;
    while (!inputOk) {
        int x, y;
        cout << "Podaj wspolrzedna x: ";
        cin >> x;
        cout << "Podaj wspolrzedna y: ";
        cin >> y;
        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
            if (BOARD[y][x] == '_') {
                BOARD[y][x] = playerSign;
                inputOk = true;
            }
            else {
                cout << "Bledne koordynaty, wpisz ponownie" << endl;
            }
        }
        else {
            cout << "Bledne koordynaty, wpisz ponownie" << endl;
        }
    }
}

void ChangePlayer() {
    //Zmiana znaku dla wartosci CurrentPlayerSign
    if (CurrentPlayerSign == PlayerOneSign) {
        CurrentPlayerSign = PlayerTwoSign;
    }
    else {
        CurrentPlayerSign = PlayerOneSign;
    }
}

bool CheckGameState() {
    //Sprawdzanie czy jeden z graczy nie wygral
    for (int i = 0; i < BOARD_SIZE; i++) {
        bool result = true;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (BOARD[i][j] != CurrentPlayerSign) {
                result = false;
            }
        }
        if (result) return true;
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        bool result = true;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (BOARD[j][i] != CurrentPlayerSign) {
                result = false;
            }
        }
        if (result) return true;
    }
    if ((BOARD[0][0] == CurrentPlayerSign) && (BOARD[1][1] == CurrentPlayerSign) && (BOARD[2][2] == CurrentPlayerSign)) {
        return true;
    }
    if ((BOARD[0][2] == CurrentPlayerSign) && (BOARD[1][1] == CurrentPlayerSign) && (BOARD[2][0] == CurrentPlayerSign)) {
        return true;
    }
    bool full = true;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (BOARD[i][j] == '_') {
                full = false;
            }
        }
    }
    if (full) {
        IsDraw = true;
        return true;
    }

    ChangePlayer();
    return false;
}

//SEKCJA AI
bool IsAIwin(char playerSign) {
    //Sprawdzenie, czy komputer moze wygrac w kolejnym ruchu.
    for (int i = 0; i < BOARD_SIZE; i++) {
        int temp1 = 0, temp2 = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (BOARD[i][j] == playerSign) {
                temp1 += 1;
            }
            else if (BOARD[i][j] == '_') {
                temp2 += 1;
            }
        }
        if (temp1 == 2 && temp2 == 1) {
            for (int k = 0; k < BOARD_SIZE; k++) {
                BOARD[i][k] = playerSign;
            }
            return true;
        }
    }
    ////////////////////////////////////////////////////////////////
    for (int i = 0; i < BOARD_SIZE; i++) {
        int temp1 = 0, temp2 = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (BOARD[j][i] == playerSign) {
                temp1 += 1;
            }
            else if (BOARD[j][i] == '_') {
                temp2 += 1;
            }
        }
        if (temp1 == 2 && temp2 == 1) {
            for (int k = 0; k < BOARD_SIZE; k++) {
                BOARD[k][i] = playerSign;
            }
            return true;
        }
    }
    ////////////////////////////////////////////////////////////////
    int temp1 = 0, temp2 = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (BOARD[i][i] == playerSign) {
            temp1 += 1;
        }
        else if (BOARD[i][i] == '_') {
            temp2 += 1;
        }
    }
    if (temp1 == 2 && temp2 == 1) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            BOARD[i][i] = playerSign;
        }
        return true;
    }
    ////////////////////////////////////////////////////////////////
    temp1 = 0, temp2 = 0; int var = 2;
    for (int i = 0; i < BOARD_SIZE; i++, var--) {
        if (BOARD[i][var] == playerSign) {
            temp1 += 1;
        }
        else if (BOARD[i][var] == '_') {
            temp2 += 1;
        }
    }
    var = 2;
    if (temp1 == 2 && temp2 == 1) {
        for (int i = 0; i < BOARD_SIZE; i++, var--) {
            BOARD[i][var] = playerSign;
        }
        return true;
    }
    return false;
}

bool CanAIblock(char playerSign) {
    //Sprawdzenie, czy przeciwnik nie wygra w następnym ruchu. Jeśli istnieje taka możliwość, komputer blokuje potencjalne zwycięskie pole.
    char SecondPlayerSign;
    if (playerSign == 'X') {
        SecondPlayerSign = 'O';
    }
    else {
        SecondPlayerSign = 'X';
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        int temp1 = 0, temp2 = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (BOARD[i][j] == SecondPlayerSign) {
                temp1 += 1;
            }
            else if (BOARD[i][j] == '_') {
                temp2 += 1;
            }
        }
        if (temp1 == 2 && temp2 == 1) {
            for (int k = 0; k < BOARD_SIZE; k++) {
                if (BOARD[i][k] == '_') {
                    BOARD[i][k] = playerSign;
                }
            }
            return true;
        }
    }
    ///////////////////////////////////////////////////////
    for (int i = 0; i < BOARD_SIZE; i++) {
        int temp1 = 0, temp2 = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (BOARD[j][i] == SecondPlayerSign) {
                temp1 += 1;
            }
            else if (BOARD[i][j] == '_') {
                temp2 += 1;
            }
        }
        if (temp1 == 2 && temp2 == 1) {
            for (int k = 0; k < BOARD_SIZE; k++) {
                if (BOARD[k][i] == '_') {
                    BOARD[k][i] = playerSign;
                }
            }
            return true;
        }
    }
    ///////////////////////////////////////////////////////
    int temp1 = 0, temp2 = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (BOARD[i][i] == SecondPlayerSign) {
            temp1 += 1;
        }
        else if (BOARD[i][i] == '_') {
            temp2 += 1;
        }
    }
    if (temp1 == 2 && temp2 == 1) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (BOARD[i][i] == '_') {
                BOARD[i][i] = playerSign;
            }
        }
        return true;
    }
    ////////////////////////////////////////////////////////////////
    temp1 = 0, temp2 = 0; int var = 2;
    for (int i = 0; i < BOARD_SIZE; i++, var--) {
        if (BOARD[i][var] == SecondPlayerSign) {
            temp1 += 1;
        }
        else if (BOARD[i][var] == '_') {
            temp2 += 1;
        }
    }
    var = 2;
    if (temp1 == 2 && temp2 == 1) {
        for (int i = 0; i < BOARD_SIZE; i++, var--) {
            if (BOARD[i][var] == '_') {
                BOARD[i][var] = playerSign;
            }
        }
        return true;
    }
    return false;
}

void AIturn(char playerSign) {
    //Losowy ruch wykonany przez komputer.
    srand(time(NULL));
    int randx = 0, randy = 0;
    while (true) {
        randx = rand() % 2;
        randy = rand() % 2;
        if (BOARD[randx][randy] == '_') {
            BOARD[randx][randy] = playerSign;
            break;
        }
    }
}

void GetAIinput(char playersign) {
    /*Funkcja pobiera znak komputera.
    Sprawdzane są dwa przypadki: pierwszy – czy komputer jest w stanie wygrać w jednym ruchu, drugi – czy przeciwnik będzie mógł wygrać w kolejnym ruchu.
    Jeśli żaden z tych warunków nie jest spełniony, to komputer stawia znak w losowym wolnym polu.*/
    if (IsAIwin(playersign)) {
        return;
    }
    else if (CanAIblock(playersign)) {
        return;
    }
    else {
        AIturn(playersign);
        return;
    }
}

int main()
{

    //Dodaj remis i to aby mozna bylo wpisac male p/k na start
    //Funkcja główna
    char Opponent;
    int a = true;
    char ans;
    cout << "Gra w kolko i krzyzyk :)" << endl;
    while (a == true) {
        cout << "Chcesz grac z przyjacielem(P) czy z komputerem(K)? ";
        cin >> Opponent; Opponent = toupper(Opponent);
        cout << "Jaki chcesz miec znak jako osoba rozpoczynajaca?(X/O) ";
        cin >> CurrentPlayerSign; CurrentPlayerSign = toupper(CurrentPlayerSign);
        if ((Opponent == 'K' || Opponent == 'P') && (CurrentPlayerSign == 'X' || CurrentPlayerSign == 'O')) {
            if (Opponent == 'K') {
                Initialize();
                bool b = true;
                while (b == true) {
                    while (true) {
                        Print();
                        GetPlayerInput(CurrentPlayerSign);
                        if (CheckGameState()) {
                            break;
                        }
                        GetAIinput(CurrentPlayerSign);
                        if (CheckGameState()) {
                            break;
                        }
                    }
                    if (IsDraw) {
                        Print();
                        cout << "Mamy remis!" << endl;
                    }
                    else {
                        Print();
                        cout << "Brawo, wygral uzytkownik ze znakiem:" << CurrentPlayerSign << endl;
                    }
                    b = false;
                }
            }
            else if (Opponent == 'P') {
                Initialize();
                bool c = true;
                while (c == true) {
                    while (true) {
                        Print();
                        GetPlayerInput(CurrentPlayerSign);
                        if (CheckGameState()) {
                            break;
                        }
                    }
                    if (IsDraw) {
                        Print();
                        cout << "Mamy remis!" << endl;
                    }
                    else {
                        Print();
                        cout << "Brawo, wygral uzytkownik ze znakiem:" << CurrentPlayerSign << endl;
                    }
                    c = false;
                }
            }
            cout << "Czy chcesz zagrac ponownie?(T/N)";
            cin >> ans;
            if (ans == 'N') {
                a = false;
            }
        }
        else {
            cout << "Blad, wprowadz wartosci ponownie" << endl;
        }
    }
    return 0;
}