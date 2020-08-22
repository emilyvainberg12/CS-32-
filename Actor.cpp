#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>

using namespace std;

class StudentWorld;

// ------  ACTOR    ----------- //

Actor::Actor(StudentWorld* w, int imageID, int x, int y, Direction dir, double size, unsigned int depth): GraphObject(imageID, x, y, dir, size, depth){
    setVisible(true);
    m_alive = true;
    m_world = w;
}

Actor::~Actor(){};

void Actor::MakeAnnoyed(int amount){};

bool Actor::isAlive(){return m_alive;}

void Actor::setAlive(bool alive){m_alive = alive;}

StudentWorld* Actor::getWorld(){return m_world;}

bool Actor::isPro(){return false;}

bool Actor::isBoulder(){return false;}

bool Actor::MoveActor(Direction dir){
    
    if (dir == right){
        if (!getWorld()->EmptyEarth(getX()+1, getY()))
            return false;
        moveTo(getX()+1,getY());
        return true;
    }
    
     if (dir == left){
        if (!getWorld()->EmptyEarth(getX()-1, getY()))
                return false;
         moveTo(getX()-1,getY());
         return true;
     }
    
    
    if (dir == up){
        if (!getWorld()->EmptyEarth(getX(), getY()+1))
                return false;
        moveTo(getX(),getY()+1);
        return true;
    }
    
    if (dir == down){
        if (!getWorld()->EmptyEarth(getX(), getY()-1))
                  return false;
          moveTo(getX(),getY()-1);
          return true;
      }

    return false;
}
//--------------- TUNNEL MAN -----------------//

TunnelMan::TunnelMan(StudentWorld *w, int hitPoints): Actor(w,TID_PLAYER, 30, 60, right, 1.0, 0){
    m_hitPoints = hitPoints;
    m_water = 5;
    m_sonar = 1;
    m_gold = 0;
}

TunnelMan::~TunnelMan(){}

void TunnelMan::setGold(){m_gold= m_gold+1;}

int TunnelMan::getGold(){return m_gold;}

int TunnelMan::getHitPtrs(){return m_hitPoints;}

int TunnelMan::getWater(){return m_water;}

int TunnelMan::getSonar(){return m_sonar;}

void TunnelMan::setSonar(int amount){m_sonar= m_sonar+amount;}

void TunnelMan::setWater(){m_water = m_water+5;}

void TunnelMan::MakeAnnoyed(int amount){
    
    m_hitPoints = m_hitPoints - amount;

    if (m_hitPoints <= 0)
        setAlive(false);
}

void TunnelMan::doSomething(){
   
    int ch;
    if (getWorld()->getKey(ch) == true) { // user hit a key this tick!
        switch (ch){
            case KEY_PRESS_LEFT:
                if (getDirection() != left){
                    setDirection(left);
                    break;
                }
                if (getX() > 0 && !getWorld()->FindBoulder(getX()-1, getY())){
                    moveTo(getX()-1, getY()); //move player left
                    getWorld()->DigEarthLR(getX(), getY());
                }
                break;
            case KEY_PRESS_RIGHT:
                if (getDirection()!= right){
                    setDirection(right);
                    break;
                }
                if (getX() < 60 && !getWorld()->FindBoulder(getX()+1, getY())){
                    getWorld()->DigEarthLR(getX()+4, getY());
                    moveTo(getX()+1, getY()); //move player right
                }
                break;
            case KEY_PRESS_UP:
                if (getDirection()!= up){
                    setDirection(up);
                    break;
                }
                if (getY() < 60 && !getWorld()->FindBoulder(getX(), getY()+1)){
                    getWorld()->DigEarth(getX(), getY()+4);
                    moveTo(getX(), getY()+1); // move player up
                }
                break;
            case KEY_PRESS_DOWN:
                if (getDirection() != down){
                    setDirection(down);
                    break;
                }
                if ((getY() > 0) && !getWorld()->FindBoulder(getX(), getY()-1)){
                    moveTo(getX(), getY()-1);
                    getWorld()->DigEarth(getX(), getY());
                }
                break;
            case KEY_PRESS_SPACE:
                if (m_water > 0){
                    Squirt *m_squirt;
                    Direction current = getDirection();
                    m_water--;
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
                    
                    if (current == right&& getWorld()->canMoveHere(getX()+1, getY())){
                        m_squirt = new Squirt(getWorld(),getX()+1 , getY(), current);
                        getWorld()->InsertVector(m_squirt);
                        for (int i = 0; i< 6; i++){
                            if (getWorld()->canMoveHere(m_squirt->getX()+i, m_squirt->getY()))
                                m_squirt->moveTo(getX()+i, getY());
                        }
                    }
            
                    else if (current == left && getWorld()->canMoveHere(getX()-1, getY())){
                        m_squirt = new Squirt(getWorld(),getX()-1, getY(), current);
                        getWorld()->InsertVector(m_squirt);
                        for (int i = 0; i< 6; i++){
                             if (getWorld()->canMoveHere(m_squirt->getX(), m_squirt->getY()+i))
                                m_squirt->moveTo(getX()-i, getY());
                        }
                    }

                    else if (current == down&& getWorld()->canMoveHere(getX(), getY()-1)){
                            m_squirt = new Squirt(getWorld(),getX(), getY()-1, current);
                            getWorld()->InsertVector(m_squirt);
                            for (int i = 0; i< 6; i++){
                                if (!getWorld()->ifEarth(m_squirt->getX(), m_squirt->getY()-i) && (getY()-i) > 0)
                                    m_squirt->moveTo(getX(), getY()-i);
                            }
                    }
                    
                    else if (current == up && getWorld()->canMoveHere(getX(), getY())+1){
                        m_squirt = new Squirt(getWorld(),getX(), getY()+1, current);
                        getWorld()->InsertVector(m_squirt);
                        for (int i = 0; i< 7; i++){
                            if (!getWorld()->ifEarth(m_squirt->getX(), m_squirt->getY()+i) && (getY()+i) < 60)
                                m_squirt->moveTo(getX(), getY()+i);
                        }
                    }
                }
                break;
            case KEY_PRESS_TAB:
                if (m_gold > 0){
                    m_gold--;
                    Gold* m_gold = new Gold(getWorld(),getX(), getY());
                    getWorld()->InsertVector(m_gold);
                    m_gold->setVisible(true);
                    m_gold->ProCanTake(); // now lets the protestors take the gold
                }
                break;
            case KEY_PRESS_ESCAPE:
                (setAlive(false));
                break;
            case 'Z':
                if (getSonar() > 0){
                    setSonar(-1);
                    getWorld()->playSound(SOUND_SONAR);
                    getWorld()->releaseSonar(this);
                }
                break;
            case 'z':
                if (getSonar() > 0){
                    setSonar(-1);
                    getWorld()->playSound(SOUND_SONAR);
                    getWorld()->releaseSonar(this);
                }
                break;
        } // end of switch statement
    } // end of if key was pressed
}


// ----- GOODIE -----//

WaterPool::WaterPool(StudentWorld *w, int x, int y): Goodie(w, TID_WATER_POOL, x, y){
    m_ticks = max<int>(100, 300 - (10* getWorld()->getLevel()));
}

Gold::Gold(StudentWorld *w, int x, int y): Goodie(w, TID_GOLD, x, y){
    m_ticks = 100;
    setVisible(false);
    m_perm = true;
    m_proCanTake = false;
}

Squirt::Squirt(StudentWorld *w, int x, int y, Direction dir): Actor(w, TID_WATER_SPURT, x, y, dir, 1.0, 1){m_travel = 6;}
Earth::Earth(StudentWorld *w, int x, int y): Actor (w, TID_EARTH, x, y, right, .25, 3){}
SonarKit::SonarKit(StudentWorld *w, int x, int y): Goodie(w,TID_SONAR, x, y){}
OilBarrels::OilBarrels(StudentWorld *w, int x, int y): Goodie(w, TID_BARREL, x, y){setVisible(false);}
Goodie::Goodie(StudentWorld *w, int imageID, int x, int y): Actor(w, imageID, x, y, right, 1.0, 2){}
void Earth::doSomething(){};
void Gold::ProCanTake(){m_proCanTake = true;}
void Goodie::doSomething(){};
Goodie::~Goodie(){};
OilBarrels::~OilBarrels(){};
WaterPool::~WaterPool(){};
Gold::~Gold(){};
SonarKit::~SonarKit(){};
Squirt::~Squirt(){}
Earth::~Earth(){};


int Goodie::Helper(){
    if (this->isVisible() == true){
            if (getWorld()->GetDistance(getX(), getY(), getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY()) <= 3){
                setAlive(false);
                setVisible(false);
                getWorld()->playSound(SOUND_GOT_GOODIE);
                return 1;
            }
        }
    return 0;
}
void SonarKit::doSomething(){
    
    if (Helper() == 1){
        getWorld()->increaseScore(75);
        getWorld()->getTunnelMan()->setSonar(2);
    }
}
void OilBarrels::doSomething(){
    
    if (isVisible() == false){
        // check if the oilbarrels are near the tunnelman
        if (getWorld()->GetDistance(getX(), getY(), getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY()) <= 4){
            setVisible(true);
            return;
        }
    }
    // if the Barrel is within a radius of 3.0 (<= 3.00 units away) from the TunnelMan, then the Barrel will activate, and: The Barrel must set its state to dead (so that it will be removed by your StudentWorld class from the game at the end of the current tick).
    if (getWorld()->GetDistance(getX(), getY(), getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY()) <= 3){
        setAlive(false);
        setVisible(false);
        getWorld()->playSound(SOUND_FOUND_OIL);
        getWorld()->increaseScore(1000);  //Barrel must increase the player’s score by 1000 points.
        getWorld()->FoundOil(); // tell student world barrel was picked up
    }
}

void WaterPool::doSomething(){
    
    if (m_ticks == 0){
        setAlive(false);
        setVisible(false);
        return;
    }
    
    if (m_ticks != 0)
        m_ticks--; 
    
    if (Helper() == 1){
        getWorld()->increaseScore(75);
        getWorld()->getTunnelMan()->setWater();
    }
}

void Gold::doSomething(){
    
    if (m_proCanTake == false){
        if (isVisible() == false){
            if (getWorld()->GetDistance(getX(), getY(), getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY()) <= 4){
                setVisible(true);
                return;
            }
        }
        
        if (Helper() == 1){
            getWorld()->increaseScore(10);
            getWorld()->getTunnelMan()->setGold();
        }
    }
    
    else if (m_proCanTake == true){
        
    getWorld()->ProGetGold(this, 3);
        
        m_ticks--;

        if (m_ticks <= 0)
            setAlive(false);
    }
}

void Squirt::doSomething(){
    
    if(getWorld()->AnnoyPro(this, 3, 2))
        setAlive(false);
        
    else if (m_travel == 0)
        setAlive(false);
    m_travel--;
}

//    ----------------------- PROTESTORS ----------------- //

Protestors::Protestors(StudentWorld *w, int x, int y, int imageID): Actor(w, imageID, x, y, left, 1.0, 1){
    m_hitPoints = 5; //TODO: how many hit points do protestors start with
    m_ticksMoves = fmax(0, 3-(getWorld()->getLevel()/4));
    m_ticksTurn = 200;
    m_ticksShout = 15;
    m_leaveEarth = false;
}

Protestors::~Protestors(){}

int Protestors::getTurnTicks(){return m_ticksTurn;}

bool Protestors::isPro(){return true;};

Actor::Direction Protestors::GetRandomDir(){
    
    int x = rand() % 4;
    
    if (x == 0)
        return right;
    
    else if (x == 1)
        return left;
    
    else if (x== 2)
        return up;
    
    else
        return down;
}

void Protestors::doSomething(){
    
    
    // leave the oil field state
    if (m_leaveEarth == true){
        if (getX() == 60 && getY() == 60){
            getWorld()->SetProtestors();
            setAlive(false);
            setVisible(false);
        }
        
        Direction tmp = none;
        int TY = getY();
        int TX = getX();
        
        tmp = getWorld()->ProLeave(TX, TY);
        
        if (tmp != none){
            setDirection(tmp);
            moveTo(TX, TY);
        }
        
    return;
    } // end of "trying to leave earth"
    
    if (m_ticksMoves != 0){
        m_ticksMoves--;
        return;
    }
    
        m_ticksTurn--;
      
    // check to see if they are within a distance of 4 units of the TunnelMan, AND they are currently facing in the TunnelMan’s direction
    if (getWorld()->GetDistance(getX(), getY(), getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY()) <= 4){
        if (m_ticksShout <= 0){
            getWorld()->playSound(SOUND_PROTESTER_YELL);
            getWorld()->getTunnelMan()->MakeAnnoyed(2);
            m_ticksShout = 60;
            m_ticksMoves = fmax(0, 3-(getWorld()->getLevel()/4));
            return;
        }
        m_ticksShout--;
        return;
    }
    
    else {
        if (getY() == 60 && getDirection()== left && getWorld()->EmptyEarth(getX(), getY()-1)){
            setDirection(down);
            moveTo(getX(), getY()-1);
            return;
        }
        
        if (getWorld()->SeesTunnelMan(getX(), getY())){
            if (getWorld()->GetDistance(getX(), getY(), getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY()) > 4){
                setDirection(getWorld()->FaceTunnelMan(getX(), getY()));
                MoveActor(getDirection());
            }
            else{
                setDirection(getWorld()->FaceTunnelMan(getX(), getY()));
            }
           // m_numSquaresToMoveInCurrentDirection = 0;
            m_ticksMoves = fmax(0, 3-(getWorld()->getLevel()/4));
        }
        else{
            m_numSquaresToMoveInCurrentDirection--;
            if (m_numSquaresToMoveInCurrentDirection > 0){
                MoveActor(getDirection());
                m_ticksMoves = fmax(0, 3-(getWorld()->getLevel()/4));
                return;
            }
            
            if (m_numSquaresToMoveInCurrentDirection <= 0){
                setDirection(GetGoodDir());
                m_numSquaresToMoveInCurrentDirection = ((rand() % 53) +8);
            }
            else {
                Direction newDir = getWorld()->canTurn(getX(), getY(), getDirection());
                    if (newDir != none){
                        if (m_ticksTurn <= 0){
                            setDirection(newDir);
                            m_numSquaresToMoveInCurrentDirection = ((rand() % 53) +8);
                            m_ticksTurn = 200;
                        }
                         m_ticksTurn--;
                    }
                if (getWorld()->MoveProtestorsHere(getX(), getY(), getDirection()))
                        MoveActor(getDirection());
                else
                    m_numSquaresToMoveInCurrentDirection = 0;
                    
                m_ticksMoves = fmax(0, 3-(getWorld()->getLevel()/4));
                return;
            }
        }
    }
}

GraphObject::Direction Protestors::GetGoodDir(){
    Direction dir;
    
    dir = GetRandomDir();
    
    for (;;){
        dir = GetRandomDir();
    
        if (dir == up && getWorld()->EmptyEarth(getX(), getY()+1))
            return dir;
        
        else if (dir == down && getWorld()->EmptyEarth(getX(), getY()-1))
            return dir;
        
        else if (dir == left && getWorld()->EmptyEarth(getX()-1, getY()))
            return dir;
        
        else if (dir == right && getWorld()->EmptyEarth(getX()+1, getY()))
            return dir;
    
    }
    return dir;
}

void Protestors::MakeAnnoyed(int amount){
    if (m_leaveEarth == true)
        return;
    
    if (amount == 500){
        m_leaveEarth = true;
        return; 
    }
    
    // find out what the new hit points/ health is
     m_hitPoints = m_hitPoints - amount;
    
    if (m_hitPoints <= 0){
        m_leaveEarth = true; // now the protestors give up and want to leave earth
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        m_ticksMoves = 0;
    
        if (amount == 2) // if killed by squirt
            getWorld()->increaseScore(100);
        else if (amount == 100)
            getWorld()->increaseScore(500);
    }
    
    else if (m_hitPoints > 0){
        getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
        int temp = 100 - (getWorld()->getLevel()*10);
        m_ticksMoves = max(50, temp);
    }
    
}

// ----------- HARDCORE PROTESTORS --------- //
HardProtestors::HardProtestors(StudentWorld *w, int x, int y, int imageID): Protestors(w, x, y, imageID){
    m_leaveEarth = false;
    m_hitPoints = 20;
    m_ticksShout = 45;
    m_numSquaresToMoveInCurrentDirection = ((rand() % 53) +8);
    m_ticksMoves =  fmax(0, 3- getWorld()->getLevel()/4);
    m_stareTicks = 0;
    
}

HardProtestors::~HardProtestors(){};

bool HardProtestors::isPro(){return true;};

void HardProtestors::MakeAnnoyed(int amount){
    
    if (m_leaveEarth == true)
          return;
    
    if (amount == 500){ // found gold
        getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
        getWorld()->increaseScore(50);
        m_stareTicks = (max<int>(50, 100 - getWorld()->getLevel() * 10));
        return;
    }

     m_hitPoints = m_hitPoints - amount;
    
    if (m_hitPoints <= 0){
        m_leaveEarth = true; // now the protestors give up and want to leave earth
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        m_ticks = 0;
    
        if (amount == 2) // if killed by squirt
            getWorld()->increaseScore(100);
        else if (amount == 100)
            getWorld()->increaseScore(500);
    }
    
    else if (m_hitPoints > 0){
        getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
        m_ticks = fmax(0, 3- getWorld()->getLevel()/4);
    }
};

void HardProtestors::doSomething(){
    
    if (m_stareTicks != 0){
        m_stareTicks--;
        return; 
    }
    
    // leave the oil field state
    if (m_leaveEarth == true){
        if (getX() == 60 && getY() == 60){
            getWorld()->SetProtestors();
            setAlive(false);
            setVisible(false);
        }
        
        Direction tmp = none;
        int TY = getY();
        int TX = getX();
        
        tmp = getWorld()->ProLeave(TX, TY);
        
        if (tmp != none){
            setDirection(tmp);
            moveTo(TX, TY);
        }
        
    return;
    } // end of "trying to leave earth"
    
    if (m_ticksMoves != 0){
        m_ticksMoves--;
        return;
    }
    
   
    // check to see if they are within a distance of 4 units of the TunnelMan, AND they are currently facing in the TunnelMan’s direction
    if (getWorld()->GetDistance(getX(), getY(), getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY()) <= 4){
        if (m_ticksShout <= 0){
            getWorld()->playSound(SOUND_PROTESTER_YELL);
            getWorld()->getTunnelMan()->MakeAnnoyed(2);
            m_ticksShout = 60;
            m_ticksMoves = fmax(0, 3-(getWorld()->getLevel()/4));
            return;
        }
        m_ticksShout--;
        return;
    }
    
    else {
        if (getWorld()->SeesTunnelMan(getX(), getY())){
            if (getWorld()->GetDistance(getX(), getY(), getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY()) > 4){
                setDirection(getWorld()->FaceTunnelMan(getX(), getY()));
                MoveActor(getDirection());
            }
            else{
                setDirection(getWorld()->FaceTunnelMan(getX(), getY()));
            }
           // m_numSquaresToMoveInCurrentDirection = 0;
            m_ticksMoves = fmax(0, 3-(getWorld()->getLevel()/4));
        }
        else{
            if ((getWorld()->GetDistance(getX(), getY(), getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY()) < 25)){
                int tx = getX();
                int ty = getY();
                Direction dir = getWorld()->MoveTowardsTman(tx, ty);
                
                if (dir != none){
                    setDirection(dir);
                    moveTo(tx, ty);
                    m_ticksMoves = fmax(0, 3-(getWorld()->getLevel()/4));
                    return;
                }
            }
            else{
            
            m_numSquaresToMoveInCurrentDirection--;
            if (m_numSquaresToMoveInCurrentDirection > 0){
                MoveActor(getDirection());
                m_ticksMoves = fmax(0, 3-(getWorld()->getLevel()/4));
                return;
            }
            
            if (m_numSquaresToMoveInCurrentDirection <= 0){
                setDirection(GetGoodDir());
                m_numSquaresToMoveInCurrentDirection = ((rand() % 53) +8);
            }
            else {
                Direction newDir = getWorld()->canTurn(getX(), getY(), getDirection());
                    if (newDir != none){
                        if (m_ticksTurn <= 0){
                            setDirection(newDir);
                            m_numSquaresToMoveInCurrentDirection = ((rand() % 53) +8);
                            m_ticksTurn = 200;
                        }
                         m_ticksTurn--;
                    }
                if (getWorld()->MoveProtestorsHere(getX(), getY(), getDirection()))
                        MoveActor(getDirection());
                else
                    m_numSquaresToMoveInCurrentDirection = 0;
                    
                m_ticksMoves = fmax(0, 3-(getWorld()->getLevel()/4));
                return;
            }
            }
        }
    }
}


// ------ BOULDER ---------------//

Boulder::Boulder(StudentWorld *w, int x, int y):Actor(w, TID_BOULDER, x, y, down, 1.0, 1){
    fallingState = false;
    m_ticks = 30;
    m_state = 0;
}

Boulder::~Boulder(){}

bool Boulder::isBoulder() {return true;}

void Boulder::doSomething(){
    
    if (m_state == 0){
    
    // check that there are four sqaures below that don't have earth
    if (!getWorld()->ifEarth(getX(),getY()-1) && !getWorld()->ifEarth(getX()+1,getY()-1) && !getWorld()->ifEarth(getX()+1,getY()-1) && !getWorld()->ifEarth(getX()+2,getY()-1) && !getWorld()->ifEarth(getX()+3,getY()-1)){
        m_state = 1;
        }
    }
    
    else if (m_state == 1){
    // if its in a falling state
        
        if (m_ticks <= 0){
            m_state = 2;
        }
        else
            m_ticks--;
    }
    
    else {
         getWorld()->playSound(SOUND_FALLING_ROCK);
        
        
        if (getWorld()->GetDistance(getX(), getY(), getWorld()->getTunnelMan()->getX(), getWorld()->getTunnelMan()->getY()) <= 3)
            getWorld()->getTunnelMan()->setAlive(false);
        
          getWorld()->AnnoyPro(this, 3, 100);
            
        if (getWorld()->ifEarth(getX(),getY()-1) ||  getWorld()->ifEarth(getX()+1, getY()-1) || getWorld()->ifEarth(getX()+2, getY()-1) || getWorld()->ifEarth(getX()+3, getY()-1)){
           setAlive(false);
            return;
        }

        else if (getY()-1 < 0){
            setAlive(false);
            return;
        }
        
        else{
            moveTo(getX(), getY()-1);
        }
    }
}


        








