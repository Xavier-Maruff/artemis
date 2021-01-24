#include <iostream>
#include <vector>
#include <cmath>
#include <array>

using std::vector, std::array;

typedef struct pixel {
    int x, y;
    array<int, 3> rgb = {0,0,0};
    pixel(int x_, int y_): x(x_), y(y_){}
} pixel;

namespace artemis{
    class image {
        public:
        vector<vector<pixel>> pixels;
        int width, height;

        image(int width_, int height_): width(width_), height(height_) {
            for(int x = 0; x < width; x++){
                for(int y = 0; y < height; y++){
                    pixels.push_back(pixel(x, y));
                }
            }
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