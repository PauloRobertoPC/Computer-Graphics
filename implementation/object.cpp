#include "../header/object.hpp"
#include "../header/stb_image.hpp"
#include "../header/stb_image_write.hpp"

object::object() {}
object::object(px k_a, px k_d, px k_s, double specular, double reflective) : k_a(k_a), k_d(k_d), k_s(k_s), specular(specular), reflective(reflective)
{
    this->has_image = false;
    this->transformations = matrix::identity(4);
}

object::object(const char *name, double s, double reflective)
{
    this->transformations = matrix::identity(4);
    this->has_image = true;
    this->specular = s;
    this->reflective = reflective;
    int chanel;
    int8 *imageR = stbi_load(name, &this->width, &this->height, &chanel, 0);
    if (imageR == NULL)
    {
        printf("Error in loading the image\n");
        exit(1);
    }
    this->image.resize(this->height, std::vector<px>(this->width));
    double r, g, b;
    for (int i = 0, c = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            r = 1.0 * imageR[c++] / 255, g = 1.0 * imageR[c++] / 255, b = 1.0 * imageR[c++] / 255;
            this->image[i][j] = px(r, g, b);
        }
    }
    stbi_image_free(imageR);
}

// transformations
void object::translation(vp P, bool point)
{
    vp t = ((point) ? (P - this->get_def_point()) : P);
    matrix T = matrix::translation_matrix(t);
    this->transformations = T * this->transformations;
    this->transform();
}

void object::rotation_auxiliar(matrix M)
{
    vp T = this->get_def_point();
    this->transformations = M * this->transformations;
    this->transform();
    this->translation(T);
}
void object::rotation_x(double angle) { rotation_auxiliar(matrix::rotationX_matrix(angle)); }
void object::rotation_y(double angle) { rotation_auxiliar(matrix::rotationY_matrix(angle)); }
void object::rotation_z(double angle) { rotation_auxiliar(matrix::rotationZ_matrix(angle)); }
void object::rotate_arbitrary(vp o, vp direction, double angle) { rotation_auxiliar(matrix::rotation_arbitrary_matrix(o, direction, angle)); }

void object::shear_xy(double angle) {}
void object::shear_yx(double angle) {}
void object::shear_xz(double angle) {}
void object::shear_zx(double angle) {}
void object::shear_yz(double angle) {}
void object::shear_zy(double angle) {}

void object::mirror_xy()
{
    this->transformations = matrix::mirroringXY_matrix() * this->transformations;
    this->transform();
}
void object::mirror_xz()
{
    this->transformations = matrix::mirroringXZ_matrix() * this->transformations;
    this->transform();
}
void object::mirror_yz()
{
    this->transformations = matrix::mirroringYZ_matrix() * this->transformations;
    this->transform();
}
void object::mirror_arbitrary(vp n, vp p)
{
    this->transformations = matrix::mirror_arbitrary_matrix(n, p) * this->transformations;
    this->transform();
}

// Getters and Setters
void object::set_pixel_image(int i, int j) { this->current_pixel_image = image[i % this->height][j % this->width]; }
bool object::get_has_image() { return this->has_image; }
px object::get_k_a() { return (this->has_image ? this->current_pixel_image : this->k_a); }
void object::set_k_a(px k_a) { this->k_a = k_a; }
px object::get_k_d() { return (this->has_image ? this->current_pixel_image : this->k_d); }
void object::set_k_d(px k_d) { this->k_d = k_d; }
px object::get_k_s() { return (this->has_image ? this->current_pixel_image : this->k_s); }
void object::set_k_s(px k_s) { this->k_s = k_s; }

double object::get_specular() { return this->specular; }
void object::set_specular(double specular) { this->specular = specular; }

double object::get_reflective() { return this->reflective; }
void object::set_reflective(double reflective) { this->reflective = reflective; }
