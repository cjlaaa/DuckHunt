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
    static DHDuck* create(const std::string& filename , DuckData data);
    void Loop();
    void Hurt();
protected:
    DuckData m_Data;
    bool Init(const std::string& filename , DuckData data);
    void Move();
    void Disappear();
    void Dead();
};

#endif /* defined(__DuckHunt__Duck__) */
