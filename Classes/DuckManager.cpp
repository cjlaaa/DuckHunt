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
    //这里的代码是为了防止目标点与起始点在一条边上,写的很烂,但总算没有两点在一条边上的情况了...
    //这只是看效果用的,不要在意这些细节...
    float nStartBorder = CCRANDOM_0_1()*10;
    //0-3分别表示下,右,上,左
    int nStartBorderType = 0;
    if (nStartBorder<2)
    {
        Data.StartPos = Vec2(CCRANDOM_0_1()*visibleSize.width,0);
        nStartBorderType = 0;
    }
    else if(nStartBorder<5)
    {
        Data.StartPos = Vec2(visibleSize.width,visibleSize.height*CCRANDOM_0_1());
        nStartBorderType = 1;
    }
    else if (nStartBorder<7)
    {
        Data.StartPos = Vec2(CCRANDOM_0_1()*visibleSize.width,visibleSize.height);
        nStartBorderType = 2;
    }
    else
    {
        Data.StartPos = Vec2(0,CCRANDOM_0_1()*visibleSize.height);
        nStartBorderType = 3;
    }
    
    int nTargetBorderType = -1;
    while (true) {
        //计算目标位置所在边
        float nTargetPos = CCRANDOM_0_1()*10;
        if (nTargetPos<2)
        {
            Data.TargetPos = Vec2(CCRANDOM_0_1()*visibleSize.width,0);
            nTargetBorderType = 0;
        }
        else if(nTargetPos<5)
        {
            Data.TargetPos = Vec2(visibleSize.width,visibleSize.height*CCRANDOM_0_1());
            nTargetBorderType = 1;
        }
        else if (nTargetPos<7)
        {
            Data.TargetPos = Vec2(CCRANDOM_0_1()*visibleSize.width,visibleSize.height);
            nTargetBorderType = 2;
        }
        else
        {
            Data.TargetPos = Vec2(0,CCRANDOM_0_1()*visibleSize.height);
            nTargetBorderType = 3;
        }
        if (nTargetBorderType==nStartBorderType) continue; else break;
    }
    

    structDuckCreate Info;
    Info.DuckInfo = Data;
    
    SendMsg(MsgDuckCreate,&Info,sizeof(Info));
}