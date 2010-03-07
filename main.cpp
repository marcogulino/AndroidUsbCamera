#include <QCoreApplication>
#include "androidusbcamera.h"
#include <qstringlist.h>
#include <qtextstream.h>
#include <QFileInfo>
#include <QDebug>

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("AndroidUsbCamera");
    QString filename=app.arguments().first();
    if( app.arguments().size() != 2 || ! QFileInfo(app.arguments()[1]).isWritable()) {
      QTextStream(stdout) << "Usage: " << app.applicationName() << " <video device>\n";
      QTextStream(stdout) << "Usually video device is one of /dev/videoN files\n";
      QTextStream(stdout) << "Best match finding the \"output\" device for vloopback running \"dmesg | grep vloopback\"\n";
      return 1;
    }
    AndroidUsbCamera camera;
    return app.exec();
}
