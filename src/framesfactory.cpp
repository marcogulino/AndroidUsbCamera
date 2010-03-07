/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "framesfactory.h"
#include <QDebug>
class FrameInitializationData {
  public:
    FrameInitializationData(quint16 width, quint16 height, quint16 bitsPerPixel) {
      this->width=width;
      this->height=height;
      this->bitsPerPixel=bitsPerPixel;
    }
    quint16 width;
    quint16 height;
    quint16 bitsPerPixel;
};

FramesFactory::FramesFactory(QObject* parent): QObject(parent)
{
  frameInitializationDataMap.insert(QByteArray::fromHex("F0000000"), new FrameInitializationData(320, 240, 12));
  frameInitializationDataMap.insert(QByteArray::fromHex("F8000000"), new FrameInitializationData(160, 120, 12));
}

FramesFactory::~FramesFactory()
{
  foreach(QByteArray header, frameInitializationDataMap.keys()) {
    delete (frameInitializationDataMap.take(header));
  }
}


Frame* FramesFactory::create(const QByteArray& headerData)
{
  FrameInitializationData *frameInitializationData = frameInitializationDataMap.value(headerData);
  return frameInitializationData 
    ? new Frame(frameInitializationData->width, frameInitializationData->height, frameInitializationData->bitsPerPixel)
    : NULL;
}


#include "framesfactory.moc"

