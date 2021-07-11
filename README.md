# RandomMapGenerator

Inspired by all the time I spent making maps in GIMP for D&D campaigns,
this uses simplex noise to create random landmasses.

This only depends on SFML and FastNoiseLite, both of which are included with the project.
SFML libs built for Visual Studio 2019 on Windows ae included, they are the only non-portable
part of this project.

To-do:
* Optimize island assignment (recursive function occasionally causes stack overflow, I had to set stack size to 4mb for an 800x600 window, seems unacceptable)
	* Use explicit stack
* Add beaches around the borders of the islands  
* Add features like towns, rivers, mountains  
* Add configuration file to change threshold value, island count, map size, etc  
* Give water some kind of texture/animation so it isn't just solid blue  
