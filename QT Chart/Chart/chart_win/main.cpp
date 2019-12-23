#include <QApplication>
#include "chartshow.h"

#define PRINT_BEGIN_DATA

ChartShow *ParentForm;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChartShow w;

    ParentForm = &w;

    switch(argc)
    {
    case 22:

    case 13:
      w.perevorot = atoi(argv[12]);
    case 12:
      w.cur_page = atoi(argv[11]);
    case 11:
      w.upk_port_read = atoi(argv[10]);
    case 10:
      w.solo_port_read_osc = atoi(argv[9]);
    case 9:
      w.solo_port_read_dn = atoi(argv[8]);
    case 8:
      w.upk_port_write = atoi(argv[7]);
    case 7:
      w.solo_port_write = atoi(argv[6]);
    case 6:
      w.solo_ip = argv[5];
    case 5:
      w.panel_h = atoi(argv[4]);
    case 4:
      w.panel_w = atoi(argv[3]);
    case 3:
      w.panel_y = atoi(argv[2]);
    case 2:
      w.panel_x = atoi(argv[1]);
    case 1:
    break;
    }

#ifdef PRINT_BEGIN_DATA
   qDebug("panel_x = %d   cur_page  = %d",w.panel_x, w.cur_page);
   qDebug("solo_ip = %s my_ip %s",w.solo_ip,FROM_QT_UTF8(w.my_ip));
   qDebug("solo_port_write = %d  upk_port_write = %d",w.solo_port_write, w.upk_port_write);
   qDebug("solo_port_read_dn = %d  solo_port_read_osc = %d upk15_port_read = %d",w.solo_port_read_dn, w.solo_port_read_osc, w.upk_port_read);
#endif


   QFile File;
   File.setFileName(":/styles/my_style.stl");
   File.open(QFile::ReadOnly);
   a.setStyleSheet(QString(File.readAll()));
   File.close();

   if (w.panel_w<900)
    w.panel_w=900;
   if (w.panel_h<600)
    w.panel_h=600;

  // w.panel_x=0;w.panel_y=0;w.panel_w=1280; w.panel_h=1024;

   w.setGeometry(w.panel_x,w.panel_y,w.panel_w,w.panel_h);
   w.show();
   w.Init();

   return a.exec();
}


/*
QLabel
 {
  border: 1px solid rgb(190,190,190);
  font: 14px;
  color: black;
  font-family: PT Sans;
 }

QLabel:disabled
  {
   border: 1px solid rgb(190,190,190);
   font: bold 10px;
   color: gray;
   font-family: PT Sans;
  }
*/
