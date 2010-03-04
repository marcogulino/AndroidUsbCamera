#include "AndroidUsbCamera.h"
#include "databridge.h"
#include <QTcpSocket>

AndroidUsbCamera::AndroidUsbCamera()
{
  QAbstractSocket *socket = new QTcpSocket(this);
  databridge=new DataBridge(socket, this);
}

void AndroidUsbCamera::stream()
{
  databridge->stream();
}

void AndroidUsbCamera::close()
{
  databridge->close();
}

AndroidUsbCamera::~AndroidUsbCamera()
{

}


#include "AndroidUsbCamera.moc"
