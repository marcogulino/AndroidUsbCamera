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

#ifndef FRAMESCREATORTEST_H
#define FRAMESCREATORTEST_H

#include <qt4/QtCore/QObject>
#include "android_usb_camera_test_base.h"
#include "framescreator.h"
class MockFramesFactory;
class MockFrame;

class FramesCreatorTest : public QObject
{
  Q_OBJECT
  private:
    FramesCreator *framesCreator;
    MockFramesFactory *mockFramesFactory;
    MockFrame *mockFrame;
  private slots:
    void init();
    void shouldReturn0AsRemainingBytesIfCurrentFrameIsBlank();
    void shouldCreateNewFrame();
    void shouldWriteDataToFrame();
    void shouldReportRemainingBytes();
    void shouldEmitProcessedFrameSignalWhenNoMoreBytesAreRemaining();
    void cleanup();
};


class MockFramesFactory : public FramesFactory {
  public:
    MOCK_METHOD1(create, Frame*(const QByteArray&));
};

class MockFrame : public Frame {
  public:
    MockFrame() : Frame(0, 0, 0) {};
    MOCK_METHOD0(totalbytes, quint32());
    MOCK_METHOD0(frameData, QByteArray*());
};
#endif // FRAMESCREATORTEST_H
