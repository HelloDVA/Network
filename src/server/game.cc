#include "game.h"

const int Game::directions_[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};

Game::Game() {
}

bool Game::MakeMove(int x, int y, int player) {
    board_[x][y] = player; 
    if (CheckWin(x, y, player)) 
        return true;
    else 
        return false;
}

bool Game::CheckWin(int x, int y, int player) {
	for(int i = 0; i < 4; i ++){
		int count = 1;

		int dx = directions_[i][0];
		int dy = directions_[i][1];

		for(int j = 1; j < 5; j ++){
			int new_x = x + dx * j;
			int new_y = y + dy * j;

			if(new_x >= 0 && new_x < 15 && new_y >= 0 && new_y < 15 && board_[new_x][new_y] == player)
				count ++;
			else 
				break;
		}

		for(int j = 1; j < 5; j ++){
			int new_x = x - dx * j;
			int new_y = y - dy * j;

			if(new_x >= 0 && new_x < 15 && new_y >= 0 && new_y < 15 && board_[new_x][new_y] == player)
				count ++;
			else 
				break;
		}

		if(count >= 5)
			return false;
	}
	return true;

}
