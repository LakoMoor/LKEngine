#include "../State/State.hpp"
#include <SFML/Graphics.hpp>

sf::View CamView;

void GetPlayerCorView(float x, float y)
{
    CamView.setCenter(x+100, y);
}

void ViewMap(float time)
{
    if(Keyboard::isKeyPressed(Keyboard::D))
        CamView.move(0.1*time, 0);
    if(Keyboard::isKeyPressed(Keyboard::S))
        CamView.move(0, 0.1*time);
    if(Keyboard::isKeyPressed(Keyboard::A))
        CamView.move(-0.1*time, 0);
    if(Keyboard::isKeyPressed(Keyboard::W))
        CamView.move(0,-0.1*time);

}

void ChangeView()
{
    if(Keyboard::isKeyPressed(Keyboard::U))
        CamView.zoom(1.0100f);
    //if(Keyboard::isKeyPressed(Keyboard::R))
    //    CamView.rotate(1);
    if(Keyboard::isKeyPressed(Keyboard::I))
        CamView.setSize(640, 480);
    if(Keyboard::isKeyPressed(Keyboard::P))
        CamView.setSize(540, 380);
    //if(Keyboard::isKeyPressed(Keyboard::Q))
    //    CamView.setViewport(FloatRect(0, 0, 0.5f, 1));
}