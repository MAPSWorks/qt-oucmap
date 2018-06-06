

#ifndef OUCMAP_H
#define OUCMAP_H

#include <QtWidgets>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChartGlobal>
#include <QtWidgets/QDialog>
#include <qqueue.h>
#include <QtWidgets/QGridLayout>
#include "ui_oucmap.h"


class oucmap : public QWidget {
	Q_OBJECT

public:
	Ui::oucmapClass ui;
	QGridLayout * mainLayout;
	QLabel * myLabel;

	oucmap(QWidget *parent = Q_NULLPTR);
	void setLayout1();
	void addSeries(QVector<QPointF> * vector);                //改变路径
	void handleClickedPoint(const QPointF &point);            //点击散点图处理函数
	void handleTimeOut();                                     //超时处理函数, 超时后折线消失
	void handleHoveredPoint(const QPointF &point);            //鼠标悬停散点处理函数, 悬停显示散点信息
	void changeTxt(const QString & s);                        //改变label中的内容
															  //void handleDoubleClickedPoint(const QPointF &point);      //

};
#endif // !OUCMAP_H
