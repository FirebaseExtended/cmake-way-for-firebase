Invoke-WebRequest "https://dl.google.com/firebase/sdk/cpp/firebase_cpp_sdk_6.15.1.zip" -OutFile "$PSScriptRoot/firebase_cpp_sdk.zip"
Expand-Archive "$PSScriptRoot/firebase_cpp_sdk.zip"
Remove-Item -Path "$PSScriptRoot/firebase_cpp_sdk.zip"