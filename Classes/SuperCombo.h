//
//  SuperCombo.h
//  DuckHunt
//
//  Created by hENRYcHANG on 14/11/26.
//
//

#ifndef __DuckHunt__SuperCombo__
#define __DuckHunt__SuperCombo__

#include <stdio.h>

//设置一个计时器  有效打击就重置计时器  计数加一  计时器走完就计数置零
class CSuperCombo
{
public:
    CSuperCombo();
    //有效点击
    void Hit();
    //循环,需要每0.1秒调用一次
    void Loop();
    //获得连击数
    int GetCombo();
private:
    int m_nComboCount;
    int m_nTimer;
    
    void Reset();
};

#endif /* defined(__DuckHunt__SuperCombo__) */
