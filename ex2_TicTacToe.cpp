#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

// TicTacToe

#define BOARD_SIZE 3
char BOARD[BOARD_SIZE][BOARD_SIZE];
const char PlayerOneSign = 'X';
const char PlayerTwoSign = 'O';
char CurrentPlayerSign;
bool IsDraw = false;

void Initialize() {
	// Initialize the game board with empty spaces
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            BOARD[i][j] = '_';
        }
    }
	IsDraw = false;
}

void Print() {
    // Print the game board
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
	// Get input from the player and update the board
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
	// Switch the current player
    if (CurrentPlayerSign == PlayerOneSign) {
        CurrentPlayerSign = PlayerTwoSign;
    }
    else {
        CurrentPlayerSign = PlayerOneSign;
    }
}

bool CheckGameState() {
	// Check if the game is over
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

/* ======================== AI section ======================== */

bool IsAIwin(char playerSign) {
	// Check if the AI can win in the next move
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
	// Check if the AI can block the opponent from winning
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

    for (int i = 0; i < BOARD_SIZE; i++) {
        int temp1 = 0, temp2 = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (BOARD[j][i] == SecondPlayerSign) {
                temp1 += 1;
            }
            else if (BOARD[j][i] == '_') {
                temp2 += 1;
            }
        }
        if (temp1 == 2 && temp2 == 1) {
            for (int k = 0; k < BOARD_SIZE; k++) {
                if (BOARD[k][i] == '_') {
                    BOARD[k][i] = playerSign;
                    break;;
                }
            }
            return true;
        }
    }
    
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
	// AI makes a random move
    int randx = 0, randy = 0;
    while (true) {
        randx = rand() % BOARD_SIZE;
        randy = rand() % BOARD_SIZE;
        if (BOARD[randx][randy] == '_') {
            BOARD[randx][randy] = playerSign;
            break;
        }
    }
}

void GetAIinput(char playersign) {
	// AI decides its move
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
	// Main function to run the game
    srand(time(NULL));
    char Opponent;
    int a = true;
    char ans;
    cout << "Welcome to my Tic Tac Toe game!" << endl;
    while (a == true) {
        while (true) {
            cout << "Do you want to play with your friend (F) or with a computer (C)? ";
            cin >> Opponent; Opponent = toupper(Opponent);
			if (Opponent == 'C' || Opponent == 'F') {
				break;
			}
			else {
				cout << "Invalid input. Please try again." << endl;
			}
        }

        while (true) {
            cout << "Which symbol do you want to play as? (X/O): ";
            cin >> CurrentPlayerSign; CurrentPlayerSign = toupper(CurrentPlayerSign);
			if (CurrentPlayerSign == 'X' || CurrentPlayerSign == 'O') {
				break;
            }
			else {
				cout << "Invalid input. Please try again." << endl;
            }
        }

    	if (Opponent == 'C') {
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
    				cout << "It's a draw!\n" << endl;
    			}
    			else {
    				Print();
    				cout << "Congratulations! Player with symbol " << CurrentPlayerSign << " won." << endl;
    			}
    			b = false;
    		}
    	}

    	else if (Opponent == 'F') {
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
    				cout << "It's a draw!" << endl;
    			}
    			else {
    				Print();
    				cout << "Congratulations! Player with symbol " << CurrentPlayerSign << " won." << endl;
    			}
    			c = false;
    		}
        }

        while (true) {
			cout << "Do you want to play again? (Y/N): ";
			cin >> ans; ans = toupper(ans);
            if (ans == 'Y') {
	            break;
            }
			else if (ans == 'N') {
				a = false;
				break;
			}
            else {
				cout << "Invalid input. Please try again." << endl;
            }
        }
    }
    return 0;
}