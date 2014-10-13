//
//  PublicDef.h
//  DuckHunt
//
//  Created by hENRYcHANG on 14-10-14.
//
//

#ifndef DuckHunt_PublicDef_h
#define DuckHunt_PublicDef_h

#include "cocos2d.h"
USING_NS_CC;

class Receiver
{
public:
    virtual void OnMsgReceive(int nMsg,void* pData,int nSize) = 0;
};

class Sender
{
protected:
    Receiver* m_pReceiver;
public:
    void SetReceiver(Receiver* pReceiver)
    {
        m_pReceiver = pReceiver;
    }
    void SendMsg(int enMsg,void* pData,int nSize)
    {
        m_pReceiver->OnMsgReceive(enMsg,pData,nSize);
    }
};

#endif
