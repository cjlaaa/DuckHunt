//
//  PublicDef.cpp
//  DuckHunt
//
//  Created by hENRYcHANG on 14/11/30.
//
//

#include "PublicDef.h"

static DHUtils* s_UtilsManager = NULL;

DHUtils* DHUtils::getInstance()
{
    if (s_UtilsManager == nullptr)
    {
        s_UtilsManager = new DHUtils();
    }
    return s_UtilsManager;
}

int DHUtils::GetRandom(int nRange,bool bFromZero)
{
    CCRANDOM_0_1();
    int nResult = rand() % nRange;
    
    if (bFromZero)          return nResult;
    else                    return nResult + 1;
}