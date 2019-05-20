/* File : nc_full.i

  Steps to generate the wrapper are manual for now. Follow
  these steps:

  1) Copy this file to c:\geode-native-install\include
  2) Open a Powershell Interactive Window in Visual Studio
  3) In Powershell do
      cd c:\geode-native-install\include
      swig -csharp -c++ .\nc-full.i

*/

%module nc_cachefactory

#define APACHE_GEODE_EXPORT
#define APACHE_GEODE_EXTERN_TEMPLATE_EXPORT

%{
#include "c:/geode-native/build/cppcache/apache-geode_export.h"
#include <geode/internal/geode_base.hpp>
#include <geode/internal/geode_globals.hpp>
#include <geode/internal/DSCode.hpp>
#include <geode/internal/CacheableBuiltinTemplates.hpp>
#include <geode/internal/CacheableKeys.hpp>
#include <geode/util/LogLevel.hpp>
#include <geode/Region.hpp>

#include <geode/Serializable.hpp>
#include <geode/CacheableKey.hpp>
#include <geode/CacheableDate.hpp>
#include <geode/CacheableBuiltins.hpp>
#include <geode/Properties.hpp>
#include <geode/SystemProperties.hpp>
#include <geode/AttributesMutator.hpp>
#include <geode/AuthInitialize.hpp>
#include <geode/PdxWriter.hpp>
#include <geode/PdxReader.hpp>
#include <geode/PdxInstance.hpp>
#include <geode/PdxInstanceFactory.hpp>
#include <geode/PdxFieldTypes.hpp>
#include <geode/PdxSerializable.hpp>
#include <geode/PdxSerializer.hpp>
#include <geode/PdxUnreadFields.hpp>
#include <geode/PdxWrapper.hpp>
#include <geode/AuthenticatedView.hpp>
#include <geode/TransactionId.hpp>
#include <geode/Cache.hpp>
#include <geode/CacheableEnum.hpp>
#include <geode/CacheableFileName.hpp>
#include <geode/CacheableObjectArray.hpp>
#include <geode/CacheableString.hpp>
#include <geode/CacheableUndefined.hpp>
#include <geode/CacheFactory.hpp>
#include <geode/CacheListener.hpp>
#include <geode/CacheLoader.hpp>
#include <geode/CacheStatistics.hpp>
#include <geode/CacheTransactionManager.hpp>
#include <geode/CacheWriter.hpp>
#include <geode/CqAttributes.hpp>
#include <geode/CqAttributesFactory.hpp>
#include <geode/CqAttributesMutator.hpp>
#include <geode/CqOperation.hpp>
#include <geode/CqEvent.hpp>
#include <geode/CqListener.hpp>
#include <geode/CqQuery.hpp>
#include <geode/CqResults.hpp>
#include <geode/CqServiceStatistics.hpp>
#include <geode/CqState.hpp>
#include <geode/CqStatistics.hpp>
#include <geode/CqStatusListener.hpp>
#include <geode/DataInput.hpp>
#include <geode/DataOutput.hpp>
#include <geode/DataSerializable.hpp>
#include <geode/DefaultResultCollector.hpp>
#include <geode/Delta.hpp>
#include <geode/DiskPolicyType.hpp>
#include <geode/EntryEvent.hpp>
#include <geode/Exception.hpp>
#include <geode/ExceptionTypes.hpp>
#include <geode/ResultCollector.hpp>
#include <geode/Execution.hpp>
#include <geode/ExpirationAction.hpp>
#include <geode/ExpirationAttributes.hpp>
#include <geode/FixedPartitionResolver.hpp>
#include <geode/FunctionService.hpp>
#include <geode/GeodeCache.hpp>
#include <geode/HashMapOfPools.hpp>
#include <geode/PartitionResolver.hpp>
#include <geode/PersistenceManager.hpp>
#include <geode/Pool.hpp>
#include <geode/PoolFactory.hpp>
#include <geode/PoolManager.hpp>
#include <geode/Query.hpp>
#include <geode/RegionAttributes.hpp>
#include <geode/RegionAttributesFactory.hpp>
#include <geode/RegionEntry.hpp>
#include <geode/RegionEvent.hpp>
#include <geode/RegionFactory.hpp>
#include <geode/RegionService.hpp>
#include <geode/RegionShortcut.hpp>
#include <geode/ResultSet.hpp>
#include <geode/SelectResults.hpp>
#include <geode/Serializer.hpp>
#include <geode/Struct.hpp>
#include <geode/StructSet.hpp>
#include <geode/TypeRegistry.hpp>
#include <geode/UserFunctionExecutionException.hpp>
#include <geode/WritablePdxInstance.hpp>
%}

%include "c:/geode-native/build/cppcache/apache-geode_export.h"
%include <geode/Serializable.hpp>
%include <geode/Serializer.hpp>
%include <geode/CacheableKey.hpp>
%include <geode/internal/DSCode.hpp>
%include <geode/util/LogLevel.hpp>
%include <geode/internal/geode_base.hpp>
%include <geode/internal/geode_globals.hpp>

%include <geode/CacheableDate.hpp>
%include <geode/CacheableEnum.hpp>
%include <geode/CacheableFileName.hpp>
%include <geode/CacheableObjectArray.hpp>
%include <geode/CacheableString.hpp>
%include <geode/CacheableUndefined.hpp>
%include <geode/CacheableBuiltins.hpp>
%include <geode/Properties.hpp>
%include <geode/SystemProperties.hpp>
%include <geode/ExpirationAction.hpp>
%include <geode/SelectResults.hpp>
%include <geode/CqStatistics.hpp>
%include <geode/CqAttributes.hpp>
%include <geode/CqResults.hpp>
%include <geode/CqAttributesMutator.hpp>
%include <geode/CqState.hpp>
%include <geode/CqQuery.hpp>
%include <geode/Query.hpp>
%include <geode/CqServiceStatistics.hpp>
%include <geode/QueryService.hpp>
%include <geode/Pool.hpp>

%include <geode/AttributesMutator.hpp>
%include <geode/AuthInitialize.hpp>
%include <geode/PdxFieldTypes.hpp>
%include <geode/PdxWriter.hpp>
%include <geode/PdxReader.hpp>
%include <geode/PdxInstance.hpp>
%include <geode/PdxInstanceFactory.hpp>
%include <geode/PdxSerializable.hpp>
%include <geode/PdxSerializer.hpp>
%include <geode/PdxUnreadFields.hpp>
%include <geode/PdxWrapper.hpp>
%include <geode/AuthenticatedView.hpp>
%include <geode/TransactionId.hpp>
%include <geode/Cache.hpp>
%include <geode/CacheFactory.hpp>
%include <geode/CacheListener.hpp>
%include <geode/CacheLoader.hpp>
%include <geode/CacheStatistics.hpp>
%include <geode/CacheTransactionManager.hpp>
%include <geode/CacheWriter.hpp>
%include <geode/CqAttributesFactory.hpp>
%include <geode/CqOperation.hpp>
%include <geode/CqEvent.hpp>
%include <geode/CqListener.hpp>
%include <geode/CqStatusListener.hpp>
%include <geode/DataInput.hpp>
%include <geode/DataOutput.hpp>
%include <geode/DataSerializable.hpp>
%include <geode/DefaultResultCollector.hpp>
%include <geode/Delta.hpp>
%include <geode/DiskPolicyType.hpp>
%include <geode/EntryEvent.hpp>
%include <geode/Exception.hpp>
%include <geode/ExceptionTypes.hpp>
%include <geode/ResultCollector.hpp>
%include <geode/Execution.hpp>
%include <geode/ExpirationAttributes.hpp>
%include <geode/FixedPartitionResolver.hpp>
%include <geode/FunctionService.hpp>
%include <geode/GeodeCache.hpp>
%include <geode/HashMapOfPools.hpp>
%include <geode/PartitionResolver.hpp>
%include <geode/PersistenceManager.hpp>
%include <geode/PoolFactory.hpp>
%include <geode/PoolManager.hpp>
%include <geode/Region.hpp>
%include <geode/RegionAttributes.hpp>
%include <geode/RegionAttributesFactory.hpp>
%include <geode/RegionEntry.hpp>
%include <geode/RegionEvent.hpp>
%include <geode/RegionFactory.hpp>
%include <geode/RegionService.hpp>
%include <geode/RegionShortcut.hpp>
%include <geode/ResultSet.hpp>
%include <geode/Serializer.hpp>
%include <geode/Struct.hpp>
%include <geode/StructSet.hpp>
%include <geode/TypeRegistry.hpp>
%include <geode/UserFunctionExecutionException.hpp>
%include <geode/WritablePdxInstance.hpp>