// Computação Gráfica - Felipe, Frederiko e Gabriel
#include <GL/glut.h>
#include <math.h>
#include "tgaload.h"

GLfloat ASPECTO, ANGULO;
int x_ini, y_ini, bot, limPortaR = 0, limPortaL = 0, limJanelaR = 0, limJanelaL = 0;
int limBonecoL = 0, limBonecoR = 0, limBonecoU = 0, limBonecoD = 0;
GLfloat obsX, obsY, obsZ, rotX, rotY;
GLfloat obsX_ini, obsY_ini, obsZ_ini, rotX_ini, rotY_ini;
GLfloat escalaX, escalaY, escalaZ;
GLUquadricObj * quadObj = gluNewQuadric();

static double a = 0;
static double bracoE = 0;
static double bracoD = -90;
static double pernaD = 0;
static double pernaE = 0;
static double joelhoD = 0;
static double joelhoE = 0;
int be = 0;
int bd = 0;
int pd = 0;
int pe = 0;
int jd = 0;
int je = 0;

GLfloat viewangle = 0, tippangle = 0, traj[120][3];

GLfloat vetBoneco[3] = {0.1, 0.1, 0.1};
GLfloat vetPorta[3] = {0.1, 0.1, 0.1};
GLfloat vetJanela[3] = {0.1, 0.1, 0.1};
GLfloat vetJanelaZ[3] = {0.1, 0.1, 0.1};

GLfloat  xAngle = 0.0, yAngle = 0.0, zAngle = 0.0, BonecoAngle = 0.0;


#define PI 3.14159265f
#define SENS_ROT 10.0
#define SENS_OBS 10.0
#define SENS_TRANS 10.0
#define ALTURA_PAREDE 15.0f
#define ALTURA_TELHADO 35.0f
#define ALTURA_TOPO_TELHADO 50.0f
#define COMPRIMENTO_GRAMA 180.0f
#define PISCINA_X 30.0f
#define PISCINA_Z 55.0f
#define POSICAO_BULE 80.0f, 6.5f, 20.0f
#define POSICAO_MESA 80.0f, 5.0f, 20.0f
#define TAMANHO_CASA_X 150.0f
#define TAMANHO_CASA_Z 90.0f
#define TAMANHO_GARAGEM_Z 60.0f
#define TAMANHO_JANELA_XY 5.0f

// Qtd máxima de texturas a serem usadas no programa
#define MAX_NO_TEXTURES 50
// vetor com os números das texturas
GLuint texture_id[MAX_NO_TEXTURES];

// Cores
#define COR_BULE 0.690, 0.769, 0.871 // LightSteelBlue
#define COR_GRAMA 0.133, 0.545, 0.133 // ForestGreen
#define COR_PAREDE 1.000, 0.922, 0.804 // BlanchedAlmond
#define COR_PISCINA 0.000, 1.000, 1.000 // BlanchedAlmond
#define COR_PISO 0.961, 0.961, 0.961 // WhiteSmoke
#define COR_TELHADO 0.545, 0.271, 0.075 // SaddleBrown
#define COR_VIDRO 0.878, 1.000, 1.000 // LightCyan
#define COR_JANELA 0.878, 1.000, 1.000,0.5 // Transparent Gray

void iniciaTexturas(void)
{
	// Habilita o uso de textura
	glEnable ( GL_TEXTURE_2D );
	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
	// Define quantas texturas serão usadas no programa
	glGenTextures (MAX_NO_TEXTURES, texture_id);  // Quantidade de texturas, vetor de texturas
	// TEXTURA 0
	texture_id[0] = 1001;
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	image_t temp_image0;
	tgaLoad("texturas/wood_box.tga", &temp_image0, TGA_FREE | TGA_LOW_QUALITY);
	// TEXTURA 1
	texture_id[1] = 1002;
	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
	image_t temp_image1;
	tgaLoad("texturas/grass.tga", &temp_image1, TGA_FREE | TGA_LOW_QUALITY);
	// TEXTURA 2
	texture_id[2] = 1003;
	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
	image_t temp_image2;
	tgaLoad("texturas/white_wall.tga", &temp_image2, TGA_FREE | TGA_LOW_QUALITY);
	// TEXTURA 3
	texture_id[3] = 1004;
	glBindTexture ( GL_TEXTURE_2D, texture_id[3] );
	image_t temp_image3;
	tgaLoad("texturas/glass.tga", &temp_image3, TGA_FREE | TGA_LOW_QUALITY);
	// TEXTURA 4
	texture_id[4] = 1005;
	glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
	image_t temp_image4;
	tgaLoad("texturas/water.tga", &temp_image4, TGA_FREE | TGA_LOW_QUALITY);
	// TEXTURA 5
	texture_id[5] = 1006;
	glBindTexture ( GL_TEXTURE_2D, texture_id[5] );
	image_t temp_image5;
	tgaLoad("texturas/telhado.tga", &temp_image5, TGA_FREE | TGA_LOW_QUALITY);
	//TEXTURA 6
	texture_id[6] = 1007;
	glBindTexture ( GL_TEXTURE_2D, texture_id[6] );
	image_t temp_image6;
	tgaLoad("texturas/wooden_floor.tga", &temp_image6, TGA_FREE | TGA_LOW_QUALITY);
	// TEXTURA 7
	texture_id[7] = 1008;
	glBindTexture ( GL_TEXTURE_2D, texture_id[7] );
	image_t temp_image7;
	tgaLoad("texturas/telhado2.tga", &temp_image7, TGA_FREE | TGA_LOW_QUALITY);

}

void LinhasPlanoCartesiano(void)
{
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 300.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(300.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 300.0);
	glEnd();
	glPopMatrix();
}

void Grama(void)
{
	glBindTexture(GL_TEXTURE_2D, texture_id[1]);
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-30.0, -0.01, -10.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(COMPRIMENTO_GRAMA, -0.01, -10.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(COMPRIMENTO_GRAMA, -0.01, COMPRIMENTO_GRAMA);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-30.0, -0.01, COMPRIMENTO_GRAMA);
	glEnd();

	glPopMatrix();
}
void Boneco(void)
{
	
	glPushMatrix();//Inicia corpo
	glTranslatef(75.0, 12.0, 55.0);
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef (vetBoneco[0], vetBoneco[1], vetBoneco[2]);
	//Pescoço
	glRotatef (BonecoAngle, 0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	//Cabeça
	glPushMatrix();
	glTranslatef(0, 1.0, 0);
	glutSolidSphere(1.0, 5.0, 5.0);
	glPopMatrix();

	//Peito
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1, 1, 5, 5, 5);
	glPopMatrix();

	//Parte superior do braço direito
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glColor3f(0.7, 0.5, 0.5);
	glRotated(-45, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(2.5, 0.0, 0.0);
	glEnd();

	//cotovelo direito
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(2.5, 0.0, 0.0);
	glutSolidSphere(1.0, 5.0, 5.0);
	glPopMatrix();

	//Antebraço superior direito
	//-------------------- 2
	glTranslatef(2.5, 0.0, 0.0);
	glColor3f(0.7, 0.5, 0.5);
	glRotated(-45, 0, 0, 1);
	glRotated(bracoD, 0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(2.5, 0.0, 0.0);
	glEnd();
	//Mão direita
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(4.0, 0.0, 0.0);
	glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadObj, 0.5, 0.5, 4, 5, 2);
	glutSolidSphere(.6, 5.0, 5.0);
	glPopMatrix();

	glPopMatrix();

	//Parte superior do braço esquerdo
	glPushMatrix(); //-------------------- 2
	glTranslatef(0.0, 0.0, 0.0);
	glRotated(45, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-2.5, 0.0, 0.0);
	glEnd();

	//Cotovelo esquerdo
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(-2.5, 0.0, 0.0);
	glutSolidSphere(1.0, 5.0, 5.0);
	glPopMatrix();

	//antebraço

	glTranslatef(-2.5, 0.0, 0.0);
	glRotated(45, 0, 0, 1);
	glRotated(bracoE, 0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-2.5, 0.0, 0.0);
	glEnd();

	//Mão esquerda
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(-4.0, 0.0, 0.0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadObj, 0.5, 0.5, 4, 5, 2);
	glutSolidSphere(.6, 5.0, 5.0);
	glPopMatrix();



	glPopMatrix(); // Fecha

	//Torax
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotated(a, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, -3.75, 0.0);
	glEnd();

	//Cintura





	//Não sei o nome direito
	glPushMatrix();
	glTranslatef(0.0, -3.75, 0.0);
	//glRotated(a,0,0,1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.25, -3.0, 0.0);
	glEnd();

	//Não sei o nome2 direito
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(1.0, -2.0, 0.0);
	glutSolidSphere(1.0, 5.0, 5.0);
	glPopMatrix();

	//Parte superior perna direito

	glTranslatef(1.0, -2.0, 0.0);
	glRotated(pernaD, 1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, -2.5, 0.0);
	glEnd();


	//Joelho direito
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(0.0, -2.5, 0.0);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 0.5, 0.5, 3, 5, 2);
	glPopMatrix();

	//Parte inferior perna direita

	glTranslatef(0.0, -2.5, 0.0);
	glRotated(joelhoD, 1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, -2.5, 0.0);
	glEnd();


	//Calcanhar direito
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(0.0, -2.5, 0.0);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 0.5, 0.5, 3, 5, 2);
	glPopMatrix();

	//pe direito

	glTranslatef(0.0, -2.5, 0.0);
	//glRotated(a,0,0,1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.5);
	glEnd();


	//ponta do pe direito
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(0.0, -0.0, 0.5);
	glutSolidSphere(.8, 5.0, 5.0);
	glPopMatrix();
	glPopMatrix();

	//Não sei o nome esquerdo
	glPushMatrix();
	glTranslatef(0.0, -3.75, 0.0);
	//glRotated(pernaE,0,0,1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-1.25, -3.0, 0.0);
	glEnd();

	//Não sei o nome2 esquerdo
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(-1.0, -2.0, 0.0);
	glutSolidSphere(1.0, 5.0, 5.0);
	glPopMatrix();

	//Parte superior perna Esquerda

	glTranslatef(-1.0, -2.0, 0.0);
	glRotated(pernaE, 1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, -2.5, 0.0);
	glEnd();

	//Joelho Esquerdo
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(0.0, -2.5, 0.0);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 0.5, 0.5, 3, 5, 2);
	glPopMatrix();

	//Parte inferior perna Esquerda

	glTranslatef(0.0, -2.5, 0.0);
	glRotated(joelhoE, 1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, -2.5, 0.0);
	glEnd();


	//Calcanhar Esquerdo
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(0.0, -2.5, 0.0);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 0.5, 0.5, 3, 5, 2);
	glPopMatrix();

	//pe Esquerdo

	glTranslatef(0.0, -2.5, 0.0);
	glRotated(a, 0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.5);
	glEnd();


	//ponta do pe esquerdo
	glPushMatrix();
	glColor3f(0.7, 0.5, 0.5);
	glTranslatef(0.0, 0.0, 0.5);
	glutSolidSphere(.8, 5.0, 5.0);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();//Fecha torso

	glPopMatrix();
}

static void mexeBoneco(void)
{
	//t = glutGet(GLUT_ELAPSED_TIME) / 1000.0; //Tempo randomico
	//a = t*90.0;
	//aqui

	if(bracoD >= -90 && bd == 0)
	{

		bracoD = bracoD - 1.05;
		if(bracoD <= -90)
		{
			bd = 1;
		}
		//cout<<bracoD<<endl<<bd<<endl;

	}
	if(bracoD <= 1 && bd == 1)
	{
		bracoD = bracoD + 1.05;
		if(bracoD >= 0)
		{
			bd = 0;
		}


	}



	if(bracoE <= 90 && be == 0)
	{
		bracoE = bracoE + 1.05;

		if(bracoE >= 90)
		{
			be = 1;
		}

	}

	if(bracoE >= -1 && be == 1)
	{

		bracoE = bracoE - 1.05;
		if(bracoE <= 0)
		{
			be = 0;
		}

	}

	if(pernaD >= -20 && pd == 0)
	{

		pernaD = pernaD - 1.05;
		if(pernaD <= -20)
		{
			pd = 1;
		}


	}

	if(pernaD <= 20 && pd == 1)
	{
		pernaD = pernaD + 1.05;
		if(pernaD >= 20)
		{
			pd = 0;
		}


	}

	if(pernaE <= 20 && pe == 0)
	{
		pernaE = pernaE + 1.05;

		if(pernaE >= 20)
		{
			pe = 1;
		}

	}

	if(pernaE >= -20 && pe == 1)
	{

		pernaE = pernaE - 1.05;
		if(pernaE <= -20)
		{
			pe = 0;
		}
	}


	if(joelhoD >= 0 && jd == 0)
	{

		joelhoD = joelhoD - 1.05;
		if(joelhoD <= 0)
		{
			jd = 1;
		}


	}
	if(joelhoD <= 20 && jd == 1)
	{
		joelhoD = joelhoD + 1.05;
		if(joelhoD >= 20)
		{
			jd = 0;
		}


	}

	if(joelhoE <= 20 && je == 0)
	{

		joelhoE = joelhoE + 1.05;
		if(joelhoE >= 20)
		{
			je = 1;
		}


	}
	if(joelhoE >= 0 && je == 1)
	{
		joelhoE = joelhoE - 1.0;
		if(joelhoE <= 0)
		{
			je = 0;
		}


	}

	//glutPostRedisplay();
}

void Piso(void)
{
	glBindTexture(GL_TEXTURE_2D, texture_id[6]);
	// Piso térreo
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, 0.0, TAMANHO_CASA_Z / 2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 0.0, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, 0.0, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PISO);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, 0.0, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	// Piso andar superior
	glPushMatrix();
	// glColor3f(COR_PISO);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, ALTURA_PAREDE, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, TAMANHO_CASA_Z / 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, ALTURA_PAREDE, TAMANHO_CASA_Z / 2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PISO);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, ALTURA_PAREDE, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_PAREDE, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	// glColor3f(COR_PISO);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_PAREDE, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	// Laje
	glPushMatrix();
	// glColor3f(COR_PISO);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PISO);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	// glColor3f(COR_PISO);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();
}

void Paredes(void)
{

	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	// Parede em X
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, 0.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, ALTURA_TELHADO, 0.0);
	glEnd();
	glPopMatrix();

	// Parede em Z
	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0, ALTURA_TELHADO, TAMANHO_CASA_Z - 60);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, 0.0, TAMANHO_CASA_Z - 60);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 0.0, 60);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO, 60);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, 0.0, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO - 5, TAMANHO_CASA_Z - 60);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO, TAMANHO_CASA_Z - 60);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0, ALTURA_TELHADO, TAMANHO_CASA_Z - 30);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, ALTURA_TELHADO - 5, TAMANHO_CASA_Z - 30);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 0, TAMANHO_CASA_Z - 60);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, (ALTURA_TELHADO / 2) + 5, TAMANHO_CASA_Z - 60);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0, (ALTURA_TELHADO / 2) + 5, TAMANHO_CASA_Z - 30);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, 0, TAMANHO_CASA_Z - 30);
	glEnd();
	glPopMatrix();

	// Parede paralela a X adjacente a Z
	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 10, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 10, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, 0, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 6) - 3, 0, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 6) - 3, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, ALTURA_TELHADO - 25, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 6) + 3, 0.0, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 0, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 10, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 6) + 3, 10, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();

	// Parede paralela a X da porta
	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 2) + 4, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 2) + 4, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 2) - 4, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 2) - 4, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 2) + 4, 12.0, (TAMANHO_CASA_Z / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 2) - 4, 12.0, (TAMANHO_CASA_Z / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 2) - 4, ALTURA_PAREDE, (TAMANHO_CASA_Z / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 2) + 4, ALTURA_PAREDE, (TAMANHO_CASA_Z / 2));
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 2) - 4, ALTURA_TELHADO - 2, (TAMANHO_CASA_Z / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 2) + 4, ALTURA_TELHADO - 2, (TAMANHO_CASA_Z / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 2) + 4, ALTURA_TELHADO, (TAMANHO_CASA_Z / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 2) - 4, ALTURA_TELHADO, (TAMANHO_CASA_Z / 2));
	glEnd();
	glPopMatrix();

	// Parede paralela a X mais externa em relação a Z (Térreo)
	/*
		glPushMatrix();
		glColor3f(COR_TELHADO);
		glBegin(GL_QUADS);
		glVertex3f((TAMANHO_CASA_X * 5 / 6)-3, 0.0, TAMANHO_CASA_Z);
		glVertex3f((TAMANHO_CASA_X * 5 / 6)+3, 0.0, TAMANHO_CASA_Z);
		glVertex3f((TAMANHO_CASA_X * 5 / 6)+3, 10.0, TAMANHO_CASA_Z);
		glVertex3f((TAMANHO_CASA_X * 5 / 6)-3, 10.0, TAMANHO_CASA_Z);
		glEnd();
		glPopMatrix();
	*/

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, 10.0, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 10.0, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_PAREDE, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X * 5 / 6) + 3, 0.0, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 10, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X * 5 / 6) + 3, 10, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, 0.0, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X * 5 / 6) - 3, 0.0, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X * 5 / 6) - 3, 10, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, 10, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();

	// Parede paralela a X mais externa em relação a Z
	glPushMatrix();
	glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X * 2 / 3), ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X - 35, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X - 35, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X * 2 / 3), ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X - 15, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X - 15, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X - 35 , ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X - 15, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X - 15, ALTURA_PAREDE + 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X - 35, ALTURA_PAREDE + 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X - 35 , ALTURA_TELHADO - 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X - 15, ALTURA_TELHADO - 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X - 15, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X - 35, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	// Parede paralela a Z adjacente a X (Térreo)

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, 40);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, 40);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, 50);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, 50);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, 50);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 5, 50);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 5, 40);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 0.0, 40);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 15, 50);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 10, 50);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 10, 40);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 15, 40);
	glEnd();
	glPopMatrix();

	// Parede paralela a Z adjacente a X
	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	// Parede paralela a Z
	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, (TAMANHO_CASA_Z / 2) + 15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 0.0, (TAMANHO_CASA_Z / 2) + 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 0.0, TAMANHO_CASA_Z - 15);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z - 15);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 0.0, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 0.0, TAMANHO_CASA_Z - 30);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 5, TAMANHO_CASA_Z - 30);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 5, TAMANHO_CASA_Z - 15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 0.0, TAMANHO_CASA_Z - 15);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 10, TAMANHO_CASA_Z - 30);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 17, TAMANHO_CASA_Z - 30);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 17, TAMANHO_CASA_Z - 15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 10, TAMANHO_CASA_Z - 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 29, TAMANHO_CASA_Z - 30);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z - 30);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z - 15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 29, TAMANHO_CASA_Z - 15);
	glEnd();
	glPopMatrix();


	// Parede paralela a Z (Térreo)
	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, 0.0, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_PAREDE, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_PAREDE, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, 0.0, TAMANHO_CASA_Z);
	glEnd();
	glPopMatrix();

	// Parede paralela a Z
	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_PAREDE, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	// Pilastras

	glPushMatrix();
	// glColor3f(1.0f,1.0f,1.0f);
	glTranslatef((TAMANHO_CASA_X * 2 / 3) + 2.0, ALTURA_PAREDE, TAMANHO_CASA_Z + (TAMANHO_GARAGEM_Z / 3));
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);

	// glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glTranslatef(TAMANHO_CASA_X - 2, ALTURA_PAREDE, TAMANHO_CASA_Z + (TAMANHO_GARAGEM_Z / 3));
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	// glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glTranslatef((TAMANHO_CASA_X * 2 / 3) + 2.0, ALTURA_PAREDE, TAMANHO_CASA_Z + (TAMANHO_GARAGEM_Z * 2 / 3));
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	// glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glTranslatef(TAMANHO_CASA_X - 2, ALTURA_PAREDE, TAMANHO_CASA_Z + (TAMANHO_GARAGEM_Z * 2 / 3));
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	// glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glTranslatef((TAMANHO_CASA_X * 2 / 3) + 2.0, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	// glEnd();
	glPopMatrix();

	glPushMatrix();
	// glColor3f(COR_PAREDE);
	glTranslatef(TAMANHO_CASA_X - 2, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	// glEnd();
	glPopMatrix();
}

void Janelas(void)
{
	glBindTexture(GL_TEXTURE_2D, texture_id[3]);
	glPushMatrix();
	glColor4f(COR_JANELA);
	glTranslatef (vetJanela[0], vetJanela[1], vetJanela[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 2) - 4, ALTURA_PAREDE, (TAMANHO_CASA_Z / 2));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 2) + 4, ALTURA_PAREDE, (TAMANHO_CASA_Z / 2));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 2) + 4, ALTURA_TELHADO - 2, (TAMANHO_CASA_Z / 2));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 2) - 4, ALTURA_TELHADO - 2, (TAMANHO_CASA_Z / 2));
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture_id[3]);
	glPushMatrix();
	glColor4f(COR_JANELA);
	glTranslatef (vetJanelaZ[0], vetJanelaZ[1], vetJanelaZ[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 29, TAMANHO_CASA_Z - 30);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 17, TAMANHO_CASA_Z - 30);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 17, TAMANHO_CASA_Z - 15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 29, TAMANHO_CASA_Z - 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4f(COR_JANELA);
	glTranslatef (vetJanelaZ[0], vetJanelaZ[1], vetJanelaZ[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 10, TAMANHO_CASA_Z - 30);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 5, TAMANHO_CASA_Z - 30);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 5, TAMANHO_CASA_Z - 15);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, 10, TAMANHO_CASA_Z - 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4f(COR_JANELA);
	glTranslatef (vetJanelaZ[0], vetJanelaZ[1], vetJanelaZ[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 5, 40);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, 10, 40);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 10, 50);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, 5, 50);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4f(COR_JANELA);
	glTranslatef (vetJanela[0], vetJanela[1], vetJanela[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X - 35 , ALTURA_TELHADO - 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X - 15, ALTURA_TELHADO - 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X - 15, ALTURA_PAREDE + 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X - 35, ALTURA_PAREDE + 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor4f(COR_JANELA);

	//glTranslatef (vetJanelaZ[0], vetJanelaZ[1], vetJanelaZ[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, (ALTURA_TELHADO / 2) + 5, TAMANHO_CASA_Z - 60);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO - 5, TAMANHO_CASA_Z - 60);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.0, ALTURA_TELHADO - 5, TAMANHO_CASA_Z - 30);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, (ALTURA_TELHADO / 2) + 5, TAMANHO_CASA_Z - 30);
	glEnd();
	glPopMatrix();

}

void Portas(void)
{
	/* Porta Principal*/

	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	glPushMatrix ();
	// glColor3f(COR_TELHADO);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTranslatef ((TAMANHO_CASA_X / 2) - 4, 0.0, (TAMANHO_CASA_Z / 2) + 0.1);
	//se quiser rotacionar em torno do eixo
	glRotatef (yAngle, 0, 1, 0);

	glTranslatef (-((TAMANHO_CASA_X / 2) - 4), -0.0, -((TAMANHO_CASA_Z / 2) + 0.1));


	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 2) - 4, 0.0, (TAMANHO_CASA_Z / 2) + 0.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 2) + 4, 0.0, (TAMANHO_CASA_Z / 2) + 0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 2) + 4, 12.0, (TAMANHO_CASA_Z / 2) + 0.1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 2) - 4, 12.0, (TAMANHO_CASA_Z / 2) + 0.1);
	glEnd();
	glPopMatrix();

	// Porta da Garagem
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef ((TAMANHO_CASA_X / 6) - 3, 0.0, TAMANHO_CASA_Z + 0.1);
	glRotatef (yAngle, 0, 1, 0);
	glTranslatef (-((TAMANHO_CASA_X / 6) - 3), -0.0, -(TAMANHO_CASA_Z + 0.1));
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 6) - 3, 0.0, TAMANHO_CASA_Z + 0.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X / 6) + 3, 0.0, TAMANHO_CASA_Z + 0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 6) + 3, 10.0, TAMANHO_CASA_Z + 0.1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X / 6) - 3, 10.0, TAMANHO_CASA_Z + 0.1);
	glEnd();
	glPopMatrix();

	// Porta da Piscina
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef ((TAMANHO_CASA_X * 5 / 6) - 3, 0.0, TAMANHO_CASA_Z + 0.1);
	glRotatef (yAngle, 0, 1, 0);
	glTranslatef (-((TAMANHO_CASA_X * 5 / 6) - 3), -0.0, -(TAMANHO_CASA_Z + 0.1));
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X * 5 / 6) - 3, 0.0, TAMANHO_CASA_Z + 0.1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X * 5 / 6) + 3, 0.0, TAMANHO_CASA_Z + 0.1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X * 5 / 6) + 3, 10.0, TAMANHO_CASA_Z + 0.1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((TAMANHO_CASA_X * 5 / 6) - 3, 10.0, TAMANHO_CASA_Z + 0.1);
	glEnd();
	glPopMatrix();
}

void Garagem(void)
{
	// Pilastras
	glPushMatrix();
	glColor3f(COR_PAREDE);
	glTranslatef(2.0, ALTURA_PAREDE, TAMANHO_CASA_Z + (TAMANHO_GARAGEM_Z / 3));
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(COR_PAREDE);
	glTranslatef((TAMANHO_CASA_X / 3) - 2, ALTURA_PAREDE, TAMANHO_CASA_Z + (TAMANHO_GARAGEM_Z / 3));
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	glEnd();

	glPopMatrix();
	glPushMatrix();
	glColor3f(COR_PAREDE);
	glTranslatef(2.0, ALTURA_PAREDE, TAMANHO_CASA_Z + (TAMANHO_GARAGEM_Z * 2 / 3));
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(COR_PAREDE);
	glTranslatef((TAMANHO_CASA_X / 3) - 2, ALTURA_PAREDE, TAMANHO_CASA_Z + (TAMANHO_GARAGEM_Z * 2 / 3));
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glPushMatrix();
	glColor3f(COR_PAREDE);
	glTranslatef(2.0, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(COR_PAREDE);
	glTranslatef((TAMANHO_CASA_X / 3) - 2, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 1.5, 1.5, ALTURA_PAREDE, 10, 10);
	glEnd();
	glPopMatrix();
}

void Telhado(void)
{
	// Início Garagem
	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_PAREDE + 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, ALTURA_PAREDE, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_PAREDE + 5, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_PAREDE + 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_PAREDE + 5, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_PAREDE, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_PAREDE, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_PAREDE + 5, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z);
	glEnd();
	glPopMatrix();
	// Fim Garagem
	glBindTexture(GL_TEXTURE_2D, texture_id[7]);
	// Triângulo Adjacente a Z
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z * 3 / 4);
	glEnd();
	glPopMatrix();

	// Triângulo mais externo a Z
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 5 / 6, ALTURA_TOPO_TELHADO, (TAMANHO_CASA_Z * 3 / 4) + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z * 3 / 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z / 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z / 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z * 3 / 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0, ALTURA_TELHADO, 0.0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, 0.0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 5 / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z / 4);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z / 4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z / 4);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 5 / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z / 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X / 3, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_TELHADO, TAMANHO_CASA_Z / 2);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 5 / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z / 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 5 / 6, ALTURA_TOPO_TELHADO, (TAMANHO_CASA_Z * 3 / 4) + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X * 2 / 3, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 5 / 6, ALTURA_TOPO_TELHADO, (TAMANHO_CASA_Z * 3 / 4) + TAMANHO_GARAGEM_Z + 5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(TAMANHO_CASA_X * 5 / 6, ALTURA_TOPO_TELHADO, TAMANHO_CASA_Z / 4);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, 0.0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X, ALTURA_TELHADO, TAMANHO_CASA_Z + TAMANHO_GARAGEM_Z + 5);
	glEnd();
	glPopMatrix();
}

void Piscina(void)
{
	glBindTexture(GL_TEXTURE_2D, texture_id[4]);
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X * 2 / 3) + 10, 0.1, TAMANHO_CASA_Z + 10);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((TAMANHO_CASA_X * 2 / 3) + 10, 0.1, TAMANHO_CASA_Z + PISCINA_Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X - 10, 0.1, TAMANHO_CASA_Z + PISCINA_Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(TAMANHO_CASA_X - 10, 0.1, TAMANHO_CASA_Z + 10);
	glEnd();
	glPopMatrix();
}

void Bule(void)
{
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(POSICAO_BULE);
	glutSolidTeapot(2.0f);
	glEnd();
	glPopMatrix();
}

void Mesa(void)
{
	glPushMatrix();
	glTranslatef(POSICAO_MESA);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(COR_VIDRO);
	glVertex2f(0.0f, 0.0f);
	int numSegments = 100;
	GLfloat angulo;
	GLfloat raio = 4.0f;
	for (int i = 0; i <= numSegments; i++)
	{
		angulo = i * 2.0f * PI / numSegments;
		glVertex2f(cos(angulo) * raio, sin(angulo) * raio);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(COR_TELHADO);
	glTranslatef(POSICAO_MESA);
	glRotatef(90.0, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadObj, 2, 2, 5, 10, 5);
	glEnd();
	glPopMatrix();
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT);

	// Linhas de referência do plano cartesiano
	// LinhasPlanoCartesiano();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Casa em formato de U

	Piso();
	Paredes();
	Garagem();
	Telhado();
	Bule();
	Mesa();
	Janelas();
	Portas();
	Grama();
	Piscina();
	Boneco();

	glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat luzAmbiente[4] = {0.5, 0.5, 0.5, 1.0};
	GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0};		 // "cor"
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
	GLfloat posicaoLuz[4] = {0.0, 0.0, 10.0, 0.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
	GLint especMaterial = 0;

	// Especifica que a cor de fundo da janela não será preta
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearColor(0.529f, 0.808f, 0.922f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	ANGULO = 45;
	rotX = rotY = 0;
	obsX = obsY = 0;
	obsZ = 10;
	escalaX = escalaY = escalaZ = 1;

}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)   //equivalente ao posiciona observador
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	//gluPerspective(angle,fAspect,0.4,500);
	gluPerspective(ANGULO, ASPECTO, 0.4, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	//gluLookAt(200, 80, 150, 0, 0, 0, 0, 1, 0);
	gluLookAt(obsX, obsY, obsZ, 0, 0, 0, 0, 1, 0);
	glTranslatef(-obsX, -obsY, -obsZ);/*Translada a câmera para essas variáveis*/
	glRotatef(rotX, 1, 0, 0); /*Rotacionar a câmera para essas coordenadas*/
	glRotatef(rotY, 0, 1, 0);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	//fAspect = (GLfloat)w/(GLfloat)h;
	ASPECTO = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int botao, int estado, int x, int y)
{
	if(estado == GLUT_DOWN)
	{
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = botao;
	}
	else
		bot = -1;
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
		//	abre a porta
	case 'r' :

		if(yAngle <= 90)
		{
			yAngle += 2;
		}
		break;

		//	fecha a porta
	case 't' :
		if(yAngle >= 0)
		{
			yAngle -= 2;
		}
		break;

		// JANELAS
	case 'f' :
		if(limJanelaL == 0 && limJanelaR == 0)
		{
			limJanelaL = vetJanela[0];
			limJanelaR = vetJanela[0] + 7;
			vetJanela[2] -= 0.3; //efeito profundidade
			vetJanelaZ[0] -= 0.3;
		}

		if(vetJanela[0] <= limJanelaR && vetJanela[0] >= limJanelaL)
		{
			vetJanela[0] += 0.2;
			vetJanelaZ[2] += 0.2;
		}
		break;


		//	fecha a porta - deslizar para esquerda
	case 'g' :
		if(vetJanela[0] > limJanelaL + 0.1)
		{
			vetJanela[0] -= 0.2;
			vetJanelaZ[2] -= 0.2;
		}
		break;

	case 'w':
		mexeBoneco();
		vetBoneco[2] += 0.2;
		break;
	case 's':
		mexeBoneco();
		vetBoneco[2] -= 0.2;
		break;
	case 'a':
		mexeBoneco();
		vetBoneco[0] -= 0.2;
		break;
	case 'd':
		mexeBoneco();
		vetBoneco[0] += 0.2;
		break;
	case 'x':
		BonecoAngle += 2;
		break;
	case 'z':
		BonecoAngle -= 2;
		break;
	}
	glutPostRedisplay();
}



void motion(int x, int y)
{
	if(bot == GLUT_LEFT_BUTTON)   //Rotação
	{
		int deltaX = x_ini - x;
		int deltaY = y_ini - y;
		rotX = rotX_ini - deltaY / SENS_ROT;
		rotY = rotY_ini - deltaX / SENS_ROT;
	}
	else if (bot == GLUT_RIGHT_BUTTON)     //Zoom
	{
		int deltaZ = y_ini - y;
		obsZ = obsZ_ini + deltaZ / SENS_OBS;
	}
	else if (bot == GLUT_MIDDLE_BUTTON)     //Correr
	{
		int deltaX = x_ini - x;
		int deltaY = y_ini - y;
		obsX = obsX_ini + deltaX / SENS_TRANS;
		obsY = obsY_ini + deltaY / SENS_TRANS;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Programa Principal
int main(int argc, char * * argv)
{
	glutInit( & argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1080, 640);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Casa em U - pressione 'R' e 'T' (portas) ou 'F' e 'G' (janelas) e WASD anda e XY rotaciona (Boneco)");
	iniciaTexturas();
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(key);
	Inicializa();
	glutMainLoop();
}

