#include "EasyBMP.hpp"
#include "artemis.hpp"
#include <cmath>

#define WIDTH 800
#define HEIGHT 800

int main(){
    //Instantiate an artemis image, which is a wrapper over an EasyBMP image
    artemis::image img(WIDTH, HEIGHT, "img/output.bmp", {0,0,0});
    
    //Define f as our lambda expression (must map from int to int as artemis works in discrete pixels)
    std::function<int(int)> f = [](int arg) -> int {return (int)(sqrt(arg));};

    //Render f onto image
    //args: function, colour, origin, maximum, zoom factor
    img.render_function(f, {255, 0, 0}, {0,0}, {WIDTH, HEIGHT}, 500);
    
    //Save image
    img.write();

    return 0;
}