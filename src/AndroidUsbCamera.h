#ifndef AndroidUsbCamera_H
#define AndroidUsbCamera_H

#include <QtCore/QObject>
class DataBridge;
class AndroidUsbCamera : public QObject
{
Q_OBJECT
public:
    AndroidUsbCamera();
    virtual ~AndroidUsbCamera();

  public slots:
    void stream();
    void close();
  private:
    DataBridge *databridge;
    
};

#endif // AndroidUsbCamera_H
