#include "../header/comparator.hpp"
#include "../header/cube.hpp"
#include "../header/matrix.hpp"

cube::cube() : mesh(vp(0, 0, 0), px(), px(), px(), 1, 0) { make_cube(); }
cube::cube(px k_a, px k_d, px k_s, double s, double reflective) : mesh(vp(0, 0, 0), k_a, k_d, k_s, s, reflective)
{
    make_cube();
}

cube::cube(const char *name, double s, double reflective) : mesh(vp(0, 0, 0), name, s, reflective)
{
    make_cube();
}

vp cube::get_def_point() { return this->center; }

void cube::scaling(vp S)
{ // length, height, width
    vp P = this->get_def_point();
    vp N(S.get_x() / this->height, S.get_y() / this->width, S.get_z() / this->length);
    this->transformations = matrix::scaling_matrix(N) * this->transformations;
    this->transform();
    this->height = S.get_x();
    this->width = S.get_y();
    this->length = S.get_z();
    this->translation(P);
}

void cube::make_cube()
{
    this->width = this->length = this->height = 1;
    // Vertices
    this->vertices.push_back(new vertex(new vp(-0.5, -0.5, +0.5)));
    this->vertices.push_back(new vertex(new vp(+0.5, -0.5, +0.5)));
    this->vertices.push_back(new vertex(new vp(+0.5, +0.5, +0.5)));
    this->vertices.push_back(new vertex(new vp(-0.5, +0.5, +0.5)));
    this->vertices.push_back(new vertex(new vp(-0.5, +0.5, -0.5)));
    this->vertices.push_back(new vertex(new vp(-0.5, -0.5, -0.5)));
    this->vertices.push_back(new vertex(new vp(+0.5, -0.5, -0.5)));
    this->vertices.push_back(new vertex(new vp(+0.5, +0.5, -0.5)));
    // Faces
    this->faces.push_back(new face(this->vertices[0], this->vertices[1], this->vertices[3]));
    this->faces.push_back(new face(this->vertices[1], this->vertices[2], this->vertices[3]));
    this->faces.push_back(new face(this->vertices[1], this->vertices[6], this->vertices[2]));
    this->faces.push_back(new face(this->vertices[2], this->vertices[6], this->vertices[7]));
    this->faces.push_back(new face(this->vertices[5], this->vertices[7], this->vertices[6]));
    this->faces.push_back(new face(this->vertices[5], this->vertices[4], this->vertices[7]));
    this->faces.push_back(new face(this->vertices[0], this->vertices[4], this->vertices[5]));
    this->faces.push_back(new face(this->vertices[3], this->vertices[4], this->vertices[0]));
    this->faces.push_back(new face(this->vertices[4], this->vertices[2], this->vertices[7]));
    this->faces.push_back(new face(this->vertices[4], this->vertices[3], this->vertices[2]));
    this->faces.push_back(new face(this->vertices[0], this->vertices[5], this->vertices[1]));
    this->faces.push_back(new face(this->vertices[1], this->vertices[5], this->vertices[6]));
}
