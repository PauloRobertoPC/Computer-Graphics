#include <fstream>
#include <sstream>
#include "../header/comparator.hpp"
#include "../header/complex_object.hpp"
#include "../header/matrix.hpp"

std::tuple<double, double, double> read_vertex(std::string &s){
    std::stringstream sr(s);
    char ch; double a, b, c; 
    sr >> ch >> a >> b >> c;
    return {a, b, c};
}

std::tuple<double, double, double> read_face(std::string &s){
    std::stringstream sr(s);
    char ch; int a, b, c, d;
    sr >> ch;
    sr >> a >> ch >> d >> ch >> d;
    sr >> b >> ch >> d >> ch >> d;
    sr >> c >> ch >> d >> ch >> d;
    return {a, b, c};
}

std::tuple<int, int, int> read_face2(std::string &s){
    std::stringstream sr(s);
    char ch; int a, b, c; 
    sr >> ch >> a >> b >> c;
    return {a, b, c};
}

complex_object::complex_object(std::string name, px k_a, px k_d, px k_s, double s) :  mesh(vp(0, 0, 0), k_a, k_d, k_s, s){
    std::fstream my_file(name);
    std::string line; double x, y, z; int v1, v2, v3;
    int c = 0;
    double mx = INF, my = INF, mz = INF, Mx = -INF, My = -INF, Mz = -INF, ax = 0, ay = 0, az = 0;
    while(std::getline(my_file, line)){
        if(line[0] == 'v' && line[1] == ' '){
            std::tie(x, y, z) = read_vertex(line); 
            this->vertices.push_back(new vertex(new vp(x, y, z)));
            mx = std::min(mx, x); my = std::min(my, y); mz = std::min(mz, z);
            Mx = std::max(Mx, x); My = std::max(My, y); Mz = std::max(Mz, z);
            ax += x; ay += y; az += z; ++c;
        }else if(line[0] == 'f' && line[1] == ' '){
            std::tie(v1, v2, v3) = read_face2(line); 
            this->faces.push_back(new face(this->vertices[v1-1], this->vertices[v2-1], this->vertices[v3-1]));
        }
    }
    this->height = Mx - mx;
    this->width = My - my;
    this->length = Mz - mz;
    std::cout << height << " " << width << " " << length << "\n";
    this->center = vp(ax/c, ay/c, az/c);
    my_file.close();
}

vp complex_object::get_def_point(){ return this->center; }

void complex_object::scaling(vp S){ //length, height, width
    vp P = this->get_def_point();
    vp N(S.get_x()/this->height, S.get_y()/this->width, S.get_z()/this->length);  
    this->transformations = matrix::scaling_matrix(N)*this->transformations; 
    this->transform();
    this->height = S.get_x(); this->width = S.get_y(); this->length = S.get_z();
    this->translation(P);
}
