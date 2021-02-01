/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "PhotosValue.hpp"

using apache::geode::client::CacheableString;


namespace DataSerializableTest {

void PhotoMetaData::toData(DataOutput output) {
  output.writeInt(fullResId);

  int numPixels = PhotoMetaData::THUMB_HEIGHT * PhotoMetaData::THUMB_WIDTH;
  for (int i = 0; i < numPixels - 1; i++) {
    output.writeChar(thumbnailImage[i]);
  }
}

void PhotoMetaData::fromData(DataInput input) {
  fullResId = input.readInt32();

  int numPixels = PhotoMetaData::THUMB_HEIGHT * PhotoMetaData::THUMB_WIDTH;
  for (int i = 0; i < numPixels - 1; i++) {
    thumbnailImage[i] = input.read();
  }
}

void PhotosValue::toData(DataOutput output) {

  std::vector<std::shared_ptr<CacheableString>> cstr{
      CacheableString::create("Taaa"), CacheableString::create("Tbbb"),
      CacheableString::create("Tccc"), CacheableString::create("Tddd")};
  cacheStrArray = CacheableStringArray::create(cstr);

  std::vector<std::shared_ptr<CacheableString>> vec;
  for (int i = 0; i < photosMeta.size(); i++) {
    
  }

  output.writeObject(photosMeta);
}

  void PhotosValue::fromData(DataInput input) {
    // photosMeta = new std::list<PhotoMetaData>();
    // var pmd = input.readObject() as std::list<CacheableString>;
    // if (pmd != null) {
    //  foreach (var item in pmd) { photosMeta.Add((PhotoMetaData)item); }
    //}

    photosMeta =
        std::dynamic_pointer_cast<std::list<PhotoMetaData>>(dataInput.readObject());
  }

}  // namespace DataSerializableTest
