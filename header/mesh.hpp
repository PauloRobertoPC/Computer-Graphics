#ifndef MESH_HPP
#define MESH_HPP

#include "object.hpp"
#include <vector>
#include <tuple>

class mesh : public object {
    protected:
        class vertex{
            private:
                vp *pos;
            public:
                bool operator<(vertex b);
                vertex();
                vertex(vp *pos);
                vp* get_pos();
                void set_pos(vp *pos);
        };

        class edge{
            private:
                vertex *u, *v;         
            public:
                edge();
                edge(vertex *&u, vertex *&v);
                vertex* get_u();
                void set_u(vertex *u);
                vertex* get_v();
                void set_v(vertex *v);
        };

        class face{
            private:
                vertex *a, *b, *c;
                vp normal;
            public:
                
                face();
                face(edge *&a, edge *&b, edge *&c);
                face(vertex *&a, vertex *&b, vertex *&c);
                
                bool in_face(vp P);
                std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max);
                std::tuple<vertex*, vertex*, vertex*> counter_clocwise_vertices(edge* a, edge* b, edge* c);
                vertex* get_a(); 
                vertex* get_b(); 
                vertex* get_c(); 
                vp get_normal();
                void set_normal(vp normal);
        };
    
        vp center;
        std::vector<vertex*> vertices;
        std::vector<edge*> edges;
        std::vector<face*> faces;
    
    public:

        mesh(); 
        mesh(vp center, px k_a, px k_d, px k_s, double s);
        
        std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max);
    
};

#endif
