#include "StudentWorld.h"
#include "GameWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


void StudentWorld::DigEarth(int x, int y){
    
    // make sure not to dig if its already been dug
    if (earthArray[x][y]->isVisible()== false)
        return;
    
    // set a 4x4 to not visible
    for (int i=x; i<x+4; i++){
         for (int j=y; j<y+4; j++){
             earthArray[i][j]->setVisible(false);
         }
    }
}

int StudentWorld::move() {

  //  decLives();
    
    m_tManPtr->doSomething();
    
    
//    for (vector<GraphObject*>::iterator itr = m_objectPtrs.begin(); itr != m_objectPtrs.end(); itr++){
//        (*itr)->doSomething();
//    }
    return GWSTATUS_CONTINUE_GAME;
}


int StudentWorld::init(){
    
//Construct a new oil field filled with Earth, Barrels of oil, Boulders, Gold Nuggets, etc.
    for (int i=0; i < 64; i++){
        for (int j=0; j< 60; j++){
            earthArray[i][j] = new Earth(this,i,j);
        }
    }
    
    for(int i = 30; i <= 33; i++){
        for(int j = 4; j <= 59; j++){
            earthArray[i][j]->setVisible(false);
        }
    }

    m_tManPtr = new TunnelMan(this, 10);   // Allocate and insert a valid TunnelMan object into the gameworld at the proper location
   
    return GWSTATUS_CONTINUE_GAME;
    //Initialize the data structures used to keep track of your game’s virtual world
    
}

void StudentWorld::cleanUp(){
}

