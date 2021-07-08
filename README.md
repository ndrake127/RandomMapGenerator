# RandomMapGenerator

Inspired by all the time I spent making maps in GIMP for D&D campaigns,
this uses simplex noise to create random landmasses.

This only depends on the standard library and FastNoiseLite, which is distributed with the project,
so this should compile without much effort using Visual Studio 2019

To-do:


Markup : * Optimize island assignment (recursive function occasionally causes stack overflow, I had to set stack size to 4mb for an 800x600 window, seems unacceptable)
         * Color islands and water
         * Add beaches around the borders of the islands
         * Add features like towns, rivers, mountains
         * Add configuration file to change threshold value, island count, map size, etc
         * Give water some kind of texture/animation so it isn't just solid blue
