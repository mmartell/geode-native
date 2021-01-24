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
using Apache.Geode.Client;
using System;
using System.Drawing;
using System.Collections.Generic;

namespace Apache.Geode.Examples.ClassAsKey
{
  public class PhotoMetaData : IPdxSerializable
  {
    public int fullResId;
    public Bitmap thumbnailImage;

    public const int THUMB_WIDTH = 32;
    public const int THUMB_HEIGHT = 32;

    // A default constructor is required for deserialization
    public PhotoMetaData() { }

    public PhotoMetaData(int id, Bitmap thumb)
    {
      fullResId = id;
      thumbnailImage = thumb;
    }

    public void ToData(IPdxWriter output)
    {
      output.WriteInt("fullResId", fullResId);
      output.WriteByteArray("thumnailImage", ConvertToByteArray(thumbnailImage));
    }

    public void FromData(IPdxReader input)
    {
      fullResId = input.ReadInt("fullResId");
      byte[] bytes = input.ReadByteArray("thumbnailImage");
      ConvertFromByteArray(ref thumbnailImage, ref bytes);
    }

    public ulong ObjectSize
    {
      get { return 0; }
    }

    public static IPdxSerializable CreateDeserializable()
    {
      return new PhotoMetaData();
    }

    public static byte[] ConvertToByteArray(Bitmap thumb)
    {
      using (var stream = new System.IO.MemoryStream())
      {
        thumb.Save(stream, System.Drawing.Imaging.ImageFormat.Bmp);
        return stream.ToArray();
      }
    }

    public static void ConvertFromByteArray(ref Bitmap thumb, ref byte[] bytes)
    {
      using (var ms = new System.IO.MemoryStream(bytes))
      {
        thumb = (Bitmap)Image.FromStream(ms);
      }
    }
  }

  public class PhotosValue : IPdxSerializable
  {
    public List<PhotoMetaData> photosMeta;

    // A default constructor is required for deserialization
    public PhotosValue() { }

    public PhotosValue(List<PhotoMetaData> metaData)
    {
      photosMeta = metaData;
    }

    public void ToData(IPdxWriter output)
    {
      output.WriteObject("photosMeta", photosMeta);
    }

    public void FromData(IPdxReader input)
    {
      photosMeta = new List<PhotoMetaData>();
      var pmd = input.ReadObject("photosMeta") as IList<object>;
      if (pmd != null)
      {
        foreach (var item in pmd)
        {
          photosMeta.Add((PhotoMetaData)item);
        }
      }
    }

    public ulong ObjectSize
    {
      get { return 0; }
    }

    public static IPdxSerializable CreateDeserializable()
    {
      return new PhotosValue();
    }
  }
}


