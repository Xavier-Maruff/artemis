#include "EasyBMP.hpp"
#include "image.hpp"
#include <iostream>
#include <vector>
#include <cmath>
using std::array, std::vector;

#define WIDTH 512
#define HEIGHT 512

EasyBMP::RGBColor bg(0,0,0);

int main(){
    EasyBMP::Image img(WIDTH, HEIGHT, "img/output.bmp", EasyBMP::RGBColor(0,0,0));

    //img.SetPixel(x, y, EasyBMP::RGBColor(final_color, final_color, 0));
    img.Write();
    return 0;
}