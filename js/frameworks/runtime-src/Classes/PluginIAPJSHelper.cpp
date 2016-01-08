#include "PluginIAPJSHelper.h"
#include "cocos2d_specifics.hpp"
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

#else
    JSObject* jsobj = JS_NewObject(cx, NULL, NULL, NULL);
    JS::RootedValue name(cx);
    JS::RootedValue id(cx);
    JS::RootedValue title(cx);
    JS::RootedValue description(cx);
    JS::RootedValue price(cx);

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
#endif
#elif defined(JS_VERSION)
    JSObject* jsobj = JS_NewObject(cx, NULL, NULL, NULL);
    jsval name;
    jsval id;
    jsval title;
    jsval description;
    jsval price;

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
#if COCOS2D_VERSION < 0x00030000
#else
#define CCObject Ref
#define CCDirector Director
#define sharedDirector getInstance
#endif

class JsIAPCallbackObj : public CCObject
{
public:
    static JsIAPCallbackObj *create(const std::string &eventName, JSObject *handler, const std::vector<sdkbox::Product>& products)
    {
        JsIAPCallbackObj *obj = new JsIAPCallbackObj(eventName, handler, products);
        obj->autorelease();
        return obj;
    }

    void start()
    {
        CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(JsIAPCallbackObj::callback), this, 0.1, false);
    }

    void callback(float dt)
    {
        if (!s_cx)
        {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = _eventName.data();

        JS::RootedObject obj(cx, m_jsHandler);
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

        jsval dataVal[1];
        jsval value = std_vector_product_to_jsval(cx, m_products);
        dataVal[0] = value;

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(1, dataVal), &retval);
#else
            JS_CallFunctionName(cx, obj, func_name, sizeof(dataVal)/sizeof(*dataVal), dataVal, &retval);
#endif
        }

        CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
        release();
    }

private:
    JsIAPCallbackObj(const std::string &eventName, JSObject *handler, const std::vector<sdkbox::Product>& products)
    : _eventName(eventName)
    , m_jsHandler(handler)
    {
        m_products = products;
        retain();
    }

    std::vector<sdkbox::Product> m_products;
    JSObject* m_jsHandler;
    std::string _eventName;
}; // JsIAPCallbackObj


class IAPWrapperJS : public sdkbox::IAPListener
{
private:
    JSObject* _JSDelegate;
public:
    void setJSDelegate(JSObject* delegate)
    {
        _JSDelegate = delegate;
    }

    JSObject* getJSDelegate()
    {
        return _JSDelegate;
    }

    void onSuccess(const sdkbox::Product& info)
    {
        if (!s_cx)
        {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = "onSuccess";

        JS::RootedObject obj(cx, _JSDelegate);
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
        jsval dataVal[1];

        jsval value = OBJECT_TO_JSVAL(product_to_obj(s_cx, info));

        dataVal[0] = value;

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(sizeof(dataVal)/sizeof(*dataVal), dataVal), &retval);
#else
            JS_CallFunctionName(cx, obj, func_name, sizeof(dataVal)/sizeof(*dataVal), dataVal, &retval);
#endif
        }
    }

    void onFailure(const sdkbox::Product& info, const std::string& msg)
    {
        if (!s_cx)
        {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = "onFailure";

        JS::RootedObject obj(cx, _JSDelegate);
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
        jsval value = OBJECT_TO_JSVAL(product_to_obj(s_cx, info));

        dataVal[0] = value;
        dataVal[1] = std_string_to_jsval(cx, msg);

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(sizeof(dataVal)/sizeof(*dataVal), dataVal), &retval);
#else
            JS_CallFunctionName(cx, obj, func_name, sizeof(dataVal)/sizeof(*dataVal), dataVal, &retval);
#endif
        }
    }

    void onCanceled(const sdkbox::Product& info)
    {
        if (!s_cx)
        {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = "onCanceled";

        JS::RootedObject obj(cx, _JSDelegate);
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

        jsval dataVal[1];
        jsval value = OBJECT_TO_JSVAL(product_to_obj(s_cx, info));

        dataVal[0] = value;

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(sizeof(dataVal)/sizeof(*dataVal), dataVal), &retval);
#else
            JS_CallFunctionName(cx, obj, func_name, sizeof(dataVal)/sizeof(*dataVal), dataVal, &retval);
#endif
        }
    }

    void onRestored(const sdkbox::Product& info)
    {
        if (!s_cx)
        {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = "onRestored";

        JS::RootedObject obj(cx, _JSDelegate);
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
        jsval dataVal[1];
        jsval value = OBJECT_TO_JSVAL(product_to_obj(s_cx, info));

        dataVal[0] = value;

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(sizeof(dataVal)/sizeof(*dataVal), dataVal), &retval);
#else
            JS_CallFunctionName(cx, obj, func_name, sizeof(dataVal)/sizeof(*dataVal), dataVal, &retval);
#endif
        }
    }

    void onProductRequestSuccess(const std::vector<sdkbox::Product>& products)
    {
        JsIAPCallbackObj::create("onProductRequestSuccess", _JSDelegate, products)->start();
    }

    void onProductRequestFailure(const std::string& msg)
    {
        if (!s_cx)
        {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = "onProductRequestFailure";

        JS::RootedObject obj(cx, _JSDelegate);
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
        jsval dataVal[1];

        dataVal[0] = std_string_to_jsval(cx, msg);

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(sizeof(dataVal)/sizeof(*dataVal), dataVal), &retval);
#else
            JS_CallFunctionName(cx, obj, func_name, sizeof(dataVal)/sizeof(*dataVal), dataVal, &retval);
#endif
        }
    }

    void onInitialized(bool ok)
    {
        if (!s_cx)
        {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = "onInitialized";

        JS::RootedObject obj(cx, _JSDelegate);
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
        jsval dataVal[1];

        dataVal[0] = BOOLEAN_TO_JSVAL(ok);

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(sizeof(dataVal)/sizeof(*dataVal), dataVal), &retval);
#else
            JS_CallFunctionName(cx, obj, func_name, sizeof(dataVal)/sizeof(*dataVal), dataVal, &retval);
#endif
        }
    }

    void onRestoreComplete(bool ok, const std::string& msg)
    {
        if (!s_cx)
        {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = "onRestoreComplete";

        JS::RootedObject obj(cx, _JSDelegate);
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

        dataVal[0] = BOOLEAN_TO_JSVAL(ok);
        dataVal[1] = std_string_to_jsval(cx, msg);

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(sizeof(dataVal)/sizeof(*dataVal), dataVal), &retval);
#else
            JS_CallFunctionName(cx, obj, func_name, sizeof(dataVal)/sizeof(*dataVal), dataVal, &retval);
#endif
        }
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
        JSObject *tmpObj = args.get(0).toObjectOrNull();

        JSB_PRECONDITION2(ok, cx, false, "js_PluginIAPJS_setListener : Error processing arguments");
        IAPWrapperJS* wrapper = new IAPWrapperJS();
        wrapper->setJSDelegate(tmpObj);
        sdkbox::IAP::setListener(wrapper);

        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginIAPJS_setListener : wrong number of arguments");
    return false;
}


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginIAPJS_helper(JSContext* cx, JS::HandleObject global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, global, "sdkbox.IAP", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginIAPJS_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
#else
void register_all_PluginIAPJS_helper(JSContext* cx, JSObject* global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, JS::RootedObject(cx, global), "sdkbox.IAP", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginIAPJS_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginIAPJS_helper(JSContext* cx, JSObject* global) {
    jsval pluginVal;
    JSObject* pluginObj;
    pluginVal = sdkbox::getJsObjOrCreat(cx, global, "sdkbox.IAP", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginIAPJS_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}
#endif
