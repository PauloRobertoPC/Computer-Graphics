#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "../utils/px.hpp"
#include "../objects/object.hpp"
#include <vector>

class canvas{
    private:
        int n, m; //heigth and width of the canvas
        std::vector<std::vector<px>> M; //Matrix who will represent our canvas/image
        std::vector<std::vector<object*>> z_buffer;  //Matrix who will represent which object in being showed in each pixel
        px background_color;            //background_color of our canvas/image

    public:
        canvas();
        canvas(int n, int m, px bg);
        
        void write_image(const char* image_name); //save imagem with name "image_name" in .png 
        void to_color(int i, int j, px color, object *o); //to color the pixel[i][j] of our canvas/image with the "color"
        px get_color(int i, int j);        
        object* get_object(int i, int j); 
    
        //Getters and Setters
        int get_n();
        void set_n(int n);
        int get_m();
        void set_m(int m);
        px get_background_color();
        void set_background_color(px background_color);
};

#endif
