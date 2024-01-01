//
//  History.cpp
//  CS32_Project_1
//
//  Created by Tom Slavonia on 1/11/23.
//

#include "History.h"
#include "Arena.h"
#include "globals.h"
#include <iostream>

History::History(int nRows, int nCols) {
    
    m_rows = nRows;
    m_cols = nCols;
    
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            history_mat[r][c] = 0;
        }
    }
}

bool History::record(int r, int c) {
    
    if (r > m_rows || c > m_cols || r < 1 || c < 1) {
        return(false);
    }
    
    history_mat[r - 1][c - 1] = history_mat[r - 1][c - 1] + 1;
    return true;
}

void History::display() const {
    
    clearScreen();
    
    char history_mat_display[MAXROWS][MAXCOLS];
    
    
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            
            if (history_mat[i][j] == 0) {
                history_mat_display[i][j] = '.';
            }
            
            switch (history_mat[i][j]) {
                case 1:
                    history_mat_display[i][j] = 'A';
                    break;
                case 2:
                    history_mat_display[i][j] = 'B';
                    break;
                case 3:
                    history_mat_display[i][j] = 'C';
                    break;
                case 4:
                    history_mat_display[i][j] = 'D';
                    break;
                case 5:
                    history_mat_display[i][j] = 'E';
                    break;
                case 6:
                    history_mat_display[i][j] = 'F';
                    break;
                case 7:
                    history_mat_display[i][j] = 'G';
                    break;
                case 8:
                    history_mat_display[i][j] = 'H';
                    break;
                case 9:
                    history_mat_display[i][j] = 'I';
                    break;
                case 10:
                    history_mat_display[i][j] = 'J';
                    break;
                case 11:
                    history_mat_display[i][j] = 'K';
                    break;
                case 12:
                    history_mat_display[i][j] = 'L';
                    break;
                case 13:
                    history_mat_display[i][j] = 'M';
                    break;
                case 14:
                    history_mat_display[i][j] = 'N';
                    break;
                case 15:
                    history_mat_display[i][j] = 'O';
                    break;
                case 16:
                    history_mat_display[i][j] = 'P';
                    break;
                case 17:
                    history_mat_display[i][j] = 'Q';
                    break;
                case 18:
                    history_mat_display[i][j] = 'R';
                    break;
                case 19:
                    history_mat_display[i][j] = 'S';
                    break;
                case 20:
                    history_mat_display[i][j] = 'T';
                    break;
                case 21:
                    history_mat_display[i][j] = 'U';
                    break;
                case 22:
                    history_mat_display[i][j] = 'V';
                    break;
                case 23:
                    history_mat_display[i][j] = 'W';
                    break;
                case 24:
                    history_mat_display[i][j] = 'X';
                    break;
                case 25:
                    history_mat_display[i][j] = 'Y';
                    break;
                case 26:
                    history_mat_display[i][j] = 'Z';
                    break;
            }
            if (history_mat[i][j] > 26) {
                history_mat_display[i][j] = 'Z';
            }
        }
    }
    
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            std::cout << history_mat_display[i][j];
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
}
