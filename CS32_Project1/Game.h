//
//  Game.h
//  CS32_Project_1
//
//  Created by Tom Slavonia on 1/11/23.
//


#ifndef Game_h
#define Game_h



#include <string>
#include <iostream>

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif /* Game_h */
