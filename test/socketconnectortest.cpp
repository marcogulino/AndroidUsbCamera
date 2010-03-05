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
#include "qtInterfaces/abstractsocket.h"


GQTEST_MAIN(SocketConnectorTest)

class MockSocket : public AbstractSocket {
  public:
    MockSocket() : AbstractSocket(NULL, NULL) {};
    MOCK_METHOD2(connectToHost, void(const QString &, int) );
    MOCK_METHOD1(waitForConnected, bool(int));
};


void SocketConnectorTest::shouldConnectToLocalhost()
{
  StrictMock<MockSocket> mockSocket;

  Expectation shouldConnectFirst = EXPECT_CALL(mockSocket, connectToHost(QString("localhost"), 8080) );
  EXPECT_CALL(mockSocket, waitForConnected(30000)).After(shouldConnectFirst).WillOnce(Return(true));
  SocketConnector connector(&mockSocket, this);

  connector.openConnection();
}

#include "socketconnectortest.moc"

