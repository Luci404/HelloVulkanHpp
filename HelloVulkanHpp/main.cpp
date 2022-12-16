#include <vulkan/vulkan.hpp>

int main(int argc, char** argv)
{
	vk::ApplicationInfo applicationInfo{ "HelloVulkanHpp", 1, nullptr, 0, VK_API_VERSION_1_1 };

	const std::vector<const char*> layers = { "VK_LAYER_KHRONOS_validation" };
	vk::InstanceCreateInfo instanceCreateInfo(vk::InstanceCreateFlags(), &applicationInfo, layers, {});
	vk::Instance instance = vk::createInstance(instanceCreateInfo);

	return 0;
}