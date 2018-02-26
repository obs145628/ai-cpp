#pragma once

#include <SFML/Graphics.hpp>

class SfWindow : public sf::RenderWindow
{

public:

    SfWindow();
    SfWindow(sf::VideoMode mode, const sf::String& title,
             sf::Uint32 style = sf::Style::Default,
             const sf::ContextSettings& settings = sf::ContextSettings{});
    SfWindow(sf::WindowHandle handle,
             const sf::ContextSettings& settings = sf::ContextSettings{});

    void wait_for_close();

    void draw_line(float x1, float y1, float x2, float y2,
                   const sf::Color& color);
    void fill_rect(float x, float y, float w, float h,
                   const sf::Color& color);

    /**
     * Poll all events
     * Make sure window doesn't block
     */
    void poll_events();



private:



};
