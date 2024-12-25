#include "entity.h"

int Entity::createCycle(int r, int w, int h, int amount, int speed)
{
    cycle temp;
    temp.row = r - 1;
    temp.w = w;
    temp.h = h;
    temp.amount = amount;
    temp.tick = 0;
    temp.speed = speed;

    animations.push_back(temp);
    return animations.size() - 1;
};

void Entity::updateAnimation()
{
    setSource(animations[curAnim].w * animations[curAnim].tick,
              animations[curAnim].row * animations[curAnim].h,
              animations[curAnim].w,
              animations[curAnim].h);

    if (begin > animations[curAnim].speed)
    {
        if (!rev)
            animations[curAnim].tick++;
        if (rev)
            animations[curAnim].tick--;
        begin = 0;
    }
    begin++;

    if (animations[curAnim].tick >= animations[curAnim].amount)
    {
        animations[curAnim].tick = 0;
    }

    if (animations[curAnim].tick <= 0)
    {
        if (newAnimBool)
        {
            setCurAnimation(newAnimation);
            newAnimBool = false;
            rev = false;
        }
        else
        {
            animations[curAnim].tick = 0;
        }
    }
};
