Kandidatnummer: 10026
# Pinball Game 

![GameLogo](doc/logo.png "GameLogo")

### What is it?
This is a pinball game implemented in C++ using the threepp library for 3D visualization and Bullet3 for physics simulation. 
The game aims to recreate the classic feel of an arcade game of pinball, where players use flippers to keep a ball in play.

#### Features:
* 3D graphics using threepp library.
* Realistic physics simulation using Bullet3.

#### Todo:
* Points system
* Different layouts (With an easy-to-use map loader)

### How to compile and run:

To run the game, you need to have the following dependencies installed on your system:
* C++ compiler with C++17 support
* [vcpkg](https://vcpkg.io/en/index.html)

Call CMake with `-DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake`

Then just run the `pinBallGame` in Release mode!

### How to play:

When you start the executable you will be presented with the pinball game board.

Controls:
* W : Move the plunger upwards
* S : Pull the plunger down
* Space : Releases the plunger
* A : Activate Left Flipper
* D : Activate Right FLipper

To play you first pull back the plunger and release it. Then the ball will be in play, have fun! Keep the ball from falling down!

Any object that is red will increase the ball speed when hit!

#### Disclaimer:
There is a chance the ball gains so much speed that it will pass through the board border during a "tick". That means that between the updating of the physics world the ball will move in a "tick" longer than the border width.
If this happens reset the ball position using "R".

#### No tests for bullet...

Testing the actual bullet implementation has not worked. I might be thinking about how to do this wrong but, testing physics would require tests that run for longer, which results in test timeouts.
Also, from the bulletphysics header a lot of features of bullet is private. So getting information form the bullet world isn't easily possible. For example, getting the amount of children in the world.
I might have overseen how to do this, it might exist. Need to investigate further.

#### Any class is not split into hpp declaration and cpp definition?

For some reason whenever I try to split any class into a hpp declaration and cpp definition I get linker errors. (LNK 2005)

And for the life of me I cannot figure out how to fix this.
So for the meantime a bit longer compiling times and everything is in header files.
I suspect it has something to do with how I am implementing bullet and using it in different functions in classes.

#### Credits:

* threepp: https://github.com/markaren/threepp
* bullet3: https://github.com/bulletphysics/bullet3
* Pinball textures from: https://ambientcg.com/view?id=Metal007