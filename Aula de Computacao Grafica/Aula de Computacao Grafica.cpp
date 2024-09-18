#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string.h>
#include <time.h>

#include <chrono>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"


std::vector<Mesh*> listMesh;
std::vector<Shader*> listShader;
Window* window;

//Vertex Shader
static const char* vertexLocation = "VertexShader.glsl";

//Fragment Shader
static const char* fragmentLocation = "FragmentShader.glsl";


void CreateTriagle() {
	//1. Definir os pontos dos vértices
	GLfloat verticesTri[] = {
		-1.0f, -1.0f, 0.0f, //Vértice 1 (x, y)
		0.0f, 1.0f, 0.0f,   //Vértice 2 (x, y)
		1.0f, -1.0f, 0.0f,	//Verice
		0.0f, 0.0f, 1.0f    //Vértice 3 (x, y)
	};

	GLuint indicesTri[] = {
		0, 1, 2,
		0, 1, 3,
		0, 2, 3,
		1, 2, 3
	};

	GLfloat verticesQuad[] = {
		-1.0f, 1.0f, 1.0f,
		-1.0, -1.0f, 1.0f,
		
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		
		-1.0f, 1.0f, -1.0f,
		-1.0, -1.0f, -1.0f,
		
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f
	};

	GLuint indicesQuad[] = {
		0, 1, 5,
		0, 4, 5,
		
		1, 3, 5,
		3, 5, 7,
		
		4, 5, 7,
		4, 6, 7,
		
		0, 2, 6,
		0, 4, 6,
		
		2, 3, 6,
		3, 6, 7,

		0, 1, 2,
		1, 2, 3
	};

	//VAO
	Mesh* triangulo1 = new Mesh();
	triangulo1->CreateMesh(verticesTri, sizeof(verticesTri), indicesTri, sizeof(indicesTri));

	listMesh.push_back(triangulo1);

	Mesh* cubo = new Mesh();
	cubo->CreateMesh(verticesQuad, sizeof(verticesQuad), indicesQuad, sizeof(indicesQuad));

	listMesh.push_back(cubo);
}

void CreateShader() {
	Shader* shader = new Shader();
	shader->CreateFromFile(vertexLocation, fragmentLocation);
	listShader.push_back(shader);
}

int main()
{
	window = new Window(1024, 768);
	window->Initialize();

	//Criar um triangulo
	CreateTriagle();
	CreateShader();

	bool direction = true, sizeDirection = true, angleDirection = true;//true = direita / false = esquerda
	float triOffset = 0.0f, maxOffset = 0.7f, minOffset = -0.7f, incOffset = 0.01f;
	float size = 0.0f, maxSize = 0.7f, minSize = -0.7f, incSize = 0.01f;
	float angle = 0.0f, maxAngle = 360.0f, minAngle = -1.0f, incAngle = 0.5f;

	//Loop until the window close
	//while (window->ShouldClose()) {
	//	//Get + Handle user input events
	//	glfwPollEvents();

	//	//Clear Window (100% = 255)
	//	glClearColor(0.52f, 0.36f, 0.87f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//	//Desenhar o triangulol
	//	//glUseProgram(shaderProgram); //Busca o programa que está com o shader (triangulo)
	//	
	//	Shader* shader = listShader[0];
	//	shader->UseProgram();

	//	listMesh[0]->RenderMesh();

	//	/*auto t_now = std::chrono::high_resolution_clock::now();
	//	float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
	//	glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);*/

	//	//Mover nosso triangulo
	//		
	//	if (triOffset >= maxOffset || triOffset <= minOffset)
	//		direction = !direction;
	//	triOffset += direction ? incOffset : incOffset * -1;

	//	if (size >= maxSize || size <= minSize)
	//		sizeDirection = !sizeDirection;
	//	size += sizeDirection ? incSize : incSize * -1;

	//	if (angle >= maxAngle || angle <= minAngle)
	//		angleDirection = !angleDirection;
	//	angle += angleDirection ? incAngle : incAngle * -1;

	//	//criar matriz
	//	glm::mat4 model(1.0f);
	//	
	//	model = glm::translate(model, glm::vec3(triOffset, triOffset, 0.0f)); //Movimentações do triangulo
	//	model = glm::scale(model, glm::vec3(0.4, 0.4, 0.4)); //Tamanho do triangulo
	//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.0f)); //Rotação

	//	glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));


	//	//cubo
	//	listMesh[1]->RenderMesh();

	//	//glm::mat4 model(1.0f);
	//	model = glm::translate(model, glm::vec3(-triOffset, -triOffset, 0.0f));
	//	model = glm::scale(model, glm::vec3(0.4, 0.4, 0.4));
	//	model = glm::rotate(model, glm::radians(-angle), glm::vec3(1.0f, 1.0f, 0.0f));
	//	
	//	glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));

	//	glm::mat4 projection = glm::perspective(1.0f, window->GetBufferWidth() / window->GetBufferHeight(), 0.1f, 100.0f);

	//	glUniformMatrix4fv(shader->GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(model));

	//	//glUniform3f(uniColor, 1.0f, 0.0f, 0.0f); //atualiza o valor da entrada com a cor vermelha
	//	//glDrawArrays(GL_TRIANGLES, 0, 3); //Desenha um triangulo | 0: Array index | 2: Número de pontos (vértices)

	//	glUseProgram(0); //remove o programa da memória

	//	window->SwapBuffers();
	//}

	//window->~Window();
	//return 0;
	while (!window->ShouldClose()) {
		//Get + Handle user input events
		glfwPollEvents();

		//Clear Window (100% = 255)
		glClearColor(0.6f, 0.4f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		////Desenhar o triangulo
		//glUseProgram(shaderProgram); //Busca o programa que está com o shader (triangulo)

		//listMesh[0]->RenderMesh();

		//GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor"); //procura a entrada chamada triangleColor
		//float r = (float)rand()/RAND_MAX;
		//float g = (float)rand()/RAND_MAX;
		//float b = (float)rand()/RAND_MAX;
		//glUniform3f(uniColor, r, g, b); //atualiza o valor da entrada com a cor vermelha

		Shader* shader = listShader[0];
		shader->UseProgram();


		/*
		* Mover nosso triangulo
		*/
		if (triOffset >= maxOffset || triOffset <= minOffset)
			direction = !direction;
		triOffset += direction ? incOffset : incOffset * -1;

		if (size >= maxSize || size <= minSize)
			sizeDirection = !sizeDirection;
		size += sizeDirection ? incSize : incSize * -1;

		if (angle >= maxAngle || angle <= minAngle)
			angleDirection = !angleDirection;
		angle += angleDirection ? incAngle : incAngle * -1;


		listMesh[0]->RenderMesh();

		glm::mat4 model(1.0f);

		//Movimentações do triangulo
		model = glm::translate(model, glm::vec3(triOffset, triOffset, -2.0f));

		//Tamanho do triangulo
		model = glm::scale(model, glm::vec3(0.4, 0.4, 0.4));

		//Rotação
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.0f));

		/*GLuint uniModel = glGetUniformLocation(shaderProgram, "model");*/
		glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));


		listMesh[1]->RenderMesh();

		glm::mat4 model2(1.0f);

		//Movimentações do triangulo
		model2 = glm::translate(model2, glm::vec3(-triOffset, -triOffset, -2.0f));

		//Tamanho do triangulo
		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0.2));

		//Rotação
		model2 = glm::rotate(model2, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));

		//GLuint uniModel2 = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model2));

		glm::mat4 projection = glm::perspective(1.0f, window->GetBufferWidth() / window->GetBufferHeight(), 0.1f, 100.0f);
		glUniformMatrix4fv(shader->GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(projection));



		//auto t_now = std::chrono::high_resolution_clock::now();
		//float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
		//glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

		////glUniform3f(uniColor, 1.0f, 0.0f, 0.0f); //atualiza o valor da entrada com a cor vermelha
		//glDrawArrays(GL_TRIANGLES, 0, 3); //Desenha um triangulo | 0: Array index | 2: Número de pontos (vértices)

		//glBindVertexArray(0);

		glUseProgram(0); //remove o programa da memória

		window->SwapBuffers();
	}

	//glfwDestroyWindow(window);
	//glfwTerminate();

	window->~Window();
	return 0;
}
