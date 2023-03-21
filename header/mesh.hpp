#ifndef MESH_HPP
#define MESH_HPP

#include "object.hpp"
#include <vector>
#include <tuple>

class mesh : public object
{
private:
    bool invert_normal;
    void mirror(matrix M);
    void shear(matrix M);

protected:
    class vertex
    {
    private:
        vp *pos;

    public:
        bool operator<(vertex b);
        vertex();
        vertex(vp *pos);
        vp *get_pos();
        void set_pos(vp *pos);
    };

    class edge
    {
    private:
        vertex *u, *v;

    public:
        edge();
        edge(vertex *&u, vertex *&v);
        vertex *get_u();
        void set_u(vertex *u);
        vertex *get_v();
        void set_v(vertex *v);
    };

    class face
    {
    private:
        vertex *a, *b, *c;
        vp normal;

    public:
        face();
        face(edge *&a, edge *&b, edge *&c);
        face(vertex *&a, vertex *&b, vertex *&c);

        bool in_face(vp P);
        std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max);
        std::tuple<vertex *, vertex *, vertex *> counter_clocwise_vertices(edge *a, edge *b, edge *c);
        vertex *get_a();
        vertex *get_b();
        vertex *get_c();
        vp get_normal();
        void set_normal(vp normal);
        void update_normal(bool invert = false);
    };

    vp center;
    std::vector<vertex *> vertices;
    std::vector<edge *> edges;
    std::vector<face *> faces;

public:
    mesh();
    mesh(vp center, px k_a, px k_d, px k_s, double s, double reflective);
    mesh(vp center, const char *name, double s, double reflective);

    virtual std::tuple<double, vp> intersection_with_ray(vp O, vp D, double t_min, double t_max);

    void update_normals();

    // transformations
    void transform();
    void to_camera(vp M);
    void shear_xy(double angle);
    void shear_yx(double angle);
    void shear_xz(double angle);
    void shear_zx(double angle);
    void shear_yz(double angle);
    void shear_zy(double angle);
    void mirror_xy();
    void mirror_xz();
    void mirror_yz();
    void mirror_arbitrary(vp n, vp p);
    void to_camera(matrix M);
};

#endif
