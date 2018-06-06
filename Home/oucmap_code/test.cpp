
//关于解决链接错误，参考文档 https://blog.csdn.net/shenziheng1/article/details/54588457
//进行重构
#include "oucmap.h"

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);
	oucmap window;
	window.setLayout1();
	window.resize(800, 500);

	window.show();

	return a.exec();
}
