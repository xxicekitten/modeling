#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <map>
#include <vector>

using namespace std;

const int maxn = 1000;

map<string, int> S_to_int;
map<int, string> int_to_S;
int S_to_int_size;

int dist[maxn][maxn];
int path[maxn][maxn];

void init(){
	S_to_int_size = 0;
	//cout << S_to_int.size();
	memset(dist, 0, sizeof dist);
	memset(path, 0, sizeof path);
}

void input(){
	ifstream fin("input_1.txt");

	int yuan;
	while(fin >> yuan){
		string line;
		fin >> line;
		//cout << line << endl;

		vector<string> split_line;
		//std::size_t found = line.find("-");
		//while(found != std::string::npos){
		while(line.size() > 5){
			string temp = line.substr(0, 5);
			split_line.push_back(temp);
			line = line.substr(6);
		}
		split_line.push_back(line);

		for(int i = 0; i < split_line.size(); i ++){
			if(S_to_int.find(split_line[i]) == S_to_int.end()){
				S_to_int.insert(pair<string, int>(split_line[i], S_to_int_size));
				int_to_S.insert(pair<int, string>(S_to_int_size, split_line[i]));
				S_to_int_size ++;
			}
			//cout << split_line[i] << " ";

			if(i){
				int a, b;
				a = S_to_int[split_line[i - 1]];
				b = S_to_int[split_line[i]];

				//cout << a << " " << b << endl;
				
				if(dist[a][b] == 5){
					if(yuan == 3){
						dist[a][b] = dist[b][a] = 5;
					}
					else{
						dist[a][b] = dist[b][a] = 3;
					}
				}
				if(dist[a][b] == 3){
					//do nothing
				}
				else{
					if(yuan == 3){
						dist[a][b] = dist[b][a] = 5;
					}
					else{
						dist[a][b] = dist[b][a] = 3;
					}
				}
				//system("pause");
			}
		}
		//cout << endl;
	}

	//cout << S_to_int.size() << endl;
	//cout << S_to_int_size << endl;

	//system("pause");
}

void solve(){
	//cou << S_to_int_size << endl;
	for(int k = 0; k < S_to_int_size; k ++){
		for(int i = 0; i < S_to_int_size; i ++){
			if(dist[i][k] > 0){
				for(int j = 0; j < S_to_int_size; j ++){
					if(i == j){
						continue;
					}
					if(dist[k][j] > 0){
						if((dist[i][j] > dist[i][k] + dist[k][j]) || (dist[i][j] == 0)){
							dist[i][j] = dist[i][k] + dist[k][j];
							//dist[j][i] = dist[i][k] + dist[k][j];
							path[i][j] = k;
						}
					}
				}
			}
		}
	}

	cout << "solve complete" << endl;
}

void print_line(int a, int b){
	if(path[a][b] > 0){
		print_line(a, path[a][b]);
		print_line(path[a][b], b);
	}
	else{
		cout << int_to_S[b] << " ";
	}
}

void answer(){
	string st, ed;
	int a, b;
	/*
	st = "S0045";
	ed = "S0881";
	a = S_to_int[st];
	b = S_to_int[ed];

	cout << dist[a][b] << endl;
	print_line(a, b);
	cout << endl;
	*/

	while(cin >> st >> ed){
		a = S_to_int[st];
		b = S_to_int[ed];
		cout << dist[a][b] << endl;

		print_line(a, b);
		cout << endl;
	}
}

int main(){
	init();
	input();
	solve();
	answer();
	return 0;
}
