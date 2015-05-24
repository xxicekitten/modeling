#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <cstring>

using namespace std;

//---------------------------------------------------------

const int maxl = 50;
const int maxn = 700 * maxl;
const int maxm = 700 * 700 + 700 * maxl * maxl;
const int inf = 0x7fffffff;

const int line_num = 49;

ofstream fout("output.txt");

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
					//addEdge(a, b, 5, 0);
					//addEdge(a, b, 5, 0);
					/*
					for(int p = 0; p < line_num; p ++){
						addEdge(a * line_num + p, b * line_num + p, 5, 0);
						addEdge(b * line_num + p, a * line_num + p, 5, 0);
					}
					*/
					addEdge(a * line_num + line_pos, b * line_num + line_pos, 5, 0);
					addEdge(b * line_num + line_pos, a * line_num + line_pos, 5, 0);
				}
				else{
					//addEdge(a, b, 3, 0);
					//addEdge(a, b, 3, 0);
					/*
					for(int p = 0; p < line_num; p ++){
						addEdge(a * line_num + p, b * line_num + p, 3, 0);
						addEdge(b * line_num + p, a * line_num + p, 3, 0);
					}
					*/
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

int get_ans(string ed, int &change_line_sum, int &time_trans_sum){
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

	//cout << best_ans << endl;
	//cout << best_yuan << endl;
	//fout << best_ans << "\t" << best_yuan << "\t";

	reverse(line_s.begin(), line_s.end());
	reverse(line_s_len.begin(), line_s_len.end());

	map<int, bool> log;

	for(int i = 0; i < line_s.size(); i ++){
		int current_line = (line_s[i] % line_num) + 1;
		int current_node = line_s[i] / line_num;
		//cout << "==> line" << current_line << ": ";
		//cout << int_to_S[current_node] << " ";
		//cout << "use: " << line_s_len[i] << endl;
		//fout << " ==> line" << current_line << ": " << int_to_S[current_node] << " ";

		log[current_line] = true;
	}

	//fout << endl;

	time_trans_sum += best_ans;
	change_line_sum += log.size();
	return best_yuan;
}

int get_my_ans(string st, string ed, int &change_line_sum, int &time_trans_sum){
	init();
	make_graph();
	make_st_edge(st);
	spfa(start_node);
	return get_ans(ed, change_line_sum, time_trans_sum);
}
//---------------------------------------------------------






vector<string> hotel_name;
vector<string> view_name;
map<string, int> view_level;
map<string, int> view_cost;
map<string, int> view_time;
map<string, string> view_to_s;
vector<string> my_queue;

int current_plan_day_num;
double best_day_yuan[10];
vector<string> best_day_plan[10];

int step_flag;

void init_B6(){
	step_flag = 0;
	best_day_yuan[6] = 0.0;

	my_queue.clear();

	hotel_name.clear();
	hotel_name.push_back("H017");
	hotel_name.push_back("H023");
	hotel_name.push_back("H025");
	hotel_name.push_back("H027");

	view_name.clear();
	view_name.push_back("V002");
	view_name.push_back("V004");
	view_name.push_back("V007");
	view_name.push_back("V009");
	view_name.push_back("V001");
	view_name.push_back("V005");
	view_name.push_back("V006");
	view_name.push_back("V014");

	view_level.clear();
	view_level.insert(pair<string, int>("V002", 1));
	view_level.insert(pair<string, int>("V004", 1));
	view_level.insert(pair<string, int>("V007", 1));
	view_level.insert(pair<string, int>("V009", 1));
	view_level.insert(pair<string, int>("V001", 2));
	view_level.insert(pair<string, int>("V005", 2));
	view_level.insert(pair<string, int>("V006", 2));
	view_level.insert(pair<string, int>("V014", 2));

	view_cost.insert(pair<string, int>("V002", 90));
	view_cost.insert(pair<string, int>("V004", 50));
	view_cost.insert(pair<string, int>("V007", 145));
	view_cost.insert(pair<string, int>("V009", 100));
	view_cost.insert(pair<string, int>("V001", 120));
	view_cost.insert(pair<string, int>("V005", 180));
	view_cost.insert(pair<string, int>("V006", 50));
	view_cost.insert(pair<string, int>("V014", 120));

	view_time.insert(pair<string, int>("V002", 150));
	view_time.insert(pair<string, int>("V004", 180));
	view_time.insert(pair<string, int>("V007", 150));
	view_time.insert(pair<string, int>("V009", 240));
	view_time.insert(pair<string, int>("V001", 120));
	view_time.insert(pair<string, int>("V005", 210));
	view_time.insert(pair<string, int>("V006", 180));
	view_time.insert(pair<string, int>("V014", 210));

	view_to_s.insert(pair<string, string>("V002", "S0995"));
	view_to_s.insert(pair<string, string>("V004", "S1119"));
	view_to_s.insert(pair<string, string>("V007", "S0917"));
	view_to_s.insert(pair<string, string>("V009", "S1187"));
	view_to_s.insert(pair<string, string>("V001", "S0045"));
	view_to_s.insert(pair<string, string>("V005", "S0897"));
	view_to_s.insert(pair<string, string>("V006", "S0771"));
	view_to_s.insert(pair<string, string>("V014", "S1049"));

	view_to_s.insert(pair<string, string>("H017", "S0971"));
	view_to_s.insert(pair<string, string>("H023", "S1153"));
	view_to_s.insert(pair<string, string>("H025", "S1229"));
	view_to_s.insert(pair<string, string>("H027", "S0965"));
}

void compute_fun(){
	/*
	for(int i = 0; i < my_queue.size(); i ++){
		cout << my_queue[i] << " ==> ";
	}
	cout << endl;
	*/

	/*
	my_queue.clear();
	my_queue.push_back("V008");
	my_queue.push_back("V007");
	my_queue.push_back("H027");
	my_queue.push_back("V004");
	my_queue.push_back("V006");
	my_queue.push_back("H023");
	my_queue.push_back("V001");
	my_queue.push_back("V009");
	*/


	//todo
	int cost_sum = 0 + 360;
	int cost_trans = 0;
	int change_line_sum = 0;
	int time_trans_sum = 0;
	for(int i = 1; i < my_queue.size(); i ++){
		cost_trans += get_my_ans(view_to_s[my_queue[i - 1]], view_to_s[my_queue[i]], change_line_sum, time_trans_sum);
		
		//cost_trans += 3;
	}
	//change_line_sum = my_queue.size() * 2;
	//time_trans_sum += 300;
	//cout << time_trans_sum;

	cost_sum += cost_trans;
	for(int i = 0; i < my_queue.size(); i ++){
		if(my_queue[i][0] == 'V'){
			cost_sum += view_cost[my_queue[i]];
		}
	}

	int view_sum = my_queue.size() - 2;

	int level_sum = 0;
	for(int i = 0; i < my_queue.size(); i ++){
		if(my_queue[i][0] == 'V'){
			if(view_level.find(my_queue[i]) != view_level.end()){
				level_sum += view_level[my_queue[i]];
			}
			else{
				level_sum += 3;
			}
		}
	}

	double comfortable_sum = 0;
	double weight_change_line_sum = 0.06;
	double weight_hotel_sum = 0.4;
	double weight_free_time = 0.3 / 240;
	int hotel_sum = 0;
	int free_time = 0 + time_trans_sum;

	string temp_hotel = "";
	for(int i = 0; i < my_queue.size(); i ++){
		if(my_queue[i][0] == 'H'){
			if(temp_hotel == ""){
				temp_hotel = my_queue[i];
			}
			else{
				if(temp_hotel == my_queue[i]){
					hotel_sum = 0;
				}
				else{
					hotel_sum = 1;
				}
				break;
			}
		}
	}

	for(int i = 0; i < my_queue.size(); i ++){
		if(my_queue[i][0] == 'V'){
			free_time += view_time[my_queue[i]];
		}
	}

	comfortable_sum = weight_change_line_sum * change_line_sum
		+ weight_hotel_sum * hotel_sum
		+ weight_free_time * (9 * 60 * 3 - free_time);

	double final_result = current_plan_day_num * comfortable_sum / (1.0 * cost_sum * level_sum);

	if(final_result > best_day_yuan[current_plan_day_num]){
		best_day_yuan[current_plan_day_num] = final_result;
		best_day_plan[current_plan_day_num] = my_queue;
	}
}

void compute(int remain_view, int remain_day, vector<string> remain_view_name, int add_sum){
	if(remain_view == 0){
		compute_fun();
		step_flag ++;
		if(step_flag % 10 == 0){
			cout << step_flag << endl;
		}
		if(step_flag % 100 == 0){
			cout << current_plan_day_num << " " << best_day_yuan[current_plan_day_num] << " ";
			fout << current_plan_day_num << " " << best_day_yuan[current_plan_day_num] << " ";
			for(int j = 0; j < best_day_plan[current_plan_day_num].size(); j ++){
				if(j){
					fout << " ==> ";
					cout << " ==> ";
				}
				fout << best_day_plan[current_plan_day_num][j] << " ";
				cout << best_day_plan[current_plan_day_num][j] << " ";
			}
		}
		return;
	}
	else{

		for(int i = 0; i < remain_view_name.size(); i ++){
			my_queue.push_back(remain_view_name[i]);

			vector<string> temp = remain_view_name;
			temp.erase(temp.begin() + i);

			int d = remain_view / remain_day;

			if(add_sum == 0){

				if(d == 2){//not insert hotel
					compute(remain_view - 1, remain_day, temp, 1);

					my_queue.pop_back();
				}
				else if(d * remain_day == remain_view){//insert hotel

					if(remain_day != 1){
						for(int j = 0; j < hotel_name.size(); j ++){
							my_queue.push_back(hotel_name[j]);
							compute(remain_view - 1, remain_day - 1, temp, 0);
							my_queue.pop_back();
						}
					}
					else{
						compute(remain_view - 1, remain_day - 1, temp, 0);
					}
					my_queue.pop_back();
				}
				else{//insert or not
					compute(remain_view - 1, remain_day, temp, 1);

					if(remain_day != 1){
						for(int j = 0; j < hotel_name.size(); j ++){
							my_queue.push_back(hotel_name[j]);
							compute(remain_view - 1, remain_day - 1, temp, 0);
							my_queue.pop_back();
						}
					}
					else{
						compute(remain_view - 1, remain_day - 1, temp, 0);
					}

					my_queue.pop_back();
				}
			}
			else{//insert hotel
				if(remain_day != 1){
					for(int j = 0; j < hotel_name.size(); j ++){
						my_queue.push_back(hotel_name[j]);
						compute(remain_view - 1, remain_day - 1, temp, 0);
						my_queue.pop_back();
					}
				}
				else{
					compute(remain_view - 1, remain_day - 1, temp, 0);
				}
				my_queue.pop_back();
			}
		}
		return;
	}
}

void solve(){
	vector<string> remain_view_name = view_name;

	for(int i = 6; i >= 6; i --){
		cout << i << endl;
		current_plan_day_num = i;
		compute(i, 3, remain_view_name, 0);

		cout << current_plan_day_num << " " << best_day_yuan[current_plan_day_num] << " ";
		fout << current_plan_day_num << " " << best_day_yuan[current_plan_day_num] << " ";
		for(int j = 0; j < best_day_plan[current_plan_day_num].size(); j ++){
			if(j){
				fout << " ==> ";
				cout << " ==> ";
			}
			fout << best_day_plan[current_plan_day_num][j] << " ";
			cout << best_day_plan[current_plan_day_num][j] << " ";
		}
	}
	system("pause");
}

int main(){
	init_B6();
	solve();
	return 0;
}
