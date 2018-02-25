#include "graphics/gui-lib.hh"
#include <cstdio>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "io/filesystem.hh"
#include "io/path.hh"

#include <iostream>




namespace
{

    const char* TEMP_PATH = "temp.data";
    const char* DATA_PATH = "~/gui-server\\data\\cmds.data";
    const char* RES_DIR = "~/gui-server\\public\\res\\";

    std::vector<std::string> cmds_list;

    void add_cmd(const std::string& cmd)
    {
        cmds_list.push_back(cmd);
    }

    std::string color2str(const Color& c)
    {
        char data[17] = "0123456789abcdef";
        std::string res;

        res += data[c.r() / 16];
        res += data[c.r() % 16];
        res += data[c.g() / 16];
        res += data[c.g() % 16];
        res += data[c.b() / 16];
        res += data[c.b() % 16];
        res += data[c.a() / 16];
        res += data[c.a() % 16];

        return res;
    }

    void send_cmds()
    {
        {
            std::ofstream fs(TEMP_PATH);
            for (const auto& cmd: cmds_list)
                fs << cmd << "\n";
            fs.flush();
            fs.close();
        }

        std::rename(TEMP_PATH, DATA_PATH);
    }

    void clear_cmds()
    {
        cmds_list.clear();
    }

    std::string unique_str()
    {
        static int n = 0;
        int val = n++;

        return std::to_string(val);
    }

    std::map<std::string, std::string> ress_files;

    std::string get_ress_file(const std::string& path)
    {
        auto it = ress_files.find(path);
        if (it != ress_files.end())
            return it->second;

        std::string name = unique_str() + path::basename(path);

        filesystem::copy_file(path, RES_DIR + name);
        ress_files[path] = name;
        return name;
    }
}

namespace guilib {

    void clear()
    {
        add_cmd("clear");
    }

    void draw_pixel(int x, int y, const Color& c)
    {
        add_cmd("pixel " + std::to_string(x) + " " + std::to_string(y)
            + " " + color2str(c));
    }

    void draw_line(int x1, int y1, int x2, int y2, const Color &c)
    {
        add_cmd("line " + std::to_string(x1) + " " + std::to_string(y1)
                + " " + std::to_string(x2) + " " + std::to_string(y2)
                + " " + color2str(c));
    }

    void draw_circle(int x1, int y1, int r, const Color &c)
    {
        add_cmd("dcircle " + std::to_string(x1) + " " + std::to_string(y1)
                + " " + std::to_string(r) + " " + color2str(c));
    }

    void fill_circle(int x1, int y1, int r, const Color& c)
    {
        add_cmd("fcircle " + std::to_string(x1) + " " + std::to_string(y1)
                + " " + std::to_string(r) + " " + color2str(c));
    }

    void draw_rect(int x, int y, int w, int h, const Color& c)
    {
        add_cmd("drect " + std::to_string(x) + " " + std::to_string(y)
                + " " + std::to_string(w) + " " + std::to_string(h)
                + " " + color2str(c));
    }

    void fill_rect(int x, int y, int w, int h, const Color& c)
    {
        add_cmd("frect " + std::to_string(x) + " " + std::to_string(y)
                + " " + std::to_string(w) + " " + std::to_string(h)
                + " " + color2str(c));
    }

    void draw_ellipse(int x, int y, int w, int h, const Color& c)
    {
        add_cmd("dellipse " + std::to_string(x) + " " + std::to_string(y)
                + " " + std::to_string(w) + " " + std::to_string(h)
                + " " + color2str(c));
    }

    void fill_ellipse(int x, int y, int w, int h, const Color& c)
    {
        add_cmd("fellipse " + std::to_string(x) + " " + std::to_string(y)
                + " " + std::to_string(w) + " " + std::to_string(h)
                + " " + color2str(c));
    }

    void draw_polygon(int* begin, int* end, const Color& c)
    {
        std::string cmd = "dpolygon ";
        for (int* it = begin; it != end; ++it)
            cmd += std::to_string(*it) + " ";
        cmd += color2str(c);
        add_cmd(cmd);
    }

    void fill_polygon(int* begin, int* end, const Color& c)
    {
        std::string cmd = "fpolygon ";
        for (int* it = begin; it != end; ++it)
            cmd += std::to_string(*it) + " ";
        cmd += color2str(c);
        add_cmd(cmd);
    }

    void draw_img(const char* path, double angle,
                  int src_x, int src_y, int src_w, int src_h,
                  int dst_x, int dst_y, int dst_w, int dst_h)
    {
        add_cmd("img " + get_ress_file(path) + " " + std::to_string(angle)
                + " " + std::to_string(src_x) + " " + std::to_string(src_y)
                + " " + std::to_string(src_w) + " " + std::to_string(src_h)
                + " " + std::to_string(dst_x) + " " + std::to_string(dst_y)
                + " " + std::to_string(dst_w) + " " + std::to_string(dst_h));
    }

    void draw_text(int x, int y, const char* font, int size, const Color& c,
                   const char* str, double angle)
    {
        add_cmd("text " + std::to_string(x) + " " + std::to_string(y)
                + " " + std::string(font) + " " + std::to_string(size)
                + " " + color2str(c) + " " + str
                + " " + std::to_string(angle));
    }

    void draw_img(const bim::Img& img, int x, int y)
    {
        char code[17] = "0123456789abcdef";

        std::string cmd = "bimg " + std::to_string(x) + " " + std::to_string(y)
                          + " " + std::to_string(img.rows()) + " "
                          + std::to_string(img.cols()) + " ";

        for (const uint8_t* it = img.begin(); it != img.end(); ++it) {
            cmd += code[*it / 16];
            cmd += code[*it % 16];
        }

        add_cmd(cmd);
    }


    void render()
    {
        send_cmds();
        clear_cmds();
    }

    void render_img(const bim::Img& img)
    {
        char code[17] = "0123456789abcdef";

        {
            std::ofstream fs(TEMP_PATH);

            fs << "clear\n";
            fs << "bimg 0 0 " << std::to_string(img.rows())
               << " " << std::to_string(img.cols()) << " ";

            for (const uint8_t* it = img.begin(); it != img.end(); ++it) {
                fs << code[*it / 16];
                fs << code[*it % 16];
            }

            fs << "\n";

            fs.flush();
            fs.close();
        }

        std::rename(TEMP_PATH, DATA_PATH);
    }

}
