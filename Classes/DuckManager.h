//
//  DuckManager.h
//  DuckHunt
//
//  Created by hENRYcHANG on 14-10-14.
//
//

#ifndef __DuckHunt__DuckManager__
#define __DuckHunt__DuckManager__

#include "PublicDef.h"

class DHDuckManager : public Sprite , public Sender
{
public:
    static DHDuckManager* create();
protected:
    bool Init();
};

#endif /* defined(__DuckHunt__DuckManager__) */
