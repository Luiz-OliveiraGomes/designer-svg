#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <iostream>

/// ESSE ARQUIVO PODE RECEBER ACRESCIMOS NAS PARTES INDICADAS.
/// AS PARTES JAH IMPLEMENTADAS NAO PODEM SER SUPRIMIDAS OU MODIFICADAS.

class Shape;
using pShape = Shape*;

/// Classe base de todas as formas
class Shape
{
public:
  // Construtor (especifico e default)
  Shape(int R=0, int G=0, int B=0, double W=1.0):
    r(R),
    g(G),
    b(B),
    width(W)
  {}

  // destrutor virtual
  virtual ~Shape() = default;

  // copia polimorfica
  virtual Shape* clone() const = 0;

  // Leh uma forma generica de uma stream.
  // Leh a cor da forma e a largura do contorno.
  virtual void read(std::istream& X);

  // Salva a cor da forma e a largura do contorno em formato SVG
  virtual void save(std::ostream& X) const;

protected:
  // A cor da forma.
  // Precisa ser consultado pela FilledShape (por isso eh protegido).
  int r,g,b;

private:
  // Largura do contorno da forma
  double width=1.0;
};

/// Classe base de todas as formas que podem ser preenchidas ou nao
class FilledShape: public Shape
{
public:
  // Construtor (especifico e default)
  FilledShape(int R=0, int G=0, int B=0, int W=1, bool F=true):
    Shape(R,G,B,W),
    filled(F)
  {}

  // Leh uma forma preenchivel generica de uma stream.
  // Leh cor e largura (usando Shape::read) e depois se eh preenchida ou nao.
  void read(std::istream& X) override;

  // Salva a forma preenchivel em formato SVG.
  // Salva a cor e largura (usando Shape::save) e o depois se eh preenchida ou nao.
  void save(std::ostream& X) const override;

private:
  // forma preenchida ou nao
  bool filled=true;
};

/// Classe que representa linhas
class Line: public Shape
{
public:
  Line(int R=0, int G=0, int B=0, double W=1.0,
       double X1=0.0, double Y1=0.0, double X2=0.0, double Y2=0.0):
    Shape(R,G,B,W),
    x1(X1), y1(Y1), x2(X2), y2(Y2)
  {}

  // copia da linha
  Shape* clone() const override { return new Line(*this); }

  void read(std::istream& X) override;
  void save(std::ostream& X) const override;

private:
  // pontos da linha
  double x1=0.0, y1=0.0, x2=0.0, y2=0.0;
};

/// Classe que representa circulos
class Circle: public FilledShape
{
public:
  Circle(int R=0, int G=0, int B=0, double W=1.0, bool F=true,
         double Xc=0.0, double Yc=0.0, double Rc=1.0):
    FilledShape(R,G,B,W,F),
    xc(Xc), yc(Yc), rc(Rc)
  {}

  // copia do circulo
  Shape* clone() const override { return new Circle(*this); }

  void read(std::istream& X) override;
  void save(std::ostream& X) const override;

private:
  // centro e raio
  double xc=0.0, yc=0.0, rc=1.0;
};

/// Classe que representa estrelas
class Star: public FilledShape
{
public:
  Star(int R=0, int G=0, int B=0, double W=1.0, bool F=true,
       double Xc=0.0, double Yc=0.0, double Rc=1.0):
    FilledShape(R,G,B,W,F),
    xc(Xc), yc(Yc), rc(Rc)
  {}

  // copia da estrela
  Shape* clone() const override { return new Star(*this); }

  void read(std::istream& X) override;
  void save(std::ostream& X) const override;

private:
  // centro e raio
  double xc=0.0, yc=0.0, rc=1.0;
};

/// Classe que representa retangulos
class Rectangle: public FilledShape
{
public:
  Rectangle(int R=0, int G=0, int B=0, double W=1.0, bool F=true,
            double Xmin=0.0, double Xmax=1.0, double Ymin=0.0, double Ymax=1.0):
    FilledShape(R,G,B,W,F),
    xmin(Xmin), xmax(Xmax), ymin(Ymin), ymax(Ymax)
  {}

  // copia do retangulo
  Shape* clone() const override { return new Rectangle(*this); }

  void read(std::istream& X) override;
  void save(std::ostream& X) const override;

private:
  // limites do retangulo
  double xmin=0.0, xmax=1.0, ymin=0.0, ymax=1.0;
};

/// Classe que representa losangos
class Rhombus: public FilledShape
{
public:
  Rhombus(int R=0, int G=0, int B=0, double W=1.0, bool F=true,
          double Xmin=0.0, double Xmax=1.0, double Ymin=0.0, double Ymax=1.0):
    FilledShape(R,G,B,W,F),
    xmin(Xmin), xmax(Xmax), ymin(Ymin), ymax(Ymax)
  {}

  // copia do losango
  Shape* clone() const override { return new Rhombus(*this); }

  void read(std::istream& X) override;
  void save(std::ostream& X) const override;

private:
  // limites do losango
  double xmin=0.0, xmax=1.0, ymin=0.0, ymax=1.0;
};

/// Classe que representa triangulos
class Triangle: public FilledShape
{
public:
  Triangle(int R=0, int G=0, int B=0, double W=1.0, bool F=true,
           double X1=0.0, double Y1=0.0,
           double X2=1.0, double Y2=0.0,
           double X3=0.0, double Y3=1.0):
    FilledShape(R,G,B,W,F),
    x1(X1), y1(Y1), x2(X2), y2(Y2), x3(X3), y3(Y3)
  {}

  // copia do triangulo
  Shape* clone() const override { return new Triangle(*this); }

  void read(std::istream& X) override;
  void save(std::ostream& X) const override;

private:
  // vertices do triangulo
  double x1=0.0, y1=0.0, x2=1.0, y2=0.0, x3=0.0, y3=1.0;
};

#endif // _SHAPE_H_
