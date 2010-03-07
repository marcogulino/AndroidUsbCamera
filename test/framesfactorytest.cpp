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

#include "framesfactorytest.h"
#include "framesfactory.h"

GQTEST_MAIN(FramesFactoryTest)

void FramesFactoryTest::frameTotalBytesCalculationTest()
{
  Frame frame(640, 480, 12);
  QCOMPARE(frame.totalbytes(), (quint32)460800);
}


void FramesFactoryTest::shouldCreate320x240NV12Frame()
{
  FramesFactory factory;
  Frame *createdFrame = factory.create(QByteArray::fromHex("F0000000"));
  QCOMPARE(createdFrame->width(), (quint16)320);
  QCOMPARE(createdFrame->height(), (quint16)240);
  QCOMPARE(createdFrame->totalbytes(), (quint32)115200); 
}

void FramesFactoryTest::shouldCreate160x120NV12Frame()
{
  FramesFactory factory;
  Frame *createdFrame = factory.create(QByteArray::fromHex("F8000000"));
  QCOMPARE(createdFrame->width(), (quint16)160);
  QCOMPARE(createdFrame->height(), (quint16)120);
  QCOMPARE(createdFrame->totalbytes(), (quint32)28800); 
}

void FramesFactoryTest::shouldReturnNullForInvalidHeader()
{
  FramesFactory factory;
  QCOMPARE(factory.create(QByteArray::fromHex("any invalid header")), (Frame*)NULL);
}



#include "framesfactorytest.moc"