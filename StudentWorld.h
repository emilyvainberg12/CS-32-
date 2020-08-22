#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <vector>
#include <algorithm>
#include <queue>

class Earth;
class TunnelMan;

struct Coord{
public:
    Coord(int x, int y) : m_x(x), m_y(y) {}
    int x() const { return m_x; }
    int y() const { return m_y; }
private:
    int m_x;
    int m_y;
};

class StudentWorld : public GameWorld {
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void FoundOil();
    void DigEarth(int x, int y);
    void DigEarthLR(int x, int y);
    bool ifEarth(int x, int y);
    bool EmptyEarth(int x, int y);
    bool canMoveHere(int x, int y);
    bool NearActor(int BaX, int BaY);
    bool AnnoyPro(Actor* actor, int distance, int amt);
    void InsertVector(Actor* actor_type);
    float GetDistance(const int x1, const int y1, const int x2, const int y2);
    void releaseSonar(TunnelMan* tman);
    bool FindBoulder(int x, int y);
    void SetProtestors();
    bool ProGetGold(Actor* prot, int distance);
    bool SeesTunnelMan(int x, int y);
    bool MoveProtestorsHere(int x, int y, Actor::Direction dir);
    void FinalSolve(int x, int y, Actor::Direction g[64][64]);
    void RouteToMan(int x, int y, Actor::Direction g[64][64]);
    Actor::Direction FaceTunnelMan(int x, int y);
    Actor::Direction canTurn(int x, int y, Actor::Direction dir);
    Actor::Direction ProLeave(int &x, int &y);
    Actor::Direction MoveTowardsTman(int &x, int &y);
    TunnelMan* getTunnelMan();
    
private:
    int numPro;
    int m_barrels;
    int m_tickAddProtestor;
    int m_sonarTicks;
    int maxPro;
    void setDisplayText();
    TunnelMan *m_tManPtr;
    Earth* earthArray[64][64];
    std::vector<Actor*> m_ActorsPtrs;
    Actor::Direction maze[64][64];
    Actor::Direction toMan[64][64];
  };

    

#endif // STUDENTWORLD_H_
