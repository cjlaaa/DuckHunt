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

#define DUCK_TYPE_NUM 3

struct DuckData
{
    int nScore;
    int nHp;
    int nCD;
    Point StartPos;
    Point TargetPos;
};

//单位信息数据集合
const DuckData DuckDataBase[DUCK_TYPE_NUM] =
{
    {1,1,1},
    {2,2,2},
    {3,3,3},
};

//发给主场景的消息
enum MsgToMainScene
{
    //单位消失
    MsgDuckDisappear,
    //单位创建
    MsgDuckCreate,
};

class DHDuck;
//单位消失
struct structDuckDisappear
{
    DHDuck* pSelf;
};

//单位创建
struct structDuckCreate
{
    DuckData DuckInfo;
};

class Receiver
{
public:
    virtual void OnMsgReceive(MsgToMainScene nMsg,void* pData,int nSize) = 0;
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
    void SendMsg(MsgToMainScene enMsg,void* pData = NULL,int nSize = 0)
    {
        m_pReceiver->OnMsgReceive(enMsg,pData,nSize);
    }
};

#endif
