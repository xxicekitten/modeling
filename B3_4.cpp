#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <map>
#include <string>
#include <cstring>

using namespace std;

//V002, V004, V006, V010
vector<string> need[4];
string hotel[4] = {"S0971", "S1153", "S1229", "S0965"};
string final = "S0115";
int best_result;
vector<string> result;
string best_hotel;
vector<string> current;

const int maxl = 50;
const int maxn = 700 * maxl;
const int maxm = 700 * 700 + 700 * maxl * maxl;
const int inf = 0x7fffffff;

const int line_num = 49;

class Edge{
public:
	int x, y;
	double c;
	int yuan;
	int next;
};

Edge edge[maxm];
int head[maxn], edgeNum;
bool vis[maxn];
double dis[maxn];
int sum_yuan[maxn];
int father[maxn];
double father_len[maxn];
int start_node;

map<string, int> S_to_int;
map<int, string> int_to_S;
int S_to_int_size;

double line_wait_time[maxl];
int line_yuan[maxl];

void init(){
	memset(head, -1, sizeof head);
	edgeNum = 0;

	memset(vis, 0, sizeof vis);
	fill(dis, dis + maxn, inf);
}

void addEdge(int x, int y, double cap, int yuan){
	edge[edgeNum].x = x;
	edge[edgeNum].y = y;
	edge[edgeNum].c = cap;
	edge[edgeNum].yuan = yuan;
	edge[edgeNum].next = head[x];
	head[x] = edgeNum ++;
}

void make_graph(){
	//	1...line_num(49)
	//	0		1		2		...	48
	//  1*49+0	1*49+1	1*49+2	...	1*49+48
	//	2*49+0	2*49+1	2*49+2	...	2*49+48

	ifstream fin("input_1_2.txt");

	int line_pos = 0;

	int temp_yuan;
	double temp_time;

	while(fin >> temp_time >> temp_yuan){
		line_wait_time[line_pos] = temp_time;
		line_yuan[line_pos] = temp_yuan;

		string temp_line;
		fin >> temp_line;

		vector<string> split_line;
		while(temp_line.size() > 5){
			string temp = temp_line.substr(0, 5);
			split_line.push_back(temp);
			temp_line = temp_line.substr(6);
		}
		split_line.push_back(temp_line);

		for(int i = 0; i < split_line.size(); i ++){
			if(S_to_int.find(split_line[i]) == S_to_int.end()){
				S_to_int.insert(pair<string, int>(split_line[i], S_to_int_size));
				int_to_S.insert(pair<int, string>(S_to_int_size, split_line[i]));
				S_to_int_size ++;
			}

			//add row edge
			int current_s = S_to_int[split_line[i]];
			for(int p = 0; p < line_num; p ++){
				if(p != line_pos){
					addEdge(current_s * line_num + p, current_s * line_num + line_pos, temp_time / 2, temp_yuan);
				}
			}

			//add column edge
			if(i){
				int a, b;
				a = S_to_int[split_line[i - 1]];
				b = S_to_int[split_line[i]];
				
				if(temp_yuan == 3){
					addEdge(a * line_num + line_pos, b * line_num + line_pos, 5, 0);
					addEdge(b * line_num + line_pos, a * line_num + line_pos, 5, 0);
				}
				else{
					addEdge(a * line_num + line_pos, b * line_num + line_pos, 3, 0);
					addEdge(b * line_num + line_pos, a * line_num + line_pos, 3, 0);
				}
			}
		}

		line_pos ++;
	}

	start_node = line_num * S_to_int_size;
}

void make_st_edge(string st){
	int a = S_to_int[st];
	for(int i = 0; i < line_num; i ++){
		//addEdge(start_node, a * line_num + i, 0, line_yuan[i]);
		addEdge(start_node, a * line_num + i, line_wait_time[i] / 2, line_yuan[i]);
	}
}

void spfa(int start){
	dis[start] = 0;

	//
	sum_yuan[start] = 0;
	
	vis[start] = true;
	queue<int> q;
	q.push(start);
	while(!q.empty()){
		int t = q.front();
		q.pop();
		vis[t] = false;
		for(int j = head[t]; ~j; j = edge[j].next){
			//int w = edge[j].c;
			double w = edge[j].c;
			
			int temp = edge[j].y;
			if(w + dis[t] < dis[temp]){
				//
				father[temp] = t;
				father_len[temp] = w;

				dis[temp] = w + dis[t];
				//
				sum_yuan[temp] = edge[j].yuan + sum_yuan[t];

				if(!vis[temp]){
					vis[temp] = true;
					q.push(temp);
				}
			}

			//still to update yuan;
			if(w + dis[t] == dis[temp]){
				if(edge[j].yuan + sum_yuan[t] < sum_yuan[temp]){
					//
					father[temp] = t;
					father_len[temp] = w;

					dis[temp] = w + dis[t];
					//
					sum_yuan[temp] = edge[j].yuan + sum_yuan[t];

					if(!vis[temp]){
						vis[temp] = true;
						q.push(temp);
					}
				}
			}
		}
	}
}

int get_ans(string ed){
	int b = S_to_int[ed];

	double best_ans = inf;
	int best_yuan = inf;
	int best_node = -1;

	for(int i = 0; i < line_num; i ++){
		if(dis[b * line_num + i] < best_ans){
			best_ans = dis[b * line_num + i];
			best_yuan = sum_yuan[b * line_num + i];
			best_node = b * line_num + i;
		}
		else if(dis[b * line_num + i] == best_ans){
			if(sum_yuan[b * line_num + i] < best_yuan){
				best_yuan = sum_yuan[b * line_num + i];
				best_node = b * line_num + i;
			}
		}
	}

	vector<int> line_s;
	vector<double> line_s_len;
	if(best_node != -1){
		while(best_node != start_node){
			line_s.push_back(best_node);
			line_s_len.push_back(father_len[best_node]);
			best_node = father[best_node];
		}
	}

	return best_yuan;
}

int get_result(string st, string ed){
	init();
	make_graph();
	make_st_edge(st);
	spfa(start_node);
	return get_ans(ed);
}

void compute(string a, int now, int sum){

	if(now == 4){
		sum += get_result(current[3], a);
		sum += get_result(a, final); // hotel --> final

		if(sum < best_result || best_result == -1){
			best_result = sum;
			result = current;
			best_hotel = a;
		}
		return;
	}

	
	else{
		if(now == 2){
			sum += get_result(current[1], a);// current[1] --> hotel
		}

		for(int i = 0; i < need[now].size(); i ++){
			current.push_back(need[now][i]);
			if(now == 2){
				sum += get_result(a, current[now]);
			}
			else if(now){
				sum += get_result(current[now - 1], current[now]);// current[now - 1] --> current[now]
			}
			compute(a, now + 1, sum);

			current.pop_back();
		}
	}
}

void fun(){

	for(int i = 0; i < 4; i ++){
		current.clear();
		compute(hotel[i], 0, 0);
	}

	cout << best_result << endl;
	for(int i = 0; i < result.size(); i ++){
		cout << result[i] << " ";
	}
	cout << endl;
}

int main(){
	best_result = -1;

	need[0].push_back("S1171");
	need[0].push_back("S0995");
	need[1].push_back("S1353");
	need[1].push_back("S1119");
	need[1].push_back("S1281");
	need[2].push_back("S0771");
	need[2].push_back("S0471");
	need[3].push_back("S0009");

	do{
		fun();
	}while(next_permutation(need, need + 4));

	cout << best_result << endl;
	for(int i = 0; i < result.size(); i ++){
		cout << result[i] << " ";
	}
	cout << endl;
	cout << best_hotel;

	system("pause");
	return 0;
}
