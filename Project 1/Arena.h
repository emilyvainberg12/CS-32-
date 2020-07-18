//
//  Arena.hpp
//  cs 32- proj 1
//
//  Created by Emily Vainberg on 6/22/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#ifndef ARENA_H
#define ARENA_H

#include <iostream>
#include <string>
#include "globals.h"
#include "Previous.h"

class Robot;
class Player;

class Arena
{
  public:
        // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    void    display(std::string msg) const;
    Previous& thePrevious(); // notice that it returns a reference to a Previous object.
    
        // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    void   damageRobotAt(int r, int c);
    bool   moveRobots();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    int     m_nRobots;
    Previous ret_previous;
    
};

#endif
