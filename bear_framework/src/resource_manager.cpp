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
	// TODO@ Delete all resources allocated on the heap on exit
}

void bear::ResourceManager::CreateTexture(std::string a_Name, std::string a_File, graphics::image_format a_Format)
{

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
	return m_ShaderMap[a_Name];
}

graphics::Texture * bear::ResourceManager::GetTexture(std::string a_Name)
{
	return nullptr;
}
