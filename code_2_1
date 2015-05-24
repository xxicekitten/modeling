//
//  main.cpp
//  modeling
//
//  Created by ronghaiyang on 5/20/15.
//  Copyright (c) 2015 ronghaiyang. All rights reserved.
//

/*
 
 不考虑候车时间.
 
 
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <set>

using namespace std;


string toStr(int i){
    stringstream ss;
    //    ss<<i;
    char ch[16];
    sprintf(ch, "%04d",i);
    ss<<ch;
    string s1 = ss.str();
    //    cout<<s1<<endl; // 30
    return s1;
}

/**********************************************/

const int maxn = 1000;

map<string, int> S_to_int;
map<int, string> int_to_S;
int S_to_int_size;

int dist[maxn][maxn];
int path[maxn][maxn];

vector<int> path_name;

void init(){
    S_to_int_size = 0;
    //cout << S_to_int.size();
    memset(dist, 0, sizeof dist);
    memset(path, 0, sizeof path);
}

void input(){
    ifstream fin("/Users/roger/workspace/Game/Study/CPP/B2_1_bukaolv/B2_1_bukaolv/input_1.txt");
    
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

void print_line_split(int a, int b){
    if(path[a][b] > 0){
        print_line_split(a, path[a][b]);
        print_line_split(path[a][b], b);
    }
    else{
        //cout << int_to_S[b] << " ";
        path_name.push_back(b);
    }
}

void print_line(int a, int b){
    path_name.clear();
    
    path_name.push_back(a);
    print_line_split(a, b);
    
    cout << int_to_S[path_name[0]];
    for(int i = 0; i < path_name.size(); i ++){
        if(i){
            //cout << "--" << dist[path_name[i - 1]][path_name[i]] << "--" << int_to_S[path_name[i]];
            cout << "--" << int_to_S[path_name[i]];
        }
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


string print_line_ret(int a,int b){
    //    path_name.clear();
    string ret;
    path_name.clear();
    
    path_name.push_back(a);
    print_line_split(a, b);
    
    ret += int_to_S[path_name[0]];
    for(int i = 0; i < path_name.size(); i ++){
        if(i){
            //cout << "--" << dist[path_name[i - 1]][path_name[i]] << "--" << int_to_S[path_name[i]];
            ret =ret + "--" + int_to_S[path_name[i]];
        }
    }
    return ret;
}

/**********************************************/




typedef struct __V{
    __V(){
        
    }
    
    __V(int _i,int _time,int _startTime,const vector<int>& _s){
        iID = _i;
        time = _time;
        startTime = _startTime;
        _S.assign(_s.begin(),_s.end());
    }
    //    void operator = (const __V&& ref){
    //        this->_S = ref._S;
    //        this->iID = ref.iID;
    //    }
    int iID;        //景点ID
    int time;//游览时间
    int startTime;//0表示8:30-16:30 1表示9:00-17:00
    vector<int> _S; //站点
}_V;

vector<_V> g_vv;

vector<vector<int>> g_result;


/*  组合 */
void print(std::vector<int>& s)
{
    for (auto ite = s.begin(); ite!=s.end(); ++ite) {
        cout<<(*ite)<<" ";
    }
    cout<<endl;
    return;
    
    static int n = 1;
    //         //printf("%d:", n++);
    //         //printf("[");
    
    int c = 0,v = 0;
    
    int cSum =0,vSum = 0;
    
    
    
}

void permutation(std::vector<int>& v, int beg, int end)
{
    if (beg > end) {
        print(v);
        return;
    }
    for (int i = beg; i <= end; i++) {
        std::swap(v[i], v[beg]);
        permutation(v, beg+1, end); // pleate note, here always beg+1, not i+1
        std::swap(v[i], v[beg]);
    }
}

void pm(std::vector<int>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    //printf("\nfull permulation are:\n");
    permutation(v, 0, v.size()-1);
}

void print(const std::vector<int>& v, int beg, int end)
{
    static int n = 1;
    ////printf("%d:", n++);
    //printf("[");
    std::copy(v.begin()+beg, v.begin()+end+1, std::ostream_iterator<int>(std::cout, " "));
    //printf("]\n");
}

void fullcombination(std::vector<int>& v)
{
    //         //printf("full combination are:\n");
    for (unsigned int i = 0; i < v.size(); i++) {
        //                print(v, i, i);
        for (unsigned int j = i+1; j < v.size(); j++) {
            for (int k = 0; k < v.size()-j; k++) {
                std::swap(v[j+k], v[j]);
                //                                 print(v, i, j);
                std::vector<int> vN(v.begin()+i,v.begin()+j+1);
                print(vN);
                
                std::swap(v[j+k], v[j]);
            }
        }
    }
}

//01转换法. 2的22次方
void all_combine(){
    //    for (int i = 0; i < ; <#increment#>) {
    //
    //    }
}

/**/
void initData(){
    
    vector<int> v;
    
    v.clear();v.push_back(0);
    g_vv.push_back( _V(0,0,0,v) );
    
    v.clear();v.push_back(45);
    g_vv.push_back( _V(1,120,0,v) );
    
    v.clear();v.push_back(1171); v.push_back(995);
    g_vv.push_back( _V(2,150,1,v) );
    
    v.clear();v.push_back(25);
    g_vv.push_back( _V(3,210,1,v) );
    
    v.clear();v.push_back(1353);v.push_back(1119);v.push_back(1281);
    g_vv.push_back( _V(4,180,1,v) );
    
    v.clear();v.push_back(897);v.push_back(861);
    g_vv.push_back( _V(5,210,1,v) );
    
    v.clear();v.push_back(771);v.push_back(471);
    g_vv.push_back( _V(6,180,1,v) );
    
    v.clear();v.push_back(881);v.push_back(917);    //v.push_back(1059);
    g_vv.push_back( _V(7,150,1,v) );
    
    v.clear();v.push_back(761);
    g_vv.push_back( _V(8,120,1,v) );
    
    v.clear();v.push_back(757);v.push_back(1187);
    g_vv.push_back( _V(9,240,0,v) );
    
    v.clear();v.push_back(9);
    g_vv.push_back( _V(10,150,0,v) );
    
    v.clear();v.push_back(987);
    g_vv.push_back( _V(11,180,1,v) );
    
    v.clear();v.push_back(237);
    g_vv.push_back( _V(12,180,1,v) );
    
    v.clear();v.push_back(115);
    g_vv.push_back( _V(13,150,0,v) );
    
    v.clear();v.push_back(1049);
    g_vv.push_back( _V(14,210,0,v) );
    
}

#define _max_v 14
void pailie_3(vector<_V>& v){
    
    for(auto i1 = 1 ; i1 <= _max_v ; ++i1){
        for (auto i2 = 1; i2 <= _max_v; ++i2) {
            for (auto i3 = 1; i3 <= _max_v; ++i3) {
                if(i1 == i2 || i1 == i3 || i2 == i3){   // >= 从小到大，1 2 不会出现 2 1，==会出现1 2 ，2 1
                    continue;
                }
                vector<int> vec;
                vec.push_back(i1);
                vec.push_back(i2);
                vec.push_back(i3);
                g_result.push_back(vec);
            }
        }
    }
}
void pailie_2(vector<_V>& v){
    
    for(auto i1 = 1 ; i1 <= _max_v ; ++i1){
        for (auto i2 = 1; i2 <= _max_v; ++i2) {
            if(i1 == i2){
                continue;
            }
            
            vector<int> vec;
            vec.push_back(i1);
            vec.push_back(i2);
            g_result.push_back(vec);
        }
    }
}

void pailie_1(vector<_V>& v){
    
    for(auto i1 = 1 ; i1 <= _max_v ; ++i1){
        
        vector<int> vec;
        vec.push_back(i1);
        g_result.push_back(vec);
    }
}


void compute(){
    const auto zuhe_type_max = g_result.size();
    
    vector<vector<int>> v1[15];//包含v1景点的路线。
    
    for (int kk = 1; kk <= 14; ++kk) {
        for (auto i = 0; i < zuhe_type_max; ++i) {
            for (int j = 0; j < g_result[i].size(); ++j) {
                if(g_result[i][j]==kk)
                    v1[kk].push_back(g_result[i]);
            }
        }
    }
    
    //最多6天
#define max_days 6
}




int busTime(string st,string dt){
    int a,b;
    //    cout<<"---"<<st<<","<<dt<<endl;
    //    a = S_to_int["S0809"];
    //    b = S_to_int["S1121"];
    a = S_to_int[st];
    b = S_to_int[dt];
    //    cout << dist[a][b] << endl;
    //    cout<<st<<","<<dt<<endl;
    assert(dist[a][b]);
    if(dist[a][b]==0)
        dist[a][b] = 999;
    return dist[a][b];
}

int busTime(int st,int dt){
    return busTime("S"+toStr(st) ,"S"+toStr(dt));
}
int busTime(vector<int>& st,vector<int>& dt,string& pRetBestBusRoute){
    int minRouteTime = 9999;
    string busRoute;
    for (auto ite = st.begin(); ite!= st.end(); ++ite) {
        for (auto kk = dt.begin(); kk!= dt.end(); ++kk) {
            int curTime = busTime((*ite), (*kk));
            if (curTime < minRouteTime) {
                minRouteTime = curTime;
                if((*ite)==45)
                    ;
                busRoute = print_line_ret( S_to_int["S"+toStr(*ite)], S_to_int["S"+toStr(*kk)]);
            }
        }
    }
    assert(minRouteTime!=9999);
    assert(minRouteTime!=0);
    
    pRetBestBusRoute = busRoute;
    //    print_line(beg,end);
    return minRouteTime;
}

typedef struct  __day{
    __day(){}
    __day(vector<int> v,int i,string route){
        _route = v;
        _wasteTime = i;
        _strBestRoute = route;
    }
    vector<int> _route; //景点的游览顺序
    string _strBestRoute;//游览景点，最佳坐车顺序。
    int _wasteTime;
    
    __day& operator=(const __day& aObj){
        _route          = aObj._route;
        _strBestRoute   = aObj._strBestRoute;
        _wasteTime      = aObj._wasteTime;
        return *this;
    }

}_day;

vector<_day> days;


int cmp(_day p1,_day  p2)
{
    return p1._wasteTime < p2._wasteTime;
}
//int cmp( const void *a ,const void *b)
//{ return (*(_day*)a)._wasteTime > (*(_day*)b)._wasteTime ? 1 : -1; }


vector<pair<int, int>> g_lushang_tmp;
int cmpLushangTime(pair<int , int> p1,pair<int , int>  p2){
    return p1.first < p2.first;
}


vector<vector<int>> g_fullCombination;
//组合。子集合
void _fullCombination(int num[], int rcd[], int cur, int begin, int n)
{
    int i;
    vector<int> vec;
    for(i=0; i<cur; ++i)
        vec.push_back(rcd[i]);          //printf("%d ", rcd[i]);
    g_fullCombination.push_back(vec);   //printf("\n");
    
    for(i=begin; i<n; ++i)
    {
        rcd[cur] = num[i];
        if(cur+1 <= 4)//最大4个
            _fullCombination(num, rcd, cur+1, i+1, n);
    }
}

//二者是否“一样”（同内容，不同顺序）
bool compareDay(_day a,_day b){
//    return a._wasteTime > b._wasteTime;
    if (a._route.size() != b._route.size()) {
        return false;
    }
    for (auto ite = a._route.begin(); ite!= a._route.end(); ++ite) {
        bool bHas = false;
        for (auto ii = b._route.begin(); ii != b._route.end(); ++ii) {
            if ((*ii) == (*ite)) {
                bHas = true;
                break;
            }
        }
        if (!bHas) {
            return false;
        }
    }
    return true;
}

bool isContain(vector<_day>& vec,_day day) {
    for (auto ite = vec.begin(); ite!= vec.end(); ++ite) {
        if (compareDay((*ite), day)) {
            return true;
        }
    }
    return false;
}
//bool isContain(vector<_day>)

//4个 2景点集合，相互没重复景点。
vector<int> _jingdian_3plus2_6; //3*2 = 6 的景点
bool isNotChongfu_2(vector<int> v1,
                  vector<int> v2,
                  vector<int> v3,
                  vector<int> v4){
    set<int> all;
    all.insert(_jingdian_3plus2_6.begin(),_jingdian_3plus2_6.end());
    all.insert(v1.begin(),v1.end());
    all.insert(v2.begin(),v2.end());
    all.insert(v3.begin(),v3.end());
    all.insert(v4.begin(),v4.end());
    if (all.size() == v1.size() + v2.size() + v3.size() + v4.size() + _jingdian_3plus2_6.size()) {
        return true;
    }
    return false;
}

int main(int argc, const char * argv[]) {
    
    _jingdian_3plus2_6.push_back(1);
    _jingdian_3plus2_6.push_back(2);
    _jingdian_3plus2_6.push_back(7);
    _jingdian_3plus2_6.push_back(13);
    _jingdian_3plus2_6.push_back(12);
    _jingdian_3plus2_6.push_back(8);
    
    /*************/
    
    init();
    input();
    solve();
    //    answer();
    
    
    
    /************/
    // insert code here...
    
    initData();
    
    //赋值到g_result中.1,2,3   4,5,6
    pailie_3(g_vv);
    pailie_2(g_vv);
    pailie_1(g_vv);
    
    
    
    cout<<g_result.size();
    
    
    std::cout << "************************"<<endl;
    //    compute();
    
    
    //剪枝
    for (auto ite = g_result.begin(); ite!=g_result.end(); ++ite) {
        int iWasteTime = 0;
        
        string strBestBusRoute1;
        string strBestBusRoute2;
        
        //ite某一天，ii某一景点
        auto ii = (*ite).begin();
        
        int lushang = 0;
        if((*ite).size() == 3){
            lushang += busTime(g_vv[(*ii)]._S,   g_vv[(*(ii+1))]._S  ,strBestBusRoute1);
            lushang += busTime(g_vv[*(ii+1)]._S, g_vv[(*(ii+2))]._S  ,strBestBusRoute2);
        }else if((*ite).size() == 2){
            lushang += busTime(g_vv[(*ii)]._S,   g_vv[(*(ii+1))]._S  ,strBestBusRoute1);
        }else{
            lushang = 0;
        }
        
        iWasteTime += lushang;
        
//        g_lushang_tmp.push_back(pair<int, int>(routeTime, (*ite).size()) );
        
        int time_ = 0 ;
        for (auto j = (*ite).begin(); j < (*ite).end(); ++j) {
            time_ += g_vv[(*j)].time; // 游览
        }
        
        //确定一天时长
        int limit = 480;
        if((*ite).size()==3){
            if(
               g_vv[(*ite)[0]].startTime == 0 &&
               g_vv[(*ite)[2]].startTime == 1
               ){
                limit = 480 + 30;
            }else if(
                     g_vv[(*ite)[0]].startTime == 1 &&
                     g_vv[(*ite)[2]].startTime == 0
                     ){
                limit = 480 - 30;
            }else{
                limit = 480;
            }
        }else if((*ite).size()==2){
            if(
               g_vv[(*ite)[0]].startTime == 0 &&
               g_vv[(*ite)[1]].startTime == 1
               ){
                limit = 480 + 30;
            }else if(
                     g_vv[(*ite)[0]].startTime == 1 &&
                     g_vv[(*ite)[1]].startTime == 0
                     ){
                limit = 480 - 30;
            }else{
                limit = 480;
            }
        }else{
            limit = 480;
        }
        
        iWasteTime = limit - time_  - lushang;  //总 - 游览 = 闲+路上，指导函数
        
        if(limit - time_ - lushang >= 0){  //总 - 游览 - 路上 = 闲。闲>=0 表示有效,剪枝
            days.push_back(
                           _day((*ite),
                                iWasteTime,
                                strBestBusRoute1 +" # "+strBestBusRoute2));
            
         
        }
    }
    
    //剪枝2. 除掉重复的，留下重复的中空闲时间最大的。 （当天总时间 - 路上时间 -  游览时间）
    vector<_day> newDays;
    for (auto ite = days.begin(); ite!= days.end(); ++ite) {
        _day bestDay = (*ite);
        if (isContain(newDays,(*ite))) {
            continue;
        }
        for (auto ii = ite+1 ; ii != days.end(); ++ii) {
//            if(isContain(newDays,(*ii)))
//               continue;
            if(compareDay((*ii),bestDay) && (*ii)._wasteTime > bestDay._wasteTime){
                bestDay = (*ii);
            }
        }
        newDays.push_back(bestDay);
    }
    days = newDays;
    //End
    
    
    //是否排序by iWasteTime
    //    sort(days.begin(),days.end(),cmp);
    
    for (auto iz = days.begin(); iz != days.end(); ++iz) {
        //        cout<<"waste time:"<<(*iz)._wasteTime<<endl;
//        cout<<"route:";
        for (auto ix = (*iz)._route.begin(); ix != (*iz)._route.end(); ++ix) {
            cout<<(*ix)<<",";
        }
        cout<<endl;
//        cout<<"waste:"<<(*iz)._wasteTime<<endl;
        //        cout<<"BusRoute:"<<(*iz)._strBestRoute<<endl;
        
        //        print_line(45,1119);
    }
    
  
    //把 2 个景点的天，拿出来。
    vector<_day> day_2v;
    for (auto ite = days.begin(); ite != days.end(); ++ite) {
        if ((*ite)._route.size()==2) {
            day_2v.push_back((*ite));
        }
    }
//    cout<<day_2v.size()<<endl;
    
     unsigned int max_ele = (unsigned int)day_2v.size();
    
     int num[max_ele];
     int rcd[2000];
     for (int i = 0 ; i < max_ele; ++i) {
         num[i] = i;
     }
     g_fullCombination.clear();
     _fullCombination(num, rcd, 0, 0, max_ele);
    
    
    //8景点集合.由2景点*4构成
    vector<vector<int>> _vec_8jingdian;
    
    for (auto ite = g_fullCombination.begin(); ite!= g_fullCombination.end(); ++ite) {
        if((*ite).size()!=4)
            continue;
   
        //4组  2景点组合，均无重复
        if(isNotChongfu_2(day_2v[(*ite)[0]]._route,
                       day_2v[(*ite)[1]]._route,
                       day_2v[(*ite)[2]]._route,
                       day_2v[(*ite)[3]]._route)
           ){
            vector<int> v8;
            for (int i=0; i<4; ++i) {
                for (int j=0; j<2; ++j) {
                    v8.push_back(day_2v[(*ite)[i]]._route[j]);
//                    cout<<day_2v[(*ite)[i]]._route[j]<<",";
                }
            }
            _vec_8jingdian.push_back(v8);
//            cout<<endl;
        }
    }
    
    cout<<"size:"<<_vec_8jingdian.size()<<endl;
    int iii=0;
    for (auto i = _vec_8jingdian.begin(); i!= _vec_8jingdian.end(); ++i) {
        cout<<"#";
        iii = 0;
        for (auto j = (*i).begin(); j != (*i).end(); ++j) {
            cout<<(*j);
            if(iii==7)
                continue;
            if((++iii)%2 ==0)
                cout<<"--";
            else
                cout<<",";
        }
        cout<<endl;
    }
  
    
    
    
    std::cout << "Hello, World!\n";
  
    
    
    return 0;
}


