//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Includes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define SIZE 5
#define WAITTIME 750

using namespace std;

char texto[30];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Declaracoes memoria
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int valores_sorteados[25];
int usuario[25];
int user;
int posMaxLida;
int poslida;
int valor_rand;
int view_w, view_h;
int clickquad;
int win = 600;
float xf = 20, yf = 20;
float r1, g1, b1;
float r2, g2, b2;
float r3, g3, b3;
float r4, g4, b4;
float r5, g5, b5;
float r6, g6, b6;
float r7, g7, b7;
float r8, g8, b8;
float r9, g9, b9;
bool clicou = false;
bool animation = true;
bool aceso = true;  
bool modo2x2 = true;
void gerencia_mouse(int button, int state, int x, int y);
void acende_quadrado_sorteado_3x3();
void acende_quadrado_sorteado_2x2();
void mostra_sequencia_sorteados_3x3();
void mostra_sequencia_sorteados_2x2();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Desenha texto na tela
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DesenhaTexto(char *string) {
    glPushMatrix();      
    glRasterPos2f(-win/5,0);
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
    glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Reseta variaveis memoria
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void reseta() {
    posMaxLida = 0;
    poslida = 0;
    aceso = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Comeca memoria tres por tres
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Comeca memoria dois por dois
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DISPLAY_SEQUENCIA(int);
void desenha_quad_sequencia();
void desenha_quad_usuario();
void sorteiaQuadrados(int);
void desenha_quadrados_3x3(int);
void desenha_quadrados_2x2(int);
void PRE_MOSTRAR_SEQUENCIA(int);

void dois_por_dois() {
    reseta();
    modo2x2 = true;
    sorteiaQuadrados(4);
    desenha_quadrados_2x2(-1);
    glutTimerFunc(WAITTIME,PRE_MOSTRAR_SEQUENCIA,0);
}

void tres_por_tres() {
    reseta();
    modo2x2 = false;
    sorteiaQuadrados(9);
    desenha_quadrados_3x3(-1);
    glutTimerFunc(WAITTIME,PRE_MOSTRAR_SEQUENCIA,0);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Tela branca
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tela_branca() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Tela de gameover
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tela_gameover() {
    sprintf(texto, "GameOver");
    glColor3f(0.0f, 0.0f, 0.0f);
    DesenhaTexto(texto);
    glFlush();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Tela de venceu
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tela_venceu() {
    sprintf(texto, "Ganhou");
    glColor3f(0.0f, 0.0f, 0.0f);
    DesenhaTexto(texto);
    glFlush();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Tela de go
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tela_go() {
    sprintf(texto, "GO!!!!!!");
    glColor3f(0.0f, 0.0f, 0.0f);
    DesenhaTexto(texto);
    glFlush();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Verifica quadrado clicado na tela e depois confere se este esta de acordo com a sequencia ja sorteada
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gerencia_mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if(clicou) {
            if(state == GLUT_UP) {
                if(valores_sorteados[poslida] != user) {
                    glutDisplayFunc(tela_gameover);
                    glutMouseFunc(NULL);
                } else if(poslida == SIZE-1) {
                    glutDisplayFunc(tela_venceu);
                } else if(poslida < posMaxLida) {
                    poslida++;
                } else {
                    posMaxLida++;
                    glutTimerFunc(100,PRE_MOSTRAR_SEQUENCIA,0);
                }
                clicou = false;
            }
        } 

        if (state == GLUT_DOWN) {
            clicou = true;
            aceso = true;

            //Obtem valores em relação a resolução da tela
            if(modo2x2) {
                clickquad = 2*(y/(win/2))+x/(win/2);
            } else {
                clickquad = 3*(y/(win/3))+x/(win/3);    
            }
            user = clickquad;           

        } else if(state == GLUT_UP) {
            aceso = false;
        }
    }
    glutPostRedisplay();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Animação Mostrar Sequencia
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PRE_MOSTRAR_SEQUENCIA(int val) {
    glutMouseFunc(NULL);
    poslida = 0;
    animation = true;
    glutDisplayFunc(desenha_quad_sequencia);
    glutTimerFunc(WAITTIME,DISPLAY_SEQUENCIA,1);
}

void PLAYING(int val) {
    glutDisplayFunc(desenha_quad_usuario);
    glutPostRedisplay();
    poslida = 0;
    glutMouseFunc(gerencia_mouse);
}

void GO(int val) {
    if(val) {
        aceso = false;
        glutTimerFunc(WAITTIME/2,GO,0);
    } else {
        glutDisplayFunc(tela_go);
        glutTimerFunc(WAITTIME,PLAYING,0);
    }
    glutPostRedisplay();
}

void DISPLAY_SEQUENCIA(int val) {
    if(animation) {
        glutTimerFunc(WAITTIME,DISPLAY_SEQUENCIA,!val);
        if(val) {
            aceso = true;
        } else {
            aceso = false;
            poslida++;
        }
        if(poslida>posMaxLida) {
            animation = false;
            glutTimerFunc(WAITTIME,GO,1);
        }
        glutPostRedisplay();
    }
}

void desenha_quad_sequencia() {
    if(aceso) {
        if(modo2x2)
            desenha_quadrados_2x2(valores_sorteados[poslida]);
        else
            desenha_quadrados_3x3(valores_sorteados[poslida]);
    } else {
        if(modo2x2)
            desenha_quadrados_2x2(-1);
        else
            desenha_quadrados_3x3(-1);
    }
}

void desenha_quad_usuario() {
    if(aceso) {
        if(modo2x2)
            desenha_quadrados_2x2(user);
        else
            desenha_quadrados_3x3(user);
    } else {
        if(modo2x2)
            desenha_quadrados_2x2(-1);
        else
            desenha_quadrados_3x3(-1);
    }
}

void sorteiaQuadrados(int val) {
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++) {
        valores_sorteados[i] = rand()%val;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Renderiza quadrados apagados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void desenha_quadrados_2x2(int quad) {

    glBegin(GL_QUADS); //primeiro
    glColor3f(0.7, 0.0, 0.0);
    glVertex2f(-win, 0); // x, y
    glVertex2f(-win, win);
    glVertex2f(0, win);
    glVertex2f(0, 0);
    glEnd();

    glBegin(GL_QUADS); //segundo
    glColor3f(0.0, 0.7, 0.0);
    glVertex2f(0, 0); // x, y
    glVertex2f(0, win);
    glVertex2f(win, win);
    glVertex2f(win, 0);
    glEnd();

    glBegin(GL_QUADS); //terceiro
    glColor3f(0.0, 0.0, 0.7);
    glVertex2f(-win, -win); // x, y
    glVertex2f(-win, 0);
    glVertex2f(0, 0);
    glVertex2f(0, -win);
    glEnd();

    glBegin(GL_QUADS); //quarto
    glColor3f(0.7, 0.7, 0.0);
    glVertex2f(0, -win); // x, y
    glVertex2f(0, 0);
    glVertex2f(win, 0);
    glVertex2f(win, -win);
    glEnd();

    //Paleta de cores
    r1 = 1.0, g1 = 0.0, b1 = 0.0;
    r2 = 0.0, g2 = 1.0, b2 = 0.0;
    r3 = 0.0, g3 = 0.0, b3 = 1.0;
    r4 = 1.0, g4 = 1.0, b4 = 0.0;

    switch (quad) {
        case -1:
            break;
        case 0:
            glBegin(GL_QUADS); //primeiro
            glColor3f(r1, g1, b1);
            glVertex2f(-win, 0); // x, y
            glVertex2f(-win, win);
            glVertex2f(0, win);
            glVertex2f(0, 0);
            glEnd();
            break;
        case 1:  
            glBegin(GL_QUADS); //segundo
            glColor3f(r2, g2, b2);
            glVertex2f(0, 0); // x, y
            glVertex2f(0, win);
            glVertex2f(win, win);
            glVertex2f(win, 0);
            glEnd();
            break;
        case 2:
            glBegin(GL_QUADS); //terceiro
            glColor3f(r3, g3, b3);
            glVertex2f(-win, -win); // x, y
            glVertex2f(-win, 0);
            glVertex2f(0, 0);
            glVertex2f(0, -win);
            glEnd();
            break;
        case 3:
            glBegin(GL_QUADS); //quarto
            glColor3f(r4, g4, b4);
            glVertex2f(0, -win); // x, y
            glVertex2f(0, 0);
            glVertex2f(win, 0);
            glVertex2f(win, -win);
            glEnd();
            break;
    }

    glFlush();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Renderiza quadrados apagados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void renderiza_quadrados_apagados_3x3() {
    glBegin(GL_QUADS); //primeiro
    glColor3f(0.7, 0.0, 0.0);
    glVertex2f(-win, win / 3); // x, y
    glVertex2f(-win, win);
    glVertex2f(-win / 3, win);
    glVertex2f(-win / 3, win / 3);
    glEnd();

    glBegin(GL_QUADS); //segundo
    glColor3f(0.0, 0.7, 0.0);
    glVertex2f(-win / 3, win / 3); // x, y
    glVertex2f(-win / 3, win);
    glVertex2f(win / 3, win);
    glVertex2f(win / 3, win / 3);
    glEnd();

    glBegin(GL_QUADS); //terceiro
    glColor3f(0.0, 0.0, 0.7);
    glVertex2f(win / 3, win / 3); // x, y
    glVertex2f(win / 3, win);
    glVertex2f(win, win);
    glVertex2f(win, win / 3);
    glEnd();

    glBegin(GL_QUADS); //quarto
    glColor3f(0.7, 0.7, 0.0);
    glVertex2f(-win, -win / 3); // x, y
    glVertex2f(-win, win / 3);
    glVertex2f(-win / 3, win / 3);
    glVertex2f(-win / 3, -win / 3);
    glEnd();


    glBegin(GL_QUADS); //quinto
    glColor3f(0.7, 0.7, 0.7);
    glVertex2f(-win / 3, -win / 3); // x, y
    glVertex2f(-win / 3, win / 3);
    glVertex2f(win / 3, win / 3);
    glVertex2f(win / 3, -win / 3);
    glEnd();

    glBegin(GL_QUADS); //sexto
    glColor3f(0.0, 0.7, 0.7);
    glVertex2f(win / 3, -win / 3); // x, y
    glVertex2f(win / 3, win / 3);
    glVertex2f(win, win / 3);
    glVertex2f(win, -win / 3);
    glEnd();


    glBegin(GL_QUADS); //setimo
    glColor3f(0.7, 0.5, 0.5);
    glVertex2f(-win, -win); // x, y
    glVertex2f(-win, -win / 3);
    glVertex2f(-win / 3, -win / 3);
    glVertex2f(-win / 3, -win);
    glEnd();


    glBegin(GL_QUADS); //oitavo
    glColor3f(0.0, 0.7, 0.5);
    glVertex2f(-win / 3, -win); // x, y
    glVertex2f(-win / 3, -win / 3);
    glVertex2f(win / 3, -win / 3);
    glVertex2f(win / 3, -win);
    glEnd();

    glBegin(GL_QUADS); //nono
    glColor3f(0.2, 0.5, 0.7);
    glVertex2f(win / 3, -win); // x, y
    glVertex2f(win / 3, -win / 3);
    glVertex2f(win, -win / 3);
    glVertex2f(win, -win);
    glEnd();

    glFlush();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Vai acendendo os quadrados ja sorteados na sequencia salva no array
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void desenha_quadrados_3x3(int quad) {
    renderiza_quadrados_apagados_3x3();

    //Paleta de cores
    r1 = 1.0, g1 = 0.0, b1 = 0.0;
    r2 = 0.0, g2 = 1.0, b2 = 0.0;
    r3 = 0.0, g3 = 0.0, b3 = 1.0;
    r4 = 1.0, g4 = 1.0, b4 = 0.0;
    r5 = 0.9, g5 = 0.8, b5 = 0.8;
    r6 = 0.0, g6 = 1.0, b6 = 1.0;
    r7 = 1.0, g7 = 0.7, b7 = 0.7;
    r8 = 0.0, g8 = 1.0, b8 = 0.7;
    r9 = 0.5, g9 = 0.7, b9 = 1.0;

    switch (quad) {
        case -1:
            break;
        case 0:
            glBegin(GL_QUADS); //primeiro
            glColor3f(r1, g1, b1);
            glVertex2f(-win, win / 3); // x, y
            glVertex2f(-win, win);
            glVertex2f(-win / 3, win);
            glVertex2f(-win / 3, win / 3);
            glEnd();
            glFlush();
            break;
        case 1:
            glBegin(GL_QUADS); //segundo
            glColor3f(r2, g2, b2);
            glVertex2f(-win / 3, win / 3); // x, y
            glVertex2f(-win / 3, win);
            glVertex2f(win / 3, win);
            glVertex2f(win / 3, win / 3);
            glEnd();
            glFlush();
            break;
        case 2:
            glBegin(GL_QUADS); //terceiro
            glColor3f(r3, g3, b3);
            glVertex2f(win / 3, win / 3); // x, y
            glVertex2f(win / 3, win);
            glVertex2f(win, win);
            glVertex2f(win, win / 3);
            glEnd();
            glFlush();
            break;
        case 3:
            glBegin(GL_QUADS); //quarto
            glColor3f(r4, g4, b4);
            glVertex2f(-win, -win / 3); // x, y
            glVertex2f(-win, win / 3);
            glVertex2f(-win / 3, win / 3);
            glVertex2f(-win / 3, -win / 3);
            glEnd();
            glFlush();
            break;
        case 4:
            glBegin(GL_QUADS); //quinto
            glColor3f(r5, g5, b5);
            glVertex2f(-win / 3, -win / 3); // x, y
            glVertex2f(-win / 3, win / 3);
            glVertex2f(win / 3, win / 3);
            glVertex2f(win / 3, -win / 3);
            glEnd();
            glFlush();
            break;
        case 5:
            glBegin(GL_QUADS); //sexto
            glColor3f(r6, g6, b6);
            glVertex2f(win / 3, -win / 3); // x, y
            glVertex2f(win / 3, win / 3);
            glVertex2f(win, win / 3);
            glVertex2f(win, -win / 3);
            glEnd();
            glFlush();
            break;
        case 6:
            glBegin(GL_QUADS); //setimo
            glColor3f(r7, g7, b7);
            glVertex2f(-win, -win); // x, y
            glVertex2f(-win, -win / 3);
            glVertex2f(-win / 3, -win / 3);
            glVertex2f(-win / 3, -win);
            glEnd();
            glFlush();
            break;
        case 7:
            glBegin(GL_QUADS); //oitavo
            glColor3f(r8, g8, b8);
            glVertex2f(-win / 3, -win); // x, y
            glVertex2f(-win / 3, -win / 3);
            glVertex2f(win / 3, -win / 3);
            glVertex2f(win / 3, -win);
            glEnd();
            glFlush();
            break;
        case 8:
            glBegin(GL_QUADS); //novo
            glColor3f(r9, g9, b9);
            glVertex2f(win / 3, -win); // x, y
            glVertex2f(win / 3, -win / 3);
            glVertex2f(win, -win / 3);
            glVertex2f(win, -win);
            glEnd();
            glFlush();
            break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Chamada pela GLUT quando a janela é redimensionada
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void redimensionamento(GLsizei w, GLsizei h) {
    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;

    // Inicializa sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece volume de visualização
    // (esquerda, direita, inferior, superior)
    gluOrtho2D(-win, win, -win, win);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuMemoria(int op) {
    switch (op) {
        case 0:
            dois_por_dois();
            break;
        case 1:
            tres_por_tres();
            break;
    }
}
/*
void MenuBatalhaNaval(int op) {
    switch (op) {
        case 0:
            batalha_naval_normal();
            break;
    }
}
*/
void MenuPrincipal(int op) {
    switch (op) {
        case 1:
            exit(0);
            break;
    }
}

void CriaMenu() {
    int menu, submenu1, submenu2;

    submenu1 = glutCreateMenu(MenuMemoria);
    glutAddMenuEntry("2x2 Facil", 0);
    glutAddMenuEntry("3x3 Dificil", 1);
/*
    submenu2 = glutCreateMenu(MenuBatalhaNaval);
    glutAddMenuEntry("Normal", 0);
*/
    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Memoria", submenu1);
  //  glutAddSubMenu("Batalha Naval", submenu2);
    glutAddMenuEntry("Sair", 1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Programa Principal
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Primeiro Trabalho CG");
    glutDisplayFunc(tela_branca);
    glutReshapeFunc(redimensionamento);
    //glutMouseFunc(pos_mouse);
    CriaMenu();
    glutMainLoop();
    return 0;
}

