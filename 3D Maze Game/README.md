# 3D Maze Game

This game was created by Colin Hommerding, Fan Ding, and Matthew Fischbach

Contained within this folder is a fully functional 3D Game. 
The goal of this game is for the player to find a sword that is located within the map.
There will be multiple doors and stones blocking the players way to the goal. The player must find matching color keys in order to open the doors. The player must make use of other powerups such as a potion that makes the player larger and a hammer in order to break the stones. 

Key Features:
The player can pick up and drop items.
The player can look around with the mouse.
The player can jump with the space bar.
Doors use a falling animation once they are unlocked and then turn into floor spaces.
The game world has multiple scene objects within it.
Item animations when they are used. For example, keys will rotate and the hammer will smash vertically based on time passing.
The player can break weaker stone walls with the brand new hammer power-up.
The player can become the “Hulk” when using the transforming potion power-up. The hulk has increased strength allowing him to use heavier powerups that a normal human cannot.
The game includes multiple point lights as programmed in the shader that follows the complete Phong model. All objects can be specified with different material properties, which change the lighting as specified in the Phong model.
The game includes dynamic point lighting that can move up and down.
Our game supports multi-sampling.
The walls and floors feature quality textures that fit the theme of the game.
Our game has a night sky view with a realistically textured moon and blinking stars.
Upon completion of the game there is a "you win" screen that will appear.
Our game incorporates music that changes with the human/hulk mode. The normal music is a groovy beat, but once the player drinks the hulk potion to become hulk it switches to more intense music to match with what is happening. 
The program loads in better looking models for items such as the potion and hammer from a .obj file format that is specified as triangle primitives

GameScreenshots:
Game Screenshots are included within the Game Screenshots folder.

Compilation: 
This game is compiled on MacOS. OpenGL, SDL2, and SDL2_mixer are frameworks that are required to be installed.

The game is compiled with: g++ -std=c++11 video_game_code.cpp glad/glad.c -F/Library/Frameworks -framework SDL2 -framework SDL2_mixer -framework OpenGL -o FinalProject




