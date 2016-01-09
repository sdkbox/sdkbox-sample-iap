
#include "PluginIAPLuaHelper.h"
#include "PluginIAP/PluginIAP.h"
#include "CCLuaEngine.h"
#include "tolua_fix.h"
#include "SDKBoxLuaHelper.h"


class IAPListenerLuaManual : public sdkbox::IAPListener {
public:
	IAPListenerLuaManual(): mLuaHandler(0) {

	}
	~IAPListenerLuaManual() {
		resetHandler();
	}

	void setHandler(int luaHandler) {
		if (mLuaHandler == luaHandler) {
			return;
		}
		resetHandler();
		mLuaHandler = luaHandler;
	}

	void resetHandler() {
		if (0 == mLuaHandler) {
			return;
		}

        LUAENGINE->removeScriptHandler(mLuaHandler);
		mLuaHandler = 0;
	}

    void onSuccess(const sdkbox::Product& p) {
        LuaStack* stack = LUAENGINE->getLuaStack();

        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onSuccess")));
        dict.insert(std::make_pair("product", prouct2LuaValue(p)));
        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }

    void onFailure(const sdkbox::Product& p, const std::string& msg) {
        LuaStack* stack = LUAENGINE->getLuaStack();

        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onFailure")));
        dict.insert(std::make_pair("product", prouct2LuaValue(p)));
        dict.insert(std::make_pair("msg", LuaValue::stringValue(msg)));
        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void onCanceled(const sdkbox::Product& p) {
        LuaStack* stack = LUAENGINE->getLuaStack();

        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onCanceled")));
        dict.insert(std::make_pair("product", prouct2LuaValue(p)));
        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void onRestored(const sdkbox::Product& p) {
        LuaStack* stack = LUAENGINE->getLuaStack();

        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onRestored")));
        dict.insert(std::make_pair("product", prouct2LuaValue(p)));
        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void onProductRequestSuccess(const std::vector<sdkbox::Product>& products) {
        LuaStack* stack = LUAENGINE->getLuaStack();

        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onProductRequestSuccess")));
        dict.insert(std::make_pair("products", proucts2LuaValue(products)));
        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);

    }
    void onProductRequestFailure(const std::string& msg) {
        LuaStack* stack = LUAENGINE->getLuaStack();

        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onProductRequestFailure")));
        dict.insert(std::make_pair("msg", LuaValue::stringValue(msg)));
        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void onInitialized(bool ok) {
        LuaStack* stack = LUAENGINE->getLuaStack();

        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onInitialized")));
        dict.insert(std::make_pair("ok", LuaValue::booleanValue(ok)));
        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    void onRestoreComplete(bool ok, const std::string& msg)
    {
        LuaStack* stack = LUAENGINE->getLuaStack();

        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onRestoreComplete")));
        dict.insert(std::make_pair("ok", LuaValue::booleanValue(ok)));
        dict.insert(std::make_pair("msg", LuaValue::stringValue(msg)));
        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }


private:

    LuaValue prouct2LuaValue(const sdkbox::Product& p) {
        LuaValueDict dicLua;
        dicLua.insert(std::make_pair("name", LuaValue::stringValue(p.name)));
        dicLua.insert(std::make_pair("id", LuaValue::stringValue(p.id)));
        dicLua.insert(std::make_pair("title", LuaValue::stringValue(p.title)));
        dicLua.insert(std::make_pair("description", LuaValue::stringValue(p.description)));
        dicLua.insert(std::make_pair("price", LuaValue::stringValue(p.price)));

        return LuaValue::dictValue(dicLua);
    }

    LuaValue proucts2LuaValue(const std::vector<sdkbox::Product>& products) {
        std::vector<sdkbox::Product>::const_iterator it;
        LuaValueArray arrLua;
        for (it = products.begin(); it != products.end(); it++) {
            arrLua.push_back(prouct2LuaValue(*it));
        }

        return LuaValue::arrayValue(arrLua);
    }

private:
	int mLuaHandler;
};

int lua_PluginIAPLua_PluginIAP_setListener(lua_State* tolua_S) {
	int argc = 0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2 , "LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        sdkbox::IAP::removeListener();
        IAPListenerLuaManual* lis = nullptr;
        lis = new IAPListenerLuaManual();
        lis->setHandler(handler);
        sdkbox::IAP::setListener(lis);

        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP::setListener",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_PluginIAP_setListener'.",&tolua_err);
#endif
    return 0;
}



int extern_PluginIAP(lua_State* L) {
	if (nullptr == L) {
		return 0;
	}

	lua_pushstring(L, "sdkbox.IAP");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L,"setListener", lua_PluginIAPLua_PluginIAP_setListener);
    }
     lua_pop(L, 1);

    return 1;
}

TOLUA_API int register_all_PluginIAPLua_helper(lua_State* L) {
	tolua_module(L,"sdkbox",0);
	tolua_beginmodule(L,"sdkbox");

	extern_PluginIAP(L);

	tolua_endmodule(L);
	return 1;
}

