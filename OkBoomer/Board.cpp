#include "Board.h"
#include "Game.h"
#include <iostream>

/* Board class. this is where board information and control is handled
* Header file is Board.h
*/

/* 2D array Board TID usage:
    0 = empty, no entity occupying
    1 = player1 occupying
    2 = player2 occupying
    3 = bomb (planted) occupying
    4 = bomb (collectable) occupying
    5 = bomb (planted) + player 1 occupying (bomb is planted by p1)
    6 = bomb (planted) + player 2 occupying (bomb is planted by p2)
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
    // Offset based on tile pixel size = 64
    prevX /= 64;
    prevY /= 64;
    newX /= 64;
    newY /= 64;
    
    // get other player id
    m_pid += 1; // + 1 because 0 on the array board is 'empty space'. player id inside player class starts from 0.
    
    int m_nextTID = m_board[newX][newY];
    //std::printf("PID: %d\tPrevX: %d\tPrevY: %d\tnewX: %d\tnewY: %d\n", m_pid, prevX, prevY, newX, newY);

    if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10) { // check if out of board
        // if its not another player OR bomb + planted player
        //std::cout << m_otherPID << std::endl;
        switch (m_nextTID) {
        case 1:
        case 2:
        case 5:
        case 6:
            return false;
        default:
            return true;
        }
    }
    else { return false; }
}

bool Board::canPlayerPlant(int m_pid, int prevX, int prevY)
{
    prevX /= 64;
    prevY /= 64;
    m_pid += 1;
    
    int currTID = m_board[prevX][prevY];

    if (m_pid == 1 && currTID != 5) {
        return true;
    }
    else if (m_pid == 2 && currTID != 6) {
        return true;
    }

    return false;
}

bool Board::updateBoardMove(int m_pid, int prevX, int prevY, int newX, int newY)
{
    // Offset based on tile pixel size = 64
    prevX /= 64;
    prevY /= 64;
    newX /= 64;
    newY /= 64;

    // Temporarily Offset m_pid so that player 1's pid = 1 & player 2's pid = 2
    m_pid += 1;

    std::printf("PID: %d\tPrevX: %d\tPrevY: %d\tnewX: %d\tnewY: %d\n", m_pid, prevX, prevY, newX, newY);

    int tidPrev = m_board[prevX][prevY];
    int tidNew = m_board[newX][newY];

    // Player X Move and planted bomb prior
    if (tidPrev == 5 || tidPrev == 6) {
        m_board[prevX][prevY] = 3; 
        m_board[newX][newY] = m_pid;
        
    }
    // ELSE Player X Move without planting bomb prior
    else {
        if (tidNew == 0) {
            m_board[prevX][prevY] = 0;
            m_board[newX][newY] = m_pid;
        }
        else if (tidNew == 3) {
            m_board[prevX][prevY] = 0;
            m_board[newX][newY] = m_pid;
            // Update respective player's health
            Game::GetInstance()->BombPlayer(m_pid);
        }
        else if (tidNew == 4) {
            m_board[prevX][prevY] = 0;
            m_board[newX][newY] = m_pid;
            // Update respective player's bombCollectable pouch
            Game::GetInstance()->CollectBomb(m_pid);
        }

    }  

    return true;
}

bool Board::updateBoardPlant(int m_pid, int prevX, int prevY)
{
    // Offset based on tile pixel size = 64
    prevX /= 64;
    prevY /= 64;

    // Temporarily Offset m_pid so that player 1's pid = 1 & player 2's pid = 2
    m_pid += 1;

    int tidPrev = m_board[prevX][prevY];

    // Update respective player's health
    Game::GetInstance()->PlantBomb(m_pid);

    /* m_pid = 5 -> player 1 and bomb planted on tile
        m_pid = 6 -> player 2 and bomb planted on tile
    */
    m_board[prevX][prevY] = m_pid + 3 + 1;

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

// return tile ID of given coordinates x and y
int Board::getTileID(int x, int y) {
    int tid = m_board[x][y];
    return tid;
}

void Board::updateBoardWithItem(int x, int y, int iid) {
    m_board[x][y] = iid;
}