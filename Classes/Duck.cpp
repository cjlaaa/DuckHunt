//
//  Duck.cpp
//  DuckHunt
//
//  Created by hENRYcHANG on 14-10-14.
//
//

#include "Duck.h"

DHDuck* DHDuck::CreateDuck(const std::string& filename, DuckData data,Receiver* pReceiver)
{
    DHDuck *pRet = new DHDuck();
    if (pRet && pRet->Init(filename , data , pReceiver))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool DHDuck::Init(const std::string& filename , DuckData data,Receiver* pReceiver)
{
    CCASSERT(initWithFile(filename),"DHDuck::Init initWithFile Error!");
    SetReceiver(pReceiver);
    m_Data = data;
    m_bIsDead = false;
    setPosition(m_Data.StartPos);
    cocos2d::Node::setScale(0.3f);
    
//    runAction(Sequence::create(MoveTo::create(m_Data.nSpeed, m_Data.TargetPos),CallFunc::create(CC_CALLBACK_0(DHDuck::Disappear,this)),NULL));
    return true;
}

void DHDuck::Loop()
{
    Move();
    Dead();
}

void DHDuck::Hurt()
{
    m_Data.nHp--;
}

void DHDuck::Move()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    if (!m_bIsDead)
    {
        //向右移动
        if (m_Data.bMoveRight)
        {
            setPositionX(getPositionX()+m_Data.nSpeed);
        }
        else    //向左移动
        {
            setPositionX(getPositionX()-m_Data.nSpeed);
        }
        setPositionY(sin(getPositionX() / visibleSize.width * 10) * visibleSize.height * 0.05 + m_Data.TargetPos.y);
    }
    
    //消失判断
    if (getPositionX() > visibleSize.width || getPositionX() < 0)
    {
        Disappear();
    }
}

void DHDuck::Disappear()
{
    struct structDuckDisappear Info;
    Info.pDuck = this;
    SendMsg(MsgDuckDisappear,&Info,sizeof(Info));
    //SendMsg(MsgAddScore);
}

void DHDuck::Dead()
{
    if (m_Data.nHp < 1)
    {
        m_bIsDead = true;
        Disappear();
    }
}