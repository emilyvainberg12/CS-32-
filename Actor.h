#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <algorithm>

class StudentWorld;
class Protestors;
class Earth;
class Squirt;
class Gold; 


class Actor: public GraphObject {
    public:
        // constructor
        Actor(StudentWorld *w, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
        virtual ~Actor();
        virtual void doSomething() = 0;
        bool isAlive();
        void setAlive(bool alive);
        virtual void MakeAnnoyed(int amount);
        StudentWorld* getWorld();
        virtual bool isPro();
        virtual bool isBoulder();
        bool MoveActor(Direction dir);
    private:
        bool m_alive;
        StudentWorld* m_world;
};

class TunnelMan: public Actor{
    public:
        TunnelMan(StudentWorld *w, int hitPoints);
        virtual ~TunnelMan();
        virtual void doSomething();
        virtual void MakeAnnoyed(int amount);
        void setWater();
        void setSonar(int amount);
        void setGold();
        int getGold();
        int getHitPtrs();
        int getWater();
        int getSonar();
    private:
        int m_water;
        int m_sonar;
        int m_gold;
        int m_hitPoints;
};

class Protestors: public Actor {
    public:
        Protestors(StudentWorld *w, int x, int y, int imageID);
        virtual void MakeAnnoyed(int amount);
        virtual ~Protestors();
        virtual void doSomething();
        virtual bool isPro();
        void setTurnTicks(int amount);
        int getTurnTicks();
        Actor::Direction GetRandomDir();
        GraphObject::Direction GetGoodDir();
    private:
        int imageID;
        int m_hitPoints;
        int m_ticksMoves;
        int m_ticksTurn;
        int m_ticksShout;
        bool m_leaveEarth;
        int m_numSquaresToMoveInCurrentDirection;
};

class HardProtestors: public Protestors{
    public:
        HardProtestors(StudentWorld *w, int x, int y, int imageID);
        virtual void MakeAnnoyed(int amount);
        virtual ~HardProtestors();
        virtual void doSomething();
        virtual bool isPro();
    private:
        int m_ticksTurn;
        int m_ticks;
        int m_leaveEarth;
        int m_hitPoints;
        int m_ticksShout;
        int m_numSquaresToMoveInCurrentDirection;
        int m_ticksMoves;
        int m_stareTicks;
};

class Squirt: public Actor {
    public:
    Squirt(StudentWorld *w, int x, int y, Direction dir);
        virtual void doSomething();
        virtual ~Squirt();
    private:
        int m_travel;
        Direction m_direction;
};

class Earth: public Actor{
    public:
        Earth(StudentWorld *w, int x, int y);
        virtual ~Earth();
        virtual void doSomething();
};

class Goodie: public Actor {
    public:
        Goodie(StudentWorld *w, int imageID, int x, int y);
        int Helper();
        virtual void doSomething();
        virtual ~Goodie();
};

class OilBarrels: public Goodie{
    public:
        OilBarrels(StudentWorld *w, int x, int y);
        virtual void doSomething();
        virtual ~OilBarrels();
    private:
        int m_traveled;
};

class SonarKit: public Goodie{
    public:
        SonarKit(StudentWorld *w, int x, int y);
        virtual void doSomething();
        virtual ~SonarKit();
};

class WaterPool: public Goodie{
    public:
        WaterPool(StudentWorld *w, int x, int y);
        virtual void doSomething();
        virtual ~WaterPool();
    private:
        int m_ticks; 
};

class Boulder: public Actor {
    public:
        Boulder(StudentWorld *w, int x, int y);
        virtual ~Boulder();
        virtual void doSomething();
        virtual bool isBoulder();
    private:
       // int m_travel;
        int m_ticks;
        bool fallingState;
        int m_state;
};

class Gold: public Goodie{
    public:
        Gold(StudentWorld *w, int x, int y);
        virtual void doSomething();
        virtual ~Gold();
        void ProCanTake();
    private:
        int m_ticks;
        bool m_proCanTake;
        bool m_perm;
};

#endif // ACTOR_H_
