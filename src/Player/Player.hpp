#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../State/State.hpp"
#include "../Config/map.hpp"

class Player
{
public:
    float x, y, w, h, dx, dy, speed = 0;
    int dir, PlayerScore, Health;
    bool life;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    Player(String F, float X, float Y, float W, float H)
    {
        dir = 0; 
        speed = 0;
        PlayerScore = 0;
        Health = 100;
        life = true;
        File = F;
        w = W;
        h = H;
        image.loadFromFile("res/" + File);
        image.createMaskFromColor(Color(41, 33, 59));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X;
        y = Y;
        sprite.setTextureRect(IntRect(0, 0, w, h));
    }

    void Update(float time)
    {
        switch (dir)
        {
            case 0:    
                dx = speed; 
                dy = 0;
                break;
            case 1: 
                dx = -speed; 
                dy = 0;
                break;
            case 2: 
                dx = 0;
                dy = speed;
                break;
            case 3:
                dx = 0;
                dy = -speed;
                break;
        }

        x += dx*time;
        y += dy*time;

        speed = 0;
        sprite.setPosition(x,y);
        InteractionMap();
        if(Health <= 0)
        {
            life = false;
            speed = 0;
        }
    }

    void InteractionMap()
    {
        for (int i = y /32; i < (y+h)/32; i++)
        for (int j = x/32; j <(x+w)/32; j++)
        {
            if(TileMap[i][j] == '0')
            {
                if (dy > 0)
                    y = i*32-h;
                if (dy < 0)
                    y = i*32+32;
                if(dx > 0)
                    x = j * 32 - w;
                if(dx < 0)
                    x = j*32+32;
            }
            if(TileMap[i][j] == 's')
            {
                PlayerScore++;
                TileMap[i][j] = ' ';
            }
            if(TileMap[i][j] == 'f')
            {
                Health -= 40;
                TileMap[i][j] = ' ';
            }
            if(TileMap[i][j] == 'h')
            {
                Health += 10;
                TileMap[i][j] = ' ';
            }
        }
    }

};

#endif // !PLAYER_HP

