#include "main.h"

//-----------------------------------------------------------------------------
int ccount = 0;
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	

	// Preenche o background. Para cada valor no argumento, desenha uma reta de um ponto a outro.
	// Example_Slide(ccount);
	// ccount++;


	// Desenha um triângulo pré-definido.
	clear(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
	Example_Triangle((PI/(float)25)*ccount, (PI/(float)45)*ccount, (PI/(float)11)*ccount + 2);
	ccount++;


	// Desenha uma espécie de asterisco. Quanto maior o argumento, maior a quantidade de retas.
	//Example_Asterisk(256);
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

