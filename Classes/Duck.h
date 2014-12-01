//
//  Duck.h
//  DuckHunt
//
//  Created by hENRYcHANG on 14-10-14.
//
//

#ifndef __DuckHunt__Duck__
#define __DuckHunt__Duck__

#include "PublicDef.h"

class DHDuck : public Sprite , public Sender
{
public:
    static DHDuck* CreateDuck(const std::string& filename , DuckData data,Receiver* pReceiver);
    void Loop();
    void Hurt();
    DuckData m_Data;
    bool m_bIsDead;
protected:
    bool Init(const std::string& filename , DuckData data,Receiver* pReceiver);
    void Move();
    void Disappear();
    void Dead();
};

#endif /* defined(__DuckHunt__Duck__) */
