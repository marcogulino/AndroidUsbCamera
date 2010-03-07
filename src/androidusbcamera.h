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

#ifndef ANDROIDUSBCAMERA_H
#define ANDROIDUSBCAMERA_H

#include <qt4/QtCore/QObject>

class Frame;
class SocketInterface; 
class FramesFactory   ;
class FramesCreator    ;
class FramesDataExtractor;
class SocketConnector     ;
class FramesConverter;

class AndroidUsbCamera : public QObject
{
  Q_OBJECT
  public:
    AndroidUsbCamera(QObject *parent=0);
  private:
    SocketInterface *socketInterface;
    FramesFactory *framesFactory;
    FramesCreator *framesCreator;
    FramesDataExtractor *framesDataExtractor;
    SocketConnector *connector;
    FramesConverter *framesConverter;
};

#endif // ANDROIDUSBCAMERA_H
