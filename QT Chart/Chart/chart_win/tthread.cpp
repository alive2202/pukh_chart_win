#include <qlineedit.h>
#include <qevent.h>
#include <sys/time.h>
#include <stdlib.h>


#include "tthread.h"
#include "perevorot.h"


extern ChartShow *ParentForm;

TThread::TThread()
{
 SocketFromSoloDN=0;
 SocketFromSoloOsc=0;
 SocketToSolo=0;
 Sock_ToUpk15=0;
 Sock_FromUpk15=0;

 send_CN=0;
}

TThread::~TThread()
{
}

void TThread::run()
{
}

void TThread::stop()
{
}

void TThread::open_Main_sockets()
{
    SocketFromSoloDN = new QUdpSocket (this);
    SocketFromSoloDN->bind(ParentForm->solo_port_read_dn,QUdpSocket::ShareAddress);
    bool eee = connect(SocketFromSoloDN,SIGNAL(readyRead()),this,SLOT(readFromNetwork()));

    SocketFromSoloOsc = new QUdpSocket (this);
    SocketFromSoloOsc->bind(ParentForm->solo_port_read_osc,QUdpSocket::ShareAddress);
    eee = connect(SocketFromSoloOsc,SIGNAL(readyRead()),this,SLOT(readFromNetwork()));

    Sock_FromUpk15 = new QUdpSocket (this);
    Sock_FromUpk15->bind(ParentForm->upk_port_read,QUdpSocket::ShareAddress);
    eee = connect(Sock_FromUpk15,SIGNAL(readyRead()),this,SLOT(readFromNetwork()));

    //qDebug("Create sockets %d %d", ParentForm->solo_port_read_dn, ParentForm->solo_port_read_osc);

    SocketToSolo = new QUdpSocket (this);
    Sock_ToUpk15 =  new QUdpSocket (this);

    SoloAddr.setAddress("172.20.182.163");
    //SoloAddr.setAddress(ParentForm->solo_ip);
    UpkAddr.setAddress(ParentForm->upk15_ip);
}

void TThread::readFromNetwork()
{
    while(SocketFromSoloDN->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(SocketFromSoloDN->pendingDatagramSize());

        //SocketFromSoloDN->readDatagram(data.data(),data.size());
        SocketFromSoloDN->readDatagram((char*)&ParentForm->dn,sizeof(ParentForm->dn));

        if(!ParentForm->start_dn) continue;

        if(ParentForm->dn.Azimut[0]>ParentForm->dn.Azimut[4])
          {
           ParentForm->north_count++;
          }
        else
         {
          if(pred_az>ParentForm->dn.Azimut[0])
            {
             ParentForm->north_count++;
            }
         }
        pred_az=  ParentForm->dn.Azimut[4];

        if(ParentForm->north_count == 1)
        {
         for(int i=0; i<5; i++)
            {
             for(int j=0; j<NumCan; j++)
                {
                 ParentForm->dn_data[j][ParentForm->cnt].Azimut =  ParentForm->dn.Azimut [i];
                 ParentForm->dn_data[j][ParentForm->cnt].Mosha =  ParentForm->dn.Mosha [i][j];
                 //qDebug ("Az  %d\n",  frm->dn.Azimut [0]/8192*  ptrChartShow->dn.Azimut [i]);
                 //qDebug ("az  %d m %d %d \n",  frm->data[j][cnt].Azimut,frm->data[j][cnt].Mosha, frm->dn.Mosha[i][j]);
                }

             ParentForm->cnt ++;
            }

        //qDebug("%d %d %d\n", frm->dn.Azimut[0], frm->dn.Azimut[4], north_count);

         if((ParentForm->cnt%50)==0)
           {
            AZ =(short)(( ParentForm->dn.Azimut [0]/8191.0)*100);
            ParentForm->setLabelDN(AZ);
            //QCustomEvent* Event;
            //Event=new QCustomEvent(2222);
            //postEvent( frm,Event);
           }
        }

        if(ParentForm->north_count == 2)
          {
           qDebug("cnt = %d \n",ParentForm->cnt);

           ParentForm->NumYData=ParentForm->cnt;
           ParentForm->cnt=0;
           ParentForm->raskladData();
           ParentForm->setLabelDN(2222);

           //QCustomEvent* Event;
           //Event=new QCustomEvent(1111);
           //postEvent(frm,Event);
           ParentForm->north_count++;

           ParentForm->sendToSoloDN(301);
           ParentForm->start_dn=0;
           ParentForm->CheckBoxLK_clicked();
          }

    }

    while(Sock_FromUpk15->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(Sock_FromUpk15->pendingDatagramSize());

        Sock_FromUpk15->readDatagram((char*)&ParentForm->read_cifr,sizeof(ParentForm->read_cifr));

        if(ParentForm->read_cifr.Ts==1&&send_CN==1)
          {
           send_CN=0;
           if(ParentForm->read_cifr.N!=0)
             {
              char read_text[50] = "\0";

              strncpy(read_text,ParentForm->read_cifr.data_read,ParentForm->read_cifr.N);
              float tmp = atof(read_text);
              QString str = QString("%1").arg(tmp);
              ParentForm->mouseObrab(ParentForm->imit_obj, 0, str);
             }
          }

    }

    while(SocketFromSoloOsc->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(SocketFromSoloOsc->pendingDatagramSize());

        //qDebug("recv osc data %d", ParentForm->start_osc);

        char * ptr = &(ParentForm->osc_data.c_data[0]);

        int num = SocketFromSoloOsc->readDatagram((char*)ptr,sizeof(ParentForm->osc_data));

        if(ParentForm->perevorot)
          {
           for(int i=0;i<Num;i++)
              ParentForm->osc_data.i_data[i] = Turn_int(ParentForm->osc_data.i_data[i]);
          }

        ParentForm->getOscData(num);

    }

}

void TThread::sendDataToServer()
{    
 SocketToSolo->writeDatagram((char*)&SendData,sizeof(SendData),SoloAddr,ParentForm->solo_port_write);

 //qDebug("sendDataToServer() ");
}

void TThread::close_Main_sockets()
{
 SocketFromSoloDN->close();
 SocketFromSoloOsc->close();
 SocketToSolo->close();
 Sock_FromUpk15->close();

}
