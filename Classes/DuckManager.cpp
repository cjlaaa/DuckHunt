//
//  DuckManager.cpp
//  DuckHunt
//
//  Created by hENRYcHANG on 14-10-14.
//
//

#include "DuckManager.h"

DHDuckManager* DHDuckManager::create()
{
    DHDuckManager *pRet = new DHDuckManager();
    if (pRet && pRet->Init())
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

bool DHDuckManager::Init()
{
    for (int i=0; i < DUCK_TYPE_NUM; i++)
    {
        m_nDuckCDCount[i] = DuckDataBase[i].nCD;
    }
    return false;
}

void DHDuckManager::Loop()
{
    for (int i = 0; i < DUCK_TYPE_NUM; i++)
    {
        if (m_nDuckCDCount[i]==0)
        {
            m_nDuckCDCount[i] = DuckDataBase[i].nCD;
            CreateDuck(i);
        }
        else
        {
            m_nDuckCDCount[i]--;
        }
    }
}

void DHDuckManager::CreateDuck(int nDuckIndex)
{
    DuckData Info = DuckDataBase[nDuckIndex];
    //初始位置
    Info.StartPos = Vec2(0,100);
    //目标位置
    Info.TargetPos = Vec2(200,200);
    
    SendMsg(MsgDuckCreate,&Info,sizeof(Info));
}