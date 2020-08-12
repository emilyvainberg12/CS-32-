#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;
class Earth;


class Actor: public GraphObject {
    public:
        // constructor
        Actor(StudentWorld *w, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
        virtual ~Actor(){};
        virtual void doSomething() = 0;
        bool isAlive(){ return m_alive;};
        void setAlive(bool alive) {m_alive = alive;};
        StudentWorld* getWorld() {return m_world;};
    
    private:
        bool m_alive;
        StudentWorld* m_world;
};


class TunnelMan: public Actor{
    public:
        TunnelMan(StudentWorld *w, int hitPoints): Actor(w,TID_PLAYER, 30, 60, right, 1.0, 0), m_hitPoints(hitPoints){}
        virtual ~TunnelMan(){};
        virtual void doSomething();
    private:
        int m_hitPoints;
};

class Earth: public GraphObject {
    public:
        Earth(StudentWorld *w, int x, int y):GraphObject(TID_EARTH, x, y, right, .25, 3), m_world(w){
       // virtual ~Earth() = default;
        setVisible(true);
        }
    private:
        StudentWorld* m_world;
};



//class Protester: public Actor {
//    public:
//
//};
//
//class HardcoreProtester: public Protester {
//    public:
//
//};

#endif // ACTOR_H_
