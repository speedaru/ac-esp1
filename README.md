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

using CalculateWidthOffset() we calculate 4 points:
- 2 using the entity pos:
    - headpos + CalculateWidthOffset()
    - headpos - CalculateWidthOffset()
- 2 using feet pos:
    - feetpos + CalculateWidthOffset()
    - feetpos - CalculateWidthOffset()

now we have 4 points around the entity and we can draw a box connecting these 4 points so now the box is nice around the player and not just a rectangle

## showcase
![image_alt]([https://github.com/speedaru/ac-esp1/issues/1](https://private-user-images.githubusercontent.com/165056498/428421874-ae076c27-bc76-4806-9c1b-11e8a49b72c9.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDMzNjI2NzMsIm5iZiI6MTc0MzM2MjM3MywicGF0aCI6Ii8xNjUwNTY0OTgvNDI4NDIxODc0LWFlMDc2YzI3LWJjNzYtNDgwNi05YzFiLTExZThhNDliNzJjOS5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMzMwJTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDMzMFQxOTE5MzNaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1hNzQyZTE5ODRhMTI0Y2M0YmIxYzhmNWI0Y2Q1MzQ1MzIxODc3NjFjZWE4NmU1ZjBiNTdkNDkzZjc2YTc1MTY4JlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.UE98QpbxP_p10g80jPH9QuQde8IpKUAZZ7smg6tQxRg))
