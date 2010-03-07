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

#include "frame.h"

class FramePrivate {
  public:
    QByteArray frameData;
    quint16 width;
    quint16 height;
    quint16 bitsPerPixel;
};

Frame::Frame ( quint16 width, quint16 height, quint16 bitsPerPixel, QObject* parent ) : QObject ( parent )
{
  d=new FramePrivate;
  d->width=width;
  d->height=height;
  d->bitsPerPixel=bitsPerPixel;
  d->frameData.reserve(totalbytes());
}

Frame::~Frame()
{
  delete d;
}

QByteArray* Frame::frameData()
{
  return &(d->frameData);
}

quint32 Frame::totalbytes()
{
  return (d->bitsPerPixel * d->width * d->height) / 8;
}

quint16 Frame::height()
{
  return d->height;
}

quint16 Frame::width()
{
  return d->width;
}

#include "frame.moc"

