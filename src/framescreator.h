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

#ifndef FRAMESCREATOR_H
#define FRAMESCREATOR_H

#include <qt4/QtCore/QObject>
#define FRAMES_HEADER_LENGTH 4

#include "framesfactory.h"
#include "frame.h"

class FramesCreator : public QObject
{
  Q_OBJECT
  public:
    FramesCreator(FramesFactory *framesFactory, QObject *parent=0);
    virtual quint64 remainingBytesForCurrentFrame();
    virtual void addFramesData(const QByteArray &data);
    virtual void createNewFrame(const QByteArray &header);
  private:
    FramesFactory *framesFactory;
    Frame *currentFrame;
  signals:
    void frameProcessed(Frame*);
};

#endif // FRAMESCREATOR_H
