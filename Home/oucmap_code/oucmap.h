

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
	void addSeries(QVector<QPointF> * vector);                //�ı�·��
	void handleClickedPoint(const QPointF &point);            //���ɢ��ͼ������
	void handleTimeOut();                                     //��ʱ������, ��ʱ��������ʧ
	void handleHoveredPoint(const QPointF &point);            //�����ͣɢ�㴦����, ��ͣ��ʾɢ����Ϣ
	void changeTxt(const QString & s);                        //�ı�label�е�����
															  //void handleDoubleClickedPoint(const QPointF &point);      //

};
#endif // !OUCMAP_H
