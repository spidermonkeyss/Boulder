#pragma once

class Shader
{
private:
	unsigned int boulder_programID;
public:
	Shader();
	~Shader();

	void Bind() const;
	void Unbind() const;
};