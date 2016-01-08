#ifndef __PluginIAPJS_h__
#define __PluginIAPJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_sdkbox_IAP_class;
extern JSObject *jsb_sdkbox_IAP_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginIAPJS_IAP(JSContext *cx, JS::HandleObject global);
void register_all_PluginIAPJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginIAPJS_IAP(JSContext *cx, JSObject* global);
void register_all_PluginIAPJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginIAPJS_IAP_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginIAPJS_IAP_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginIAPJS_IAP_purchase(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginIAPJS_IAP_purchase(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginIAPJS_IAP_restore(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginIAPJS_IAP_restore(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginIAPJS_IAP_refresh(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginIAPJS_IAP_refresh(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginIAPJS_IAP_init(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginIAPJS_IAP_init(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginIAPJS_IAP_setDebug(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginIAPJS_IAP_setDebug(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginIAPJS_IAP_removeListener(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginIAPJS_IAP_removeListener(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#endif

