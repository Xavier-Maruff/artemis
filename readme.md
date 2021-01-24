# Artemis

Artemis is a very minimal function plotting C++ library, a wrapper over the <a href="https://github.com/izanbf1803/EasyBMP">EasyBMP library</a>, from <a href="https://github.com/izanbf1803">izanbf1803</a>. The library takes one or many lambda expressions mapping an x integer to a y integer, and renders them as a bitmap image.

## Example:
```c++
#include "EasyBMP.hpp"
#include "artemis.hpp"
#include <cmath>

#define WIDTH 800
#define HEIGHT 800

int main(){
    //Instantiate an artemis image, which is a wrapper over an EasyBMP image
    //args: width, height, image path, rgb background colour
    artemis::image img(WIDTH, HEIGHT, "img/output.bmp", {0,0,0});
    
    //Define f as our lambda expression (must map from int to int as artemis works in discrete pixels)
    std::function<int(int)> f = [](int arg) -> int {return (int)(sqrt(arg));};

    //Render f onto image
    //args: function, plotting colour, origin, maximum, zoom factor
    img.render_function(f, {255, 0, 0}, {0,0}, {WIDTH, HEIGHT}, 500);
    
    //Save image
    img.write();

    return 0;
}
```

## Output:
<img src="/img/output.bmp">