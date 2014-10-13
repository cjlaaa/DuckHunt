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
    static DHDuck* create();
protected:
    bool Init();
};

#endif /* defined(__DuckHunt__Duck__) */
