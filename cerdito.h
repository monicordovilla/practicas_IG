//**************************************************************************
// Clases para realizar la practica 3
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "objetos_B3.h"

using namespace std;

//*************************************************************************
// Cilindro(para las paras y la nariz)
//*************************************************************************

class _cilindro: public _triangulos3D
{
public:
	_cilindro();
void parametros(float alto, float ancho, int num);
};

//*************************************************************************
// Abdomen
//*************************************************************************

class _abdomen: public _triangulos3D
{
public:

	_abdomen(); //alto 5 ancho 4 profundo 2
};

//*************************************************************************
// Pata
// alto 2 radio 1
//*************************************************************************

class _pata: public _triangulos3D
{
public:
	_pata();
	void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

_cilindro cilindro;
};

//*************************************************************************
// Nariz
//*************************************************************************

class _nariz: public _triangulos3D
{
public:

	_nariz(); //alto 1 ancho 1 profundo 1
	void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

_cilindro cilindro;
};

//*************************************************************************
// Oreja
//*************************************************************************

class _oreja: public _triangulos3D
{
public:

	_oreja(); //alto 1 radio 0.5
	void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_piramide piramide;
};

//*************************************************************************
// Cara
//*************************************************************************

class _esfera: public _triangulos3D
{
public:

	_esfera(); //radio 2
};

//*************************************************************************
// Cara
//*************************************************************************

class _cara: public _triangulos3D
{
public:

	_cara();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float radio;

protected:
_esfera  esfera;
_oreja orejaDer;
_oreja orejaIzq;
_nariz nariz;
};

//*************************************************************************
// Cuerpo (abdomen + patas)
//*************************************************************************

class _cuerpo: public _triangulos3D
{
public:
       _cuerpo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, float giro, float saludo);

float alturaC;
float anchuraC;
float profundidadC;
float alturaP;
float radioP;

_pata  pataSupDer;
_pata  pataSupIzq;
_pata  pataInfDer;
_pata  pataInfIzq;
protected:
_abdomen  abdomen;
};

//*************************************************************************
// Cerdito
//*************************************************************************

class _cerdito: public _triangulos3D
{
public:
//movimiento de las patas
float giro_pata;
float giro_saludo;
int saludo_arriba;
float giro_pata_min;
float giro_pata_max;
//movimiento de la cara
float giro_cara = 0.0;
float giro_cara_max = 45.0;
float giro_cara_min = -45.0;


       _cerdito();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cuerpo cuerpo;
_cara cara;
};
