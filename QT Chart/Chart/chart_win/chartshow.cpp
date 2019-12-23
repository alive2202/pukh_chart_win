#include "tthread.h"
#include "ui_chartshow.h"
#include <QDateTime>

ChartShow::ChartShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartShow)
{
    ui->setupUi(this);

    setWindowFlags(/*Qt::CustomizeWindowHint |  Qt::FramelessWindowHint |*/ Qt::WindowStaysOnTopHint );//| Qt::X11BypassWindowManagerHint);

    panel_x=0;
    panel_y=30;
    panel_w=1024;
    panel_h=768;

    solo_ip="59.0.0.11";

    solo_port_write=5002;
    solo_port_read_dn=7111;
    solo_port_read_osc=5001;
    upk_port_write=8401;
    upk_port_read=8400;

    cur_page=1;

    my_ip = "172.20.180";
    getIpAddr();

    start_dn=0;
    start_osc=0;
    NumYData=0;
    cur_chnl=1;
    cnt=0;
    north_count=0;
    perevorot=0;

    cnt_draw=0;
    cnt_recv=0;
    freq_draw=1;


    Mas_color[0] = QColor(255,0,0);
    Mas_color[1] = QColor(0,0,255);
    Mas_color[2] = QColor(0,255,0);
    Mas_color[3] = QColor(255,255,0);
    Mas_color[4] = QColor(255,0,255);
    Mas_color[5] = QColor(0,255,255);
    Mas_color[6] = QColor(255,126,14);
    Mas_color[7] = QColor(170,0,255);
    Mas_color[8] = QColor(84,155,244);

    Mas_color[9] = QColor(121,255,132);
    Mas_color[10] = QColor(255,0,127);
    Mas_color[11] = QColor(77,77,255);
    Mas_color[12] = QColor(34,120,41);
    Mas_color[13] = QColor(203,255,160);
    Mas_color[14] = QColor(200,101,200);
    Mas_color[15] = QColor(100,100,100);
    Mas_color[16] = QColor(176,152,255);
    Mas_color[17] = QColor(255,100,100);

    Mas_color[18] = QColor(66,170,255);
    Mas_color[19] = QColor(0,0,160);
    Mas_color[20] = QColor(65,0,0);
    Mas_color[21] = QColor(85,85,0);
    Mas_color[22] = QColor(95,0,95);
    Mas_color[23] = QColor(0,190,100);
    Mas_color[24] = QColor(255,92,28);
    Mas_color[25] = QColor(5,218,255);
    Mas_color[26] = QColor(72,255,6);

    Mas_color[27] = QColor(255,255,255);
    Mas_color[28] = QColor(0,0,0);
    Mas_color[29] = QColor(255,42,73);
    Mas_color[30] = QColor(100,0,180);

    mas_lk[0] = ui->chbK1;
    mas_lk[1] = ui->chbK2;
    mas_lk[2] = ui->chbK3;
    mas_lk[3] = ui->chbK4;
    mas_lk[4] = ui->chbK5;
    mas_lk[5] = ui->chbK6;
    mas_lk[6] = ui->chbK7;
    mas_lk[7] = ui->chbK8;
    mas_lk[8] = ui->chbK9;
    mas_lk[9] = ui->chbK10;
    mas_lk[10] = ui->chbK11;
    mas_lk[11] = ui->chbK12;
    mas_lk[12] = ui->chbK13;
    mas_lk[13] = ui->chbK14;
    mas_lk[14] = ui->chbK15;
    mas_lk[15] = ui->chbK16;
    mas_lk[16] = ui->chbK17;
    mas_lk[17] = ui->chbK18;
    mas_lk[18] = ui->chbK19;
    mas_lk[19] = ui->chbK20;
    mas_lk[20] = ui->chbK21;
    mas_lk[21] = ui->chbK22;
    mas_lk[22] = ui->chbK23;
    mas_lk[23] = ui->chbK24;
    mas_lk[24] = ui->chbK25;
    mas_lk[25] = ui->chbK26;
    mas_lk[26] = ui->chbK27;
    mas_lk[27] = ui->chbK28;
    mas_lk[28] = ui->chbK29;
    mas_lk[29] = ui->chbK30;
    mas_lk[30] = ui->chbK31;

    frs[0]=ui->frCanColor1;
    frs[1]=ui->frCanColor2;
    frs[2]=ui->frCanColor3;
    frs[3]=ui->frCanColor4;
    frs[4]=ui->frCanColor5;
    frs[5]=ui->frCanColor6;
    frs[6]=ui->frCanColor7;
    frs[7]=ui->frCanColor8;
    frs[8]=ui->frCanColor9;
    frs[9]=ui->frCanColor10;
    frs[10]=ui->frCanColor11;
    frs[11]=ui->frCanColor12;
    frs[12]=ui->frCanColor13;
    frs[13]=ui->frCanColor14;
    frs[14]=ui->frCanColor15;
    frs[15]=ui->frCanColor16;
    frs[16]=ui->frCanColor17;
    frs[17]=ui->frCanColor18;
    frs[18]=ui->frCanColor19;
    frs[19]=ui->frCanColor20;
    frs[20]=ui->frCanColor21;
    frs[21]=ui->frCanColor22;
    frs[22]=ui->frCanColor23;
    frs[23]=ui->frCanColor24;
    frs[24]=ui->frCanColor25;
    frs[25]=ui->frCanColor26;
    frs[26]=ui->frCanColor27;
    frs[27]=ui->frCanColor28;
    frs[28]=ui->frCanColor29;
    frs[29]=ui->frCanColor30;
    frs[30]=ui->frCanColor31;

    connect( ui->btnClose, SIGNAL(clicked()), this, SLOT(btnClose_clicked()) );
    connect( ui->PushButtonIshRazmDN, SIGNAL(clicked()), this, SLOT(PushButtonIshRazmDN_clicked()) );
    connect( ui->PushButtonStartDN, SIGNAL(clicked()), this, SLOT(PushButtonStart_clicked()) );
    connect( ui->PushButtonOnAll, SIGNAL(clicked()), this, SLOT(PushButtonOnAll_clicked()) );
    connect( ui->PushButtonOffAll, SIGNAL(clicked()), this, SLOT(PushButtonOffAll_clicked()) );
    connect( ui->CheckBoxRegKK, SIGNAL(clicked()), this, SLOT(CheckBoxRegKK_clicked()) );

    for(int i=0;i<NumCan;i++)
    {
     connect( (QObject*)mas_lk[i], SIGNAL(clicked()), this, SLOT(CheckBoxLK_clicked()) );
    }

    connect( ui->PushButtonStart, SIGNAL(clicked()), this, SLOT(PushButtonStartOsc_clicked()) );
    connect( ui->PushButtonAccept, SIGNAL(clicked()), this, SLOT(PushButtonAccept_clicked()) );
    connect( ui->PushButtonNoise, SIGNAL(clicked()), this, SLOT(PushButtonNoise_clicked()) );
    connect( ui->PushButtonSigs, SIGNAL(clicked()), this, SLOT(PushButtonSigs_clicked()) );
    connect( ui->PushButtonIshRazm, SIGNAL(clicked()), this, SLOT(PushButtonIshRazmOsc_clicked()) );
    connect( ui->ComboBoxPoints, SIGNAL(activated(const QString &)), this, SLOT(ComboBoxPoints_activated( const QString & )) );
    connect( ui->SpinBoxCanals, SIGNAL(valueChanged(const QString &)), this, SLOT(SpinBoxCanals_valueChanged( const QString & )) );
    connect( ui->LineEditUp, SIGNAL(textChanged(const QString &)), this, SLOT(LineEditUp_textChanged(const QString &)) );
    connect( ui->LineEditDown, SIGNAL(textChanged(const QString &)), this, SLOT(LineEditDown_textChanged(const QString &)) );
    connect( ui->LineEditData, SIGNAL(textChanged(const QString &)), this, SLOT(LineEditData_textChanged(const QString &)) );


    ui->LineEditUp->setValidator(new QIntValidator(-35000,35000,ui->LineEditUp));
    ui->LineEditDown->setValidator(new QIntValidator(-35000,35000,ui->LineEditDown));
    ui->LineEditData->setValidator(new QIntValidator(0,1024,ui->LineEditData));

    startMaxX=ui->LineEditData->text().toInt();
    startMaxY=ui->LineEditUp->text().toInt();
    startMinY=ui->LineEditDown->text().toInt();
    startMinX=0;

    ui->frCanColor32->hide();
    ui->chbK32->hide();
    //ui->lblPr->hide();


    myTimer1 = new QTimer(this);

    connect(myTimer1, SIGNAL(timeout()), this, SLOT(makeRandData()) );
    connect( ui->chbTData, SIGNAL(clicked()), this, SLOT(chbTData_clicked()) );



}

ChartShow::~ChartShow()
{
    delete ui;
}

void ChartShow::getIpAddr()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(uint i=0;i<list.count();i++)
    {
        if(list[i].protocol()==QAbstractSocket::IPv4Protocol)
          {
           QString get_ip = list[i].toString();

           if(my_ip == get_ip.section('.',0,2))
             {
              int pnl_type = get_ip.section('.',3,3).toInt();

              strcpy(upk15_ip,FROM_QT_UTF8("1.0.0."+QString::number(pnl_type)));
              my_ip = my_ip+"."+QString::number(pnl_type);

              //qDebug("%d", pnl_type);
             }
           //qDebug("all system ip %s %s", FROM_QT_UTF8(get_ip), FROM_QT_UTF8(get_ip.section('.',0,2)));
          }
    }
}

void ChartShow::Init()
{
 ui->btnClose->setParent(ui->MainFrame);
 ui->btnClose->move(ui->MainFrame->width() - ui->btnClose->width() - 2,3);
 ui->btnClose->show();

 chartGL_dn = new ChartGL(ui->frDN_chart);
 chartGL_osc = new ChartGL(ui->frOsc_chart);

 layDN = new QGridLayout(ui->frDN_chart);
 layDN->setContentsMargins(0,0,0,0);
 layDN->addWidget(chartGL_dn,0,0);

 layOsc = new QGridLayout(ui->frOsc_chart);
 layOsc->setContentsMargins(0,0,0,0);
 layOsc->addWidget(chartGL_osc,0,0);


 chartGL_dn->resize(ui->frDN_chart->width(),ui->frDN_chart->height());
 chartGL_osc->resize(ui->frOsc_chart->width(),ui->frOsc_chart->height());



 if(cur_page==0||cur_page==2)
 {
  chartGL_dn->setBackgroundColor(QColor(100,100,100));//BackgroundColor=QColor(100,100,100);
  chartGL_dn->TextAxisColor=QColor(255,255,255);
  chartGL_dn->AxisColor=QColor(255,255,255);
  chartGL_dn->LineStippleColor=QColor(0,0,0);

  chartGL_dn->Point=false;
  chartGL_dn->PointSize=0;
  chartGL_dn->Line=true;

  chartGL_dn->Oscill=0;
  chartGL_dn->ShowZoomUpdate=0;
  chartGL_dn->initializeGL();


  chartGL_dn->SetStartMinX(0);
  chartGL_dn->SetStartMaxX(360);
  chartGL_dn->SetStartMinY(-90);
  chartGL_dn->SetStartMaxY(5);
  chartGL_dn->SetRezh(1);
  chartGL_dn->SetStartNumXTicks(10*chartGL_dn->Rezh);
  chartGL_dn->SetStartNumYTicks(10*chartGL_dn->Rezh);
  chartGL_dn->SetStart();
 }
 else
 {
  chartGL_osc->Oscill=1;
  chartGL_osc->Point=false;
  chartGL_osc->PointSize=0;
  chartGL_osc->Line=true;
  chartGL_osc->setBackgroundColor(QColor(10,10,10));
  chartGL_osc->initializeGL();
  chartGL_osc->SetStart();
 }

 makeColorFlags();

 if(cur_page==0||cur_page==1)
   {
     ui->tabWidget->removeTab(!cur_page);
     QString str;
     str = QString("%1").number(ui->tabWidget->width()-ui->btnClose->width() - 2);
     ui->tabWidget->setStyleSheet("QTabBar::tab { width: "+str+"px; }");
   }
 else
   {
     QString str = QString::number(300);
     ui->tabWidget->setStyleSheet("QTabBar::tab { width: "+str+"px; }");
   }

 ui->tabWidget->setCurrentIndex(0);

 thr = new TThread();
 thr->open_Main_sockets();

 ui->LineEditData->installEventFilter(new MouseFilter(ui->LineEditData));
 ui->LineEditUp->installEventFilter(new MouseFilter(ui->LineEditUp));
 ui->LineEditDown->installEventFilter(new MouseFilter(ui->LineEditDown));
 ui->SpinBoxCanals->installEventFilter(new MouseFilter(ui->SpinBoxCanals));

}

void ChartShow::makeColorFlags()
{
 QString str;

 for(int i=0; i<NumCan; i++)
    {
     str = "rgb("+QString("%1").number(Mas_color[i].red())+","+
                  QString("%1").number(Mas_color[i].green())+","+
                  QString("%1").number(Mas_color[i].blue())+");";

     frs[i]->setStyleSheet("QFrame {background-color: "+str+"; }");
    }
 update();
}

void ChartShow::mouseObrab(QObject *obj, int par, QString data)
{
 char str[255]="\0";
 int sender=0;

   if(obj==ui->LineEditData)
    {
     if(par)
      {
       strcat(str, FROM_QT_UTF8(ui->tlDataOsc->text()));
       strcat(str, " @([0-9]{1,5})");
       sender=1;
      }
     else
       LineEditData_textChanged(data);
    }

  if(obj==ui->LineEditUp)
    {
     if(par)
      {
       strcat(str, FROM_QT_UTF8(ui->tlTopOsc->text()));
       strcat(str, " @(-[0-9]{1,9})|([0-9]{1,9}*))");
       sender=1;
      }
     else
       LineEditUp_textChanged(data);
    }

  if(obj==ui->LineEditDown)
    {
     if(par)
      {
       strcat(str, FROM_QT_UTF8(ui->tlBottomOsc->text()));
       strcat(str, " @(-[0-9]{1,9})|([0-9]{1,9}*))");
       sender=1;
      }
     else
       LineEditDown_textChanged(data);
    }

   if(obj==ui->SpinBoxCanals)
    {
     if(par)
      {
       strcat(str, "Канал ");
       strcat(str, " @([0-9]{1,2})");
       sender=1;
      }
     else
       SpinBoxCanals_valueChanged(data);
    }

       //qDebug("%s ", str);


if(sender)
{
 write_cifr.Ts=1;
 sprintf(write_cifr.data_send, str);
 write_cifr.N = strlen(write_cifr.data_send);

 thr->Sock_ToUpk15->writeDatagram((const char*)&write_cifr,sizeof(write_cifr),thr->UpkAddr,upk_port_write);
 usleep(10000);
}

}

void ChartShow::PushButtonStart_clicked()                                //start
{
 start_dn  = !start_dn;
 if(start_dn)
   {
    ui->lblPr->setText( TO_QT_UTF8("Ожидание приема данных") );

    sendToSoloDN(300);
   }
 else
   {
    ui->lblPr->setText( TO_QT("") );
   }

 north_count=0;
 cnt=0;
}

void ChartShow::PushButtonIshRazmDN_clicked() //исходный размер графика
{
 chartGL_dn->ChangeFirst();
 chartGL_dn->updateGL();
}

void ChartShow::PushButtonOnAll_clicked()     //вкл.каналы 1-31
{
  for(int j =0; j < NumCan; j++ )
     mas_lk[j]->setChecked(true);

  CheckBoxLK_clicked();

}

void ChartShow::PushButtonOffAll_clicked()   // откл.каналы 1-31
{

 for(int j =0; j < NumCan; j++ )
    mas_lk[j]->setChecked(false);

 CheckBoxLK_clicked();

}

void ChartShow::CheckBoxLK_clicked()
{

  for (int j =0; j < NumCan; j++ )
  {
   if(chartGL_dn->Series.size()>0)
    chartGL_dn->Series.erase(j);

    if (mas_lk[j]->isChecked())
       Draw_DN(j);
  }

chartGL_dn->updateGL();

}

void ChartShow::CheckBoxRegKK_clicked()
{

 if(ui->CheckBoxRegKK->isChecked())
   {
    mas_lk[28]->setText(TO_QT_UTF8("КК 1"));
    mas_lk[29]->setText(TO_QT_UTF8("КК 2"));
    mas_lk[30]->setText(TO_QT_UTF8("КК 3"));
   }
 else
   {
    mas_lk[28]->setText(TO_QT_UTF8("Канал 1"));
    mas_lk[29]->setText(TO_QT_UTF8("Канал 2"));
    mas_lk[30]->setText(TO_QT_UTF8("Канал 3"));
   }

 chartGL_dn->updateGL();
}


void ChartShow::btnClose_clicked()
{
 thr->close_Main_sockets();
 thr->terminate();
 close();
}

void ChartShow::Draw_DN (int N)
{
 int MaxY=0;
 for(int i =0; i < NumYData; i++ )
    {
     if(i<5)
       {
        if( dn_data[N][i].Azimut*perevod> dn_data[N][4].Azimut*perevod) continue;
        else chartGL_dn->Series[N].push_back(TSeriesPoints(dn_data[N][i].Azimut*perevod, dn_data[N][i].Mosha, Mas_color[N]));
       }
     else if(i>(NumYData-5))
       {
        if( dn_data[N][i].Azimut*perevod< dn_data[N][NumYData].Azimut*perevod) continue;
        else chartGL_dn->Series[N].push_back(TSeriesPoints(dn_data[N][i].Azimut*perevod, dn_data[N][i].Mosha, Mas_color[N]));
       }
     else
        chartGL_dn->Series[N].push_back(TSeriesPoints(dn_data[N][i].Azimut*perevod, dn_data[N][i].Mosha, Mas_color[N]));

     //qDebug("draw %d %f  %f", i, dn_data[N][i].Azimut*perevod , dn_data[N][i].Mosha);

     if ( dn_data[N][i].Mosha > MaxY)
      MaxY= (int)dn_data[N][i].Mosha;

     //qDebug ("MaxY %d ", MaxY);
}

//if ( MaxY>90)
//{
chartGL_dn->SetStartMaxY(MaxY);
//chartGL_dn->updateGL();

//printf ("StartMaxY %d \n", MaxY);
//}
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//---------Функции осциллографа--------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------

void ChartShow::PushButtonStartOsc_clicked()
{
 start_osc  = !start_osc;
}

void ChartShow::PushButtonAccept_clicked()
{
 startMaxY=ui->LineEditUp->text().toInt();
 chartGL_osc->SetStartMaxY(startMaxY);
 startMinY=ui->LineEditDown->text().toInt();
 chartGL_osc->SetStartMinY(startMinY);
 startMaxX=ui->LineEditData->text().toInt();
 chartGL_osc->SetStartMaxX(startMaxX);
 chartGL_osc->SetStartMinX(0);

 chartGL_osc->SetStart();
 chartGL_osc->updateGL();

}

void ChartShow::PushButtonNoise_clicked()  // шумы
{
 ui->LineEditUp->setText("30");
 ui->LineEditDown->setText("-30");

 startMaxY=ui->LineEditUp->text().toInt();
 startMinY=ui->LineEditDown->text().toInt();

 chartGL_osc->SetStartMaxY(startMaxY);
 chartGL_osc->SetStartMinY(startMinY);
 chartGL_osc->SetStart();
 chartGL_osc->updateGL();
}

void ChartShow::PushButtonSigs_clicked()     //сигналы
{
 ui->LineEditUp->setText("32767");
 ui->LineEditDown->setText("-32767");


 startMaxY=ui->LineEditUp->text().toInt();
 startMinY=ui->LineEditDown->text().toInt();

 chartGL_osc->SetStartMaxY(startMaxY);
 chartGL_osc->SetStartMinY(startMinY);
 chartGL_osc->SetStart();
 chartGL_osc->updateGL();
}

void ChartShow::LineEditData_textChanged(const QString & str)
{
 if(str.toInt()>1024) { ui->LineEditData->setText(QString::number(1024)); return; }
 if(str.toInt()<1) { ui->LineEditData->setText(QString::number(1)); return; }


 ui->LineEditData->setText(str);
 startMaxX=ui->LineEditData->text().toInt();
 chartGL_osc->SetStartMaxX(startMaxX);
 chartGL_osc->SetStart();

}

void ChartShow::LineEditUp_textChanged(const QString & str)     //    верхняя граница
{
 if(str.toInt()>660000) { ui->LineEditUp->setText(QString::number(660000));  return; }
 if(str.toInt()<-660000) { ui->LineEditUp->setText(QString::number(-660000));  return; }


 ui->LineEditUp->setText(str);
 startMaxY=ui->LineEditUp->text().toInt();
 chartGL_osc->SetStartMaxY(startMaxY);
 chartGL_osc->SetStart();
// chartGL_osc->updateGL();
}

void ChartShow::LineEditDown_textChanged(const QString & str)      //    нижняя граница
{
 if(str.toInt()>659999) { ui->LineEditDown->setText(QString::number(659999));  return; }
 if(str.toInt()<-660001) { ui->LineEditDown->setText(QString::number(-660001));  return; }

 ui->LineEditDown->setText(str);
 startMinY=ui->LineEditDown->text().toInt();
 chartGL_osc->SetStartMinY(startMinY);
 chartGL_osc->SetStart();
//chartGL_osc->updateGL();
}

void ChartShow::PushButtonIshRazmOsc_clicked() //исходный размер графика
{
 chartGL_osc->ChangeFirst();
 chartGL_osc->updateGL();
}

void ChartShow::ComboBoxPoints_activated( const QString & )
{
 unsigned int buf[20];

 buf[0] = 101;
 buf[1] = ui->ComboBoxPoints->currentIndex();

 if(ui->ComboBoxPoints->currentIndex()>1)
   {
    ui->SpinBoxCanals->setMaximum(32);
    if(ui->SpinBoxCanals->value()>32) cur_chnl=1;
   }
 else
   {
    ui->SpinBoxCanals->setMaximum(52);
   }

 if( (ui->ComboBoxPoints->currentIndex()==1) && (cur_chnl<=48))
 {
  if(((cur_chnl-1)%8)<4) buf[2] = cur_chnl+4;
  else buf[2] = cur_chnl-4;
 }
 else
 buf[2]=cur_chnl;

 thr->SocketToSolo->writeDatagram((const char*)&buf,sizeof(buf),thr->SoloAddr,solo_port_write);

 QFont f("Helvetica", 11, 0);
 chartGL_osc->renderText(chartGL_osc, 100, 100, QString::number(1000), chartGL_osc->TextAxisColor, f, Qt::AlignHCenter | Qt::AlignTop);
 chartGL_osc->updateGL();

}

void ChartShow::SpinBoxCanals_valueChanged( const QString & str )
{
// printf("set %d %f %f\n", str.toInt(), SpinBoxCanals->maxValue(), SpinBoxCanals->minValue());

 if((str.toInt()>(int)ui->SpinBoxCanals->maximum())||(str.toInt()<(int)ui->SpinBoxCanals->minimum())) return;

 ui->SpinBoxCanals->setValue(str.toInt());

 cur_chnl=str.toInt();

 unsigned int buf[20];

 buf[0] = 100;
 if( (ui->ComboBoxPoints->currentIndex()==1) && (cur_chnl<=48))
 {
  if(((cur_chnl-1)%8)<4) buf[1] = cur_chnl+4;
  else buf[1] = cur_chnl-4;
 }
 else
 buf[1]=cur_chnl;

// printf("%d %d \n", buf[0],buf[1]);

 thr->SocketToSolo->writeDatagram((const char*)&buf,sizeof(buf),thr->SoloAddr,solo_port_write);

// chartGL_osc->updateGL();

}

void ChartShow::raskladData()
{
 float max=0;

 for (int j =0; j < NumCan; j++ )
  for (int i =0; i < NumYData; i++ )
      {
       if(dn_data[j][i].Mosha==0)
        dn_data[j][i].Mosha=0;
       else
        dn_data[j][i].Mosha=(float)CALC_DB(dn_data[j][i].Mosha);

       if(dn_data[j][i].Mosha>max) max=dn_data[j][i].Mosha;

      }


 for (int j =0; j < NumCan; j++ )
  for (int i =0; i < NumYData; i++ )
       dn_data[j][i].Mosha-=max;


 //for (int j =0; j < NumCan; j++ ) CalcDNShir(j);

}

void ChartShow::CalcDNShir(int N_c)
{
 N_c=N_c;
/*
 int counter;
 float max=0;
 int n_max=0,n_l=0,n_r=0;
 float razn=0;

 for(int i=0;i<cnt;i++)
    {
     if(max<data[N_c][i].Mosha) { max=data[N_c][i].Mosha; n_max=i; }
    }

 counter=n_max;
 while(1)
    {
     if((data[N_c][n_max].Mosha-data[N_c][counter--].Mosha)<-1.5) { n_l=counter; break; }
    }

 counter=n_max;
 while(1)
    {
     if((data[N_c][n_max].Mosha-data[N_c][counter++].Mosha)<-1.5) { n_r=counter; break; }
    }

 razn = data[N_c][n_r].Azimut - data[N_c][n_l].Azimut;

 printf("shirina %f \n", razn);

*/
}


void ChartShow::setLabelDN(ushort az)
{
 QString str;

 if(az==2222)
   {
    str = TO_QT_UTF8("Данные приняты");
    ui->PushButtonStartDN->setChecked(false);
    start_dn=0;
   }
 else
    str = TO_QT_UTF8("Идет прием данных ")+QString ("%1").arg(az)+ " %";

 ui->lblPr->setText(str);
 //qDebug("%s", FROM_QT_UTF8(str));
}

void ChartShow::sendToSoloDN(int w)
{
 if(ui->CheckBoxRegKK->isChecked())
   thr->SocketToSolo->writeDatagram((const char*)&w,sizeof(w),thr->SoloAddr,solo_port_write);
}

void ChartShow::getOscData(int n_read)
{
 if(start_osc)
   {
    Draw_oscGL(0);

    //chartGL_osc->RefreshSeriesGL();
    chartGL_osc->updateGL();

    cnt_draw++;

    if(n_read!=0)
      {
       cnt_recv++;
       ui->tlNumWords->setText(QString("%1").arg(cnt_recv));
      }
     update();
    }
}

void ChartShow::Draw_oscGL(int num)
{
 if(chartGL_osc->Series.size()>0)
  chartGL_osc->Series.erase(num);

 for(int i =0; i < Num; i++ )
    {
     chartGL_osc->Series[num].push_back(TSeriesPoints(i, osc_data.f_data[i], Mas_color[5]));
    }

 memset(&(osc_data.f_data[0]), 0, 4*Num);
}

void ChartShow::resizeEvent(QResizeEvent *e)
{
 if(e->oldSize()!=e->size())
      {
       ui->btnClose->move(ui->MainFrame->width() - ui->btnClose->width() - 2,3);
       ui->btnClose->show();
       QString str;
       str = QString("%1").number(ui->tabWidget->width()-ui->btnClose->width() - 2);
       ui->tabWidget->setStyleSheet("QTabBar::tab { width: "+str+"px; }");
      }

 return QWidget::resizeEvent(e);
}

void ChartShow:: makeRandData()
{
 static int num=0;

 for(int i=0;i<Num;++i)
    {
     osc_data.f_data[i] = rand()*32768./RAND_MAX-16384.;
    }

 getOscData(Num);
}

void ChartShow::chbTData_clicked()
{
    if(ui->chbTData->isChecked())
      {
       QDateTime dt;

       uint start_point = dt.currentDateTime().time().second()+dt.currentDateTime().time().hour()*3600+
       dt.currentDateTime().time().minute()*60;

       qDebug("start point = %d", start_point);

       srand(start_point);

       myTimer1->start(10);
      }
    else
       myTimer1->stop();
}
