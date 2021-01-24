#ifndef ARTEMIS_IMAGE
#define ARTEMIS_IMAGE

#include <vector>
#include <array>
#include <functional>
#include "EasyBMP.hpp"

using std::vector, std::array;

typedef struct point {
    int x, y;
    point(int x_, int y_): x(x_), y(y_){}
} point;

namespace artemis{

    class image {
        public:
        vector<vector<array<int, 3>>> pixels;
        int width, height;

        image(int width_, int height_): width(width_), height(height_) {
            for(int x = 0; x < width; x++){
                vector<array<int, 3>> column = {};
                for(int y = 0; y < height; y++){
                    column.push_back(array<int, 3>({0,0,0}));
                }
                pixels.push_back(column);
            }
        }

        void apply_function(std::function<int(int)> lambda, array<int, 3> colour, point origin, point max, float scale = 1){
            int previous = origin.y;

            max.x = (max.x <= width ? max.x : width);
            max.y = (max.y <= height ? max.y : height);

            std::function<int(int, std::function<int(int)>, float)> scaled;
            if(scale >= 1) {
                scaled = [=](int val, std::function<int(int)> rule, float scale) -> int {return rule(val*scale);};
            } else {
                scaled = [=](int val, std::function<int(int)> rule, float scale) -> int {return (int)(rule(val)*scale);};
            }

            for(int x = 0; x < max.x; x++){
                int result = scaled(x, lambda, scale);
                if(result >= max.y) {
                    for(int y = previous; y < height; y++){
                    pixels[x][height-y] = colour;
                    }
                    break;
                }
                else{
                    for(int y = previous; y <= result; y++){
                        pixels[x][height-y] = colour;
                    }
                }
                previous = result;
            }
        }

        void render(EasyBMP::Image& img){
            //todo: parallel implementation of this
            for(int x = 0; x < width; x++){
                for(int y = 0; y < height; y++){
                    img.SetPixel(x, y, EasyBMP::RGBColor(pixels[x][y][0], pixels[x][y][1], pixels[x][y][2]));
                }
            }
            return;
        }


    };
}


#endif