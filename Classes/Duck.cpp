//
//  Duck.cpp
//  DuckHunt
//
//  Created by hENRYcHANG on 14-10-14.
//
//

#include "Duck.h"

DHDuck* DHDuck::create()
{
    DHDuck *pRet = new DHDuck();
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

bool DHDuck::Init()
{
    return false;
}
