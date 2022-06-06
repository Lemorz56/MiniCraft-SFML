#pragma once
#include <SFML/Graphics.hpp>
#include "WorldObject.h"
#include <string>

//basic "character" class that creates an in game character
//sprite directory is specified in constructor argument along with dimensions in sprite sheet
//example instantiation:
//Character foo("spritedirectory.png");

class Character : public sf::Drawable //publically inheriting from "Drawable" class for cleaner syntax when drawing to screen
{
private:
    sf::Sprite _character;

    //the texture needs to be a private variable so it does not go out of scope until destructor
    sf::Texture m_t;

   //used in conjunction with sprite sheet
   //directions should correspond to actual order of animatoin rows on sprite sheet
    enum Facing
    {
        down = 0,//row zero on sprite sheet
        left = 1,//row one on sprite sheet
        up = 3,//row two on sprite sheet
        right = 2,//row three on sprite sheet
        //these are used for 8 directional animation!
        downLeft = 4,
        downRight = 5,
        upLeft = 6,
        upRight = 7,
    };
    Facing m_dir;//dir represents not only direction but also the "row" on the sprite shee that is being used for animation

    sf::Clock m_frameTimer;//used for timing frame switches
    sf::Time m_currentFrameTime;//records current frame's time
    sf::Time m_nextFrameTime;//represents time @ which next frame should be played
    sf::Time m_timeToWait;//time between frames

    int m_animFrameX;//frame number origin in animation, defaults to zero
    int m_spriteWidth;
    int m_spriteHeight;
    int m_numFrames;

    bool m_slopingMovement;//bool passed to constructor to decide movement method

    float m_xSpeed;//used for sloping movement
    float m_ySpeed;
    float m_xDecrease;
    float m_yDecrease;
    float m_maxSpeed;
    sf::FloatRect m_collisionBox;
    bool m_collision;

    float m_moveSpeed = 4.15f;//used for static movement - 0.015f

    bool m_eightDirections;

public:
    Character(std::string filename, int sprW, int sprH, int nFrames, bool eightDir = false, bool slopingMovement = false);
    ~Character();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void charMove();
    virtual void charMoveStatic();
    virtual void charMoveSloping();
    virtual void animate(bool isMoving);
    void checkCollision(WorldObject& obj);
    sf::Sprite GetSpriteObj();
};
