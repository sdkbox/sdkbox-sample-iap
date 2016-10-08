/****************************************************************************

 Copyright (c) 2014-2016 SDKBOX Inc

 ****************************************************************************/


#ifndef _SDKBOX_IAPWRAPPER_H_
#define _SDKBOX_IAPWRAPPER_H_

#include <string>
#include <map>
#include <functional>
#include "PluginIAP.h"
#include "json98.h"

#define IAP_TAG "IAP"
#define TAG "IAP"
#define VERSION "2.1.0"

namespace sdkbox
{
    typedef std::vector<Product> TProductList;

    typedef enum
    {
        kPaySuccess = 0,
        kPayFail = 1,
        kPayCancel = 2,
        kPayRestored = 3,
        kPayTimeOut = 4,
        kPaySuccessAndNeedsUserSideValidation=5,     // results needs local validation.

        // added for server side validation return values.
        kPaySuccessAndValidationAuthenticated,    // pay success locally, and authenticated by the IAP server
        kPaySuccessAndValidationNotAuthenticated, // pay success locally, but the server said the receipt is not valid.
        kPaySuccessAndValidationTimeout,          // pay success locally, but timeout in the IAP server
        kPaySuccessAndValidationError,            // pay success locally, and error in the IAP server


    } PayResultCode;

    typedef enum
    {
        RequestSuccees = 0,
        RequestFail = 1,
        RequestTimeout = 2,
    } ProductRequestCode;


    class IAPWrapper
    {
    public:

        static IAPWrapper *getInstance();
        static std::string _productsStringDef;

        virtual void init(const char* jsonconfig = 0)=0;
        virtual void setDebug(bool debug)=0;
        virtual void purchase(const std::string &name)=0;
        virtual void restorePurchase()=0;
        virtual void refresh()=0;
        virtual void enableUserSideVerification( bool b )=0;
        virtual void setListener(IAPListener *listener)=0;
        virtual void removeListener()=0;
        virtual IAPListener* getListener() const=0;

        /**
         @brief pay result callback
         */
        virtual void onInitialized(bool ok)=0;
        virtual void onPurchaseResult(PayResultCode code, const char *msg)=0;
        virtual void onPurchaseResultWithPendingValidation( PayResultCode code, const std::string& product_id, const std::string& receipt, const std::string& payload )=0;
        virtual void onProductRequestResult(ProductRequestCode code, const char *msg, const char *data) = 0;
        virtual void onRestoreComplete(bool ok, const std::string &msg)= 0;
        virtual Product findProduct(const std::string &productID) = 0;
        virtual TProductList getProducts() = 0;
		virtual void resetPurchase() = 0;
    };

    class IAPWrapperDisabled : public IAPWrapper {
    public:
        void init(const char* jsonconfig = 0) {}
        void setDebug(bool debug) {}
        void purchase(const std::string &name) {}
        void restorePurchase() {}
        void refresh() {}
        void enableUserSideVerification( bool b ) {}
        void setListener(IAPListener *listener) {}
        void removeListener() {}
        IAPListener* getListener() const { return NULL; }

        /**
         @brief pay result callback
         */
        void onInitialized(bool ok) {}
        void onPurchaseResult(PayResultCode code, const char *msg) {}
        void onPurchaseResultWithPendingValidation( PayResultCode code, const std::string& product_id, const std::string& receipt, const std::string& payload ) {}
        void onProductRequestResult(ProductRequestCode code, const char *msg, const char *data) {}
        void onRestoreComplete(bool ok, const std::string &msg) {}
        Product findProduct(const std::string &productID) { return Product(); }
        TProductList getProducts() { return TProductList(); }
        void resetPurchase() {}
    };

    class IAPWrapperEnabled : public IAPWrapper
    {
    public:
        IAPWrapperEnabled();
        virtual ~IAPWrapperEnabled();

        void init(const char* jsonconfig = 0);
        void setDebug(bool debug);
        void purchase(const std::string &name);
        void restorePurchase();
        void refresh();
        void enableUserSideVerification( bool b );
        void setListener(IAPListener *listener);
        void removeListener();
        IAPListener* getListener() const;

        /**
        @brief pay result callback
        */
        void onInitialized(bool ok);
        void onPurchaseResult(PayResultCode code, const char *msg);
        void onPurchaseResultWithPendingValidation( PayResultCode code, const std::string& product_id, const std::string& receipt, const std::string& payload );
        void onProductRequestResult(ProductRequestCode code, const char *msg, const char *data);
        void onRestoreComplete(bool ok, const std::string &msg);
        Product findProduct(const std::string &productID);
        TProductList getProducts();
        void resetPurchase();

    protected:

        void __notifyByProduct( const Product& p );
        void nativeInit(const Json &config);
        void nativeRefresh(const std::string &products);
        void nativePurchase(const Product &p);
        void nativeUserSideVerification(bool enable);
        void populateProductData(const TProductList &data);
        bool isNetAvailable();
        bool _paying;
        Json createTrackingData(const Product& p);

        bool _userSideVerification;
        std::string _curProduct;
        IAPListener *_listener;
        std::map<std::string, Product> _iapItems;
    };

}

#endif /* _SDKBOX_IAPWRAPPER_H_ */
