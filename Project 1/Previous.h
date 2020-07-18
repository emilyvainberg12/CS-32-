//
//  Previous.hpp
//  cs 32- proj 1
//
//  Created by Emily Vainberg on 6/22/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#ifndef PREVIOUS_H
#define PREVIOUS_H

#include "globals.h"


class Arena;

 class Previous
     {
     public:
         Previous(int nRows, int nCols);
         bool dropACrumb(int r, int c);
         void showPreviousMoves() const;
     private:
         int m_rows; 
         int m_cols;
         int p_rows;
         int p_cols;
         int m_prevarena[MAXROWS][MAXCOLS];
};
#endif 
