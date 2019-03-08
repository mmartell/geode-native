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

#ifndef GEODE_CACHEABLEBUILTINS_H_
#define GEODE_CACHEABLEBUILTINS_H_

/** @file CacheableBuiltins.hpp
 *  @brief Contains generic template definitions for Cacheable types
 *         and instantiations for built-in types.
 */

#include <cstring>

#include "CacheableKey.hpp"
#include "CacheableString.hpp"
#include "Serializable.hpp"
#include "Serializer.hpp"
#include "internal/CacheableBuiltinTemplates.hpp"
#include "internal/CacheableKeys.hpp"

namespace apache {
namespace geode {
namespace client {

/**
 * An immutable wrapper for bool that can serve as
 * a distributable key object for caching.
 */
using CacheableBoolean =
    internalXYZ::CacheableKeyPrimitive<bool, internalXYZ::DSCode::CacheableBoolean>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableKeyPrimitive<bool, internalXYZ::DSCode::CacheableBoolean>;
template <>
inline std::shared_ptr<CacheableKey> CacheableKey::create(bool value) {
  return CacheableBoolean::create(value);
}
template <>
inline std::shared_ptr<Cacheable> Serializable::create(bool value) {
  return CacheableBoolean::create(value);
}

/**
 * An immutable wrapper for byte that can serve as
 * a distributable key object for caching.
 */
using CacheableByte =
    internalXYZ::CacheableKeyPrimitive<int8_t, internalXYZ::DSCode::CacheableByte>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableKeyPrimitive<int8_t, internalXYZ::DSCode::CacheableByte>;
template <>
inline std::shared_ptr<CacheableKey> CacheableKey::create(int8_t value) {
  return CacheableByte::create(value);
}
template <>
inline std::shared_ptr<Cacheable> Serializable::create(int8_t value) {
  return CacheableByte::create(value);
}

/**
 * An immutable wrapper for doubles that can serve as
 * a distributable key object for caching.
 */
using CacheableDouble =
    internalXYZ::CacheableKeyPrimitive<double, internalXYZ::DSCode::CacheableDouble>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableKeyPrimitive<double, internalXYZ::DSCode::CacheableDouble>;
template <>
inline std::shared_ptr<CacheableKey> CacheableKey::create(double value) {
  return CacheableDouble::create(value);
}
template <>
inline std::shared_ptr<Cacheable> Serializable::create(double value) {
  return CacheableDouble::create(value);
}

/**
 * An immutable wrapper for floats that can serve as

 * a distributable key object for caching.
 */
using CacheableFloat =
    internalXYZ::CacheableKeyPrimitive<float, internalXYZ::DSCode::CacheableFloat>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableKeyPrimitive<float, internalXYZ::DSCode::CacheableFloat>;
template <>
inline std::shared_ptr<CacheableKey> CacheableKey::create(float value) {
  return CacheableFloat::create(value);
}
template <>
inline std::shared_ptr<Cacheable> Serializable::create(float value) {
  return CacheableFloat::create(value);
}

/**
 * An immutable wrapper for 16-bit integers that can serve as
 * a distributable key object for caching.
 */
using CacheableInt16 =
    internalXYZ::CacheableKeyPrimitive<int16_t, internalXYZ::DSCode::CacheableInt16>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableKeyPrimitive<int16_t, internalXYZ::DSCode::CacheableInt16>;
template <>
inline std::shared_ptr<CacheableKey> CacheableKey::create(int16_t value) {
  return CacheableInt16::create(value);
}
template <>
inline std::shared_ptr<Cacheable> Serializable::create(int16_t value) {
  return CacheableInt16::create(value);
}

/**
 * An immutable wrapper for 32-bit integers that can serve as
 * a distributable key object for caching.
 */
using CacheableInt32 =
    internalXYZ::CacheableKeyPrimitive<int32_t, internalXYZ::DSCode::CacheableInt32>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableKeyPrimitive<int32_t, internalXYZ::DSCode::CacheableInt32>;
template <>
inline std::shared_ptr<CacheableKey> CacheableKey::create(int32_t value) {
  return CacheableInt32::create(value);
}
template <>
inline std::shared_ptr<Cacheable> Serializable::create(int32_t value) {
  return CacheableInt32::create(value);
}

/**
 * An immutable wrapper for 64-bit integers that can serve as
 * a distributable key object for caching.
 */
using CacheableInt64 =
    internalXYZ::CacheableKeyPrimitive<int64_t, internalXYZ::DSCode::CacheableInt64>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableKeyPrimitive<int64_t, internalXYZ::DSCode::CacheableInt64>;
template <>
inline std::shared_ptr<CacheableKey> CacheableKey::create(int64_t value) {
  return CacheableInt64::create(value);
}
template <>
inline std::shared_ptr<Cacheable> Serializable::create(int64_t value) {
  return CacheableInt64::create(value);
}

/**
 * An immutable wrapper for 16-bit characters that can serve as
 * a distributable key object for caching.
 */
using CacheableCharacter =
    internalXYZ::CacheableKeyPrimitive<char16_t,
                                    internalXYZ::DSCode::CacheableCharacter>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableKeyPrimitive<char16_t,
                                    internalXYZ::DSCode::CacheableCharacter>;
template <>
inline std::shared_ptr<CacheableKey> CacheableKey::create(char16_t value) {
  return CacheableCharacter::create(value);
}
template <>
inline std::shared_ptr<Cacheable> Serializable::create(char16_t value) {
  return CacheableCharacter::create(value);
}

/**
 * An immutable wrapper for byte arrays that can serve as
 * a distributable object for caching.
 */
using CacheableBytes =
    internalXYZ::CacheableArrayPrimitive<int8_t, internalXYZ::DSCode::CacheableBytes>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableArrayPrimitive<int8_t, internalXYZ::DSCode::CacheableBytes>;

/**
 * An immutable wrapper for array of booleans that can serve as
 * a distributable object for caching.
 */
using BooleanArray =
    internalXYZ::CacheableArrayPrimitive<bool, internalXYZ::DSCode::BooleanArray>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableArrayPrimitive<bool, internalXYZ::DSCode::BooleanArray>;

/**
 * An immutable wrapper for array of wide-characters that can serve as
 * a distributable object for caching.
 */
using CharArray =
    internalXYZ::CacheableArrayPrimitive<char16_t, internalXYZ::DSCode::CharArray>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableArrayPrimitive<char16_t, internalXYZ::DSCode::CharArray>;

/**
 * An immutable wrapper for array of doubles that can serve as
 * a distributable object for caching.
 */
using CacheableDoubleArray =
    internalXYZ::CacheableArrayPrimitive<double,
                                      internalXYZ::DSCode::CacheableDoubleArray>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableArrayPrimitive<double,
                                      internalXYZ::DSCode::CacheableDoubleArray>;

/**
 * An immutable wrapper for array of floats that can serve as
 * a distributable object for caching.
 */
using CacheableFloatArray =
    internalXYZ::CacheableArrayPrimitive<float,
                                      internalXYZ::DSCode::CacheableFloatArray>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableArrayPrimitive<float,
                                      internalXYZ::DSCode::CacheableFloatArray>;

/**
 * An immutable wrapper for array of 16-bit integers that can serve as
 * a distributable object for caching.
 */
using CacheableInt16Array =
    internalXYZ::CacheableArrayPrimitive<int16_t,
                                      internalXYZ::DSCode::CacheableInt16Array>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableArrayPrimitive<int16_t,
                                      internalXYZ::DSCode::CacheableInt16Array>;

/**
 * An immutable wrapper for array of 32-bit integers that can serve as
 * a distributable object for caching.
 */
using CacheableInt32Array =
    internalXYZ::CacheableArrayPrimitive<int32_t,
                                      internalXYZ::DSCode::CacheableInt32Array>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableArrayPrimitive<int32_t,
                                      internalXYZ::DSCode::CacheableInt32Array>;

/**
 * An immutable wrapper for array of 64-bit integers that can serve as
 * a distributable object for caching.
 */
using CacheableInt64Array =
    internalXYZ::CacheableArrayPrimitive<int64_t,
                                      internalXYZ::DSCode::CacheableInt64Array>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableArrayPrimitive<int64_t,
                                      internalXYZ::DSCode::CacheableInt64Array>;

/**
 * An immutable wrapper for array of strings that can serve as
 * a distributable object for caching.
 */
using CacheableStringArray =
    internalXYZ::CacheableArrayPrimitive<std::shared_ptr<CacheableString>,
                                      internalXYZ::DSCode::CacheableStringArray>;
extern template class APACHE_GEODE_EXTERN_TEMPLATE_EXPORT
    internalXYZ::CacheableArrayPrimitive<std::shared_ptr<CacheableString>,
                                      internalXYZ::DSCode::CacheableStringArray>;

// The following are defined as classes to avoid the issues with MSVC++
// warning/erroring on C4503

/**
 * A mutable <code>Cacheable</code> vector wrapper that can serve as
 * a distributable object for caching.
 */
class APACHE_GEODE_EXPORT CacheableVector
    : public internalXYZ::CacheableContainerPrimitive<
          std::vector<std::shared_ptr<Cacheable>>,
          internalXYZ::DSCode::CacheableVector, CacheableVector> {
 public:
  using CacheableContainerPrimitive::CacheableContainerPrimitive;
};

template class internalXYZ::CacheableContainerPrimitive<
    std::vector<std::shared_ptr<Cacheable>>, internalXYZ::DSCode::CacheableVector,
    CacheableVector>;

/**
 * A mutable <code>CacheableKey</code> to <code>Serializable</code>
 * hash map that can serve as a distributable object for caching.
 */
class APACHE_GEODE_EXPORT CacheableHashMap
    : public internalXYZ::CacheableContainerPrimitive<
          HashMapOfCacheable, internalXYZ::DSCode::CacheableHashMap,
          CacheableHashMap> {
 public:
  using CacheableContainerPrimitive::CacheableContainerPrimitive;
};

template class internalXYZ::CacheableContainerPrimitive<
    HashMapOfCacheable, internalXYZ::DSCode::CacheableHashMap, CacheableHashMap>;

/**
 * A mutable <code>CacheableKey</code> hash set wrapper that can serve as
 * a distributable object for caching.
 */
class APACHE_GEODE_EXPORT CacheableHashSet
    : public internalXYZ::CacheableContainerPrimitive<
          HashSetOfCacheableKey, internalXYZ::DSCode::CacheableHashSet,
          CacheableHashSet> {
 public:
  using CacheableContainerPrimitive::CacheableContainerPrimitive;
};

template class internalXYZ::CacheableContainerPrimitive<
    HashSetOfCacheableKey, internalXYZ::DSCode::CacheableHashSet,
    CacheableHashSet>;

/**
 * A mutable <code>Cacheable</code> array list wrapper that can serve as
 * a distributable object for caching.
 */
class APACHE_GEODE_EXPORT CacheableArrayList
    : public internalXYZ::CacheableContainerPrimitive<
          std::vector<std::shared_ptr<Cacheable>>,
          internalXYZ::DSCode::CacheableArrayList, CacheableArrayList> {
 public:
  using CacheableContainerPrimitive::CacheableContainerPrimitive;
};

template class internalXYZ::CacheableContainerPrimitive<
    std::vector<std::shared_ptr<Cacheable>>,
    internalXYZ::DSCode::CacheableArrayList, CacheableArrayList>;

/**
 * A mutable <code>Cacheable</code> array list wrapper that can serve as
 * a distributable object for caching.
 */
class APACHE_GEODE_EXPORT CacheableLinkedList
    : public internalXYZ::CacheableContainerPrimitive<
          std::vector<std::shared_ptr<Cacheable>>,
          internalXYZ::DSCode::CacheableLinkedList, CacheableLinkedList> {
 public:
  using CacheableContainerPrimitive::CacheableContainerPrimitive;
};

template class internalXYZ::CacheableContainerPrimitive<
    std::vector<std::shared_ptr<Cacheable>>,
    internalXYZ::DSCode::CacheableLinkedList, CacheableLinkedList>;

/**
 * A mutable <code>Cacheable</code> stack wrapper that can serve as
 * a distributable object for caching.
 */
class APACHE_GEODE_EXPORT CacheableStack
    : public internalXYZ::CacheableContainerPrimitive<
          std::vector<std::shared_ptr<Cacheable>>,
          internalXYZ::DSCode::CacheableStack, CacheableStack> {
 public:
  using CacheableContainerPrimitive::CacheableContainerPrimitive;
};

template class internalXYZ::CacheableContainerPrimitive<
    HashMapOfCacheable, internalXYZ::DSCode::CacheableStack, CacheableStack>;

/**
 * A mutable <code>CacheableKey</code> to <code>Serializable</code>
 * hash map that can serve as a distributable object for caching.
 */
class APACHE_GEODE_EXPORT CacheableHashTable
    : public internalXYZ::CacheableContainerPrimitive<
          HashMapOfCacheable, internalXYZ::DSCode::CacheableHashTable,
          CacheableHashTable> {
 public:
  using CacheableContainerPrimitive::CacheableContainerPrimitive;
};

template class internalXYZ::CacheableContainerPrimitive<
    HashMapOfCacheable, internalXYZ::DSCode::CacheableHashTable,
    CacheableHashTable>;

/**
 * A mutable <code>CacheableKey</code> to <code>Serializable</code>
 * hash map that can serve as a distributable object for caching. This is
 * provided for compability with java side, though is functionally identical
 * to <code>CacheableHashMap</code> i.e. does not provide the semantics of
 * java <code>IdentityHashMap</code>.
 */
class APACHE_GEODE_EXPORT CacheableIdentityHashMap
    : public internalXYZ::CacheableContainerPrimitive<
          HashMapOfCacheable, internalXYZ::DSCode::CacheableIdentityHashMap,
          CacheableIdentityHashMap> {
 public:
  using CacheableContainerPrimitive::CacheableContainerPrimitive;
};

template class internalXYZ::CacheableContainerPrimitive<
    HashMapOfCacheable, internalXYZ::DSCode::CacheableIdentityHashMap,
    CacheableIdentityHashMap>;

/**
 * A mutable <code>CacheableKey</code> hash set wrapper that can serve as
 * a distributable object for caching. This is provided for compability
 * with java side, though is functionally identical to
 * <code>CacheableHashSet</code> i.e. does not provide the predictable
 * iteration semantics of java <code>LinkedHashSet</code>.
 */
class APACHE_GEODE_EXPORT CacheableLinkedHashSet
    : public internalXYZ::CacheableContainerPrimitive<
          HashSetOfCacheableKey, internalXYZ::DSCode::CacheableLinkedHashSet,
          CacheableLinkedHashSet> {
 public:
  using CacheableContainerPrimitive::CacheableContainerPrimitive;
};

template class internalXYZ::CacheableContainerPrimitive<
    HashSetOfCacheableKey, internalXYZ::DSCode::CacheableLinkedHashSet,
    CacheableLinkedHashSet>;

}  // namespace client
}  // namespace geode
}  // namespace apache

#endif  // GEODE_CACHEABLEBUILTINS_H_
