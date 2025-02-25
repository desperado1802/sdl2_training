#ifndef ENTITY_H
#define ENTITY_H

#include "object.h"
#include <vector>

class Entity : public Object
{

public:
    Entity() { rev = 0; }
    void setHealth(int h) { health = h; }
    void setMaxHealth(int h) { maxHealth = h; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int createCycle(int r, int w, int h, int amount, int speed);
    void setCurAnimation(int c)
    {
        begin = 0;
        curAnim = c;
    }
    void updateAnimation();
    void reverse(bool r) { rev = r; };
    void reverse(bool r, int newAnim)
    {
        rev = r;
        newAnimBool = true;
        newAnimation = newAnim;
    };

private:
    int health,
        maxHealth;
    struct cycle
    {
        int row;
        int w;
        int h;
        int amount;
        int speed;
        int tick;
    };
    std::vector<cycle> animations;
    int curAnim;
    int begin;
    bool rev, newAnimBool;
    int newAnimation;
};

#endif