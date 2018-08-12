# ICG-1st-BresenhamAlgorithm
---

## Introdução



---


## O Projeto


<br>
---

## As estruturas
O Projeto possui uma hierarquia de estruturas "primitivas" usados nas chamadas das funções:

**struct Color**: Representa uma cor no sistema, composto pelas componentes RGBA, cada uma em sua variável (unsigned char), variando de 0 a 255 de acordo com o padrão. Cada "instância" ocupa um total de 4 bytes na memória RAM da maioria dos sistemas.

**struct Point**: Representa um ponto no sistema de coordenadas, composto pelos inteiros **x** e **y**.

**struct ColoredPoint**: Representa uma tupla Ponto-Cor; sendo definido, portanto, como uma associação de um ponto **p** a uma cor **c**.

**struct Line**: Representa uma tupla de ColoredPoint; sendo definido, portanto, como uma reta entre dois pontos de cores diferentes.

**struct Triangle**: Representa uma tripla de ColoredPoint; sendo definido, portanto, como um triângulo entre três pontos de cores diferentes.
<br><br><br>


---

## As funções/métodos
**PutPixel(ColoredPoint)**: Desenha um pixel no quadro com a cor e na posição especificada no parâmetro. Esta função utiliza o ponteiro fornecido e escreve nele diretamente os valores RGBA do parâmetro na posição especificada, ignorando, portanto, quaisquer cálculos relacionados a componente **Alpha**. Alternativamente, para tal finalidade, pode-se utilizar a função **PutPixelAlpha(ColoredPoint)**, implementada e funcional, porém não usada no projeto original. **ESTA FUNÇÃO NÃO VERIFICA A VALIDADE DOS PONTOS FORNECIDOS**

**DrawLine(Line)**: Desenha uma linha utilizando o algoritmo de Bresenham, interpolando as cores de acordo com os pontos fornecidos no paramêtro. Considerando que o ponto (0,0) está localizado na parte superior direita da tela, foi adotado, por conveniência, o sistema de classificação de quadrantes/octantes equivalente ao evidenciado na imagem abaixo:

<p align="center">
	<br>
	<img src="https://github.com/ThiagoLuizNunes/CG-Assignments/raw/master/cg_framework/prints/bresenhamGeneralization.png"/ width=310px height=340px>
	<h5 align="center">Sistema horário de octantes/quadrantes.</h5>
	<br>
</p>

O Algoritmo de Bresenham é designado para desenhar retas apenas no primeiro octante, isto é, retas de 0º a 45º.
Dessa forma, faz-se necessário modificar o algoritmo para cada octante/quadrante OU aplicar transformações de modo a tornar os demais octantes/quadrantes equivalentes ao primeiro.<br>
Nesse projeto, foi escolhida a segunda abordagem:
1. Primeiro, transformamos os quadrantes 2, 3 e 4 completos de modo a equivaler ao primeiro.
* 2º quadrante (3º e 4º octantes): Multiplica-se os valores do eixo-x por -1.
* 3º quadrante (5º e 6º octantes): Multiplica-se os valores dos eixos x e y por -1.
* 4º quadrante (7º e 8º octantes): Multiplica-se os valores do eixo-y por -1.<br>
Considerando que a função PutPixel não processa valores negativos, as transformações nos eixos são revertidas durante a chamada da função. Dessa forma, é possível transformar facilmente os três mencionados quadrantes no primeiro e aplicar o algoritmo nos mesmos.<br>
2. Resta, no entanto, transformar o 2º octante, que está no primeiro quadrante mas não é suportado pelo protótipo básico do algoritmo (pois possui angulo de 45º a 90º). Isso implica que os octantes 3, 6 e 7 também não são suportados, pois são esses os octantes que passam a ser equivalentes ao 2º. Portanto, basta transformar ou corrigir o 2º octante e todos os demais estarão prontos, desde que já tenha sido realizada a primeira transformação. Para isso, foi decidido fazer o uso de ponteiros, de modo que os eixos x e y são trocados (entre si).

Essa abordagem (realizar transformações de modo a fazer todos os octantes equivalerem ao primeiro) permitiu a construção de um código razoavelmente sofisticado, mas enxuto e relativamente limpo de redundâncias. Possibilita ainda uma excelente precisão e simetria em todos os octantes, devido a sua natureza replicativa.
<p align="center">
	<br>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/asterisk-detail-64.png"/ width=420px height=420px>
	<h5 align="center">Imagem em detalhe do experimento Example_Asterisk, evidênciando sua simetria. Zoom de 4x.</h5>
	<br>
</p>

**DrawTriangle(Triangle)**: Desenha um triângulo por meio do desenho de 3 retas usando DrawLine(Line) com os pontos fornecidos no parâmetro.

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

**Example_Asterisk(int)**: Desenha uma espécie de asterisco em formato circular. Quanto maior o argumento, maior a quantidade de retas. Note que o exemplo faz uma simples interpolação de cores no centro da circuferência (aumento gradativo e descontrolado do componente verde da cor).
<p align="center">
	<br>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/asterisk-32.png"/ width=280px height=280px>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/asterisk-64.png"/ width=280px height=280px>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/asterisk-256.png"/ width=280px height=280px>
	<h5 align="center">Da esquerda para a direita, Example_Asterisk executado com parâmetros 32, 64 e 256, respectivamente. Simultaneamente, Example_Triangle desenhado "por baixo".</h5>
	<br>
</p>

**Example_Slide(int)**: Desenha um reta de uma extremidade a outra da tela, interpolando as cores vermelho, azul e verde. O seu parâmetro define qual reta será desenhada. Na imagem abaixo, a função é chamada e o parâmetro sempre incrementado por **void MyGlDraw(void)**, presente em **main.cpp**:
<p align="center">
	<br>
	<img src="https://github.com/VictorKoehler/ICG-1st-BresenhamAlgorithm/raw/master/images/showezgif.gif"/ width=380px height=380px>
	<h5 align="center">Experimentos Example_Slide, Example_Triangle e Example_Asterisk executados simultaneamente.</h5>
	<br>
</p>


---
## Conclusão



---

## Referências
Material e especificações fornecido pelo docente.<br>
https://github.com/ThiagoLuizNunes/CG-Assignments
