#pragma once

#include "img.hh"

namespace bim
{

    void draw_pixel(Img& img, int x, int y, uint32_t color);

    void draw_hline(Img& img, int x1, int y, int x2, uint32_t color);
    void draw_vline(Img& img, int x, int y1, int y2, uint32_t color);
    void draw_line(Img& img, int x1, int y1, int x2, int y2,
                   uint32_t color);

    void draw_rect(Img& img, int x, int y, int w, int h, uint32_t color);
    void fill_rect(Img& img, int x, int y, int w, int h, uint32_t color);

    void draw_circle(Img& img, int cx, int cy, int r, uint32_t color);
    void fill_circle(Img& img, int cx, int cy, int r, uint32_t color);

    void draw_polygon(Img& img, int* coords, int len, uint32_t color);
    void fill_polygon(Img& img, int* coords, int len, uint32_t color); //TODO

    void draw_ellipse(Img& img, int cx, int cy, int rx, int ry,
                      uint32_t color);
    void fill_ellipse(Img& img, int cx, int cy, int rx, int ry,
                      uint32_t color);

    void flood_fill(Img& img, int x, int y, uint32_t dst_color,
                    bool diag = false);

    void draw_bezier3(Img& img, int x1, int y1, int x2, int y2, int x3, int y3,
                      uint32_t color);
    void draw_bezier4(Img& img, int x1, int y1, int x2, int y2, int x3, int y3,
                      int x4, int y4, uint32_t color);
    void draw_beziern(Img& img, int* xs, int* ys, int npts, uint32_t color);


    void draw_img(Img& img, const Img& src, int x, int y,
                  int src_x, int src_y, int src_w, int src_h);

    void draw_sprite(Img& img, const uint8_t* data, int x, int y,
                     int src_x, int src_y, int src_w, int src_h,
                     uint32_t color);

    void draw_sprite(Img& img, const uint8_t* data,
                     int dst_x, int dst_y, int dst_w, int dst_h,
                     int src_x, int src_y, int src_w, int src_h,
                     uint32_t color);

    void draw_text(Img& img, const char* text, int x, int y,
                   int font_size, uint32_t color);

    void text_size_get(const char* text, int font_size,
                       int* width, int* height);

    
}
