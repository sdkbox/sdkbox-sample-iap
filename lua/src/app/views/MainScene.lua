
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    print("Sample Startup")

    local label = cc.Label:createWithSystemFont("QUIT", "sans", 32)
    local quit = cc.MenuItemLabel:create(label)
    quit:onClicked(function()
        os.exit(0)
    end)
    local size = label:getContentSize()
    local menu = cc.Menu:create(quit)
    menu:setPosition(display.right - size.width / 2 - 16, display.bottom + size.height / 2 + 16)
    self:addChild(menu)

    self:setupTestMenu()
end

function MainScene:setupTestMenu()
    cc.MenuItemFont:setFontName("sans")
    local winsize = cc.Director:getInstance():getWinSize()

    local btnLoad = cc.MenuItemFont:create("load products"):onClicked(function()
        sdkbox.IAP:refresh()
    end)

    local btnRestore = cc.MenuItemFont:create("restore purchase"):onClicked(function()
        sdkbox.IAP:restore();
    end)

    local menu = cc.Menu:create(btnLoad, btnRestore)
    menu:setPosition(winsize.width / 2, winsize.height - 140)
    menu:alignItemsVerticallyWithPadding(5);
    self:addChild(menu)

    local txtCoin = cc.Label:createWithSystemFont("0", "sans", 24)
    txtCoin:setPosition(winsize.width / 2, 120)
    self:addChild(txtCoin)

    local menuIAP = cc.Menu:create()
    self:addChild(menuIAP)

    sdkbox.IAP:init()
    sdkbox.IAP:setDebug(true)
    sdkbox.IAP:setListener(function(args)
        if "onSuccess" == args.event then
                local product = args.product
                dump(product, "onSuccess:")
        elseif "onFailure" == args.event then
                local product = args.product
                local msg = args.msg
                dump(product, "onFailure:")
                print("msg:", msg)
        elseif "onCanceled" == args.event then
                local product = args.product
                dump(product, "onCanceled:")
        elseif "onRestored" == args.event then
                local product = args.product
                dump(product, "onRestored:")
        elseif "onProductRequestSuccess" == args.event then
                local products = args.products
                dump(products, "onProductRequestSuccess:")

                menuIAP:removeAllChildren()
                for _, product in ipairs(products) do
                    local btn = cc.MenuItemFont:create(product.name):onClicked(function()
                        sdkbox.IAP:purchase(product.name)
                    end)
                    menuIAP:addChild(btn)
                end

                menuIAP:alignItemsVerticallyWithPadding(5)
                menuIAP:setPosition(winsize.width / 2, winsize.height / 2)

        elseif "onProductRequestFailure" == args.event then
                local msg = args.msg
                print("msg:", msg)
        else
                print("unknown event ", args.event)
        end
    end)
end

return MainScene
