#ifndef ARTEMIS_IMAGE
#define ARTEMIS_IMAGE

#include <vector>
#include <array>
#include <functional>
#include <string>
#include "EasyBMP.hpp"

using std::vector, std::array, std::string;

typedef struct point {
    int64_t x, y;
    point(const int64_t x_, const int64_t y_): x(x_), y(y_){}
} point;

class artemis : public EasyBMP::Image {
    public:
    artemis(const int64_t width_, const int64_t height_, const string& fname, const array<uint8_t, 3> bg):EasyBMP::Image(width_, height_, fname, EasyBMP::RGBColor({bg[0], bg[1], bg[2]})){}
    artemis(const int64_t width_, const int64_t height_, const string& fname):EasyBMP::Image(width_, height_, fname){}
    artemis(const int64_t width_, const int64_t height_, const array<uint8_t, 3> bg):EasyBMP::Image(width_, height_,  EasyBMP::RGBColor({bg[0], bg[1], bg[2]})){}
    artemis(const int64_t width_, const int64_t height_):EasyBMP::Image(width_, height_){}
    ~artemis(){}

    void render_function(const std::function<int(int)> lambda, const array<int, 3> colour, const point origin, const point max, const float scale = 1){
        int64_t previous = (origin.y >= 0 ? (origin.y < height ? origin.y : height) : 0);
        const EasyBMP::RGBColor bmp_colour(colour[0], colour[1], colour[2]);
        std::function<int64_t(int64_t)> scaled;

        if(scale >= 1) scaled = [&](int64_t val) -> int64_t {return lambda(val*scale);};
        else scaled = [&](int64_t val) -> int64_t {return (int64_t)(lambda(val)*scale);};
    
        for(int64_t x = 0; x < max.x; x++){
            int64_t result = scaled(x)+origin.y;
            int64_t x_offset = x+origin.x;
            if(result >= 0 && x_offset < width && x_offset >= 0){
                if(result >= max.y || result >= height) {
                    for(int64_t y = previous; y < height; y++) SetPixel(x_offset, height-y-1, bmp_colour);
                }
                else{
                    for(int64_t y = previous; y <= result; y++) SetPixel(x_offset, height-y-1, bmp_colour);
                }
            }
            previous = result;
        }
    }
};
#endif