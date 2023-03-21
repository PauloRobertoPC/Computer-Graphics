#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include "../header/comparator.hpp"
#include "../header/complex_object.hpp"
#include "../header/matrix.hpp"

std::tuple<double, double, double> read_vertex(std::string &s)
{
    std::stringstream sr(s);
    char ch;
    double a, b, c;
    sr >> ch >> a >> b >> c;
    return {a, b, c};
}

std::tuple<double, double, double> read_face(std::string &s)
{
    std::stringstream sr(s);
    char ch;
    int a, b, c, d;
    sr >> ch;
    sr >> a >> ch >> d >> ch >> d;
    sr >> b >> ch >> d >> ch >> d;
    sr >> c >> ch >> d >> ch >> d;
    return {a, b, c};
}

std::tuple<int, int, int> read_face2(std::string &s)
{
    std::stringstream sr(s);
    char ch;
    int a, b, c;
    sr >> ch >> a >> b >> c;
    return {a, b, c};
}

complex_object::complex_object(std::string name, px k_a, px k_d, px k_s, double s, double reflective) : mesh(vp(0, 0, 0), k_a, k_d, k_s, s, reflective)
{
    std::fstream my_file(name);
    std::string line;
    double x, y, z;
    int v1, v2, v3;
    int c = 0;
    double mx = INF, my = INF, mz = INF, Mx = -INF, My = -INF, Mz = -INF, ax = 0, ay = 0, az = 0;
    while (std::getline(my_file, line))
    {
        if (line[0] == 'v' && line[1] == ' ')
        {
            std::tie(x, y, z) = read_vertex(line);
            this->vertices.push_back(new vertex(new vp(x, y, z)));
            mx = std::min(mx, x);
            my = std::min(my, y);
            mz = std::min(mz, z);
            Mx = std::max(Mx, x);
            My = std::max(My, y);
            Mz = std::max(Mz, z);
            ax += x;
            ay += y;
            az += z;
            ++c;
        }
        else if (line[0] == 'f' && line[1] == ' ')
        {
            std::tie(v1, v2, v3) = read_face2(line);
            this->faces.push_back(new face(this->vertices[v1 - 1], this->vertices[v2 - 1], this->vertices[v3 - 1]));
        }
    }
    my_file.close();

    this->height = Mx - mx;
    this->width = My - my;
    this->length = Mz - mz;
    this->center = vp(ax / c, ay / c, az / c);
    // cluster
    this->cluster = new cube();
    this->cluster->scaling(vp(this->height + 20, this->width + 20, this->length + 20));
    this->cluster->translation(this->center);
}

std::tuple<double, vp> complex_object::intersection_with_ray(vp O, vp D, double t_min, double t_max)
{
    // testing interrsection with cluster
    double t;
    vp n;
    std::tie(t, n) = this->cluster->intersection_with_ray(O, D, t_min, t_max);
    if (t == INF)
        return {t, n};
    return this->mesh::intersection_with_ray(O, D, t_min, t_max);
}

vp complex_object::get_def_point() { return this->center; }

void complex_object::scaling(vp S)
{
    vp P = this->get_def_point();
    vp N(S.get_x() / this->height, S.get_y() / this->width, S.get_z() / this->length);
    this->transformations = matrix::scaling_matrix(N) * this->transformations;
    this->transform();
    this->height = S.get_x();
    this->width = S.get_y();
    this->length = S.get_z();
    this->translation(P);

    this->cluster->scaling(vp(this->height + 1, this->width + 1, this->length + 1));
    this->cluster->translation(this->center);
}

void complex_object::translation(vp P, bool point)
{
    this->mesh::translation(P, point);
    this->cluster->translation((point ? this->center : P), point);
}

void complex_object::rotation_x(double angle)
{
    this->mesh::rotation_x(angle);
    this->cluster->rotation_x(angle);
    this->cluster->translation(this->center);
}

void complex_object::rotation_y(double angle)
{
    this->mesh::rotation_y(angle);
    this->cluster->rotation_y(angle);
    this->cluster->translation(this->center);
}

void complex_object::rotation_z(double angle)
{
    this->mesh::rotation_z(angle);
    this->cluster->rotation_z(angle);
    this->cluster->translation(this->center);
}

void complex_object::rotate_arbitrary(vp o, vp direction, double angle)
{
    this->mesh::rotate_arbitrary(o, direction, angle);
    this->cluster->rotate_arbitrary(o, direction, angle);
    this->cluster->translation(this->center);
}

void complex_object::shear_xy(double angle)
{
    this->mesh::shear_xy(angle);
    this->cluster->shear_xy(angle);
    this->cluster->translation(this->center);
}

void complex_object::shear_yx(double angle)
{
    this->mesh::shear_yx(angle);
    this->cluster->shear_yx(angle);
    this->cluster->translation(this->center);
}

void complex_object::shear_xz(double angle)
{
    this->mesh::shear_xz(angle);
    this->cluster->shear_xz(angle);
    this->cluster->translation(this->center);
}

void complex_object::shear_zx(double angle)
{
    this->mesh::shear_zx(angle);
    this->cluster->shear_zx(angle);
    this->cluster->translation(this->center);
}

void complex_object::shear_yz(double angle)
{
    this->mesh::shear_yz(angle);
    this->cluster->shear_yz(angle);
    this->cluster->translation(this->center);
}

void complex_object::shear_zy(double angle)
{
    this->mesh::shear_zy(angle);
    this->cluster->shear_zy(angle);
    this->cluster->translation(this->center);
}

void complex_object::mirror_xy()
{
    this->mesh::mirror_xy();
    this->cluster->mirror_xy();
    this->cluster->translation(this->center);
}

void complex_object::mirror_xz()
{
    this->mesh::mirror_xz();
    this->cluster->mirror_xz();
    this->cluster->translation(this->center);
}

void complex_object::mirror_yz()
{
    this->mesh::mirror_yz();
    this->cluster->mirror_yz();
    this->cluster->translation(this->center);
}

void complex_object::mirror_arbitrary(vp n, vp p)
{
    this->mesh::mirror_arbitrary(n, p);
    this->cluster->mirror_arbitrary(n, p);
    this->cluster->translation(this->center);
}

void complex_object::to_camera(matrix M)
{
    this->mesh::to_camera(M);
    this->cluster->to_camera(M);
}
