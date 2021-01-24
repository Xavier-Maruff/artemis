# Artemis

Artemis is a very minimal function plotting C++ library, a wrapper over the <a href="https://github.com/izanbf1803/EasyBMP">EasyBMP library</a>, from <a href="https://github.com/izanbf1803">izanbf1803</a>. The library takes one or many lambda expressions mapping an x integer to a y integer, and renders them as a bitmap image.

## Example:
```c++
#include "artemis.hpp"
#include <cmath>

#define WIDTH 800
#define HEIGHT 800

int main(){
    //Instantiate an artemis image, which is a wrapper over an EasyBMP image
    artemis img(WIDTH, HEIGHT, "img/output.bmp", {0,0,0});
    
    //Define f1 as our lambda expression (must map from int to int as artemis works in discrete pixels)
    //This function can be continuous, discrete, anything you want
    std::function<int64_t(int64_t)> f = [](int64_t arg) -> int64_t {return (int64_t)sqrt(arg);};

    //Render f onto image
    //args: function, colour, origin, maximum, zoom factor
    img.render_function(f, {255, 0, 0}, {0,0}, {WIDTH, HEIGHT}, 500);

    //Doing the same with another function
    std::function<int64_t(int64_t)> f2 = [](int64_t arg) -> int64_t {return (int64_t)(arg*arg);};
    img.render_function(f2, {0, 255, 0}, {0,0},{WIDTH, HEIGHT}, 0.002);
    
    //Save image
    img.Write();

    return 0;
}
```

## Output:
<img src="/img/output.bmp">