#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include "cocos2d.h"

USING_NS_CC;

#include "Gems.h"

class GameBoard : public cocos2d::Node
{
public:
	enum BOARD_STATE
	{
		BOARD_CREATING,
		BOARD_NORMAL,
		BOARD_UPDATING,
		BOARD_PAUSE,
	};
public:
	GameBoard();
	virtual ~GameBoard();
	virtual void update(float);

	// Main Functions
	void Init();
	void CheckBoardStatus();
	bool CheckLowerX(int, int);
	bool CheckLowerY(int, int);
	void UpdateGemPositions();

	// Test Functions
	void RemoveVerticalRow(int);
	void RemoveHorizontalRow(int);

	// Set & Get Functions
	void setBoardState(BOARD_STATE state) { m_eBoardState = state; }
	BOARD_STATE getBoardState() { return m_eBoardState; }

private:
	BOARD_STATE m_eBoardState;
	Gems * m_gemArray[MAX_HORIZONTAL][MAX_VERTICAL];
};

#endif