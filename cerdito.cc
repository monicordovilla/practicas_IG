#include "cerdito.h"

//*************************************************************************
// Cilindro
//*************************************************************************
_cilindro::_cilindro(){}

void _cilindro::parametros(float alto, float ancho, int num){

//perfil
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=ancho/2; aux.y=-alto/2; aux.z=0.0;
perfil.push_back(aux);
aux.x=ancho/2; aux.y=alto/2; aux.z=0.0;
perfil.push_back(aux);

int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux; //numero de puntos que tiene el perfil

// tratamiento de los vértices
num_aux=perfil.size();
vertices.resize(num_aux*num);
caras.clear();
for (j=0; j<num; j++)
  {for (i=0; i<num_aux; i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras j=perfiles i=puntos
for(j=0; j<num; j++)
{for (i=0;i<num_aux-1;i++)
     {
		cara_aux._0=i + ((j+1)%num)*num_aux;
		cara_aux._1=i + 1 + ((j+1)%num)*num_aux;
		cara_aux._2=i + 1 + j*num_aux;
		caras.push_back(cara_aux);

		cara_aux._0=i + 1 + j*num_aux;
		cara_aux._1=i + j*num_aux;
		cara_aux._2=i + ((j+1)%num)*num_aux;
		caras.push_back(cara_aux);
	}
}
     
 // tapa inferior
if (fabs(perfil[0].x)>0.0) //Si el objeto de revolucion empieza fuera del eje
  {
	vertice_aux.x=0.0;  //Creamos un nuevo punto en mitad del eje, a la misma altura del primer punto del perfil
	vertice_aux.y=perfil[0].y;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<num; j++) //Y creamos caras que unen los puntos inferiores del perfil con nuestro nuevo punto central
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=j*num_aux;
		cara_aux._2=((j+1)%num)*num_aux;
		caras.push_back(cara_aux);
	}
  }
 
 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
	vertice_aux.x=0.0;
	vertice_aux.y=perfil[num_aux-1].y;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<num; j++)
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=j*num_aux+num_aux-1;
		cara_aux._2=((j+1)%num)*num_aux+num_aux-1;
		caras.push_back(cara_aux);
	}
  }

}

//*************************************************************************
// Abdomen
// alto 5 ancho 4 profundo 2
//*************************************************************************
_abdomen::_abdomen(){
float tam = 2.0;
float ancho = 2.0;
float profundo = 1.0;

	//vertices
	vertices.resize(8);
	vertices[0].x=-ancho;vertices[0].y=-tam-1;vertices[0].z=profundo;
	vertices[1].x=ancho;vertices[1].y=-tam-1;vertices[1].z=profundo;
	vertices[2].x=ancho;vertices[2].y=-tam-1;vertices[2].z=-profundo;
	vertices[3].x=-ancho;vertices[3].y=-tam-1;vertices[3].z=-profundo;
	vertices[4].x=-ancho;vertices[4].y=tam;vertices[4].z=profundo;
	vertices[5].x=ancho;vertices[5].y=tam;vertices[5].z=profundo;
	vertices[6].x=ancho;vertices[6].y=tam;vertices[6].z=-profundo;
	vertices[7].x=-ancho;vertices[7].y=tam;vertices[7].z=-profundo;

	// triangulos
	caras.resize(12);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=4;caras[1]._2=5;

	caras[2]._0=1;caras[2]._1=2;caras[2]._2=5;
	caras[3]._0=2;caras[3]._1=5;caras[3]._2=6;

	caras[4]._0=2;caras[4]._1=3;caras[4]._2=6;
	caras[5]._0=3;caras[5]._1=6;caras[5]._2=7;

	caras[6]._0=3;caras[6]._1=0;caras[6]._2=7;
	caras[7]._0=0;caras[7]._1=7;caras[7]._2=4;

	caras[8]._0=0;caras[8]._1=1;caras[8]._2=2;
	caras[9]._0=0;caras[9]._1=2;caras[9]._2=3;

	caras[10]._0=4;caras[10]._1=5;caras[10]._2=6;
	caras[11]._0=4;caras[11]._1=6;caras[11]._2=7;
} 

//*************************************************************************
// Pata
// alto 2 radio 1
//*************************************************************************

 _pata::_pata(){

	float alto = 2.0;
	float ancho = 1.0;
	int num = 8;
	cilindro.parametros(alto, ancho, num);
}

void _pata::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	cilindro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

//*************************************************************************
// Nariz
// alto 1 ancho 1
//*************************************************************************

_nariz::_nariz(){

	float alto = 0.5;
	float ancho = 1.0;
	int num = 6;
	cilindro.parametros(alto, ancho, num);

}

void _nariz::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	glRotatef(90.0,1,0,0);
	cilindro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

//*************************************************************************
// Oreja
// cono de alto 1 radio 0.5
//*************************************************************************

_oreja::_oreja(){
	float alto = 2.0;
	float ancho = 1.0;
	piramide = _piramide(ancho , alto);
}

void _oreja::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	piramide.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

/*float altura = 1.0;
float radio = 0.5;
int num = 3;

int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;

// tratamiento de los vértices
vertices.resize(num);
caras.clear();
for (j=0; j<num; j++){
      vertice_aux.x=radio*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-radio*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=0.0;
      vertices[j]=vertice_aux;
  }

     
	// tapa inferior
	vertice_aux.x=0.0;  //Creamos un nuevo punto en mitad del eje, a la misma altura del primer punto del perfil
	vertice_aux.y=0.0;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<num; j++) //Y creamos caras que unen los puntos inferiores del perfil con nuestro nuevo punto central
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=j;
		cara_aux._2=(j+1)%num;
		caras.push_back(cara_aux);
	}

	// tapa superior
	vertice_aux.x=0.0;
	vertice_aux.y=altura;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<num; j++)
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=j;
		cara_aux._2=(j+1)%num;
		caras.push_back(cara_aux);
	}
*/
//*************************************************************************
// esfera
// radio 2
//*************************************************************************

_esfera::_esfera(){
int perfiles = 6;
int puntos = 6;
float radio = 2.0;
int i,j;
vector<_vertex3f> perfil;
_vertex3f vertice_aux;
_vertex3i cara_aux;
vertices.clear();
// tratamiento de los vértices
for (j=0; j<perfiles; j++){
      vertice_aux.x=radio*cos( (3*M_PI)/2 + M_PI*(1+j)/(1.0+perfiles));
      vertice_aux.y=radio*sin( (3*M_PI)/2 + M_PI*(1+j)/(1.0+perfiles));
      vertice_aux.z=0.0;
	  perfil.push_back(vertice_aux);
  }

for (j=0; j<perfiles; j++)
  {for (i=0; i<puntos; i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*perfiles))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*perfiles));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*perfiles))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*perfiles));
      vertice_aux.y=perfil[i].y;

      vertices.push_back(vertice_aux);
     }
  }

// tratamiento de las caras
for(j=0; j<perfiles; j++)
{for (i=0;i<puntos-1; i++)
     {	
/**/
		cara_aux._0=i + ((j+1)%perfiles)*puntos;
		cara_aux._1=i + 1 + ((j+1)%perfiles)*puntos;
		cara_aux._2=i + 1 + j*puntos;
		caras.push_back(cara_aux);

		cara_aux._0=i + 1 + j*puntos;
		cara_aux._1=i + j*puntos;
		cara_aux._2=i + ((j+1)%perfiles)*puntos;
		caras.push_back(cara_aux);
}
}

 // tapa inferior
	vertice_aux.x=0.0;  //Creamos un nuevo punto en mitad del eje, a la misma altura del primer punto del perfil
	vertice_aux.y=-radio;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<perfiles; j++) //Y creamos caras que unen los radio inferiores del perfil con nuestro nuevo punto central
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=j*perfiles;
		cara_aux._2=((j+1)%puntos)*perfiles;
		caras.push_back(cara_aux);
	}
 
 // tapa superior
	vertice_aux.x=0.0;
	vertice_aux.y=radio;
	vertice_aux.z=0.0;
	vertices.push_back(vertice_aux);

	for(j=0; j<perfiles; j++)
	{
		cara_aux._0=vertices.size()-1;
		cara_aux._1=puntos-1+j*perfiles;
		cara_aux._2=puntos-1+((j+1)%puntos)*perfiles;
		caras.push_back(cara_aux);
	}
}

//*************************************************************************
// Cara
//*************************************************************************

_cara::_cara(){
	radio = 2.0;
}

void _cara::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	glPushMatrix();
	esfera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -(radio/2) , radio-(0.25));
	glRotatef(25.0,1,0,0);
	nariz.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef( -radio/2, radio/2 , 0);
	glRotatef(45.0,0,0,1);
	orejaIzq.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef( radio/2 , radio/2 , 0);
	glRotatef(-45.0,0,0,1);
	orejaDer.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

//*************************************************************************
// Cuerpo
//*************************************************************************

_cuerpo::_cuerpo(){
	alturaC = 5.0;
	anchuraC = 4.0;
	profundidadC = 2.0;
	alturaP = 3.0;
	radioP = 1.0;
}

void _cuerpo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, float giro, float saludo)
{
	glPushMatrix();
	abdomen.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(anchuraC/2+radioP/2,-alturaC/2,0);
	glRotatef(90.0+giro,0,0,1);
	pataInfDer.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(anchuraC/2+radioP/2),-alturaC/2,0);
	glRotatef(-90.0-giro,0,0,1);
	pataInfIzq.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(anchuraC/2+radioP/2, (alturaC/2)-1 ,0);
	glRotatef(90.0+giro+saludo,0,0,1);
	pataSupDer.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-(anchuraC/2+radioP/2), (alturaC/2)-1 ,0);
	glRotatef(-90.0-giro,0,0,1);
	pataSupIzq.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();

}
//*************************************************************************
// Cerdito
//*************************************************************************

_cerdito::_cerdito(){
	giro_pata = 0.0;
	giro_saludo = 0.0;
	saludo_arriba = 1;
	giro_pata_min = -8.0;
	giro_pata_max = 8.0;

	giro_cara = 0.0;
	giro_cara_max = 15.0;
	giro_cara_min = -45.0;
}

void _cerdito::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{

	glPushMatrix();
	cuerpo.draw(modo, r1, g1, b1, r2, g2, b2, grosor, giro_pata, giro_saludo);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3.5, 0);
	glRotatef(giro_cara,1,0,0);
	cara.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}
