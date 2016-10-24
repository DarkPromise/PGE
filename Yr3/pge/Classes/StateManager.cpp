#include "StateManager.h"

StateManager::StateManager(cocos2d::Director * director)
	: m_director(director)
{
}

StateManager::~StateManager()
{
	if (!m_stateList.empty())
	{
		for (State * state : m_stateList)
		{
			delete state;
		}
		m_stateList.clear();
		m_stateList.~vector();
	}
}