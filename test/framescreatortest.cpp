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

#include "framescreatortest.h"
#include <QSignalSpy>

GQTEST_MAIN(FramesCreatorTest)

void FramesCreatorTest::init()
{
  mockFramesFactory=new StrictMock<MockFramesFactory>();
  framesCreator=new FramesCreator(mockFramesFactory);
  mockFrame=new StrictMock<MockFrame>();
}


void FramesCreatorTest::shouldReturn0AsRemainingBytesIfCurrentFrameIsBlank()
{
  QCOMPARE(framesCreator->remainingBytesForCurrentFrame(), (quint16)0);
}

void FramesCreatorTest::shouldCreateNewFrame()
{
  EXPECT_CALL(*mockFramesFactory, create(QByteArray("header data")));
  framesCreator->createNewFrame(QByteArray("header data"));
}

void FramesCreatorTest::shouldReportRemainingBytes()
{
  QByteArray data;
  EXPECT_CALL(*mockFramesFactory, create(QByteArray("header data"))).WillOnce(Return(mockFrame));
  EXPECT_CALL(*mockFrame, totalbytes()).Times(AnyNumber()).WillRepeatedly(Return(1024));
  EXPECT_CALL(*mockFrame, frameData()).Times(AnyNumber()).WillRepeatedly(Return(&data));
  
  framesCreator->createNewFrame(QByteArray("header data"));
  
  QCOMPARE(framesCreator->remainingBytesForCurrentFrame(), (quint16) 1024);
  data.append("1234567890");
  QCOMPARE(framesCreator->remainingBytesForCurrentFrame(), (quint16) (1024-10) );
  data.append("123456789012345");
  QCOMPARE(framesCreator->remainingBytesForCurrentFrame(), (quint16) (1024-10-15) );
}

void FramesCreatorTest::shouldWriteDataToFrame()
{
  QByteArray data;
  EXPECT_CALL(*mockFramesFactory, create(QByteArray("header data"))).WillOnce(Return(mockFrame));
  EXPECT_CALL(*mockFrame, frameData()).Times(AnyNumber()).WillRepeatedly(Return(&data));
  EXPECT_CALL(*mockFrame, totalbytes()).Times(AnyNumber()).WillRepeatedly(Return(100));

  framesCreator->createNewFrame(QByteArray("header data"));
  framesCreator->addFramesData(QByteArray("Any data to write into the frame"));
  QCOMPARE(data, QByteArray("Any data to write into the frame"));
}

void FramesCreatorTest::shouldEmitProcessedFrameSignalWhenNoMoreBytesAreRemaining()
{
  QByteArray data;
  QSignalSpy spy(framesCreator, SIGNAL(frameProcessed(Frame*)));

  EXPECT_CALL(*mockFramesFactory, create(QByteArray("header data"))).WillOnce(Return(mockFrame));
  EXPECT_CALL(*mockFrame, frameData()).Times(AnyNumber()).WillRepeatedly(Return(&data));
  EXPECT_CALL(*mockFrame, totalbytes()).Times(AnyNumber()).WillRepeatedly(Return(10));

  framesCreator->createNewFrame(QByteArray("header data"));
  
  framesCreator->addFramesData(QByteArray("12345"));
  QCOMPARE(spy.count(), 0);
  framesCreator->addFramesData(QByteArray("12345"));
  QCOMPARE(framesCreator->remainingBytesForCurrentFrame(), (quint16)0);
  QCOMPARE(spy.count(), 1);
}


void FramesCreatorTest::cleanup()
{
  delete framesCreator;
  delete mockFramesFactory;
  delete mockFrame;
}

#include "framescreatortest.moc"
