/**
 *
 *                              Advanced Programming EEEE-346.600
 *                                 Tic Tac Toe Intelligent Bot
 *
 *                              @uthor: Rashed Alnuman
 *                              @uthor: Komil Mamasaliev
 *
 *                              Language: C++ 17
 *
 *                              Description: X O program that allows for player versus player
 *                              or against a intelligent bot based on minimax algorithm
 *
*/


#include <algorithm> //  std find
#include <iterator>  //  std begin & end
#include <iostream>  //  input & output operations
#include <time.h>    //  C header file for time operations
#include <fstream> 
//#include <cstdio>
//#include <chrono>
//#include <thread>

using namespace std;

struct Move { int row, col; };
// can also be replaced with pair, where bestmove will return a pair



class Game {

public:

	Game() { cout << "Playing Board is set...\n\n"; } // default constructor

	bool isMovesLeft();
	bool winCheck(char chr);
	void displayBoard();
	char element(int i, int j) { return board[i][j]; }

	char board[3][3] =  // creating 2d 3x3 matrix board

	{ { '_', '_', '_' },
	 { '_', '_', '_' },
	 { '_', '_', '_' } };

	/* Matrix Key

	   0{ '0', '1', '2' }
	   1{ '0', '1', '2' }
	   2{ '0', '1', '2' } */
};


Game game;
char player1 = 'X';
char player2 = 'O';



/**
 * displays the board using a nested loop
 */
void Game::displayBoard() {  // can also be done with a mod 3 to determine every row

	for (int i = 0; i < 3; i++) {

		cout << "\n";

		for (int j = 0; j < 3; j++) {

			cout << "  " << game.board[i][j];

		}
	}
}

//gets random row and colum

Move random() {

	Move firstmove;
	//this_thread::sleep_for(chrono::milliseconds(500));
	ifstream infile("location.txt");
	int row, col;
	infile >> row >> col;
	//cout << row << col;
	firstmove.row = row;
	firstmove.col = col;
	return firstmove;
}

/**
 * checks if anymore moves are possible through verifying if
 * '_' exists within the array
 *
 * @return boolean, true if '_' exists, false otherwise
 */
bool Game::isMovesLeft() { //2d array means we use nested loop to access all elements

	for (int i = 0; i < 3; i++) {

		if (find(begin(game.board[i]), end(game.board[i]), '_') != end(game.board[i])) {

			return true;
		}
	}

	return false;
}


/**
 * verifies if the given player won the game by verifying if said player
 * achieved any of the given winning patterns.
 *
 * @param char chr (X O)
 * @return boolean, true if pattern achieved, false if not
 */
bool Game::winCheck(char chr) {

	bool win = false;               //every winning pattern is checked, if someone has anyof these combinations, he wins.

	if (game.board[0][0] == chr && game.board[1][0] == chr && game.board[2][0] == chr) { win = true; }
	else if (game.board[0][1] == chr && game.board[1][1] == chr && game.board[2][1] == chr) { win = true; }
	else if (game.board[0][2] == chr && game.board[1][2] == chr && game.board[2][2] == chr) { win = true; }
	else if (game.board[0][0] == chr && game.board[0][1] == chr && game.board[0][2] == chr) { win = true; }
	else if (game.board[1][0] == chr && game.board[1][1] == chr && game.board[1][2] == chr) { win = true; }
	else if (game.board[2][0] == chr && game.board[2][1] == chr && game.board[2][2] == chr) { win = true; }
	else if (game.board[0][0] == chr && game.board[1][1] == chr && game.board[2][2] == chr) { win = true; }
	else if (game.board[0][2] == chr && game.board[1][1] == chr && game.board[2][0] == chr) { win = true; }

	return win;
}


/**
 * Minimax algorithm, recursive function. internally simulates the entire
 * game to discover the highest scoring move. depth evaluation allows to
 * pick the best of several winning moves based on least number of steps.
 *
 * @param integer depth, must start at 0 by default and incremented each stack call
 * @param boolean isMax, if true, maximizer simulated turn, else, minimizer simulated turn
 * @return integer, either (10 or -10) - depth or best (represents the highest scoring move)
 */
int minimax(int depth, bool isMax) {

	if (game.winCheck(player1)) { return (10 - depth); } // without depth evaluation, put 1 and -1
	else if (game.winCheck(player2)) { return (-10 + depth); } // any number above above 6 works (check)
	else if (game.isMovesLeft() == false) { return 0; }

	// If this maximizer's move
	if (isMax) {

		int best = -1000;

		// Traverse all cells
		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				// Check if cell is empty
				if (game.board[i][j] == '_') {

					// Make the move
					game.board[i][j] = player1;

					// Call minimax recursively and choose
					// the maximum value
					best = max(best, minimax(depth + 1, !isMax));

					// Undo the move
					game.board[i][j] = '_';
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else {

		int best = 1000;

		// Traverse all cells
		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				// Check if cell is empty
				if (game.board[i][j] == '_') {

					// Make the move
					game.board[i][j] = player2;

					// Call minimax recursively and choose
					// the minimum value
					best = min(best, minimax(depth + 1, !isMax));

					// Undo the move
					game.board[i][j] = '_';
				}
			}
		}
		return best;
	}
}


// This will return the best possible move for player1

/**
 * finds the best possible move for the AI. plays a turn internally,
 * then uses minimax to simulate the outcome of that turn. picks the
 * best turn according to the best value returned by minimax.
 *
 * @return Struct representing row and col
 */
Move findBestMove() {

	int bestVal = -1000; //any very low negative value works
	Move bestMove;
	bestMove.row = -1;   // out of board row
	bestMove.col = -1;  // out of board col

	// Traverse all cells, evaluate minimax function for
	// all empty cells. And return the cell with optimal
	// value.
	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			// Check if cell is empty
			if (game.board[i][j] == '_') {

				// Make the move
				game.board[i][j] = player1; // TO MAKE BOT O THEN CHANGE TO PLAYER 2

				// compute evaluation function for this move

				int moveVal = minimax(0, false);

				// Undo the move
				game.board[i][j] = '_';

				// If the value of the current move is
				// more than the best value, then update
				// best
				if (moveVal > bestVal) {

					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	printf("Optimal Move Value : %d\n\n", bestVal);

	return bestMove;
}



/**
 * displays the winner of the game, performs a wincheck on each player
 * and ends the game if a player wins or if no turns are left, thus a draw.
 */
void displayWinner(string contestant1, string contestant2) {

	if (game.winCheck(player1)) {  //check if player1 won (AI)
		cout << " \n\n \t" << contestant1 << " won" << endl;
		exit(0);

	}
	else if (game.winCheck(player2)) {  //check if player2 won (user)
		cout << "\n\n \t" << contestant2 << " won" << endl;
		exit(0);
	}

	if (!game.isMovesLeft()) {  //  If movesLeft returns false, then...

		cout << " \n\n \tIt's a draw... \n";
		exit(0);
	}



}

/**
 * emulates player verses computer gameplay. plays turn by turn with
 * the computer until a win or a draw occurs. immune to double placement
 * on the board using conditional flow.
 */
void pvc() {

	cout << "\n\nWelcome to Tic Tac Toe \n Pick your spot by choosing the row and column mapped below, you are O and pc is X \n \n";
	cout << "      c0  c1  c2 \n r0 | _   _   _  | \n r1 | _   _   _  | \n r2 | _   _   _  | \n \n \n";

	Move first = random();
	int turn = 0;


	while (true) {

		int row;
		int col;
		int mov1 = 0;
		Move bestMove;

		if (turn == 0) { bestMove = random(); turn++;}
		else { bestMove = findBestMove();}
	

		//Move bestMove = findBestMove();  //creating the Move struct

		game.board[bestMove.row][bestMove.col] = 'X'; //position on the board as X

		cout << "\n \n";
		game.displayBoard();  //showing the board after every turn
		cout << "\n \n";
		displayWinner("Computer", "You"); //check if anyone won after each turn



		while (true) {

			cout << "Enter the row : "; // prompt user for row
			cin >> row;
			cout << "\nEnter the column : "; // prompt user for column
			cin >> col;

			if (game.board[row][col] != '_') { // if its not empty, make user pick another spot
				cout << "\n the spot is allready taken, pick another... \n \n";

			}
			else { break; }

		}//end while

		game.board[row][col] = 'O'; //placing the users O on the board

		cout << "\n \n";
		game.displayBoard();
		cout << "\n \n";
		displayWinner("Computer", "You"); // check if if X or O won

	}

}


void pvp() {

	cout << "Welcome to Tic Tac Toe \n Pick your spot by choosing the row and column mapped below, you are O and pc is X \n \n";
	cout << "      c0  c1  c2 \n r0 | _   _   _  | \n r1 | _   _   _  | \n r2 | _   _   _  | \n \n \n";

	while (true) {

		int row;
		int col;

		while (true) {

			cout << "\nPlayer1 - Enter row: ";
			cin >> row;
			cout << "\nPlayer1 - Enter column: ";
			cin >> col;

			if (game.board[row][col] != '_') {
				cout << "\n the spot is allready taken, pick another... \n \n";

			}
			else {

				game.board[row][col] = player1;
				break;

			}
		}

		cout << "\n \n";
		game.displayBoard();
		cout << "\n \n";
		displayWinner("Player One", "Player Two"); // check if a player has won

		while (true) { // player 2 game loop

			cout << "\nPlayer2 - Enter row: ";
			cin >> row;
			cout << "\nPlayer2 - Enter column: ";
			cin >> col;

			if (game.board[row][col] != '_') {
				cout << "\n the spot is allready taken, pick another... \n \n";

			}
			else {

				game.board[row][col] = player2;
				break;

			}
		}

		cout << "\n \n";
		game.displayBoard();
		cout << "\n \n";
		displayWinner("Player One", "Player Two"); // check if a player has won



	}

}

/**
 * Main function, contains main menu, prompts user to enter 1
 * for player versus player or 2 for player versus computer
 *
 * @param argc - Non-negative value representing the number of arguments passed
 * @param argv - Pointer to the first element of an array of argc + 1 pointers
 * @return int 0
 */
int main() {

	system("randomiser.exe");
	int option;


	while (true) {

		cout << "Enter 1 to play for PVC, 2 for PVP: "; // prompt user for choice
		cin >> option;

		if (option == 1) { pvc(); } // if 1 then player vs computer

		else if (option == 2) { pvp(); }  // if 2 then player vs player

		else { cout << "Invalid input...\n\n"; } // otherwise, invalid input

	}

	return 0;
}