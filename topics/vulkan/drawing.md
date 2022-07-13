# Framebuffers
Attachments sepcified during a render pass creation are bound by wrapping them into a `VkFramebuffer` object.

A framebuffer object references all of the `VkImageView` objects that represent attachments.

Because the image the swap chain returns dictates the image we have to use for attachments, we have to create a framebuffer for all of the images in the swap chain and use the one that corresponds to the retrieved image.

```c++
for (size_t i = 0; i < swapChainImageViews.size(); i++) {
    VkImageView attachments[] = {
        swapChainImageViews[i]
    };

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
    framebufferInfo.width = swapChainExtent.width;
    framebufferInfo.height = swapChainExtent.height;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
        throw std::runtime_error("failed to create framebuffer!");
    }
}
```

We only have the color attachment.

# Command Buffers
Commands are executed by recording all the operations you want to perform in a command buffer object.

## Command Pools
Command pools manage memory that is used to store the buffers and command buffers are allocated from them.

`VkCommandPool commandPool`

```c++
QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

VkCommandPoolCreateInfo poolInfo{};
poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
```

## Command Buffer Allocation
`VkCommandBuffer commandBuffer`

Command buffers can have secondary functionality and may reuse common operations from primary command buffers.

## Command Buffer recording
Now we want to work on a function that writes the commands we want to execute to a command buffer
```c++
void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = 0; // Optional
  beginInfo.pInheritanceInfo = nullptr; // Optional

  if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("failed to begin recording command buffer!");
  }
}
```

## Starting a render pass
Drawing starts by beginning th reder pass with `vkCmdBeginRenderPass`
```c++
void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = 0; // Optional
  beginInfo.pInheritanceInfo = nullptr; // Optional

  if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  // The renderpass itself and the images to bind to from the framebuffer
  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = renderPass;
  renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];

  // size of render area
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = swapChainExtent;

  VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
  renderPassInfo.clearValueCount = 1;
  renderPassInfo.pClearValues = &clearColor;

  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

```

## Basic Drawing Commands
Bind the graphics pipeline

```c++
void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = 0; // Optional
  beginInfo.pInheritanceInfo = nullptr; // Optional

  if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  // The renderpass itself and the images to bind to from the framebuffer
  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = renderPass;
  renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];

  // size of render area
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = swapChainExtent;

  VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
  renderPassInfo.clearValueCount = 1;
  renderPassInfo.pClearValues = &clearColor;

  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

  // specify if the pipeline is graphics or compute
  vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

  // draw command
  vkCmdDraw(commandBuffer, 3, 1, 0, 0);

  // end render pass
  vkCmdEndRenderPass(commandBuffer);
}

```

# Rendering and Presentation
```c++
void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        drawFrame();
    }
}
```

## Outline of a frame
Rendering a frame consists of:
1. Wait for the previous frame to finish
2. Acquire an image from swap chain
3. Record a command buffer which draws the scene onto that image.
4. Submit the recorded command buffer
5. Present the swap chain image.

## Synchronization
Synchronization of GPU is explicit in Vulkan.

## Semaphores
A semaphore is used to add order between queue operations.

There are two kinds of semaphores in Vulkan:
1. Binary
2. Timeline

A semaphore is either unsignaled or signaled.

The way we use a semaphore to order queue ops is by providing the same semapphore as a "signa" semaphore in one queue op and as a wait semaphore in another queue op.

Suppose we have _*S*_, and queue ops _*A*_ and _*B*_ and execute in the respective order. Then _*A*_ will signal semaphore _*S*_ when it finishes execution and op _*B*_ will wait on _*S*_ before executing.

```c++
VkCommandBuffer A, B = ... // record command buffers
VkSemaphore S = ... // create a semaphore

// enqueue A, signal S when done - starts executing immediately
vkQueueSubmit(work: A, signal: S, wait: None)

// enqueue B, wait on S to start
vkQueueSubmit(work: B, signal: None, wait: S)
```

However `vKQueueSubmit()` returns immediately. Waiting only happens in GPU.

So we need to synchronize the CPU as well.

## Fences
CPU (Host) needs to know when GPU finishes.

Fences are signaled/unsignaled state that can be attached to work. When
the work completes, the fence is signaled.

```c++
VkCommandBuffer A = ... // record command buffer with the transfer
VkFence F = ... // create the fence  

// enqueue A, start work immediately, signal F when done
vkQueueSubmit(work: A, fence: F)

vkWaitForFence(F) // blocks execution until A has finished executing

save_screenshot_to_disk() // can't run until the transfer has finished
```

This will block the host execution. Fences must be reset manually to put them back into the unsignaled state.

## Waiting on PRevious frame.
At the start of a frame, we want to wait until the previous frame has finished.

```c++
void drawFrame() {
    vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
}
```

Create the fence in the signaled state for the start of the program so
we can bootstrap the drawing process.
```c++
VkFenceCreateInfo fenceInfo{};
fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
```

## Acquire an Image from Swap Chain
```c++
uint32_t imageIndex;
vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
```

This sets the image index from the swap chain.

## Record Command Buffer
```c++
vkResetCommandBuffer(commandBuffer, 0);
```
Reset to see if we can do anything. 0 is a flag to say don't do anything sepcial.

Then record the buffer from the index.
```c++
recordCommandBuffer(commandBuffer, imageIndex);
```

## Submit Command Buffer
```c++
VkSubmitInfo submitInfo{};
submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
// we want to wait until image is available before writing colors
VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
submitInfo.waitSemaphoreCount = 1;
submitInfo.pWaitSemaphores = waitSemaphores;
submitInfo.pWaitDstStageMask = waitStages;
```

```c++
if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
    throw std::runtime_error("failed to submit draw command buffer!");
}
```

## Subpass Dependencies
Subpasses in a render pass automatically take care of image layout transitions which are controlled by subpass dependencies.

Operations before and right after a subpass count as implicit subpasses.

src and dstSubpass control dependencies.

The dstSubpass must always be higher than srcSubpass to prevent cycles in the dependency graph (unless one of the subpasses is VK_SUBPASS_EXTERNAL).

```c++
VkSubpassDependency dependency{};
// implicit subpass before or after the render pass.
dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
dependency.dstSubpass = 0;

// op to wait on 
dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
// stages in which these occur
dependency.srcAccessMask = 0;

// wait on the end of the stage
dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
// 
dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;


```
## Presentation

The last step of the drawing the frame is submitting result back to swap chain to have it eventually show up on the screen.

```c++
VkPresentInfoKHR presentInfo{};
presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

presentInfo.waitSemaphoreCount = 1;
presentInfo.pWaitSemaphores = signalSemaphores;
```

 Swap chains to present.
```c++
VkSwapchainKHR swapChains[] = {swapChain};
presentInfo.swapchainCount = 1;
presentInfo.pSwapchains = swapChains;
presentInfo.pImageIndices = &imageIndex
```

Submits request to present swapchain
```c++
vkQueuePresentKHR(presentQueue, &presentInfo);
```

# Frames in Flight