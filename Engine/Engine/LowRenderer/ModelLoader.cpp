#include "ModelLoader.h"

using namespace engine::low_renderer;

ModelLoader::ModelLoader()
{

}

ModelLoader::~ModelLoader()
{
	for (int i{ 0 }; i < m_models.size(); ++i)
	{
		if (m_models[i] != nullptr)
		{
			delete m_models[i];
			m_models[i] = nullptr;
		}
	}
	m_models.clear();
}

Model* ModelLoader::GetCube()
{
	Model* model = GetModel("Cube");
	if (model != nullptr)
		return model;
	CreateCube();
	return GetModel("Cube");
}


Model* ModelLoader::GetPyramid()
{
	Model* model = GetModel("Pyramid");
	if (model != nullptr)
		return model;
	CreatePyramid();
	return GetModel("Pyramid");
}


void ModelLoader::CreateCube()
{
	std::vector<Vertex> vList
	{
		// front face
		Vertex{ { -0.5f,  0.5f, -0.5f },   {  0.0f,  0.0f,  1.0f },   { 0.0f, 0.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ {  0.5f, -0.5f, -0.5f },   {  0.0f,  0.0f,  1.0f },   { 1.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ { -0.5f, -0.5f, -0.5f },   {  0.0f,  0.0f,  1.0f },   { 0.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ {  0.5f,  0.5f, -0.5f },   {  0.0f,  0.0f,  1.0f },   { 1.0f, 0.0f },   {  0.f,  0.f,  0.f } },

		// left side face
		Vertex{ {  0.5f, -0.5f, -0.5f },   {  1.0f,  0.0f,  0.0f },   { 0.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ {  0.5f,  0.5f,  0.5f },   {  1.0f,  0.0f,  0.0f },   { 1.0f, 0.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ {  0.5f, -0.5f,  0.5f },   {  1.0f,  0.0f,  0.0f },   { 1.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ {  0.5f,  0.5f, -0.5f },   {  1.0f,  0.0f,  0.0f },   { 0.0f, 0.0f },   {  0.f,  0.f,  0.f } },

		// right side face
		Vertex{ { -0.5f,  0.5f,  0.5f },   { -1.0f,  0.0f,  0.0f },   { 0.0f, 0.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ { -0.5f, -0.5f, -0.5f },   { -1.0f,  0.0f,  0.0f },   { 1.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ { -0.5f, -0.5f,  0.5f },   { -1.0f,  0.0f,  0.0f },   { 0.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ { -0.5f,  0.5f, -0.5f },   { -1.0f,  0.0f,  0.0f },   { 1.0f, 0.0f },   {  0.f,  0.f,  0.f } },

		// back face
		Vertex{ {  0.5f,  0.5f,  0.5f },   {  0.0f,  0.0f, -1.0f },   { 0.0f, 0.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ { -0.5f, -0.5f,  0.5f },   {  0.0f,  0.0f, -1.0f },   { 1.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ {  0.5f, -0.5f,  0.5f },   {  0.0f,  0.0f, -1.0f },   { 0.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ { -0.5f,  0.5f,  0.5f },   {  0.0f,  0.0f, -1.0f },   { 1.0f, 0.0f },   {  0.f,  0.f,  0.f } },

		// top face
		Vertex{ { -0.5f,  0.5f, -0.5f },   {  0.0f,  1.0f,  0.0f },   { 0.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ {  0.5f,  0.5f,  0.5f },   {  0.0f,  1.0f,  0.0f },   { 1.0f, 0.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ {  0.5f,  0.5f, -0.5f },   {  0.0f,  1.0f,  0.0f },   { 1.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ { -0.5f,  0.5f,  0.5f },   {  0.0f,  1.0f,  0.0f },   { 0.0f, 0.0f },   {  0.f,  0.f,  0.f } },
		
		// bottom face
		Vertex{ {  0.5f, -0.5f,  0.5f },   {  0.0f, -1.0f,  0.0f },   { 0.0f, 0.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ { -0.5f, -0.5f, -0.5f },   {  0.0f, -1.0f,  0.0f },   { 1.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ {  0.5f, -0.5f, -0.5f },   {  0.0f, -1.0f,  0.0f },   { 0.0f, 1.0f },   {  0.f,  0.f,  0.f } },
		Vertex{ { -0.5f, -0.5f,  0.5f },   {  0.0f, -1.0f,  0.0f },   { 1.0f, 0.0f },   {  0.f,  0.f,  0.f } },
	};

	std::vector<int> iList
	{
		// front face
		0, 1, 2, // first triangle
		0, 3, 1, // second triangle
		// left face
		4, 5, 6, // first triangle
		4, 7, 5, // second triangle
		// right face
		8, 9, 10, // first triangle
		8, 11, 9, // second triangle
		//back face
		12, 13, 14, // first triangle
		12, 15, 13, // second triangle
		// top face
		16, 17, 18, // first triangle
		16, 19, 17, // second triangle
		// bottom face
		20, 21, 22, // first triangle
		20, 23, 21, // second triangle
	};

	m_models.push_back(new Model("Cube", vList, iList));
}

void ModelLoader::CreatePyramid()
{}
/*	std::vector<Vertex> vList
	{
		// bottom face
		{  0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f,	0.0f, 0.0f },
		{ -0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	1.0f, 1.0f },
		{  0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	0.0f, 1.0f },
		{ -0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f,	1.0f, 0.0f },

		// front face
		{  0.5f, -0.5f,  0.5f,	0.0f, 0.5f, 0.5f,	1.0f, 1.0f },
		{  0.0f,  0.5f,  0.0f,	0.0f, 0.5f, 0.5f,	0.5f, 0.0f },
		{ -0.5f, -0.5f,  0.5f,	0.0f, 0.5f, 0.5f,	0.0f, 1.0f },

		// left face
		{ -0.5f, -0.5f,  0.5f,	0.5f, 0.5f, 0.0f,	1.0f, 1.0f },
		{  0.0f,  0.5f,  0.0f,	0.5f, 0.5f, 0.0f,	0.5f, 0.0f },
		{ -0.5f, -0.5f, -0.5f,	0.5f, 0.5f, 0.0f,	0.0f, 1.0f },

		// back face
		{ -0.5f, -0.5f, -0.5f,	0.0f, 0.5f, -0.5f,	1.0f, 1.0f },
		{  0.0f,  0.5f,  0.0f,	0.0f, 0.5f, -0.5f,	0.5f, 0.0f },
		{  0.5f, -0.5f, -0.5f,	0.0f, 0.5f, -0.5f,	0.0f, 1.0f },

		// right face
		{ 0.5f, -0.5f, -0.5f,	-0.5f, 0.5f, 0.0f,	1.0f, 1.0f },
		{  0.0f,  0.5f,  0.0f,	-0.5f, 0.5f, 0.0f,	0.5f, 0.0f },
		{ 0.5f, -0.5f,  0.5f,	-0.5f, 0.5f, 0.0f,	0.0f, 1.0f },

	};


	std::vector<int> iList
	{
		// bottom face
		0, 1, 2, // first triangle
		0, 3, 1, // second triangle

		// front triangle
		4, 5 ,6,
		// left triangle
		7, 8 ,9,
		// back triangle
		10, 11 ,12,
		// right triangle
		13, 14 ,15

	};

	m_models.push_back(new Model("Pyramid", vList, iList));
}
*/

Model* ModelLoader::GetModel(const char* path)
{
	for (int i{ 0 }; i < m_models.size(); ++i)
	{
		if (m_models[i]->GetPath() == path)
			return m_models[i];
	}
	return nullptr;
}
