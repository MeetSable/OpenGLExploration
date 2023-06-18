#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader{
private:
	std::string m_FilePath;
	unsigned int  m_RendererID;
	std::unordered_map<std::string, int> m_LocationCache;
public:
	Shader(const std::string& shaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform4mat(const std::string& name, glm::mat4 mat);
	void SetUniform1f(const std::string& name, float val);
	void SetUniform2f(const std::string& name, glm::vec2 val);

private:
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
	ShaderProgramSource ParseShader(const std::string& filePath);
	int GetUniformLocation(const std::string& name);
};