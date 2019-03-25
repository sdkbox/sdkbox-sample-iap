#include "PluginIAPLua.hpp"
#include "PluginIAP/PluginIAP.h"
#include "SDKBoxLuaHelper.h"
#include "sdkbox/Sdkbox.h"



int lua_PluginIAPLua_IAP_purchase(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.IAP:purchase");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_purchase'", nullptr);
            return 0;
        }
        sdkbox::IAP::purchase(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:purchase",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_purchase'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_getInitializedErrMsg(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_getInitializedErrMsg'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::IAP::getInitializedErrMsg();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:getInitializedErrMsg",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_getInitializedErrMsg'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_updateStorePromotionVisibility(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        bool arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.IAP:updateStorePromotionVisibility");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "sdkbox.IAP:updateStorePromotionVisibility");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_updateStorePromotionVisibility'", nullptr);
            return 0;
        }
        sdkbox::IAP::updateStorePromotionVisibility(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:updateStorePromotionVisibility",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_updateStorePromotionVisibility'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_updateStorePromotionOrder(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::vector<std::string> arg0;
        ok &= luaval_to_std_vector_string(tolua_S, 2, &arg0, "sdkbox.IAP:updateStorePromotionOrder");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_updateStorePromotionOrder'", nullptr);
            return 0;
        }
        sdkbox::IAP::updateStorePromotionOrder(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:updateStorePromotionOrder",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_updateStorePromotionOrder'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_restore(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_restore'", nullptr);
            return 0;
        }
        sdkbox::IAP::restore();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:restore",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_restore'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_isAutoFinishTransaction(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_isAutoFinishTransaction'", nullptr);
            return 0;
        }
        bool ret = sdkbox::IAP::isAutoFinishTransaction();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:isAutoFinishTransaction",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_isAutoFinishTransaction'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_fetchStorePromotionOrder(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_fetchStorePromotionOrder'", nullptr);
            return 0;
        }
        sdkbox::IAP::fetchStorePromotionOrder();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:fetchStorePromotionOrder",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_fetchStorePromotionOrder'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_refresh(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_refresh'", nullptr);
            return 0;
        }
        sdkbox::IAP::refresh();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:refresh",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_refresh'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_fetchStorePromotionVisibility(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.IAP:fetchStorePromotionVisibility");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_fetchStorePromotionVisibility'", nullptr);
            return 0;
        }
        sdkbox::IAP::fetchStorePromotionVisibility(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:fetchStorePromotionVisibility",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_fetchStorePromotionVisibility'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_setAutoFinishTransaction(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "sdkbox.IAP:setAutoFinishTransaction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_setAutoFinishTransaction'", nullptr);
            return 0;
        }
        sdkbox::IAP::setAutoFinishTransaction(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:setAutoFinishTransaction",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_setAutoFinishTransaction'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_getPurchaseHistory(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_getPurchaseHistory'", nullptr);
            return 0;
        }
        sdkbox::IAP::getPurchaseHistory();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:getPurchaseHistory",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_getPurchaseHistory'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_init(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_init'", nullptr);
            return 0;
        }
        sdkbox::IAP::init();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "sdkbox.IAP:init"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_init'", nullptr);
            return 0;
        }
        sdkbox::IAP::init(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:init",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_init'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_setDebug(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "sdkbox.IAP:setDebug");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_setDebug'", nullptr);
            return 0;
        }
        sdkbox::IAP::setDebug(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:setDebug",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_setDebug'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_requestUpdateTransaction(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_requestUpdateTransaction'", nullptr);
            return 0;
        }
        sdkbox::IAP::requestUpdateTransaction();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:requestUpdateTransaction",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_requestUpdateTransaction'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_enableUserSideVerification(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "sdkbox.IAP:enableUserSideVerification");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_enableUserSideVerification'", nullptr);
            return 0;
        }
        sdkbox::IAP::enableUserSideVerification(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:enableUserSideVerification",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_enableUserSideVerification'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_finishTransaction(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.IAP:finishTransaction");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_finishTransaction'", nullptr);
            return 0;
        }
        sdkbox::IAP::finishTransaction(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:finishTransaction",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_finishTransaction'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginIAPLua_IAP_removeListener(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginIAPLua_IAP_removeListener'", nullptr);
            return 0;
        }
        sdkbox::IAP::removeListener();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP:removeListener",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_IAP_removeListener'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginIAPLua_IAP_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (IAP)");
    return 0;
}

int lua_register_PluginIAPLua_IAP(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.IAP");
    tolua_cclass(tolua_S,"IAP","sdkbox.IAP","",nullptr);

    tolua_beginmodule(tolua_S,"IAP");
        tolua_function(tolua_S,"purchase", lua_PluginIAPLua_IAP_purchase);
        tolua_function(tolua_S,"getInitializedErrMsg", lua_PluginIAPLua_IAP_getInitializedErrMsg);
        tolua_function(tolua_S,"updateStorePromotionVisibility", lua_PluginIAPLua_IAP_updateStorePromotionVisibility);
        tolua_function(tolua_S,"updateStorePromotionOrder", lua_PluginIAPLua_IAP_updateStorePromotionOrder);
        tolua_function(tolua_S,"restore", lua_PluginIAPLua_IAP_restore);
        tolua_function(tolua_S,"isAutoFinishTransaction", lua_PluginIAPLua_IAP_isAutoFinishTransaction);
        tolua_function(tolua_S,"fetchStorePromotionOrder", lua_PluginIAPLua_IAP_fetchStorePromotionOrder);
        tolua_function(tolua_S,"refresh", lua_PluginIAPLua_IAP_refresh);
        tolua_function(tolua_S,"fetchStorePromotionVisibility", lua_PluginIAPLua_IAP_fetchStorePromotionVisibility);
        tolua_function(tolua_S,"setAutoFinishTransaction", lua_PluginIAPLua_IAP_setAutoFinishTransaction);
        tolua_function(tolua_S,"getPurchaseHistory", lua_PluginIAPLua_IAP_getPurchaseHistory);
        tolua_function(tolua_S,"init", lua_PluginIAPLua_IAP_init);
        tolua_function(tolua_S,"setDebug", lua_PluginIAPLua_IAP_setDebug);
        tolua_function(tolua_S,"requestUpdateTransaction", lua_PluginIAPLua_IAP_requestUpdateTransaction);
        tolua_function(tolua_S,"enableUserSideVerification", lua_PluginIAPLua_IAP_enableUserSideVerification);
        tolua_function(tolua_S,"finishTransaction", lua_PluginIAPLua_IAP_finishTransaction);
        tolua_function(tolua_S,"removeListener", lua_PluginIAPLua_IAP_removeListener);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::IAP).name();
    g_luaType[typeName] = "sdkbox.IAP";
    g_typeCast["IAP"] = "sdkbox.IAP";
    return 1;
}
TOLUA_API int register_all_PluginIAPLua(lua_State* tolua_S)
{
	tolua_open(tolua_S);

	std::stringstream ss("sdkbox");
    std::vector<std::string> nsvec;
    std::string item;
    while (std::getline(ss, item, '.')) {
        nsvec.push_back(item);
    }
    int nsLen = nsvec.size();
    item = nsvec.front();
    nsvec.erase(nsvec.begin());

    tolua_module(tolua_S, item.c_str(), 0);
    tolua_beginmodule(tolua_S, item.c_str());

    while (nsvec.size() > 0) {
        item = nsvec.front();
        nsvec.erase(nsvec.begin());
        lua_pushstring(tolua_S, item.c_str()); // m name
        lua_rawget(tolua_S, -2);             // m value
        if (!lua_istable(tolua_S, -1)) {
            lua_pop(tolua_S, 1);             // m
            lua_newtable(tolua_S);           // m t
            lua_pushstring(tolua_S, item.c_str()); // m t name
            lua_pushvalue(tolua_S, -2);      // m t name t
            lua_rawset(tolua_S, -4);         // m t
        }
    }

	lua_register_PluginIAPLua_IAP(tolua_S);

	if (nsLen > 1) {
        lua_pop(tolua_S, nsLen - 1); // m
    }
	tolua_endmodule(tolua_S);

	sdkbox::setProjectType("lua");
	return 1;
}

