/* File : nc.i */

%module nc

#define APACHE_GEODE_EXPORT

%{
#include <iostream>

#include "c:/geode-native/build/cppcache/apache-geode_export.h"
#include <geode/internal/DSCode.hpp>
#include <geode/internal/DSFixedId.hpp>
#include <geode/internal/DataSerializableFixedId.hpp>
#include <geode/internal/DataSerializableInternal.hpp>
#include <geode/internal/DataSerializablePrimitive.hpp>
#include <geode/internal/functional.hpp>
#include <geode/internal/geode_base.hpp>
#include <geode/internal/geode_globals.hpp>
#include <geode/internal/CacheableBuiltinTemplates.hpp>
#include <geode/CacheableBuiltins.hpp>
#include <geode/Serializable.hpp>
#include <geode/Serializer.hpp>
/*#include <geode/CacheableKey.hpp>*/
#include <geode/internal/CacheableKeys.hpp>
#include <geode/CacheableString.hpp>
#include <geode/RegionShortcut.hpp>
#include <geode/Region.hpp>
#include <geode/RegionFactory.hpp>
#include <geode/Cache.hpp>
#include <geode/Properties.hpp>
#include <geode/CacheFactory.hpp>
#include <geode/PoolManager.hpp>


%}

/* %include <iostream> */

%include "c:/geode-native/build/cppcache/apache-geode_export.h"
%include <geode/internal/DSCode.hpp>
%include <geode/internal/DSFixedId.hpp>
%include <geode/internal/functional.hpp>
%include <geode/internal/DataSerializableFixedId.hpp>
%include <geode/internal/DataSerializableInternal.hpp>
%include <geode/internal/DataSerializablePrimitive.hpp>
%include <geode/internal/geode_base.hpp>
%include <geode/internal/geode_globals.hpp>
%include <geode/internal/CacheableBuiltinTemplates.hpp>
%include <geode/CacheableBuiltins.hpp>
%include <geode/Serializable.hpp>
%include <geode/Serializer.hpp>
/*%include <geode/CacheableKey.hpp>*/
%include <geode/internal/CacheableKeys.hpp>
%include <geode/CacheableString.hpp>
%include <geode/RegionShortcut.hpp>
%include <geode/Region.hpp>
%include <geode/RegionFactory.hpp>
%include <geode/Cache.hpp>
%include <geode/Properties.hpp>
%include <geode/CacheFactory.hpp>
%include <geode/PoolManager.hpp>


