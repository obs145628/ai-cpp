#pragma once

#include <cstdint>
#include "color.hh"

namespace bim
{

    class Img
    {
    public:


        static Img load_mono_sprite(const uint8_t * data, std::size_t channels,
                                    uint32_t fg_color, uint32_t bg_color);

        Img();
        Img(std::size_t rows, std::size_t cols, std::size_t channels);
        Img(const Img&) = delete;
        Img(Img&& img);
        Img&operator=(const Img& img) = delete;
        Img&operator=(Img&&) = delete;
        ~Img();

        void assign(std::size_t rows, std::size_t cols, std::size_t channels);

        bool empty() const;
        std::size_t rows() const;
        std::size_t cols() const;
        std::size_t channels() const;
        std::size_t total() const;
        const std::uint8_t* begin() const;
        std::uint8_t* begin();
        const std::uint8_t* end() const;
        std::uint8_t* end();

        uint32_t get_pixel(std::size_t i, std::size_t j) const;
        void set_pixel(std::size_t i, std::size_t j, uint32_t c);
        void fill_pixels(uint32_t c);

        Color color_get(std::size_t i, std::size_t j) const;
        void color_set(std::size_t i, std::size_t j, const Color& c);

    private:
        std::size_t rows_;
        std::size_t cols_;
        std::size_t channels_;
        std::uint8_t* data_;
    };

}

#include "img.hxx"
