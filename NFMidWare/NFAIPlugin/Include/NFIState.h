// -------------------------------------------------------------------------
//    @FileName			:    NFIState.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2017-02-08
//    @Module           :    NFIState
//    @Desc             :
// -------------------------------------------------------------------------

#ifndef NFI_STATE_H
#define NFI_STATE_H

#include "NFComm/NFCore/NFDataList.hpp"

class NFIMoveModule;
class NFIAIModule;
class NFIHateModule;
class NFIKernelModule;
class NFIEventProcessModule;
class NFIElementInfoModule;
class NFIPluginManager;

//所有的状态
enum NFAI_MOVE_TYPE
{
	NO_MOVE_TYPE,              // 不走的，塔等
	MOVE_BY_POINT_LIST,        // 路径巡逻
	MOVE_BY_RANDOM,            // 随机巡逻
	MOVE_BY_PLAYER_AI,         // Player's ai
};

//所有的状态
enum NFAI_STATE
{
    State_Error = 0,
    IdleState,                  // 休闲状态
    PatrolState,                // 巡逻状态
    FightState,                 // 战斗状态
    ChaseState,                 // 追击状态
    DeadState,                  // 死亡状态
};

class NFIState
{
public:
    NFIState(NFAI_STATE eState, const float fHeartBeatTime, NFIPluginManager* p)
    {
        meState = eState;
        mfHeartBeatTime = fHeartBeatTime;
        pPluginManager = p;
    }

    virtual ~NFIState()
    {
    }

    virtual bool DoRule(const NFGUID& self)
    {
        //返回true表示基类处理过，上面就别处理了
        return false;
    }

    virtual bool Enter(const NFGUID& self)
    {
        return false;
    }

    virtual bool Execute(const NFGUID& self)
    {
        return false;
    }

    virtual bool Exit(const NFGUID& self)
    {
        return false;
    }

    const NFAI_STATE GetCurrState()
    {
        return meState;
    }

    float GetHeartBeatTime()
    {
        return mfHeartBeatTime;
    }

protected:

    virtual bool DoEnterScript(const NFGUID& self)
    {
        return true;
    }

    virtual bool DoExecuteScript(const NFGUID& self)
    {
        return true;
    }

    virtual bool DoExitScript(const NFGUID& self)
    {
        return true;
    }

protected:
    NFAI_STATE  meState;
    float               mfHeartBeatTime;
    NFIPluginManager* pPluginManager;

    NFIAIModule* m_pAIModule;
    NFIHateModule* m_pHateModule;
    NFIKernelModule* m_pKernelModule;
    NFIMoveModule* m_pMoveModule;
    NFIElementInfoModule* m_pElementInfoModule;

};

#endif