#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtGui/QScreen>
#include <QtGui/QFont>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtCore/QString>
#include "ui_Watermarker.h"

class Watermarker : public QMainWindow
{
    Q_OBJECT

public:
    Watermarker(QWidget *parent = nullptr);
	// 水印构造函数
    Watermarker(QString text, 
		QFont font,
		int angle, 
		float opacity, 
		int spacing, 
		QColor color,
		QWidget *parent = nullptr):
			m_text(text),
			m_font(font), 
			m_angle(angle),
			m_opacity(opacity), 
			m_spacing(spacing), 
			m_color(color), QMainWindow(parent)
		
	{
		ui.setupUi(this);

		this->setAttribute(Qt::WidgetAttribute::WA_TranslucentBackground);
		this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
		auto& rc = QApplication::desktop()->screenGeometry();
		this->setGeometry(rc);
		this->setAttribute(Qt::WA_NoSystemBackground, true);
		this->setAttribute(Qt::WA_TransparentForMouseEvents, true);

	}

	// 需要重载的绘制函数（关键处理点）
	void paintEvent(QPaintEvent* event) override 
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::RenderHint::Antialiasing);

		painter.setFont(m_font);
		painter.setPen(m_color);

		int nTextWidth = painter.fontMetrics().width(m_text);
		int nTextHeight = painter.fontMetrics().height();
		auto& rc = QApplication::desktop()->screenGeometry();
		auto nScreenWidth = rc.width();
		auto nScreenHeight = rc.height();

		int x = -nScreenWidth;
		while (x < 2 * nScreenWidth)
		{
			int y = -nTextHeight;
			while (y < 2 * nScreenHeight) 
			{
				painter.save();
				painter.translate(x + nTextWidth / 2, y + nTextHeight / 2);
				painter.rotate(m_angle);
				painter.drawText(-nTextWidth / 2, nTextHeight / 4, m_text);
				painter.restore();
				y += nTextHeight + m_spacing;
			}
			x += nTextWidth + m_spacing;
		}

		update();
	}

    ~Watermarker();

private:
    Ui::WatermarkerClass ui;

	QString m_text;
	QFont m_font;
	int m_angle; 
	float m_opacity; 
	int m_spacing; 
	QColor m_color;
};
