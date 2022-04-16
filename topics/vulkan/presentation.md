# Windows Surface
Since Vulkan is platform agnostic it needs a way to interface with the window system.

# Swap Chain
Vulkan requires own buffers to hold images before we visualize them.

Swap chain is a queue of images that are waiting to be presented to screen.

# Image views
To use any `VkImage`, including those on swap chain, in the render pipeline, we need to create a `VkImageView` object. It's a view into an image.