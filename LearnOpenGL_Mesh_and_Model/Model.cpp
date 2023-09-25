#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <string>

Model::Model(char* path, TextureManager* textureManager) : g_textureManager(textureManager)
{
	loadModel(path);
}

Model::~Model()
{
	for (auto& mesh : m_meshes)
		mesh->~Mesh();
}

void Model::Draw(Shader& shader)
{
	for (auto& mesh : m_meshes)
		mesh->Draw(shader);
}

void Model::loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

std::shared_ptr<Mesh> Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> textures;
	
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoord = vec;
		}
		else
		{
			vertex.texCoord = glm::vec2(0.0f);
		}
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		
		std::vector<unsigned int> diffuseMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, Diffuse);
		textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());

		std::vector<unsigned int> specularMap = loadMaterialTextures(material, aiTextureType_SPECULAR, Specular);
		textures.insert(textures.end(), specularMap.begin(), specularMap.end());
	}
	return std::make_shared<Mesh>(vertices, indices, textures);
}

std::vector<unsigned int> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType aiType, TextureType type)
{
	std::vector<unsigned int> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(aiType); i++)
	{
		aiString str;
		mat->GetTexture(aiType, i, &str);
		std::string tex_path = directory + "/" + (std::string)str.C_Str();
		textures.push_back(g_textureManager->AddTexture(tex_path.c_str(), type));
	}
	return textures;
}