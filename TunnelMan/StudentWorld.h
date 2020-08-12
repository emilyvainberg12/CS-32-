#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <vector>

class Earth;
class TunnelMan;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir): GameWorld(assetDir){}
    ~StudentWorld(){};
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void DigEarth(int x, int y);

private:
    TunnelMan *m_tManPtr;
    Earth* earthArray[64][64];
    std::vector<GraphObject*> m_objectPtrs;
};

#endif // STUDENTWORLD_H_
