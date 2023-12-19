#pragma once
#include <akai_engine/render/renderer.h>
#include <vulkan/vulkan.h>
#include <vector>

class VulkanRenderer : public Renderer
{
public:
  void Init(RendererSettings settings) override;
  void Shutdown() override;
  void RenderFrame() override;

private:
  void initVulkanCore();
  void createSwapchain();
  void createCommands();
  void createDefaultRenderPass();
  void createFramebuffers();
  void createSyncStructures();

  RendererSettings _rendererSettings{};
  uint64_t _frameNumber {0};

  // Core Vulkan
  VkInstance _instance;
  VkDebugUtilsMessengerEXT _debugMessenger;
  VkPhysicalDevice _physicalDevice; // physical device
  VkDevice _device;                 // logical device
  VkSurfaceKHR _surface;

  // Swap Chain
  VkSwapchainKHR _swapchain;
  VkFormat _swapchainImageFormat;
  std::vector<VkImage> _swapchainImages;
  std::vector<VkImageView> _swapchainImageViews;
  VkExtent2D _windowExtent;

  // COMMAND POOLS AND QUEUES
  VkQueue _graphicsQueue;
  uint32_t _graphicsQueueFamily;

  VkCommandPool _commandPool;
  VkCommandBuffer _mainCommandBuffer;

  // RENDER PASSES
  VkRenderPass _renderPass;
  std::vector<VkFramebuffer> _framebuffers{3};

  // SYNCHRONIZATION OBJECTS
  VkSemaphore _presentSemaphore, _renderSemaphore;
  VkFence _renderFence;
};