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

#include "framesdataextractortest.h"
#include "framesdataextractor.h"
GQTEST_MAIN(FramesDataExtractorTest)

void FramesDataExtractorTest::init()
{
  mockFramesCreator=new StrictMock<MockFramesCreator>();
  framesDataExtractor=new FramesDataExtractor(mockFramesCreator, this);
}

void FramesDataExtractorTest::shouldAskForRemainingBytesOnNewData()
{
  EXPECT_CALL(*mockFramesCreator, remainingBytesForCurrentFrame()).WillOnce(Return(19));
  EXPECT_CALL(*mockFramesCreator, addFramesData(_));

  framesDataExtractor->gotFramesData(QByteArray("any qbytearray"));
}

void FramesDataExtractorTest::shouldAppendRemainingBytesToExistingFrame()
{
  QByteArray data("Frames Data");

  EXPECT_CALL(*mockFramesCreator, remainingBytesForCurrentFrame()).WillOnce(Return(19));
  EXPECT_CALL(*mockFramesCreator, addFramesData(data));
  framesDataExtractor->gotFramesData(data);
}

void FramesDataExtractorTest::shouldCreateNewFrameOnNoRemainingBytesAndStripHeader()
{
  InSequence seq;
  EXPECT_CALL(*mockFramesCreator, remainingBytesForCurrentFrame()).WillRepeatedly(Return(0));
  EXPECT_CALL(*mockFramesCreator, createNewFrame(QByteArray("1234")));
  EXPECT_CALL(*mockFramesCreator, remainingBytesForCurrentFrame()).WillRepeatedly(Return(250));
  
  EXPECT_CALL(*mockFramesCreator, addFramesData(QByteArray(" other bytes data to be added to frame")));
  framesDataExtractor->gotFramesData(QByteArray("1234 other bytes data to be added to frame"));
}

void FramesDataExtractorTest::shouldSplitDataOnOverlappingData()
{
  InSequence seq;
  Expectation firstFrameRemainingBytes=EXPECT_CALL(*mockFramesCreator, remainingBytesForCurrentFrame()).WillRepeatedly(Return(4));
  Expectation lastData=EXPECT_CALL(*mockFramesCreator, addFramesData(QByteArray("4321"))).After(firstFrameRemainingBytes);
  
  Expectation newFrameHeader=EXPECT_CALL(*mockFramesCreator, createNewFrame(QByteArray("1234"))).After(lastData);
  Expectation nextFrameRemainingBytes=EXPECT_CALL(*mockFramesCreator, remainingBytesForCurrentFrame()).WillRepeatedly(Return(256));

  EXPECT_CALL(*mockFramesCreator, addFramesData(QByteArray(" other bytes data to be added to frame"))).After(newFrameHeader);

  framesDataExtractor->gotFramesData(QByteArray("43211234 other bytes data to be added to frame"));
}

void FramesDataExtractorTest::cleanup()
{
  delete framesDataExtractor;
  delete mockFramesCreator;
}

#include "framesdataextractortest.moc"

