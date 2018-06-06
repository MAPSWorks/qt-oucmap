

#include "oucmap.h"
#include "dijkstra.h"
QT_CHARTS_USE_NAMESPACE


QLineSeries * series = new QLineSeries();
QScatterSeries * scatterSeries = new QScatterSeries();
QTimer * timer = new QTimer();


// ���봴��һ���ö���, �����ù��캯��, ��points �������
Dijkstra * dij = new Dijkstra();
//����������
extern QVector<QPointF> * points;
extern QVector<QPointF> * vec;
extern QVector<QString> * strings;
extern QString * s;

//�û�ѡ�еĵ�Ķ���, ʹ��ǰ��������һ��·��
QQueue<QPointF> * resvec = new QQueue<QPointF>();

oucmap::oucmap(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	mainLayout = new QGridLayout();
	myLabel = new QLabel();

	this->setLayout(mainLayout);
	connect(scatterSeries, &QScatterSeries::clicked, this, &oucmap::handleClickedPoint);
	connect(timer, &QTimer::timeout, this, &oucmap::handleTimeOut);
	connect(scatterSeries, &QScatterSeries::hovered, this, &oucmap::handleHoveredPoint);
	//connect(scatterSeries, &QScatterSeries::doubleClicked, this, &oucmap::handleDoubleClickedPoint);

}

void oucmap::setLayout1() {

	//����ɢ��ͼ
	scatterSeries->setPen(QPen(Qt::red, 1));
	scatterSeries->setColor(QColor(255, 0, 0));
	scatterSeries->setName("node");
	//�������
	for (int i = 0; i < 15; i++) {
		scatterSeries->append(points->at(i));
	}

	QChart * chart = new QChart();
	chart->addSeries(series);
	chart->addSeries(scatterSeries);

	chart->setTitle("ouc map");
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	chart->createDefaultAxes();                        //����Ĭ�ϵ�����ϵ����������ó��������в��˵�    
	chart->axisX()->setRange(0, 100);                  //����ͼ��������ķ�Χ�����Բ����ã��Զ����ڵ�    
	chart->axisY()->setRange(0, 100);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);  //�������Ⱦ   

	myLabel->setText("    test     ");
	myLabel->setStyleSheet("color: black");
	myLabel->setAlignment(Qt::AlignCenter);

	mainLayout->addWidget(chartView, 0, 0);
	mainLayout->addWidget(myLabel, 1, 0);
}

//�����Ǹı������ϵĵ�  
void oucmap::addSeries(QVector<QPointF> * vector) {
	srand((unsigned)time(NULL));
	series->setPen(QPen(Qt::blue, 1, Qt::SolidLine));    //���û���
	series->setColor(QColor(rand() % (100), rand() % (200 - 100), rand() % (255 - 100)));                 //������ɫ 
	series->setName("path");

	for (auto c : *vector) {
		series->append(c);
	}
}


//�����¼�, �����һ��, ��ΪԴ��, �ڶ��ε���ΪĿ�ĵص�
void oucmap::handleClickedPoint(const QPointF &point) {
	//���иĽ�, ��һ��������Ӧ�ô���һ������
	//����ĵ�
	QPointF clickedPoint = point;
	// �ҵ��Ǹ���
	QPointF closest(INT_MAX, INT_MAX);
	qreal distance(INT_MAX);
	const auto points1 = scatterSeries->points();
	for (const QPointF &currentPoint : points1) {
		qreal currentDistance = qSqrt((currentPoint.x() - clickedPoint.x())
			* (currentPoint.x() - clickedPoint.x())
			+ (currentPoint.y() - clickedPoint.y())
			* (currentPoint.y() - clickedPoint.y()));
		if (currentDistance < distance) {
			distance = currentDistance;
			closest = currentPoint;
		}
	}

	//���һЩ����..........................................................
	//ͨ�����, �ҿ������߼��������������
	resvec->append(closest);
	if (resvec->size() >= 2) {
		QPointF source = resvec->front();
		resvec->pop_front();
		QPointF vertex = resvec->front();
		resvec->pop_front();
		int i = 0;
		int j = 0;
		const auto points1 = scatterSeries->points();
		for (const QPointF &currentPoint : points1) {
			if (source == currentPoint) {
				break;
			}
			i++;
		}
		for (const QPointF &currentPoint : points1) {
			if (vertex == currentPoint) {
				break;
			}
			j++;
		}
		//�����Դ���Ŀ�ص�֮��, ���� dijkstra ���м���, ·���Ľ������� vec ��
		dij->computeSP(i, j);
		//�����·��֮��, ��ͼ����ʾ����
		addSeries(vec);
		//������� myLabel�е�����
		changeTxt(*s);


		//ͬʱ�ж�ͼ���Ƿ�������·��, ��ʱʹ����ֻ����һ��·��
		//������ʱ��, 5 ��֮��·����ʧ
		timer->start(5000);
	}
	//���"����", ����ʧ�Ĳ���
	//scatterSeries->remove(closest);
}

void oucmap::handleTimeOut() {
	for (auto c : *vec) {
		series->remove(c);
	}
}

void oucmap::handleHoveredPoint(const QPointF & point) {
	//����ĵ�
	QPointF clickedPoint = point;
	// �ҵ��Ǹ���
	QPointF closest(INT_MAX, INT_MAX);
	qreal distance(INT_MAX);
	const auto points1 = scatterSeries->points();
	for (const QPointF &currentPoint : points1) {
		qreal currentDistance = qSqrt((currentPoint.x() - clickedPoint.x())
			* (currentPoint.x() - clickedPoint.x())
			+ (currentPoint.y() - clickedPoint.y())
			* (currentPoint.y() - clickedPoint.y()));
		if (currentDistance < distance) {
			distance = currentDistance;
			closest = currentPoint;
		}
	}
	int i = 0;
	for (const QPointF &currentPoint : points1) {
		if (closest == currentPoint) {
			break;
		}
		i++;
	}
	//�õ���ͣ��֮��, ��label����ʾ��Ϣ
	changeTxt(strings->at(i));

}


void oucmap::changeTxt(const QString & s) {
	myLabel->setText(s);
}

//void oucmap::handleDoubleClickedPoint(const QPointF & point) {
//	//����ĵ�
//	QPointF clickedPoint = point;
//	// �ҵ��Ǹ���
//	QPointF closest(INT_MAX, INT_MAX);
//	qreal distance(INT_MAX);
//	const auto points1 = scatterSeries->points();
//	for (const QPointF &currentPoint : points1) {
//		qreal currentDistance = qSqrt((currentPoint.x() - clickedPoint.x())
//			* (currentPoint.x() - clickedPoint.x())
//			+ (currentPoint.y() - clickedPoint.y())
//			* (currentPoint.y() - clickedPoint.y()));
//		if (currentDistance < distance) {
//			distance = currentDistance;
//			closest = currentPoint;
//		}
//	}
//	int i = 0;
//	for (const QPointF &currentPoint : points1) {
//		if (closest == currentPoint) {
//			break;
//		}
//		i++;
//	}
//	//˫��һ��Դ���, �����Զ�����·��, һ��ѭ��
//	//��֤5��֮��, j++
//	for (n = 0; n < i; ) {
//		//�����Դ���Ŀ�ص�֮��, ���� dijkstra ���м���, ·���Ľ������� vec ��
//		dij->computeSP(i, n);
//		//�����·��֮��, ��ͼ����ʾ����
//		addSeries(vec);
//		//������� myLabel�е�����
//		changeTxt(*s);
//		//ͬʱ�ж�ͼ���Ƿ�������·��, ��ʱʹ����ֻ����һ��·��
//		//������ʱ��, 5 ��֮��·����ʧ
//		timer->start(5000);
//	}
//	/*for (int j = i; j < 15; j++) {
//		dij->computeSP(i, j);
//		addSeries(vec);
//		changeTxt(*s);
//		timer->start(5000);
//	}*/
//}