#!/bin/sh
# Copyright 2020 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

pushd `dirname $0`/third_party
curl https://dl.google.com/firebase/sdk/cpp/firebase_cpp_sdk_6.15.1.zip > firebase_cpp_sdk.zip &&
unzip -q firebase_cpp_sdk.zip &&
rm firebase_cpp_sdk.zip
popd