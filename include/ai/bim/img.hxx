#pragma once

#include "img.hh"
#include <algorithm>
#include <cassert>

#include <iostream>

namespace bim {

    inline Img::Img()
            : rows_(0), cols_(0), channels_(0), data_(nullptr) {}

    inline Img::Img(std::size_t rows, std::size_t cols, std::size_t channels)
            : rows_(rows), cols_(cols), channels_(channels), data_(new uint8_t[rows * cols * channels]) {}

    inline Img::Img(Img &&img)
            : rows_(img.rows_), cols_(img.cols_), channels_(img.channels_), data_(img.data_) {
        img.data_ = nullptr;
    }

    inline Img::~Img() {
        delete[] data_;
    }

    inline void Img::assign(std::size_t rows,
                            std::size_t cols,
                            std::size_t channels) {
        delete[] data_;
        rows_ = rows;
        cols_ = cols;
        channels_ = channels;
        data_ = new uint8_t[rows * cols * channels];
    }

    inline bool Img::empty() const {
        return data_ == nullptr;
    }

    inline std::size_t Img::rows() const {
        return rows_;
    }

    inline std::size_t Img::cols() const {
        return cols_;
    }

    inline std::size_t Img::channels() const {
        return channels_;
    }

    inline std::size_t Img::total() const {
        return rows_ * cols_ * channels_;
    }

    inline const std::uint8_t *Img::begin() const {
        return data_;
    }

    inline std::uint8_t *Img::begin() {
        return data_;
    }

    inline const std::uint8_t *Img::end() const {
        return data_ + total();
    }

    inline std::uint8_t *Img::end() {
        return data_ + total();
    }


    inline uint32_t Img::get_pixel(std::size_t i, std::size_t j) const {
        assert(i < rows_);
        assert(j < cols_);
        uint32_t res = 0;
        uint8_t *output = reinterpret_cast<uint8_t *>(&res);
        std::copy_n(begin() + (i * cols_ + j) * channels_, channels_, output);
        return res;
    }

    inline void Img::set_pixel(std::size_t i, std::size_t j, uint32_t c) {
        assert(i < rows_);
        assert(j < cols_);
        const uint8_t *input = reinterpret_cast<const uint8_t *> (&c);
        std::copy_n(input, channels_, begin() + (i * cols_ + j) * channels_);
    }

    inline void Img::fill_pixels(uint32_t c) {
        const uint8_t *input = reinterpret_cast<const uint8_t *> (&c);
        for (uint8_t *output = begin(); output != end(); output += channels_)
            std::copy_n(input, channels_, output);
    }

    inline Color Img::color_get(std::size_t i, std::size_t j) const {
        auto val = get_pixel(i, j);
        if (channels() == 3)
            return Color::from_rgb(val);

        else
            return Color::from_rgb(val);
    }

    inline void Img::color_set(std::size_t i, std::size_t j, const Color &c)
    {
        if (channels() == 3)
            set_pixel(i, i, c.rgb());

        else
            set_pixel(i, j, c.rgb());
    }

}
