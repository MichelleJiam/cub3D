# cub3D
42/Codam cub3D, a new curriculum project exploring raycasting, inspired by Wolfenstein 3D.
## Description
The goal of the project is to display a dynamic view inside a maze, with the ability to traverse the maze.

The input is a .cub file that contains the following map specifications: resolution, wall textures for all directions, sprite texture(s), floor & ceiling colours/textures, and lastly, the map. 
The map will be denoted as follows: 1 for wall, 0 for floor, space for void, 2 for items, N/S/E/W for spawn position & orientation).

This is a MacOSX compilation. For execution on Linux systems, XMing must be installed and minilibx for Linux included. 

![cub3D](/screenshot.png)

## Commands
```
# Build
make

# Run
./cub3D maps/map.cub
```

## Controls
Move around with ```W``````A``````S``````D```.
Look left and right with ```←``` and ```→```.
Press ```ESC``` or the red X button to exit the game.

## Resources
[minilibx guide](https://harm-smits.github.io/42docs/libs/minilibx/introduction.html)
[Raycasting tutorial](https://lodev.org/cgtutor/raycasting.html)
[Floodfill explanation](https://inventwithpython.com/blog/2011/08/11/recursion-explained-with-the-flood-fill-algorithm-and-zombies-and-cats/)
[MacOSX key and mouse events](https://github.com/VBrazhnik/FdF/wiki/How-to-handle-mouse-buttons-and-key-presses%3F)
