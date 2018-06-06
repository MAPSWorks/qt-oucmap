
#include "dijkstra.h"
using namespace std;

//ȫ�ֱ���Ӧ������ͷ�ļ���, ��Դ�ļ��ж���
//������ȫ�ֱ������� dijkstra ���� �� oucmap ����֮����Ϣ�Ĵ���
//��ִ�й�һ��������, ������Ӧ����ֵ, �� oucmap ʹ��

//�ṩ�˾����������ͼ������֮��Ķ�Ӧ��ϵ
QVector<QPointF> * points = new QVector<QPointF>();
//��Դ���Ŀ�ĵ�õ�����������·��, ������ʾ��ͼ�е�
QVector<QPointF> * vec = new QVector<QPointF>();
//���ÿ������Ľ���
QVector<QString> * strings = new QVector<QString>();
//���·���Ͼ������Ϣ
QString * s = new QString();

//������Ŀ
const int MAX_NUM = 15;
TVNode adjList[] = {
	*new TVNode(0, "������", "ѧУ��������"),
	*new TVNode(1, "����ѧԺ", "�����еĵ���"),
	*new TVNode(2, "��Զ¥", "�����ǵĵ���"),
	*new TVNode(3, "�ϴ���", "ѧУ���ϴ���"),
	*new TVNode(4, "����", "�ϱߵ�ѧ����Ԣ"),
	*new TVNode(5, "������", "�������εĵط�"),
	*new TVNode(6, "��ѧ��", "ѧ֪ʶ�ĵط�"),
	*new TVNode(7, "����", "���ߵ�ѧ����Ԣ"),
	*new TVNode(8, "��Ժ��¥", "��ϢѧԺѧ���ĵط�"),
	*new TVNode(9, "��Ժ��¥", "�������ұ���ѧԺ"),
	*new TVNode(10, "ͼ���", "����ͼ���"),
	*new TVNode(11, "����", "����¶��������"),
	*new TVNode(12, "���Ӷ�", "һ��Сɽ"),
	*new TVNode(13, "����ѧԺ", "����ϵѧ���ĵ���"),
	*new TVNode(14, "��ѧ��ѧԺ", "������ǵĵ���")
};
const double INFINE = 999999.9;
const int V = 15;                                //������
const int E = 24;                                //����
double disTo[100];                               //��¼���ǵ���õ�ʱ���ܳ���
int edgeTo[100];                                 //��¼����·�������һ������


map<int, vector<tuple<int, int, double>>> EWD;   //�洢ͼ�����ݽṹ, ����, ����������������ıߵļ���

												 //�������ȶ��У��洢index ������distTo[index]��Ϊ���ȶ��е���������
												 //�Ƚ��� GreaterThanByDist ���� distTo[] ��ֵԽС����Խǰ��
struct GreaterThanByDist {
	bool operator()(const int i, const int j) const {
		return disTo[i] > disTo[j];
	}
};

priority_queue<int, vector<int>, GreaterThanByDist> minpq;                //�������ȶ���

Dijkstra::Dijkstra() {

	{
		//Ӳ����
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

// s Դ��
//����������
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

	//���³�ʼ�� vec, �������ֺܶ���·��
	vec->clear();
	s->clear();
	while (!path.empty()) {
		//cout << adjList[path.top()].name << "    ";
		//ʹ�ú���at(), ����Ӧ��ʹ���±������, �������
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

//��ӡͼ
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
