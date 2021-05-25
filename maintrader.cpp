#include <iostream>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <fstream>
#include <iomanip>

using namespace std;

#define max_vexNum 8		// 最大城市个数
#define MAX_PATH_LENGTH 200 //最大路径数量
#define samepath 20			//存储相同路径
typedef struct
{
	int vex_num, arc_num;				 // 顶点数 边数
	char vexs[max_vexNum];				 // 顶点向量
	double arcs[max_vexNum][max_vexNum]; // 邻接矩阵
} Graph;

bool is_visited[max_vexNum];			// 存储当前城市是否已被访问
char path[MAX_PATH_LENGTH][max_vexNum]; // 存储所有路径
double sum_lenth[MAX_PATH_LENGTH];		// 存储所有路径对应的长度

long int path_num = 0, path_index = 0;//路径数目变量和记录路径城市的变量
long double bestLength = INT_MAX + 0.0; // 最短路径初始化为无穷大

int num, newnum = 0;
int mark[samepath];		//用来存储所有在比较中产生的次级路径标号
int mark_new[samepath]; //用来存储和最优路径等价的路径标号

string textname;
//确认城市有没有存在,找出它的标号
int CityIndex(Graph G, char city)
{
	for (int i = 0; i < G.vex_num; i++)
	{
		if (G.vexs[i] == city)
		{
			return i;//将城市的下表返回
		}
	}
	cout << "【error】当前城市未找到！" << endl;
	return -1;
}



void DFS(Graph G, char city)
{
	int current_index = CityIndex(G, city); // 将当前城市下标记住

	if (path_index == G.vex_num - 1 && G.arcs[current_index][int('A') - 65] > 0)
	{   //如果是最后一个城市，且最后一个城市能回到起始城市，进入此分支
		path[path_num][path_index] = city;//运行到到此处时，表明一条路径将走到最后一个城市，将其添加到路径
		path[path_num][path_index + 1] = 'A';//再加上起始城市
		// 即回到出发城市
		sum_lenth[path_num] = 0; // 用来存储最短路径

		// 计算最短路径
		for (int i = 0; i < G.vex_num; i++)
		{
			sum_lenth[path_num] += G.arcs[(int)path[path_num][i] - 65][(int)path[path_num][i + 1] - 65];
			//从a-j依次连接所有城市
			cout << path[path_num][i] << "-" << G.arcs[(int)path[path_num][i] - 65][(int)path[path_num][i + 1] - 65] << "->";
			//当path-num＋1后，path[path_num][i]的前面需要保持，后面变化
			path[path_num + 1][i] = path[path_num][i];
		}

		if (bestLength >= sum_lenth[path_num])
		{
			// 更新最短路径
			bestLength = sum_lenth[path_num];
			mark[num] = path_num;//将所有比较产生的次级路径记录下来
			num++;
		}

		cout << path[path_num][G.vex_num] << ' ';
		cout << "该线路总长度为" << sum_lenth[path_num] << endl;
		cout << "第【" << (path_num + 1) << "】条路径！" << endl;
		path_num++; // 下一条路径

		return;
	}
	else
	{ //利用递归从起始城市开始
		for (int i = 0; i < G.vex_num; i++)
		{
			if (G.arcs[current_index][i] > 0 && !is_visited[i])//若当前边值不为0，即能走的通（不到对角线的位置）
			{
				path[path_num][path_index] = city;//放入前者城市
				path_index++;//指向下一个城市
				is_visited[current_index] = true;//将前者城市变为已经访问
				DFS(G, (char)(i + 65));//调用递归，访问下一个城市
				path_index--;//回溯
				is_visited[current_index] = false;
			}
		}
	}
}

//创建这个邻接矩阵
void CreateGraph(Graph &G)
{
	ifstream read_in; //读操作（输入）的文件类(由istream引申而来)
	read_in.open(textname);
	if (!read_in.is_open())
	{
		cout << "文件读取失败." << endl;
		return;
	}

	read_in >> G.vex_num; //读取顶点数目

	G.arc_num = 0;
	for (int i = 0; i < G.vex_num; i++)
	{
		read_in >> G.vexs[i];
	}
	G.vexs[G.vex_num] = '\0'; // char的结束符

	for (int i = 0; i < G.vex_num; i++)
	{
		for (int j = 0; j < G.vex_num; j++)
		{
			read_in >> G.arcs[i][j];

			// 计算边数
			if (G.arcs[i][j] > 0)
			{
				G.arc_num++;
			}
		}
	}

	// display，用来读取文件中的数组
	cout << "无向图创建完毕，相关信息如下：" << endl;
	cout << "【顶点数/城市数】 G.vex_num = " << G.vex_num << endl;
	cout << "【边数】 G.arc_num = " << G.arc_num << endl;
	cout << "【城市代号】 vexs[max_vexNum] = ";
	for (int i = 0; i < G.vex_num; i++)
	{
		cout << G.vexs[i] << " ";
	}
	cout << endl
		 << "【邻接矩阵】 arcs[max_vexNum][max_vexNum] 如下：" << endl;
	for (int i = 0; i < G.vex_num; i++)
	{
		for (int j = 0; j < G.vex_num; j++)
		{
			cout << std::right << setw(10) << G.arcs[i][j] << " ";//通过右对齐的方式输出数组
		}
		cout << endl;
	}
}

int main()
{
	cout << "程序开始..." << endl;
	time_t T_begin = clock();
    
    cout<<"请输入要读取的文件名"<<endl;
	cin>>textname;


	Graph G;
	CreateGraph(G);

	//初始化访问数组
	for (int i = 0; i < G.vex_num; i++)
	{
		is_visited[i] = false;
	}
	//令开始城市为a
	char city = 'A';
	DFS(G, city);

	// 最短路程bestLength
	cout << "最短路程bestLength = " << bestLength << endl;
	cout << "最短路径有" << endl;

	//计算相同最短路径，通过与已经计算出的最短路径进行比较，并记住路径
	for (int i = 0; i < num; i++)
	{
		if (sum_lenth[mark[i]] == bestLength)
		{
			mark_new[newnum] = mark[i];
			newnum++;
		}
	}
	//进行最短路径的输出,通过之间设置的记录数组进行输出（注意数据的类型）
	for (int i = 0; i < newnum; i++)
	{
		for (int j = 0; j < G.vex_num; j++)
		{
			cout << path[mark_new[i]][j] << "-" << G.arcs[(int)path[mark_new[i]][j] - 65][(int)path[mark_new[i]][j + 1] - 65] << "->";
		}//输出所有被记住的与最短路径相同的路径
		cout << path[mark_new[i]][G.vex_num] << endl;//加上起始城市
	}

	time_t T_end = clock();
	double RunningTime = double(T_end - T_begin) / CLOCKS_PER_SEC;
	cout << endl;
	cout << "程序运行时间 RunningTime = " << RunningTime << endl;
	std::system("pause");
	return 0;
}
