//
//  utilities.hpp
//  cs 32- proj 1
//
//  Created by Emily Vainberg on 6/22/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#ifndef GLOBALS_H
#define GLOBALS_H


///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the arena
const int MAXCOLS = 40;             // max number of columns in the arena
const int MAXROBOTS = 130;          // max number of robots allowed
const int MAXSHOTLEN = 5;           // max number of steps you can shoot
const int INITIAL_ROBOT_HEALTH = 2;

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
void clearScreen();


#endif
