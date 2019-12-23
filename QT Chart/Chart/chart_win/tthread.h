#ifndef TTHREAD_H
#define TTHREAD_H


#include <QUdpSocket>
#include <qthread.h>
#include <QNetworkInterface>
#include <math.h>

#include "chartshow.h"

class ChartShow;


class TThread : public QThread
{
    Q_OBJECT

 public:
  TThread();
  ~TThread();

  QUdpSocket* SocketFromSoloDN, *SocketFromSoloOsc, *SocketToSolo, *Sock_ToUpk15, *Sock_FromUpk15;
  QHostAddress SoloAddr, UpkAddr;

  uchar SendData[1000];
  uchar RecvData[10000];

  ushort pred_az;
  ushort AZ;
  uchar send_CN;

  void sendDataToServer();
  void close_Main_sockets();
  void open_Main_sockets();

 public slots:
  void run();
  void stop();
  void readFromNetwork();
};


#endif
