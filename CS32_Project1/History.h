//
//  History.h
//  CS32_Project_1
//
//  Created by Tom Slavonia on 1/11/23.
//

#ifndef History_h
#define History_h

#include "globals.h"


class History {
    
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int m_rows;
    int m_cols;
    int history_mat[MAXROWS][MAXCOLS];
};

#endif /* History_h */
