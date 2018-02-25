#pragma once

#include "img.hh"
#include "color.hh"
#include <string>
#include <utility>
#include <vector>

namespace bim
{

    class Canvas
    {
    public:

        Canvas(std::size_t width, std::size_t height);

        std::size_t width_get() const;
        std::size_t height_get() const;
        const Img& img_get() const;

        const Color& draw_color_get() const;
        void draw_color_set(const Color& c);
        const Color& fill_color_get() const;
        void fill_color_set(const Color& c);
        const Color& font_color_get() const;
        void font_color_set(const Color& c);
        std::size_t font_size_get() const;
        void font_size_set(std::size_t size);

        void draw_pixel(double x, double y);
        void draw_line(double x1, double y1, double x2, double y2);
        void draw_rect(double x, double y, double w, double h);
        void fill_rect(double x, double y, double w, double h);
        void draw_circle(double cx, double cy, double r);
        void fill_circle(double cx, double cy, double r);
        void draw_polygon(const std::vector<double>& coords);
        void fill_polygon(const std::vector<double>& coords);
        void draw_ellipse(double cx, double cy, double rx, double ry);
        void fill_ellipse(double cx, double cy, double rx, double ry);
        void draw_bezier3(double x1, double y1, double x2, double y2,
                          double x3, double y3);
        void draw_bezier4(double x1, double y1, double x2, double y2,
                          double x3, double y3, double x4, double y4);
        void draw_beziern(const std::vector<double>& xs,
                          const std::vector<double>& ys);

        void draw_img(const Img& src, double x, double y,
                      double src_x, double src_y, double src_w, double src_h);
        void draw_sprite(const uint8_t* data, double x, int y,
                         double src_x, double src_y,
                         double src_w, double src_h);
        void draw_sprite(const uint8_t* data,
                         double dst_x, double dst_y,
                         double dst_w, double dst_h,
                         double src_x, double src_y,
                         double src_w, double src_h);

        void draw_text(const std::string& text, double x, double y);
        int text_width_get(const std::string& text);
        int text_height_get(const std::string& text);
        std::pair<int, int> text_size_get(const std::string& text);

        void clear();
        void render();

    private:
        Img img_;
        Color draw_color_;
        Color fill_color_;
        Color font_color_;
        std::size_t font_size_;



    };

}
