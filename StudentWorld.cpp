#include "StudentWorld.h"
#include "GameWorld.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <queue>

using namespace std;

GameWorld* createStudentWorld(string assetDir){return new StudentWorld(assetDir);}

StudentWorld::StudentWorld(std::string assetDir): GameWorld(assetDir){}

StudentWorld::~StudentWorld(){}

int StudentWorld::init(){
    
    // both for inits
    maxPro = (min<int>(15, 2 + getLevel() * 1.5));
    numPro = 0;
    m_tickAddProtestor = 0;

    m_barrels = std::min<int>(2 + getLevel(), 21);
    
    //Construct a full 64x64 oil field
    for (int i=0; i < 64; i++){
        for (int j=0; j< 64; j++){
            earthArray[i][j] = new Earth(this,i,j);
        }
    }
    
    // remove the visibility of the middle line
    for(int i = 30; i <= 33; i++){
        for(int j = 4; j <= 59; j++){
            earthArray[i][j]->setVisible(false);
        }
    }
    
    // remove the visibility of the top 4 rows
    for(int i = 0; i < 64; i++){
        for(int j = 60; j < 64; j++){
            earthArray[i][j]->setVisible(false);
        }
    }

    m_tManPtr = new TunnelMan(this, 10);   // Allocate and insert a valid TunnelMan object into the gameworld at the proper location

    // randomly place oil barrels
    for(int i=0; i < m_barrels; i++){
        int BaX = rand() %61 + 1; // x goes from 0-60 inclusive
        int BaY = rand() % 57 + 1;  //  y goes from 0-56 inclusive
        
        while (BaX >= 26 && BaX <= 33){
            BaX = rand() % 60 + 1;
        }
        
        vector<Actor*>::iterator itr;
        itr = m_ActorsPtrs.begin();
        while (itr != m_ActorsPtrs.end()){
            if (NearActor(BaX, BaY)){
                BaX = rand() %61 + 1; // x goes from 0-60 inclusive
                BaY = rand() % 57 + 1;  //  y goes from 0-56 inclusive
            }
            else
                itr++;
        }
        m_ActorsPtrs.push_back(new OilBarrels(this, BaX, BaY));
    }

    //   place boulders
    int B = min<int>(getLevel()/2 + 2, 9);
    for(int i=0; i < B; i++){
        int BaX = rand() %60; // x goes from 0-60 inclusive
        int BaY = rand() % 56;  //  y goes from 0-56 inclusive
        
        while (BaX <= 33 && BaX >= 26){
            BaX = rand() % 60;
        }
        
        vector<Actor*>::iterator itr;
        itr = m_ActorsPtrs.begin();
        
        while (itr != m_ActorsPtrs.end()){
            if (NearActor(BaX, BaY) || (BaX <= 33 && BaX >= 26)){
                BaX = rand() %60; // x goes from 0-60 inclusive
                BaY = rand() % 56;  //  y goes from 0-56 inclusive
            }
            else
                itr++;
        }
        m_ActorsPtrs.push_back(new Boulder(this, BaX, BaY));

        for (int i=BaX; i< BaX+4; i++){
            for (int j=BaY; j< BaY+4; j++){
                earthArray[i][j]->setVisible(false);
            }
        }
    }
    
    // randomly place gold
    int G = max<int>(5-getLevel()/ 2, 2);
    for(int i=0; i < G; i++){
        int BaX = rand() %61 + 1; // x goes from 0-60 inclusive
        int BaY = rand() % 57 + 1;  //  y goes from 0-56 inclusive
        
        while (BaX >= 25 && BaX <= 33){
            BaX = rand() % 60 + 1;
        }
        
        vector<Actor*>::iterator itr;
        itr = m_ActorsPtrs.begin();
        while (itr != m_ActorsPtrs.end()){
            if (NearActor(BaX, BaY) || (BaX <= 33 && BaX >= 26)){
                BaX = rand() %61 + 1; // x goes from 0-60 inclusive
                BaY = rand() % 57 + 1;  //  y goes from 0-56 inclusive
            }
            else
                itr++;
        }
        m_ActorsPtrs.push_back(new  Gold(this, BaX, BaY));
    }
    
   return GWSTATUS_CONTINUE_GAME;
}

//------MOVE-------------//

int StudentWorld::move() {
    

    FinalSolve(60, 60, maze);
    
    RouteToMan(getTunnelMan()->getX(), getTunnelMan()->getY(), toMan);
    
   // GoToMan(getTunnelMan()->getX(), getTunnelMan()->getY(), toMan);
    
    if (m_barrels <= 0){
           playSound(SOUND_FINISHED_LEVEL);
           return GWSTATUS_FINISHED_LEVEL; // not moving on
    }
    
    else if (m_tManPtr->isAlive() == false){
        playSound(SOUND_PLAYER_GIVE_UP);
        decLives();
        return GWSTATUS_PLAYER_DIED; // automaticaly moves on
    }
    
    m_tManPtr->doSomething();

   //  place goodies(either sonars or waters)
     int GoodieCount = rand() % (getLevel()*25 +300);

     if (GoodieCount == 2){
         int chance = rand() % 5;
         if (chance == 1){
             m_ActorsPtrs.push_back(new SonarKit(this, 0,60));
         }
         else {
             int xpos = rand() % 60;
             int ypos = rand() % 57;
             
             while (!EmptyEarth(xpos, ypos)){
                 xpos = rand() % 60;
                 ypos = rand() % 57;
             }
             m_ActorsPtrs.push_back(new WaterPool(this, xpos, ypos));
         }
     }
    
    m_tickAddProtestor--;
    
    if (m_tickAddProtestor <= 0 && numPro < maxPro){
    
    int HardPro = min<int>(90, getLevel()*10 + 30);
    
    if (((rand() % 99) + 1) <= HardPro){
        m_ActorsPtrs.push_back(new HardProtestors(this, 60, 60, TID_HARD_CORE_PROTESTER));
    }
    else{
        m_ActorsPtrs.push_back(new Protestors(this, 60, 60, TID_PROTESTER));
    }
        numPro++;
        m_tickAddProtestor =  max<int>(25, 200-getLevel());
    }
    
    setDisplayText();
    
    vector<Actor*>::iterator it;
    
    // make all the alive actors do something
    for (it = m_ActorsPtrs.begin(); it != m_ActorsPtrs.end(); it++){
        if ((*it)->isAlive())
            (*it)->doSomething();
    }
    
    // kill all the dead actors
    for (it = m_ActorsPtrs.begin(); it != m_ActorsPtrs.end();){
        if((*it)->isAlive() == false){
            delete *it;
            it = m_ActorsPtrs.erase(it);
        }
        else
            it++;
    }
    
    return GWSTATUS_CONTINUE_GAME;
}


// ----------- clean Up ------------------ //
void StudentWorld::cleanUp(){
    
    for (int i=0; i < 64; i++){
         for (int j=0; j< 64; j++){
             delete earthArray[i][j];
         }
     }
    
    delete m_tManPtr;
    
    vector<Actor*>::iterator itr;
    
    for (itr = m_ActorsPtrs.begin(); itr != m_ActorsPtrs.end(); itr++) {
        delete *itr;
    }
    m_ActorsPtrs.clear();
}

// -------------------- Other functions ------------- //


bool StudentWorld::ifEarth(int x, int y){
   if (x > 63 || x < 0 || y < 0 || y > 60)
       return false;
    
    if (earthArray[x][y]->isVisible() == true)
        return true;
    else
        return false;
}


bool StudentWorld::EmptyEarth(int x, int y){
    if (x > 60 || x < 0 || y < 0 || y > 60)
         return false;
    
    for (int i = x; i < x+4; i++){
        for (int j = y; j < y+4; j++){
            if (earthArray[i][j]->isVisible())
                return false;
        }
    }
    
    for (int i = x; i < x+4; i++){
        for (int j = y; j < y+4; j++){
            if (FindBoulder(x, y))
                return false;
          }
      }
    
    return true;
}

bool StudentWorld::NearActor(int x, int y){
    
    vector<Actor*>::iterator itr;
    itr = m_ActorsPtrs.begin();
    
    while (itr!= m_ActorsPtrs.end()){
        
        if (GetDistance(x, y, (*itr)->getX(), (*itr)->getY()) <= 6)
            return true;
        itr++;
    }
    return false;
}

bool StudentWorld::canMoveHere(int x, int y){
    if (x > 60 || x < 0 || y < 0 || y > 60)
       return false;
    
    if (earthArray[x][y]->isVisible())
        return false;
    
    return true;
}

bool StudentWorld::MoveProtestorsHere(int x, int y, Actor::Direction dir){
    
    if (dir == Actor::down){
        if (ifEarth(x, y-1) || x < 0 || y < 0 || x > 63 || y > 63)
            return false;
    }
    
    if (dir == Actor::right){
        if (ifEarth(x+1, y) || x < 0 || y < 0 || x > 63 || y > 63)
            return false;
       }
    
    if (dir == Actor::up){
         if (ifEarth(x, y+1) || x < 0 || y < 0 || x > 63 || y > 63)
             return false;
        }
    
    if (dir == Actor::left){
         if (ifEarth(x, y-1) || x < 0 || y < 0 || x > 63 || y > 63)
             return false;
        }
    
    return true;
}


void StudentWorld::DigEarth(int x, int y){

if (earthArray[x][y]->isVisible()== true)
    playSound(SOUND_DIG);
    
    // make sure not to dig if its already been dug
    for (int i=x; i<x+4; i++){
            earthArray[i][y]->setVisible(false);
    }
}

void StudentWorld::DigEarthLR(int x, int y){
    
if (earthArray[x][y]->isVisible()== true)
    playSound(SOUND_DIG);
    
    // make sure not to dig if its already been dug
    for (int j=y; j<y+4; j++){
            earthArray[x][j]->setVisible(false);
    }
}

float StudentWorld::GetDistance(const int x1, const int y1, const int x2, const int y2){
    
    // using the distance formula to find the distance between the position of two objects
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}


void StudentWorld::InsertVector(Actor* actor_type){
    m_ActorsPtrs.push_back(actor_type);
}

TunnelMan* StudentWorld::getTunnelMan(){return m_tManPtr;}

void StudentWorld::FoundOil(){m_barrels= m_barrels-1;};

void StudentWorld::releaseSonar(TunnelMan *tman){
    int TmX = tman->getX();
    int TmY = tman->getY();
    
    for ( int i=0; i < m_ActorsPtrs.size(); i++){
        int actX = m_ActorsPtrs[i]->getX();
        int actY = m_ActorsPtrs[i]->getY();
        
        if (GetDistance(TmX, TmY, actX, actY) <= 12){
            m_ActorsPtrs[i]->setVisible(true);
        }
    }
}


bool StudentWorld::ProGetGold(Actor* actor, int distance){
  int actX = actor->getX();
  int actY = actor->getY();

    for (int i= 0; i < m_ActorsPtrs.size(); i++){
        if (GetDistance(actX, actY, m_ActorsPtrs[i]->getX(), m_ActorsPtrs[i]->getY()) <= distance){
            if (m_ActorsPtrs[i]->isPro()){
                playSound(SOUND_PROTESTER_FOUND_GOLD);
                m_ActorsPtrs[i]->MakeAnnoyed(500);
                increaseScore(25);
                actor->setAlive(false);
                return true;
            }
        }
    }
    return false; 
}

bool StudentWorld::AnnoyPro(Actor* actor, int distance, int amt){
  int actX = actor->getX();
  int actY = actor->getY();

    for (int i= 0; i < m_ActorsPtrs.size(); i++){
        Actor* ptr = m_ActorsPtrs[i];
        
        if (GetDistance(actX, actY, ptr->getX(), ptr->getY()) <= distance){
            if (ptr->isPro()){
                ptr->MakeAnnoyed(amt);
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::FindBoulder(int x, int y){
    
    vector<Actor*>::iterator itr;
    itr = m_ActorsPtrs.begin();
    
    while (itr != m_ActorsPtrs.end()){
        if ((*itr)->isBoulder()){
            for (int i = x - 3; i < x + 4; i++){
            for (int j = y - 3; j < y + 4; j++){
                if (i == (*itr)->getX() && j == (*itr)->getY())
                    return true;
            }
            }
        }
    itr++;
    }
    return false;
}

Actor::Direction StudentWorld::FaceTunnelMan(int x, int y){
    int TunY = getTunnelMan()->getY();
    int TunX = getTunnelMan()->getX();
    
    
    if (y > TunY)
        return Actor::down;
    else if (x < TunX)
        return Actor::right;
    else if (y < TunY)
        return Actor::up;
    else
        return Actor::left;
}

Actor::Direction StudentWorld::canTurn(int x, int y, Actor::Direction dir){
    
    if (dir == Actor::right || dir == Actor::left){
        
        if (MoveProtestorsHere(x, y, Actor::down) && MoveProtestorsHere(x, y, Actor::up)){
            
            int val = rand() % 1;
            
            if (val == 0)
                return Actor::down;
            else
                return Actor::up;
        }
        
    
        else if (MoveProtestorsHere(x, y, Actor::down))
            return Actor::down;
        
        else if (MoveProtestorsHere(x, y, Actor::up))
            return Actor::up;
    }
    
    else {
        if (MoveProtestorsHere(x, y, Actor::right) && MoveProtestorsHere(x, y, Actor::left)){
            int val = rand() % 1;
            
            if (val == 0)
                return Actor::left;
            else
                return Actor::right;
            }
            
        else if (MoveProtestorsHere(x, y, Actor::right))
            return Actor::right;
            
        else if (MoveProtestorsHere(x, y, Actor::left))
            return Actor::left;
    }
    return Actor::none;
}

bool StudentWorld::SeesTunnelMan(int x, int y){
    
    
    int fx = getTunnelMan()->getX();
    int fy = getTunnelMan()->getY();
    
    int smallerX;
    int smallerY;
    int bigX;
    int bigY;
    
    if (x == fx){
        if (y < fy){
            smallerY = y;
            bigY = fy-1;
        }
        else {
            smallerY = 4 + fy;
            bigY = y;
        }
        
        for (int i = smallerY; i < bigY; i++){
            if (ifEarth(x, i))
                return false;
        }
     return true;
    }
    
    else if (y == fy){
        if (x < fx){
            smallerX = x;
            bigX = fx-1;
        }
        
        else {
            smallerX = 4+ fx;
            bigX = x;
            
        }
        
        for (int z = smallerX; z < bigX; z++){
            if (ifEarth(z, y))
            return false;
        }
    return true;
    }
    
    return false;
}

Actor::Direction StudentWorld::ProLeave(int &x, int &y){
    
    if (maze[x][y] == Actor::up){
        y++;
        return Actor::up; // up
    }
    else if (maze[x][y] == Actor::left){
        x--;
        return Actor::left; // left
    }
    else if (maze[x][y] == Actor::right){
        x++;
        return Actor::right; // right
    }
    else if (maze[x][y] == Actor::down){
        y--;
        return Actor::down; // down
    }

    else
        return Actor::none;
}

Actor::Direction StudentWorld::MoveTowardsTman(int &x, int &y){

    if (toMan[x][y] == Actor::up){
        y++;
        return Actor::up; // up
    }
    else if (toMan[x][y] == Actor::left){
        x--;
        return Actor::left; // left
    }
    else if (toMan[x][y] == Actor::right){
        x++;
        return Actor::right; // right
    }
    else if (toMan[x][y] == Actor::down){
        y--;
        return Actor::down; // down
    }

    else
        return Actor::none;
}

void StudentWorld::FinalSolve(int x, int y, Actor::Direction g[64][64]){
    
    queue<Coord>  MazeQueue;
    MazeQueue.push(Coord(x, y));
    
    for (int i = 0; i < 64; i++){
        for (int j = 0; j < 64; j++){
                g[i][j] = Actor::none;
        }
    }

    while (!MazeQueue.empty()){
    Coord maze =  MazeQueue.front();
    MazeQueue.pop();
    
        if (g[maze.x()- 1][maze.y()] == 0 && EmptyEarth(maze.x() - 1, maze.y()) && maze.y() >= 0 && maze.y() <61){
            MazeQueue.push(Coord(maze.x() - 1, maze.y()));
            g[maze.x()- 1][maze.y()] = Actor::right;
        }
        
        if (g[maze.x()][maze.y() - 1] == 0 && EmptyEarth(maze.x(), maze.y() - 1) && maze.y() <61 && maze.y() >= 0){
            MazeQueue.push(Coord(maze.x(), maze.y() - 1));
            g[maze.x()][maze.y() - 1] = Actor::up;
        }
        
        if (g[maze.x()+ 1][maze.y()] == 0 && EmptyEarth(maze.x()+1,maze.y()) && maze.x() < 64 && maze.y() > 0 && maze.y() <61){
            MazeQueue.push(Coord(maze.x() + 1, maze.y()));
            g[maze.x() + 1][maze.y()] = Actor::left;
        }
    
        if (g[maze.x()][maze.y() + 1] == 0 && EmptyEarth(maze.x(), maze.y()+1) && maze.y() >= 0 && maze.y() < 61){
            MazeQueue.push(Coord(maze.x(), maze.y() + 1));
            g[maze.x()][maze.y() + 1] = Actor::down;
        }
    }
}

void StudentWorld::RouteToMan(int x, int y, Actor::Direction g[64][64]){

    queue<Coord>  MazeQueue;
    MazeQueue.push(Coord(x, y));

    for (int i = 0; i < 64; i++){
        for (int j = 0; j < 64; j++){
                g[i][j] = Actor::none;
        }
    }

    while (!MazeQueue.empty()){
    Coord maze =  MazeQueue.front();
    MazeQueue.pop();

        if (g[maze.x()- 1][maze.y()] == 0 && EmptyEarth(maze.x() - 1, maze.y()) && maze.y() >= 0 && maze.y() <61){
            MazeQueue.push(Coord(maze.x() - 1, maze.y()));
            g[maze.x()- 1][maze.y()] = Actor::right;
        }

        if (g[maze.x()][maze.y() - 1] == 0 && EmptyEarth(maze.x(), maze.y() - 1) && maze.y() <61 && maze.y() >= 0){
            MazeQueue.push(Coord(maze.x(), maze.y() - 1));
            g[maze.x()][maze.y() - 1] = Actor::up;
        }

        if (g[maze.x()+ 1][maze.y()] == 0 && EmptyEarth(maze.x()+1,maze.y()) && maze.x() < 64 && maze.y() > 0 && maze.y() <61){
            MazeQueue.push(Coord(maze.x() + 1, maze.y()));
            g[maze.x() + 1][maze.y()] = Actor::left;
        }

        if (g[maze.x()][maze.y() + 1] == 0 && EmptyEarth(maze.x(), maze.y()+1) && maze.y() >= 0 && maze.y() < 61){
            MazeQueue.push(Coord(maze.x(), maze.y() + 1));
            g[maze.x()][maze.y() + 1] = Actor::down;
        }
    }
}

void StudentWorld::SetProtestors(){
    maxPro++; 
}

void StudentWorld::setDisplayText(){

    int level = getLevel();
    int lives = getLives();
    int health = getTunnelMan()->getHitPtrs();
    int squirts = getTunnelMan()->getWater();
    int gold = getTunnelMan()->getGold();
    int barrelsLeft = m_barrels;
    int sonar = getTunnelMan()->getSonar();
    int score = getScore();
    
    ostringstream oss;

    oss.fill('0');
    
    oss << "Scr: ";
    oss << setw(6) << score << "  ";
    
    oss << "Lvl: ";
    oss << level << "  ";

    oss << "Lives: ";
    oss << lives << "  ";

    oss << "Hlth: ";
    oss << health*10 << "% ";

    oss << "Wtr: ";
    oss << squirts << "  ";

    oss << "Gld: ";
    oss << gold << "  ";

    
    oss << "Sonar: ";
    oss << sonar << " ";
    
    oss << "Oil Left: ";
    oss << barrelsLeft << " ";
    
    setGameStatText(oss.str());
}

