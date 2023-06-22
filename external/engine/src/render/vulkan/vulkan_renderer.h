#pragma  once
#include <akai_engine/render/renderer.h>
#include <vulkan/vulkan.h>

class VulkanRenderer : public Renderer {
public:
  void Init(RendererSettings settings) override;
  void Shutdown() override;
  void RenderFrame() override;

private:
  void initVulkanCore(); 

  RendererSettings _rendererSettings {};

  // Core Vulkan
  VkInstance _instance;
  VkDebugUtilsMessengerEXT _debugMessenger;
  VkPhysicalDevice _physicalDevice; // physical device
  VkDevice _device;                 // logical device
  VkSurfaceKHR _surface;
};