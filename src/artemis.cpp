#include "EasyBMP.hpp"
#include "image.hpp"
#include <iostream>
#include <vector>
#include <cmath>
using std::array, std::vector;

#define WIDTH 800
#define HEIGHT 800

EasyBMP::RGBColor bg(0,0,0);

int main(){
    EasyBMP::Image img(WIDTH, HEIGHT, "img/output.bmp", EasyBMP::RGBColor(0,0,0));
    artemis::image artemis_img(WIDTH, HEIGHT);

    function f1([=](int arg) -> int {return (int)(arg^50);}, 1);
    artemis_img.apply_function(f1, {255, 255, 255}, {0,0}, {WIDTH, HEIGHT});

    function f2([=](int arg) -> int {return (int)(arg^7);}, 1);
    artemis_img.apply_function(f2, {0, 255, 0}, {0,0}, {WIDTH, HEIGHT});

    function f3([=](int arg) -> int {return (int)(arg^80);}, 1);
    artemis_img.apply_function(f3, {0, 100, 100}, {0,0}, {WIDTH, HEIGHT});

    function f4([=](int arg) -> int {return (int)(arg^90);}, 1);
    artemis_img.apply_function(f4, {0, 255, 255}, {0,0}, {WIDTH, HEIGHT});

    function f5([=](int arg) -> int {return (int)arg;}, 1);
    artemis_img.apply_function(f5, {255, 0, 0}, {0,0}, {WIDTH, HEIGHT});

    function f6([=](int arg) -> int {return (int)(arg*arg);}, 1);
    artemis_img.apply_function(f6, {255, 0, 0}, {0,0}, {WIDTH, HEIGHT}, false, 0.05);
    
    function f7([=](int arg) -> int {return (int)(sqrt(arg));}, 1);
    artemis_img.apply_function(f7, {255, 0, 0}, {0,0}, {WIDTH, HEIGHT}, false, 20);

    artemis_img.render(img);

    img.Write();
    return 0;
}