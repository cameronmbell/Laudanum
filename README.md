# Laudanum

An arena FPS drawing HEAVY inspiration from Devil Daggers

```
Yes, but keep in mind the default frame buffer will always be the same size of the window. What you can do is to render your scenes internally into an off-screen (400x300) frame buffer, and then up-scale it to (800x600), you can do this by rendering this into a texture and applying it on a full screen quad, the advantage you will get is your shaders will run less often than with higher resolution. But you will lose quality due to scaling up which will need interpolating the original data in order to fill the bigger image.
```