
#include "PluginIAPLuaHelper.h"
#include "PluginIAP/PluginIAP.h"
#include "SDKBoxLuaHelper.h"


class LuaIAPCallbackObj : public CCObject {

public:
    static LuaIAPCallbackObj* create(int handler) {
        LuaIAPCallbackObj *obj = new LuaIAPCallbackObj();
        obj->_luaHandler = handler;

        obj->autorelease();
        return obj;
    }

    LuaIAPCallbackObj* setLuaDict(const LuaValueDict& val) {
        _luaValueDict = val;
        return this;
    }

    void start() {
        CCDirector::sharedDirector()->getScheduler()
            ->scheduleSelector(schedule_selector(LuaIAPCallbackObj::callback), this, 0.1, 0, 0.0f, false);
    }

    void callback(float dt) {
        LuaStack* stack = LUAENGINE->getLuaStack();
        stack->pushLuaValueDict(_luaValueDict);
        stack->executeFunctionByHandler(_luaHandler, 1);

        release();
    }

private:
    LuaIAPCallbackObj()
    : _luaHandler(0) {
        retain();
    }

    int _luaHandler;
    LuaValueDict _luaValueDict;
};


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
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onSuccess")));
        dict.insert(std::make_pair("product", prouct2LuaValue(p)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    void onFailure(const sdkbox::Product& p, const std::string& msg) {
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onFailure")));
        dict.insert(std::make_pair("product", prouct2LuaValue(p)));
        dict.insert(std::make_pair("msg", LuaValue::stringValue(msg)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    void onCanceled(const sdkbox::Product& p) {
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onCanceled")));
        dict.insert(std::make_pair("product", prouct2LuaValue(p)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    void onRestored(const sdkbox::Product& p) {
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onRestored")));
        dict.insert(std::make_pair("product", prouct2LuaValue(p)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    void onProductRequestSuccess(const std::vector<sdkbox::Product>& products) {
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onProductRequestSuccess")));
        dict.insert(std::make_pair("products", proucts2LuaValue(products)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    void onProductRequestFailure(const std::string& msg) {
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onProductRequestFailure")));
        dict.insert(std::make_pair("msg", LuaValue::stringValue(msg)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    void onInitialized(bool ok) {
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onInitialized")));
        dict.insert(std::make_pair("ok", LuaValue::booleanValue(ok)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    void onRestoreComplete(bool ok, const std::string& msg){
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onRestoreComplete")));
        dict.insert(std::make_pair("ok", LuaValue::booleanValue(ok)));
        dict.insert(std::make_pair("msg", LuaValue::stringValue(msg)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    bool onShouldAddStorePayment(const std::string& productId) {
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue("onShouldAddStorePayment")));
        dict.insert(std::make_pair("productId", LuaValue::stringValue(productId)));

        LuaStack* stack = LUAENGINE->getLuaStack();
        stack->pushLuaValueDict(dict);
        return (bool)stack->executeFunctionByHandler(mLuaHandler, 1);
    }

    void onFetchStorePromotionOrder(const std::vector<std::string>& productIds, const std::string& error) {
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onFetchStorePromotionOrder")));

        std::vector<std::string>::const_iterator it;
        LuaValueArray arrLua;
        for (it = productIds.begin(); it != productIds.end(); it++) {
            arrLua.push_back(LuaValue::stringValue(*it));
        }
        dict.insert(std::make_pair("productIds", LuaValue::arrayValue(arrLua)));
        dict.insert(std::make_pair("error", LuaValue::stringValue(error)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    void onFetchStorePromotionVisibility(const std::string productId, bool visibility, const std::string& error) {
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onFetchStorePromotionVisibility")));
        dict.insert(std::make_pair("productId", LuaValue::stringValue(productId)));
        dict.insert(std::make_pair("visibility", LuaValue::booleanValue(visibility)));
        dict.insert(std::make_pair("error", LuaValue::stringValue(error)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    void onUpdateStorePromotionOrder(const std::string& error) {
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onUpdateStorePromotionOrder")));
        dict.insert(std::make_pair("error", LuaValue::stringValue(error)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

    void onUpdateStorePromotionVisibility(const std::string& error) {
        LuaValueDict dict;
        dict.insert(std::make_pair("event", LuaValue::stringValue("onUpdateStorePromotionVisibility")));
        dict.insert(std::make_pair("error", LuaValue::stringValue(error)));
        LuaIAPCallbackObj::create(mLuaHandler)->setLuaDict(dict)->start();
    }

public:

    static LuaValue prouct2LuaValue(const sdkbox::Product& p) {
        LuaValueDict dicLua;
        dicLua.insert(std::make_pair("name", LuaValue::stringValue(p.name)));
        dicLua.insert(std::make_pair("id", LuaValue::stringValue(p.id)));
        dicLua.insert(std::make_pair("title", LuaValue::stringValue(p.title)));
        dicLua.insert(std::make_pair("description", LuaValue::stringValue(p.description)));
        dicLua.insert(std::make_pair("price", LuaValue::stringValue(p.price)));
        dicLua.insert(std::make_pair("currencyCode", LuaValue::stringValue(p.currencyCode)));
        dicLua.insert(std::make_pair("receipt", LuaValue::stringValue(p.receipt)));
        dicLua.insert(std::make_pair("receiptCipheredPayload", LuaValue::stringValue(p.receiptCipheredPayload)));
        dicLua.insert(std::make_pair("priceValue", LuaValue::floatValue(p.priceValue)));
        dicLua.insert(std::make_pair("transactionID", LuaValue::stringValue(p.transactionID)));
        switch (p.type) {
            case sdkbox::IAP_Type::CONSUMABLE: {
                dicLua.insert(std::make_pair("type", LuaValue::stringValue("CONSUMABLE")));
                break;
            }
            case sdkbox::IAP_Type::NON_CONSUMABLE: {
                dicLua.insert(std::make_pair("type", LuaValue::stringValue("NON_CONSUMABLE")));
                break;
            }
            default:
                break;
        }

        return LuaValue::dictValue(dicLua);
    }

    static LuaValue proucts2LuaValue(const std::vector<sdkbox::Product>& products) {
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

int lua_PluginIAPLua_PluginIAP_getProducts(lua_State* tolua_S) {
    int argc = 0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.IAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0) {
        std::vector<sdkbox::Product> products = sdkbox::IAP::getProducts();
        LuaValue v = IAPListenerLuaManual::proucts2LuaValue(products);
        LuaStack* stack = LUAENGINE->getLuaStack();
        stack->pushLuaValue(v);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.IAP::getProducts",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginIAPLua_PluginIAP_getProducts'.",&tolua_err);
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
        tolua_function(L,"getProducts", lua_PluginIAPLua_PluginIAP_getProducts);
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

