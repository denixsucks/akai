#include <akai_engine/service_locator.h>
#include "vulkan_renderer.h"
#include "vulkan_init.h"
#include "vulkan_types.h"
#include "vulkan_utilities.h"
#include <VkBootstrap.h>

// public
void VulkanRenderer::Init(RendererSettings settings) {
  _rendererSettings = settings;


  initVulkanCore();
  createSwapchain();
}

void VulkanRenderer::Shutdown() {
  vkDestroySwapchainKHR(_device, _swapchain, nullptr); // destroy swapchain

  for (auto imageView : _swapchainImageViews) {
    vkDestroyImageView(_device, imageView, nullptr); // destroy all image views
  }

  // destroy vulkan core
  vkDestroyDevice(_device, nullptr);
  vkDestroySurfaceKHR(_instance, _surface, nullptr);
  vkb::destroy_debug_utils_messenger(_instance, _debugMessenger);
  vkDestroyInstance(_instance, nullptr);
}

void VulkanRenderer::RenderFrame() {

}


// private
void VulkanRenderer::initVulkanCore() {
  vkb::InstanceBuilder builder;
  auto builderInstance = builder.set_app_name(_rendererSettings.ApplicationName.c_str())
    .request_validation_layers(true)
    .require_api_version(1,2,0)
    .use_default_debug_messenger()
    .build();

  vkb::Instance vkbInstance = builderInstance.value();
  _instance = vkbInstance.instance;
  _debugMessenger = vkbInstance.debug_messenger;

  // request vulkan surface
  std::unordered_map<SurfaceArgs, std::any> surfaceArgs {
    {SurfaceArgs::INSTANCE, _instance},
    // {SurfaceArgs::ALLOCATORS, nullptr}, // calls bad cast (idk why lmao), maybe we shouldn't use nullptr in surface args. -d
    {SurfaceArgs::OUT_SURFACE, &_surface}
  };
  ServiceLocator::GetWindow()->RequestDrawSurface(surfaceArgs);

  vkb::PhysicalDeviceSelector selector { vkbInstance };
  vkb::PhysicalDevice vkbPhysicalDevice = {
    selector
      .set_minimum_version(1, 1)
      .set_surface(_surface)
      .select()
      .value()
  };

  vkb::DeviceBuilder deviceBuilder { vkbPhysicalDevice };
  vkb::Device vkbDevice { deviceBuilder.build().value() };

  _device = vkbDevice.device;
  _physicalDevice = vkbPhysicalDevice.physical_device;

}

void VulkanRenderer::createSwapchain() {
  vkb::SwapchainBuilder swapchainBuilder {
    _physicalDevice, _device, _surface
  };

  auto [width, height] = ServiceLocator::GetWindow()->GetWindowExtents();
  vkb::Swapchain vkbSwapchain = swapchainBuilder
    .use_default_format_selection()
    .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR) // Hard Vsync
    .set_desired_extent(width, height)
    .build()
    .value();
  

  _swapchain = vkbSwapchain.swapchain;
  _swapchainImages = vkbSwapchain.get_images().value();
  _swapchainImageViews = vkbSwapchain.get_image_views().value();
  _swapchainImageFormat = vkbSwapchain.image_format;



}