//
//  DuckManager.cpp
//  DuckHunt
//
//  Created by hENRYcHANG on 14-10-14.
//
//

#include "DuckManager.h"

DHDuckManager* DHDuckManager::create(Receiver* pNode)
{
    DHDuckManager *pRet = new DHDuckManager();
    if (pRet && pRet->Init(pNode))
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

bool DHDuckManager::Init(Receiver* pNode)
{
    m_pReceiver = pNode;
    
    for (int i=0; i < DUCK_TYPE_NUM; i++)
    {
        m_nDuckCDCount[i] = DuckDataBase[i].nCD;
    }

    return true;
}

void DHDuckManager::Loop()
{
    for (int i = 0; i < DUCK_TYPE_NUM; i++)
    {
        if (m_nDuckCDCount[i]<0)
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
    DuckData Data = DuckDataBase[nDuckIndex];
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //计算初始位置所在边
    //这里的代码是为了防止目标点与起始点在一条边上,写的很烂,而且还是有两点在一条边上的情况,但这只是看效果用的,不要在意这些细节...
    float nStartBorder = CCRANDOM_0_1()*10;
    //0-3分别表示下,右,上,左
    int nBorderType = 0;
    if (nStartBorder<2)
    {
        Data.StartPos = Vec2(CCRANDOM_0_1()*visibleSize.width,0);
        nBorderType = 0;
    }
    else if(nStartBorder<5)
    {
        Data.StartPos = Vec2(visibleSize.width,visibleSize.height*CCRANDOM_0_1());
        nBorderType = 1;
    }
    else if (nStartBorder<7)
    {
        Data.StartPos = Vec2(CCRANDOM_0_1()*visibleSize.width,visibleSize.height);
        nBorderType = 2;
    }
    else
    {
        Data.StartPos = Vec2(0,CCRANDOM_0_1()*visibleSize.height);
        nBorderType = 3;
    }
    
    while (true) {
        //计算目标位置所在边
        float nTargetPos = CCRANDOM_0_1()*10;
        if (nTargetPos<2)
        {
            Data.TargetPos = Vec2(CCRANDOM_0_1()*visibleSize.width,0);
            if (nBorderType==0) continue; else break;
        }
        else if(nTargetPos<5)
        {
            Data.TargetPos = Vec2(visibleSize.width,visibleSize.height*CCRANDOM_0_1());
            if (nBorderType==1) continue; else break;
        }
        else if (nTargetPos<7)
        {
            Data.TargetPos = Vec2(CCRANDOM_0_1()*visibleSize.width,visibleSize.height);
            if (nBorderType==2) continue; else break;
        }
        else
        {
            Data.TargetPos = Vec2(0,CCRANDOM_0_1()*visibleSize.height);
            if (nTargetPos==3) continue; else break;
        }
    }
    

    structDuckCreate Info;
    Info.DuckInfo = Data;
    
    SendMsg(MsgDuckCreate,&Info,sizeof(Info));
}