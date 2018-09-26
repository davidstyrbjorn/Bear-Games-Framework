#include"../include/memory/resource_manager.h"

#include"../include/graphics/graphics.h" // Shader & Texture

using namespace bear;
using namespace bear::graphics;

ResourceManager* ResourceManager::s_Instance = nullptr;

ResourceManager* ResourceManager::Instance()
{
	if (s_Instance == nullptr)
		s_Instance = new ResourceManager();
	return s_Instance;
}

void bear::ResourceManager::Init()
{
	// Pass
}

void bear::ResourceManager::Exit()
{
	for (auto it = m_ShaderMap.begin(); it != m_ShaderMap.end(); ++it) {
		delete it->second;
		m_ShaderMap.erase(it);
	}
	m_ShaderMap.clear();

	for (auto it = m_TextureMap.begin(); it != m_TextureMap.end(); ++it) {
		delete it->second;
		m_TextureMap.erase(it);
	}
	m_TextureMap.clear();
}

void bear::ResourceManager::CreateTexture(std::string a_Name, std::string a_File, graphics::image_format a_Format)
{
	Image image(a_File, a_Format);
	Texture* texture = new graphics::Texture(image);
	m_TextureMap.insert(std::pair<std::string, Texture*>(a_Name, texture));
}

graphics::Shader* bear::ResourceManager::CreateShaderFromFile(std::string a_Name, std::string a_File1, std::string a_File2, std::string a_File3)
{
	// Create & compile & insert a new shader into the map
	graphics::Shader* shader = new Shader();
	shader->setSourceFromFile(a_File1, a_File2);
	if (a_File3 != "") {
		shader->setGeometrySourcePath(a_File3);
	}
	shader->compile();
	m_ShaderMap.insert(std::pair<std::string, Shader*>(a_Name, shader));
	return shader;
}

graphics::Shader* bear::ResourceManager::CreateShaderFromSource(std::string a_Name, std::string a_Source1, std::string a_Source2, std::string a_Source3)
{
	// Create & compile & insert a new shader into the map
	graphics::Shader* shader = new Shader();
	shader->setSource(a_Source1, a_Source2);
	if (a_Source3 != "") {
		shader->setGeometrySource(a_Source3);
	}
	shader->compile();
	m_ShaderMap.insert(std::pair<std::string, Shader*>(a_Name, shader));
	return shader;
}

graphics::Shader * bear::ResourceManager::GetShader(std::string a_Name)
{
	auto shdr = m_ShaderMap[a_Name];
	if (shdr == nullptr) {
		std::cout << "RESOURCE_MANAGER, returning a null Shader object" << std::endl;
	}
	return shdr;
}

graphics::Texture * bear::ResourceManager::GetTexture(std::string a_Name)
{
	auto txtr = m_TextureMap[a_Name];
	if (txtr == nullptr) {
		std::cout << "RESOURCE_MANAGER, returning a null Texture object!" << std::endl;
	}
	return txtr;
}
