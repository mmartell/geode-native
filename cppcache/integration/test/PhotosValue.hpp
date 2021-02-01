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

#pragma once

#ifndef PHOTOSVALUE_H
#define PHOTOSVALUE_H

#include <chrono>
#include <list>

#include <geode/CacheableDate.hpp>
#include <geode/CacheableKey.hpp>
#include <geode/CacheableString.hpp>
#include <geode/DataInput.hpp>
#include <geode/DataOutput.hpp>
#include <geode/DataSerializable.hpp>

namespace DataSerializableTest {

using apache::geode::client::CacheableDate;
using apache::geode::client::CacheableKey;
using apache::geode::client::CacheableString;
using apache::geode::client::DataInput;
using apache::geode::client::DataOutput;
using apache::geode::client::DataSerializable;

class PhotoMetaData : public DataSerializable {
 public:
  PhotoMetaData() {}
  PhotoMetaData::PhotoMetaData(int id, char* thumb) {
    fullResId = id;
    for (int i = 0; i < (int)(sizeof(thumb) - 1); i++) {
      thumbnailImage[i] = thumb[i];
    }
  }

  static const int THUMB_WIDTH = 32;
  static const int THUMB_HEIGHT = 32;

  int fullResId;
  uint8_t thumbnailImage[THUMB_WIDTH * THUMB_HEIGHT];

  virtual void toData(DataOutput output);
  virtual void fromData(DataInput input);

  static std::shared_ptr<Serializable> createDeserializable() {
    return std::make_shared<PhotoMetaData>();
  }
};

class PhotosValue : public DataSerializable {
 public:
  std::list<PhotoMetaData> photosMeta;

  // A default constructor is required for deserialization
  PhotosValue() {}
  PhotosValue(std::list<PhotoMetaData> metaData) { photosMeta = metaData; }

  void toData(DataOutput output);
  void fromData(DataInput input);

  static std::shared_ptr<Serializable> createDeserializable() {
    return std::make_shared<PhotosValue>();
  }
};
}  // namespace DataSerializableTest

#endif  // PHOTOSVALUE_H
