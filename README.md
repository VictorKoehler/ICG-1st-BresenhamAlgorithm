# ICG-1st-BresenhamAlgorithm
---

## Introdução
Este projeto aborda e implementa técnicas de rasterização de pontos, retas (usando o algoritmo de Bresenham) e triângulos, mais precisamente, usando um framework específico de fins didáticos disponibilizado por Christian Pagot, professor da Universidade Federal da Paraíba, da qual este trabalho se destina como complemento de nota da disciplina de Introdução à Computação Gráfica, período 2018.1.

Discente: Victor José de Sousa Koehler

Matrícula: 20170068974

<br><br><br>

---


## O Projeto

O framework consiste de uma simples janela (usando as ferramentas GLUT/OpenGL), duas constantes, `IMAGE_WIDTH` e `IMAGE_HEIGHT`, respectivamente, a largura e altura da janela e, por fim, um ponteiro para simulação de uma região de memória de vídeo. Esta memória está disposta de forma linear, 1 byte por cor, 4 cores por pixel (RGBA), de coordenadas (0, 0) a (IMAGE_WIDTH - 1, IMAGE_HEIGHT - 1). Especificamente, o objetivo do trabalho é proporcionar ao aluno/programador a experiência de manipular diretamente o *output* do vídeo e aplicar suas habilidades de rasterização.

<br>

---

## As estruturas
O Projeto possui uma hierarquia de estruturas "primitivas" usados nas chamadas das funções:

**struct Color**: Representa uma cor no sistema, composto pelas componentes RGBA, cada uma em sua variável (unsigned char), variando de 0 a 255 de acordo com o padrão. Cada "instância" ocupa um total de 4 bytes na memória RAM da maioria dos sistemas.

**struct Point**: Representa um ponto no sistema de coordenadas, composto pelos inteiros `x` e `y`.

**struct ColoredPoint**: Representa uma tupla Ponto-Cor; sendo definido, portanto, como uma associação de um ponto `p` com uma cor `c`.

**struct Line**: Representa uma tupla de ColoredPoint; sendo definido, portanto, como uma reta entre dois pontos de cores diferentes.

**struct Triangle**: Representa uma tripla de ColoredPoint; sendo definido, portanto, como um triângulo entre três pontos de cores diferentes.

<br>


---

## As funções/métodos
**PutPixel(ColoredPoint)**: Desenha um pixel no quadro com a cor e na posição especificada no parâmetro. Esta função utiliza o ponteiro fornecido pelo framework e escreve diretamente nele os valores RGBA do parâmetro na posição especificada, ignorando, portanto, quaisquer cálculos relacionados a componente _**Alpha**_ (Para tal finalidade, pode-se utilizar a função `PutPixelAlpha(ColoredPoint)`, implementada e funcional, porém não usada no projeto original). Esta função implementa o cálculo das coordenadas de acordo com o framework embutido, isto é, considerando a memória de vídeo como uma região linear, fazendo uso da expressão `4*x + 4*y*IMAGE_WIDTH`, sendo *x* e *y* as coordenadas do ponto fornecido e *IMAGE_WIDTH* a constante que corresponde a largura da tela/janela, definida no framework. **ESTA FUNÇÃO NÃO REALIZA VERIFICAÇÕES DE SEGURANÇA NO PARÂMETRO FORNECIDO.**

**DrawLine(Line)**: Desenha uma linha, pixel-a-pixel através de `PutPixel(ColoredPoint)`, utilizando o algoritmo de Bresenham, interpolando as cores de acordo com os pontos fornecidos no paramêtro. Considerando que o ponto (0, 0) está localizado na parte superior esquerda da tela, foi adotado, por conveniência, o sistema de classificação de quadrantes/octantes equivalente ao exibido na imagem abaixo:

<p align="center">
	<br>
	<img src="https://github.com/ThiagoLuizNunes/CG-Assignments/raw/master/cg_framework/prints/bresenhamGeneralization.png"/ width=310px height=340px>
	<h5 align="center">Sistema horário de octantes/quadrantes.</h5>
	<br>
</p>

O Algoritmo de Bresenham, *a grosso modo*, é designado para desenhar retas apenas no primeiro octante, isto é, retas de 0º a 45º.
Dessa forma, faz-se necessário modificar/replicar o algoritmo para cada octante/quadrante OU aplicar transformações de modo a tornar os demais octantes/quadrantes equivalentes ao primeiro.

Nesse projeto, foi escolhida a segunda abordagem:
1. Primeiro, transformamos os quadrantes 2, 3 e 4 completos de modo a equivaler ao primeiro.
* 2º quadrante (3º e 4º octantes): Multiplica-se os valores do eixo-x por -1.
* 3º quadrante (5º e 6º octantes): Multiplica-se os valores dos eixos x e y por -1.
* 4º quadrante (7º e 8º octantes): Multiplica-se os valores do eixo-y por -1.<br>
Considerando que a função `PutPixel(ColoredPoint)` não processa valores negativos, as transformações nos eixos são revertidas antes da chamada da função. Dessa forma, é possível transformar facilmente os três mencionados quadrantes no primeiro e.<br>
2. Resta, no entanto, transformar o 2º octante, que está no primeiro quadrante mas não é suportado pelo protótipo básico do algoritmo (pois possui angulo de 45º a 90º). Isso implica que os octantes 3, 6 e 7 também não são suportados, pois são esses os octantes que passam a ser equivalentes ao 2º. Portanto, basta transformar ou corrigir o 2º octante e todos os demais estarão prontos, desde que já tenha sido realizada a primeira transformação. Para isso, foi decidido fazer o uso de ponteiros, de modo que os eixos x e y são trocados (entre si).

Essa abordagem (realizar transformações de modo a fazer todos os octantes equivalerem ao primeiro) permitiu a construção de um código razoavelmente sofisticado, mas enxuto e relativamente limpo de redundâncias<sup>[0]</sup>. Possibilita ainda uma excelente precisão e simetria em todos os octantes, devido a sua natureza replicativa:
<p align="center">
	<br>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/asterisk-detail-64.png"/ width=420px height=420px>
	<h5 align="center">Imagem em detalhe do experimento Example_Asterisk, evidênciando sua simetria. Zoom de 4x.</h5>
	<br>
</p>

**DrawTriangle(Triangle)**: Desenha um triângulo por meio do desenho de 3 retas usando `DrawLine(Line)` com os pontos fornecidos no parâmetro.

<p align="center">
	<br>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/triangle.png"/ >
	<h5 align="center">Experimento Example_Triangle</h5>
	<br>
</p>


<br>

---

## Experimentos

**Example_Triangle()**: Desenha um simples triângulo de posição e cores pré-definidos.

**Example_Asterisk(int)**: Desenha uma espécie de asterisco em formato circular usando retas desenhadas do centro para fora. Quanto maior o argumento, maior a quantidade de retas. Note que o exemplo faz uma simples interpolação de cores no centro da circuferência (aumento gradativo e "descontrolado"<sup>[1]</sup> do componente verde da cor).
<p align="center">
	<br>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/asterisk-32.png"/ width=280px height=280px>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/asterisk-64.png"/ width=280px height=280px>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/asterisk-256.png"/ width=280px height=280px>
	<h5 align="center">Da esquerda para a direita, Example_Asterisk executado com parâmetros 32, 64 e 256, respectivamente. Simultaneamente, Example_Triangle desenhado "por baixo".</h5>
	<br>
</p>

**Example_Slide(int)**: Desenha um reta de uma extremidade a outra da tela, interpolando as cores vermelho, azul e verde. O seu parâmetro define qual reta será desenhada. Na imagem abaixo, a função é chamada e o parâmetro sempre incrementado por `void MyGlDraw(void)`, presente em _**main.cpp**_:
<p align="center">
	<br>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/showezgif.gif"/ width=380px height=380px>
	<h5 align="center">Experimentos Example_Slide, Example_Triangle e Example_Asterisk executados simultaneamente.</h5>
	<br>
</p>

<br><br>

---

## Conclusão
Os resultados dos experimentos mostram que a parte estética demonstra-se satisfatória, evidenciando excelente qualidade no que se refere à precisão, simetria e interpolação de cores.

Como referência para os próximos projetos, pode-se destacar o maior cuidado ao usar e escrever códigos com ponteiros, tendo em vista a dificuldade inicial provocada pelo seu uso, bem como a natural dificuldade em documentar e explicar o funcionamento de técnicas que exploram fortemente seu uso.

<br><br>

---

## Referências
Material e especificações fornecido pelo docente.

https://github.com/ThiagoLuizNunes/CG-Assignments

<br>
<br>

0. _Se comparado ao método de re-escrita do algoritmo para cada octante._
1. _A Função simplesmente aumenta a componente verde da cor a cada reta desenhada sem verificar a possibilidade da ocorrência de Integer Overflow. O Experimento Example_Slide com parâmetro 256 (imagem acima) exemplifica a ocorrência deste evento._
