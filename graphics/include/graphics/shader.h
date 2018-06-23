#pragma once

#include<string>

namespace bear { namespace graphics {

	class Shader {
	private:
		unsigned int m_Program;

	public:
		Shader(std::string a_VertexPath, std::string a_FragmentPath);

		void enable() const;
		void disable() const;

	private:
		bool didCompile(unsigned int a_ShaderID, std::string &a_ErrMsg);
	};

} }