# Sprite Ordering And Camera Culling

## A research project about sprite sorting and camera culling
***

## Introduction

I am Pol Rius, student of the Degree in Video Games by UPC at CITM. This content is generated for the Research project.
***

## Sprite Sorting

At some point in game development, it appears a big problem when it comes to render sprites, sprite overlapping and, in order to fix that we will have to sort the sprites dynamically.
Sorting sprites will provide the player the illusion of depth, even if it’s a 2D game.

A few games that follow a sprite rendering order are:

### Street Fighter 2:
![Street Fighter 2](https://img.redbull.com/images/c_limit,w_1500,h_1000,f_auto,q_auto/redbullcom/2017/05/26/8e9df911-f4d9-48c0-81cf-a7f1a3a01b9a/ultra-street-fighter-2-nintendo-switch)

As you can see, it follows the order of background sprite, ground sprite, players sprites and SpecialAttacks sprite.

### The Binding of Isaac:

![TheBindingOfIsaac](https://image.noelshack.com/fichiers-sm/2015/26/1435235106-647-noelshack-capture-d-ecran.gif)

Another example would be The binding of isaac, but in this example it takes into account the position of the entity in the Y-axis. And depending on which entity is in front or behind of the other, the one that is ahead will overlap the other. 
***

## Camera Culling

It is a method that empower the program to only render the entities that are on the camera viewport. It is useful because it can improve both GPU and the CPU performances. 
Furthermore, it is a must for games with huge maps with so many render objects.

## My Research Project

First, I added a struct of a renderObject with a bunch of variables, and a vector of vectors of renderObjects called layers:


- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
