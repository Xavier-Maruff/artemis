#ifndef ARTEMIS_IMAGE
#define ARTEMIS_IMAGE

#include <vector>
#include <array>
#include <functional>
#include <string>
#include "EasyBMP.hpp"

using std::vector, std::array, std::string;

typedef struct point {
    int x, y;
    point(int x_, int y_): x(x_), y(y_){}
} point;

namespace artemis{

    class image {
        public:
        int width, height;
        EasyBMP::Image bmp_img;

        image(int width_, int height_, string fname, array<uint8_t, 3> bg):
        width(width_),
        height(height_),
        bmp_img(width, height, fname, EasyBMP::RGBColor({bg[0], bg[1], bg[2]}))
        {}
        

        void render_function(std::function<int(int)> lambda, array<int, 3> colour, point origin, point max, float scale = 1){
            int previous = origin.y;

            max.x = (max.x <= width ? max.x : width);
            max.y = (max.y <= height ? max.y : height);

            EasyBMP::RGBColor bmp_colour(colour[0], colour[1], colour[2]);

            std::function<int(int)> scaled;
            if(scale >= 1) {
                scaled = [&](int val) -> int {return lambda(val*scale);};
            } else {
                scaled = [&](int val) -> int {return (int)(lambda(val)*scale);};
            }

            for(int x = 0; x < max.x; x++){
                int result = scaled(x);
                if(result >= max.y) {
                    for(int y = previous; y < height; y++){
                        bmp_img.SetPixel(x, height-y-1, bmp_colour);
                    }
                }
                else{
                    for(int y = previous; y <= result; y++){
                        bmp_img.SetPixel(x, height-y-1, bmp_colour);
                    }
                }
                previous = result;
            }
        }

        void write() {
            bmp_img.Write();
        }
    
    };
}


#endif