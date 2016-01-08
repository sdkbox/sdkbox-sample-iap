#include "jsapi.h"
#include "jsfriendapi.h"
#include <map>
#include <vector>
#include <string>

#if MOZJS_MAJOR_VERSION >= 31
typedef JS::HandleObject one_JSObject;
#else
typedef JSObject* one_JSObject;
#endif

namespace sdkbox
{
// Spidermonkey v186+
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
    bool js_to_number(JSContext *cx, JS::HandleValue v, double *dp);
    bool jsval_to_std_map_string_string(JSContext *cx, JS::HandleValue v, std::map<std::string,std::string> *ret);
    void getJsObjOrCreat(JSContext* cx, JS::HandleObject jsObj, const char* name, JS::RootedObject* retObj);
#else
    JSBool js_to_number(JSContext *cx, jsval v, double *dp);
    JSBool jsval_to_std_map_string_string(JSContext *cx, jsval v, std::map<std::string,std::string> *ret);
    jsval getJsObjOrCreat(JSContext* cx, JSObject* jsObj, const char* name, JSObject** retObj);
    jsval std_vector_string_to_jsval(JSContext* cx, const std::vector<std::string>& arr);
    JSBool jsval_to_std_vector_string(JSContext* cx, jsval v, std::vector<std::string>* ret);
#endif
    jsval std_map_string_int_to_jsval(JSContext* cx, const std::map<std::string, int>& v);
    jsval std_map_string_string_to_jsval(JSContext* cx, const std::map<std::string, std::string>& v);
}
