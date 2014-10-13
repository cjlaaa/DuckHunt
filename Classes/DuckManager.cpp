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
    return false;
}
