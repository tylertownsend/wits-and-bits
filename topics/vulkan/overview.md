# Overview
# Origin
Vulkan is designed as a cross-platform abstraction over GPU's. However, previous graphices apis were limited to configurable fixed functionality due to the graphics hardware.

Graphics card architectures started offering more programmable functionality which resulted in less than ideal abstractions from drivers and constant driver updates.


Vulkan reduces driver overhead allowing programmers to specify their intentn with a more verbose api.

Vulkan also reduces inconsistencies in shader compilation by switching to standardized byte code formate.

# Drawing a Triangle

## Step 1 Instance and Phsyical Device Selection
### Instance
A vulkan application is created through the `VkInstance` api. This describes:
1. The application
2. Any api extensions used.

### Physical Device
The instance then can query one ore more `VkPhysicalDevice`s to use.

## Step 2 Logical device and queue families
### Logical Device
After the hardware is created, you can create a `VkDevice` (logical) which describes the 
`VkPhysicalDeviceFeatures` to use like:
- Multi viewport rendering
- 64 bit floats

### Queue Family
You also specify the queue families to use. Most operations used queues to sub operation to be executed asynchronously. Ex (Draw, Memory ops).

Queues are allocated from queue families where each family supports specific set of operations of queues. There are:
- Graphics Queues
- Compute Queues
- Memory Transfer Queues.

This is also dependent on physical device selection.

## Step 3 Window selection and swap chain
We need two components to render a window using the GLFW library.

1. `VkSurfaceKHR` - cross platform abstraction over windows to render to and is generally
instantiated by providing reference to native window handle.
2. `VkSwapchainKHR` - collection of render targets. Its basic purpose is to make sure image it renders is different from one on screen. We want to draw a fame, the swap chain provides us image to render to. When we finish drawing a frame, the image is returned to the swap chain.

The number of render targets and conditions for presenting finished images to the screen depends on present mode:
- double buffering
- triple buffering


## Step 4 Imageviews and Framebuffers
To draw an image acquired from the swap chain we wrap it into a `VkImageView` an `VkFramebuffer`

`VkImageView` references the specific part of image to use.

`VkFramebuffer` references images views that are used for colo, depth, and stencil targets.
 
## Step 5 Render pass

Render passes in Vulkan describe:
1. the type of images that are used during rendering operation.
2. how the images are used
3. How there content should be trated.

In the intial triangle rendering app, we tell Vulkan to use a single image as a color target and cleared to solid color right before drawing op.

## Step 6 Graphics Pipeline
`VkPipeline` is the graphics pipeline and is a configurable state of graphics card:
 1. Viewport size
 2. Buffer operations

`VkShaderModule` is the programable state. These objects are created from shader byte code. The driver also needs to know which render targets will be used in the pipeline.

### Configuration
All configuration is set in advance which is different from other apis.

Switching to a different shader or chaing vertex layout requires recreating graphics pipeline.

Only some basic config like viewport size and clear color can be changed dynamically.

Because of ahead-of-time compilation, runtime performance and optimization is predicatble because of different graphics pipelines are explicit.

## Step 7 Command Pools and Command Buffers
`VkCommandBuffer` - operation that are executed (drawing operations) are submitted to this queue.

`VkCommandPool` - allocates the command buffers and is associated with a specific queue family 

Drawing a triable requires:
 - Being reder pass
 - bind graphics pipeline
 - draw three verticies
 - end render pass.

Because the image in the framebuffer depends on the specific image the swap chain gives us, we need to record command buffer for each possible image and select the right one at draw time.

## Step 8 Main loop
1. We acquire an image from swap chain with `vkAcquireNextImageKHR`.
2. Select approriate command buffer for that image
3. For given image execute it with `vkQueueSubmit`
4. Return image to the swap chain for presentation to the screen with `VkQueuePresentKHR`.

Executions are async so we use synchronization objects to handle.