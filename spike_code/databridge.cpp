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

#include "databridge.h"
#include <QDebug>
// V4l stuff
#include <linux/videodev2.h>
#include <linux/videodev.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>


extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}


DataBridge::DataBridge ( QAbstractSocket* socket, QObject* parent ) : QObject ( parent )
{
  this->socket=socket;
  videodev.setFileName("/dev/video1");
}

void DataBridge::close()
{
  qDebug() << "Closing device";
  videodev.close();
}


void DataBridge::stream()
{
  av_register_all();
  bool first_read=true;

  socket->connectToHost("localhost", 8080, QIODevice::ReadOnly);
  if( ! socket->waitForConnected()) return;
  struct video_picture vid_pic;
  struct video_window vid_win;
  struct video_capability vid_caps;

  videodev.open(QIODevice::ReadWrite);
  int dev=videodev.handle();

  
//   int dev=open("/dev/video1", O_SYNC, O_RDWR);
//   if(dev==-1) perror("error on open: ");
  if(ioctl(dev, VIDIOCGCAP, &vid_caps)==-1) perror("error on VIDIOCGCAP: ");
  if(ioctl(dev, VIDIOCGPICT, &vid_pic)==-1) perror("error on VIDIOCGPICT: ");
  vid_pic.palette=VIDEO_PALETTE_RGB24;

  if(ioctl(dev, VIDIOCSPICT, &vid_pic)==-1) perror("error on VIDIOCSPICT: ");
  if(ioctl(dev, VIDIOCGWIN, &vid_win) == -1) perror("error on VIDIOCGWIN: ");
  vid_win.width=320;
  vid_win.height=240;
  if(ioctl(dev, VIDIOCSWIN, &vid_win) == -1) perror("error on VIDIOCSWIN: ");

//   int winSize=vid_win.width * vid_win.height * 3;

  int winSize=(vid_win.width*vid_win.height) * 12 / 8;
  int w = vid_win.width;
  int h = vid_win.height;
  int destdata_size = avpicture_get_size(PIX_FMT_RGB24, w, h);
  uint8_t *dest_data = new uint8_t[destdata_size];
  uint8_t *src_data = new uint8_t[winSize];
  QByteArray data;
  AVFrame         *pFrameRGB;
  AVFrame         *pFrameNV21;
  while(socket->waitForReadyRead()) {
    data.append(socket->readAll());
    if(first_read) {
      first_read=false;
//       qDebug() << "Got first " << data.size() << " bytes";
//       qDebug() << "Original bytearray: " << data.toHex();
//       qDebug() << "Stripping header: " << QByteArray(data.data(), 4).toHex();
      data.remove(0,4);
//       qDebug() << "Remaining: " << data.toHex() << ", " << data.size() << " bytes";
    }
    if(data.size()>=winSize) {
      qDebug() << "Got data size: " << data.size();
      QByteArray tempBA=data.left(winSize);
      
      
      
      static struct SwsContext *img_convert_ctx;

      if(img_convert_ctx == NULL) {	      
	      img_convert_ctx = sws_getContext(w, h, 
					      PIX_FMT_NV12, 
					      w, h, PIX_FMT_RGB24, SWS_BICUBIC,
					      NULL, NULL, NULL);
	      if(img_convert_ctx == NULL) {
		      qDebug()<< "Cannot initialize the conversion context!";
		      return;
	      }
      }
      pFrameRGB=avcodec_alloc_frame();
      pFrameNV21=avcodec_alloc_frame();
      qDebug() << "fill in pFrameNV21";
      avpicture_fill((AVPicture *)pFrameNV21,  (uint8_t*) data.data(), PIX_FMT_NV21, w, h);
      qDebug() << "fill in pFrameRGB";
      avpicture_fill((AVPicture *)pFrameRGB, dest_data, PIX_FMT_RGB24, w, h);
      qDebug() << "doing sws_scale";
      int ret = sws_scale(img_convert_ctx, pFrameNV21->data, pFrameNV21->linesize, 0, 240, pFrameRGB->data, pFrameRGB->linesize);
      qDebug() << "Ret: " << ret;
      int could_write = videodev.write((char*)dest_data, destdata_size );
//       write(videofile, tempBA.data(), tempBA.size());
      data.remove(0, winSize);
      if(could_write>-1) {
	qDebug() << "wrote " << could_write << "bytes..";
	first_read=true;
      }
      else
	qDebug() << "Error writing "<< tempBA.size() << " bytes of data on file descriptor " << dev << ": " << could_write << " " << strerror(errno);
    }
  }
  videodev.close();
}
