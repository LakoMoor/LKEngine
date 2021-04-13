#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "../State/State.hpp"

class Core
{



public:

void LKESprite();
void LKERender();
void LKETextures();
void LKEControls();
void LKEClock();
void LKETimeGame();
void LKEFont();
void LKEDiscord();

void LKEHero();
void LKEMap();
void LKEMapSprite();

void LKEFrame();

Core();


private:
RenderWindow window;
Sprite herosprite;

//Font font;
//Text text;

Sprite maptexture;
Sprite mapsprt;

Texture herotexture;

Texture mapTexture;
Texture maptex;

bool GameErrorClose = false;

Clock clock;
Clock GameTimeClock;
float time;
float timeInGame = clock.getElapsedTime().asMicroseconds(); 
int GameTime = 0;
float heroteleporttimer = 0;
float CurrentFrame=0;
//Player p;


};



#endif // !GAME_HPP
