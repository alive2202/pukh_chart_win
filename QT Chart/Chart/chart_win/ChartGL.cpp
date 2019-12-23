/***************************************************************************
                          ChartGL.cpp  -  description
                             -------------------
    begin                : 18 07 2012
    copyright            : (C) 2012 by Alexander Pukh
 ***************************************************************************/
#include <stdlib.h>
#include <unistd.h>
#include <qpainter.h>
#include <cmath>

#include <qcheckbox.h>
#include "ChartGL.h"

/*
TSeriesPoints::TSeriesPoints(double X, double Y, QColor Color)
{
 x=X;
 y=Y;
 color=Color;
}
*/

ChartGL:: ChartGL(QWidget *parent)
     :QGLWidget(parent)
{
//Границы выделения нет
 ZoomIsShown = false;

 BackgroundColor=QColor(10,10,10);
 TextAxisColor=QColor(255,255,255);
 AxisColor=QColor(255,255,255);
 LineStippleColor=QColor(105,105,105);
 ICOColor=QColor(150,150,150);
 ICOColorMain=QColor(245,245,245);
 SelectionPointColor=QColor(0,255,0);
 SelectionTrackColor=QColor(255,255,255);
 TrackColor=QColor(255,255,0);//QColor(250,70,10);//QColor(255,0,0);


 font_axis = QFont("Helvetica", 8, 0);

 setFocusPolicy(Qt::StrongFocus);

 MarginL=50;
 MarginT=10;
 MarginR=15;
 MarginB=40;

 Point=true;
 PointSize=2;
 Line=false;
 LineWidth=1;
 ICO=false;
 Square=false;
 ShowZoomUpdate=true;
 Rezh=1;
 NPoint=1;
 Track_Selection=false;
 Point_Selection=false;

 StartMinX=0;
 StartMaxX=1024;
 StartNumXTicks=10;
 StartMinY=-32767;
 StartMaxY=32767;
 StartNumYTicks=10;


 GLSettings settings;
 settings.MinX = StartMinX;
 settings.MaxX = StartMaxX;
 settings.NumXTicks = StartNumXTicks;
 settings.MinY = StartMinY;
 settings.MaxY = StartMaxY;
 settings.NumYTicks = StartNumYTicks;
 settings.Adjust();

 SetGLSettings(settings);

 ChartW_Pix = (float)(settings.MaxX-settings.MinX)/(float)(width()-MarginR-MarginL);
 ChartH_Pix = (float)(settings.MaxY-settings.MinY)/(float)(height()-MarginT-MarginB);

 show();

// printf("ChartGL \n");
}

ChartGL::~ChartGL()
{

}

void ChartGL::paintGL()
{
// qglClearColor(BackgroundColor);
// glClear(GL_COLOR_BUFFER_BIT);

 RefreshGridGL();
 RefreshSeriesGL();

 // printf("paintGL %d\n",BackgroundColor.red());

// swapBuffers();
}

void ChartGL::initializeGL()
{
 qglClearColor(BackgroundColor);
 qDebug("initializeGL %d %x\n",BackgroundColor.red(), this);

}


void ChartGL::resizeGL(int nWidth, int nHeight)
{
 GLSettings settings = ZoomStack[CurZoom];

// printf("curzoom = %d Resize !!!! %f   %f   %f   %f \n", CurZoom, settings.MinX, settings.MaxX, settings.MinY, settings.MaxY );
 ChartW_Pix = (float)(settings.MaxX-settings.MinX)/(float)(width()-MarginR-MarginL);
 ChartH_Pix = (float)(settings.MaxY-settings.MinY)/(float)(height()-MarginT-MarginB);


 glViewport(0,0,(GLint)nWidth,(GLint)nHeight);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(settings.MinX - MarginL*ChartW_Pix,settings.MaxX + MarginR*ChartW_Pix, settings.MinY - MarginB*ChartH_Pix, settings.MaxY + MarginT*ChartH_Pix,-1,1);

// printf("%f  %f %f %f w =  %d h =  %d\n" ,-1*MarginL*ChartW_Pix, startMaxX + MarginR*ChartW_Pix, startMinY - MarginB*ChartH_Pix, startMaxY + MarginT*ChartH_Pix, width(), height());

 //glOrtho(0,1024,-32767,32767,-1,1);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();

// printf("resizeGL\n");

}

void ChartGL::DrawGridGL()
{
//Текущие настройки графика
 GLSettings settings = ZoomStack[CurZoom];
 float label;
 float mas_label[settings.NumYTicks+1];
 double  sdvig_x=0, sdvig_y=0;
 unsigned int max_len=0;
 QFontMetrics fm(font_axis);

 glLineWidth(1);

//Прорисовываем координатные линии по оси X
 for (int i = 0; i <= settings.NumXTicks; ++i)
 {
//Координата текущей линии
  mas_X_axis[i] = (( settings.MinX +  (float)i * (settings.MaxX - settings.MinX) / (float)settings.NumXTicks));

//Метка текущей линии
  label = (settings.MinX + ((float)i * settings.SpanX() / (float)settings.NumXTicks));
//Округляем до 3-х знаков после запятой чтобы не лезли слишком большие остатки

  sdvig_x = 1.2*(float)(QString("%1").arg(label,0,'f',3).length())*ChartW_Pix;

//  label = (int)(label*1000.0) / 1000.0;
//  sdvig=4.0*calc_num_digits(label)*ChartW_Pix;

 if(i%Rezh==0) renderText(this, mas_X_axis[i]-sdvig_x, settings.MinY - 0.35*(float)MarginB*ChartH_Pix, QString::number(label), TextAxisColor, font_axis, Qt::AlignHCenter | Qt::AlignTop);

  //printf("os = %f = text %f\n", mas_X_axis[i], mas_X_axis[i]-sdvig);
 }


//Прорисовываем координатные линии по оси Y
 for (int i = 0; i <= settings.NumYTicks; ++i)
 {
//Координата текущей линии
  mas_Y_axis[i] = (settings.MinY + ((float)i * (settings.MaxY - settings.MinY) / (float)settings.NumYTicks));

//Метка текущей линии
//  label = (settings.MinY + ((float)i * settings.SpanY() / settings.NumYTicks));
//Округляем до 3-х знаков после запятой чтобы не лезли слишком большие остатки
//  label = (int)(label*1000.0) / 1000.0;

//Метка текущей линии
  mas_label[i] = (settings.MinY + ((float)i * settings.SpanY() / settings.NumYTicks));
//Округляем до 3-х знаков после запятой чтобы не лезли слишком большие остатки
  mas_label[i] = (int)(mas_label[i]*1000.0) / 1000.0;



  if(QString("%1").arg(mas_label[i],0,'f',3).length()>max_len) max_len=QString("%1").arg(mas_label[i],0,'f',3).length();

////////////  renderText(this, settings.MinX - 0.8*(float)MarginL*ChartW_Pix, mas_Y_axis[i] - 4*ChartH_Pix, QString::number(label), TextAxisColor, f, AlignRight | AlignVCenter);

 }

 for (int i = 0; i <= settings.NumYTicks; ++i)
 {

  sdvig_y = (double)(max_len-QString("%1").arg(mas_label[i],0,'f',3).length())*ChartW_Pix*(double)fm.width('0');

  if(i%Rezh==0) renderText(this, settings.MinX - 0.85*(float)MarginL*ChartW_Pix + sdvig_y, mas_Y_axis[i] - 4*ChartH_Pix, QString::number(mas_label[i]), TextAxisColor, font_axis, Qt::AlignRight | Qt::AlignVCenter);

 }

 DrawRamka();

 // printf("DrawGridGL \n");

}

void ChartGL::DrawRamka()
{
//Текущие настройки графика
 GLSettings settings = ZoomStack[CurZoom];

 glEnable(GL_LINE_SMOOTH);

 qglColor(AxisColor);
// glColor3f(1.0,1.0,1.0);

 glBegin(GL_LINE_LOOP);
// glVertex2f(settings.MinX-0.1/ChartW_Pix, settings.MaxY+.1/ChartH_Pix);
// glVertex2f(settings.MaxX+0.1/ChartW_Pix, settings.MaxY+.1/ChartH_Pix);
// glVertex2f(settings.MaxX+0.1/ChartW_Pix, settings.MinY-.1/ChartH_Pix);
// glVertex2f(settings.MinX-0.1/ChartW_Pix, settings.MinY-.1/ChartH_Pix);
 glVertex2f(settings.MinX, settings.MaxY);
 glVertex2f(settings.MaxX, settings.MaxY);
 glVertex2f(settings.MaxX, settings.MinY);
 glVertex2f(settings.MinX, settings.MinY);
 glEnd();

 glDisable(GL_LINE_SMOOTH);

 // printf("Draw Ramka\n");
}

void ChartGL::DrawInsideAxisGL()
{
//Текущие настройки графика
 GLSettings settings = ZoomStack[CurZoom];

 glLineWidth(1);

 glEnable(GL_LINE_STIPPLE);
 GLint l=0xf0f0;
 glLineStipple(1,l);
 qglColor(LineStippleColor);

//Прорисовываем координатные линии по оси X
 for (int i = 0; i < settings.NumXTicks; ++i)
 {
//Рисуем текущуу линии
 if(i!=0)
 {
  glBegin(GL_LINE_STRIP);
  glVertex2f(mas_X_axis[i], settings.MaxY);
  glVertex2f(mas_X_axis[i], settings.MinY);
  glEnd();
 }
 }

//Прорисовываем координатные линии по оси Y
 for (int i = 0; i < settings.NumYTicks; ++i)
 {
//Рисуем текущуу линии
 if(i!=0)
 {
  glBegin(GL_LINE_STRIP);
  glVertex2f(settings.MinX, mas_Y_axis[i]);
  glVertex2f(settings.MaxX, mas_Y_axis[i]);
  glEnd();
 }
 }

 glDisable(GL_LINE_STIPPLE);

// DrawRamka();

 // printf("DrawInsideAxisGL \n");
}

void ChartGL::DrawSeriesGL_TrackSelection(int Track_num)
{
 if(Series.size()<1) return;

 qglColor(SelectionTrackColor);
 glEnable(GL_LINE_SMOOTH);
 glEnable(GL_POINT_SMOOTH);
 glLineWidth(LineWidth);
 glPointSize(PointSize);

 const SeriesPoints &data = Series[Track_num];

 int maxPoints = data.size();


 glBegin(GL_LINE_STRIP);
  for (int i = 0; i <maxPoints; ++i)
  {
   glVertex2f(data[i].GetX(), data[i].GetY());
  }
 glEnd();

 if(Point)
   {
    glBegin(GL_POINTS);
     for (int i = 0; i <maxPoints; ++i)
       {
        glVertex2f(data[i].GetX(), data[i].GetY());
        //printf("DrawSeriesGL_Track x %f y %f GL %x \n",data[i].GetX(), data[i].GetY(), this);
       }
    glEnd();
   }

// printf("DrawSeriesGL_Track x %f y %f GL %x \n",data[0].GetX(), data[0].GetY(), this);

 glDisable(GL_LINE_SMOOTH);
 glDisable(GL_POINT_SMOOTH);

// updateGL();

// printf("DrawSeriesGL_TrackSelection \n");
}

void ChartGL::DrawSeriesGL_TrackPoint(int Track_num, int Point_num)
{
 if(Series.size()<1) return;

 glEnable(GL_POINT_SMOOTH);
 glPointSize(PointSize);
 qglColor(SelectionPointColor);

// map<int, SeriesPoints>::const_iterator it = Series[Track_num];

 const SeriesPoints &data = Series[Track_num];

 if(Point)
   {
    glBegin(GL_POINTS);
    glVertex2f(data[Point_num].GetX(), data[Point_num].GetY());
    glEnd();
   }

 glDisable(GL_POINT_SMOOTH);

// updateGL();

 // printf("DrawSeriesGL_TrackPoint \n");

}

void ChartGL::DrawSeriesGL_Track()
{
// GLSettings settings = ZoomStack[CurZoom];

 std::map<int, SeriesPoints>::const_iterator it = Series.begin();

 if(Series.size()<1) return;

 glEnable(GL_LINE_SMOOTH);
 glEnable(GL_POINT_SMOOTH);
 glLineWidth(LineWidth);
 glPointSize(PointSize);

while (it != Series.end())
{
 const SeriesPoints &data = (*it).second;

 int maxPoints = data.size();

 //qglColor(TrackColor);
 qglColor(data[0].GetColor());

 glBegin(GL_LINE_STRIP);
  for (int i = 0; i <maxPoints; ++i)
  {
   glVertex2f(data[i].GetX(), data[i].GetY());
  }
 glEnd();

 if(Point)
 {
    qglColor(data[0].GetColor());
    glBegin(GL_POINTS);
     for (int i = 0; i <maxPoints; ++i)
       {
        glVertex2f(data[i].GetX(), data[i].GetY());
        //printf("DrawSeriesGL_Track x %f y %f \n",in_chartGL(data[i].GetX(), "X" ),in_chartGL(data[i].GetX(), "Y" ));
       }
    glEnd();
   }

++it;
}

 glDisable(GL_LINE_SMOOTH);
 glDisable(GL_POINT_SMOOTH);

 // printf("DrawSeriesGL_Track \n");
}

void ChartGL::DrawSeriesGL_Osc()
{
 GLSettings settings = ZoomStack[CurZoom];

 int start_point=(int)settings.MinX, end_point=(int)settings.MaxX;

 std::map<int, SeriesPoints>::const_iterator iter = Series.begin();

 if(Series.size()<1) return;

while (iter != Series.end())
{
 //printf("draw series number %d   \n", (*it).first);
 const SeriesPoints &data = (*iter).second;

 int maxPoints = data.size();

 if(end_point>=maxPoints) end_point=maxPoints;

// glEnable(GL_LINE_SMOOTH);
 glLineWidth(LineWidth);
 glBegin(GL_LINE_STRIP);
 qglColor(data[0].GetColor());

  for (int i = start_point; i < end_point; ++i)
  {
   glVertex2f(i, in_chartGL(data[i].GetY(), "Y" ));
  }

 glEnd();
// glDisable(GL_LINE_SMOOTH);

++iter;
}

 // printf("DrawSeriesGL_Osc \n");
}

void ChartGL::RefreshSeriesGL()
{
// RefreshGridGL();

 glEnable(GL_SCISSOR_TEST);
 glScissor(MarginL, MarginB, width() - MarginL - MarginR, height() - MarginT - MarginB);

 // printf("RefreshSeriesGL %d %d %x %d %d %d %d\n", width(), height(), this, MarginL, MarginB, MarginR, MarginT);


 glClear(GL_COLOR_BUFFER_BIT);

 DrawInsideAxisGL();

 if(ICO) DrawICO();

 if(Oscill) DrawSeriesGL_Osc();
 else
   {
    DrawSeriesGL_Track();
    if(Series.size()>0)
      {
       if(Track_Selection) DrawSeriesGL_TrackSelection(0);
       if(Point_Selection) DrawSeriesGL_TrackPoint(0,NPoint-1);
      }
   }

 if (ZoomIsShown)
 {
  DrawZoomRect();
 }

 glDisable(GL_SCISSOR_TEST);

// updateGL();

 // printf("RefreshSeriesGL \n");

}

void ChartGL::RefreshGridGL()
{
 glClear(GL_COLOR_BUFFER_BIT);
 //chartGL->resizeGL(1124,540);
 DrawGridGL();

 // printf("RefreshGridGL \n");
}

/***************************************************************************************************/
//Обработчик нажатия кнопки мыши
void ChartGL::mousePressEvent(QMouseEvent *event)
{

//Если нажали левую кнопку мыши
 if (event->button() == Qt::LeftButton)
 {
//Текущие настройки графика
  GLSettings settings = ZoomStack[CurZoom];

//Область выделения видима
  ZoomIsShown = true;
  RectZoom[0][0] = RectZoom[1][0] = settings.MinX + (event->pos().x()-MarginL)*ChartW_Pix;
  RectZoom[0][1] = RectZoom[1][1] = settings.MaxY - (event->pos().y()-MarginT)*ChartH_Pix;
//  printf("X = %d  Y = %d  %f   %f  \n", event->pos().x(), event->pos().y(), RectZoom[1][0], RectZoom[1][1]);

//Меняем курсор
  setCursor(Qt::CrossCursor);

  // printf("mousePressEvent \n");
 }


}
/***************************************************************************************************/
//Обработчик движения мыши
void ChartGL::mouseMoveEvent(QMouseEvent *event)
{
//Если левая кнопка нажата
 if (event->buttons() & Qt::LeftButton)
 {
//Текущие настройки графика
  GLSettings settings = ZoomStack[CurZoom];

  RectZoom[1][0] = settings.MinX + (event->pos().x()-MarginL)*ChartW_Pix;
  RectZoom[1][1] = settings.MaxY - (event->pos().y()-MarginT)*ChartH_Pix;

  if(ShowZoomUpdate) updateGL();

  //printf("X = %d  Y = %d  %f   %f  \n", event->pos().x(), event->pos().y(), RectZoom[1][0], RectZoom[1][1]);

//   printf("mouseMoveEvent \n");
 }


}
/***************************************************************************************************/
//Обработчик отжатия кнопки мыши
void ChartGL::mouseReleaseEvent(QMouseEvent *event)
{

//Если отжата левая кнопка
 if (event->button() == Qt::LeftButton)
 {
//Рамка невидима
  ZoomIsShown = false;

//Возвращаем курсор
  setCursor(Qt::ArrowCursor);

  RectZoomW = fabs(RectZoom[0][0]-RectZoom[1][0]);
  RectZoomH = fabs(RectZoom[0][1]-RectZoom[1][1]);

//Если выделяли справа налево
 if(RectZoom[1][0]<=RectZoom[0][0])
  {
   // printf("rel 1\n");
   ChangeFirst();
  }
//Если выделяли слевa направо
//  if(event->x()>=rint(RectZoom[0][0]/ChartW_Pix))
 else
  {
   if(RectZoom[1][1]>RectZoom[0][1])
    {
     ChangeLast();
     return;
    }

//Проверка слишком сильное увеличение
  if ( (RectZoomW < 0.01) || (RectZoomH < 0.01) )
   {
     printf("Kuda dalshe zoommat' %f   %f   \n", RectZoomW, RectZoomH);
    ChangeLast();
    return;
   }


//Проверка мизерное выделение
  if ( ((RectZoomW/ChartW_Pix) < 4.0) || ((RectZoomH/ChartH_Pix) < 4.0 ))
   {
     printf("MizeRRRRRRR  v pixelax %f   %f   \n", RectZoomW/ChartW_Pix, RectZoomH/ChartH_Pix);
    ChangeLast();
    return;
   }

//Текущие параметра графика
   GLSettings settings;

//   printf("prev %f %f %f %f %f %f \n",prevSettings.MinX, prevSettings.MaxX, prevSettings.MinY, prevSettings.MaxY, prevSettings.SpanX(),prevSettings.SpanY());

//расчитываем новые параметры графика
   settings.MinX = RectZoom[0][0];
   settings.MaxX = RectZoom[1][0];
   settings.MinY = RectZoom[1][1];
   settings.MaxY = RectZoom[0][1];
   settings.NumXTicks = StartNumXTicks;
   settings.NumYTicks = StartNumYTicks;

//   printf("new %f %f %f %f %f %f \n",settings.MinX, settings.MaxX, settings.MinY, settings.MaxY, settings.SpanX(),settings.SpanY());

//Применяем их
   settings.Adjust();
//Увеличиваем стек
   ZoomStack.resize(CurZoom + 1);
//Помещаем в него новые параметры
   ZoomStack.push_back(settings);
//Увеличиваем изображение
   ChangeNext();
   // printf("rel 3\n");


  }
    // printf("mouseReleaseEvent\n");
 }


// DrawRamka();

 updateGL();

}
/***************************************************************************************************/
void ChartGL::DrawZoomRect()
{
// RectZoom[1][0] = Xr;
// RectZoom[1][1] = Yr;

 glLineWidth(0.5);
// glEnable(GL_LINE_SMOOTH);


// glColor3f(1.0,1.0,1.0);
 qglColor(AxisColor);

 glBegin(GL_LINE_LOOP);
 glVertex2fv(RectZoom[0]);
 glVertex2f (RectZoom[1][0],RectZoom[0][1]);
 glVertex2fv(RectZoom[1]);
 glVertex2f (RectZoom[0][0],RectZoom[1][1]);
 glEnd();

// glDisable(GL_LINE_SMOOTH);

// updateGL();
// printf("DrawZoomRect\n");
}
/***************************************************************************************************/
//Ф-я установки настроек графика
void ChartGL::SetGLSettings (const GLSettings &settings)
{
//Заносим текущее состояние плотера в стек
 ZoomStack.resize(1);
 ZoomStack[0]=settings;
 CurZoom=0;

 // printf("SetGLSettings\n");
}
/***************************************************************************************************/
//Начальные настройки графика
GLSettings::GLSettings()
{
/*
 MinX = 0.0;
 MaxX = 1024.0;
 NumXTicks = 16;
 MinY = -32767.0;
 MaxY = 32767.0;
 NumYTicks = 16;
*/
}

/***************************************************************************************************/
//Ф-я сдвига на заданное кол-во шагов
void GLSettings::scroll(int dx, int dy)
{
 double stepX = SpanX() / NumXTicks;
 MinX += dx * stepX;
 MaxX += dx * stepX;
 double stepY = SpanY() / NumYTicks;
 MinY += dy * stepY;
 MaxY += dy * stepY;
 // printf("scroll\n");
}
/***************************************************************************************************/
//Ф-я перерасчета параметров осей плотера
void GLSettings::Adjust()
{
 AdjustAxis(MinX, MaxX, NumXTicks);
 AdjustAxis(MinY, MaxY, NumYTicks);
 // printf("Adjust\n");
}
/***************************************************************************************************/
//Ф-я округления minX, maxX, minY и maxY до "наилучших" и определяет значения рисок на осях
void GLSettings::AdjustAxis(double &min, double &max,int &numTicks)
{
//"наилучшими" будут значения 10^n, 2*10^n или 5*10^n
 int MinTicks = numTicks;                        //минимальное кол-во меток
 if(MinTicks<2)
  MinTicks=5;
 double grossStep = (max - min) / MinTicks;     //максимальный шаг

 double step = pow(10, floor(log10(grossStep)));//шаг в виде 10^n

 if (5 * step < grossStep)
  step *= 5;                    //шаг в виде 5*10^n
 else if (2 * step < grossStep)
  step *= 2;                    //шаг в виде 2*10^n

 numTicks = (int)rint(ceil(max / step) - floor(min / step));//"наилучшее" кол-во рисок
 min = floor(min / step) * step;//"наилучшее" зн-е min
 max = ceil(max / step) * step; //"наилучшее" зн-е max

 //printf("AdjustAxis\n");
}
/***************************************************************************************************/
void ChartGL::renderText( QGLWidget* , double x, double y, const QString& text, QColor col, QFont font, int )
{
//Текущие настройки графика
  GLSettings settings = ZoomStack[CurZoom];

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
//    glOrtho( 0, w->width(), w->height(), 0, 0, 1 );
//    glOrtho(0,startMaxX,startMinY,startMaxY,-1,1);
    glOrtho(settings.MinX - MarginL*ChartW_Pix,settings.MaxX + MarginR*ChartW_Pix, settings.MinY - MarginB*ChartH_Pix, settings.MaxY + MarginT*ChartH_Pix,-1,1);

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();


  QFontMetrics fm(font);
//  printf("%d \n", fm.width(text));

  QRect rect;// = QRect(x,y,100,100);
  rect = fm.boundingRect( text);
  //rect = fm.boundingRect( x, y, fm.width(text), fm.height(), AlignRight | AlignVCenter, text );

//  printf("%d \n", rect.width());

  QPixmap pixmap( rect.size() );
//  pixmap.fill( Qt::white );
  pixmap.fill( Qt::black );
  QPainter painter(&pixmap);
  painter.setPen( Qt::white );
//  painter.setPen( Qt::black );
  painter.setFont( font );
  //rect.setWidth(30);
  painter.drawText( -rect.left(), -rect.top(), text);

//  painter.drawText(-rect.left(), -rect.top(), rect.width(), rect.height(), AlignRight | AlignVCenter, text);

//  printf("%d %d %d %d \n",-rect.left(), -rect.top(), rect.width(), rect.height());

  QImage img = pixmap.toImage();

  img.setAlphaChannel(img);
  for ( int i = 0; i < img.height(); i++ ) {
  QRgb* rgb = (QRgb*) img.scanLine(i);
  for ( int j = 0; j < img.width(); j++ ) {
      rgb[j] = qRgba( col.red(), col.green(), col.blue(), qRed(rgb[j]) );
    }
  }
  img = QGLWidget::convertToGLFormat(img);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glRasterPos2f( x, y );
  glDrawPixels( rect.width(), rect.height(), GL_RGBA, GL_UNSIGNED_BYTE, img.bits() );
  glDisable(GL_BLEND);
  glMatrixMode( GL_PROJECTION );
  glPopMatrix();
  glMatrixMode( GL_MODELVIEW );
  glPopMatrix();

//     printf("renderText\n");
}
/***************************************************************************************************/
void ChartGL::SetStart()
{
 GLSettings settings;
 settings.MinX = StartMinX;
 settings.MaxX = StartMaxX;
 settings.NumXTicks = StartNumXTicks;
 settings.MinY = StartMinY;
 settings.MaxY = StartMaxY;
 settings.NumYTicks = StartNumYTicks;
 settings.Adjust();
 SetGLSettings(settings);
 resizeGL(width(),height());
// RefreshGridGL();
// RefreshSeriesGL();
 // printf("SetStart\n");
}
void ChartGL::SetStartMinX(int startMinX)
{
 StartMinX = startMinX;
// SetStart();
}
void ChartGL::SetStartMinY(int startMinY)
{
 StartMinY = startMinY;
// SetStart();
}
void ChartGL::SetStartMaxX(int startMaxX)
{
 StartMaxX = startMaxX;
// SetStart();
}
void ChartGL::SetStartMaxY(int startMaxY)
{
 StartMaxY = startMaxY;
// SetStart();
}

void ChartGL::SetStartNumXTicks(int startNumXTicks)
{
 StartNumXTicks = startNumXTicks;
 if(StartNumXTicks>100) StartNumXTicks=100;
// SetStart();
      // printf("SetStartNumYTicks\n");
}
void ChartGL::SetStartNumYTicks(int startNumYTicks)
{
 StartNumYTicks = startNumYTicks;
 if(StartNumYTicks>100) StartNumYTicks=100;
// SetStart();
      // printf("SetStartNumYTicks\n");
}
/***************************************************************************************************/
void ChartGL::ChangeNext()
{
 if(CurZoom<(int)rint(ZoomStack.size())-1)
 {
  ++CurZoom;
  resizeGL(width(),height());
 }
// RefreshGridGL();
// RefreshSeriesGL();
// DrawRamka();
 updateGL();

 // printf("ChangeNext\n");
}
/***************************************************************************************************/

void ChartGL::ChangePrev()
{
 if(CurZoom>0)
 {
  --CurZoom;
  resizeGL(width(),height());
 }
// RefreshGridGL();
// RefreshSeriesGL();
 updateGL();

 // printf("ChangePrev %d %d %x\n", width(), height(), this);
}
/***************************************************************************************************/

void ChartGL::ChangeFirst()
{
 CurZoom=1;
 ChangePrev();
       // printf("ChangeFirst\n");
}
/***************************************************************************************************/

void ChartGL::ChangeLast()
{
 CurZoom=(int)rint(ZoomStack.size())-2;
 ChangeNext();

        // printf("ChangeLast\n");
}
/***************************************************************************************************/
double ChartGL::in_chartGL(double num, const QString axis)
{
 GLSettings settings = ZoomStack[CurZoom];

 if(axis=="X"||axis=="x")
   {
    if(num>=settings.MaxX) return settings.MaxX;
    else if(num<=settings.MinX) return settings.MinX;
    else return num;
   }
 else if (axis=="Y"||axis=="y")
   {
    if(num>=settings.MaxY) return settings.MaxY;
    else if(num<=settings.MinY) return settings.MinY;
    else return num;
   }
 else return num;
}
/***************************************************************************************************/
void ChartGL::DrawICO()
{
 double x1,y1,x2, y2, tmp;

//Текущие настройки графика
// GLSettings settings = ZoomStack[CurZoom];

 glEnable(GL_LINE_SMOOTH);

 glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
 glEnable(GL_BLEND);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

 glLineWidth(1);

 qglColor(ICOColor);

 for (int j = 0; j < 8; j++)
 {

//  printf("j = %d  (%f , %f) (%f , %f) \n", j, dx1,dy1, dx2,dy2);

  if(j!=0||j!=4)
   {
    x1 = StartMaxX*sin(j*M_PI/8.);
    y1 = StartMaxY*cos(j*M_PI/8.);
    x2 = StartMinX*sin(j*M_PI/8.);
    y2 = StartMinY*cos(j*M_PI/8.);

    glBegin(GL_LINE_STRIP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
   }
 }

 qglColor(ICOColorMain);

 glBegin(GL_LINE_STRIP);
 glVertex2f(0, StartMaxY);
 glVertex2f(0, StartMinY);
 glEnd();

 glBegin(GL_LINE_STRIP);
 glVertex2f(StartMinX,0);
 glVertex2f(StartMaxX,0);
 glEnd();

// qglColor(ICOColorMain);
 glLineWidth(1);

 glBegin(GL_LINE_LOOP);
 for (int j = 0; j < 100; j++)
 {
  tmp = (float)j*2.0*M_PI/100.0;

  glVertex2f(StartMaxX*cos(tmp), StartMaxY*sin(tmp));
 }
 glEnd();

 glDisable(GL_LINE_SMOOTH);

 // printf("DrawICO\n");
}
/***************************************************************************************************/
int ChartGL::calc_num_digits(double num)
{
 int num_d=1;

 double tmp=(int)num;

 while(tmp>=1)
  {
   if((tmp*0.1)>=1)
      num_d++;
   if(num_d>15) return 15;
   tmp=tmp*0.1;
  }

if((tmp=(num-(int)num))>0) num_d++;

 while((tmp-(int)(tmp+0.5))>0.000001)
  {
   if((tmp*10.0-(int)(tmp*10.0+0.5))>0.000001)
     {
      //printf("rez %f %d %f %f \n", tmp*10.0, (int)(tmp*10.0+0.5), ( tmp*10.0 -    (int)(tmp*10.0+0.5) ),  (tmp-(int)(tmp+0.5)));
      num_d++;
     }
   if(num_d>15) return 15;
   tmp=tmp*10.0;
   //usleep(1000000);
  }



 return num_d;
}
/***************************************************************************************************/
void ChartGL::SetRezh(int num)
{
 if(num > 10) Rezh=10;
 if(num < 1) Rezh=1;
 Rezh=num;
}

