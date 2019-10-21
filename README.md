# OOLights - Object-oriented based LED control system
This project is a re-imaging of the FastLED-based "seirlight" demo reel into an object-oriented
system where effect is a class (subclassing some master "effect" superclass), and the main loop
controls rendering, while each instance of a class has methods for rendering itself
