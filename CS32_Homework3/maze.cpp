//
//  maze.cpp
//  Homework3_Maze
//
//  Created by Tom Slavonia on 2/8/23.
//

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
    
    maze[sr][sc] = 'B'; // B for been
    
    if (sr == er && sc == ec) {
        return(true);
    }
    
    if (maze[sr][sc + 1] == '.' && pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) {
        return(true);
    }
    if (maze[sr][sc - 1] == '.' && pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) {
        return(true);
    }
    if (maze[sr + 1][sc] == '.' && pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) {
        return(true);
    }
    if (maze[sr - 1][sc] == '.' && pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) {
        return(true);
    }
    return(false);
}


