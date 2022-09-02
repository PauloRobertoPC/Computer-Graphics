#ifndef CANVAS_HPP
#define CANVAS_HPP
#define CHANNEL_NUM 3
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <bits/stdc++.h>
#include "stb_image.hpp"
#include "stb_image_write.hpp"
#include "util.hpp"
#include "viewport.hpp"

using namespace std;

struct canvas{
    int n, m; //altura e a largura do canvas
    viewport vw; //viewport a qual o canvas vai se basear para se pintar
    vector<vector<px>> M; //Matriz que vai representar o nosso canvas/imagem
    px background_color;

    canvas(){}
    canvas(int n, int m, viewport vw, px bg): n(n), m(m), vw(vw), background_color(bg), M(n, vector<px>(m, bg)){}
    
    void write_image(const char* image_name){
    	int width = m, height = n;
      	int8 *imageW = new int8[width * height * CHANNEL_NUM];
    	for(int i = 0, c = 0; i < height; i++)
    		for(int j = 0; j < width; j++)
    			imageW[c++] = M[i][j].convert_red(), imageW[c++] = M[i][j].convert_green(), imageW[c++] = M[i][j].convert_blue();
    	stbi_write_png(image_name, width, height, CHANNEL_NUM, imageW, width * CHANNEL_NUM);
    }
    
    void to_color(int i, int j, px color){ M[i][j] = color; }
};

#endif
