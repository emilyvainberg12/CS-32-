//
//  Game.hpp
//  cs 32- proj 1
//
//  Created by Emily Vainberg on 6/22/20.
//  Copyright © 2020 Emily Vainberg. All rights reserved.
//

#ifndef GAME_H
#define GAME_H

class Arena;

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

        // Mutators
    void play();

  private:
    Arena* m_arena;
};

#endif
