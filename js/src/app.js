
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    txtCoin:null,
    menuIAP:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        cc.log("Sample Startup")

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

    createTestMenu:function() {
        sdkbox.IAP.init();
        sdkbox.IAP.setDebug(true);
        sdkbox.IAP.setListener({
            onSuccess : function (product) {
                //Purchase success
                cc.log("Purchase successful: " + product.name)
            },
            onFailure : function (product, msg) {
                //Purchase failed
                //msg is the error message
                cc.log("Purchase failed: " + product.name + " error: " + msg);
            },
            onCanceled : function (product) {
                //Purchase was canceled by user
                cc.log("Purchase canceled: " + product.name);
            },
            onRestored : function (product) {
                //Purchase restored
                cc.log("Restored: " + product.name);
            },
            onProductRequestSuccess : function (products) {
                self.menuIAP.removeAllChildren();
                //Returns you the data for all the iap products
                //You can get each item using following method
                for (var i = 0; i < products.length; i++) {
                    cc.log("================");
                    cc.log("name: " + products[i].name);
                    cc.log("price: " + products[i].price);
                    cc.log("================");

                    var btn = new ccui.Button(res.button_png);
                    btn.name = products[i].name;
                    btn.addClickEventListener(function(){
                      sdkbox.IAP.purchase(btn.name);
                    });
                    self.menuIAP.addChild(btn);
                }
            },
            onProductRequestFailure : function (msg) {
                //When product refresh request fails.
                cc.log("Failed to get products");
            }
        });

        var size = cc.winSize;

        var ui = ccs.load(res.MainScene_json);
        this.addChild(ui.node);

        var btnLoad = ui.node.getChildByName("btnLoad");
        btnLoad.addClickEventListener(function(){
          sdkbox.IAP.refresh();
        });

        var btnRestore = ui.node.getChildByName("btnRestore");
        btnRestore.addClickEventListener(function(){
          sdkbox.IAP.restore();
        });

        this.menuIAP = ui.node.getChildByName("menuIAP");

        this.txtCoin = ui.node.getChildByName("txtCoin");

        // add a "close" icon to exit the progress. it's an autorelease object
        var closeItem = new cc.MenuItemImage(
            res.CloseNormal_png,
            res.CloseSelected_png,
            function () {
                cc.log("Menu is clicked!");
            }, this);
        closeItem.attr({
            x: size.width - 20,
            y: 20,
            anchorX: 0.5,
            anchorY: 0.5
        });

        var menu = new cc.Menu(closeItem);
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu, 1);
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

