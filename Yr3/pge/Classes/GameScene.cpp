#include "GameScene.h"
#include "SimpleAudioEngine.h"

Scene* Game::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = Game::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Default Values
	m_eState = E_NORMAL;
	m_fDelay = 0.f;

	// Create Listeners
	this->createListeners();
	
	// Set Background Color 
	auto background = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(background, -1);

	// Create Title 
	auto test = Label::createWithTTF("Game Mode", "fonts/arial.ttf", 24);
	test->setName("test");
	test->setColor(Color3B(255, 255, 255));
	test->enableOutline(Color4B(0, 0, 0, 255), 2);
	test->setPosition(Vec2(Director::getInstance()->getVisibleSize().width * 0.5f, (Director::getInstance()->getVisibleSize().height * 0.955f)));
	auto fadein = FadeIn::create(0.6f);
	auto fadeout = FadeOut::create(0.6f);
	auto animSeq = Sequence::create(fadeout, fadein, nullptr);
	test->runAction(RepeatForever::create(animSeq));
	this->addChild(test, 1);

	// Create GameBoard
	this->createGameBoard();

#if _DEBUG
	auto gameboardStatus = Label::createWithTTF("Game Status", "fonts/arial.ttf", 18);
	gameboardStatus->setName("Gameboard Status");
	gameboardStatus->setColor(Color3B(255, 255, 255));
	gameboardStatus->enableOutline(Color4B(0, 0, 0, 255), 2);
	gameboardStatus->setPosition(Vec2(Director::getInstance()->getVisibleSize().width * 0.1f, (Director::getInstance()->getVisibleSize().height * 0.1f)));
	this->addChild(gameboardStatus, 1);
#endif

	// Create UI
	this->createUI();

	// Updates
	this->scheduleUpdate();

	return true;
}

void Game::update(float dt)
{
	m_fDelay += dt;
	m_gameboard->update(dt);

#if _DEBUG
	auto gbState = dynamic_cast<Label*>(this->getChildByName("Gameboard Status"));
	if(gbState)
	{
		std::stringstream ss;
		switch (m_gameboard->getBoardState())
		{
		case GameBoard::BOARD_CREATING:
			ss << "Gameboard : Creating";
			break;
		case GameBoard::BOARD_NORMAL:
			ss << "Gameboard : Normal";
			break;
		case GameBoard::BOARD_UPDATING:
			ss << "Gameboard : Updating";
			break;
		case GameBoard::BOARD_PAUSE:
			ss << "Gameboard : Pause";
			break;
		}
		gbState->setString(ss.str());
	}
#endif
}

void Game::createGameBoard()
{
	this->m_gameboard = new GameBoard();
	this->m_gameboard->setName("Gameboard");
	this->m_gameboard->setScale(1.f);
	this->m_gameboard->setPosition(Vec2(Director::getInstance()->getVisibleSize().width * 0.65f, Director::getInstance()->getVisibleSize().height * 0.5f));
	this->m_gameboard->Init();
	this->addChild(m_gameboard, 0);
}

void Game::createUI()
{
	auto uiNode = Node::create();
	uiNode->setName("UI");

	// UI Background
	/*auto uiSprite = Sprite::create("background.png");
	uiSprite->setName("UI background");
	uiSprite->setScaleX(1.5f);
	uiSprite->setScaleY(3.f);
	uiSprite->setPosition(Vec2(uiSprite->getContentSize().width * 0.5f, (Director::getInstance()->getVisibleSize().height * 0.5f)));
	uiNode->addChild(uiSprite, -1);*/

	// Score
	auto uiSprite = Sprite::create("UI/score.png");
	uiSprite->setName("score UI");
	uiSprite->setScale(0.8f);
	uiSprite->setPosition(Vec2(Director::getInstance()->getVisibleSize().width * 0.15f, (Director::getInstance()->getVisibleSize().height * 0.8f)));

	auto name = Label::createWithTTF("Score Placeholder", "fonts/arial.ttf", 24);
	name->setName("score value");
	name->setColor(Color3B(255, 255, 255));
	name->enableOutline(Color4B(0, 0, 0, 255), 2);
	name->setPosition(Vec2(uiSprite->getContentSize().width * 0.5f, uiSprite->getContentSize().height * 0.5f));
	uiSprite->addChild(name, 1);

	uiNode->addChild(uiSprite, 1);

	this->addChild(uiNode, 1);
}

void Game::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Game::createListeners()
{
	// Create Keyboard Listener
	auto kListener = EventListenerKeyboard::create();
	kListener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPressed, this);
	kListener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(kListener, this);

	// Create Mouse Listener
	auto mListener = EventListenerMouse::create();
	mListener->onMouseMove = CC_CALLBACK_1(Game::onMouseMove, this);
	mListener->onMouseUp = CC_CALLBACK_1(Game::onMouseUp, this);
	mListener->onMouseDown = CC_CALLBACK_1(Game::onMouseDown, this);
	mListener->onMouseScroll = CC_CALLBACK_1(Game::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mListener, this);
}

void Game::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		this->menuCloseCallback(this);
		break;
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		break;
	case EventKeyboard::KeyCode::KEY_P:
		// TODO
		// Should be GameBoard->pause();
		if (!Director::getInstance()->isPaused())
		{
			Director::getInstance()->pause();
		}
		else
		{
			Director::getInstance()->resume();
		}
		break;
	case EventKeyboard::KeyCode::KEY_1:
		this->m_gameboard->RemoveHorizontalRow(5);
		break;
	case EventKeyboard::KeyCode::KEY_2:
		this->m_gameboard->RemoveVerticalRow(0);
		break;
	}
}

void Game::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	
}

void Game::onMouseMove(cocos2d::Event * event)
{

}

void Game::onMouseUp(cocos2d::Event * event)
{

}

void Game::onMouseDown(cocos2d::Event * event)
{

}

void Game::onMouseScroll(cocos2d::Event * event)
{

}