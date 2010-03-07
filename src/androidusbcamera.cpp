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

#include "androidusbcamera.h"
#include "framesconverter.h"
#include "socketconnector.h"
#include <QTcpSocket>

#include <QDebug>
#include <QTimer>

AndroidUsbCamera::AndroidUsbCamera() : QObject(NULL) {
  qDebug() << "Initializing objects...";
  socketInterface=new SocketInterface(new QTcpSocket(this), this);
  framesFactory=new FramesFactory(this);
  framesCreator=new FramesCreator(framesFactory, this);
  framesDataExtractor=new FramesDataExtractor(framesCreator, this);
  connector=new SocketConnector(socketInterface, framesDataExtractor, this);
  framesConverter=new FramesConverter(this);
  connect(framesCreator, SIGNAL(frameProcessed(Frame*)), framesConverter, SLOT(gotFrame(Frame*)));
  framesConverter->start();
  connector->openConnection();
}

#include "androidusbcamera.moc"

