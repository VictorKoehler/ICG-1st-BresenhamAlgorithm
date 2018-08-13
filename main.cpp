#include "main.h"

//-----------------------------------------------------------------------------
int ccount = 0;
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	

	// EXPERIMENTAL: Desenha e preenche um triângulo na tela.
	// Example_FilledTriangle(ccount);


	

	// Preenche o background. Para cada valor no argumento, desenha uma reta de um ponto a outro.
	Example_Slide(ccount);

	// Desenha um triângulo pré-definido.
	Example_Triangle();

	// Desenha uma espécie de asterisco. Quanto maior o argumento, maior a quantidade de retas.
	Example_Asterisk(256);
	


	ccount++;
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

