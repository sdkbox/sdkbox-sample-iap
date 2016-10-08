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
        tolua_function(tolua_S,"restore", lua_PluginIAPLua_IAP_restore);
        tolua_function(tolua_S,"refresh", lua_PluginIAPLua_IAP_refresh);
        tolua_function(tolua_S,"init", lua_PluginIAPLua_IAP_init);
        tolua_function(tolua_S,"setDebug", lua_PluginIAPLua_IAP_setDebug);
        tolua_function(tolua_S,"enableUserSideVerification", lua_PluginIAPLua_IAP_enableUserSideVerification);
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
	
	tolua_module(tolua_S,"sdkbox",0);
	tolua_beginmodule(tolua_S,"sdkbox");

	lua_register_PluginIAPLua_IAP(tolua_S);

	tolua_endmodule(tolua_S);

	sdkbox::setProjectType("lua");
	return 1;
}

