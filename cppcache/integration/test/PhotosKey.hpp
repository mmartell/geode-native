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

#ifndef PHOTOSKEY_H
#define PHOTOSKEY_H

/*
 * @brief User class for testing the put functionality for object.
 */

#include <chrono>
#include <ctime>
#include <string>

#include <geode/CacheableDate.hpp>
#include <geode/CacheableString.hpp>
#include <geode/DataSerializable.hpp>

namespace DataSerializableTest {

using apache::geode::client::CacheableDate;
using apache::geode::client::CacheableKey;
using apache::geode::client::CacheableString;
using apache::geode::client::DataInput;
using apache::geode::client::DataOutput;
using apache::geode::client::DataSerializable;

class PhotosKey : public DataSerializable, public CacheableKey {
 private:
  std::shared_ptr<CacheableString> people_;
  std::shared_ptr<CacheableDate> rangeStart_;
  std::shared_ptr<CacheableDate> rangeEnd_;

 public:
  PhotosKey() = default;
  explicit PhotosKey(std::shared_ptr<CacheableString> people,
                     std::shared_ptr<CacheableDate> start,
                     std::shared_ptr<CacheableDate> end)
      : people_(people), rangeStart_(start), rangeEnd_(end) {}
  ~PhotosKey() override = default;
  void toData(DataOutput& output) const override;
  void fromData(DataInput& input) override;
  bool operator==(const CacheableKey& other) const override;
  int32_t hashcode() const override;

  std::shared_ptr<CacheableString> getPeople() const { return people_; }
  std::shared_ptr<CacheableDate> getStart() const { return rangeStart_; }
  std::shared_ptr<CacheableDate> getEnd() const { return rangeEnd_; }
  static std::shared_ptr<Serializable> createDeserializable() {
    return std::make_shared<PhotosKey>();
  }
};

}  // namespace DataSerializableTest

#endif  // PHOTOSKEY_H
