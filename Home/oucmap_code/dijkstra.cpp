
#include "dijkstra.h"
using namespace std;

//全局变量应声明在头文件中, 在源文件中定义
//这两个全局变量负责 dijkstra 对象 与 oucmap 对象之间信息的传递
//当执行过一定操作后, 二者中应该有值, 供 oucmap 使用

//提供了景点序号与在图中坐标之间的对应关系
QVector<QPointF> * points = new QVector<QPointF>();
//有源点和目的点得到的最终坐标路径, 用来显示到图中的
QVector<QPointF> * vec = new QVector<QPointF>();
//存放每个景点的介绍
QVector<QString> * strings = new QVector<QString>();
//存放路径上景点的信息
QString * s = new QString();

//景点数目
const int MAX_NUM = 15;
TVNode adjList[] = {
	*new TVNode(0, "西大门", "学校的西大门"),
	*new TVNode(1, "工程学院", "工科男的地盘"),
	*new TVNode(2, "行远楼", "大佬们的地盘"),
	*new TVNode(3, "南大门", "学校的南大门"),
	*new TVNode(4, "南区", "南边的学生公寓"),
	*new TVNode(5, "体育馆", "上体育课的地方"),
	*new TVNode(6, "教学区", "学知识的地方"),
	*new TVNode(7, "北区", "北边的学生公寓"),
	*new TVNode(8, "信院北楼", "信息学院学生的地方")	*new TVNode(9, "信院南楼", "别名国家保密学院"),
	*new TVNode(10, "图书馆", "就是图书馆"),
	*new TVNode(11, "东操", "东边露天体育场"),
	*new TVNode(12, "五子顶", "一座小山"),
	*new TVNode(13, "法政学院", "法律系学生的地盘"),
	*new TVNode(14, "数学科学院", "真大佬们的地盘")
};
const double INFINE = 999999.9;
const int V = 15;                                //顶点数
const int E = 24;                                //边数
double disTo[100];                               //记录的是到达该点时的总长度
int edgeTo[100];                                 //记录的是路径上最后一个顶点


map<int, vector<tuple<int, int, double>>> EWD;   //存储图的数据结构, 顶点, 和与这个顶点相连的边的集合

//索引优先队列，存储index ，并以distTo[index]作为优先队列的排序依据
//比较器 GreaterThanByDist 定义 distTo[] 的值越小排在越前面
struct GreaterThanByDist {
	bool operator()(const int i, const int j) const {
		return disTo[i] > disTo[j];
	}
};

priority_queue<int, vector<int>, GreaterThanByDist> minpq;                //索引优先队列

Dijkstra::Dijkstra() {

	{
		//硬编码
		EWD[0].push_back(make_tuple(0, 5, 40));
		EWD[5].push_back(make_tuple(5, 0, 40));

		EWD[0].push_back(make_tuple(0, 6, 50));
		EWD[6].push_back(make_tuple(6, 0, 50));

		EWD[0].push_back(make_tuple(0, 1, 140));
		EWD[1].push_back(make_tuple(1, 0, 140));

		EWD[1].push_back(make_tuple(1, 6, 80));
		EWD[6].push_back(make_tuple(6, 1, 80));

		EWD[1].push_back(make_tuple(1, 2, 30));
		EWD[2].push_back(make_tuple(2, 1, 30));

		EWD[2].push_back(make_tuple(2, 9, 200));
		EWD[9].push_back(make_tuple(9, 2, 200));

		EWD[2].push_back(make_tuple(2, 3, 20));
		EWD[3].push_back(make_tuple(3, 2, 20));

		EWD[3].push_back(make_tuple(3, 4, 10));
		EWD[4].push_back(make_tuple(4, 3, 10));

		EWD[3].push_back(make_tuple(3, 10, 160));
		EWD[10].push_back(make_tuple(10, 3, 160));

		EWD[5].push_back(make_tuple(5, 7, 30));
		EWD[7].push_back(make_tuple(7, 5, 30));

		EWD[5].push_back(make_tuple(5, 6, 20));
		EWD[6].push_back(make_tuple(6, 5, 20));

		EWD[6].push_back(make_tuple(6, 7, 30));
		EWD[7].push_back(make_tuple(7, 6, 30));

		EWD[6].push_back(make_tuple(6, 8, 20));
		EWD[8].push_back(make_tuple(8, 6, 20));

		EWD[6].push_back(make_tuple(6, 11, 100));
		EWD[11].push_back(make_tuple(11, 6, 100));

		EWD[7].push_back(make_tuple(7, 11, 50));
		EWD[11].push_back(make_tuple(11, 7, 50));

		EWD[8].push_back(make_tuple(8, 9, 10));
		EWD[9].push_back(make_tuple(9, 8, 10));

		EWD[8].push_back(make_tuple(8, 12, 10));
		EWD[12].push_back(make_tuple(12, 8, 10));

		EWD[9].push_back(make_tuple(9, 12, 20));
		EWD[12].push_back(make_tuple(12, 9, 20));

		EWD[9].push_back(make_tuple(9, 10, 40));
		EWD[10].push_back(make_tuple(10, 9, 40));

		EWD[10].push_back(make_tuple(10, 14, 70));
		EWD[14].push_back(make_tuple(14, 10, 70));

		EWD[10].push_back(make_tuple(10, 13, 50));
		EWD[13].push_back(make_tuple(13, 10, 50));

		EWD[11].push_back(make_tuple(11, 12, 10));
		EWD[12].push_back(make_tuple(12, 11, 10));

		EWD[11].push_back(make_tuple(13, 11, 800));
		EWD[13].push_back(make_tuple(11, 13, 800));

		EWD[13].push_back(make_tuple(13, 14, 50));
		EWD[14].push_back(make_tuple(14, 13, 50));
	}

	{
		points->append(*new QPointF(5, 59));
		points->append(*new QPointF(9, 45));
		points->append(*new QPointF(10, 30));
		points->append(*new QPointF(21, 19));
		points->append(*new QPointF(22, 4));
		points->append(*new QPointF(23, 70));
		points->append(*new QPointF(34, 64));
		points->append(*new QPointF(39, 76));
		points->append(*new QPointF(43, 52));
		points->append(*new QPointF(45, 39));
		points->append(*new QPointF(52, 30));
		points->append(*new QPointF(65, 75));
		points->append(*new QPointF(67, 55));
		points->append(*new QPointF(75, 35));
		points->append(*new QPointF(58, 18));
	}

	{
		strings->append(*new QString("  xiMen  "));
		strings->append(*new QString("  gongYuan  "));
		strings->append(*new QString("  xingYuanLou  "));
		strings->append(*new QString("  nanMen  "));
		strings->append(*new QString("  nanQu  "));
		strings->append(*new QString("  tiYuGuan  "));
		strings->append(*new QString("  jiaoXueLou  "));
		strings->append(*new QString("  beiQu  "));
		strings->append(*new QString("  xinBei  "));
		strings->append(*new QString("  xinNan  "));
		strings->append(*new QString("  library   "));
		strings->append(*new QString("  dongCao  "));
		strings->append(*new QString("  wuZhiDing  "));
		strings->append(*new QString("  faZheng  "));
		strings->append(*new QString("  shuYuan  "));
	}
}

void Dijkstra::relax(tuple<int, int, double> edge) {
	int v = get<0>(edge);
	int w = get<1>(edge);
	double weight = get<2>(edge);
	if (disTo[w] > disTo[v] + weight) {
		disTo[w] = disTo[v] + weight;
		edgeTo[w] = v;
		minpq.push(w);
	}
}

// s 源点
//很像广度搜索
void Dijkstra::dijkstra(int s) {
	for (int i = 0; i < V; i++) {
		disTo[i] = INFINE;
	}
	disTo[s] = 0.0;
	minpq.push(s);
	while (!minpq.empty()) {
		int u = minpq.top();
		minpq.pop();
		for (vector<tuple<int, int, double>>::iterator iter = EWD[u].begin(); iter != EWD[u].end(); iter++) {
			relax(*iter);
		}
	}
}

void Dijkstra::computeSP(int source, int vertex) {
	dijkstra(source);

	stack<int> path;
	for (int i = vertex; i != source; i = edgeTo[i]) {
		path.push(i);
	}
	path.push(source);

	//重新初始化 vec, 否则会出现很多条路径
	vec->clear();
	s->clear();
	while (!path.empty()) {
		//cout << adjList[path.top()].name << "    ";
		//使用函数at(), 而不应该使用下标运算符, 解决问题
		vec->append(points->at(path.top()));
		s->append(strings->at(path.top()));
		path.pop();
		if (!path.empty()) {
			s->append("---->");
		}
	}
	s->append("   : ");
	s->append(to_string(disTo[vertex]).c_str());
}

//打印图
void Dijkstra::showEWD() {
	cout << "graph: " << endl;
	for (int i = 0; i < V; i++) {
		cout << i << " : ";
		for (vector<tuple<int, int, double>>::iterator iter = EWD[i].begin(); iter != EWD[i].end(); iter++) {
			cout << get<0>(*iter) << " -> " << get<1>(*iter) << " : " << get<2>(*iter) << "   ";
		}
		cout << endl;
	}
}
