
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace sdkbox;

template <typename T> std::string tostr(const T& t) { std::ostringstream os; os<<t; return os.str(); }

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

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

    CCLOG("Sample Startup");

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
    int i = reinterpret_cast<int>(dynamic_cast<MenuItemFont*>(sender)->getUserData());
    auto const &product = _products[i];
    CCLOG("Start IAP %s", product.name.c_str());
    IAP::purchase(product.name);
}

void HelloWorld::onInitialized(bool ok)
{
    CCLOG("%s : %d", __func__, ok);
}

void HelloWorld::onSuccess(const Product &p)
{
    if (p.name == "coin_package") {
        CCLOG("Purchase complete: coin_package");
        _coinCount += 1000;
        _txtCoin->setString(tostr(_coinCount));
    }
    else if (p.name == "coin_package2") {
        CCLOG("Purchase complete: coin_package2");
        _coinCount += 5000;
        _txtCoin->setString(tostr(_coinCount));
    }
    else if (p.name == "remove_ads") {
        CCLOG("Purchase complete: Remove Ads");
    }

    CCLOG("Purchase Success: %s", p.id.c_str());
}

void HelloWorld::onFailure(const Product &p, const std::string &msg)
{
    CCLOG("Purchase Failed: %s", msg.c_str());
}

void HelloWorld::onCanceled(const Product &p)
{
    CCLOG("Purchase Canceled: %s", p.id.c_str());
}

void HelloWorld::onRestored(const Product& p)
{
    CCLOG("Purchase Restored: %s", p.name.c_str());
}

void HelloWorld::updateIAP(const std::vector<sdkbox::Product>& products)
{
    _iapMenu->removeAllChildren();
    _products = products;


    for (int i=0; i < _products.size(); i++)
    {
        CCLOG("IAP: ========= IAP Item =========");
        CCLOG("IAP: Name: %s", _products[i].name.c_str());
        CCLOG("IAP: ID: %s", _products[i].id.c_str());
        CCLOG("IAP: Title: %s", _products[i].title.c_str());
        CCLOG("IAP: Desc: %s", _products[i].description.c_str());
        CCLOG("IAP: Price: %s", _products[i].price.c_str());
        CCLOG("IAP: Price Value: %f", _products[i].priceValue);

        auto item = MenuItemFont::create(_products[i].name, CC_CALLBACK_1(HelloWorld::onIAP, this));
        item->setUserData(reinterpret_cast<void*>(i));
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
    CCLOG("Fail to load products");
}

void HelloWorld::onRestoreComplete(bool ok, const std::string &msg)
{
    CCLOG("%s:%d:%s", __func__, ok, msg.data());
}
