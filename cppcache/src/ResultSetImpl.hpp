#pragma once

#ifndef GEODE_RESULTSETIMPL_H_
#define GEODE_RESULTSETIMPL_H_

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

#include <geode/internal/geode_globals.hpp>
#include <geode/ExceptionTypes.hpp>

#include <geode/ResultSet.hpp>
#include <geode/CacheableBuiltins.hpp>
#include <geode/SelectResultsIterator.hpp>

/**
 * @file
 */

namespace apache {
namespace geode {
namespace client {

class APACHE_GEODE_EXPORT ResultSetImpl
    : public ResultSet,
      public std::enable_shared_from_this<ResultSetImpl> {
 public:
  ResultSetImpl(const std::shared_ptr<CacheableVector>& response);

  bool isModifiable() const override;

  size_t size() const override;

  const std::shared_ptr<Serializable> operator[](size_t index) const override;

  SelectResultsIterator getIterator() override;

  /** Get an iterator pointing to the start of vector. */
  virtual SelectResults::Iterator begin() const override;

  /** Get an iterator pointing to the end of vector. */
  virtual SelectResults::Iterator end() const override;

  ~ResultSetImpl() noexcept override {}

 private:
  std::shared_ptr<CacheableVector> m_resultSetVector;
  // UNUSED int32_t m_nextIndex;
};
}  // namespace client
}  // namespace geode
}  // namespace apache

#endif  // GEODE_RESULTSETIMPL_H_
