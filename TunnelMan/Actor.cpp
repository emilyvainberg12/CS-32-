#include "Actor.h"
#include "StudentWorld.h"

class StudentWorld;


Actor::Actor(StudentWorld* w, int imageID, int x, int y, Direction dir, double size, unsigned int depth)
: GraphObject(imageID, x, y)
{
    m_alive = true;
    setVisible(true);
    m_world = w;
}

void TunnelMan::doSomething(){
    if (isAlive() == false) // check to see if it is currently alive. If not, then return immediately
        return;
    
    //If the TunnelMan’s 4x4 image currently overlaps any Earth objects within the oil field, then it will call upon the StudentWorld object to:
    // Set  Earth objects from the 4x4 area occupied by the TunnelMan (from x, y to x+3,y+3 inclusive) to not visibile
    //Make a digging sound by playing the SOUND_DIG sound (see the StudentWorld section of this document for details on how to play a sound).
    
    int ch;
    if (getWorld()->getKey(ch) == true) { // user hit a key this tick!
        switch (ch){
            case KEY_PRESS_LEFT:
                if (getDirection() != left){
                    setDirection(left);
                    break;
                }
                if (getX() > 0){
                    moveTo(getX()-1, getY()); //move player left
                    getWorld()->DigEarth(getX(), getY());
                }
                break;
            case KEY_PRESS_RIGHT:
                if (getDirection()!= right){
                    setDirection(right);
                    break;
                }
                if (getX() < 60){
                    moveTo(getX()+1, getY()); //move player right
                    getWorld()->DigEarth(getX(), getY());
                }
                break;
            case KEY_PRESS_UP:
                if (getDirection()!= up){
                    setDirection(up);
                    break;
                }
                if (getY() < 60){
                    moveTo(getX(), getY()+1); // move player up
                    getWorld()->DigEarth(getX(), getY());
                }
                break;
            case KEY_PRESS_DOWN:
                if (getDirection() != down){
                    setDirection(down);
                    break;
                }
                if (getY() > 0){
                    moveTo(getX(), getY()-1);
                    getWorld()->DigEarth(getX(), getY());
                }
                break;
            case KEY_PRESS_SPACE:
                //... add a Squirt in front of the player...;
                break;
            case KEY_PRESS_TAB:
                break; // finihs
            case KEY_PRESS_ESCAPE:
                (setAlive(false));
                break; // finsih
            case 'Z':
                break;
            case 'z':
                break;
        }
    }
}
