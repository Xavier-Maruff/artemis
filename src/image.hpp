#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <algorithm>
#include <functional>
#include "EasyBMP.hpp"

using std::vector, std::array;

typedef struct point {
    int x, y;
    point(int x_, int y_): x(x_), y(y_){}
} point;

typedef struct pixel {
    point pos;
    array<int, 3> rgb = {0,0,0};
    pixel(int x, int y): pos(x, y){}
} pixel;

typedef struct function {
    std::function<int(int)> rule;
    point rule_result;
    int scale;

    function(std::function<int(int)> rule_, int scale_ = 1):rule(rule_), rule_result(0,0), scale(scale_){}

    void iterate(){
        rule_result.x++;
        rule_result.y = rule(rule_result.x)*scale;
    }
} function;

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

        void apply_function(function& lambda, array<int, 3> colour, point origin, point max, bool impactful = false, float scale = 1){
            point rule_initial = lambda.rule_result;
            lambda.rule_result = origin;
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
                int result = scaled(x, lambda.rule, scale);
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
            if(!impactful) lambda.rule_result = rule_initial;
        }

        void render(EasyBMP::Image& img){
            //todo: parallel implementation of this
            for(int x = 0; x < width; x++){
                for(int y = 0; y < height; y++){
                    img.SetPixel(x, y, EasyBMP::RGBColor(pixels[x][y][0], pixels[x][y][1], pixels[x][y][2]));
                }
            }
            return;
            //img.SetPixel(x, y, EasyBMP::RGBColor(final_color, final_color, 0));
        }


    };
}


/*vector<vector<pixel>> create_pos(){
    vector<vector<pixel>> ret;
    for(int x = 0; x < WIDTH; x++){
        vector<pixel> column(0);
        for(int y = 0; y < HEIGHT; y++){
            column.push_back(pixel(x, y));
        }
        ret.push_back(column);
    }
    return ret;
}*/