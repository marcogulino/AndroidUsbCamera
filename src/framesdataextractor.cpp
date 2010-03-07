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

#include "framesdataextractor.h"
FramesDataExtractor::FramesDataExtractor ( FramesCreator* framesCreator, QObject* parent ) : QObject ( parent )
{
  this->framesCreator=framesCreator;
}

void FramesDataExtractor::gotFramesData(QByteArray data)
{
  quint64 remainingBytes=framesCreator->remainingBytesForCurrentFrame();
  if(!remainingBytes) {
    remainingBytes=createNewFrame(&data);
  }
  if(remainingBytes<data.size()) {
    framesCreator->addFramesData(data.left(remainingBytes));
    data.remove(0, remainingBytes);
    remainingBytes=createNewFrame(&data);
  }
  framesCreator->addFramesData(data);
}

quint64 FramesDataExtractor::createNewFrame ( QByteArray *data )
{
    QByteArray header=data->left(FRAMES_HEADER_LENGTH);
    framesCreator->createNewFrame(header);
    data->remove(0, FRAMES_HEADER_LENGTH);
    return framesCreator->remainingBytesForCurrentFrame();
}

#include "framesdataextractor.moc"
