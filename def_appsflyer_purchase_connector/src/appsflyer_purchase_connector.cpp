#define EXTENSION_NAME AppsflyerPurchaseConnectorExt
#define LIB_NAME "AppsflyerPurchaseConnector"
#define MODULE_NAME "appsflyer_purchase_connector"

#define DLIB_LOG_DOMAIN LIB_NAME

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)

#include <stdlib.h>
#include "appsflyer_purchase_connector.h"
#include "utils/lua_util.h"

namespace dmAppsflyerPurchaseConnector
{

    static int Lua_SetIapAdditionalData(lua_State* L) { 
        DM_LUA_STACK_CHECK(L, 0);    
        if (lua_type(L, 1) != LUA_TSTRING) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Rewarded UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
            luaL_error(L, msg);
            return 0;
        }
        if (lua_type(L, 2) != LUA_TSTRING) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Rewarded UnitId variable '%s'.", luaL_typename(L, 2), lua_tostring(L, 2));
            luaL_error(L, msg);
            return 0;
        }
        const char* key = luaL_checkstring(L, 1);
        const char* value = luaL_checkstring(L, 2);
        SetIapAdditionalData(key,value); 
        return 0; 
    }
    
    static int Lua_SetSubscriptionsAdditionalData(lua_State* L) { 
        DM_LUA_STACK_CHECK(L, 0);    
        if (lua_type(L, 1) != LUA_TSTRING) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Rewarded UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
            luaL_error(L, msg);
            return 0;
        }
        if (lua_type(L, 2) != LUA_TSTRING) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Rewarded UnitId variable '%s'.", luaL_typename(L, 2), lua_tostring(L, 2));
            luaL_error(L, msg);
            return 0;
        }
        const char* key = luaL_checkstring(L, 1);
        const char* value = luaL_checkstring(L, 2);
        SetSubscriptionsAdditionalData(key,value); 
        return 0; 
    }
    
    static int Lua_SetSandbox(lua_State* L) { 
        DM_LUA_STACK_CHECK(L, 0);    
        bool param = luaL_checkbool(L, 1);
        SetSandbox(param); 
        return 0; 
    }
    static int Lua_LogSubscriptions(lua_State* L) { 
        DM_LUA_STACK_CHECK(L, 0);    
        bool param = luaL_checkbool(L, 1);
        LogSubscriptions(param); 
        return 0; 
    }
    static int Lua_AutoLogInApps(lua_State* L) { 
        DM_LUA_STACK_CHECK(L, 0);    
        bool param = luaL_checkbool(L, 1);
        AutoLogInApps(param); 
        return 0; 
    }

    static int Lua_StartObservingTransactions(lua_State *L){
        DM_LUA_STACK_CHECK(L, 0);
        StartObservingTransactions();
        return 0;
    }

    static int Lua_StopObservingTransactions(lua_State *L){
        DM_LUA_STACK_CHECK(L, 0);
        StopObservingTransactions();
        return 0;
    }

    static const luaL_reg Module_methods[] =
        {
            {"set_iap_additional_data",Lua_SetIapAdditionalData},
            {"set_subscriptions_additional_data",Lua_SetSubscriptionsAdditionalData},
            {"set_sandbox",Lua_SetSandbox},
            {"log_subscriptions",Lua_LogSubscriptions},
            {"auto_log_inapps",Lua_AutoLogInApps},
            {"start_observing_transactions",Lua_StartObservingTransactions},
            {"stop_observing_transactions",Lua_StopObservingTransactions},
            {0, 0}
        };

    static void LuaInit(lua_State *L)
    {
        DM_LUA_STACK_CHECK(L, 0);
        luaL_register(L, MODULE_NAME, Module_methods);
        lua_pop(L, 1);
    }

    static dmExtension::Result AppInitializeAppsflyerPurchaseConnector(dmExtension::AppParams *params)
    {
        Initialize_Ext();
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result InitializeAppsflyerPurchaseConnector(dmExtension::Params *params)
    {
        LuaInit(params->m_L);
        dmLogInfo("Registered extension AppsflyerPurchaseConnector");
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result UpdateAppsflyerPurchaseConnector(dmExtension::Params *params)
    {
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result AppFinalizeAppsflyerPurchaseConnector(dmExtension::AppParams *params)
    {
        return dmExtension::RESULT_OK;
    }

    static dmExtension::Result FinalizeAppsflyerPurchaseConnector(dmExtension::Params *params)
    {
        return dmExtension::RESULT_OK;
    }

} // namespace

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, dmAppsflyerPurchaseConnector::AppInitializeAppsflyerPurchaseConnector, dmAppsflyerPurchaseConnector::AppFinalizeAppsflyerPurchaseConnector, dmAppsflyerPurchaseConnector::InitializeAppsflyerPurchaseConnector, dmAppsflyerPurchaseConnector::UpdateAppsflyerPurchaseConnector, 0, dmAppsflyerPurchaseConnector::FinalizeAppsflyerPurchaseConnector)

#else // platform

static dmExtension::Result InitializeAppsflyerPurchaseConnector(dmExtension::Params *params)
{
    dmLogInfo("Registered extension AppsflyerPurchaseConnector (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeAppsflyerPurchaseConnector(dmExtension::Params *params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeAppsflyerPurchaseConnector, 0, 0, FinalizeAppsflyerPurchaseConnector)

#endif // platform