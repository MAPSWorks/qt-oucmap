

#include "oucmap.h"
#include "dijkstra.h"
QT_CHARTS_USE_NAMESPACE


QLineSeries * series = new QLineSeries();
QScatterSeries * scatterSeries = new QScatterSeries();
QTimer * timer = new QTimer();


// 必须创建一个该对象, 来调用构造函数, 对points 进行填充
Dijkstra * dij = new Dijkstra();
//引用性声明
extern QVector<QPointF> * points;
extern QVector<QPointF> * vec;
extern QVector<QString> * strings;
extern QString * s;

//用户选中的点的队列, 使用前两个创造一条路径
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

	//绘制散点图
	scatterSeries->setPen(QPen(Qt::red, 1));
	scatterSeries->setColor(QColor(255, 0, 0));
	scatterSeries->setName("node");
	//添加数据
	for (int i = 0; i < 15; i++) {
		scatterSeries->append(points->at(i));
	}

	QChart * chart = new QChart();
	chart->addSeries(series);
	chart->addSeries(scatterSeries);

	chart->setTitle("ouc map");
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	chart->createDefaultAxes();                        //设置默认的坐标系，如果不设置程序是运行不了的    
	chart->axisX()->setRange(0, 100);                  //设置图表坐标轴的范围，可以不设置，自动调节的    
	chart->axisY()->setRange(0, 100);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);  //抗锯齿渲染   

	myLabel->setText("    test     ");
	myLabel->setStyleSheet("color: black");
	myLabel->setAlignment(Qt::AlignCenter);

	mainLayout->addWidget(chartView, 0, 0);
	mainLayout->addWidget(myLabel, 1, 0);
}

//仅仅是改变折线上的点  
void oucmap::addSeries(QVector<QPointF> * vector) {
	srand((unsigned)time(NULL));
	series->setPen(QPen(Qt::blue, 1, Qt::SolidLine));    //设置画笔
	series->setColor(QColor(rand() % (100), rand() % (200 - 100), rand() % (255 - 100)));                 //设置颜色 
	series->setName("path");

	for (auto c : *vector) {
		series->append(c);
	}
}


//触发事件, 点击第一次, 作为源点, 第二次的作为目的地点
void oucmap::handleClickedPoint(const QPointF &point) {
	//进行改进, 这一公共部分应该创建一个函数
	//点击的点
	QPointF clickedPoint = point;
	// 找到那个点
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

	//添加一些动作..........................................................
	//通过点击, 我可以在逻辑上任意控制他们
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
		//获得了源点和目地点之后, 调用 dijkstra 进行计算, 路径的结果存放在 vec 中
		dij->computeSP(i, j);
		//获得了路径之后, 在图中显示出来
		addSeries(vec);
		//另外更新 myLabel中的内容
		changeTxt(*s);


		//同时判断图中是否含有其他路径, 暂时使现在只出现一条路径
		//开启定时器, 5 秒之后路径消失
		timer->start(5000);
	}
	//点击"景点", 会消失的测试
	//scatterSeries->remove(closest);
}

void oucmap::handleTimeOut() {
	for (auto c : *vec) {
		series->remove(c);
	}
}

void oucmap::handleHoveredPoint(const QPointF & point) {
	//点击的点
	QPointF clickedPoint = point;
	// 找到那个点
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
	//得到悬停点之后, 在label上显示信息
	changeTxt(strings->at(i));

}


void oucmap::changeTxt(const QString & s) {
	myLabel->setText(s);
}

//void oucmap::handleDoubleClickedPoint(const QPointF & point) {
//	//点击的点
//	QPointF clickedPoint = point;
//	// 找到那个点
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
//	//双击一个源点后, 进行自动更换路径, 一个循环
//	//保证5秒之后, j++
//	for (n = 0; n < i; ) {
//		//获得了源点和目地点之后, 调用 dijkstra 进行计算, 路径的结果存放在 vec 中
//		dij->computeSP(i, n);
//		//获得了路径之后, 在图中显示出来
//		addSeries(vec);
//		//另外更新 myLabel中的内容
//		changeTxt(*s);
//		//同时判断图中是否含有其他路径, 暂时使现在只出现一条路径
//		//开启定时器, 5 秒之后路径消失
//		timer->start(5000);
//	}
//	/*for (int j = i; j < 15; j++) {
//		dij->computeSP(i, j);
//		addSeries(vec);
//		changeTxt(*s);
//		timer->start(5000);
//	}*/
//}