//
//  Duck.cpp
//  DuckHunt
//
//  Created by hENRYcHANG on 14-10-14.
//
//

#include "Duck.h"

DHDuck* DHDuck::create(const std::string& filename, DuckData data)
{
    DHDuck *pRet = new DHDuck();
    if (pRet && pRet->Init(filename , data))
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

bool DHDuck::Init(const std::string& filename , DuckData data)
{
    CCASSERT(initWithFile(filename)==false,"DHDuck::Init initWithFile Error!");
    SetReceiver(dynamic_cast<Receiver*>(getParent()));
    m_Data = data;
    return false;
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
    Info.pSelf = this;
    SendMsg(MsgDuckDisappear,&Info,sizeof(Info));
}

void DHDuck::Dead()
{
    if (m_Data.nHp < 1)
        Disappear();
}