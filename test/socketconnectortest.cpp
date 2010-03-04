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

#include "socketconnectortest.h"
#include "socketconnector.h"
#include <QTcpSocket>

#include "android_usb_camera_test_base.h"

GQTEST_MAIN(SocketConnectorTest)

class MockSocket : public QTcpSocket {
  public:
  MOCK_METHOD3(connectToHost, void(const QString &, quint16, QAbstractSocket::OpenMode) );
  MOCK_METHOD0(abort, void() );
};


void SocketConnectorTest::testFoo()
{
  StrictMock<MockSocket> mockSocket;
  SocketConnector connector(&mockSocket, this);
//   EXPECT_CALL(mockSocket, connectToHost(_,_,_ )).Times(1);
  EXPECT_CALL(mockSocket, abort());
  connector.openConnection();
//   QVERIFY(Mock::VerifyAndClearExpectations(&mockSocket));
}

#include "socketconnectortest.moc"

