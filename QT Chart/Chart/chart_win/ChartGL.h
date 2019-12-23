/***************************************************************************
                          ChartGL.h  -  description
                             -------------------
    begin                : 18 07 2012
    copyright            : (C) 2012 by Alexander Pukh
 ***************************************************************************/
#ifndef CHARTGL_H
#define CHARTGL_H

#include <map>
#include <vector>

//#include <qgl.h>
#include <GL/glu.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qwidget.h>
#include <QtOpenGL/QGLWidget>
#include <QMouseEvent>

class TSeriesPoints;
class GLSettings;

//Точка серии
typedef std::vector<TSeriesPoints> SeriesPoints;

class ChartGL : public QGLWidget
{
  Q_OBJECT
 Q_PROPERTY( bool ico READ GetICO WRITE SetICO )
 Q_PROPERTY( bool point READ GetPoint WRITE SetPoint )
 Q_PROPERTY( bool line READ GetLine WRITE SetLine )
 Q_PROPERTY( bool square READ GetSquare WRITE SetSquare )

 Q_PROPERTY( int pointSize READ GetPointSize WRITE SetPointSize )
 Q_PROPERTY( int lineWidth READ GetLineWidth WRITE SetLineWidth )

  Q_PROPERTY( int marginL READ GetMarginL WRITE SetMarginL )
  Q_PROPERTY( int marginR READ GetMarginR WRITE SetMarginR )
  Q_PROPERTY( int marginT READ GetMarginT WRITE SetMarginT )
  Q_PROPERTY( int marginB READ GetMarginB WRITE SetMarginB )

  Q_PROPERTY( int startMinX READ GetStartMinX WRITE SetStartMinX )
  Q_PROPERTY( int startMinY READ GetStartMinY WRITE SetStartMinY )
  Q_PROPERTY( int startMaxX READ GetStartMaxX WRITE SetStartMaxX )
  Q_PROPERTY( int startMaxY READ GetStartMaxY WRITE SetStartMaxY )
  Q_PROPERTY( int startNumXTicks READ GetStartNumXTicks WRITE SetStartNumXTicks )
  Q_PROPERTY( int startNumYTicks READ GetStartNumYTicks WRITE SetStartNumYTicks )

  public:
  ChartGL(QWidget* parent = 0);
  ~ChartGL();

  float ChartW_Pix, ChartH_Pix;
  QColor BackgroundColor;
  QColor TextAxisColor;
  QColor AxisColor;
  QColor LineStippleColor;
  QColor ICOColorMain;
  QColor ICOColor;
  QColor SelectionPointColor;
  QColor SelectionTrackColor;
  QColor TrackColor;

  int MarginL;
  int MarginT;
  int MarginR;
  int MarginB;

  int StartMinX;       //минимальная координата по Х
  int StartMaxX;       //максимальная координата по Х
  int StartNumXTicks;  //чило отметок на оси Х
  int StartMinY;       //минимальная координата по Y
  int StartMaxY;       //максимальная координата по Y
  int StartNumYTicks;  //чило отметок на оси Y

  QFont font_axis;

  bool ICO;
  bool Oscill;
  bool Point;
  int PointSize;
  bool Line;
  int LineWidth;
  bool Square;
  int ShowZoomUpdate;
  int Rezh;

  int NPoint;
  bool Track_Selection;
  bool Point_Selection;


  float mas_X_axis[100],mas_Y_axis[100];

//Словарь точек серий
  std::map<int, SeriesPoints> Series;
//Стек действий пользователя
  std::vector<GLSettings> ZoomStack;
//Номер текущего элемента в стеке изменений пользователя
  int CurZoom;


//Флаг видимости границы выделения
  bool ZoomIsShown;
  GLfloat RectZoom[2][2];
  float RectZoomW,RectZoomH;

  int calc_digits(int num) { return (num/=10 ) ? ( 1 + calc_digits(num) ) : (1);};

  bool GetICO() const { return ICO; }
  void SetICO(bool ico) { ICO = ico; }

  bool GetPoint() const { return Point; }
  void SetPoint(bool point) { Point = point; }
  bool GetLine() const { return Line; }
  void SetLine(bool line) { Line = line; }
  int GetPointSize() const { return PointSize; }
  void SetPointSize(int pointsize) { PointSize = pointsize; }
  int GetLineWidth() const { return LineWidth; }
  void SetLineWidth(int linewidth) { LineWidth = linewidth; }
  bool GetSquare() const { return Square; }
  void SetSquare(bool sq) { Square = sq; }


  int GetMarginL() const { return MarginL; }
  void SetMarginL(int marginL) { MarginL = marginL; }
  int GetMarginR() const { return MarginR; }
  void SetMarginR(int marginR) { MarginR = marginR; }
  int GetMarginT() const { return MarginT; }
  void SetMarginT(int marginT) { MarginT = marginT; }
  int GetMarginB() const { return MarginB; }
  void SetMarginB(int marginB) { MarginB = marginB; }

  void SetStart();

  int GetStartMinX() const { return StartMinX; }
  void SetStartMinX(int startMinX);
  int GetStartMinY() const { return StartMinY; }
  void SetStartMinY(int startMinY);
  int GetStartMaxX() const { return StartMaxX; }
  void SetStartMaxX(int startMaxX);
  int GetStartMaxY() const { return StartMaxY; }
  void SetStartMaxY(int startMaxY);

  int GetStartNumXTicks() const { return StartNumXTicks; }
  void SetStartNumXTicks(int startNumXTicks);
  int GetStartNumYTicks() const { return StartNumYTicks; }
  void SetStartNumYTicks(int startNumYTicks);

  void SetRezh(int );

//Ф-я прорисовки zoom'a
  void DrawZoomRect();
//Ф-я прорисовки осей и сетки
  void DrawGridGL();
  void DrawInsideAxisGL();
  void DrawSeriesGL_Osc();
  void DrawSeriesGL_Track();
  void DrawRamka();
//Ф-я обновления копии изображения и экрана
  void RefreshSeriesGL();
  void RefreshGridGL();

  void DrawICO();


//Обработчик нажатия кнопки мыши
  void mousePressEvent(QMouseEvent *event);
//Обработчик движения мыши
  void mouseMoveEvent(QMouseEvent *event);
//Обработчик отжатия кнопки мыши
  void mouseReleaseEvent(QMouseEvent *event);
  void setBackgroundColor(QColor clr) { BackgroundColor = clr; } ;
//Ф-я установки настроек графика
  void SetGLSettings (const GLSettings &settings);

  void renderText( QGLWidget* w, double x, double y, const QString& text, QColor, QFont, int);

  double in_chartGL(double, const QString);

  int calc_num_digits(double);

  void DrawSeriesGL_TrackSelection(int);
  void DrawSeriesGL_TrackPoint(int,int);


  public slots:
   virtual void paintGL();
   virtual void initializeGL();
   virtual void resizeGL(int nWidth, int nHeight);

   void ChangeNext();
   void ChangePrev();
   void ChangeFirst();
   void ChangeLast();





};

//Настройки плотера
class GLSettings
{
 public:
  GLSettings();
//Ф-я сдвига на заданное кол-во шагов
  void scroll(int dx, int dy);
//Ф-я перерасчета параметров осей плотера
  void Adjust();
//Ф-я нахождения диапазона значений по оси Х
  double SpanX() const { return MaxX - MinX; };
//Ф-я нахождения диапазона значений по оси Y
  double SpanY() const { return MaxY - MinY; };

  double  MinX;   //минимальная координата по Х
  double  MaxX;   //максимальная координата по Х
  int NumXTicks;  //чило отметок на оси Х
  double  MinY;   //минимальная координата по Y
  double  MaxY;   //максимальная координата по Y
  int NumYTicks;  //чило отметок на оси Y

 private:
//Округление minX, maxX, minY и maxY до "наилучших" и определяет значения рисок на осях
  void AdjustAxis(double &min, double &max,int &numTicks);
};

//Точка серии
class TSeriesPoints
{
 public:
//  TSeriesPoint(double X= 0, double Y= 0);
 /* TSeriesPoints(double X = 0, double Y = 0, QColor Color=QColor(255,0,0))
  {
   x=X;
   y=Y;
   color=QColor(255,0,0);
  };
*/  TSeriesPoints(double X, double Y , QColor Color)
  {
   x=X;
   y=Y;
   color=Color;
  };

  double GetX() const { return x; }
  void SetX(double X) { x = X; }
  double GetY() const { return y; }
  void SetY(double Y) { y = Y; }
  QColor GetColor() const { return color; }
  void SetColor(QColor Color) { color = Color; }
  //QColor color;

private:
  double x;
  double y;
  QColor color;
};
#endif

