#include "vulkan_init.h"

VkCommandPoolCreateInfo VulkanInitializers::CommandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flag)
{
  VkCommandPoolCreateInfo commandPoolCreateInfo{VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
  commandPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;
  commandPoolCreateInfo.flags = flag;
  return commandPoolCreateInfo;
}

VkCommandBufferAllocateInfo VulkanInitializers::CommandBufferAllocateInfo(VkCommandPool pool, uint32_t count, VkCommandBufferLevel level)
{
  VkCommandBufferAllocateInfo commandBufferAllocateInfo{VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
  commandBufferAllocateInfo.commandPool = pool;
  commandBufferAllocateInfo.commandBufferCount = count;
  commandBufferAllocateInfo.level = level;
  return commandBufferAllocateInfo;
}
