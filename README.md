# internal assault cube ESP & no-recoil

## Features
- chat notifications
- box ESP
- no recoil

## Usage
inject dll using a dll injector, for example mine:
- [FasterPeak Injector](https://github.com/speedaru/fasterpeak-injector)
press F1 to toggle when injected

## Description
esp is a red box around enemy playerers and green box around allies

## ESP logic
added cool logic when drawing esp inside esp.cpp so that the box looks 3d and not just a rectangle.
This is because without CalculateWidthOffset the box would be just a rectangle and so when a player appears
tilted the box would still appear as a rectangle that's not tilted and so it wouldn't be able to draw properly around the player

CalculateWidthOffset()
- calculates a vector3 from localplayer to an entity (player)
- ignores z (up axis)
- divides it by the distance so we don't take into account the distance because we just need the direction
- calculates a normal vector3 from the vector we just calculated (-y, x, 0), again we ignore z
- returns the normal vector

this also makes it so when your turn around the enemy the box continues to face you

using CalculateWidthOffset() we calculate 4 points:
- 2 using the entity pos:
    - headpos + CalculateWidthOffset()
    - headpos - CalculateWidthOffset()
- 2 using feet pos:
    - feetpos + CalculateWidthOffset()
    - feetpos - CalculateWidthOffset()

now we have 4 points around the entity and we can draw a box connecting these 4 points so now the box is nice around the player and not just a rectangle

## showcase
![image_alt](https://github.com/speedaru/ac-esp1/blob/main/showcase.png?raw=true)
