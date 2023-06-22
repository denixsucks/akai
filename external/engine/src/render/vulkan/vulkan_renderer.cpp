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
}

void VulkanRenderer::Shutdown() {

}

void VulkanRenderer::RenderFrame() {

}


// priv
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
    {SurfaceArgs::ALLOCATORS, nullptr},
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