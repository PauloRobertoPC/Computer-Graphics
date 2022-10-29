#ifndef SCENE_HPP
#define SCENE_HPP

#include "object.hpp"
#include "vp.hpp"
#include "px.hpp"
#include "viewport.hpp"
#include "canvas.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "camera.hpp"

enum PROJECTION{
    PERSPECITVE,
    PARALELL
};

class scene{
    private:
        camera O;                       //camera
        viewport vw;                    //viewport
        canvas c;                       //canvas
        PROJECTION p;                   //projection used
        std::vector<object*> objects;   //objects who are in the scene
        std::vector<light*> lights;     //lights whoa are in the scene
        double dx, dy;                  //width and heigth of each pixel of canvas in real world
    
        px compute_lighting(vp P, vp N, vp V, object* obj); //calculate all the light in an specific point

        std::tuple<px, object*> trace_ray(vp O, vp D, double t_min, double t_max); //trace rays of from observer to direction D
        
        bool without_shade(vp P, light* l);

        void transform_scenario_to_camera();
        
        vp xy(int i, int j); //direction of the ray from the observer to the real world passing through the pixel i,j of the canvas
    
        std::tuple<vp, vp> ray_equation(int i, int j);
    

    public:
        scene(camera O, viewport vw, canvas c, PROJECTION p);        
    
        void add_object(object *o);
        void add_light(light *l);
        
        void draw_scenario(bool change_coordinates);

        void save_scenario(const char* image_name);

        object* select_object(int i, int j);

        void translation(object *choosen_object, int x, int y, int i, int j);

        px get_pixel(int i, int j); 
};

#endif
