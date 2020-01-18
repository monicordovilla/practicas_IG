//**************************************************************************
// Práctica 5 usando objetos
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "cerdito.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO, CERDITO} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

//varibles de control del objeto articulado
int flag=0;
int seMueve = 0;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply;
_rotacion rotacion;
_tanque tanque;
_cerdito cerdito;

// _objeto_ply *ply1;
int estadoRaton[3], xc, yc;

solido *piramide1, *piramide2, *piramide3, *piramide4, *piramide5;

int Ancho=450, Alto=450, tipo_camara=0;
float factor=1.0;

void pick_color(int x, int y);

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
if(tipo_camara == 0){
	glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}
else if(tipo_camara == 1){
	glOrtho(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glRotatef(0,factor,0,0);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
	case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	case CERDITO: cerdito.draw(modo, 0.737255,0.560784,0.737255, 1.0,0.0,1.0, 2);break;
	}

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{
	clean_window();
	/*clean_window();
	change_observer();
	draw_axis();
	draw_objects();
	glutSwapBuffers();*/

	if(tipo_camara == 0){
		change_observer();
	}
	else if(tipo_camara ==1){
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(4,1,4, -1,0,0, 0.1,-1,0); //Posicion desde la que se observaría
		glScalef(factor,factor,factor);
	}
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
	case '5':(tipo_camara++)%2;break;
	case 'P':t_objeto=PIRAMIDE;break;
	case 'C':t_objeto=CUBO;break;
	case 'O':t_objeto=OBJETO_PLY;break;
	case 'R':t_objeto=ROTACION;break;
	case 'A':t_objeto=ARTICULADO;break;
	case 'G':t_objeto=CERDITO;break;
	case 'N':
		if(tipo_camara==1)factor*=0.9;
		if(tipo_camara==0)Observer_distance*=0.9;
		break;
	case 'M':
		if(tipo_camara==1)factor*=1.1;
		if(tipo_camara==0)Observer_distance*=1.1;
		break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
        case GLUT_KEY_F1:
		if(t_objeto==ARTICULADO){
			tanque.giro_tubo+=1;
                         if (tanque.giro_tubo>tanque.giro_tubo_max) tanque.giro_tubo=tanque.giro_tubo_max;
		}
		else if(t_objeto==CERDITO){
			cerdito.giro_pata+=1;
				if (cerdito.giro_pata > cerdito.giro_pata_max){
					cerdito.giro_pata=cerdito.giro_pata_max;
					/*Quiero que continue desde el punto en el que saluda pero que no
					supere el angulo maximo y en este punto se coordine con los demas*/
					cerdito.giro_saludo = 0;
				}
		}
                 break;
        case GLUT_KEY_F2:
		if(t_objeto==ARTICULADO){
			tanque.giro_tubo-=1;
                         if (tanque.giro_tubo<tanque.giro_tubo_min) tanque.giro_tubo=tanque.giro_tubo_min;

		}
		else if(t_objeto==CERDITO){
			cerdito.giro_pata-=1;
				if (cerdito.giro_pata < cerdito.giro_pata_min){
					cerdito.giro_pata=cerdito.giro_pata_min;
					/*Quiero que continue desde el punto en el que saluda pero que no
					supere el angulo minimo y en este punto se coordine con los demas*/
					cerdito.giro_saludo = 0;
				}
		}
			break;
        case GLUT_KEY_F3:
		if(t_objeto==ARTICULADO){
			tanque.giro_torreta+=5;
		}
		else if(t_objeto==CERDITO){
			/**INICIO ANIMACION**/
			if(seMueve == 0) seMueve = 1;
			else seMueve = 0;

		}
			break;
        case GLUT_KEY_F4:
		if(t_objeto==ARTICULADO){
			tanque.giro_torreta-=5;
		}
		else if(t_objeto==CERDITO){
			cerdito.giro_cara-=1;
			if (cerdito.giro_cara < cerdito.giro_cara_min)
				cerdito.giro_cara=cerdito.giro_cara_min;
		}
			break;
		case GLUT_KEY_F5:
		if(t_objeto==CERDITO){
			cerdito.giro_cara+=1;
			if (cerdito.giro_cara > cerdito.giro_cara_max)
				cerdito.giro_cara=cerdito.giro_cara_max;
		}
			break;
		case GLUT_KEY_F6:
		if(t_objeto==CERDITO){
			if(cerdito.salto >= cerdito.salto_max ) cerdito.saltando = false;
			if(cerdito.salto <= cerdito.salto_min )	cerdito.saltando = true;

			if(cerdito.saltando){
				cerdito.salto += 0.5;
			}
			else{
				cerdito.salto -= 0.5;
			}
		}
			break;
	}

glutPostRedisplay();
}


//***************************************************************************
// Funcion de movimiento de mi animacion
//***************************************************************************

void automatico()
{
	if(seMueve == 1){
		//movimiento de subida del saludo
		if (flag==0) cerdito.giro_saludo+=0.5;
		if ( (cerdito.giro_saludo + cerdito.giro_pata) > cerdito.giro_pata_max && flag==0 )
			{
				cerdito.giro_saludo=cerdito.giro_pata_max - cerdito.giro_pata; //Se resta el giro ya que la suma de ambas puede superar el maximo
		   		flag=1;
			}

		//movimiento de bajada del saludo
		if (flag==1) cerdito.giro_saludo-=0.5;
		if ( (cerdito.giro_saludo + cerdito.giro_pata) < cerdito.giro_pata_min && flag==1 )
			{
				cerdito.giro_saludo=cerdito.giro_pata_min - cerdito.giro_pata; //Se resta el giro ya que la suma de ambas puede superar el minimo
				flag=0;
			}

		glutPostRedisplay();
	}
}

//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
     }
   else estadoRaton[2] = 1;
   }
if(boton== GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      pick_color(xc, yc);
    }
  }
	if(boton== 3) { //SCROLL UP
		if(tipo_camara==1)factor/=1.2;
		if(tipo_camara==0)Observer_distance/=1.2;
		glutPostRedisplay();
	 }
	if(boton== 4) { //SCROLL DOWN
		if(tipo_camara==1)factor*=1.2;
		if(tipo_camara==0)Observer_distance*=1.2;
		glutPostRedisplay();
	}
}

/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}



/*************************************************************************/

void RatonMovido( int x, int y )
{
float x0, y0, xn, yn;
if(estadoRaton[2]==1)
    {getCamara(&x0,&y0);
     yn=y0+(y-yc);
     xn=x0-(x-xc);
     setCamara(xn,yn);
     xc=x;
     yc=y;
     glutPostRedisplay();
    }
}

//***************************************************************************
// Funciones para la seleccion
//************************************************************************


void procesar_color(GLint hits, GLuint *names)
{
	std::cout << "HIIIIIEEEAATS " << hits << '\n';
	if(hits<=0) return;
	unsigned num= names[3];
	std::cout << "num "<< num << '\n';

	// mostrar contenido de la pila
	printf("%d hits:\n", hits);
	for (int i = 0; i < hits; i++)
		printf("Número: %d\n Min Z: %d\n Max Z: %d\n Nombre en la pila: %d\n",
			(GLubyte)names[i * 4],
			(GLubyte)names[i * 4 + 1],
			(GLubyte)names[i * 4 + 2],
			(GLubyte)names[i * 4 + 3]);
	printf("\n");

	//procesar el cambiode colo
	if ( t_objeto==CERDITO){
		switch (num){
			//case 1: cerdito.cuerpo.abdomen.coloreado = !cerdito.cuerpo.abdomen.coloreado ;break;
			case 2: cerdito.cuerpo.pataSupDer.coloreado = !cerdito.cuerpo.pataSupDer.coloreado; cout << "Selec" << endl; break;
			case 3: cerdito.cuerpo.pataSupIzq.coloreado = !cerdito.cuerpo.pataSupIzq.coloreado;break;
			case 4: cerdito.cuerpo.pataInfDer.coloreado = !cerdito.cuerpo.pataInfDer.coloreado;break;
			case 5: cerdito.cuerpo.pataInfIzq.coloreado = !cerdito.cuerpo.pataInfIzq.coloreado;break;
			case 6: cerdito.cara.esfera.coloreado = !cerdito.cara.esfera.coloreado;break;
			case 7: cerdito.cara.orejaDer.coloreado = !cerdito.cara.orejaDer.coloreado;break;
			case 8: cerdito.cara.orejaIzq.coloreado = !cerdito.cara.orejaIzq.coloreado;break;
			case 9: cerdito.cara.nariz.coloreado = !cerdito.cara.nariz.coloreado;break;
			}
			if(num >= 50){
				cerdito.cuerpo.abdomen.vec[num-50] = !cerdito.cuerpo.abdomen.vec[num-50];
			}
	}

 }



void pick_color(int x, int y) //Modificado segun diapositivas prado
{
GLuint selectBuf[100]={0};
GLint viewport[4], hits=0;
unsigned char pixel[3];

// Declarar buffer de selección
glSelectBuffer(100, selectBuf);
// Obtener los parámetros del viewport
glGetIntegerv(GL_VIEWPORT, viewport);

//Obtener color seleccionado
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);


// Pasar OpenGL a modo selección
glRenderMode (GL_SELECT);
glInitNames();
glPushName(0);

//Fijar la transformación de proyección para la selección
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
gluPickMatrix (x,(viewport[3] - y),10.0, 10.0, viewport);
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);

// Dibujar la escena
draw();
// Pasar OpenGLa modo render
hits = glRenderMode (GL_RENDER);

// Restablecer la transformación de proyección
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);

// Restablecer la transformación de proyección
procesar_color(hits, selectBuf);

// Dibujar la escena para actualizar cambios
draw();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);


}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char **argv)
{


// creación del objeto ply

ply.parametros(argv[1]);


// perfil

vector<_vertex3f> perfil2;
_vertex3f aux;
aux.x=1.0;aux.y=-1.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0;aux.y=-1.1;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=-0.7;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=-0.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=0.5;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=0.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=0.8;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.55;aux.y=1.0;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=1.2;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.3;aux.y=1.4;aux.z=0.0;
perfil2.push_back(aux);
rotacion.parametros(perfil2,6,1);


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 5");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

//funcion de animacion
glutIdleFunc(automatico);

// eventos ratón
glutMouseFunc( clickRaton );
glutMotionFunc( RatonMovido );

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
