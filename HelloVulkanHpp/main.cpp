#include <iostream>
#include <cassert>
#include <fstream>

#include <vulkan/vulkan.hpp>

int main(int argc, char** argv)
{
	// Initialize instance and application
	vk::ApplicationInfo applicationInfo{ "HelloVulkanHpp", 1, nullptr, 0, VK_API_VERSION_1_1 };
	const std::vector<const char*> layers = { "VK_LAYER_KHRONOS_validation" };
	vk::InstanceCreateInfo instanceCreateInfo(vk::InstanceCreateFlags(), &applicationInfo, layers, {});
	vk::Instance instance = vk::createInstance(instanceCreateInfo);

	// Find physical device.
	vk::PhysicalDevice physicalDevice = instance.enumeratePhysicalDevices().front();
	vk::PhysicalDeviceProperties physicalDeviceProperties = physicalDevice.getProperties();
	std::cout << "Device name: " << physicalDeviceProperties.deviceName << std::endl;
	std::cout << "Vulkan version: " << VK_VERSION_MAJOR(physicalDeviceProperties.apiVersion) << "."
		<< VK_VERSION_MINOR(physicalDeviceProperties.apiVersion) << "."
		<< VK_VERSION_PATCH(physicalDeviceProperties.apiVersion) << std::endl;
	std::cout << "Max compute shared memory size: " << physicalDeviceProperties.limits.maxComputeSharedMemorySize << std::endl;

	// Find compute queue family index.
	std::vector<vk::QueueFamilyProperties> queueFamilyProperties = physicalDevice.getQueueFamilyProperties();
	auto computeQueueFamilyIterator = std::find(queueFamilyProperties.begin(), queueFamilyProperties.end(),
		[](const vk::QueueFamilyProperties& Prop) { return Prop.queueFlags & vk::QueueFlagBits::eCompute; });
	const uint32_t computeQueueFamilyIndex = std::distance(queueFamilyProperties.begin(), computeQueueFamilyIterator);
	std::cout << "Compute Queue Family Index: " << computeQueueFamilyIndex << std::endl;

	// Create logical device.
	vk::DeviceQueueCreateInfo deviceQueueCreateInfo(vk::DeviceQueueCreateFlags(), computeQueueFamilyIndex, 1);
	vk::DeviceCreateInfo deviceCreateInfo(vk::DeviceCreateFlags(), deviceQueueCreateInfo);
	vk::Device device = physicalDevice.createDevice(deviceCreateInfo);

	return 0;
}