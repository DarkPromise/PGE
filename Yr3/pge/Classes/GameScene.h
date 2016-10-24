#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

// Cocos2d
#include "cocos2d.h"

USING_NS_CC;

// Gameplay
#include "Gameboard.h"

class Game : public cocos2d::Layer
{
public:
	enum E_STATE
	{
		E_NORMAL,
		E_UPDATE,
		E_REMOVE,
		E_SHIFT,
		E_CREATE,
		E_STATE_TOTAL
	};

	struct sNode
	{
		Gems gem;
		E_STATE eState;
	};

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// Gameplay Functions
	void createGameBoard();
	void createUI();
	
	// Gameplay Logic (Should be in GSM)
	void CheckEntireArray();
	void RemoveGems();
	void ShiftGems();
	void CreateGems();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	
	// Listeners
	void createListeners();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode, cocos2d::Event * event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event * event);

	// Mouse
	void onMouseMove(cocos2d::Event * event);
	void onMouseUp(cocos2d::Event * event);
	void onMouseDown(cocos2d::Event * event);
	void onMouseScroll(cocos2d::Event * event);

	// implement the "static create()" method manually
	CREATE_FUNC(Game);

private:
	E_STATE m_eState;
	sNode m_arrGem[MAX_HORIZONTAL][MAX_VERTICAL];

	// Prac 1
	GameBoard * m_gameboard;
	float m_fDelay;
};

#endif // __GAME_SCENE_H__
