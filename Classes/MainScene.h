#ifndef __DHMainScene_SCENE_H__
#define __DHMainScene_SCENE_H__

#include "PublicDef.h"
#include "Duck.h"
#include "DuckManager.h"

enum
{
    enTagDuckManager,
};

class DHMainScene : public Layer , public Receiver
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(DHMainScene);
    
    void OnMsgReceive(MsgToMainScene nMsg,void* pData,int nSize);
    
    void update(float fT);
    
    Vector<Sprite*> m_vecDucks;
    
private:
    //管理器
    DHDuckManager* m_pManager;
    //创建目标
    void DuckCreate(structDuckCreate*);
    //删除目标
    void DuckDisappear(structDuckDisappear*);
};

#endif // __DHMainScene_SCENE_H__
