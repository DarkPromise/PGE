#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

// Game Scenes
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Set Background Color 
	auto background = cocos2d::LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(background, -1);

	// Create Listeners
	this->createListeners();
	
	// Create Title 
	auto title = Label::createWithTTF("Main Menu", "fonts/arial.ttf", 48);
	title->setName("Main Menu");
	title->setColor(Color3B(255, 255, 255));
	title->enableOutline(Color4B(0, 0, 0, 255), 3);
	title->setPosition(Vec2(Director::getInstance()->getVisibleSize().width * 0.5f, (Director::getInstance()->getVisibleSize().height * 0.9f)));
	this->addChild(title, 1);

	// Create Menu Buttons
	this->createMenuButtons();

	// Enable Update Overrides
	this->scheduleUpdate();

	return true;
}

void MainMenu::update(float dt)
{

}

void MainMenu::createMenuButtons()
{
	auto menuNode = Node::create();
	menuNode->setName("Menu");
	this->addChild(menuNode);

	// Start
	auto button = ui::Button::create("UI/ButtonNormal.png", "UI/ButtonPressed.png", "UI/ButtonPressed.png");
	button->setName("Start Button");
	button->setTitleText("Start");
	button->setScale(0.75f);
	button->setTitleColor(Color3B(0, 0, 0));
	button->setTitleFontName("fonts/arial.ttf");
	button->setTitleFontSize(32.f);
	button->setPosition(Vec2(Director::getInstance()->getVisibleSize().width * 0.5f, (Director::getInstance()->getVisibleSize().height * 0.5f)));
	button->addTouchEventListener([&](Ref * sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(TransitionFade::create(1.f, Game::createScene(), Color3B(0, 0, 0)));
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});
	menuNode->addChild(button);
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainMenu::createListeners()
{
	// Create Keyboard Listener
	auto kListener = EventListenerKeyboard::create();
	kListener->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
	kListener->onKeyReleased = CC_CALLBACK_2(MainMenu::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(kListener, this);

	// Create Mouse Listener
	auto mListener = EventListenerMouse::create();
	mListener->onMouseMove = CC_CALLBACK_1(MainMenu::onMouseMove, this);
	mListener->onMouseUp = CC_CALLBACK_1(MainMenu::onMouseUp, this);
	mListener->onMouseDown = CC_CALLBACK_1(MainMenu::onMouseDown, this);
	mListener->onMouseScroll = CC_CALLBACK_1(MainMenu::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mListener, this);
}

void MainMenu::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		this->menuCloseCallback(this);
		break;
	case EventKeyboard::KeyCode::KEY_1:
		auto gameScene = Game::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.f, gameScene, Color3B(0, 0, 0)));
		break;
	}
}

void MainMenu::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	
}

void MainMenu::onMouseMove(cocos2d::Event * event)
{

}

void MainMenu::onMouseUp(cocos2d::Event * event)
{

}

void MainMenu::onMouseDown(cocos2d::Event * event)
{

}

void MainMenu::onMouseScroll(cocos2d::Event * event)
{

}