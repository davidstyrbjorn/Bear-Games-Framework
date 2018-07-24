#pragma once

#include<string>
#include<map>

namespace bear {
	namespace core {
		class Matrix4x4;
	}
}

namespace bear { namespace graphics {

	class Shader {
	private:
		unsigned int m_Program;
		// Cache maping for the uniform locations
		std::map<const char*, int> m_UniformMap;
		bool m_IsActive;
		const char* m_VertexSource;
		const char* m_FragmentSource;

	public:
		static Shader DefaultUnlitShader;
		static Shader DefaultTexturedShader;

	public:
		Shader();
		Shader(std::string a_VertexPath, std::string a_FragmentPath, bool a_IsSource);
		~Shader();

		void compile(std::string a_VertexPath, std::string a_FragmentPath, bool a_IsSource);
		void enable();
		void disable();
		const bool isActive() const;

		//void setUniformVector2f(const char* a_UniformName, const core::Vector2 a_Vector);
		void setUniformMatrix4x4(const char* a_UniformName, core::Matrix4x4& a_Matrix);
		void setUniformInteger(const char* a_UniformName, int a_Integer);

	private:
		bool didCompile(unsigned int a_ShaderID, std::string &a_ErrMsg);
		int getUniformLocation(const char* a_UniformName);
	};

} }