#!/bin/bash
echo 'Debug'
keytool -exportcert -alias androiddebugkey -keystore ~/.android/debug.keystore | openssl sha1 -binary | openssl base64


echo 'Release'
keytool -exportcert -alias tecokey -keystore teco.keystore | openssl sha1 -binary | openssl base64