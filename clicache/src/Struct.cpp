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

 

#include "begin_native.hpp"
#include <geode/Struct.hpp>
#include "end_native.hpp"

#include "Struct.hpp"
#include "StructSet.hpp"
#include "ExceptionTypes.hpp"
#include "impl/SafeConvert.hpp"

using namespace System;

namespace Apache
{
  namespace Geode
  {
    namespace Client
    {
      namespace native = apache::geode::client;

      Object^ Struct::default::get(size_t index)
      {
        try
        {
          return (TypeRegistry::GetManagedValueGeneric<Object^>(
            static_cast<native::Struct*>(m_nativeptr->get())->operator[](static_cast<System::Int32>(index))));
        }
        finally
        {
          GC::KeepAlive(m_nativeptr);
        }
      }

      Object^ Struct::default::get(String^ fieldName)
      {
        try
        {
          return (TypeRegistry::GetManagedValueGeneric<Object^>(
            static_cast<native::Struct*>(m_nativeptr->get())->operator[](marshal_as<std::string>(fieldName))));
        }
        finally
        {
          GC::KeepAlive(m_nativeptr);
        }
      }

      StructSet<Object^>^ Struct::Set::get()
      {
        try
        {
          return StructSet</*TResult*/Object^>::Create(
            static_cast<native::Struct*>(m_nativeptr->get())->getStructSet());
        }
        finally
        {
          GC::KeepAlive(m_nativeptr);
        }
      }


      bool Struct/*<TResult>*/::HasNext()
      {
        try
        {
          return static_cast<native::Struct*>(m_nativeptr->get())->hasNext();
        }
        finally
        {
          GC::KeepAlive(m_nativeptr);
        }
      }

      size_t Struct/*<TResult>*/::Length::get()
      {
        try
        {
          return static_cast<native::Struct*>(m_nativeptr->get())->length();
        }
        finally
        {
          GC::KeepAlive(m_nativeptr);
        }
      }

      Object^ Struct/*<TResult>*/::Next()
      {
        try
        {
          return (TypeRegistry::GetManagedValueGeneric<Object^>(
            static_cast<native::Struct*>(m_nativeptr->get())->next()));
        }
        finally
        {
          GC::KeepAlive(m_nativeptr);
        }
      }
    }  // namespace Client
  }  // namespace Geode
}  // namespace Apache
