#pragma once

#include "color.hh"
#include "bim/img.hh"

namespace guilib
{

    void clear();
    void draw_pixel(int x, int y, const Color& c);
    void draw_line(int x1, int y1, int x2, int y2, const Color& c);
    void draw_circle(int x1, int y1, int r, const Color& c);
    void fill_circle(int x1, int y1, int r, const Color& c);
    void draw_rect(int x, int y, int w, int h, const Color& c);
    void fill_rect(int x, int y, int w, int h, const Color& c);
    void draw_ellipse(int x, int y, int w, int h, const Color& c);
    void fill_ellipse(int x, int y, int w, int h, const Color& c);
    void draw_polygon(int* begin, int* end, const Color& c);
    void fill_polygon(int* begin, int* end, const Color& c);
    void draw_img(const char* path, double angle,
                  int src_x, int src_y, int src_w, int src_h,
                  int dst_x, int dst_y, int dst_w, int dst_h);
    void draw_text(int x, int y, const char* font, int size, const Color& c,
                   const char* str, double angle);

    //must be enough for
    void draw_img(const bim::Img& img, int x, int y);


    void render();
    void render_img(const bim::Img& img);

}

