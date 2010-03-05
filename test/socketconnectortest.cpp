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

GQTEST_MAIN(SocketConnectorTest)

void SocketConnectorTest::init()
{
  mocksocket=new StrictMock<MockSocket>();
  mockframesdataextractor=new StrictMock<MockFramesDataExtractor>();
  socketConnector= new SocketConnector(mocksocket, mockframesdataextractor, this);
}


void SocketConnectorTest::shouldConnectToLocalhost()
{
  Expectation shouldConnectFirst = EXPECT_CALL(*mocksocket, connectToHost(QString("localhost"), 8080) );
  
  socketConnector->openConnection();
}

void SocketConnectorTest::shouldReadDataOnSocketSignalAndDoNothingOnNoData()
{
  EXPECT_CALL(*mocksocket, readAll()).WillOnce(Return(QByteArray()));
  EXPECT_CALL(*mockframesdataextractor, gotFramesData(_)).Times(0);
  mocksocket->emitReadyRead();
}

void SocketConnectorTest::shouldReadDataOnSocketSignalAndPassDataToFramesExtractor()
{
  QByteArray data("any not empty QByteArray");
  EXPECT_CALL(*mocksocket, readAll()).WillOnce(Return(data));
  EXPECT_CALL(*mockframesdataextractor, gotFramesData(data));
  mocksocket->emitReadyRead();
}




void SocketConnectorTest::cleanup()
{
  delete mocksocket;
  delete mockframesdataextractor;
}

#include "socketconnectortest.moc"

