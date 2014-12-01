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

enum
{
    enZOrderBack,
    enZOrderMid,
    enZOrderFront,
};

struct DuckData
{
    int nScore;
    int nHp;
    int nCD;
    int nSpeed;
    std::string fileName;
    Point StartPos;
    Point TargetPos;
    bool bMoveRight;
};

//单位信息数据集合
const DuckData DuckDataBase[DUCK_TYPE_NUM] =
{
    {1,1,50,5,"duck1.png"},
    {2,1,80,10,"duck2.png"},
    {3,1,100,15,"duck3.png"},
};

//发给主场景的消息
enum MsgToMainScene
{
    //单位消失
    MsgDuckDisappear,
    //单位创建
    MsgDuckCreate,
    //加分
    MsgAddScore,
};

class DHDuck;
//单位消失
struct structDuckDisappear
{
    DHDuck* pDuck;
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

class DHUtils
{
public:
    static DHUtils* getInstance();
    
    //获得随机数 bFromZero为false则1~nRange,true则为0~(nRange-1)
    int GetRandom(int nRange,bool bFromZero = false);
};

#endif
