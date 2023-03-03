#include "MiniLudi.h"
using namespace std;
int main() {
	int playAgain = 1;
	do{
    MiniLudi game(4, 7);
    game.initialize();
    bool gameOver = false;
    while (!gameOver) {
    	playAgain = 0;
        game.printBoard();
        cout << endl;
        cout << "It's " << game.getCurrentPlayerName() << "'s turn. Press Enter to roll the dice..."<<endl;
        cin.get();
        game.play();
        cout << endl;
        gameOver = game.isGameOver();
        if(gameOver){
        	cout<<"Do you want to play again? Type 1 for Yes, anything else for no."<<endl;
		cin >> playAgain;
		}
    } 
	} while(playAgain==1);
   
 return 0;
}

