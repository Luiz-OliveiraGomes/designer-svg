# Designer SVG

**C++17 · Polimorfismo · SVG**

Gerador de desenhos 2D em C++ que lê uma descrição de formas geométricas e exporta o resultado em SVG. O projeto explora polimorfismo com métodos virtuais para representar e exportar cada tipo de forma.

<p align="center">
  <img src="exemplo.svg" alt="Composição SVG com fundo verde, losango amarelo e círculo azul" width="480">
</p>

Exemplo incluído no repositório. O desenho usa um retângulo, um losango e um círculo descritos em [exemplo.txt](exemplo.txt).

## Funcionalidades

- Modela linhas, círculos, estrelas, retângulos, losangos, triângulos e textos.
- Permite definir desenhos por arquivo ou criar formas diretamente em C++.
- Inclui exemplos para experimentar o formato de entrada e visualizar a saída.

## Como executar

Compile na raiz do repositório ou abra `DesignerCorrigido1.cbp` no Code::Blocks.

```sh
g++ -std=c++17 designer-main.cpp designer.cpp shape.cpp -o designer
./designer
```

No Windows, execute `.\designer.exe`. Quando o programa pedir os arquivos, digite `exemplo.txt` para a entrada e `resultado.svg` para a saída. Abra o SVG no navegador. Os arquivos `eua.cpp`, `grecia.cpp` e `teste.cpp` são exemplos separados da aplicação principal.

## Créditos

Projeto de C++ da UFRN desenvolvido a partir da especificação do professor Adelardo Adelino Dantas de Medeiros.
