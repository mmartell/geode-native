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

#include <list>
#include <memory>
#include <thread>

#include <gtest/gtest.h>

#include <geode/Cache.hpp>
#include <geode/CacheFactory.hpp>
#include <geode/RegionFactory.hpp>
#include <geode/RegionShortcut.hpp>
#include <geode/Serializable.hpp>

#include "framework/Cluster.h"

using apache::geode::client::Cache;
using apache::geode::client::Cacheable;
using apache::geode::client::CacheableString;
using apache::geode::client::CacheFactory;
using apache::geode::client::Region;
using apache::geode::client::RegionShortcut;
using apache::geode::client::Serializable;

// namespace CachingProxy_F {

class CachingProxyTest_F : public ::testing::Test {
 protected:
  static std::unique_ptr<Cluster> cluster_;

  CachingProxyTest_F() {}

  ~CachingProxyTest_F() override = default;

  static void SetUpTestSuite() {
    cluster_ = std::make_unique<Cluster>(Name{"CachingProxyTest_F"},
                                         LocatorCount{1}, ServerCount{1});
    cluster_->start();

    cluster_->getGfsh()
        .create()
        .region()
        .withName("region")
        .withType("PARTITION")
        .execute();
  }

  static void TearDownTestSuite() { cluster_.reset(); }
};

std::unique_ptr<Cluster> CachingProxyTest_F::cluster_{};

TEST_F(CachingProxyTest_F, LocalRemoveAfterLocalInvalidate) {
  Cache cache = CacheFactory().create();
  std::string key = std::string("scharles");
  std::string value = std::string("Sylvia Charles");
  std::shared_ptr<Region> region;
  cache.getPoolManager()
      .createFactory()
      .addLocator("localhost", cluster_->getLocatorPort())
      .create("pool");

  region = cache.createRegionFactory(RegionShortcut::CACHING_PROXY)
               .setPoolName("pool")
               .create("region");

  region->put(key, value);

  auto user = region->get(key);

  region->localInvalidate(key);

  auto resultLocalRemove = region->localRemove(key, value);
  ASSERT_FALSE(resultLocalRemove);

  resultLocalRemove = region->localRemove(key, nullptr);
  ASSERT_TRUE(resultLocalRemove);
}

TEST_F(CachingProxyTest_F, RemoveAfterInvalidate) {
  Cache cache = CacheFactory().create();
  std::string key = std::string("scharles");
  std::string value = std::string("Sylvia Charles");
  std::shared_ptr<Region> region;
  cache.getPoolManager()
      .createFactory()
      .addLocator("localhost", cluster_->getLocatorPort())
      .create("pool");

  region = cache.createRegionFactory(RegionShortcut::CACHING_PROXY)
               .setPoolName("pool")
               .create("region");

  region->put(key, value);

  region->invalidate(key);

  auto resultRemove = region->remove(key, value);
  ASSERT_FALSE(resultRemove);

  resultRemove = region->remove(key, nullptr);
  ASSERT_TRUE(resultRemove);
}

TEST_F(CachingProxyTest_F, RemoveAfterLocalInvalidate) {
  Cache cache = CacheFactory().create();
  std::string key = std::string("scharles");
  std::string value = std::string("Sylvia Charles");
  std::shared_ptr<Region> region;
  cache.getPoolManager()
      .createFactory()
      .addLocator("localhost", cluster_->getLocatorPort())
      .create("pool");

  region = cache.createRegionFactory(RegionShortcut::CACHING_PROXY)
               .setPoolName("pool")
               .create("region");

  region->put(key, value);

  region->localInvalidate(key);

  auto resultRemove = region->remove(key, nullptr);
  ASSERT_FALSE(resultRemove);

  auto user = region->get(key);
  ASSERT_EQ(std::dynamic_pointer_cast<CacheableString>(user)->value(), value);
}

TEST_F(CachingProxyTest_F, Remove) {
  Cache cache = CacheFactory().create();
  std::string key = std::string("scharles");
  std::string value = std::string("Sylvia Charles");
  std::shared_ptr<Region> region;
  cache.getPoolManager()
      .createFactory()
      .addLocator("localhost", cluster_->getLocatorPort())
      .create("pool");

  region = cache.createRegionFactory(RegionShortcut::CACHING_PROXY)
               .setPoolName("pool")
               .create("region");
  region->put(key, value);

  auto resultRemove = region->remove(key);
  ASSERT_TRUE(resultRemove);
}

//}  // namespace CachingProxy_F
