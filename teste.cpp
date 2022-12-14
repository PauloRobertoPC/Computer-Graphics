#include <bits/stdc++.h>
#include <fstream>
#include <sstream>

using namespace std;

std::tuple<double, double, double> read_vertex(string &s){
    stringstream sr(s);
    char ch; double a, b, c; 
    sr >> ch >> a >> b >> c;
    return {a, b, c};
}

std::tuple<double, double, double> read_face(string &s){
    stringstream sr(s);
    char ch; int a, b, c, d;
    sr >> ch;
    sr >> a >> ch >> d >> ch >> d;
    sr >> b >> ch >> d >> ch >> d;
    sr >> c >> ch >> d >> ch >> d;
    return {a, b, c};
}

int main(){
    fstream my_file("chair.obj");
    string s; double x, y, z; int v1, v2, v3;
    while(getline(my_file, s)){
        if(s[0] == 'v' && s[1] == ' ')
            std::tie(x, y, z) = read_vertex(s); 
        else if(s[0] == 'f' && s[1] == ' ')
            std::tie(v1, v2, v3) = read_face(s); 
    }
    my_file.close();
    return 0;
}
