#include "EasyBMP.hpp"
#include "artemis.hpp"
#include <cmath>

#define WIDTH 800
#define HEIGHT 800

EasyBMP::RGBColor bg(0,0,0);

int main(){
    //Initialise EasyBMP image
    EasyBMP::Image img(WIDTH, HEIGHT, "img/output.bmp", EasyBMP::RGBColor(0,0,0));
    artemis::image artemis_img(WIDTH, HEIGHT);
    
    //Define f as our lambda expression (must map from int to int as artemis works in discrete pixels)
    std::function<int(int)> f = [=](int arg) -> int {return (int)(sqrt(arg));};

    //Simulate function (gets writen into artemis' pixel matrix)
    //Args: lambda function, colour, origin, maximum, scale factor (kind of works like a zoom function)
    artemis_img.apply_function(f, {255, 0, 0}, {0,0}, {WIDTH, HEIGHT}, 500);
    
    //Render the artemis pixel matrix as an EasyBMP bitmap image
    artemis_img.render(img);
    
    //Save EasyBMP image
    img.Write();

    return 0;
}