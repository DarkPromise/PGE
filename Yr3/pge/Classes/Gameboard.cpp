#include "Gameboard.h"

GameBoard::GameBoard()
: m_eBoardState(BOARD_CREATING)
{
	// Set Gameboard Background
	auto gameboardbg = Sprite::create("background.png");
	gameboardbg->setScale(3.2f);
	this->addChild(gameboardbg, -1);

	// Create Dummy Array
	for (int i = 0; i < MAX_HORIZONTAL; i++)
	{
		for (int j = 0; j < MAX_VERTICAL; j++)
		{
			m_gemArray[i][j] = nullptr;
		}
	}

	// Allow Gameboard Updates
	this->scheduleUpdate();
}

GameBoard::~GameBoard()
{

}

void GameBoard::update(float dt)
{
	static float updateDelay = 0.0;
	updateDelay += dt;
	switch (m_eBoardState)
	{
	case BOARD_CREATING:
		// Initial State on GameBoard Creation
		break;
	case BOARD_NORMAL:
		this->CheckBoardStatus();
		break;
	case BOARD_UPDATING:
		this->UpdateGemPositions();
		break;
	case BOARD_PAUSE:
		break;
	}
}

void GameBoard::Init()
{
	for (int i = 0; i < MAX_HORIZONTAL; i++)
	{
		for (int j = 0; j < MAX_VERTICAL; j++)
		{
			Gems * gem = new Gems(i,j);
			this->addChild(gem, 0);
			m_gemArray[i][j] = gem;
		}
	}
	this->m_eBoardState = BOARD_NORMAL;
}

void GameBoard::CheckBoardStatus()
{
	// if Any gems are in Animation or Update, dont do anything
	for (int x = 0; x < MAX_HORIZONTAL; x++)
	{
		for (int y = 0; y < MAX_VERTICAL; y++)
		{
			/*if(!this->CheckLowerX(x, y))
			{
				for (int i = 0; i < 3; i++)
				{
					if (m_gemArray[x-i][y] != nullptr)
					{
						m_gemArray[x-i][y]->getSprite()->removeFromParent();
						m_gemArray[x-i][y] = nullptr;
					}
				}
				m_eBoardState = BOARD_PAUSE;
			}
			if(!this->CheckLowerY(x, y))
			{
				for (int i = 0; i < 3; i++)
				{
					if (m_gemArray[x][y-i] != nullptr)
					{
						m_gemArray[x][y-i]->getSprite()->removeFromParent();
						m_gemArray[x][y-i] = nullptr;
					}
				}
				m_eBoardState = BOARD_PAUSE;
			}*/

			// There is an empty gem slot
			if (m_gemArray[x][y] == nullptr)
			{
				this->m_eBoardState = BOARD_UPDATING;
				return;
			}

			switch (m_gemArray[x][y]->getGemAnimateStatus())
			{
			case Gems::E_ANIMATE_DROPPING:
				this->m_eBoardState = BOARD_UPDATING;
				//MessageBox("Gem in Animation", "DROPPING");
				return;
				break;
			case Gems::E_ANIMATE_SLIDING:
				this->m_eBoardState = BOARD_UPDATING;
				//MessageBox("Gem in Animation", "SLIDING");
				return;
				break;
				
			}
		}
	}
	this->m_eBoardState = BOARD_NORMAL;
}

bool GameBoard::CheckLowerX(int x , int y)
{
	if (x < 2)
	{
		return true;
	}

	for (int i = 1; i < 3; i++)
	{
		if (m_gemArray[x][y] != nullptr && m_gemArray[x-i][y] != nullptr)
		{
			if (m_gemArray[x][y]->getGemType() != m_gemArray[x - i][y]->getGemType())
			{
				return true;
			}
		}
	}
	return false;
}

bool GameBoard::CheckLowerY(int x , int y)
{
	if (y < 2)
	{
		return true;
	}
	for (int i = 1; i < 3; i++)
	{
		if (m_gemArray[x][y] != nullptr && m_gemArray[x][y - i] != nullptr)
		{
			if (m_gemArray[x][y]->getGemType() != m_gemArray[x][y - i]->getGemType())
			{
				return true;
			}
		}
	}
	return false;
}

void GameBoard::UpdateGemPositions()
{ 
	// IMPORTANT NOTE : Gems does checking in positive X and Y format
	for (int x = 0; x < MAX_HORIZONTAL; x++)
	{
		for (int y = 0; y < MAX_VERTICAL; y++)
		{
			if (y < 9) // Creation of gems at layer 10 will be done using another function
			{
				if (m_gemArray[x][y] == nullptr) // Gem does not exist
				{
					// Check area above Gem for Existing Gem
					if (m_gemArray[x][y + 1] != nullptr)
					{
						// Variables
						auto oldGem = m_gemArray[x][y + 1];
						auto oldSprite = oldGem->getSprite();
						auto oldPos = oldSprite->getPosition();
						auto visibleSize = oldSprite->getContentSize();

						// X position does not change
						auto newPosY = visibleSize.height * 0.5f + (y - 5) * oldSprite->getContentSize().height;

						// Create Animation Command
						auto moveTo = MoveTo::create(0.1f, Vec2(oldPos.x, newPosY));

						// Update Gem Array
						m_gemArray[x][y] = m_gemArray[x][y + 1];
						m_gemArray[x][y + 1] = nullptr;

						// Run Animation
						auto animSeq = Sequence::create(moveTo, nullptr);
						oldSprite->runAction(animSeq);
					}
					else
					{
						continue;
					}
				}
				else
				{
					switch (m_gemArray[x][y]->getGemAnimateStatus())
					{
					case Gems::E_ANIMATE_DROPPING:
						this->m_eBoardState = BOARD_UPDATING;
						// MessageBox("Gem in Animation", "ANIMATE");
						return;
						break;
					case Gems::E_ANIMATE_SLIDING:
						this->m_eBoardState = BOARD_UPDATING;
						// MessageBox("Gem in Animation", "ANIMATE");
						return;
						break;
					}
				}
			}
			else // y = 9
			{
				if (m_gemArray[x][y] == nullptr)
				{
					// Set Pause State
					this->m_eBoardState = BOARD_PAUSE;

					// Create a new gem
					Gems * newGem = new Gems(x,y,true);
					this->addChild(newGem, 0);
					m_gemArray[x][y] = newGem;

					auto newSprite = newGem->getSprite();
					auto visibleSize = newGem->getSprite()->getContentSize();

					// X position does not change
					auto newPosY = visibleSize.height * 0.5f + (y - 5) * newSprite->getContentSize().height;

					// Create Animation Command
					auto moveTo = MoveTo::create(0.1f, Vec2(newSprite->getPositionX(), newPosY));

					// Create Continue Command
					auto continueUpdate = CallFunc::create([this]
					{
						this->CheckBoardStatus();
					});

					// Run Sequence
					auto animSeq = Sequence::create(moveTo,continueUpdate,nullptr);
					newSprite->runAction(animSeq);
				}
			}
		}
	}
}

void GameBoard::RemoveHorizontalRow(int y)
{
	// Should be checking Gem State instead
	if (m_eBoardState != BOARD_PAUSE)
	{
		for (int i = 0; i < 10; i++)
		{
			if (m_gemArray[i][y] == nullptr)
			{
				continue;
			}
			m_gemArray[i][y]->getSprite()->removeFromParent();
			m_gemArray[i][y] = nullptr;
		}
	}
}

void GameBoard::RemoveVerticalRow(int x)
{
	if (m_eBoardState != BOARD_PAUSE)
	{
		for (int i = 0; i < 10; i++)
		{
			if (m_gemArray[x][i] == nullptr)
			{
				continue;
			}
			m_gemArray[x][i]->getSprite()->removeFromParent();
			m_gemArray[x][i] = nullptr;
		}
	}
}
