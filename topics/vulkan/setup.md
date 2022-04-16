# Base Code (Integrating GLFW)
```c++
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
```
This way GLFW will include its own definitions and automatically load the vulkan header.

We want to disable the `GLFW_CLIENT_API` so we can use with vulkan.

```c++
glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
```

# Instance
The instance is a connection between your application and the vulkan library.

```c++
VkInstance instance;
```

Many structs in vulkan have:
- `sType` - type of struct
- `pType` - point to extension information

To create an Instance we need:
| Struct | Description |
| ------ | :---------- |
| VkApplicationInfo | Describes Application |
| VkInstanceCreateInfo | Describes application creation and required extensions to connect to window |

### Extensions
Extensions can be found by
```c++
glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

createInfo.enabledExtensionCount = glfwExtensionCount;
createInfo.ppEnabledExtensionNames = glfwExtensions;
```

```c++
VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
```

## Check fo ext support
```c++
uint32_t extensionCount = 0;

std::vector<VkExtensionProperties> extensions(extensionCount);
vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
```

# Phsyical Device and Queue Families
After getting the `VkInstnace` we need to look for and select a graphics card in the system that supports features we need.

`VkPhysicalDevice physicalDevice`

We can list graphics cards similar to listing extensions.
```c++
uint32_t deviceCount = 0;
vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
```

Hold all device handles.
```c++
std::vector<VkPhysicalDevice> devices(deviceCount);
vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
```
As an example, let's say we consider our application only usable for dedicated graphics cards that support geometry shaders. Then the isDeviceSuitable function would look like this:
```c++
bool isDeviceSuitable(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
           deviceFeatures.geometryShader;
}
```

Instead of just checking if a device is suitable or not and going with the first one, you could also give each device a score and pick the highest one

```c++

void pickPhysicalDevice() {
    ...

    // Use an ordered map to automatically sort candidates by increasing score
    std::multimap<int, VkPhysicalDevice> candidates;

    for (const auto& device : devices) {
        int score = rateDeviceSuitability(device);
        candidates.insert(std::make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0) {
        physicalDevice = candidates.rbegin()->second;
    } else {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

int rateDeviceSuitability(VkPhysicalDevice device) {
    ...

    int score = 0;

    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        score += 1000;
    }

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    // Application can't function without geometry shaders
    if (!deviceFeatures.geometryShader) {
        return 0;
    }

    return score;
}
```

### Queue Familes
Commands are submitted through queues and queue families allows a subset of commands.
```c++
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
  QueueFamilyIndices indices;
  // Logic to find queue family indices to populate struct with
  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
  return indices;
}
```

# Logical Device and Queues
After getting a physical device we need **logical** (virtual) device to interface with it.

# Specifying the queues to be created
Specify the number of queues we want for a single queue famliy
```c++
QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

VkDeviceQueueCreateInfo queueCreateInfo{};
queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
queueCreateInfo.queueCount = 1;
```

u can create all of the command buffers on multiple threads and then submit them all at once on the main thread with a single low-overhead call.

## Specify Device Features
Things like geometry shaders

## Creating Logical Device
```c++
VkDeviceCreateInfo createInfo{};
createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

createInfo.pQueueCreateInfos = &queueCreateInfo;
createInfo.queueCreateInfoCount = 1;

createInfo.pEnabledFeatures = &deviceFeatures;

if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
  throw std::runtime_error("failed to create logical device!");
}
```


## Retrieve Queue Handles
Queues are automatically created along with the logical device.
```c++
VkQueue graphicsQueue

vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
```

Use index 0 since we only have 1 queue for graphics.