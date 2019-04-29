/* File : nc_cachefactory.i */

%module nc_cachefactory

#define APACHE_GEODE_EXPORT

%{
#include <iostream>

#include "c:/geode-native/build/cppcache/apache-geode_export.h"
#include <geode/internal/geode_base.hpp>
#include <geode/internal/geode_globals.hpp>
#include <geode/Serializable.hpp>
#include <geode/internal/functional.hpp>
#include <geode/CacheableKey.hpp>
#include <geode/CacheableObjectArray.hpp>
#include <geode/internal/DSCode.hpp>
#include <geode/internal/DataSerializablePrimitive.hpp>
#include <geode/CacheableString.hpp>
#include <geode/CacheableDate.hpp>
#include <geode/Exception.hpp>
#include <geode/ExceptionTypes.hpp>
#include <geode/DataInput.hpp>
#include <geode/DataOutput.hpp>
#include <geode/Serializer.hpp>
#include <geode/internal/CacheableKeys.hpp>
#include <geode/internal/CacheableBuiltinTemplates.hpp>
#include <geode/CacheableBuiltins.hpp>
#include <geode/PdxInstance.hpp>
#include <geode/PdxInstanceFactory.hpp>
#include <geode/RegionService.hpp>
#include <geode/GeodeCache.hpp>
//#include <geode/Cache.hpp>
#include <geode/CacheAttributes.hpp>
#include <geode/Pool.hpp>
#include <geode/PoolFactory.hpp>
#include <geode/CacheFactory.hpp>
#include <geode/Properties.hpp>

using namespace apache::geode::client;

%}

/*
%include "c:/geode-native/build/cppcache/apache-geode_export.h"
%include <geode/internal/geode_base.hpp>
%include <geode/internal/geode_globals.hpp>
%include <geode/Serializable.hpp>
%include <geode/internal/functional.hpp>
%include <geode/CacheableKey.hpp>
%include <geode/CacheableObjectArray.hpp>
%include <geode/internal/DSCode.hpp>
%include <geode/internal/DataSerializablePrimitive.hpp>
%include <geode/CacheableString.hpp>
%include <geode/CacheableDate.hpp>
%include <geode/Exception.hpp>
%include <geode/ExceptionTypes.hpp>
%include <geode/DataInput.hpp>
%include <geode/DataOutput.hpp>
%include <geode/Serializer.hpp>
%include <geode/internal/CacheableKeys.hpp>
%include <geode/internal/CacheableBuiltinTemplates.hpp>
%include <geode/CacheableBuiltins.hpp>
%include <geode/PdxInstance.hpp>
%include <geode/PdxInstanceFactory.hpp>
%include <geode/RegionService.hpp>
%include <geode/GeodeCache.hp
%include <geode/Cache.hpp>
%include <geode/CacheAttributes.hpp>
%include <geode/Pool.hpp>
%include <geode/PoolFactory.hpp>
*/

%include <geode/CacheFactory.hpp>
//%include <geode/Cache.hpp>
//%include <geode/Properties.hpp>





