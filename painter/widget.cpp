#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QtMath>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    resize(600,300);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    int W=this->width();
    int H=this->height();

    int side=qMin(W,H);
    QRect rect((W-side)/2,(H-side)/2,side,side);
    painter.setViewport(rect);
    painter.setWindow(-100,-100,200,200);


//    QRect rect(0,0,W,H);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);
    QLinearGradient linearGrad(0,0,100,0);
    linearGrad.setColorAt(0,Qt::yellow);
    linearGrad.setColorAt(1,Qt::green);
    linearGrad.setSpread(QGradient::PadSpread);
    painter.setBrush(linearGrad);
//    painter.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
//    painter.setCompositionMode(QPainter::CompositionMode_Difference);
    painter.setCompositionMode(QPainter::CompositionMode_Exclusion);
    for(int i=0;i<36;i++)
    {
        painter.drawEllipse(QPoint(50,0),50,50);
        painter.rotate(10);
    }

//    QBrush brush;
//    QPixmap texturePixmap(":images/images/Chrysanthemum.jpg");
//    brush.setColor(Qt::yellow);
//    brush.setStyle(Qt::TexturePattern);
//    brush.setTexture(texturePixmap);
//    painter.setBrush(brush);

//    QRadialGradient radialGrad(W/2,H/2,qMax(W/8,H/8),W/2,H/2);
//    radialGrad.setColorAt(0,Qt::green);
//    radialGrad.setColorAt(1,Qt::blue);
//    radialGrad.setSpread(QGradient::PadSpread);
//    painter.setBrush(radialGrad);
//    painter.drawRect(this->rect());
//    qreal R=100;
//    const qreal Pi=3.14159;
//    qreal deg=Pi*72/180;
//    QPoint points[5]={
//        QPoint(R,0),
//        QPoint(R*std::cos(deg),-R*std::sin(deg)),
//        QPoint(R*std::cos(2*deg),-R*std::sin(2*deg)),
//        QPoint(R*std::cos(3*deg),-R*std::sin(3*deg)),
//        QPoint(R*std::cos(4*deg),-R*std::sin(4*deg)),
//    };

//    QFont font;
//    font.setPointSize(12);
//    font.setBold(true);
//    painter.setFont(font);

//    QPen penLine;
//    penLine.setWidth(2);
//    penLine.setColor(Qt::blue);
//    penLine.setStyle(Qt::SolidLine);
//    penLine.setCapStyle(Qt::FlatCap);
//    penLine.setJoinStyle(Qt::BevelJoin);
//    painter.setPen(penLine);

//    QBrush brush;
//    brush.setColor(Qt::yellow);
//    brush.setStyle(Qt::SolidPattern);
//    painter.setBrush(brush);

//    QPainterPath starPath;
//    starPath.moveTo(points[0]);
//    starPath.lineTo(points[2]);
//    starPath.lineTo(points[4]);
//    starPath.lineTo(points[1]);
//    starPath.lineTo(points[3]);
//    starPath.closeSubpath();
//    starPath.addText(points[0],font,"0");
//    starPath.addText(points[1],font,"1");
//    starPath.addText(points[2],font,"2");
//    starPath.addText(points[3],font,"3");
//    starPath.addText(points[4],font,"4");

//    painter.save();
//    painter.translate(100,120);
//    painter.drawPath(starPath);
//    painter.drawText(0,0,"S1");
//    painter.restore();

//    painter.translate(300,120);
//    painter.scale(0.8,0.8);
//    painter.rotate(90);
//    painter.drawPath(starPath);
//    painter.drawText(0,0,"S2");

//    painter.resetTransform();
//    painter.translate(500,120);
//    painter.rotate(-145);
//    painter.drawPath(starPath);
//    painter.drawText(0,0,"S3");

}