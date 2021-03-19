#include "Game.hpp"
//#include "../Config/map.hpp"
#include "../Player/View.hpp"
#include "../Player/Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
    /////////////////////////////////////////////////
   ///              LKEngine                     ///
  /////////////////////////////////////////////////
 ///                                           ///
/////////////////////////////////////////////////

Player p("hero.png",250,250,96.0,96.0);


void Core::LKERender()
{
    //TEXT
    Font font;
    Text text("", font, 20);
    if (font.loadFromFile("res/font.ttf")) {
      cout << "SUCC FONT LOAD" << endl;
    } else {
      cout << "ERR:FONT" << endl;
      GameErrorClose = true; //ERROR close window
    }

    //
 
    ifstream ifs("settings/config.lke");
    string title = "None";
    VideoMode windows_bounds(640,480);
    unsigned framerate_limit = 60;
    bool vertical_sync_enabled = false;

    if(ifs.is_open())
    {
        getline(ifs, title);
        getline(ifs, title);
        getline(ifs, title);
        getline(ifs, title);
        getline(ifs, title);      
        ifs >> windows_bounds.width >> windows_bounds.height;       
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    ifs.close();
    //

    //Loading window render
    RenderWindow window(windows_bounds, "LKEngine");
    CamView.reset(FloatRect(0, 0, 640, 480));
    window.setFramerateLimit(framerate_limit);
    window.setVerticalSyncEnabled(vertical_sync_enabled);
    
    //
    LKETextures();
    LKESprite();
    LKEMapSprite();
    heroteleporttimer = 0;
    CurrentFrame=0;
    LKETimeGame();
    //LKEFont();
    //

    while (window.isOpen())
	{
        timeInGame;
        LKEClock();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)			
			window.close();
		}
        LKEControls(); //Controls function 
        window.clear(Color(0, 151, 255));
        p.Update(time);
        ViewMap(time);
        ChangeView();

        //Map render
        for(int i = 0; i < HEIGHT_MAP; i++)
        {
            for(int j = 0; j < WIDTH_MAP; j++)
            {
                if(TileMap[i][j] == ' ')
                    mapsprt.setTextureRect(IntRect(161, 0, 32, 32));
                if(TileMap[i][j] == '0')
                    mapsprt.setTextureRect(IntRect(64, 0, 32, 32));
                if(TileMap[i][j] == 's')
                    mapsprt.setTextureRect(IntRect(32, 0, 32, 32));
                if(TileMap[i][j] == 'f')
                    mapsprt.setTextureRect(IntRect(96, 0, 32, 32));
                if(TileMap[i][j] == 'h')
                    mapsprt.setTextureRect(IntRect(128, 0, 32, 32));
                if(TileMap[i][j] == 'c')
                    mapsprt.setTextureRect(IntRect(192, 0, 32, 32));
                mapsprt.setPosition(j*32,i*32);
                window.draw(mapsprt);
                //cout << "MAP LOAD" << endl;
            }
        }
        //

        //
        if(GameErrorClose == true)
        {
            window.close();
        }
        //

        //
        if(p.life)
            GameTime = GameTimeClock.getElapsedTime().asSeconds();
        //

        window.setView(CamView); //camera view

        // Score hud
        ostringstream PlayerHealthString, GameTimeString, PlayerScoreCoin;
        PlayerScoreCoin << p.PlayerScore;
        PlayerHealthString << p.Health;
        GameTimeString << GameTime;
        text.setColor(Color::Black);
        text.setStyle(Text::Bold | Text::Underlined);
        text.setString("Health:" + PlayerHealthString.str()+"\nCoins: " + PlayerScoreCoin.str() +"\nTime in Game:" + GameTimeString.str());
        text.setPosition(CamView.getCenter().x -300, CamView.getCenter().y - 240);      
        //

		window.draw(p.sprite);
        window.draw(text);
		window.display();
    }
}

void Core::LKETimeGame()
{
    clock.restart();
    timeInGame = timeInGame/800;
}

void Core::LKEClock()
{
    time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time/800;
    //cout << time << endl;
}

void Core::LKEControls()
{
    if(p.life)
    {
        if (Keyboard::isKeyPressed(Keyboard::Left)) //
        {
            p.dir = 1;
            p.speed = 0.1;
            LKEFrame();
            p.sprite.setTextureRect(IntRect(96*int(CurrentFrame), 96, 96, 96));
            //GetPlayerCorView();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) //
        {
            p.dir = 0;
            p.speed = 0.1;        
            LKEFrame();
            p.sprite.setTextureRect(IntRect(96*int(CurrentFrame), 192, 96, 96));
        } 
        if (Keyboard::isKeyPressed(Keyboard::Up)) //
        {
            p.dir = 3;
            p.speed = 0.1;        
            LKEFrame(); 
            p.sprite.setTextureRect(IntRect(96*int(CurrentFrame), 307, 96, 96));
        } 

        if (Keyboard::isKeyPressed(Keyboard::Down)) //
        {
            p.dir = 2;
            p.speed = 0.1; 
            LKEFrame(); 
            p.sprite.setTextureRect(IntRect(96*int(CurrentFrame), 0, 96, 96)); 
        }  
        //if (Mouse::isButtonPressed(Mouse::Left)){this->herosprite->setColor(Color::Blue);}
        //if (Mouse::isButtonPressed(Mouse::Right)){this->herosprite->setColor(Color::White);}
    }
    GetPlayerCorView(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY());
}

void Core::LKESprite()
{

}

/*void Core::LKEFont()
{
    if (!font.loadFromFile("res/CyrilicOld.TTF"))
    {
        cout << "ERR" << endl;
        window.close();
    }
    else 
    {
        cout << "SUCC FONT LOAD" << endl;
    }
    //text.setColor(Color::Red);
    text.setStyle(Text::Bold | Text::Underlined);
    text.setString("Камни:");
    text.setPosition(CamView.getCenter().x, CamView.getCenter().y);
}
*/
void Core::LKEMapSprite()
{
    mapsprt.setTexture(maptex);
}

void Core::LKETextures()
{
    //this->herotexture->loadFromFile("res/hero.png");

    if(!herotexture.loadFromFile("res/hero.png"))
    {        
        cout << "ERR:HERO" << endl;
        GameErrorClose = true; //ERROR close window
    }
    else 
    {
        cout << "SUCC TEX LOAD" << endl;
    }
    
    if(!mapTexture.loadFromFile("res/grass.png"))
    {        
        cout << "ERR:SKY" << endl;
        GameErrorClose = true; //ERROR close window    
    }
    else 
    {
        cout << "SUCC SKY LOAD" << endl;
    }  

    if(!maptex.loadFromFile("res/map.png"))
    {        
        cout << "ERR: MAP" << endl;
        GameErrorClose = true; //ERROR close window
    }
    else 
    {
        cout << "SUCC MAP LOAD" << endl;
    } 
}
/*
void Core::LKEMap()
{
    for(int i = 0; i < HEIGHT_MAP; i++)
    for(int j = 0; j < WIDTH_MAP; j++)
    {
        if(TileMap[i][j] == ' ')
            mapsprt.setTextureRect(IntRect(0, 0, 32, 32));
        if(TileMap[i][j] == '0')
            mapsprt.setTextureRect(IntRect(64, 0, 32, 32));
        if(TileMap[i][j] == 's')
            mapsprt.setTextureRect(IntRect(32, 0, 32, 32));
        mapsprt.setPosition(j*32,i*32);
        window.draw(mapsprt);
        //cout << "MAP LOAD" << endl;
    }
}
*/
void Core::LKEHero()
{
    /*heroteleporttimer += time;
    if(heroteleporttimer > 3000)
    {
        herosprite.setPosition(0,120);
        heroteleporttimer = 0;
    }*/
}

void Core::LKEFrame()
{
    CurrentFrame += 0.005*time;
    if(CurrentFrame>3)
        CurrentFrame -= 3;
}

Core::Core()
{
    this -> LKERender();
}

