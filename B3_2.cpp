#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string trans(int t){
	int a = t / 60;
	int b = t % 60;
	string s1;
	stringstream ss1(s1);
	ss1 << (a + 7);
	string hour = ss1.str();
	cout << hour;

	string s2;
	stringstream ss2(s2);
	ss2 << (b);
	string minu = ss2.str();
	cout << minu;
	if(b < 10)
		minu = "0" + minu;

	return hour + ":" + minu;
}

int main(){
	ifstream fin("output.txt");
	ofstream fout("output_3.txt");

	for(int i = 0; i < 22; i ++){
		string temp;
		fin >> temp;
		fout << "\t" << temp;
	}
	fout << endl;

	for(int i = 0; i < 28; i ++){
		string temp;
		fin >> temp;
		fout << temp;
		for(int j = 0; j < 22; j ++){
			int t;
			fin >> t;
			string result = trans(t);
			fout << "\t" << result;
		}
		fout << endl;
	}
	return 0;
}
