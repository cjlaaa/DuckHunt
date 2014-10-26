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
    setPosition(m_Data.StartPos);
    
    runAction(Sequence::create(MoveTo::create(m_Data.nAliveTime, m_Data.TargetPos),
                               CallFunc::create(CC_CALLBACK_0(DHDuck::Disappear,this)),
                               NULL));
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
    
}

void DHDuck::Disappear()
{
    struct structDuckDisappear Info;
    Info.pDuck = this;
    SendMsg(MsgDuckDisappear,&Info,sizeof(Info));
    SendMsg(MsgDuckLose);
}

void DHDuck::Dead()
{
    if (m_Data.nHp < 1)
        Disappear();
}