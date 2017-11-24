/****************************************************************************

 Copyright (c) 2014-2016 SDKBOX Inc

 ****************************************************************************/

#ifndef _SDKBOX_IAP_H_
#define _SDKBOX_IAP_H_

#include <string>
#include <vector>

namespace sdkbox
{
    enum IAP_Type
    {
        CONSUMABLE = 0,
        NON_CONSUMABLE
    };

    // Product from SDKBox In App Purchase
    struct Product
    {
        Product() : name(""), id(""), title(""), description(""),
        priceValue(0), price(""), currencyCode(""), receiptCipheredPayload(""),
        receipt(""), transactionID("") {}

        // The name specified in sdkbox_config.json
        std::string name;

        // The product id of an In App Purchase
        std::string id;

        // Type of iap item
        IAP_Type type;

        // The title of the IAP item
        std::string title;

        // The description of the IAP item
        std::string description;

        // Price value in float
        float priceValue;

        // Localized price
        std::string price;

        // price currency code
        std::string currencyCode;

        // cyphered payload
        std::string receiptCipheredPayload;

        // receipt info. will be empty string for iOS
        std::string receipt;

        // unique                     id
        std::string transactionID;
    };

    /**
    * The listener for SDKBox IAP
    */
    class IAPListener
    {
    public:
        /**
        * Called when IAP initialized
        */
        virtual void onInitialized(bool success) = 0;

        /**
        * Called when an IAP processed successfully
        */
        virtual void onSuccess(const Product& p) = 0;

        /**
        * Called when an IAP fails
        */
        virtual void onFailure(const Product& p, const std::string& msg) = 0;

        /**
        * Called when user canceled the IAP
        */
        virtual void onCanceled(const Product& p) = 0;

        /**
        * Called when server returns the IAP items user already purchased
        * @note this callback will be called multiple times if there are multiple IAP
        */
        virtual void onRestored(const Product& p) = 0;

        /**
        * Called the product request is successful, usually developers use product request to update the latest info(title, price) from IAP
        */
        virtual void onProductRequestSuccess(const std::vector<Product>& products) = 0;

        /**
        * Called when the product request fails
        */
        virtual void onProductRequestFailure(const std::string& msg) = 0;

        /**
         * Called when the restore completed
         */
        virtual void onRestoreComplete(bool ok, const std::string &msg) = 0;

        virtual bool onShouldAddStorePayment(const std::string& productName) { return true; };
        virtual void onFetchStorePromotionOrder(const std::vector<std::string>& productNames, const std::string& error) {};
        virtual void onFetchStorePromotionVisibility(const std::string productName, bool visibility, const std::string& error) {};
        virtual void onUpdateStorePromotionOrder(const std::string& error) {};
        virtual void onUpdateStorePromotionVisibility(const std::string& error) {};

    };

    class IAP
    {
    public:

        /**
        * Initialize SDKBox IAP
        */
        static void init(const char* jsonconfig = 0);

        /**
        * Enable/disable debug logging
        */
        static void setDebug(bool debug);

        /**
        * Get all the products
        */
        static std::vector<Product> getProducts();

        /**
        * Make a purchase request
        *
        * @Param name is the name of the item specified in sdkbox_config.json
        */
        static void purchase(const std::string& name);

        /**
        * Refresh the IAP data(title, price, description)
        */
        static void refresh();

        /**
        * Restore purchase
        */
        static void restore();

        /**
        * Set listener for IAP
        */
        static void setListener(IAPListener* listener);

        /**
        * Remove listener for IAP
        */
        static void removeListener();

        static void enableUserSideVerification( bool );

        /**
         * get auto invoke finishTransaction flag
         */
        static bool isAutoFinishTransaction();

        /**
         * set auto invoke finishTransaction flag
         */
        static void setAutoFinishTransaction(bool b);

        /**
         * to invoke ios finishTransaction api
         */
        static void finishTransaction(const std::string productid);

        static void fetchStorePromotionOrder();
        static void updateStorePromotionOrder(const std::vector<std::string>& productNames);
        static void fetchStorePromotionVisibility(const std::string& productName);
        static void updateStorePromotionVisibility(const std::string& productName, bool visibility);

    };
}

#endif
