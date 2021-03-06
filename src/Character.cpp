#include "../headers/include/Character.h"
#include "math.h"

Character::Character(const Vector2f &pos)
{
    // Cargando texturas
    textCharIdle.loadFromFile("./assets/characters/1 Woodcutter/Woodcutter_idle.png");
    textCharRun.loadFromFile("./assets/characters/1 Woodcutter/Woodcutter_run.png");
    textCharAtk.loadFromFile("./assets/characters/1 Woodcutter/Woodcutter_attack1.png");
    textCharJump.loadFromFile("./assets/characters/1 Woodcutter/Woodcutter_jump.png");
    spChar.setTexture(textCharIdle);
    spChar.setPosition(pos);
    //Hit-box
    body.setSize(Vector2f(48.0f, 48.0f));
    body.setPosition(pos);
    body.setFillColor(Color::Transparent);
    // Animacion
    charAnim.setAnim(&textCharIdle, 4, 0.1f);
}

void Character::update(float elapsed)
{
    // Movimiento del personaje
    deltaTime = clock.restart().asSeconds();

    if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
    {
        spChar.setTexture(textCharRun);
        charAnim.setnFrames(6);
        spChar.move(-charVel, 0);
        body.move(-charVel, 0);
        faceR = false;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
    {
        spChar.setTexture(textCharRun);
        charAnim.setnFrames(6);
        spChar.move(charVel, 0);
        body.move(charVel, 0);
        faceR = true;
    }
    else if (Keyboard::isKeyPressed(Keyboard::W))
    {
        if (faceR)
        {
            spChar.setTexture(textCharJump);
            charAnim.setnFrames(6);
            float y_ofset = -sqrtf(2.0f * 1200.0f * jumpheight);
            spChar.move(charVel, y_ofset);
            body.move(charVel, y_ofset);
        }
        else
        {
            spChar.setTexture(textCharJump);
            charAnim.setnFrames(6);
            float y_ofset = -sqrtf(2.0f * 1200.0f * jumpheight);
            spChar.move(-charVel, y_ofset);
            body.move(-charVel, y_ofset);
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::J))
    {
        spChar.setTexture(textCharAtk);
        charAnim.setnFrames(6);
    }
    else
    {
        spChar.setTexture(textCharIdle);
        charAnim.setnFrames(4);
    }

    charAnim.updateAnim(deltaTime, faceR);
    spChar.setTextureRect(charAnim.uvRect);

    // Limitar el movimiento del personaje
    Vector2f charPos = spChar.getPosition();
    if (charPos.x < 0)
        charPos.x = 0;
    if (charPos.x > 500)
        charPos.x = 500;
    if (charPos.y < 210)
        charPos.y+=3.0f;
    if (charPos.y < 0)
        charPos.y = 0;
    spChar.setPosition(charPos);
    body.setPosition(charPos);
}

void Character::draw(RenderWindow &window)
{
    window.draw(body);
    window.draw(spChar);
}

Sprite Character::getSprite()
{
    return spChar;
}

// Pendiente enemy
bool Character::collidesWithEnemy(Enemy *e)
{

    FloatRect charRect = getSprite().getGlobalBounds();
    FloatRect ballRect = e->getSprite().getGlobalBounds();
    return charRect.intersects(ballRect);
}
