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

#include "framesconverter.h"
#include <QFile>
#include <QDebug>

#ifdef __linux__

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
#include <linux/videodev.h>
#include <sys/ioctl.h>
#include "frame.h"
#include <QCoreApplication>
#include <qstringlist.h>


class VideoConversionData {
  public:
    struct video_picture vid_pic;
    struct video_window vid_win;
    struct video_capability vid_caps;
};


FramesConverter::~FramesConverter()
{
  // TODO move these in another slot. Which one?
  delete videoConversionData;

  videodev->close();
  delete videodev;
}


void FramesConverter::run()
{
  QString filename=QCoreApplication::arguments()[1];
  videodev=new QFile(filename, 0);
  if(! videodev->open(QIODevice::ReadWrite)) {
    qDebug() << "Could not open video device: " << videodev->errorString() << " (" << videodev->error() << ")";
    QThread::exit(1);
    return;
  }
  av_register_all();
  videoConversionData=new VideoConversionData;
  QThread::run();
}

void FramesConverter::gotFrame(Frame* frame)
{
  int dev=videodev->handle();
  if(ioctl(dev, VIDIOCGCAP, &(videoConversionData->vid_caps ))==-1) reportError("error on VIDIOCGCAP: ");
  if(ioctl(dev, VIDIOCGPICT, &(videoConversionData->vid_pic))==-1) reportError("error on VIDIOCGPICT: ");
  (videoConversionData->vid_pic).palette=VIDEO_PALETTE_RGB24;

  if(ioctl(dev, VIDIOCSPICT, &(videoConversionData->vid_pic))==-1) reportError("error on VIDIOCSPICT: ");
  if(ioctl(dev, VIDIOCGWIN, &(videoConversionData->vid_win)) == -1) reportError("error on VIDIOCGWIN: ");
  videoConversionData->vid_win.width=frame->width();
  videoConversionData->vid_win.height=frame->height();
  if(ioctl(dev, VIDIOCSWIN, &(videoConversionData->vid_win)) == -1) reportError("error on VIDIOCSWIN: ");
  
  int destdata_size = avpicture_get_size(PIX_FMT_RGB24, frame->width(), frame->height());
  uint8_t *dest_data = new uint8_t[destdata_size];
//   uint8_t *src_data = new uint8_t[frame->totalbytes()];
  
  AVFrame         *pFrameRGB;
  AVFrame         *pFrameNV21;
  
  static struct SwsContext *img_convert_ctx;

  if(img_convert_ctx == NULL) {       
      img_convert_ctx = sws_getContext(frame->width(), frame->height(), 
                      PIX_FMT_NV12, 
                      frame->width(), frame->height(), PIX_FMT_RGB24, SWS_BICUBIC,
                      NULL, NULL, NULL);
      if(img_convert_ctx == NULL) {
          qDebug()<< "Cannot initialize the conversion context!";
          return;
      }
  }
  pFrameRGB=avcodec_alloc_frame();
  pFrameNV21=avcodec_alloc_frame();
  avpicture_fill((AVPicture *)pFrameNV21,  (uint8_t*) frame->frameData()->data(), PIX_FMT_NV21, frame->width(), frame->height());
  avpicture_fill((AVPicture *)pFrameRGB, dest_data, PIX_FMT_RGB24, frame->width(), frame->height());
  int ret = sws_scale(img_convert_ctx, pFrameNV21->data, pFrameNV21->linesize, 0, frame->height(), pFrameRGB->data, pFrameRGB->linesize);
  int could_write = videodev->write((char*)dest_data, destdata_size );

  delete pFrameNV21;
  delete pFrameRGB;
//   delete img_convert_ctx;
  delete [] dest_data;
  delete frame;
//   delete [] src_data;
}

void FramesConverter::reportError(const char* errorPrefix)
{
  qDebug() << errorPrefix << strerror(errno);
}
#else
#warning You are compiling an application that will do nothing, since you are not on GNU/Linux
#warning If you are happy with that...
void FramesConverter::gotFrame(Frame* frame)
{

}
void FramesConverter::reportError(const char* errorPrefix)
{

}
void FramesConverter::run()
{
    QThread::run();
}
FramesConverter::~FramesConverter()
{

}

#endif

#include "framesconverter.moc"

