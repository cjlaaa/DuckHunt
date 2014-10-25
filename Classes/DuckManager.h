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

class DHDuckManager : public Node , public Sender
{
public:
    static DHDuckManager* create(Receiver* );
    void Loop();
protected:
    int m_nDuckCDCount[DUCK_TYPE_NUM];
    bool Init(Receiver* pNode);
    void CreateDuck(int nDuckIndex);
};

#endif /* defined(__DuckHunt__DuckManager__) */
