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
using System.IO;
using System.Linq;
using Xunit;
using PdxTests;
using System.Collections;
using System.Collections.Generic;
using Xunit.Abstractions;

namespace Apache.Geode.Client.IntegrationTests
{
  [Trait("Category", "Integration")]
  public class PoolTest : TestBase
  {
    public PoolTest(ITestOutputHelper testOutputHelper) : base(testOutputHelper)

        {
        }

    [Fact]
    public void PoolAttributes()
    {
      using (var cluster = new Cluster(output, CreateTestCaseDirectoryName(), 1, 2))
      {
        Assert.True(cluster.Start());
        Assert.Equal(0, cluster.Gfsh.create()
            .region()
            .withName("testRegion")
            .withType("REPLICATE")
            .execute());

        var cache = cluster.CreateCache();

        var region = cache.CreateRegionFactory(RegionShortcut.PROXY)
            .SetPoolName("default")
            .Create<object, object>("testRegion");
        Assert.NotNull(region);

      }
    }

    [Fact]
    public void PoolLocator()
    {
      using (var cluster = new Cluster(output, CreateTestCaseDirectoryName(), 1, 1))
      {
        Assert.True(cluster.Start());
        Assert.Equal(0, cluster.Gfsh.create()
            .region()
            .withName("testRegion")
            .withType("REPLICATE")
            .execute());

        var cache = cluster.CreateCache();

        var region = cache.CreateRegionFactory(RegionShortcut.PROXY)
            .SetPoolName("default")
            .Create<object, object>("testRegion");
        Assert.NotNull(region);
      }
    }

    [Fact]
    public void PoolServer()
    {
      using (var cluster = new Cluster(output, CreateTestCaseDirectoryName(), 1, 1))
      {
        Assert.True(cluster.Start());
        Assert.Equal(0, cluster.Gfsh.create()
            .region()
            .withName("testRegion")
            .withType("REPLICATE")
            .execute());

        var cache = cluster.CreateCache();

        var region = cache.CreateRegionFactory(RegionShortcut.PROXY)
            .SetPoolName("default")
            .Create<object, object>("testRegion");
        Assert.NotNull(region);
      }
    }

    [Fact]
    public void PoolRedundancy()
    {
      using (var cluster = new Cluster(output, CreateTestCaseDirectoryName(), 1, 1))
      {
        Assert.True(cluster.Start());
        Assert.Equal(0, cluster.Gfsh.create()
            .region()
            .withName("testRegion")
            .withType("REPLICATE")
            .execute());

        var cache = cluster.CreateCache();

        var region = cache.CreateRegionFactory(RegionShortcut.PROXY)
            .SetPoolName("default")
            .Create<object, object>("testRegion");
        Assert.NotNull(region);
      }
    }

    [Fact]
    public void PoolRegisterInterest()
    {
      using (var cluster = new Cluster(output, CreateTestCaseDirectoryName(), 1, 1))
      {
        Assert.True(cluster.Start());
        Assert.Equal(0, cluster.Gfsh.create()
            .region()
            .withName("testRegion")
            .withType("REPLICATE")
            .execute());

        var cache = cluster.CreateCache();

        var region = cache.CreateRegionFactory(RegionShortcut.PROXY)
            .SetPoolName("default")
            .Create<object, object>("testRegion");
        Assert.NotNull(region);
      }
    }

  }
}