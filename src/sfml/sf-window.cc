#include "sfml/sf-window.hh"


SfWindow::SfWindow()
    : sf::RenderWindow()
{}

SfWindow::SfWindow(sf::VideoMode mode, const sf::String& title,
                   sf::Uint32 style,
                   const sf::ContextSettings& settings)
    : sf::RenderWindow(mode, title, style, settings)
{}

SfWindow::SfWindow(sf::WindowHandle handle,
                   const sf::ContextSettings& settings)
    : sf::RenderWindow(handle, settings)
{}


void SfWindow::wait_for_close()
{
    sf::Event evt;
    while (waitEvent(evt))
    {
        if (evt.type == sf::Event::EventType::Closed)
            break;
    }
}

void SfWindow::draw_line(float x1, float y1, float x2, float y2,
                         const sf::Color& color)
{
    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = sf::Vector2f(x1, y1);
    lines[0].color = color;
    lines[1].position = sf::Vector2f(x2, y2);
    lines[1].color = color;
    draw(lines);
}

void SfWindow::fill_rect(float x, float y, float w, float h,
                         const sf::Color& color)
{
    sf::RectangleShape rect;
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(w, h));
    rect.setFillColor(color);
    draw(rect);
}

void SfWindow::poll_events()
{
    sf::Event evt;
    while (pollEvent(evt))
        continue;
}
