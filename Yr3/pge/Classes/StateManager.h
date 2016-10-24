#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// Cocos2d
#include "cocos2d.h"
USING_NS_CC;

// Essentials
#include <vector>

// State
#include "State.h"

class StateManager : public cocos2d::Node
{
public:
	StateManager(cocos2d::Director*);
	virtual ~StateManager();

	// State Manager Functions
private:
	cocos2d::Director * m_director;
	std::vector<State*> m_stateList;
};

#endif 