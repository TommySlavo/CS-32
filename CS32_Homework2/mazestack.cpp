//
//  mazestack.cpp
//  mazestack
//
//  Created by Tom Slavonia on 2/3/23.
//

#include <stack>
#include <iostream>
#include <string>



class Coord
        {
          public:
            Coord(int r, int c) : m_row(r), m_col(c) {}
            int r() const { return m_row; }
            int c() const { return m_col; }
          private:
            int m_row;
            int m_col;
        };

bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    
    std::stack<Coord> c;
    c.push(Coord(sr, sc));
    bool been[nRows][nCols];
    
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            been[i][j] = false;
        }
    }
    
    been[sr][sc] = true;
   
    
    while (c.empty() == false) {
        Coord index = c.top();
        c.pop();
        if (index.r() == er && index.c() == ec) {
            return(true);
        }
        if (maze[index.r()][index.c() + 1] == '.' && been[index.r()][index.c() + 1] == false) {
            c.push(Coord(index.r(), index.c() + 1));
            been[index.r()][index.c() + 1] = true;
        }
        if (maze[index.r()][index.c() - 1] == '.' && been[index.r()][index.c() - 1] == false) {
            c.push(Coord(index.r(), index.c() - 1));
            been[index.r()][index.c() - 1] = true;
        }
        if (maze[index.r() + 1][index.c()] == '.' && been[index.r() + 1][index.c()] == false) {
            c.push(Coord(index.r() + 1, index.c()));
            been[index.r() + 1][index.c()] = true;
        }
        if (maze[index.r() - 1][index.c()] == '.' && been[index.r() - 1][index.c()] == false) {
            c.push(Coord(index.r() - 1, index.c()));
            been[index.r() - 1][index.c()] = true;
        }
        
    }
    
    return(false);
}

