#ifndef __GEMS_H__
#define __GEMS_H__

// Cocos2d
#include "cocos2d.h"

USING_NS_CC;

// Required
#include <iostream>
#include <string>
#include <sstream>

#define MAX_HORIZONTAL 10
#define MAX_VERTICAL 10

class Gems : public cocos2d::Node
{
public:
	enum E_GEM_TYPES
	{
		E_BLUE,
		E_GREEN,
		E_ORANGE,
		E_PURPLE,
		E_RED,
		E_WHITE,
		E_YELLOW,
		E_NONE,
		E_GEM_TOTAL,
	};
	
	enum E_GEM_ANIMATION
	{
		E_ANIMATE_DROPPING,
		E_ANIMATE_SLIDING,
		E_ANIMATE_NONE,
	};

	enum E_GEM_ANIMATION_DIRECTION
	{
		E_ANIMATE_RIGHT,
		E_ANIMATE_LEFT,
		E_DIRECTION_NONE,
	};

	Gems();
	Gems(int, int, bool n = false);
	virtual ~Gems();

	void Init(E_GEM_TYPES e, USHORT x, USHORT y);

public:
	// Set & Get Functions
	cocos2d::Sprite * getSprite() { return m_Sprite; }
	E_GEM_TYPES getGemType() { return m_eGemType; }

	E_GEM_ANIMATION getGemAnimateStatus() { return m_eAnimate; }
	E_GEM_ANIMATION_DIRECTION getGemAnimateDirection() { return m_eAnimateDir; }
private:
	cocos2d::Sprite * m_Sprite;
	E_GEM_TYPES m_eGemType;
	E_GEM_ANIMATION m_eAnimate;
	E_GEM_ANIMATION_DIRECTION m_eAnimateDir;
};

#endif