#include "SDKBoxJSHelper.h"
#include <string>
#include <sstream>
#include "cocos2d_specifics.hpp"
#include "Sdkbox/Sdkbox.h"

#if defined(MOZJS_MAJOR_VERSION)
#include "cocos2d_specifics.hpp"
#endif

namespace sdkbox
{

    // Spidermonkey v186+
#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 26
    bool js_to_number(JSContext *cx, JS::HandleValue v, double *dp)
    {
        return JS::ToNumber( cx, v, dp) && !isnan(*dp);
    }

    bool jsval_to_std_map_string_string(JSContext *cx, JS::HandleValue v, std::map<std::string,std::string> *ret)
    {
        cocos2d::ValueMap value;
        bool ok = jsval_to_ccvaluemap(cx, v, &value);
        if (!ok)
        {
            return ok;
        }
        else
        {
            for (cocos2d::ValueMap::iterator it = value.begin(); it != value.end(); it++)
            {
                ret->insert(std::make_pair(it->first, it->second.asString()));
            }
        }

        return ok;
    }

#if MOZJS_MAJOR_VERSION < 33
    void get_or_create_js_obj(JSContext* cx, JS::HandleObject obj, const std::string &name, JS::MutableHandleObject jsObj)
    {
        JS::RootedValue nsval(cx);
        JS_GetProperty(cx, obj, name.c_str(), &nsval);
        if (nsval == JSVAL_VOID) {
            jsObj.set(JS_NewObject(cx, NULL, NULL, NULL));
            nsval = OBJECT_TO_JSVAL(jsObj);
            JS_SetProperty(cx, obj, name.c_str(), nsval);
        } else {
            jsObj.set(nsval.toObjectOrNull());
        }
    }
#endif

    void getJsObjOrCreat(JSContext* cx, JS::HandleObject jsObj, const char* name, JS::RootedObject* retObj) {
        JS::RootedObject parent(cx);
        JS::RootedObject tempObj(cx);
        bool first = true;

        std::stringstream ss(name);
        std::string sub;
        const char* subChar;
        while(getline(ss, sub, '.')) {
            if(sub.empty())continue;

            subChar = sub.c_str();
            if (first) {
                get_or_create_js_obj(cx, jsObj, subChar, &tempObj);
                first = false;
            } else {
                parent = tempObj;
                get_or_create_js_obj(cx, parent, subChar, &tempObj);
            }
        }

        *retObj = tempObj;
    }

#else
    JSBool js_to_number(JSContext *cx, jsval v, double *dp)
    {
        return JS::ToNumber( cx, v, dp) && !isnan(*dp);
    }

    bool jsval_to_std_map_string_string(JSContext *cx, JS::HandleValue v, std::map<std::string,std::string> *ret)
    {
        cocos2d::ValueMap value;
        bool ok = jsval_to_ccvaluemap(cx, v, &value);
        if (!ok)
        {
            return ok;
        }
        else
        {
            for (cocos2d::ValueMap::iterator it = value.begin(); it != value.end(); it++)
            {
                ret->insert(std::make_pair(it->first, it->second.asString()));
            }
        }

        return ok;
    }

    jsval getJsObjOrCreat(JSContext* cx, JSObject* jsObj, const char* name, JSObject** retObj) {
        JSObject* parent = NULL;
        JSObject* tempObj = jsObj;
        jsval tempVal;

        std::stringstream ss(name);
        std::string sub;
        const char* subChar;

        while(getline(ss, sub, '.')) {
            if(sub.empty())continue;

            subChar = sub.c_str();
            parent = tempObj;
            JS_GetProperty(cx, parent, subChar, &tempVal);
            if (tempVal == JSVAL_VOID) {
                tempObj = JS_NewObject(cx, NULL, NULL, NULL);
                tempVal = OBJECT_TO_JSVAL(tempObj);
                JS_SetProperty(cx, parent, subChar, &tempVal);
            } else {
                JS_ValueToObject(cx, tempVal, &tempObj);
            }
        }

        *retObj = tempObj;
        return tempVal;
    }

#endif

    // Spidermonkey v186 and earlier
#else
    JSBool js_to_number(JSContext *cx, jsval v, double *dp)
    {
        return JS_ValueToNumber(cx, v, dp);
    }

    JSBool jsval_to_std_map_string_string(JSContext *cx, jsval v, std::map<std::string,std::string> *ret)
    {
        cocos2d::CCDictionary* value;
        bool ok = jsval_to_ccdictionary(cx, v, &value);
        if (!ok)
        {
            return ok;
        }
        else
        {
            CCDictElement* pElement;
            CCDICT_FOREACH(value, pElement)
            {
                const char*key = pElement->getStrKey();
                CCString *v = (CCString*) pElement->getObject();
                ret->insert(std::make_pair(key, v->getCString()));
            }
        }

        return ok;
    }

    jsval getJsObjOrCreat(JSContext* cx, JSObject* jsObj, const char* name, JSObject** retObj) {
        JSObject* parent = NULL;
        JSObject* tempObj = jsObj;
        jsval tempVal;

        std::stringstream ss(name);
        std::string sub;
        const char* subChar;

        while(getline(ss, sub, '.')) {
            if(sub.empty())continue;

            subChar = sub.c_str();
            parent = tempObj;
            JS_GetProperty(cx, parent, subChar, &tempVal);
            if (tempVal == JSVAL_VOID) {
                tempObj = JS_NewObject(cx, NULL, NULL, NULL);
                tempVal = OBJECT_TO_JSVAL(tempObj);
                JS_SetProperty(cx, parent, subChar, &tempVal);
            } else {
                JS_ValueToObject(cx, tempVal, &tempObj);
            }
        }

        *retObj = tempObj;
        return tempVal;
    }

    jsval std_vector_string_to_jsval(JSContext* cx, const std::vector<std::string>& arr) {

        JSObject *jsretArr = JS_NewArrayObject(cx, 0, NULL);

        int i = 0;
        for(std::vector<std::string>::const_iterator iter = arr.begin(); iter != arr.end(); ++iter, ++i) {
            jsval arrElement = c_string_to_jsval(cx, iter->c_str());
            if(!JS_SetElement(cx, jsretArr, i, &arrElement)) {
                break;
            }
        }
        return OBJECT_TO_JSVAL(jsretArr);
    }

    JSBool jsval_to_std_vector_string(JSContext* cx, jsval v, std::vector<std::string>* ret) {
        JSObject *jsobj;
        JSBool ok = JS_ValueToObject( cx, v, &jsobj );
        JSB_PRECONDITION2( ok, cx, JS_FALSE, "Error converting value to object");
        JSB_PRECONDITION2( jsobj && JS_IsArrayObject( cx, jsobj),  cx, JS_FALSE, "Object must be an array");

        uint32_t len = 0;
        JS_GetArrayLength(cx, jsobj, &len);

        for (uint32_t i=0; i < len; i++) {
            jsval elt;
            if (JS_GetElement(cx, jsobj, i, &elt)) {

                if (JSVAL_IS_STRING(elt))
                {
                    JSStringWrapper str(JSVAL_TO_STRING(elt));
                    ret->push_back(str.get());
                }
            }
        }

        return JS_TRUE;
    }

#endif
    
    jsval std_map_string_int_to_jsval(JSContext* cx, const std::map<std::string, int>& v) {
        JS::RootedObject proto(cx);
        JS::RootedObject parent(cx);
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
        JS::RootedObject jsRet(cx, JS_NewObject(cx, NULL, proto, parent));
#else
        JSObject *jsRet = JS_NewObject(cx, NULL, NULL, NULL);
#endif
        
        for (auto iter = v.begin(); iter != v.end(); ++iter) {
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
            JS::RootedValue element(cx);
#else
            jsval element;
#endif
            
            std::string key = iter->first;
            int val = iter->second;
            
            element = INT_TO_JSVAL(val);

            if (!key.empty()) {
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
                JS_SetProperty(cx, jsRet, key.c_str(), element);
#else
                JS_SetProperty(cx, jsRet, key.c_str(), &element);
#endif
            }
        }
        return OBJECT_TO_JSVAL(jsRet);
    }

    jsval std_map_string_string_to_jsval(JSContext* cx, const std::map<std::string, std::string>& v) {
        JS::RootedObject proto(cx);
        JS::RootedObject parent(cx);
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
        JS::RootedObject jsRet(cx, JS_NewObject(cx, NULL, proto, parent));
#else
        JSObject *jsRet = JS_NewObject(cx, NULL, NULL, NULL);
#endif
        
        for (auto iter = v.begin(); iter != v.end(); ++iter) {
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
            JS::RootedValue element(cx);
#else
            jsval element;
#endif
            
            std::string key = iter->first;
            std::string val = iter->second;

            element = std_string_to_jsval(cx, val);
            
            if (!key.empty()) {
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
                JS_SetProperty(cx, jsRet, key.c_str(), element);
#else
                JS_SetProperty(cx, jsRet, key.c_str(), &element);
#endif
            }
        }
        return OBJECT_TO_JSVAL(jsRet);
    }

}
