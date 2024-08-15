#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	//GLEW = GERENCIADOR DE PACOTES DO OPENGL
	//GLFW = GERENCIADOR DE JANELAS

	if (!glfwInit()) {
		printf("Não funcionou o GLFW");
		return 1;
	}

	//definindo as versoes min e max do glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//defini para so usar o basico do opengl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//compatibilidade entre funcoes antigas
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "computacao-grafica", NULL, NULL);

	if (!window) {
		printf("Janela não foi aberta");
		glfwTerminate();
		return 1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	//define que eh esta janela que estamos trabalhando
	glfwMakeContextCurrent(window);

	//usa as funcoes dos drives da sua placa de video
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("Nao foi iniciado o GLEW");
		glfwTerminate();
		glfwDestroyWindow(window);
		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight);

	while (!glfwWindowShouldClose(window)) {
		//cria um evento
		glfwPollEvents();

		//define a cor do fundo 
		glClearColor(1.0f, 0.0f, 0.7f, 0.7f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}
}
