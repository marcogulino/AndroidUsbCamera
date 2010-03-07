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

#ifndef FRAMESDATAEXTRACTORTEST_H
#define FRAMESDATAEXTRACTORTEST_H

#include <qt4/QtCore/QObject>
#include "android_usb_camera_test_base.h"
#include "framescreator.h"
class MockFramesCreator;
class FramesDataExtractor;
class FramesDataExtractorTest : public QObject
{
  Q_OBJECT
  private:
    MockFramesCreator *mockFramesCreator;
    FramesDataExtractor *framesDataExtractor;
    
  private slots:
    void init();
    void shouldAskForRemainingBytesOnNewData();
    void shouldCreateNewFrameOnNoRemainingBytesAndStripHeader();
    void shouldAppendRemainingBytesToExistingFrame();
    void shouldSplitDataOnOverlappingData();
    void cleanup();
};

class MockFramesCreator : public FramesCreator {
  public:
    MockFramesCreator() : FramesCreator(NULL) {};
    MOCK_METHOD0(remainingBytesForCurrentFrame, quint64());
    MOCK_METHOD1(addFramesData, void(const QByteArray &));
    MOCK_METHOD1(createNewFrame, void(const QByteArray&));
};
#endif // FRAMESDATAEXTRACTORTEST_H
