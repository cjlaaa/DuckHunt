//
//  SuperCombo.cpp
//  DuckHunt
//
//  Created by hENRYcHANG on 14/11/26.
//
//

#include "SuperCombo.h"

#define MAX_TIMER 10

CSuperCombo::CSuperCombo()
{
    m_nTimer = MAX_TIMER;
    m_nComboCount = 0;
}

void CSuperCombo::Hit(int nScore)
{
    m_nTimer = MAX_TIMER;
    m_nComboCount += nScore;
}

void CSuperCombo::Loop()
{
    if (m_nTimer > 0)
    {
        m_nTimer --;
    }
    else
    {
        Reset();
    }
}

int CSuperCombo::GetCombo()
{
    return m_nComboCount;
}

void CSuperCombo::Reset()
{
    m_nTimer = MAX_TIMER;
    m_nComboCount = 0;
}