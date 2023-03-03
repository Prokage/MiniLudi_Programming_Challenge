#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

/*
Player node, contains position and name data as well
as pointers to the following and previous player node. 
*/
struct Player {
    string name;
    int position;
    Player* next;
    Player* prev;
};

/*
Struct for game, constructor function that takes in number
of players and board size and contains functions to intiailize
and play. Initialize sets up the circulur doubly linked list
and play has the game logic.
*/
struct MiniLudi{
	int numPlayers;
	int boardSize;
	int winningPos;
	Player* currentPlayer;
	Player* head;
	Player* tail;
	
	MiniLudi(int num, int size)
	{
		numPlayers = num;
		boardSize = size;
		winningPos = boardSize * boardSize;
		currentPlayer = NULL;
		head = NULL;
		tail = NULL;
	}
	
	void initialize()
	{
		for(int i = 0; i < numPlayers; i++)
		{
			string name; 
			cout<<"Enter name for player " << i+1 << ": ";
			cin>>name;
			Player* player = new Player();
			player->name = name;
			player->position = 0;
			if(head==NULL){  // No players yet
				head=player;
				tail=player;
				head->next = tail;
				head->prev = tail;
				tail->next = head;
				tail->prev = head;
			}
			else  //More than 1 player
			{
				tail->next = player;
				player->prev = tail;
				player->next = head;
				head->prev = player;
				tail = player;
			}
		}
		currentPlayer=head;
	}
	
	void play() {
            srand(time(NULL));
            int diceRoll = rand() % 4 + 1;
            cout << currentPlayer->name << " rolled a " << diceRoll << endl;
            int newPosition = currentPlayer->position + diceRoll;
            if (newPosition > winningPos) {
                cout << currentPlayer->name << " must land exactly on " << winningPos << " to win." << endl;
                currentPlayer = currentPlayer->next;
                return;
            }
            Player* otherPlayer = findPlayer(newPosition);
            if (otherPlayer != NULL && !isSafePosition(otherPlayer)) {
                cout << currentPlayer->name << " cut " << otherPlayer->name << "!" << endl;
                otherPlayer->position = 0;
            }
            currentPlayer->position = newPosition;
            if (currentPlayer->position == winningPos) {
                cout << currentPlayer->name << " wins!" << endl;
                return;
            }
            cout << currentPlayer->name << " moved to position " << currentPlayer->position << endl;
            currentPlayer = currentPlayer->next;
        }
        
	bool isSafePosition(Player* player) {
	    int position = player->position;
	    if (position == 3 || position == 9 || position == 15 || position == 21 ||
	        position == 23 || position == 27 || position == 31 || position == 35) {
	        return true;
	    }
	    return false;
	}
    string getCurrentPlayerName() {
	    return currentPlayer->name;
	}
	
	Player* findPlayer(int position) {
            Player* temp = head;
            do {
                if (temp->position == position) {
                    return temp;
                }
                temp = temp->next;
            } while (temp != head);
            return NULL;
        }
        
    bool isGameOver() {
	    Player* temp = head;
	    do {
	        if (temp->position == winningPos) {
	            return true;
	        }
	        temp = temp->next;
	    } while (temp != head);
	    return false;
	}
	
	void printBoard() {
	    int i, j;
	    int row, col;
	    int board[7][7] = {
	        {9,8,7,6,5,4,3},
	        {10,31,32,33,34,35,2},
	        {11,30,43,44,45,36,1},
	        {12,29,42,47,46,37,0},
	        {13,28,41,40,39,38,0},
	        {14,27,26,25,24,23,22},
	        {15,16,17,18,19,20,21}
	    };
	    for (i = 0; i < 7; i++) {
	        for (j = 0; j < 7; j++) {
	        	cout << setw(3);
	            if (board[i][j] == 0) {
	                cout << "\t";
	            } else if (board[i][j] == 3 || board[i][j] == 9 || board[i][j] == 15 || board[i][j] == 21 ||
	                      board[i][j] == 27 || board[i][j] == 31 || board[i][j] == 35|| board[i][j]== 23) {
	                Player* player = findPlayer(board[i][j]);
	                if (player != NULL) {
	                    cout << player->name << board[i][j] << "*\t";
	                } else {
	                    cout << board[i][j] << "*\t";
	                }
	            } else {
	                Player* player = findPlayer(board[i][j]);
	                if (player != NULL) {
	                    cout << player->name[0] << board[i][j] << "\t";
	                } else {
	                    cout << board[i][j] << "\t";
	                }
	            }
	        }
	        cout << endl;
	    }
	}
	
	
    void reset(){
    	for(int i = 0; i<numPlayers;i++)
    	{
    		currentPlayer->position = 0;
    		currentPlayer = currentPlayer->next;
		}
	}
	
	
};


