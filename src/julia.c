//
//  julia.c
//  MyGame
//
//  Created by Dylan on 13/4/17.
//
//

#include <stdio.h>
#include "SwinGame.h"

#define MAX_ITERATION 200
#define RVALUE -0.624
#define IVALUE 0.435

color get_color(double real, double imag) {
    
    double xtemp, hue;
    color clr;
    int i;
    
    for (i = 0; i < MAX_ITERATION; i++) {
        xtemp = real * real - imag * imag + RVALUE;
        imag = 2 * real * imag - IVALUE;
        real = xtemp;
        if (real * real + imag * imag > 4) {
            break;
        }
    }
    
    if (i >= MAX_ITERATION) {
        clr = ColorPeru;
    } else {
        hue = 0.6 + (float) i / MAX_ITERATION;
        clr = hsbcolor(hue, 0.7, 0.8);
    }
    
    return clr;
    
}

void draw_juliaset(double begin_x, double begin_y, double width, double height) {
    
    double julia_w, julia_h;
    int x, y;
    double real, imag;
    color j_color;
    
    julia_w = width / screen_width();
    julia_h = height / screen_height();
    
    for (y = 0; y < screen_height(); y++) {
        for (x = 0; x < screen_width(); x++) {
            real = begin_x + x * julia_w;
            imag = begin_y + y * julia_h;
            j_color = get_color(real, imag);
            draw_pixel(j_color, x, y);
        }
    }
    
}

int main()
{
    
    double begin_x, begin_y;
    double width, height;
    
    begin_x = -1.5;
    begin_y = -2.0;
    width = 3;
    height = 4;
    
    open_graphics_window("Julia Set", 800, 600);
    
    do {
        
        process_events();
        draw_juliaset(begin_x, begin_y, width, height);
        
        if (mouse_clicked(LEFT_BUTTON)) {
            begin_x += (mouse_x() / screen_width()) * width;
            begin_y += (mouse_y() / screen_height()) * height;
            width /= 2;
            height /= 2;
            begin_x -= width / 2;
            begin_y -= height / 2;
        }
        
        if (mouse_clicked(RIGHT_BUTTON)) {
            begin_x += (mouse_x() / screen_width()) * width;
            begin_y += (mouse_y() / screen_height()) * height;
            width *= 2;
            height *= 2;
            begin_x -= width / 2;
            begin_y -= height / 2;
        }
        
        refresh_screen();
        
    } while (!window_close_requested());
    
    return 0;
}
