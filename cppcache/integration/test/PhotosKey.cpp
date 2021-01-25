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
#include <geode/DataInput.hpp>
#include <geode/DataOutput.hpp>
#include <geode/CacheableDate.hpp>

#include "PhotosKey.hpp"

namespace DataSerializableTest {

////  explicit PhotosKey(std::list<CacheableString> people, CacheableDate start,
////    CacheableDate end) {
////  people_ = people;
////  start_ = start;
////  end_ - end;
////}

void PhotosKey::toData(DataOutput& output) const {
  //std::list<CacheableString>::iterator it;
  //for (it = getPeople()->begin(); it != getPeople()->end(); ++it) {
  //  it->toData(output);
  //}
  people_->toData(output);
  rangeStart_->toData(output);
  rangeEnd_->toData(output);
}

void PhotosKey::fromData(apache::geode::client::DataInput& input) {
  //people_ = std::shared_ptr<std::list<CacheableString>>(input.readObject());
  people_->fromData(input);
  rangeStart_->fromData(input);
  rangeEnd_->fromData(input);
}

bool PhotosKey::operator==(const CacheableKey& other) const {
  //PhotosKey photosKey = static_cast<const PhotosKey&>(other);
  return people_ == static_cast<const PhotosKey&>(other).getPeople() &&
         rangeStart_ == static_cast<const PhotosKey&>(other).getStart() &&
         rangeEnd_ == static_cast<const PhotosKey&>(other).getEnd();
}

int PhotosKey::hashcode() const {
  int prime = 31;
  int result = 1;
  //std::list<CacheableString>::iterator it;
  //for(it=getPeople()->begin(); it != getPeople()->end(); ++it) {
  //  result = result * prime + it->hashcode();
  //}
  result = result * prime + getPeople()->hashcode();
  result = result * prime + getStart()->hashcode();
  result = result * prime + getEnd()->hashcode();

  return result;
}

}  // namespace DataSerializableTest


