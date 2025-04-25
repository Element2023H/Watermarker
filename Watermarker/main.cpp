#include "Watermarker.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   

	QString strTxt( "Element WaterMark Test");
	QFont font("Courier New", 30);
	QColor color(255, 100, 100, 128);

	// 设置需要显示的水印内容
	Watermarker w(strTxt, font, 30, 0.4f, 200, color);
	//Watermarker w;
    w.show();
    return a.exec();
}
