
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    txtCoin:null,
    menuIAP:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        this.log("Sample Startup")

        this.createTestMenu();

        var winsize = cc.winSize;

        var logo = new cc.Sprite("res/Logo.png");
        var logoSize = logo.getContentSize();
        logo.x = logoSize.width / 2;
        logo.y = winsize.height - logoSize.height / 2;
        this.addChild(logo);

        var quit = new cc.MenuItemLabel(new cc.LabelTTF("QUIT", "sans", 32), function() {
            cc.log("QUIT");
        });
        var menu = new cc.Menu(quit);
        var size = quit.getContentSize();
        menu.x = winsize.width - size.width / 2 - 16;
        menu.y = size.height / 2 + 16;
        this.addChild(menu);

        return true;
    },

    printProduct:function(p) {
        self.log("======The product info======");
        self.log("name=", p.name);
        self.log("title=", p.title);
        self.log("description=", p.description);
        self.log("price=", p.price);
        self.log("priceValue=", p.priceValue);
        self.log("currencyCode=", p.currencyCode);
        self.log("receipt=", p.receipt);
        self.log("receiptCipheredPayload=", p.receiptCipheredPayload);
        self.log("transactionID=", p.transactionID);
        self.log("");
    },


    createTestMenu:function() {
        var self = this;

        cc.MenuItemFont.setFontName("sans");

        sdkbox.IAP.init();
        sdkbox.IAP.setDebug(true);
        sdkbox.IAP.setListener({
            onSuccess : function (product) {
                //Purchase success
                self.log("Purchase successful: " + product.name);
                self.printProduct(product);
            },
            onFailure : function (product, msg) {
                //Purchase failed
                //msg is the error message
                self.log("Purchase failed: " + product.name + " error: " + msg);

            },
            onCanceled : function (product) {
                //Purchase was canceled by user
                self.log("Purchase canceled: " + product.name);
            },
            onRestored : function (product) {
                //Purchase restored
                self.log("Restored: " + product.name);

                self.printProduct(product);
            },
            onProductRequestSuccess : function (products) {
                self.menuIAP.removeAllChildren();
                //Returns you the data for all the iap products
                //You can get each item using following method
                for (var i = 0; i < products.length; i++) {
                    self.log("================");
                    self.log("name: " + products[i].name);
                    self.log("price: " + products[i].price);
                    self.log("priceValue: " + products[i].priceValue);
                    self.log("================");

                    (function() {
                        var name = products[i].name;
                        var btn = new cc.MenuItemFont(name, function() {
                            self.log("purchase: " + name);
                            sdkbox.IAP.purchase(name);
                        });
                        self.menuIAP.addChild(btn);
                    }());
                }
                self.menuIAP.alignItemsVerticallyWithPadding(5);
            },
            onProductRequestFailure : function (msg) {
                //When product refresh request fails.
                self.log("Failed to get products");
            }
        });

        var size = cc.winSize;

        var btnLoad = new cc.MenuItemFont("load products", function(){
          sdkbox.IAP.refresh();
        });

        var btnRestore = new cc.MenuItemFont("restore purchase", function(){
          sdkbox.IAP.restore();
        });

        var menu = new cc.Menu(btnLoad, btnRestore);
        menu.x = size.width / 2;
        menu.y = size.height - 140;
        menu.alignItemsVerticallyWithPadding(5);
        this.addChild(menu);

        this.menuIAP = new cc.Menu();
        this.addChild(this.menuIAP);

        this.txtCoin = new cc.LabelTTF("0", "sans", 32);
        this.txtCoin.x = size.width / 2;
        this.txtCoin.y = 120;
        this.addChild(this.txtCoin);
    },

    log:function(msg) {
        cc.log(msg);
        if (this.logCount == null) {
            this.logLabel = new cc.LabelTTF("log here", "sans", 16);
            this.logLabel.setAnchorPoint(0, 0)
            this.logLabel.x = 12;
            this.logLabel.y = 50;
            this.addChild(this.logLabel);
            this.logCount = 0;
        }
        this.logLabel.setString(this.logLabel.getString() + "\n" + this.logCount + ") " + msg);
        this.logCount = this.logCount + 1
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

