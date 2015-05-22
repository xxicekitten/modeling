#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <map>

using namespace std;

const int maxl = 50 * 2;
const int maxs = 700;
const int maxn = maxs * maxl;
const int maxm = maxs * maxs + maxs * maxl * maxl;

const int line_num = 49 * 2;

const int inf = 0x7fffffff;

class Edge{
public:
	int x, y;
	int c;
	int yuan;
	int next;
};

class Line{
public:
	int first_time, last_time;
	int delta;
	int yuan;
	vector<string> station;
};

vector<Line> line;

map<string, int> S_to_int;
map<int, string> int_to_S;
int S_to_int_size;

//int station_first_time[maxn];
int station_last_time[maxn];

Edge edge[maxm];
int head[maxn], edgeNum;
bool vis[maxn];
int dis[maxn];
int sum_yuan[maxn];
int father[maxn];
int father_len[maxn];
int start_node;

void init_input(){
	line.clear();
	for(int i = 0; i < maxn; i ++){
		station_last_time[i] = inf;
	}

	ifstream fin("input_3.txt");

	int temp_ft, temp_lt, temp_d, temp_y;
	while(fin >> temp_ft >> temp_lt >> temp_d >> temp_y){
		Line new_l;
		new_l.first_time = temp_ft;
		new_l.last_time = temp_lt;
		new_l.delta = temp_d;
		new_l.yuan = temp_y;

		string temp_line;
		fin >> temp_line;

		vector<string> split_line;
		while(temp_line.size() > 5){
			string temp = temp_line.substr(0, 5);
			split_line.push_back(temp);
			temp_line = temp_line.substr(6);
		}
		split_line.push_back(temp_line);

		new_l.station = split_line;
		line.push_back(new_l);

		for(int i = 0; i < split_line.size(); i ++){
			if(S_to_int.find(split_line[i]) == S_to_int.end()){
				S_to_int.insert(pair<string, int>(split_line[i], S_to_int_size));
				int_to_S.insert(pair<int, string>(S_to_int_size, split_line[i]));
				S_to_int_size ++;
			}
		}

		Line new_l_2;
		new_l_2.first_time = temp_ft;
		new_l_2.last_time = temp_lt;
		new_l_2.delta = temp_d;
		new_l_2.yuan = temp_y;

		reverse(split_line.begin(), split_line.end());
		new_l_2.station = split_line;
		line.push_back(new_l_2);
	}

	for(int i = 0; i < line.size(); i ++){
		int lt = line[i].last_time;
		int yuan = line[i].yuan;
		int run_time = 0;
		if(yuan == 3){
			run_time = 5;
		}
		else{
			run_time = 3;
		}
		for(int j = 0; j < line[i].station.size(); j ++){
			int a = S_to_int[line[i].station[j]];
			station_last_time[a * line_num + i] = lt - j * run_time;
		}
	}
}

void init_graph(){
	memset(head, -1, sizeof head);
	edgeNum = 0;

	memset(vis, 0, sizeof vis);
	fill(dis, dis + maxn, inf);

	start_node = line_num * S_to_int_size;
}

void addEdge(int x, int y, int cap, int yuan){
	edge[edgeNum].x = x;
	edge[edgeNum].y = y;
	edge[edgeNum].c = cap;
	edge[edgeNum].yuan = yuan;
	edge[edgeNum].next = head[x];
	head[x] = edgeNum ++;
}

void make_graph(){
	//	1...line_num(98)
	//	0		1		2		...	97
	//	1*98+0	1*98+1	1*98+2	...	1*98+97
	//	2*98+0	2*98+1	2*98+2	...	2*98+97

	for(int i = 0; i < line.size(); i ++){
		int delta = line[i].delta;
		int yuan = line[i].yuan;
		for(int j = 0; j < line[i].station.size(); j ++){
			int a = S_to_int[line[i].station[j]];

			//add row edge;
			for(int k = 0; k < line.size(); k ++){
				if(k != i && station_last_time[a * line_num + k] != inf){
					if(station_last_time[a * line_num + i] >= station_last_time[a * line_num + k]){
						int wait_time = station_last_time[a * line_num + i] - station_last_time[a * line_num + k];
						addEdge(a * line_num + k, a * line_num + i, wait_time, yuan);
					}
					else{
						int next_time = 0;
						while(station_last_time[a * line_num + i] + next_time < station_last_time[a * line_num + k]){
							next_time += delta;
						}
						int wait_time = station_last_time[a * line_num + i] + next_time - station_last_time[a * line_num + k];
						addEdge(a * line_num + k, a * line_num + i, wait_time, yuan);
					}
				}
			}

			//add column edge;
			if(j){
				int st, ed;
				st = S_to_int[line[i].station[j - 1]];
				ed = S_to_int[line[i].station[j]];
				if(yuan == 3){
					addEdge(ed * line_num + i, st * line_num + i, 5, 0);
				}
				else{
					addEdge(ed * line_num + i, st * line_num + i, 3, 0);
				}
			}
		}
	}
}

void make_st_graph(string st){
	int a = S_to_int[st];
	for(int i = 0; i < line_num; i ++){
		int yuan = line[i].yuan;
		int wait_time = station_last_time[a * line_num + i];
		addEdge(start_node, a * line_num + i, wait_time, yuan);
	}
}

void spfa(int start){
	dis[start] = 0;

	sum_yuan[start] = 0;
	
	vis[start] = true;
	queue<int> q;
	q.push(start);
	while(!q.empty()){
		int t = q.front();
		q.pop();
		vis[t] = false;
		for(int j = head[t]; ~j; j = edge[j].next){
			int w = edge[j].c;
			//double w = edge[j].c;
			
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

	int best_ans = inf;
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
	vector<int> line_s_len;
	if(best_node != -1){
		while(best_node != start_node){
			line_s.push_back(best_node);
			line_s_len.push_back(father_len[best_node]);
			best_node = father[best_node];
		}
	}

	//cout << best_ans << endl;
	//cout << best_yuan << endl;

	reverse(line_s.begin(), line_s.end());
	reverse(line_s_len.begin(), line_s_len.end());

	for(int i = 0; i < line_s.size(); i ++){
		int current_line = (line_s[i] % line_num) + 1;
		int current_node = line_s[i] / line_num;
		//cout << "==> line" << current_line << ": ";
		//cout << int_to_S[current_node] << " ";
		//cout << "use: " << line_s_len[i] << endl;
	}

	// cout << endl;
	return best_ans;
}

void solve(){
	/*
	string st, ed;
	while(cin >> st >> ed){
		init_input();
		init_graph();
		make_graph();
		make_st_graph(st);
		spfa(start_node);
		get_ans(ed);
	}
	*/

	vector<string> row;
	for(int i = 0; i < 28; i ++){
		string temp;
		cin >> temp;
		row.push_back(temp);
	}
	vector<string> column;
	for(int i = 0; i < 22; i ++){
		string temp;
		cin >> temp;
		column.push_back(temp);
	}

	ofstream fout("output.txt");
	for(int i = 0; i < 22; i ++){
		fout << "\t" << column[i];
	}
	fout << endl;

	for(int i = 0; i < 28; i ++){
		cout << row[i];
		fout << row[i];
		for(int j = 0; j < 22; j ++){
			//int a = S_to_int[row[i]];
			//int b = S_to_int[column[j]];

			init_input();
			init_graph();
			make_graph();
			make_st_graph(row[i]);
			spfa(start_node);
			fout << "\t" << get_ans(column[j]);
		}
		fout << endl;
	}
}

int main(){
	solve();
	return 0;
}
