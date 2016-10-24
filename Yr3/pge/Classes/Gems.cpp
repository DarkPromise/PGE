#include "Gems.h"

static const char* const g_scGemFileName[Gems::E_GEM_TOTAL] = { "blue.png","green.png","orange.png","purple.png","red.png","white.png","yellow.png","empty.png" };

Gems::Gems()
: m_eGemType(E_NONE)
, m_eAnimate(E_ANIMATE_NONE)
, m_eAnimateDir(E_DIRECTION_NONE)
{
}

Gems::Gems(int x, int y, bool newGem)
: m_eGemType((Gems::E_GEM_TYPES)cocos2d::random(0, (int)Gems::E_GEM_TOTAL - 2))
, m_eAnimate(E_ANIMATE_NONE)
, m_eAnimateDir(E_DIRECTION_NONE)
{
	if (FileUtils::getInstance()->isDirectoryExist("Icons"))
	{
		std::stringstream ss;
		ss << "Icons/" << g_scGemFileName[m_eGemType];
		this->m_Sprite = Sprite::create(ss.str());
		auto visibleSize = this->getContentSize();
		if (!newGem)
		{

			this->m_Sprite->setPosition(Vec2(
				visibleSize.width * 0.5f + (x - 5) * m_Sprite->getContentSize().width + (m_Sprite->getContentSize().width * 0.5f),
				visibleSize.height * 0.5f + (y - 5) * m_Sprite->getContentSize().height + (m_Sprite->getContentSize().height * 0.5f)
			));
		}
		else
		{
			this->m_Sprite->setPosition(Vec2(
				visibleSize.width * 0.5f + (x - 5) * m_Sprite->getContentSize().width + (m_Sprite->getContentSize().width * 0.5f),
				visibleSize.height * 0.5f + (y - 4) * m_Sprite->getContentSize().height + (m_Sprite->getContentSize().height * 0.5f)
			));
		}
#if _DEBUG
		/*std::stringstream ss1;
		ss1 << "x" << x << "y" << y;
		auto text = Label::createWithTTF(ss1.str(), "fonts/arial.ttf", 18);
		text->setColor(Color3B(255, 255, 255));
		text->enableOutline(Color4B(0, 0, 0, 255), 3);
		text->setPosition(Vec2(
			m_Sprite->getContentSize().width * 0.5f, 
			m_Sprite->getContentSize().height * 0.5f
		));
		m_Sprite->addChild(text, 1);
		this->addChild(m_Sprite);*/

		/*std::stringstream ss1;
		ss1 << "[" << m_Sprite->getPosition().x << "," << m_Sprite->getPosition().y << "]";
		auto text = Label::createWithTTF(ss1.str(), "fonts/arial.ttf", 12);
		text->setColor(Color3B(255, 255, 255));
		text->enableOutline(Color4B(0, 0, 0, 255), 3);
		text->setPosition(Vec2(
			m_Sprite->getContentSize().width * 0.5f,
			m_Sprite->getContentSize().height * 0.5f
		));
		m_Sprite->addChild(text, 1);
		this->addChild(m_Sprite);*/

		std::stringstream ss1;
		ss1 << "Type " << m_eGemType;
		auto text = Label::createWithTTF(ss1.str(), "fonts/arial.ttf", 18);
		text->setColor(Color3B(255, 255, 255));
		text->enableOutline(Color4B(0, 0, 0, 255), 3);
		text->setPosition(Vec2(
			m_Sprite->getContentSize().width * 0.5f,
			m_Sprite->getContentSize().height * 0.5f
		));
		m_Sprite->addChild(text, 1);
		this->addChild(m_Sprite);
#endif
	}
	else
	{
		MessageBox("Directory \"Icons\" does not exist!", "ERROR");
	}
}

Gems::~Gems()
{
	if (m_Sprite)
	{
		m_Sprite->release();
	}
}

void Gems::Init(E_GEM_TYPES e, USHORT x, USHORT y)
{
	this->m_eGemType = e;

	if (FileUtils::getInstance()->isDirectoryExist("Icons"))
	{
		std::stringstream ss;
		ss << "Icons/" << g_scGemFileName[m_eGemType];
		this->m_Sprite = Sprite::create(ss.str());
		auto visibleSize = this->getParent()->getContentSize();
		this->m_Sprite->setPosition(Vec2(
			visibleSize.width * 0.5 + (x - 5) * m_Sprite->getContentSize().width + (m_Sprite->getContentSize().width * 0.5f), 
			visibleSize.height * 0.5 + (y - 5) * m_Sprite->getContentSize().height + (m_Sprite->getContentSize().height * 0.5f)
		));
#if _DEBUG
		std::stringstream ss1;
		ss1 << "x" << x << "y" << y;
		auto text = Label::createWithTTF(ss1.str(), "fonts/arial.ttf", 18);
		text->setColor(Color3B(255, 255, 255));
		text->enableOutline(Color4B(0, 0, 0, 255), 3);
		text->setPosition(Vec2(
			m_Sprite->getContentSize().width * 0.5f,
			m_Sprite->getContentSize().height * 0.5f
		));
		m_Sprite->addChild(text, 1);
		this->addChild(m_Sprite);
#endif
	}
	else
	{
		MessageBox("Directory \"Icons\" does not exist!", "ERROR");
	}
}
