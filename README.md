
# sdkbox IAP samples

## Getting Started

Make sure to run setup script first to download the cocos2d-x engine
~~~bash
./setup
~~~

If the setup script runs correctly the folder structure should look like this

~~~
+-- sdkbox-cocos2d-x-binary
+-- sdkbox-sample-iap
| +-- cpp
| +-- lua
| \-- js
~~~

## Note

### Test IAP for iOS

* iOS simulator don't support purchase, please test with a real device.
* You need to use your iTunesConnect account to create a test user in order to test IAP
* Update bundle identifier to match your own bundle identifier

### Test IAP for android

1. To test Android IAP you need to opt-in as an alpha tester [here](https://play.google.com/apps/testing/org.cocos2dx.PluginTest)
2. You can only test IAP in release build
3. Replace the [key](https://github.com/sdkbox/sdkbox-sample-iap/blob/master/cpp/Resources/sdkbox_config.json#L20) with your key. In [https://play.google.com/apps/publish/](https://play.google.com/apps/publish/), open your game, follow menu "Development tools -> Services & APIs -> in-app billing"

Run the following command
```
cocos run -p android -m release
```


## Documentation
For more information, check out the [SDKBOX IAP plugin](http://docs.sdkbox.com/en/plugins/iap/)
