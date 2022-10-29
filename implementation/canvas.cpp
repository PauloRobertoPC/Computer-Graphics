#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define CHANNEL_NUM 3

#include "../header/canvas.hpp"
#include "../header/stb_image.hpp"
#include "../header/stb_image_write.hpp"

canvas::canvas(){}
canvas::canvas(int n, int m, px bg): n(n), m(m), background_color(bg), M(n, std::vector<px>(m, bg)), z_buffer(n, std::vector<object*>(m, nullptr)){}

void canvas::write_image(const char* image_name){
	int width = m, height = n;
  	int8 *imageW = new int8[width * height * CHANNEL_NUM];
	for(int i = 0, c = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			imageW[c++] = M[i][j].convert_red(), imageW[c++] = M[i][j].convert_green(), imageW[c++] = M[i][j].convert_blue();
	stbi_write_png(image_name, width, height, CHANNEL_NUM, imageW, width * CHANNEL_NUM);
}

void canvas::to_color(int i, int j, px color, object *o){ this->M[i][j] = color; this->z_buffer[i][j] = o; }
px canvas::get_color(int i, int j){ return this->M[i][j]; } 
object* canvas::get_object(int i, int j){ return this->z_buffer[i][j]; }

//Getters and Setters
int canvas::get_n(){ return this->n; }
void canvas::set_n(int n){ this->n = n; }
int canvas::get_m(){ return this->m; }
void canvas::set_m(int m){ this->m = m; }
px canvas::get_background_color(){ return this->background_color; }
void canvas::set_background_color(px background_color){ this->background_color = background_color; }
