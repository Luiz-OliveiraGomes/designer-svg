#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>
#include <utility>
#include <stdexcept>

#include "designer.h"

/// ESTE ARQUIVO PODE RECEBER ACRESCIMOS NAS PARTES INDICADAS.
/// AS PARTES JAH IMPLEMENTADAS NAO PODEM SER SUPRIMIDAS OU MODIFICADAS.

using namespace std;

/// Construtor especifico
Designer::Designer(double Width, double Height):
  width(Width>=0.0 ? Width : 0.0),
  height(Height>=0.0 ? Height : 0.0),
  VS()
{}

/// Construtor por copia
Designer::Designer(const Designer& D):
  width(D.width),
  height(D.height),
  VS()
{
  try
  {
    // copia as formas uma por uma
    for (auto S : D.VS)
    {
      if (S != nullptr)
      {
        VS.push_back(S->clone());
      }
    }
  }
  catch (...)
  {
    // limpa
    clear();
    throw;
  }
}

/// Construtor por movimento
Designer::Designer(Designer&& D) noexcept:
  width(D.width),
  height(D.height),
  VS(move(D.VS))
{
  // zera o objeto que foi movido
  D.width = 0.0;
  D.height = 0.0;
}

/// Atribuicao por copia
Designer& Designer::operator=(const Designer& D)
{
  // Teste de autoatribuicao
  if (this==&D) return *this;

    //cria uma copia temporaria
    Designer prov(D);

    //passa essa copia para o objeto atual
    *this = move(prov);

  return *this;
}

/// Atribuicao por movimento
Designer& Designer::operator=(Designer&& D) noexcept
{
  // Teste de autoatribuicao
  if (this==&D) return *this;

    clear();

    width = D.width;
    height = D.height;

    // pega o vetor de formas do outro objeto
    VS = move(D.VS);


    D.width = 0.0;
    D.height = 0.0;

  return *this;
}

/// Limpa o desenho
void Designer::clear() noexcept
{
  width = height = 0.0;

    // apaga as formas que estavam no vetor
    for (auto S : VS)
    {
      delete S;
    }

    VS.clear();
}

/// Inclusao de nova forma no desenho
void Designer::include(const Shape& S)
{
    // guarda uma copia da forma recebida
    VS.push_back(S.clone());
}

/// Leitura de arquivo com as formas
void Designer::read(const string& fileName)
{
  ifstream arq(fileName);
  if (!arq.is_open())
  {
    string msg = "could not open file "+fileName;
    throw ios_base::failure(msg);
  }

  // Leh o cabecalho
  string texto;
  double W,H;
  arq >> texto >> W >> H;
  if (!arq.good() || texto!="DESIGNER" || W<=0.0 || H<=0.0)
    throw ios_base::failure("invalid file");

  // Cria um novo Designer temporario, inicialmente vazio (sem formas)
  Designer prov(W,H);

  // Laco de leitura das diversas formas do desenho.
  // Permanece ateh o fim do arquivo.
  bool arquivo_acabou = false;
  char tipo_forma;

  do
  {
    // Leh o tipo de forma (char)
    arq >> tipo_forma;
    // Testa se acabou o arquivo
    if (!arq.good())
    {
      arquivo_acabou = true;
      continue;
    }
    tipo_forma = toupper(tipo_forma);

    // Cria dinamicamente (aloca) a nova forma de acordo com o caractere tipo_forma.
    // Se o caractere nao for nenhum dos identificadores de formas,
    // ignora o restante da linha do arquivo
    Shape* nova_forma = nullptr;

    switch (tipo_forma)
    {
      case '-':
        nova_forma = new Line;
        break;

      case 'C':
        nova_forma = new Circle;
        break;

      case 'S':
        nova_forma = new Star;
        break;

      case 'R':
        nova_forma = new Rectangle;
        break;

      case 'L':
        nova_forma = new Rhombus;
        break;

      case 'T':
        nova_forma = new Triangle;
        break;

      default:
        // ignora linhas que nao indicam uma forma valida
        arq.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }

    // Se a nova forma foi alocada (caractere corresponde a uma das formas):
    // - Leh a forma do arquivo (em um try para capturar as excecoes na leitura)
    // - Acrescenta a forma no vetor de formas do Designer temporario (prov)
    try
    {
      // le os dados da forma criada
      nova_forma->read(arq);

      prov.include(*nova_forma);

      // libera a forma temporaria
      delete nova_forma;
      nova_forma = nullptr;
    }
    catch (...)
    {
      // evita vazamento se a leitura der erro
      delete nova_forma;
      throw;
    }
  }
  while(!arquivo_acabou);

  // Testa o numero de formas lidas
  if (prov.getNumShapes() == 0) throw ios_base::failure("empty file");

  // Faz *this assumir o conteudo de prov
  *this = move(prov);
}

/// Salvamento do desenho em formato SVG
void Designer::save(const string& fileName) const
{
  // Nao exporta se o desenho for vazio
  if (getNumShapes()==0 || width<=0 || height<=0) throw logic_error("empty designer");

  // Abre o arquivo SVG para escrita
  ofstream arq(fileName);
  if (!arq.is_open())
  {
    string msg = "could not open file "+fileName;
    throw ios_base::failure(msg);
  }

  // Escreve o cabecalho inicial
  arq << "<svg"
      << " width=" << '"' << width << '"'
      << " height=" << '"' << height << '"'
      << " xmlns=" << '"' << "http://www.w3.org/2000/svg"  << '"'
      << ">\n";

  // Salva as formas
  for (auto S : VS)
  {
    if (S!=nullptr) S->save(arq); // NUNCA deve ser nullptr, mas nao custa garantir
    arq << endl;
  }

  // Escreve o rodapeh final
  arq << "</svg>" << endl;
}
