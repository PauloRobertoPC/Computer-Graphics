#include <fstream>
#include <sstream>
#include <set>
#include "../header/comparator.hpp"
#include "../header/plan.hpp"
#include "../header/mesh.hpp"

mesh::mesh() {}
mesh::mesh(vp center, px k_a, px k_d, px k_s, double s, double reflective) : center(center), object(k_a, k_d, k_s, s, reflective)
{
    invert_normal = false;
}
mesh::mesh(vp center, const char *name, double s, double reflective) : center(center), object(name, s, reflective)
{
    invert_normal = false;
}

std::tuple<double, vp> mesh::intersection_with_ray(vp O, vp D, double t_min, double t_max)
{
    double t = INF, taux;
    vp n, naux;
    for (face *f : faces)
    {
        std::tie(taux, naux) = f->intersection_with_ray(O, D, t_min, t_max);
        if (comparator::g(taux, t_min) && comparator::l(taux, t_max) && comparator::l(taux, t))
            t = taux, n = naux;
    }
    return {t, n};
}

mesh::vertex::vertex() { this->pos = new vp(); }
mesh::vertex::vertex(vp *pos) : pos(pos) {}
vp *mesh::vertex::get_pos() { return this->pos; }
void mesh::vertex::set_pos(vp *pos) { this->pos = pos; }
bool mesh::vertex::operator<(vertex b)
{
    return true;
}

mesh::edge::edge() { this->u = this->v = nullptr; }
mesh::edge::edge(vertex *&u, vertex *&v) : u(u), v(v) {}
mesh::vertex *mesh::edge::get_u() { return this->u; }
void mesh::edge::set_u(vertex *u) { this->u = u; }
mesh::vertex *mesh::edge::get_v() { return this->v; }
void mesh::edge::set_v(vertex *v) { this->v = v; }

mesh::face::face() { this->a = this->b = this->c = nullptr; }

mesh::face::face(vertex *&a, vertex *&b, vertex *&c)
{
    // TODO:: Colocar Pontos em Ordem Anti-Horária
    this->a = a;
    this->b = b;
    this->c = c;
    // Calculating normal
    this->normal = ((*this->b->get_pos()) - (*this->a->get_pos())) % ((*this->c->get_pos()) - (*this->a->get_pos()));
    if (comparator::neq(~(this->normal), 0.0))
        this->normal = this->normal / ~(this->normal);
}

mesh::face::face(edge *&a, edge *&b, edge *&c)
{
    // TODO:: Colocar Pontos em Ordem Anti-Horária
    std::tie(this->a, this->b, this->c) = counter_clocwise_vertices(a, b, c);
    // Calculating normal
    this->normal = ((*this->b->get_pos()) - (*this->a->get_pos())) % ((*this->c->get_pos()) - (*this->a->get_pos()));
    if (comparator::neq(~(this->normal), 0.0))
        this->normal = this->normal / ~(this->normal);
}

std::tuple<mesh::vertex *, mesh::vertex *, mesh::vertex *> mesh::face::counter_clocwise_vertices(edge *a, edge *b, edge *c)
{
    std::set<vertex *> cj;
    cj.insert(a->get_u());
    cj.insert(a->get_v());
    cj.insert(b->get_u());
    cj.insert(b->get_v());
    cj.insert(c->get_u());
    cj.insert(c->get_v());
    std::vector<vertex *> points;
    for (vertex *x : cj)
        points.push_back(x);
    return {points[0], points[1], points[2]};
}

bool mesh::face::in_face(vp P)
{

    vp N = this->get_normal();

    double area_total = ((*this->get_b()->get_pos() - *this->get_a()->get_pos()) % (*this->get_c()->get_pos() - *this->get_a()->get_pos())) * N;

    double a1 = ((*this->get_a()->get_pos() - P) % (*this->get_b()->get_pos() - P) * N) / area_total;
    double a2 = ((*this->get_c()->get_pos() - P) % (*this->get_a()->get_pos() - P) * N) / area_total;
    double a3 = 1 - a1 - a2;

    return (comparator::geq(a1, 0.0) && comparator::geq(a2, 0.0) && comparator::geq(a3, 0.0));
}

std::tuple<double, vp> mesh::face::intersection_with_ray(vp O, vp D, double t_min, double t_max)
{
    if (comparator::g(D * this->get_normal(), 0.0))
        return {INF, vp()};
    plan p(*(this->a->get_pos()), this->get_normal());
    double t;
    vp aux;
    std::tie(t, aux) = p.intersection_with_ray(O, D, t_min, t_max);
    vp P = (O + D * t);
    t = (in_face(P) ? t : INF);
    return {t, this->get_normal()};
}

mesh::vertex *mesh::face::get_a() { return this->a; }
mesh::vertex *mesh::face::get_b() { return this->b; }
mesh::vertex *mesh::face::get_c() { return this->c; }
vp mesh::face::get_normal() { return this->normal; }
void mesh::face::set_normal(vp normal) { this->normal = normal; }

void mesh::face::update_normal(bool invert)
{
    vp normal = ((*this->get_b()->get_pos()) - (*this->get_a()->get_pos())) % ((*this->get_c()->get_pos()) - (*this->get_a()->get_pos()));
    if (comparator::neq(~(normal), 0.0))
        normal = normal / ~(normal);
    if (invert)
        normal = normal * (-1);
    this->set_normal(normal);
}

void mesh::update_normals()
{
    for (face *f : this->faces)
        f->update_normal(this->invert_normal);
}

void mesh::to_camera(matrix M)
{
    this->transformations = M * this->transformations;
    this->transform();
}

void mesh::transform()
{
    if (this->transformations == matrix::identity(4))
        return;

    this->center = (this->transformations * matrix::vp_to_matrix(this->center)).matrix_to_vp();

    for (vertex *&v : this->vertices)
    {
        vp p = (this->transformations * matrix::vp_to_matrix(*v->get_pos())).matrix_to_vp();
        v->get_pos()->set_x(p.get_x());
        v->get_pos()->set_y(p.get_y());
        v->get_pos()->set_z(p.get_z());
    }

    this->update_normals();

    transformations = matrix::identity(4);
}

void mesh::shear(matrix M)
{
    vp T = this->get_def_point();
    this->transformations = M * this->transformations;
    this->transform();
    this->translation(T);
}
void mesh::shear_xy(double angle) { shear(matrix::shear_xy(angle)); }
void mesh::shear_yx(double angle) { shear(matrix::shear_yx(angle)); }
void mesh::shear_xz(double angle) { shear(matrix::shear_xz(angle)); }
void mesh::shear_zx(double angle) { shear(matrix::shear_zx(angle)); }
void mesh::shear_yz(double angle) { shear(matrix::shear_yz(angle)); }
void mesh::shear_zy(double angle) { shear(matrix::shear_zy(angle)); }

void mesh::mirror(matrix M)
{
    this->invert_normal ^= 1;
    this->transformations = M;
    this->transform();
}
void mesh::mirror_xy() { mirror(matrix::mirroringXY_matrix()); }
void mesh::mirror_xz() { mirror(matrix::mirroringXZ_matrix()); }
void mesh::mirror_yz() { mirror(matrix::mirroringYZ_matrix()); }
void mesh::mirror_arbitrary(vp n, vp p) { mirror(matrix::mirror_arbitrary_matrix(n, p)); }
