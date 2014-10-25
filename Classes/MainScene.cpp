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

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(DHMainScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);

    auto sprite = Sprite::create("HelloWorld.png");

    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(sprite, 0);
     
    scheduleUpdate();
    
    //初始化管理器
    m_pManager = DHDuckManager::create(this);
    m_pManager->retain();

    return true;
}

void DHMainScene::update(float fT)
{
    m_pManager->Loop();
    for (auto& pDuck : m_vecDucks)
    {
        ((DHDuck*)pDuck)->Loop();
    }
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
