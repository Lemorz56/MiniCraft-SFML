#include "Character.h"
#include <iostream>

Character::Character(const std::string& filename, const int sprW, const int sprH, const int nFrames,
                     const bool eightDirs, const bool slopeMove)
{
   //loading a file in directory "filename"
   if (m_t.loadFromFile(filename))
   {
      _character = sf::Sprite(m_t);
   }

   m_animFrameX = 0; //represents starting x coordinate of first frame, default zero
   m_spriteWidth = sprW;
   m_spriteHeight = sprH;
   m_numFrames = nFrames - 1; //needs to be one less than actual amount of frames, as 0 counts as first frame

   m_dir = down; //initilizating direction (player will face down @ spawn)

   //focusing in on first frame to display upon creation, so that not the entire sprite sheet is shown
   _character.setTextureRect(sf::IntRect(0, 0, m_spriteWidth, m_spriteHeight));

   m_currentFrameTime = sf::milliseconds(0);
   m_timeToWait = sf::milliseconds(85);
   m_nextFrameTime = m_timeToWait;

   m_eightDirections = eightDirs;
   //bool value, if false 4 directional animation, if true, 8 directional animation, defaults to 4
   m_slopingMovement = slopeMove;
   //bool value, if false, character speeds are static, if true, character speed "slopes" to a limit, then slopes back down to zero upon key release

   if (m_slopingMovement)
   {
      m_xSpeed = 0.0f;
      m_ySpeed = 0.0f;
      m_xDecrease = 0.0005f;
      m_yDecrease = 0.0005f;
      m_maxSpeed = 0.01f;
   }
}

Character::~Character() = default;

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(_character);
}

//returns current Sprite object
sf::Sprite Character::GetSpriteObj()
{
   return _character;
}

void Character::charMove()
{
   if (m_slopingMovement) { charMoveSloping(); }
   if (!m_slopingMovement) { charMoveStatic(); }
   std::cout << m_dir << std::endl;
}

void Character::checkCollision(WorldObject& obj)
{
   m_collision = false; //default collision to false
   m_collisionBox = _character.getGlobalBounds();
   if (m_collisionBox.intersects(obj.getCollisionBox()))
   {
      //update collision
      m_collision = true;
      //here we are checking keyboard values instead of dir enum because dir enum can be unreliable
      //if we are using only 4-directional movement
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || m_dir == down)
      {
         _character.setPosition(_character.getPosition().x, _character.getPosition().y - 1);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
         _character.setPosition(_character.getPosition().x, _character.getPosition().y + 1);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
         _character.setPosition(_character.getPosition().x + 1, _character.getPosition().y);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
         _character.setPosition(_character.getPosition().x - 1, _character.getPosition().y);
      }
      //it is fine to check the dir enum for 8-directional collision checking
      if (m_dir == downRight)
      {
         _character.setPosition(_character.getPosition().x - 1, _character.getPosition().y - 1);
      }
      if (m_dir == downLeft)
      {
         _character.setPosition(_character.getPosition().x + 1, _character.getPosition().y - 1);
      }
      if (m_dir == upRight)
      {
         _character.setPosition(_character.getPosition().x - 1, _character.getPosition().y + 1);
      }
      if (m_dir == upLeft)
      {
         _character.setPosition(_character.getPosition().x + 1, _character.getPosition().y + 1);
      }
   }
}

void Character::charMoveStatic()
{
   bool isMoving = false;

   if (m_eightDirections)
   {
      //if using 8 directional sprite sheet
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !
         sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
         _character.move(-m_moveSpeed, 0);
         m_dir = left;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !
         sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
         _character.move(m_moveSpeed, 0);
         m_dir = right;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !
         sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
         _character.move(0, -m_moveSpeed);
         m_dir = up;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !
         sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
         _character.move(0, m_moveSpeed);
         m_dir = down;
      }

      //8-directional stuff
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
         _character.move(-m_moveSpeed, -m_moveSpeed);
         m_dir = upLeft;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
         _character.move(m_moveSpeed, -m_moveSpeed);
         m_dir = upRight;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
         _character.move(-m_moveSpeed, m_moveSpeed);
         m_dir = downLeft;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
         _character.move(m_moveSpeed, m_moveSpeed);
         m_dir = downRight;
      }
   }
   else
   {
      //if no 8 directional animation to take place
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      {
         _character.move(-m_moveSpeed, 0);
         m_dir = left;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      {
         _character.move(m_moveSpeed, 0);
         m_dir = right;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
         _character.move(0, -m_moveSpeed);
         m_dir = up;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
         _character.move(0, m_moveSpeed);
         m_dir = down;
      }
   }

   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
      || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
   {
      isMoving = true;
   }

   animate(isMoving);
}

void Character::charMoveSloping()
{
   bool isMoving = false;

   //setting speed variables depending on input
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_xSpeed < m_maxSpeed)
   {
      m_xSpeed += (m_nextFrameTime - m_currentFrameTime).asMilliseconds() * .000025f;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_xSpeed > -m_maxSpeed)
   {
      m_xSpeed -= (m_nextFrameTime - m_currentFrameTime).asMilliseconds() * .000025f;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_ySpeed < m_maxSpeed)
   {
      m_ySpeed += (m_nextFrameTime - m_currentFrameTime).asMilliseconds() * .000025f;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_ySpeed > -m_maxSpeed)
   {
      m_ySpeed -= (m_nextFrameTime - m_currentFrameTime).asMilliseconds() * .000025f;
   }

   //resetting speed to zero if right/left keys pressed at same time, or if up/down keys pressed at same time
   if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
   {
      m_xSpeed = 0;
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
   {
      m_ySpeed = 0;
   }

   //stopping movement if no user input
   if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_xSpeed > 0)
   {
      m_xSpeed -= m_xDecrease;
      if (m_xSpeed < 0)
      {
         m_xSpeed = 0;
      }
   }
   if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_xSpeed < 0)
   {
      m_xSpeed += m_xDecrease;
      if (m_xSpeed > 0)
      {
         m_xSpeed = 0;
      }
   }
   if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_ySpeed < 0)
   {
      m_ySpeed += m_yDecrease;
      if (m_ySpeed > 0)
      {
         m_ySpeed = 0;
      }
   }
   if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_ySpeed > 0)
   {
      m_ySpeed -= m_yDecrease;
      if (m_ySpeed < 0)
      {
         m_ySpeed = 0;
      }
   }

   //finding direction
   if (m_xSpeed < 0) { m_dir = left; }
   if (m_xSpeed > 0) { m_dir = right; }
   if (m_ySpeed < 0) { m_dir = up; }
   if (m_ySpeed > 0) { m_dir = down; }

   if (m_eightDirections)
   {
      if (m_xSpeed < 0 && m_ySpeed < 0) { m_dir = upLeft; }
      if (m_xSpeed > 0 && m_ySpeed < 0) { m_dir = upRight; }
      if (m_xSpeed < 0 && m_ySpeed > 0) { m_dir = downLeft; }
      if (m_xSpeed > 0 && m_ySpeed > 0) { m_dir = downRight; }
   }

   //actually moving character
   _character.move(m_xSpeed, m_ySpeed);

   //calling animate function
   if (m_xSpeed != 0 || m_ySpeed != 0) { isMoving = true; }
   else { isMoving = false; }
   animate(isMoving);
}

//is called during every update from move function
//need to pass a boolean value representing whether the player is moving
void Character::animate(bool isMoving)
{
   //finds the exact time that current frame executes
   //time value for "next frame" is initialized in constructor
   m_currentFrameTime = m_frameTimer.getElapsedTime();

   if (m_currentFrameTime > m_nextFrameTime)
   {
      //execute if the current frame time has surpassed the next frame's expected display time
      m_nextFrameTime = m_currentFrameTime + m_timeToWait;
      if (isMoving)
      {
         //if player is currently moving, anime sprite
         m_animFrameX = m_animFrameX + m_spriteWidth;
         //increments frame value to next frame in animation, but this value is only used when it is time for next frame to be displayed
         if (m_animFrameX >= (m_spriteWidth * m_numFrames)) { m_animFrameX = 0; }
         //resets frame to starting point if last frame in sequence has been displayed
      }
      else
      {
         //if player is NOT moving, reset to first frame
         m_animFrameX = 0;
      }
      _character.setTextureRect(sf::IntRect(m_animFrameX, m_dir * m_spriteHeight, m_spriteWidth, m_spriteHeight));
      //finds appropriate "frame" in tileset, assigns to sprite
   }
}
