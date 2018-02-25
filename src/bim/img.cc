#include "bim/img.hh"

namespace bim
{

    Img Img::load_mono_sprite(const uint8_t* data, std::size_t channels,
                              uint32_t fg_color, uint32_t bg_color)
    {
        std::size_t rows = data[0];
        std::size_t cols = data[1];
        data += 2;
        Img img(rows, cols, channels);
        img.fill_pixels(0);

        for (std::size_t i = 0; i < rows; ++i)
            for (std::size_t j = 0; j < cols; ++j)
                img.set_pixel(i, j, data[i * cols + j] ? fg_color : bg_color);

        return img;
    }

}
