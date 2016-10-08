#include "PluginIAPJSHelper.h"
#include "PluginIAP/PluginIAP.h"

extern JSObject* jsb_sdkbox_PluginAdColony_prototype;

static JSContext* s_cx = nullptr;

JSObject* product_to_obj(JSContext* cx, const sdkbox::Product& p)
{
#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
    JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
    JS::RootedValue name(cx);
    JS::RootedValue id(cx);
    JS::RootedValue title(cx);
    JS::RootedValue description(cx);
    JS::RootedValue price(cx);
    JS::RootedValue currencyCode(cx);
    JS::RootedValue receipt(cx);
    JS::RootedValue receiptCipheredPayload(cx);

    name = std_string_to_jsval(cx, p.name);

    JS_SetProperty(cx, jsobj, "name", name);
    id = std_string_to_jsval(cx, p.id);
    JS_SetProperty(cx, jsobj, "id", id);
    title = std_string_to_jsval(cx, p.title);
    JS_SetProperty(cx, jsobj, "title", title);
    description = std_string_to_jsval(cx, p.description);
    JS_SetProperty(cx, jsobj, "description", description);
    price = std_string_to_jsval(cx, p.price);
    JS_SetProperty(cx, jsobj, "price", price);
    currencyCode = std_string_to_jsval(cx, p.currencyCode);
    JS_SetProperty(cx, jsobj, "currencyCode", currencyCode);
    receipt = std_string_to_jsval(cx, p.receipt);
    JS_SetProperty(cx, jsobj, "receipt", receipt);
    receiptCipheredPayload = std_string_to_jsval(cx, p.receiptCipheredPayload);
    JS_SetProperty(cx, jsobj, "receiptCipheredPayload", receiptCipheredPayload);

#else
    JSObject* jsobj = JS_NewObject(cx, NULL, NULL, NULL);
    JS::RootedValue name(cx);
    JS::RootedValue id(cx);
    JS::RootedValue title(cx);
    JS::RootedValue description(cx);
    JS::RootedValue price(cx);
    JS::RootedValue currencyCode(cx);
    JS::RootedValue receipt(cx);
    JS::RootedValue receiptCipheredPayload(cx);

    name = std_string_to_jsval(cx, p.name);

    JS_SetProperty(cx, jsobj, "name", name);
    id = std_string_to_jsval(cx, p.id);
    JS_SetProperty(cx, jsobj, "id", id);
    title = std_string_to_jsval(cx, p.title);
    JS_SetProperty(cx, jsobj, "title", title);
    description = std_string_to_jsval(cx, p.description);
    JS_SetProperty(cx, jsobj, "description", description);
    price = std_string_to_jsval(cx, p.price);
    JS_SetProperty(cx, jsobj, "price", price);
    currencyCode = std_string_to_jsval(cx, p.currencyCode);
    JS_SetProperty(cx, jsobj, "currencyCode", currencyCode);
    receipt = std_string_to_jsval(cx, p.receipt);
    JS_SetProperty(cx, jsobj, "receipt", receipt);
    receiptCipheredPayload = std_string_to_jsval(cx, p.receiptCipheredPayload);
    JS_SetProperty(cx, jsobj, "receiptCipheredPayload", receiptCipheredPayload);

#endif
#elif defined(JS_VERSION)
    JSObject* jsobj = JS_NewObject(cx, NULL, NULL, NULL);
    jsval name;
    jsval id;
    jsval title;
    jsval description;
    jsval price;
    jsval currencyCode;
    jsval receipt;
    jsval receiptCipheredPayload;

    name = std_string_to_jsval(cx, p.name);

    JS_SetProperty(cx, jsobj, "name", &name);
    id = std_string_to_jsval(cx, p.id);
    JS_SetProperty(cx, jsobj, "id", &id);
    title = std_string_to_jsval(cx, p.title);
    JS_SetProperty(cx, jsobj, "title", &title);
    description = std_string_to_jsval(cx, p.description);
    JS_SetProperty(cx, jsobj, "description", &description);
    price = std_string_to_jsval(cx, p.price);
    JS_SetProperty(cx, jsobj, "price", &price);
    currencyCode = std_string_to_jsval(cx, p.currencyCode);
    JS_SetProperty(cx, jsobj, "currencyCode", &currencyCode);
    receipt = std_string_to_jsval(cx, p.receipt);
    JS_SetProperty(cx, jsobj, "receipt", &receipt);
    receiptCipheredPayload = std_string_to_jsval(cx, p.receiptCipheredPayload);
    JS_SetProperty(cx, jsobj, "receiptCipheredPayload", &receiptCipheredPayload);

#endif

    return jsobj;
}

jsval std_vector_product_to_jsval( JSContext *cx, const std::vector<sdkbox::Product>& v)
{
#if MOZJS_MAJOR_VERSION >= 31
    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, v.size()));
#else
    jsval jsretArrVal;
    JSObject* jsretArr = JS_NewArrayObject(cx, (int)v.size(), &jsretArrVal);
#endif

    int i = 0;
    std::vector<sdkbox::Product>::const_iterator it = v.begin();
    for (; it != v.end(); it++)
    {
#if defined(MOZJS_MAJOR_VERSION)
        JS::RootedValue arrElement(cx);
#elif defined(JS_VERSION)
        jsval arrElement;
#endif
        arrElement = OBJECT_TO_JSVAL(product_to_obj(s_cx, (*it)));

#if MOZJS_MAJOR_VERSION >= 31
        if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
#else
        if (!JS_SetElement(cx, jsretArr, i, &arrElement)) {
#endif
            break;
        }
        ++i;
    }
    return OBJECT_TO_JSVAL(jsretArr);
}


USING_NS_CC;

#if (COCOS2D_VERSION < 0x00030000)
#define Ref CCObject
#define Director CCDirector
#define getInstance sharedDirector
#define schedule scheduleSelector
#endif

class JsIAPCallbackObj : public Ref {

public:
    static JsIAPCallbackObj* create(const std::string& name, JSObject *handler) {
        JsIAPCallbackObj *obj = new JsIAPCallbackObj();
        obj->_eventName = name;
        obj->_jsHandler = handler;

        obj->autorelease();
        return obj;
    }

    void setProduct(const sdkbox::Product& product) {
        _product = product;
    }

    void setProducts(const std::vector<sdkbox::Product>& products) {
         _products = products;
    }

    void setMsg(const std::string& msg) {
        _msg = msg;
    }

    void setBoolean(bool b) {
        _bValue = b;
    }

    void start() {
        Director::getInstance()->getScheduler()
            ->schedule(schedule_selector(JsIAPCallbackObj::callback), this, 0.1, 0, 0.0f, false);
    }

    void callback(float dt) {
        if (!s_cx) {
            return;
        }

        JSContext* cx = s_cx;
        const char* func_name = _eventName.data();

        JS::RootedObject obj(cx, _jsHandler);
        JSAutoCompartment ac(cx, obj);

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue func_handle(cx);
#else
        bool hasAction;
        jsval retval;
        JS::RootedValue func_handle(cx);
#endif
#elif defined(JS_VERSION)
        JSBool hasAction;
        jsval retval;
        jsval func_handle;
#endif

        jsval dataVal[2];
        int datalen = 0;

        if (0 == _eventName.compare("onInitialized")) {
            dataVal[0] = BOOLEAN_TO_JSVAL(_bValue);
            datalen = 1;
        } else if (0 == _eventName.compare("onSuccess")) {
            dataVal[0] = OBJECT_TO_JSVAL(product_to_obj(cx, _product));
            datalen = 1;
        } else if (0 == _eventName.compare("onFailure")) {
            dataVal[0] = OBJECT_TO_JSVAL(product_to_obj(cx, _product));
            dataVal[1] = std_string_to_jsval(cx, _msg);
            datalen = 2;
        } else if (0 == _eventName.compare("onCanceled")) {
            dataVal[0] = OBJECT_TO_JSVAL(product_to_obj(cx, _product));
            datalen = 1;
        } else if (0 == _eventName.compare("onRestored")) {
            dataVal[0] = OBJECT_TO_JSVAL(product_to_obj(cx, _product));
            datalen = 1;
        } else if (0 == _eventName.compare("onProductRequestSuccess")) {
            dataVal[0] = std_vector_product_to_jsval(cx, _products);
            datalen = 1;
        } else if (0 == _eventName.compare("onProductRequestFailure")) {
            dataVal[0] = std_string_to_jsval(cx, _msg);
            datalen = 1;
        } else if (0 == _eventName.compare("onRestoreComplete")) {
            dataVal[0] = BOOLEAN_TO_JSVAL(_bValue);
            dataVal[1] = std_string_to_jsval(cx, _msg);
            datalen = 2;
        } else {
            return;
        }

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(datalen, dataVal), &retval);
#else
            JS_CallFunctionName(cx, obj, func_name, datalen, dataVal, &retval);
#endif
        }
        release();
    }

private:
    JsIAPCallbackObj()
    : _eventName("")
    , _jsHandler(nullptr)
    , _msg("")
    , _bValue(false) {
        _products.clear();
        retain();
    }

    std::vector<sdkbox::Product> _products;
    JSObject* _jsHandler;
    std::string _eventName;
    std::string _msg;
    sdkbox::Product _product;
    bool _bValue;
}; // JsIAPCallbackObj


class IAPWrapperJS : public sdkbox::IAPListener, public sdkbox::JSListenerBase
{
public:
    IAPWrapperJS():sdkbox::JSListenerBase() {
    }

    void onSuccess(const sdkbox::Product& info) {
        JsIAPCallbackObj* obj = JsIAPCallbackObj::create("onSuccess", getJSDelegate());
        obj->setProduct(info);
        obj->start();
    }

    void onFailure(const sdkbox::Product& info, const std::string& msg) {
        JsIAPCallbackObj* obj = JsIAPCallbackObj::create("onFailure", getJSDelegate());
        obj->setProduct(info);
        obj->setMsg(msg);
        obj->start();
    }

    void onCanceled(const sdkbox::Product& info) {
        JsIAPCallbackObj* obj = JsIAPCallbackObj::create("onCanceled", getJSDelegate());
        obj->setProduct(info);
        obj->start();
    }

    void onRestored(const sdkbox::Product& info) {
        JsIAPCallbackObj* obj = JsIAPCallbackObj::create("onRestored", getJSDelegate());
        obj->setProduct(info);
        obj->start();
    }

    void onProductRequestSuccess(const std::vector<sdkbox::Product>& products) {
        JsIAPCallbackObj* obj = JsIAPCallbackObj::create("onProductRequestSuccess", getJSDelegate());
        obj->setProducts(products);
        obj->start();
    }

    void onProductRequestFailure(const std::string& msg) {
        JsIAPCallbackObj* obj = JsIAPCallbackObj::create("onProductRequestFailure", getJSDelegate());
        obj->setMsg(msg);
        obj->start();
    }

    void onInitialized(bool ok) {
        JsIAPCallbackObj* obj = JsIAPCallbackObj::create("onInitialized", getJSDelegate());
        obj->setBoolean(ok);
        obj->start();
    }

    void onRestoreComplete(bool ok, const std::string& msg) {
        JsIAPCallbackObj* obj = JsIAPCallbackObj::create("onRestoreComplete", getJSDelegate());
        obj->setBoolean(ok);
        obj->setMsg(msg);
        obj->start();
    }
};

#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginIAPJS_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#elif defined(JS_VERSION)
JSBool js_PluginIAPJS_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    if (argc == 1) {

        if (!args.get(0).isObject())
        {
            ok = false;
        }

        JSB_PRECONDITION2(ok, cx, false, "js_PluginIAPJS_setListener : Error processing arguments");
        IAPWrapperJS* wrapper = new IAPWrapperJS();
        wrapper->setJSDelegate(args.get(0));
        sdkbox::IAP::setListener(wrapper);

        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginIAPJS_setListener : wrong number of arguments");
    return false;
}

#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginIAPJS_IAP_getProducts(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::vector<sdkbox::Product> ret = sdkbox::IAP::getProducts();
        jsval jsret = std_vector_product_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginIAPJS_IAP_getProducts : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginIAPJS_IAP_getProducts(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::vector<sdkbox::Product> ret = sdkbox::IAP::getProducts();
        jsval jsret = std_vector_product_to_jsval(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginIAPJS_helper(JSContext* cx, JS::HandleObject global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, global, "sdkbox.IAP", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginIAPJS_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, pluginObj, "getProducts", js_PluginIAPJS_IAP_getProducts, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}
#else
void register_all_PluginIAPJS_helper(JSContext* cx, JSObject* global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, JS::RootedObject(cx, global), "sdkbox.IAP", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginIAPJS_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, pluginObj, "getProducts", js_PluginIAPJS_IAP_getProducts, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginIAPJS_helper(JSContext* cx, JSObject* global) {
    jsval pluginVal;
    JSObject* pluginObj;
    pluginVal = sdkbox::getJsObjOrCreat(cx, global, "sdkbox.IAP", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginIAPJS_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, pluginObj, "getProducts", js_PluginIAPJS_IAP_getProducts, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}
#endif
