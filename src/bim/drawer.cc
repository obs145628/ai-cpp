#include "bim/drawer.hh"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>

#include "graphics/gui-lib.hh"

namespace
{

    constexpr  int CHAR_DEC_COEFF = 10;

    uint8_t* ascii_sprites[255];
    bool asccii_loaded = false;
    int font_width;
    int font_height;


    void load_font()
    {
        if (!asccii_loaded)
        {
            std::ifstream is("courier.data");

            for (int code = 32; code < 127; ++code) {
                uint8_t rows;
                uint8_t cols;
                is.read(reinterpret_cast<char*>(&rows), 1);
                is.read(reinterpret_cast<char*>(&cols), 1);

                uint8_t* l = new uint8_t[rows * cols + 2];
                l[0] = rows;
                l[1] = cols;
                is.read(reinterpret_cast<char*>(l + 2), std::size_t(rows) * cols);

                ascii_sprites[code] = l;

                font_width = cols;
                font_height = rows;
            }

            asccii_loaded = true;
        }
    }

    int sign(int x)
    {
        return x < 0 ? -1 : x > 0;
    }


    int fact(int x)
    {
        return x == 0 ? 1 : x * fact(x - 1);
    }

    int binomial(int n, int k)
    {
        return fact(n) / (fact(k) * fact(n - k));
    }

    uint8_t sprite_get(const uint8_t* sprite, int x, int y)
    {
        assert(x >= 0 && x < sprite[1]);
        assert(y >= 0 && y < sprite[0]);
        return sprite[2 + y * sprite[1] + x];
    }

    uint8_t bilinear_interpolation(const uint8_t* sprite, double x, double y)
    {
        int ix = x;
        int iy = y;
        int w = sprite[1];
        int h = sprite[0];

        uint8_t pa = sprite_get(sprite, ix, iy);
        uint8_t pb = ix + 1 == w ? pa : sprite_get(sprite, ix + 1, iy);
        uint8_t pc = iy + 1 == h ? pa : sprite_get(sprite, ix, iy + 1);
        uint8_t pd = ix + 1 == w || iy + 1 == h ? pa : sprite_get(sprite,
                                                                  ix + 1,
                                                                  iy + 1);

        double dx = x - ix;
        double dy = y - iy;
        double dx1 = 1.0 - dx;
        double dy1 = 1.0 - dy;
        double wa = dx1 * dy1;
        double wb = dx * dy1;
        double wc = dx1 * dy;
        double wd = dx * dy;

        double val = pa * wa + pb * wb + pc * wc + pd * wd;
        return val > 0.5;
    }


}

namespace bim
{

    void draw_pixel(Img& img, int x, int y, uint32_t color)
    {
        if (x >= 0 && x < (int) img.cols() && y >= 0 && y < (int) img.rows())
            img.set_pixel(y, x, color);
    }

    void draw_hline(Img& img, int x1, int y, int x2, uint32_t color)
    {
        if (x1 > x2)
            std::swap(x1, x2);

        for (int i = x1; i <= x2; ++i)
            draw_pixel(img, i, y, color);
    }

    void draw_vline(Img& img, int x, int y1, int y2, uint32_t color)
    {
        if (y1 > y2)
            std::swap(y1, y2);

        for (int i = y1; i <= y2; ++i)
            draw_pixel(img, x, i, color);
    }

    /**
     * Bresenham's line algorithm
     * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
     */
    void draw_line(Img& img, int x1, int y1, int x2, int y2,
                   uint32_t color)
    {
        if (x1 == x2)
        {
            draw_vline(img, x1, y1, y2, color);
            return;
        }
        if (y1 == y2)
        {
            draw_hline(img, x1, y1, x2, color);
            return;
        }

        bool steep = false;

        if (std::abs(x2 -x1) < std::abs(y2 - y1))
        {
            std::swap(x1, y1);
            std::swap(x2, y2);
            steep = true;
        }

        if (x1 > x2)
        {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        int dx = x2 - x1;
        int dy = y2 - y1;
        int err = - dx;
        int y = y1;

        for (int x = x1; x <= x2; ++x)
        {
            if (steep)
                draw_pixel(img, y, x, color);
            else
                draw_pixel(img, x, y, color);

            err += 2 * std::abs(dy);
            if (err > 0)
            {
                y += sign(dy);
                err -= 2 * dx;
            }
        }
    }

    void draw_rect(Img& img, int x, int y, int w, int h, uint32_t color)
    {
        draw_hline(img, x, y, x + w, color);
        draw_hline(img, x, y + h, x + w, color);
        draw_vline(img, x, y, y + h, color);
        draw_vline(img, x + w, y, y + h, color);
    }

    void fill_rect(Img& img, int x, int y, int w, int h, uint32_t color)
    {
        if (w < 0)
        {
            x += w;
            w = -w;
        }
        if (h < 0)
        {
            y += h;
            h = -h;
        }

        for (int i = x; i <= x + w; ++i)
            for (int j = y; j <= y + h; ++j)
                draw_pixel(img, i, j, color);
    }

    /*
     * Midpoint-circle algorithm
     * https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
     */
    void draw_circle(Img& img, int cx, int cy, int r, uint32_t color)
    {
        assert(r >= 0);

        int x = r - 1;
        int y = 0;
        int dx = 1;
        int dy = 1;
        int err = dx - r * 2;

        while (x >= y)
        {
            draw_pixel(img, cx + x, cy + y, color);
            draw_pixel(img, cx + y, cy + x, color);
            draw_pixel(img, cx - y, cy + x, color);
            draw_pixel(img, cx - x, cy + y, color);
            draw_pixel(img, cx - x, cy - y, color);
            draw_pixel(img, cx - y, cy - x, color);
            draw_pixel(img, cx + y, cy - x, color);
            draw_pixel(img, cx + x, cy - y, color);

            if (err <= 0)
            {
                ++y;
                err += dy;
                dy += 2;
            }
            if (err > 0)
            {
                --x;
                dx += 2;
                err += (-r * 2) + dx;
            }
        }
    }

    /*
     * Midpoint-circle algorithm
     * https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
     */
    void fill_circle(Img& img, int cx, int cy, int r, uint32_t color)
    {
        assert(r >= 0);

        int x = r - 1;
        int y = 0;
        int dx = 1;
        int dy = 1;
        int err = dx - r * 2;

        while (x >= y)
        {
            draw_hline(img, cx - x, cy + y, cx + x, color);
            draw_hline(img, cx - y, cy + x, cx + y, color);
            draw_hline(img, cx - x, cy - y, cx + x, color);
            draw_hline(img, cx - y, cy - x, cx + y, color);


            if (err <= 0)
            {
                ++y;
                err += dy;
                dy += 2;
            }
            if (err > 0)
            {
                --x;
                dx += 2;
                err += (-r * 2) + dx;
            }
        }
    }

    void draw_polygon(Img& img, int* coords, int len, uint32_t color)
    {
        assert(len >= 2);

        for (int i = 0; i < len - 1; ++i)
            draw_line(img, coords[2 * i], coords[2 * i + 1],
                      coords[2 * i + 2], coords[2 * i + 3], color);
        draw_line(img, coords[2 * len - 2], coords[2 * len - 1],
                  coords[0], coords[1], color);
    }

    /*
    * Draw ellipse : Bresenham Type Algorithm for ellipse
    * https://dai.fmph.uniba.sk/upload/0/01/Ellipse.pdf
    */

    namespace
    {
        void draw_ellipse4(Img& img, int cx, int cy, int x, int y,
                           uint32_t color)
        {
            draw_pixel(img, cx  + x, cy + y, color);
            draw_pixel(img, cx  - x, cy + y, color);
            draw_pixel(img, cx  - x, cy - y, color);
            draw_pixel(img, cx  + x, cy - y, color);
        }
    }

    void draw_ellipse(Img& img, int cx, int cy, int rx, int ry,
                      uint32_t color)
    {
        int rx2 = 2 * rx * rx;
        int ry2 = 2 * ry * ry;
        int x = rx;
        int y = 0;
        int xchange = ry * ry * (1 - 2 * rx);
        int ychange = rx * rx;
        int err = 0;
        int xstop = ry2 * rx;
        int ystop = 0;


        while (xstop >= ystop)
        {
            draw_ellipse4(img, cx, cy, x, y, color);
            ++y;
            ystop += rx2;
            err += ychange;
            ychange += rx2;

            if (2 * err + xchange > 0)
            {
                --x;
                xstop -= ry2;
                err += xchange;
                xchange += ry2;
            }
        }

        x = 0;
        y = ry;
        xchange = ry * ry;
        ychange = rx * rx * (1 - 2 * ry);
        err = 0;
        xstop = 0;
        ystop = rx2 * ry;


        while (xstop <= ystop)
        {
            draw_ellipse4(img, cx, cy, x, y, color);
            ++x;
            xstop += ry2;
            err += xchange;
            xchange += ry2;

            if (2 * err + ychange > 0)
            {
                --y;
                ystop -= rx2;
                err += ychange;
                ychange += rx2;
            }
        }
    }

    /*
     * Fill ellipse : Bresenham Type Algorithm for ellipse
     * https://dai.fmph.uniba.sk/upload/0/01/Ellipse.pdf
     */
    namespace
    {
        void fill_ellipse4(Img& img, int cx, int cy, int x, int y,
                           uint32_t color)
        {
            draw_hline(img, cx - x, cy - y, cx + x, color);
            draw_hline(img, cx - x, cy + y, cx + x, color);
        }
    }

    void fill_ellipse(Img& img, int cx, int cy, int rx, int ry,
                      uint32_t color)
    {
        int rx2 = 2 * rx * rx;
        int ry2 = 2 * ry * ry;
        int x = rx;
        int y = 0;
        int xchange = ry * ry * (1 - 2 * rx);
        int ychange = rx * rx;
        int err = 0;
        int xstop = ry2 * rx;
        int ystop = 0;


        while (xstop >= ystop)
        {
            fill_ellipse4(img, cx, cy, x, y, color);
            ++y;
            ystop += rx2;
            err += ychange;
            ychange += rx2;

            if (2 * err + xchange > 0)
            {
                --x;
                xstop -= ry2;
                err += xchange;
                xchange += ry2;
            }
        }

        x = 0;
        y = ry;
        xchange = ry * ry;
        ychange = rx * rx * (1 - 2 * ry);
        err = 0;
        xstop = 0;
        ystop = rx2 * ry;


        while (xstop <= ystop)
        {
            fill_ellipse4(img, cx, cy, x, y, color);
            ++x;
            xstop += ry2;
            err += xchange;
            xchange += ry2;

            if (2 * err + ychange > 0)
            {
                --y;
                ystop -= rx2;
                err += ychange;
                ychange += rx2;
            }
        }
    }

    namespace
    {

        void flood_fill_rec(Img &img, int x, int y,
                            uint32_t dst_color, uint32_t src_color, bool diag)
        {
            if (x < 0 || x >= (int) img.cols() || y < 0 || y > (int) img.rows())
                return;
            if (img.get_pixel(y, x) != src_color)
                return;

            img.set_pixel(y, x, dst_color);
            flood_fill_rec(img, x - 1, y, dst_color, src_color, diag);
            flood_fill_rec(img, x + 1, y, dst_color, src_color, diag);
            flood_fill_rec(img, x, y - 1, dst_color, src_color, diag);
            flood_fill_rec(img, x, y + 1, dst_color, src_color, diag);
            if (diag)
            {
                flood_fill_rec(img, x - 1, y - 1, dst_color, src_color, diag);
                flood_fill_rec(img, x + 1, y - 1, dst_color, src_color, diag);
                flood_fill_rec(img, x - 1, y + 1, dst_color, src_color, diag);
                flood_fill_rec(img, x + 1, y + 1, dst_color, src_color, diag);
            }
        }


    }

    void flood_fill(Img& img, int x, int y, uint32_t dst_color,
                    bool diag)
    {
        flood_fill_rec(img, x, y, dst_color, img.get_pixel(y, x), diag);
    }

    /**
     * Bezier curve using De Casteljau's algorithms
     * https://en.wikipedia.org/wiki/De_Casteljau%27s_algorithm
     * https://blog.demofox.org/2015/07/05/the-de-casteljeau-algorithm-for-evaluating-bezier-curves/
     */

    namespace
    {
        double bezier_sum3(double t, double p1, double p2, double p3)
        {
            double t2 = t * t;
            double mt = 1 - t;
            double mt2 = mt * mt;
            return mt2 * p1 + 2 * mt * t * p2 + t2 * p3;
        }
    }

    void draw_bezier3(Img& img, int x1, int y1, int x2, int y2, int x3, int y3,
                      uint32_t color)
    {
        double step = 0.01;
        int px = x1;
        int py = y1;

        for (double t = 0; t < 1; t += step)
        {
            double x = bezier_sum3(t, x1, x2, x3);
            double y = bezier_sum3(t, y1, y2, y3);
            draw_line(img, px, py, x, y, color);
            px = x;
            py = y;
        }

        draw_line(img, px, py, x3, y3, color);
    }

    namespace
    {
        double bezier_sum4(double t, double p1, double p2, double p3, double p4)
        {
            double t2 = t * t;
            double t3 = t2 * t;
            double mt = 1 - t;
            double mt2 = mt * mt;
            double mt3 = mt2 * mt;
            return mt3 * p1 + 3 * mt2 * t * p2 + 3 * mt * t2 * p3 + t3 * p4;
        }
    }

    void draw_bezier4(Img& img, int x1, int y1, int x2, int y2, int x3, int y3,
                      int x4, int y4, uint32_t color)
    {
        double step = 0.01;

        int px = x1;
        int py = y1;

        for (double t = 0; t < 1; t += step)
        {
            double x = bezier_sum4(t, x1, x2, x3, x4);
            double y = bezier_sum4(t, y1, y2, y3, y4);
            draw_line(img, px, py, x, y, color);
            px = x;
            py = y;
        }

        draw_line(img, px, py, x4, y4, color);
    }

    namespace
    {
        double bezier_sumn(double t, int pts[], int n)
        {
            double res = 0;

            for (int i = 0; i <= n; ++i)
            {
                res += (double) binomial(n, i) * std::pow(1.0 - t, n - i) * std::pow(t, i) * (double) pts[i];
            }
            return res;
        }
    }

    void draw_beziern(Img& img, int* xs, int* ys, int npts, uint32_t color)
    {
        assert(npts >= 2);
        double step = 0.01;

        int px = xs[0];
        int py = ys[0];

        for (double t = 0; t < 1; t += step)
        {
            double x = bezier_sumn(t, xs, npts - 1);
            double y = bezier_sumn(t, ys, npts - 1);
            draw_line(img, px, py, x, y, color);
            px = x;
            py = y;
        }

        draw_line(img, px, py, xs[npts - 1], ys[npts - 1], color);
    }


    void draw_img(Img& img, const Img& src, int x, int y,
                  int src_x, int src_y, int src_w, int src_h)
    {
        for (int i = 0; i < src_h; ++i)
            for (int j = 0; j < src_w; ++j)
                draw_pixel(img, x + j, y + i,
                           src.get_pixel(src_y + i, src_x + j));
    }

    void draw_sprite(Img& img, const uint8_t* data, int x, int y,
                     int src_x, int src_y, int src_w, int src_h,
                     uint32_t color)
    {
        for (int i = 0; i < src_h; ++i)
            for (int j = 0; j < src_w; ++j)
                if (sprite_get(data, src_x + j, src_y + i))
                    draw_pixel(img, x + j, y + i, color);
    }

    void draw_sprite(Img& img, const uint8_t* data,
                     int dst_x, int dst_y, int dst_w, int dst_h,
                     int src_x, int src_y, int src_w, int src_h,
                     uint32_t color)
    {
        assert(dst_w > 0);
        assert(dst_h > 0);
        double xratio = double(src_w) / dst_w;
        double yratio = double(src_h) / dst_h;

        for (int y2 = 0; y2 < dst_h; ++y2)
            for (int x2 = 0; x2 < dst_w; ++x2)
                if (bilinear_interpolation(data, src_x + x2 * xratio,
                                           src_y + y2 * yratio))
                    draw_pixel(img, dst_x + x2, dst_y + y2, color);
    }

    void draw_text(Img& img, const char* text, int x, int y,
                   int font_size, uint32_t color)
    {
        load_font();

        int sprite_height = font_size;
        int sprite_width = (double(font_width) / font_height) * sprite_height;

        for (const char* it = text; *it; ++it)
        {
            char c = *it;

            uint8_t* sprite = ascii_sprites[static_cast<int>(c)];
            if (!sprite)
                continue;

            int rows = sprite[0];
            int cols = sprite[1];

            draw_sprite(img, sprite, x, y, sprite_width, sprite_height,
                        0, 0, cols, rows, color);
            x += sprite_width + std::min(1, sprite_width  / CHAR_DEC_COEFF);
        }

    }

    void text_size_get(const char* text, int font_size,
                       int* width, int* height)
    {
        load_font();

        int sprite_height = font_size;
        int sprite_width = (double(font_width) / font_height) * sprite_height;
        *width = 0;
        *height = sprite_height;

        bool written = false;

        for (const char* it = text; *it; ++it)
        {
            char c = *it;
            uint8_t* sprite = ascii_sprites[static_cast<int>(c)];
            if (!sprite)
                continue;

            *width += sprite_width
                      + std::min(1, sprite_width  / CHAR_DEC_COEFF);
            written = true;
        }

        if (written)
            *width -= std::min(1, sprite_width  / CHAR_DEC_COEFF);
    }

}
