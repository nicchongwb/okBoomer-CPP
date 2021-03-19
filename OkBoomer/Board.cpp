#include "Board.h"
#include <iostream>

/* Board class. this is where board information and control is handled
* Header file is Board.h
*/

Board* Board::s_Instance = nullptr;

bool Board::initBoard()
{
    // std::fill(board[value], board[value] + x(col) * y(row), value);
    std::fill(m_board[0], m_board[0] + 10 * 10, 0);
    m_board[0][0] = 1;
    m_board[9][9] = 2;
    return true;
}

bool Board::canPlayerMove(int m_pid, int prevX, int prevY, int newX, int newY)
{    
    prevX /= 64;
    prevY /= 64;
    newX /= 64;
    newY /= 64;
    
    // get other player id
    m_pid += 1;
    int m_otherPID = -1;
    if (m_pid == 1) {
        m_otherPID = 2;
    }
    else if (m_pid == 2) {
        m_otherPID = 1;
    }

    //std::printf("PID: %d\tPrevX: %d\tPrevY: %d\tnewX: %d\tnewY: %d\n", m_pid, prevX, prevY, newX, newY);

    if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10) { // check if out of board
        // if its not another player
        if (m_board[newX][newY] != m_otherPID) {
            return true;
        }
        else { return false; }
    }
    else { return false; }
}

bool Board::updateBoard(int m_pid, int prevX, int prevY, int newX, int newY)
{
    //std::printf("PID: %d\tPrevX: %d\tPrevY: %d\tnewX: %d\tnewY: %d\n", m_pid, prevX, prevY, newX, newY);
    m_board[prevX/64][prevY/64] = 0;
    m_board[newX/64][newY/64] = m_pid+1;
    return true;
}

// Print out board
bool Board::consoleBoard()
{

    std::cout << "     X  X  X  X  X  X  X  X  X  X"<< std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "Y [ ";
        for (int j = 0; j < 10; j++) {
            std::cout << " " << m_board[j][i] << " ";
        }
        std::cout << " ]\n";
    }
    return true;
}