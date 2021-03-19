#pragma once

#ifndef BOARD_H
#define BOARD_H


class Board
{
public:
	//Board();
	static Board* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Board();
	}

	// 2D board array method
	bool initBoard(); // initialize 2D board with player 1 in top left, player 2 in bottom right and empty with 0
	bool canPlayerMove(int m_pid, int prevX, int prevY, int newX, int newY); // check if player input is valid
	bool updateBoard(int m_pid, int prevX, int prevY, int newX, int newY); // update the board and also update player health, items etc
	bool consoleBoard();

private:
	Board() {};

	static Board* s_Instance;

	// 2D board array
	int m_board[10][10]; // board array with 10(col = x axis) by 10(row = y axis)
};

#endif // BOARD_H
