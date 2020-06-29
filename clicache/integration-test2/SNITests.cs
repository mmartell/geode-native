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

using System;
using System.Diagnostics;
using System.IO;
using Xunit;
using PdxTests;
using System.Collections;
using System.Collections.Generic;
using Xunit.Abstractions;

namespace Apache.Geode.Client.IntegrationTests
{
    [Trait("Category", "Integration")]
    public class SNITests : TestBase, IDisposable
    {
        string certificatePassword;
        string currentWorkingDirectory;
        Process dockerComposeProcess;
        Process dockerProcess;
        private readonly Cache cache_;

        public SNITests(ITestOutputHelper testOutputHelper) : base(testOutputHelper)
        {
            certificatePassword = "apachegeode";
            currentWorkingDirectory = Directory.GetCurrentDirectory();
            var clientTruststore = currentWorkingDirectory + "/sni-test-config/geode-config/truststore.jks";

            var cacheFactory = new CacheFactory();
            cacheFactory.Set("log-level", "DEBUG");
            cacheFactory.Set("ssl-enabled", "true");
            cacheFactory.Set("ssl-keystore-password", certificatePassword);
            cacheFactory.Set("ssl-truststore", clientTruststore);

            cache_ = cacheFactory.Create();

            string sniDir = Directory.GetCurrentDirectory() + "/../sni-test-config";
            Directory.SetCurrentDirectory(sniDir);

            dockerComposeProcess = Process.Start(@"C:\Program Files\docker\docker\resources\bin\docker-compose.exe", "up -d");
            dockerProcess = Process.Start(@"C:\Program Files\Docker\Docker\resources\bin\docker", "exec -t geode gfsh run --file=/geode/scripts/geode-starter.gfsh");
        }

        public void Dispose()
        {
            dockerComposeProcess.Close();
            dockerProcess.Close();
            cache_.Close();
        }

        private string MakeItSo(string dockerCommand)
        {
            Process docker = Process.Start(@"C:\Program Files\Docker\Docker\resources\bin\docker", dockerCommand);
            string result = docker.StandardOutput.ReadLine();
            return result;
        }

        private int ParseProxyPort(string proxyString)
        {
            // 15443/tcp -> 0.0.0.0:32787
            int colonPosition = proxyString.IndexOf(":");
            string portNumberString = proxyString.Substring(colonPosition + 1);
            return Int32.Parse(portNumberString);
        }

        [Fact(Skip = "Disabled until SNI Proxy Available")]
        public void ConnectViaProxyTest()
        {
            var portString = MakeItSo("port haproxy");
            var portNumber = ParseProxyPort(portString);

            cache_.GetPoolManager()
                .CreateFactory()
                .AddLocator("localhost", portNumber)
                .Create("pool");

            var region = cache_.CreateRegionFactory(RegionShortcut.PROXY)
                              .SetPoolName("pool")
                              .Create<string, string>("region");

            region.Put("1", "one");
            var value = region.Get("1");

            Assert.Equal("one", value);
        }

        [Fact]
        public void ConnectionFailsTest()
        {
            cache_.GetPoolManager()
                .CreateFactory()
                .AddLocator("localhost", 10334)
                .Create("pool");

            var region = cache_.CreateRegionFactory(RegionShortcut.PROXY)
                              .SetPoolName("pool")
                              .Create<string, string>("region");

            Assert.Throws<NotConnectedException>(() => region.Put("1", "one"));
        }

        [Fact]
        public void DoNothingTest()
        {
            cache_.GetPoolManager()
                .CreateFactory()
                .AddLocator("localhost", 10334)
                .Create("pool");
        }
    }
}