#include <set>
#include "../header/comparator.hpp"
#include "../header/plan.hpp"
#include "../header/mesh.hpp"

mesh::mesh(){}
mesh::mesh(vp center, px k_a, px k_d, px k_s, double s) :
    center(center), object(k_a, k_d, k_s, s){}

std::tuple<double, vp> mesh::intersection_with_ray(vp O, vp D, double t_min, double t_max){
    double t = INF, taux; vp n, naux;
    for(face* f:faces){
        std::tie(taux, naux) = f->intersection_with_ray(O, D, t_min, t_max);
        if(comparator::g(taux, t_min) && comparator::l(taux, t_max) && comparator::l(taux, t))
            t = taux, n = naux; 
    }
    return {t, n};
}

mesh::vertex::vertex(){ this->pos = new vp(); }
mesh::vertex::vertex(vp *pos) : pos(pos){}
vp* mesh::vertex::get_pos(){ return this->pos; }
void mesh::vertex::set_pos(vp *pos){ this->pos = pos; }
bool mesh::vertex::operator<(vertex b){
    return true;    
}

mesh::edge::edge(){ this->u = this->v = nullptr; }
mesh::edge::edge(vertex *&u, vertex *&v): u(u), v(v){}
mesh::vertex* mesh::edge::get_u(){ return this->u; }
void mesh::edge::set_u(vertex *u){ this->u = u; }
mesh::vertex* mesh::edge::get_v(){ return this->v; }
void mesh::edge::set_v(vertex *v){ this->v = v; }

mesh::face::face(){ this->a = this->b = this->c = nullptr; }

mesh::face::face(vertex *&a, vertex *&b, vertex *&c){
    //TODO:: Colocar Pontos em Ordem Anti-Horária
    this->a = a; this->b = b; this->c = c;
    //Calculating normal
    this->normal = ((*this->b->get_pos())-(*this->a->get_pos()))%((*this->c->get_pos())-(*this->a->get_pos()));
    if(comparator::neq(~(this->normal), 0.0)) this->normal = this->normal/~(this->normal);
}

mesh::face::face(edge *&a, edge *&b, edge *&c){
    //TODO:: Colocar Pontos em Ordem Anti-Horária
    std::tie(this->a, this->b, this->c) = counter_clocwise_vertices(a, b, c); 
    //Calculating normal
    this->normal = ((*this->b->get_pos())-(*this->a->get_pos()))%((*this->c->get_pos())-(*this->a->get_pos()));
    if(comparator::neq(~(this->normal), 0.0)) this->normal/~(this->normal);
}

std::tuple<mesh::vertex*, mesh::vertex*, mesh::vertex*> mesh::face::counter_clocwise_vertices(edge* a, edge* b, edge* c){
    std::set<vertex*> cj; 
    cj.insert(a->get_u()); cj.insert(a->get_v());
    cj.insert(b->get_u()); cj.insert(b->get_v());
    cj.insert(c->get_u()); cj.insert(c->get_v());
    std::vector<vertex*> points;
    for(vertex* x:cj) points.push_back(x);
    return {points[0], points[1], points[2]};
}

bool mesh::face::in_face(vp P){
    vp N = ((*this->b->get_pos())-(*this->a->get_pos()))%((*this->c->get_pos())-(*this->a->get_pos()));
    double a1 = ((*this->a->get_pos()-P)%(*this->b->get_pos()-P))*(this->get_normal()/(~N));
    double a2 = ((*this->b->get_pos()-P)%(*this->c->get_pos()-P))*(this->get_normal()/(~N));
    double a3 = 1 - a1 - a2;
    // std::cout << "P: "; P.print();
    // std::cout << a1 << " " << a2 << " " << a3 << "\n";
    return (comparator::geq(a1, 0.0) && comparator::geq(a2, 0.0) && comparator::geq(a3, 0.0));
}

std::tuple<double, vp> mesh::face::intersection_with_ray(vp O, vp D, double t_min, double t_max){
    if(comparator::g(D*this->get_normal(), 0.0)) return {INF, vp()};
    plan p(*(this->a->get_pos()), this->get_normal());
    double t; vp aux; std::tie(t, aux) = p.intersection_with_ray(O, D, t_min, t_max);
    vp P = (O + D*t);
    t = (in_face(P) ? t : INF);
    return {t, this->get_normal()};
}
    
vp mesh::face::get_normal(){ return this->normal; }
void mesh::face::set_normal(vp normal){ this->normal = normal; }
