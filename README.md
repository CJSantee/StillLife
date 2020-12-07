# Homework #5: A scene of your own

## Details

### Assignment
CS3233-01 Homework #5
  
Still Life Scene - My Desk 
  
[Colin Santee](https://github.com/CJSantee)
  
Due: December 7th, 2020

### Description
Program draws a lighted 3-dimensional scene of my general desk setup. 
Objects include: a table, laptop, monitor, textbook, coffee cup, and the Utah Teapod!
  
### Build
Compile with: `g++ Scene.cpp camera.cpp -framework GLUT -framework OpenGL -Wno-deprecated`
  
Run with: `./a.out`
  
## Objects

### Table
The table, like all other objects in the scene, was designed with variability in mind, the `generateTable()` function can be updated to change the table height, width, depth of the table top, and width of the legs.
### Laptop
The laptop in the scene is modeled after a MacBook Pro with a 16:9 aspect-ratio screen. 
### Monitor 
The secondary monitor in the scene is designed using several cubic shapes, drawn using the custom method, `triangleQuad()` which utalizes `GL_TRIANGLE_FAN` to create a quad.
### Textbook
The textbook, designed with the standard American A1 paper aspect ratio in mind, is drawn with a cover, binding, and a variable number of pages (by default, 5).
### Cup / Mug
The cup in the scene is designed as an open-ended cylinder with an entirely hollow half-cylinder for the handle. 

## A suprise!
Inlcuded in my Design is the Glut implementation of the Utah Teapot, positioned behind my laptop, ready to refill the mug. 

### Utah Teapod 
The Utah teapot, or the Newell teapot, is a 3D test model that has become a standard reference object and an in-joke within the computer graphics community. It is a mathematical model of an ordinary, Melitta-brand teapot that appears solid, cylindrical, and partially convex. Using a teapot model is considered the 3D equivalent of a "Hello, World!" program, a way to create an easy 3D scene with a somewhat complex model acting as the basic geometry for a scene with a light setup. Some programming libraries, such as the OpenGL Utility Toolkit, even have functions dedicated to drawing teapots.

The teapot model was created in 1975 by early computer graphics researcher Martin Newell, a member of the pioneering graphics program at the University of Utah. It was one of the first to be modeled (using bézier curves) rather than precisely measured. -[Wikipedia](https://en.wikipedia.org/wiki/Utah_teapot)

## Improvements
While I'm proud of the scene I created, there are several improvements I would have implemented, given more time. 
### Laptop
- Rotate the screen along the axis of the hinge.
- Add a different-colored screen, emitting it's own light
- Added a rectangular mouse pad
### Monitor
- Add a different-colored screen, emitting it's own light
- Position the screen further extended from the stand with an additional mount
### Textbook
- Round the binding
- Add a texture map to place an image on the cover
### Cup
- Increase the width of the sides of the cup
### Other Objects
Other objects I would like to include in the scene:
- Computer Mouse
- Lamp
- iPhone
- Pen / Pencil