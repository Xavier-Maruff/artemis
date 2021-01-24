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
        int img_width, img_height;
        EasyBMP::Image img;

        image(int width_, int height_, string fname, array<uint8_t, 3> bg):
        img_width(width_),
        img_height(height_),
        img(img_width, img_height, fname, EasyBMP::RGBColor({bg[0], bg[1], bg[2]}))
        {}
        

        void render_function(std::function<int(int)> lambda, array<int, 3> colour, point origin, point max, float scale = 1){
            int previous = origin.y;

            max.x = (max.x <= img_width ? max.x : img_width);
            max.y = (max.y <= img_height ? max.y : img_height);

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
                    for(int y = previous; y < img_height; y++){
                        img.SetPixel(x, img_height-y-1, bmp_colour);
                    }
                    break;
                }
                else{
                    for(int y = previous; y <= result; y++){
                        img.SetPixel(x, img_height-y-1, bmp_colour);
                    }
                }
                previous = result;
            }
        }

        void write() {
            img.Write();
        }
    
    };
}


#endif