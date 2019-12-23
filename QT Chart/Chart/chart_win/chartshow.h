#ifndef CHARTSHOW_H
#define CHARTSHOW_H

#include <QWidget>
#include <QFile>
#include <QGridLayout>
#include <QFrame>
#include <QColor>
#include <QCheckBox>
#include <QTimer>

#include <stdio.h>
#include <unistd.h>

#include "ChartGL.h"
#include "tthread.h"
#include "mousefilter.h"



namespace Ui {
class ChartShow;
}

#define TO_QT(a) QString::fromLocal8Bit(a)
#define FROM_QT(a) (const char *)((a).toLocal8Bit().data())

#define TO_QT_UTF8(a) QString::fromUtf8(a)
#define FROM_QT_UTF8(a) ((const char *)((a).toUtf8()).data())

#define  CALC_DB(a) (20.0*log10(a))

#define  Num    1024
#define  NumCan   31
#define  perevod 0.0439453

using namespace std;

class TThread;
class ChartGL;

struct DiagNapr_DATA
{
 uchar  TS;
 uchar  RES;
 ushort Azimut[5];
 //float Mosha[5][NumCan];
 uint Mosha[5][NumCan];
}__attribute__((packed));

struct DN_Data
{
 ushort Azimut;
 float Mosha;
};

struct FROM_CifrN
{
 char Ts;
 char N;
 char data_read[50];
};

struct TO_CifrN
{
 char Ts;
 char N;
 char data_send[100];
};


class ChartShow : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChartShow(QWidget *parent = 0);
    ~ChartShow();


    QTimer *myTimer1;

    TThread* thr;
    ChartGL* chartGL_osc;
    ChartGL* chartGL_dn;
    QObject *imit_obj;

    QGridLayout *layDN, *layOsc;

    int panel_x;
    int panel_y;
    int panel_w;
    int panel_h;

    const char *solo_ip;
    QString my_ip;
    char upk15_ip[255];
    uchar cur_page;
    int cur_chnl;
    int north_count;
    int cnt;
    bool perevorot;

    int cnt_draw;
    int cnt_recv;
    int freq_draw;


    int solo_port_write;
    int upk_port_write;
    int solo_port_read_dn;
    int solo_port_read_osc;
    int upk_port_read;

    QColor Mas_color[NumCan];
    QFrame *frs[NumCan];
    QCheckBox *mas_lk[NumCan];

    uchar start_dn,start_osc;
    int NumYData;
    int startMaxY, startMinY, startMaxX, startMinX;

    struct DN_Data dn_data[NumCan][1000];
    struct TO_CifrN write_cifr;
    struct FROM_CifrN read_cifr;
    struct DiagNapr_DATA dn;

    union
    {
     float f_data[Num];
     int   i_data[Num];
     char  c_data[Num*4];
    } osc_data;

    void mouseObrab(QObject *, int , QString );
    void getIpAddr();
    void Init();
    void makeColorFlags();

    void Draw_DN (int);
    void setLabelDN(ushort );
    void sendToSoloDN(int );
    void raskladData();
    void CalcDNShir(int );
    void getOscData(int );
    void Draw_oscGL(int );

    virtual void resizeEvent(QResizeEvent *);



public slots:
    void makeRandData();
    void chbTData_clicked();       //

    void btnClose_clicked();
    void PushButtonStart_clicked();                                //start
    void PushButtonOffAll_clicked();   // откл.каналы 1-31
    void PushButtonOnAll_clicked();     //вкл.каналы 1-31
    void CheckBoxLK_clicked();       // рисование канала
    void PushButtonIshRazmDN_clicked();
    void CheckBoxRegKK_clicked();


    void PushButtonStartOsc_clicked();
    void PushButtonAccept_clicked();
    void PushButtonNoise_clicked();
    void PushButtonSigs_clicked();
    void PushButtonIshRazmOsc_clicked();
    void ComboBoxPoints_activated( const QString & );
    void SpinBoxCanals_valueChanged( const QString & );
    void LineEditUp_textChanged(const QString &);
    void LineEditDown_textChanged(const QString &);
    void LineEditData_textChanged(const QString &);


private:
    Ui::ChartShow *ui;
};

#endif // CHARTSHOW_H
