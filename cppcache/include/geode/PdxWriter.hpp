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

#ifndef GEODE_PDXWRITER_H_
#define GEODE_PDXWRITER_H_

#include "internal/geode_globals.hpp"
#include "CacheableBuiltins.hpp"
#include "CacheableDate.hpp"

namespace apache {
namespace geode {
namespace client {

class CacheableObjectArray;
class PdxUnreadFields;
/**
 * A PdxWriter will be passed to PdxSerializable.toData
 * when it is serializing the domain class. The domain class needs to serialize
 * member
 * fields using this abstract class. This class is implemented by Native Client.
 */
class APACHE_GEODE_EXPORT PdxWriter {
 public:
  /**
   * @brief constructors
   */
  PdxWriter() = default;

  PdxWriter(PdxWriter&& move) = default;

  /**
   * @brief destructor
   */
  virtual ~PdxWriter() = default;

  /**
   * Writes the named field with the given value to the serialized form
   * The fields type is <code>char16_t</code>
   * <p>C++ char16_t is mapped to Java char</p>
   * @param fieldName The name of the field to write
   * @param value The value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty
   */
  virtual PdxWriter& writeChar(const std::string& fieldName,
                               char16_t value) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>bool</code>.
   * <p>C++ bool is mapped to Java boolean</p>
   * @param fieldName the name of the field to write
   * @param value the value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty
   */
  virtual PdxWriter& writeBoolean(const std::string& fieldName, bool value) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>int8_t</code>.
   * <p>C++ int8_t is mapped to Java byte</p>
   * @param fieldName the name of the field to write
   * @param value the value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty
   */
  virtual PdxWriter& writeByte(const std::string& fieldName, int8_t value) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>int16_t</code>.
   * <p>C++ int16_t is mapped to Java short</p>
   * @param fieldName the name of the field to write
   * @param value the value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty
   */
  virtual PdxWriter& writeShort(const std::string& fieldName,
                                int16_t value) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>int32_t</code>.
   * <p>C++ int32_t is mapped to Java int</p>
   * @param fieldName the name of the field to write
   * @param value the value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty
   */
  virtual PdxWriter& writeInt(const std::string& fieldName, int32_t value) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>int64_t</code>.
   * <p>C++ int64_t is mapped to Java long</p>
   * @param fieldName the name of the field to write
   * @param value the value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty
   */
  virtual PdxWriter& writeLong(const std::string& fieldName, int64_t value) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>float</code>.
   * <p>C++ float is mapped to Java float</p>
   * @param fieldName the name of the field to write
   * @param value the value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty
   */
  virtual PdxWriter& writeFloat(const std::string& fieldName, float value) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>double</code>.
   * <p>C++ double is mapped to Java double</p>
   * @param fieldName the name of the field to write
   * @param value the value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty
   */
  virtual PdxWriter& writeDouble(const std::string& fieldName,
                                 double value) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>CacheableDatePtr</code>.
   * <p>C++ std::shared_ptr<CacheableDate> is mapped to Java Date</p>
   * @param fieldName the name of the field to write
   * @param value the value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty
   */
  virtual PdxWriter& writeDate(const std::string& fieldName,
                               std::shared_ptr<CacheableDate> date) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>char*</code>.
   * <p>C++ std::string is mapped to Java String</p>
   * @param fieldName the name of the field to write
   * @param value the UTF-8 value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty
   */
  virtual PdxWriter& writeString(const std::string& fieldName,
                                                 const std::string& value) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>CacheablePtr</code>.
   * <p>C++ std::shared_ptr<Cacheable> is mapped to Java object.</p>
   * It is best to use one of the other writeXXX methods if your field type
   * will always be XXX. This method allows the field value to be anything
   * that is an instance of Object. This gives you more flexibility but more
   * space is used to store the serialized field.
   *
   * Note that some Java objects serialized with this method may not be
   * compatible with non-java languages.
   * @param fieldName the name of the field to write
   * @param value the value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeObject(const std::string& fieldName,
                                 std::shared_ptr<Cacheable> value) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>bool*</code>.
   * <p>C++ bool* is mapped to Java boolean[]</p>
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @param length the length of the array field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeBooleanArray(const std::string& fieldName,
                                       const std::vector<bool>& array) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>char16_t*</code>.
   * <p>C++ char16_t* is mapped to Java char[].</p>
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @param length the length of the array field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeCharArray(
      const std::string& fieldName, const std::vector<char16_t>& array) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>int8_t*</code>.
   * <p>C++ int8_t* is mapped to Java byte[].</p>
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @param length the length of the array field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeByteArray(const std::string& fieldName,
                                    const std::vector<int8_t>& array) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>int16_t*</code>.
   * <p>C++ int16_t* is mapped to Java short[].</p>
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @param length the length of the array field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeShortArray(const std::string& fieldName,
                                     const std::vector<int16_t>& array) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>int32_t*</code>.
   * <p>C++ int32_t* is mapped to Java int[].</p>
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @param length the length of the array field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeIntArray(const std::string& fieldName,
                                   const std::vector<int32_t>& array) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>int64_t*</code>.
   * <p>C++ int64_t* is mapped to Java long[].</p>
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @param length the length of the array field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeLongArray(const std::string& fieldName,
                                    const std::vector<int64_t>& array) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>float*</code>.
   * <p>C++ float* is mapped to Java float[].</p>
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @param length the length of the array field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeFloatArray(const std::string& fieldName,
                                     const std::vector<float>& array) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>double*</code>.
   * <p>C++ double* is mapped to Java double[].</p>
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @param length the length of the array field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeDoubleArray(const std::string& fieldName,
                                      const std::vector<double>& array) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>std::vector<std::string></code>.
   * <p>C++ std::vector<std::string> is mapped to Java String[].</p>
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @param length the length of the array field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeStringArray(
      const std::string& fieldName, const std::vector<std::string>& array) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>CacheableObjectArrayPtr</code>.
   * C++ std::shared_ptr<CacheableObjectArray> is mapped to Java Object[].
   * For how each element of the array is a mapped to C++ see {@link
   * #writeObject}.
   * Note that this call may serialize elements that are not compatible with
   * non-java languages.
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeObjectArray(
      const std::string& fieldName,
      std::shared_ptr<CacheableObjectArray> array) = 0;

  /**
   * Writes the named field with the given value to the serialized form.
   * The fields type is <code>int8_t**</code>.
   * <p>C++ int8_t** is mapped to Java byte[][].</p>
   * @param fieldName the name of the field to write
   * @param array the value of the field to write
   * @param arrayLength the length of the actual byte array field holding
   * individual byte arrays to write
   * @param elementLength the length of the individual byte arrays to write
   * @return this PdxWriter
   * @throws IllegalStateException if the named field has already been written
   * or fieldName is nullptr or empty.
   */
  virtual PdxWriter& writeArrayOfByteArrays(
      const std::string& fieldName, int8_t* const* const array, int arrayLength,
      const int* elementLength) = 0;

  /**
   * Indicate that the given field name should be included in hashCode and
   * equals checks
   * of this object on a server that is using {@link
   * CacheFactory#setPdxReadSerialized} or when a client executes a query on a
   * server.
   * The fields that are marked as identity fields are used to generate the
   * hashCode and
   * equals methods of {@link PdxInstance}. Because of this, the identity fields
   * should themselves
   * either be primitives, or implement hashCode and equals.
   *
   * If no fields are set as identity fields, then all fields will be used in
   * hashCode and equals
   * checks.
   *
   * The identity fields should make marked after they are written using a
   * write* method.
   *
   * @param fieldName the name of the field to mark as an identity field.
   * @returns this PdxWriter&
   * @throws IllegalStateException if the named field does not exist.
   */
  virtual PdxWriter& markIdentityField(const std::string& fieldName) = 0;

  /**
   * Writes the given unread fields to the serialized form.
   * The unread fields are obtained by calling {@link
   * PdxReader#readUnreadFields}.
   * <p>This method must be called first before any of the writeXXX methods is
   * called.
   * @param unread the object that was returned from {@link
   * PdxReader#readUnreadFields}.
   * @return this PdxWriter
   * @throws IllegalStateException if one of the writeXXX methods has already
   * been called.
   */
  virtual PdxWriter& writeUnreadFields(
      std::shared_ptr<PdxUnreadFields> unread) = 0;
};
}  // namespace client
}  // namespace geode
}  // namespace apache

#endif  // GEODE_PDXWRITER_H_
