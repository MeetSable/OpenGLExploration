#pragma once

#include "Mesh.h"
#include "TextureManager.h"

#include <assimp/scene.h>

class Model {
private:
	std::vector<std::shared_ptr<Mesh>> m_meshes;
	std::string directory;
	TextureManager *g_textureManager;
public:
	Model(char* path, TextureManager *textureManager);
	~Model();
	void Draw(Shader& shader);
private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<unsigned int> loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType type);
};