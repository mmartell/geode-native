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

#define ROOT_NAME "testThinClientDisconnectionListener"

#include "fw_dunit.hpp"
#include "ThinClientHelper.hpp"
#include <string>
#define CLIENT1 s1p1
#define SERVER1 s2p1
#include <geode/CacheListener.hpp>
// CacheHelper* cacheHelper = nullptr;
static bool isLocator = false;
static bool isLocalServer = true;
static int numberOfLocators = 1;
static int isDisconnected = false;
const char *locatorsG =
    CacheHelper::getLocatorHostPort(isLocator, isLocalServer, numberOfLocators);

class DisconnectCacheListioner : public CacheListener {
  void afterRegionDisconnected(Region &) override {
    LOG("After Region Disconnected event received");
    isDisconnected = true;
  }
};
auto cptr = std::make_shared<DisconnectCacheListioner>();
#include "LocatorHelper.hpp"
DUNIT_TASK_DEFINITION(CLIENT1, SetupClient1_Pool_Locator)
  {
    initClient(true);
    createPooledRegion(regionNames[0], false /*ack mode*/, locatorsG,
                       "__TEST_POOL1__", true /*client notification*/, cptr);
  }
END_TASK_DEFINITION

DUNIT_TASK_DEFINITION(CLIENT1, Verify)
  {
    SLEEP(10000);
    ASSERT(isDisconnected, "Client should have gotten disconenct event");
    isDisconnected = false;
  }
END_TASK_DEFINITION

DUNIT_TASK_DEFINITION(CLIENT1, populateServer)
  {
    SLEEP(10000);
    auto regPtr = getHelper()->getRegion(regionNames[0]);
    auto keyPtr = CacheableKey::create("PXR");
    auto valPtr = CacheableString::create("PXR1");
    regPtr->create(keyPtr, valPtr);
  }
END_TASK_DEFINITION

DUNIT_TASK_DEFINITION(SERVER1, StopServer)
  {
    if (isLocalServer) CacheHelper::closeServer(1);
    LOG("SERVER stopped");
  }
END_TASK_DEFINITION

DUNIT_TASK_DEFINITION(CLIENT1, StopClient1)
  {
    cleanProc();
    LOG("CLIENT1 stopped");
  }
END_TASK_DEFINITION

DUNIT_MAIN
  {
    CALL_TASK(CreateLocator1);
    // start locator
    //    --name=GFELOC14595
    //    --port=14595 
    //    --dir=C:\geode-native\build\cppcache\integration-test\.tests\testThinClientDisconnectionListioner\GFELOC14595 
    //    --classpath=C:\geode-native\build\tests\javaobject\javaobject.jar 
    //    --http-service-port=0 
    //    --J=-Dgemfire.jmx-manager-port=28465 
    //    --max-heap=256m 
    //    --properties-file=C:\geode-native\build\cppcache\integration-test\.tests\testThinClientDisconnectionListioner\GFELOC14595/test.geode.properties
    CALL_TASK(SetupClient1_Pool_Locator);
    //36: [config 2021/03/09 09:57:29.820759 Pacific Standard Time  :30376 23492] Geode Native Client System Properties:
36: //  archive-disk-space-limit = 0
36: //  archive-file-size-limit = 0
36: //  auto-ready-for-events = true
36: //  bucket-wait-timeout = 0ms
36: //  cache-xml-file = 
36: //  conflate-events = server
36: //  connect-timeout = 59000ms
36: //  connection-pool-size = 5
36: //  connect-wait-timeout = 0ms
36: //  enable-chunk-handler-thread = false
36: //  disable-shuffling-of-endpoints = false
36: //  durable-client-id = 
36: //  durable-timeout = 300s
36: //  enable-time-statistics = false
36: //  heap-lru-delta = 10
36: //  heap-lru-limit = 0
36: //  log-disk-space-limit = 0
36: //  log-file = 
36: //  log-file-size-limit = 0
36: //  log-level = config
36: //  max-fe-threads = 32
36: //  max-socket-buffer-size = 66560
36: //  notify-ack-interval = 1000ms
36: //  notify-dupcheck-life = 300000ms
36: //  on-client-disconnect-clear-pdxType-Ids = false
36: //  ping-interval = 10s
36: //  redundancy-monitor-interval = 10s
36: //  security-client-kspath = 
36: //  ssl-enabled = false
36: //  ssl-keystore = 
36: //  ssl-truststore = 
36: //  statistic-archive-file = statArchive.gfs
36: //  statistic-sampling-enabled = false
36: //  statistic-sample-rate = 1000ms
36: //  suspended-tx-timeout = 30s
36: //  tombstone-timeout = 480000ms
    CALL_TASK(Verify);
    CALL_TASK(CreateServer1_With_Locator_XML);
    CALL_TASK(populateServer);
    CALL_TASK(StopServer);
    CALL_TASK(Verify);
    CALL_TASK(StopClient1);
    CALL_TASK(CloseLocator1);
  }
END_MAIN
