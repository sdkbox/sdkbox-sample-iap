#ifndef __PluginIAPJS_h__
#define __PluginIAPJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginIAPJS_IAP(JSContext *cx, JS::HandleObject global);
void register_all_PluginIAPJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginIAPJS_IAP(JSContext *cx, JSObject* global);
void register_all_PluginIAPJS(JSContext* cx, JSObject* obj);
#endif
#endif

