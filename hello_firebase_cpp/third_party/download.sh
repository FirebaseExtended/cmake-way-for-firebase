#!/bin/sh
curl https://dl.google.com/firebase/sdk/cpp/firebase_cpp_sdk_6.15.1.zip > firebase_cpp_sdk.zip &&
unzip -q firebase_cpp_sdk.zip &&
rm firebase_cpp_sdk.zip