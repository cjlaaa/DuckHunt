#include "MainScene.h"

USING_NS_CC;

Scene* DHMainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = DHMainScene::create();
    scene->addChild(layer);
    return scene;
}

bool DHMainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create("CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(DHMainScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 , origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
     
    scheduleUpdate();
    
    //初始化管理器
    m_pManager = DHDuckManager::create(this);
    m_pManager->retain();

    m_nLoseCount = 0;
    m_nScore = 0;
    //分数标签
    auto pScore = LabelAtlas::create("0123456789", "fonts/tuffy_bold_italic-charmap.plist");
    addChild(pScore,enZOrderFront,enTagLabelScore);
    pScore->setPosition(visibleSize.width*0.99,visibleSize.height*0.99);
    pScore->setAnchorPoint(Vec2(1,1));
    //漏掉数量标签
    auto pLoseCount = LabelAtlas::create("0123456789", "fonts/tuffy_bold_italic-charmap.plist");
    addChild(pLoseCount,enZOrderFront,enTagLabelLoseCount);
    pLoseCount->setPosition(pScore->getPositionX(),pScore->getPositionY()-pScore->getContentSize().height);
    pLoseCount->setAnchorPoint(Vec2(1,1));
    
    //初始化触摸
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener1 = EventListenerTouchAllAtOnce::create();
    listener1->onTouchesBegan = CC_CALLBACK_2(DHMainScene::onTouchesBegan,this);
    listener1->onTouchesMoved = CC_CALLBACK_2(DHMainScene::onTouchesMoved,this);
    listener1->onTouchesEnded = CC_CALLBACK_2(DHMainScene::onTouchesEnded,this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener1,this);

    return true;
}

void DHMainScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    for (auto& pDuck : m_vecDucks)
    {
        for (auto& pTouch : touches)
        {
            if (pDuck->getBoundingBox().containsPoint(pTouch->getLocation()))
            {
                structDuckDisappear Info;
                Info.pDuck = (DHDuck*)pDuck;
                DuckDisappear(&Info);
                m_nScore++;
            }
        }
    }
}
void DHMainScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}
void DHMainScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
    
}

void DHMainScene::update(float fT)
{
    m_pManager->Loop();
    for (auto& pDuck : m_vecDucks)
    {
        ((DHDuck*)pDuck)->Loop();
    }
    
    LabelAtlas* pScore = dynamic_cast<LabelAtlas*>(getChildByTag(enTagLabelScore));
    CCASSERT(pScore!=NULL,"Get Label Error!");
    pScore->setString(CCString::createWithFormat("%d",m_nScore)->getCString());
    
    LabelAtlas* pLoseCount = dynamic_cast<LabelAtlas*>(getChildByTag(enTagLabelLoseCount));
    CCASSERT(pLoseCount!=NULL,"Get Label Error!");
    pLoseCount->setString(CCString::createWithFormat("%d",m_nLoseCount)->getCString());
}

void DHMainScene::OnMsgReceive(MsgToMainScene nMsg,void* pData,int nSize)
{
    switch (nMsg)
    {
        case MsgDuckDisappear:
        {
            CCASSERT(sizeof(structDuckDisappear)==nSize, "sizeof(MsgDuckDisappear)!=nSize");
            DuckDisappear((structDuckDisappear*)pData);
        }
            break;
        case MsgDuckCreate:
        {
            CCASSERT(sizeof(structDuckCreate)==nSize, "sizeof(structDuckCreate)!=nSize");
            DuckCreate((structDuckCreate*)pData);
        }
        case MsgDuckLose:
        {
            m_nLoseCount++;
        }
            break;
        default:
            break;
    }
}

void DHMainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void DHMainScene::DuckCreate(structDuckCreate* pData)
{
    DHDuck* pDuck = DHDuck::CreateDuck("CloseNormal.png",pData->DuckInfo,this);
    CCASSERT(pDuck!=NULL, "Duck Create Error!");
    addChild(pDuck);
    m_vecDucks.pushBack(pDuck);
}

void DHMainScene::DuckDisappear(structDuckDisappear* pData)
{
    m_vecDucks.eraseObject(pData->pDuck);
    removeChild(pData->pDuck);
}
