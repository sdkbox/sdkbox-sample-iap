#include "PluginIAPJSHelper.h"
#include "PluginIAP/PluginIAP.h"

extern JSObject* jsb_sdkbox_PluginAdColony_prototype;

static JSContext* s_cx = nullptr;

void product_to_obj(JSContext* cx, const sdkbox::Product& p, JS::MutableHandleObject retObj)
{
#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
#if MOZJS_MAJOR_VERSION >= 52
    JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL));
#else
    JS::RootedObject jsobj(cx, JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
#endif
    JS::RootedValue name(cx);
    JS::RootedValue id(cx);
    JS::RootedValue title(cx);
    JS::RootedValue description(cx);
    JS::RootedValue price(cx);
    JS::RootedValue currencyCode(cx);
    JS::RootedValue receipt(cx);
    JS::RootedValue receiptCipheredPayload(cx);
    JS::RootedValue transactionID(cx);

    name = SB_STR_TO_JSVAL(cx, p.name);

    JS_SetProperty(cx, jsobj, "name", name);
    id = SB_STR_TO_JSVAL(cx, p.id);
    JS_SetProperty(cx, jsobj, "id", id);
    title = SB_STR_TO_JSVAL(cx, p.title);
    JS_SetProperty(cx, jsobj, "title", title);
    description = SB_STR_TO_JSVAL(cx, p.description);
    JS_SetProperty(cx, jsobj, "description", description);
    price = SB_STR_TO_JSVAL(cx, p.price);
    JS_SetProperty(cx, jsobj, "price", price);
    currencyCode = SB_STR_TO_JSVAL(cx, p.currencyCode);
    JS_SetProperty(cx, jsobj, "currencyCode", currencyCode);
    receipt = SB_STR_TO_JSVAL(cx, p.receipt);
    JS_SetProperty(cx, jsobj, "receipt", receipt);
    receiptCipheredPayload = SB_STR_TO_JSVAL(cx, p.receiptCipheredPayload);
    JS_SetProperty(cx, jsobj, "receiptCipheredPayload", receiptCipheredPayload);

    transactionID = SB_STR_TO_JSVAL(cx, p.transactionID);
    JS_SetProperty(cx, jsobj, "transactionID", transactionID);

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
    JS::RootedValue transactionID(cx);

    name = SB_STR_TO_JSVAL(cx, p.name);

    JS_SetProperty(cx, jsobj, "name", name);
    id = SB_STR_TO_JSVAL(cx, p.id);
    JS_SetProperty(cx, jsobj, "id", id);
    title = SB_STR_TO_JSVAL(cx, p.title);
    JS_SetProperty(cx, jsobj, "title", title);
    description = SB_STR_TO_JSVAL(cx, p.description);
    JS_SetProperty(cx, jsobj, "description", description);
    price = SB_STR_TO_JSVAL(cx, p.price);
    JS_SetProperty(cx, jsobj, "price", price);
    currencyCode = SB_STR_TO_JSVAL(cx, p.currencyCode);
    JS_SetProperty(cx, jsobj, "currencyCode", currencyCode);
    receipt = SB_STR_TO_JSVAL(cx, p.receipt);
    JS_SetProperty(cx, jsobj, "receipt", receipt);
    receiptCipheredPayload = SB_STR_TO_JSVAL(cx, p.receiptCipheredPayload);
    JS_SetProperty(cx, jsobj, "receiptCipheredPayload", receiptCipheredPayload);
    transactionID = SB_STR_TO_JSVAL(cx, p.transactionID);
    JS_SetProperty(cx, jsobj, "transactionID", transactionID);

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
    jsval transactionID;

    name = SB_STR_TO_JSVAL(cx, p.name);

    JS_SetProperty(cx, jsobj, "name", &name);
    id = SB_STR_TO_JSVAL(cx, p.id);
    JS_SetProperty(cx, jsobj, "id", &id);
    title = SB_STR_TO_JSVAL(cx, p.title);
    JS_SetProperty(cx, jsobj, "title", &title);
    description = SB_STR_TO_JSVAL(cx, p.description);
    JS_SetProperty(cx, jsobj, "description", &description);
    price = SB_STR_TO_JSVAL(cx, p.price);
    JS_SetProperty(cx, jsobj, "price", &price);
    currencyCode = SB_STR_TO_JSVAL(cx, p.currencyCode);
    JS_SetProperty(cx, jsobj, "currencyCode", &currencyCode);
    receipt = SB_STR_TO_JSVAL(cx, p.receipt);
    JS_SetProperty(cx, jsobj, "receipt", &receipt);
    receiptCipheredPayload = SB_STR_TO_JSVAL(cx, p.receiptCipheredPayload);
    JS_SetProperty(cx, jsobj, "receiptCipheredPayload", &receiptCipheredPayload);

    transactionID = SB_STR_TO_JSVAL(cx, p.transactionID);
    JS_SetProperty(cx, jsobj, "transactionID", &transactionID);

#endif

    retObj.set(jsobj);
}

void std_vector_product_to_jsval( JSContext *cx, const std::vector<sdkbox::Product>& v, JS::MutableHandleObject retVal)
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
        JS::RootedObject arrElement(cx);
#elif defined(JS_VERSION)
        jsval arrElement;
#endif
        product_to_obj(s_cx, (*it), &arrElement);

#if MOZJS_MAJOR_VERSION >= 31
        if (!JS_SetElement(cx, jsretArr, i, arrElement)) {
#else
        JS::Value arrElementVal;
        arrElementVal.setObjectOrNull(arrElement.get());
        JS::RootedValue arrElementRV(cx, arrElementVal);
        if (!JS_SetElement(cx, jsretArr, i, &arrElementRV)) {
#endif
            break;
        }
        ++i;
    }

    retVal.set(jsretArr);
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

        JS::Value dataVal[2];
        int datalen = 0;

        if (0 == _eventName.compare("onInitialized")) {
            dataVal[0] = JS::BooleanValue(_bValue);
            datalen = 1;
        } else if (0 == _eventName.compare("onSuccess")) {
            JS::RootedObject jsProductObj(cx);
            product_to_obj(cx, _product, &jsProductObj);
            dataVal[0] = JS::ObjectValue(*jsProductObj.get());
            datalen = 1;
        } else if (0 == _eventName.compare("onFailure")) {
            JS::RootedObject jsProductObj(cx);
            product_to_obj(cx, _product, &jsProductObj);
            dataVal[0] = JS::ObjectValue(*jsProductObj.get());
            dataVal[1] = SB_STR_TO_JSVAL(cx, _msg);
            datalen = 2;
        } else if (0 == _eventName.compare("onCanceled")) {
            JS::RootedObject jsProductObj(cx);
            product_to_obj(cx, _product, &jsProductObj);
            dataVal[0] = JS::ObjectValue(*jsProductObj.get());
            datalen = 1;
        } else if (0 == _eventName.compare("onRestored")) {
            JS::RootedObject jsProductObj(cx);
            product_to_obj(cx, _product, &jsProductObj);
            dataVal[0] = JS::ObjectValue(*jsProductObj.get());
            datalen = 1;
        } else if (0 == _eventName.compare("onProductRequestSuccess")) {
            JS::RootedObject jsProductsObj(cx);
            std_vector_product_to_jsval(cx, _products, &jsProductsObj);
            dataVal[0] = JS::ObjectValue(*jsProductsObj.get());
            datalen = 1;
        } else if (0 == _eventName.compare("onProductRequestFailure")) {
            dataVal[0] = SB_STR_TO_JSVAL(cx, _msg);
            datalen = 1;
        } else if (0 == _eventName.compare("onRestoreComplete")) {
            dataVal[0] = JS::BooleanValue(_bValue);
            dataVal[1] = SB_STR_TO_JSVAL(cx, _msg);
            datalen = 2;
        } else {
            return;
        }

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JS::NullValue()) {
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
    bool js_PluginIAPJS_setListener(JSContext *cx, uint32_t argc, JS::Value *vp)
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
        wrapper->setJSDelegate(cx, args.get(0));
        sdkbox::IAP::setListener(wrapper);

        args.rval().setUndefined();
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginIAPJS_setListener : wrong number of arguments");
    return false;
}

#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginIAPJS_IAP_getProducts(JSContext *cx, uint32_t argc, JS::Value *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::vector<sdkbox::Product> ret = sdkbox::IAP::getProducts();
        JS::RootedObject products(cx);
        std_vector_product_to_jsval(cx, ret, &products);
        args.rval().set(JS::ObjectValue(*products.get()));
        return true;
    }
    JS_ReportErrorUTF8(cx, "js_PluginIAPJS_IAP_getProducts : wrong number of arguments");
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
    JS_ReportErrorUTF8(cx, "wrong number of arguments");
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
