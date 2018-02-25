#include "bim/canvas.hh"
#include <cassert>
#include "bim/drawer.hh"
#include "graphics/gui-lib.hh"

namespace bim
{

    namespace
    {
        const Color DEFAULT_DRAW_COLOR = Color::BLACK;
        const Color DEFAULT_FILL_COLOR = Color::BLACK;
        const Color DEFAULT_FONT_COLOR = Color::RED;
        constexpr int DEFAULT_FONT_SIZE = 30;
    }

    Canvas::Canvas(std::size_t width, std::size_t height)
                : img_(height, width, 3)
                ,draw_color_(DEFAULT_DRAW_COLOR)
                , fill_color_(DEFAULT_FILL_COLOR)
                , font_color_(DEFAULT_FONT_COLOR)
                , font_size_(DEFAULT_FONT_SIZE)
    {
        clear();
    }

    std::size_t Canvas::width_get() const
    {
        return img_.cols();
    }

    std::size_t Canvas::height_get() const
    {
        return img_.rows();
    }

    const Img& Canvas::img_get() const
    {
        return img_;
    }

    const Color& Canvas::draw_color_get() const
    {
        return draw_color_;
    }

    void Canvas::draw_color_set(const Color& c)
    {
        draw_color_ = c;
    }

    const Color& Canvas::fill_color_get() const
    {
        return fill_color_;
    }

    void Canvas::fill_color_set(const Color& c)
    {
        fill_color_ = c;
    }

    const Color& Canvas::font_color_get() const
    {
        return font_color_;
    }

    void Canvas::font_color_set(const Color& c)
    {
        font_color_ = c;
    }

    std::size_t Canvas::font_size_get() const
    {
        return font_size_;
    }

    void Canvas::font_size_set(std::size_t size)
    {
        font_size_ = size;
    }

    void Canvas::draw_pixel(double x, double y)
    {
        bim::draw_pixel(img_, x, y, draw_color_.rgb());
    }

    void Canvas::draw_line(double x1, double y1, double x2, double y2)
    {
        bim::draw_line(img_, x1, y1, x2, y2, draw_color_.rgb());
    }

    void Canvas::draw_rect(double x, double y, double w, double h)
    {
        bim::draw_rect(img_, x, y, w, h, draw_color_.rgb());
    }


    void Canvas::fill_rect(double x, double y, double w, double h)
    {
        bim::fill_rect(img_, x, y, w, h, fill_color_.rgb());
    }

    void Canvas::draw_circle(double cx, double cy, double r)
    {
        bim::draw_circle(img_, cx, cy, r, draw_color_.rgb());
    }

    void Canvas::fill_circle(double cx, double cy, double r)
    {
        bim::fill_circle(img_, cx, cy, r, fill_color_.rgb());
    }

    void Canvas::draw_polygon(const std::vector<double>& coords)
    {
        assert(coords.size() % 2 == 0);
        std::vector<int> icoords(coords.size());
        for (std::size_t i = 0; i < coords.size(); ++i)
            icoords[i] = coords[i];
        bim::draw_polygon(img_, icoords.data(), icoords.size() / 2,
                    draw_color_.rgb());
    }

    void Canvas::fill_polygon(const std::vector<double>& coords)
    {
        assert(coords.size() % 2 == 0);
        std::vector<int> icoords(coords.size());
        for (std::size_t i = 0; i < coords.size(); ++i)
            icoords[i] = coords[i];
        bim::draw_polygon(img_, icoords.data(), icoords.size() / 2,
                          fill_color_.rgb());
    }

    void Canvas::draw_ellipse(double cx, double cy, double rx, double ry)
    {
        bim::draw_ellipse(img_, cx, cy, rx, ry, draw_color_.rgb());
    }

    void Canvas::fill_ellipse(double cx, double cy, double rx, double ry)
    {
        bim::fill_ellipse(img_, cx, cy, rx, ry, fill_color_.rgb());
    }

    void Canvas::draw_bezier3(double x1, double y1, double x2, double y2,
                      double x3, double y3)
    {
        bim::draw_bezier3(img_, x1, y1, x2, y2, x3, y3, draw_color_.rgb());
    }

    void Canvas::draw_bezier4(double x1, double y1, double x2, double y2,
                      double x3, double y3, double x4, double y4)
    {
        bim::draw_bezier4(img_, x1, y1, x2, y2, x3, y3,
                          x4, y4, draw_color_.rgb());
    }

    void Canvas::draw_beziern(const std::vector<double>& xs,
                             const std::vector<double>& ys)
    {
        assert(xs.size() == ys.size());

        std::vector<int> xsi(xs.size());
        for (std::size_t i = 0; i < xsi.size(); ++i)
            xsi[i] = xs[i];

        std::vector<int> ysi(ys.size());
        for (std::size_t i = 0; i < ysi.size(); ++i)
            ysi[i] = ys[i];

        bim::draw_beziern(img_, xsi.data(), ysi.data(),
                          xs.size(), draw_color_.rgb());

    }

    void Canvas::draw_img(const Img& src, double x, double y,
                          double src_x, double src_y,
                          double src_w, double src_h)
    {
        bim::draw_img(img_, src, x, y, src_x, src_y, src_w, src_h);
    }

    void Canvas::draw_sprite(const uint8_t* data, double x, int y,
                             double src_x, double src_y,
                             double src_w, double src_h)
    {
        bim::draw_sprite(img_, data, x, y, src_x, src_y,
                         src_w, src_h, draw_color_.rgb());
    }

    void Canvas::draw_sprite(const uint8_t* data,
                             double dst_x, double dst_y,
                             double dst_w, double dst_h,
                             double src_x, double src_y,
                             double src_w, double src_h)
    {
        bim::draw_sprite(img_, data, dst_x, dst_y, dst_w, dst_h,
                         src_x, src_y, src_w, src_h, draw_color_.rgb());
    }

    void Canvas::draw_text(const std::string& text, double x, double y)
    {
        bim::draw_text(img_, text.c_str(), x, y, font_size_, font_color_.rgb());
    }

    int Canvas::text_width_get(const std::string& text)
    {
        int w;
        int h;
        bim::text_size_get(text.c_str(), font_size_, &w, &h);
        return w;
    }

    int Canvas::text_height_get(const std::string& text)
    {
        int w;
        int h;
        bim::text_size_get(text.c_str(), font_size_, &w, &h);
        return h;
    }

    std::pair<int, int> Canvas::text_size_get(const std::string& text)
    {
        int w;
        int h;
        bim::text_size_get(text.c_str(), font_size_, &w, &h);
        return {w, h};
    }

    void Canvas::clear()
    {
        img_.fill_pixels(Color::WHITE.rgb());
    }

    void Canvas::render()
    {
        guilib::render_img(img_);
    }

}
