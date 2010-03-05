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


GQTEST_MAIN(SocketConnectorTest)

class MockSocket : public QTcpSocket {
  public:
  MOCK_METHOD3(connectToHost, void(const QString &, quint16, QAbstractSocket::OpenMode) );
};


void SocketConnectorTest::testFoo()
{
  MockSocket mockSocket;
  SocketConnector connector(&mockSocket, this);
  const QString hostname("localhost");
  EXPECT_CALL(mockSocket, connectToHost(hostname,8080,_ ));
  connector.openConnection();
}

#include "socketconnectortest.moc"

