
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace sdkbox;

#define SCREENLOG_IMPLEMENTATION
#include "ScreenLog.h"

template <typename T> std::string tostr(const T& t) { std::ostringstream os; os<<t; return os.str(); }

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    ScreenLog::getInstance()->setLevelMask( LL_DEBUG | LL_INFO | LL_WARNING | LL_ERROR | LL_FATAL );
    ScreenLog::getInstance()->setTimeoutSeconds( 0xFFFF );
    ScreenLog::getInstance()->attachToScene( scene );

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    INFO("Sample Startup");

    // add logo
    auto winsize = Director::getInstance()->getWinSize();
    auto logo = Sprite::create("Logo.png");
    auto logoSize = logo->getContentSize();
    logo->setPosition(Vec2(logoSize.width / 2,
                           winsize.height - logoSize.height / 2));
    addChild(logo);

    // add quit button
    auto label = Label::createWithSystemFont("QUIT", "sans", 32);
    auto quit = MenuItemLabel::create(label, [](Ref*){
        exit(0);
    });
    auto labelSize = label->getContentSize();
    quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
                           -winsize.height / 2 + labelSize.height / 2 + 16));
    addChild(Menu::create(quit, NULL));

    // add test menu
    createTestMenu();

    return true;
}

void HelloWorld::createTestMenu()
{
    IAP::setDebug(true);
    IAP::setListener(this);
    IAP::init();

    MenuItemFont::setFontName("sans");
    Size size = Director::getInstance()->getWinSize();

    _coinCount = 0;
    _txtCoin = Label::createWithSystemFont("0", "sans", 24);
    _txtCoin->setPosition(Vec2(size.width / 2, 60));
    addChild(_txtCoin);

    auto menu = Menu::create(MenuItemFont::create("load products", CC_CALLBACK_1(HelloWorld::onRequestIAP, this)),
                             MenuItemFont::create("restore purchase", CC_CALLBACK_1(HelloWorld::onRestoreIAP, this)),
                             NULL);

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(Vec2(size.width/2, size.height - 120));
    addChild(menu);

    _iapMenu = Menu::create(NULL);
    addChild(_iapMenu);
}


void HelloWorld::onRequestIAP(cocos2d::Ref* sender)
{
    IAP::refresh();
}

void HelloWorld::onRestoreIAP(cocos2d::Ref* sender)
{
    IAP::restore();
}

void HelloWorld::onIAP(cocos2d::Ref *sender)
{
    int i = dynamic_cast<MenuItemFont*>(sender)->getTag();
    auto const &product = _products[i];
    INFO("Start IAP %s", product.name.c_str());
    IAP::purchase(product.name);
}

void HelloWorld::onInitialized(bool ok)
{
    INFO("%s : %d", __func__, ok);
}

void HelloWorld::onSuccess(const Product &p)
{
    if (p.name == "coin_package") {
        INFO("Purchase complete: coin_package");
        _coinCount += 1000;
        _txtCoin->setString(tostr(_coinCount));
    }
    else if (p.name == "coin_package2") {
        INFO("Purchase complete: coin_package2");
        _coinCount += 5000;
        _txtCoin->setString(tostr(_coinCount));
    }
    else if (p.name == "remove_ads") {
        INFO("Purchase complete: Remove Ads");
    }

    INFO("Purchase Success: %s", p.id.c_str());

    INFO("IAP: ========= IAP Item =========");
    INFO("IAP: Name: %s", p.name.c_str());
    INFO("IAP: ID: %s", p.id.c_str());
    INFO("IAP: Title: %s", p.title.c_str());
    INFO("IAP: Desc: %s", p.description.c_str());
    INFO("IAP: Price: %s", p.price.c_str());
    INFO("IAP: Price Value: %f", p.priceValue);
    INFO("IAP: Currency: %s", p.currencyCode.c_str());
    INFO("IAP: transactionID: %s", p.transactionID.c_str());
    INFO("IAP: receipt: %s", p.receipt.c_str());
    INFO("IAP: receipt data: %s", p.receiptCipheredPayload.c_str());
}

void HelloWorld::onFailure(const Product &p, const std::string &msg)
{
    INFO("Purchase Failed: %s", msg.c_str());
}

void HelloWorld::onCanceled(const Product &p)
{
    INFO("Purchase Canceled: %s", p.id.c_str());
}

void HelloWorld::onRestored(const Product& p)
{
    INFO("Purchase Restored: %s", p.name.c_str());
}

void HelloWorld::updateIAP(const std::vector<sdkbox::Product>& products)
{
    _iapMenu->removeAllChildren();
    _products = products;


    for (int i=0; i < _products.size(); i++)
    {
        INFO("IAP: ========= IAP Item =========");
        INFO("IAP: Name: %s", _products[i].name.c_str());
        INFO("IAP: ID: %s", _products[i].id.c_str());
        INFO("IAP: Title: %s", _products[i].title.c_str());
        INFO("IAP: Desc: %s", _products[i].description.c_str());
        INFO("IAP: Price: %s", _products[i].price.c_str());
        INFO("IAP: Price Value: %f", _products[i].priceValue);
        INFO("IAP: Currency: %s", _products[i].currencyCode.c_str());

        auto item = MenuItemFont::create(_products[i].name, CC_CALLBACK_1(HelloWorld::onIAP, this));
        item->setTag(i);
        _iapMenu->addChild(item);
    }

    Size size = Director::getInstance()->getWinSize();
    _iapMenu->alignItemsVerticallyWithPadding(5);
    _iapMenu->setPosition(Vec2(size.width/2, size.height / 2));
}

void HelloWorld::onProductRequestSuccess(const std::vector<Product> &products)
{
    updateIAP(products);
}

void HelloWorld::onProductRequestFailure(const std::string &msg)
{
    INFO("Fail to load products");
}

void HelloWorld::onRestoreComplete(bool ok, const std::string &msg)
{
    INFO("%s:%d:%s", __func__, ok, msg.data());
}
