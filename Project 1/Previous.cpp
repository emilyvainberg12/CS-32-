//
//  Previous.cpp
//  cs 32- proj 1
//
//  Created by Emily Vainberg on 6/22/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#include "Previous.h"
#include "Arena.h"

#include <string>

using namespace std;

Previous::Previous(int nRows,int nColumns) { 
    m_rows = nRows; //makes a grid for the previous moves the same dimensions as the current arena
    m_cols = nColumns;

    for (int r= 0; r <= m_rows; r++){ // basic syntax for creating a grid with m_rows and m_cols
        for (int c=0; c<= m_cols; c++){
            m_prevarena[r-1][c-1] = 0; // make sure that every spot in the grid is initilaized at 0 so you can add one when drop a crumb is called
        }
    }
}

bool Previous::dropACrumb(int r, int c)
{
    p_rows = r; //p_rows is current position of the player
    p_cols = c;
    
    if ((p_rows < 1) || p_rows > m_rows || p_cols < 1 || p_cols > m_cols) // makes sure the the player is in bounds of the grid
        return false; // if not in bounds return false
    
    m_prevarena[p_rows-1][p_cols-1] += 1; // every time drop a crumb is called, the number at the grid is increased by one
    return true; // returns true if a crumb is dropped
}

void Previous::showPreviousMoves() const
{
    string occurances = ".ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // the index of the string correlates to the number of drumbs a spot has (ex. if there are 5 crumbs then occurances[5] = E
    
    clearScreen(); // clear the screen before printing the new previous grid

    for (int r= 0; r< m_rows; r++){
        for (int c=0; c< m_cols; c++){

            if ((m_prevarena[r][c]) == 0){ // if there are no cumbs, put an . in the grid
                cout << ".";
            }
            else if (m_prevarena[r][c] >= 26){ // if there are 26 crumbs or move, grid has char Z
                cout << 'Z';
           }
           else
               cout << (occurances[m_prevarena[r][c]]); // since the string has the correct letter for each number of crumbs, called m_prevarena[r][c] will generate the number of crumbs at that point in the grid, and the stirng occurances will print the corresponding letter
        }
        cout << endl;
    }
     cout << endl;
}


