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
int quantidade_sorteada = -1;
int mouse_clicado = -1;
int valor_rand;
int view_w, view_h;
int clickquad;
int win = 600;
float xf = 20, yf = 20;//, win = 600;
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
bool aguarda = false;
bool sequencia_correta = true;
bool mouse_clicado_primeiro_quad = false;
bool mouse_clicado_terceiro_quad = false;
bool mouse_clicado_segundo_quad = false;
bool mouse_clicado_quarto_quad = false;
bool mouse_clicado_quinto_quad = false;
bool mouse_clicado_sexto_quad = false;
bool mouse_clicado_setimo_quad = false;
bool mouse_clicado_oitavo_quad = false;
bool mouse_clicado_nono_quad = false;
bool ja_foi_sorteado_algum_valor = false;
void gerencia_mouse_3x3(int button, int state, int x, int y);
void gerencia_mouse_2x2(int button, int state, int x, int y);
void acende_quadrado_sorteado_3x3();
void acende_quadrado_sorteado_2x2();
void mostra_sequencia_sorteados_3x3();
void mostra_sequencia_sorteados_2x2();
void comeca_renderizacao_3x3();
void comeca_renderizacao_2x2();
double TIMER = 2.3;


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
    //quantidade_sorteada = -1;
    posMaxLida = 0;
    poslida = 0;
    mouse_clicado = -1;
    aceso = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Comeca memoria tres por tres
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tres_por_tres() {
    reseta();
    glutDisplayFunc(comeca_renderizacao_3x3);
    glutMouseFunc(gerencia_mouse_3x3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Comeca memoria dois por dois
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void logica2(int);
void desenha_quad();
void desenha_quad_usuario();
void sorteiaQuadrados();
void PRE_MOSTRAR_SEQUENCIA(int);
void renderiza_quadrados_apagados_2x2();
//void logica();
void dois_por_dois() {
    reseta();
    sorteiaQuadrados();
    //mostra_sequencia_sorteados_2x2();
    //logica();
    //glutDisplayFunc(desenha_quad);
    renderiza_quadrados_apagados_2x2();
    glutTimerFunc(WAITTIME,PRE_MOSTRAR_SEQUENCIA,0);
    //glutDisplayFunc(comeca_renderizacao_2x2);
    //glutMouseFunc(gerencia_mouse_2x2);
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
//Renderiza quadrados apagados
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void renderiza_quadrados_apagados_2x2() {
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
    glFlush();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Inicia renderizacao e verificacoes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void comeca_renderizacao_2x2(void) {
    if (aguarda == false) {
        if (sequencia_correta) { //Se o usuario fez a sequencia certa, faz mais uma rodada
            TIMER = TIMER - 0.05; //A cada rodada a sequencia aparece mais rapida
            sequencia_correta = false; //Nova rodada, reseta contadores
            mouse_clicado = -1; //Nova rodada, reseta contadores

            renderiza_quadrados_apagados_2x2();
            mostra_sequencia_sorteados_2x2();
            sleep(TIMER);
            acende_quadrado_sorteado_2x2();
            sleep(TIMER);
            renderiza_quadrados_apagados_2x2();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Verifica quadrado clicado na tela e depois confere se este esta de acordo com a sequencia ja sorteada
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pos_mouse(int button, int state, int x, int y) {
    cout << x << " " <<  y << endl;
    cout << y/(win/2) << x/(win/2);
    clickquad = 2*(y/(win/2))+x/(win/2);
    cout << clickquad << endl;
}

void gerencia_mouse_2x2(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if(clicou) {
            if(state == GLUT_UP) {
                cout << "posMax" << posMaxLida << endl;
                cout << "sort" << valores_sorteados[poslida];
                //cout << "user" << usuario[poslida] << "sort" << valores_sorteados[poslida];
                //cout << "user" << usuario[poslida+1] << "sort" << valores_sorteados[poslida+1];
                if(valores_sorteados[poslida] != user) {
                    glutDisplayFunc(tela_gameover);
                    glutMouseFunc(NULL);
                } else if(poslida == SIZE-1) {
                    glutDisplayFunc(tela_venceu);
                } else if(poslida < posMaxLida) {
                    poslida++;
                } else {
                    cout << "passou" << endl;
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
            clickquad = 2*(y/(win/2))+x/(win/2);
            /*xf = ((2 * win * x) / view_w) - win;
            yf = (((2 * win) * (view_h - y)) / view_h) - win;

            //Verifica em qual parte da tela se encontra determinado quadrado
            if (xf < 0)
                if (yf > 0) {
                    //mouse_clicado_primeiro_quad = true;
                    clickquad = 0;
                } else if (yf < 0) {
                    //mouse_clicado_terceiro_quad = true;
                    clickquad = 2;
                }

            if (xf > 0)
                if (yf > 0) {
                    mouse_clicado_segundo_quad = true;
                } else if (yf < 0) {
                    mouse_clicado_quarto_quad = true;
                }
            */
            //Contador de cliques do mouse
            //usuario[poslida] = clickquad;
            user = clickquad;
            //poslida++;
            cout << "quad" << clickquad;
            /*
            //Guarda sequencia em array em relacao ao que o usuario clicou na tela
            if (mouse_clicado_primeiro_quad == true) {
                usuario[mouse_clicado] = 0;
                mouse_clicado_primeiro_quad = false;
            } else if (mouse_clicado_segundo_quad == true) {
                usuario[mouse_clicado] = 1;
                mouse_clicado_segundo_quad = false;
            } else if (mouse_clicado_terceiro_quad == true) {
                usuario[mouse_clicado] = 2;
                mouse_clicado_terceiro_quad = false;
            } else if (mouse_clicado_quarto_quad == true) {
                usuario[mouse_clicado] = 3;
                mouse_clicado_quarto_quad = false;
            }
            //glutPostRedisplay();
            //Se a quantidade de cliques for igual a quantidade_sorteada, significa que o usuario escolheu a quantidade total de quadrados,
            //logo temos que conferir se a sequencia feita pelo mouse, é igual a sorteada pelo programa
            */
            cout << "posMax" << posMaxLida << endl;
            
            /*
            if (mouse_clicado == quantidade_sorteada) {
                for (int i = 0; i <= quantidade_sorteada; i++) {
                    if (valores_sorteados[i] != usuario[i]) {
                        sequencia_correta = false;
                        glutDisplayFunc(tela_gameover);
                    }
                    if (mouse_clicado == 24) {
                        glutDisplayFunc(tela_venceu);

                    }
                    sequencia_correta = true; //Continua o programa se o usuario acertar a sequencia

                }
            }*/
        } else if(state == GLUT_UP) {
            aceso = false;
        }
    }
    glutPostRedisplay();
 //   aguarda = false; //Verificacao
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Vai acendendo os quadrados ja sorteados na sequencia salva no array
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostra_sequencia_sorteados_2x2() {

}

void time_sleep() {
    
}


void logica_mostra_sequencia() {
    poslida++;
}

void desenha_quadrados(int quad) {
    //Paleta de cores
    r1 = 1.0, g1 = 0.0, b1 = 0.0;
    r2 = 0.0, g2 = 1.0, b2 = 0.0;
    r3 = 0.0, g3 = 0.0, b3 = 1.0;
    r4 = 1.0, g4 = 1.0, b4 = 0.0;    
//switch (valores_sorteados[poslida]) {
    switch (quad) {
        case 0:
            //cout << "primeiro" << endl;
            glBegin(GL_QUADS); //primeiro
            glColor3f(r1, g1, b1);
            glVertex2f(-win, 0); // x, y
            glVertex2f(-win, win);
            glVertex2f(0, win);
            glVertex2f(0, 0);
            glEnd();

            glBegin(GL_QUADS); //quarto
            glColor3f(0.7, 0.7, 0.0);
            glVertex2f(0, -win); // x, y
            glVertex2f(0, 0);
            glVertex2f(win, 0);
            glVertex2f(win, -win);
            glEnd();

            glBegin(GL_QUADS); //terceiro
            glColor3f(0.0, 0.0, 0.7);
            glVertex2f(-win, -win); // x, y
            glVertex2f(-win, 0);
            glVertex2f(0, 0);
            glVertex2f(0, -win);
            glEnd();

            glBegin(GL_QUADS); //segundo
            glColor3f(0.0, 0.7, 0.0);
            glVertex2f(0, 0); // x, y
            glVertex2f(0, win);
            glVertex2f(win, win);
            glVertex2f(win, 0);
            glEnd();

            glFlush();
            break;
        case 1:
            //cout << "segundo" << endl;
            glBegin(GL_QUADS); //segundo
            glColor3f(r2, g2, b2);
            glVertex2f(0, 0); // x, y
            glVertex2f(0, win);
            glVertex2f(win, win);
            glVertex2f(win, 0);
            glEnd();

            glBegin(GL_QUADS); //quarto
            glColor3f(0.7, 0.7, 0.0);
            glVertex2f(0, -win); // x, y
            glVertex2f(0, 0);
            glVertex2f(win, 0);
            glVertex2f(win, -win);
            glEnd();

            glBegin(GL_QUADS); //terceiro
            glColor3f(0.0, 0.0, 0.7);
            glVertex2f(-win, -win); // x, y
            glVertex2f(-win, 0);
            glVertex2f(0, 0);
            glVertex2f(0, -win);
            glEnd();

            glBegin(GL_QUADS); //primeiro
            glColor3f(0.7, 0.0, 0.0);
            glVertex2f(-win, 0); // x, y
            glVertex2f(-win, win);
            glVertex2f(0, win);
            glVertex2f(0, 0);
            glEnd();

            glFlush();
            break;
        case 2:
            //cout << "terceiro" << endl;
            glBegin(GL_QUADS); //terceiro
            glColor3f(r3, g3, b3);
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

            glBegin(GL_QUADS); //segundo
            glColor3f(0.0, 0.7, 0.0);
            glVertex2f(0, 0); // x, y
            glVertex2f(0, win);
            glVertex2f(win, win);
            glVertex2f(win, 0);
            glEnd();

            glBegin(GL_QUADS); //primeiro
            glColor3f(0.7, 0.0, 0.0);
            glVertex2f(-win, 0); // x, y
            glVertex2f(-win, win);
            glVertex2f(0, win);
            glVertex2f(0, 0);
            glEnd();

            glFlush();
            break;
        case 3:
            //cout << "quarto" << endl;
            glBegin(GL_QUADS); //quarto
            glColor3f(r4, g4, b4);
            glVertex2f(0, -win); // x, y
            glVertex2f(0, 0);
            glVertex2f(win, 0);
            glVertex2f(win, -win);
            glEnd();

            glBegin(GL_QUADS); //terceiro
            glColor3f(0.0, 0.0, 0.7);
            glVertex2f(-win, -win); // x, y
            glVertex2f(-win, 0);
            glVertex2f(0, 0);
            glVertex2f(0, -win);
            glEnd();

            glBegin(GL_QUADS); //segundo
            glColor3f(0.0, 0.7, 0.0);
            glVertex2f(0, 0); // x, y
            glVertex2f(0, win);
            glVertex2f(win, win);
            glVertex2f(win, 0);
            glEnd();

            glBegin(GL_QUADS); //primeiro
            glColor3f(0.7, 0.0, 0.0);
            glVertex2f(-win, 0); // x, y
            glVertex2f(-win, win);
            glVertex2f(0, win);
            glVertex2f(0, 0);
            glEnd();

            glFlush();
            break;   
    }
        //cout << "apagado" << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Animação Mostrar Sequencia
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PRE_MOSTRAR_SEQUENCIA(int val) {
    glutMouseFunc(NULL);
    poslida = 0;
    animation = true;
    glutDisplayFunc(desenha_quad);
    cout << "passou" << endl;
    glutTimerFunc(WAITTIME,logica2,1);
}

void PLAYING(int val) {
    glutDisplayFunc(desenha_quad_usuario);
    glutPostRedisplay();
    poslida = 0;
    glutMouseFunc(gerencia_mouse_2x2);
}

void GO(int val) {
    if(val) {
        aceso = false;
        glutTimerFunc(WAITTIME,GO,0);
    } else {
        glutDisplayFunc(tela_go);
        glutTimerFunc(1.5*WAITTIME,PLAYING,0);
    }
    glutPostRedisplay();
}

void logica2(int val) {
    if(animation) {
        glutTimerFunc(WAITTIME,logica2,!val);
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
        cout << poslida << "pos" << valores_sorteados[poslida] <<  endl;
    }
}

void desenha_quad() {
    if(aceso)
        desenha_quadrados(valores_sorteados[poslida]);
    else
        renderiza_quadrados_apagados_2x2();
}

void desenha_quad_usuario() {
    if(aceso)
        desenha_quadrados(user);
    else
        renderiza_quadrados_apagados_2x2();
}

void sorteiaQuadrados() {
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++) {
        valores_sorteados[i] = rand()%4;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sorteia um quadrado e acende o mesmo
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void acende_quadrado_sorteado_2x2() {
    //Verificacao
    ja_foi_sorteado_algum_valor = true;

    //Aumenta contador
    quantidade_sorteada++;

    //Sorteia um quadrado
    srand(time(NULL));
    valor_rand = rand() % 4;

    //Preenche o array com os valores sorteados
    if (valor_rand == 0)
        valores_sorteados[quantidade_sorteada] = 0;
    else if (valor_rand == 1)
        valores_sorteados[quantidade_sorteada] = 1;
    else if (valor_rand == 2)
        valores_sorteados[quantidade_sorteada] = 2;
    else if (valor_rand == 3)
        valores_sorteados[quantidade_sorteada] = 3;

    //Paleta de cores
    r1 = 1.0, g1 = 0.0, b1 = 0.0;
    r2 = 0.0, g2 = 1.0, b2 = 0.0;
    r3 = 0.0, g3 = 0.0, b3 = 1.0;
    r4 = 1.0, g4 = 1.0, b4 = 0.0;

    //Ativa quadrado sorteado
    switch (valor_rand) {
        case 0:
            glBegin(GL_QUADS); //primeiro
            glColor3f(r1, g1, b1);
            glVertex2f(-win, 0); // x, y
            glVertex2f(-win, win);
            glVertex2f(0, win);
            glVertex2f(0, 0);
            glEnd();
            glFlush();
            glutPostRedisplay();

            break;
        case 1:
            glBegin(GL_QUADS); //segundo
            glColor3f(r2, g2, b2);
            glVertex2f(0, 0); // x, y
            glVertex2f(0, win);
            glVertex2f(win, win);
            glVertex2f(win, 0);
            glEnd();
            glFlush();
            glutPostRedisplay();
            break;
        case 2:
            glBegin(GL_QUADS); //terceiro
            glColor3f(r3, g3, b3);
            glVertex2f(-win, -win); // x, y
            glVertex2f(-win, 0);
            glVertex2f(0, 0);
            glVertex2f(0, -win);
            glEnd();
            glFlush();
            glutPostRedisplay();

            break;
        case 3:
            glBegin(GL_QUADS); //quarto
            glColor3f(r4, g4, b4);
            glVertex2f(0, -win); // x, y
            glVertex2f(0, 0);
            glVertex2f(win, 0);
            glVertex2f(win, -win);
            glEnd();
            glFlush();
            glutPostRedisplay();
            break;
    }
    aguarda = true;
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
//Inicia renderizacao e verificacoes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void comeca_renderizacao_3x3(void) {
    if (aguarda == false) { //Verificacao
        if (sequencia_correta) { //Se o usuario fez a sequencia certa, faz mais uma rodada
            TIMER = TIMER - 0.05; //A cada rodada a sequencia aparece mais rapida
            sequencia_correta = false; //Nova rodada, reseta contadores
            mouse_clicado = -1; //Nova rodada, reseta contadores

            renderiza_quadrados_apagados_3x3();
            mostra_sequencia_sorteados_3x3();
            sleep(TIMER);
            acende_quadrado_sorteado_3x3();
            sleep(TIMER);
            renderiza_quadrados_apagados_3x3();
        }
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
// Verifica quadrado clicado na tela e depois confere se este esta de acordo com a sequencia ja sorteada
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gerencia_mouse_3x3(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {

            //Obtem valores em relação a resolução da tela
            xf = ((2 * win * x) / view_w) - win;
            yf = (((2 * win) * (view_h - y)) / view_h) - win;

            //Verifica em qual parte da tela se encontra determinado quadrado
            if (xf < (-win / 3))
                if (yf > win / 3) {
                    mouse_clicado_primeiro_quad = true;
                } else if (yf > -win / 3 && yf < win / 3) {
                    mouse_clicado_quarto_quad = true;
                } else if (yf < -win / 3) {
                    mouse_clicado_setimo_quad = true;
                }


            if (xf > (-win / 3) && xf < (win / 3))
                if (yf > win / 3) {
                    mouse_clicado_segundo_quad = true;
                } else if (yf > -win / 3 && yf < win / 3) {
                    mouse_clicado_quinto_quad = true;
                } else if (yf < -win / 3) {
                    mouse_clicado_oitavo_quad = true;
                }

            if (xf > (win / 3))
                if (yf > win / 3) {
                    mouse_clicado_terceiro_quad = true;
                } else if (yf > -win / 3 && yf < win / 3) {
                    mouse_clicado_sexto_quad = true;
                } else if (yf < -win / 3) {
                    mouse_clicado_nono_quad = true;
                }

            //Contador de cliques do mouse
            mouse_clicado++;

            //Guarda sequencia em array em relacao ao que o usuario clicou na tela
            if (mouse_clicado_primeiro_quad == true) {
                usuario[mouse_clicado] = 0;
                mouse_clicado_primeiro_quad = false;
            } else if (mouse_clicado_segundo_quad == true) {
                usuario[mouse_clicado] = 1;
                mouse_clicado_segundo_quad = false;
            } else if (mouse_clicado_terceiro_quad == true) {
                usuario[mouse_clicado] = 2;
                mouse_clicado_terceiro_quad = false;
            } else if (mouse_clicado_quarto_quad == true) {
                usuario[mouse_clicado] = 3;
                mouse_clicado_quarto_quad = false;
            } else if (mouse_clicado_quinto_quad == true) {
                usuario[mouse_clicado] = 4;
                mouse_clicado_quinto_quad = false;
            } else if (mouse_clicado_sexto_quad == true) {
                usuario[mouse_clicado] = 5;
                mouse_clicado_sexto_quad = false;
            } else if (mouse_clicado_setimo_quad == true) {
                usuario[mouse_clicado] = 6;
                mouse_clicado_setimo_quad = false;
            } else if (mouse_clicado_oitavo_quad == true) {
                usuario[mouse_clicado] = 7;
                mouse_clicado_oitavo_quad = false;
            } else if (mouse_clicado_nono_quad == true) {
                usuario[mouse_clicado] = 8;
                mouse_clicado_nono_quad = false;
            }

            //Se a quantidade de cliques for igual a quantidade_sorteada, significa que o usuario escolheu a quantidade total de quadrados,
            //logo temos que conferir se a sequencia feita pelo mouse, é igual a sorteada pelo programa
            if (mouse_clicado == quantidade_sorteada) {
                for (int i = 0; i <= quantidade_sorteada; i++) {
                    if (valores_sorteados[i] != usuario[i]) {
                        sequencia_correta = false;
                        glutDisplayFunc(tela_gameover);
                    }
                    if (mouse_clicado == 24) {
                        glutDisplayFunc(tela_venceu);

                    }
                    sequencia_correta = true; //Continua o programa se o usuario acertar a sequencia
                }
            }
        }
    }
    glutPostRedisplay();
    aguarda = false; //Verificacao
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Vai acendendo os quadrados ja sorteados na sequencia salva no array
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mostra_sequencia_sorteados_3x3() {
    if (ja_foi_sorteado_algum_valor) {

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

        //Limite maximo
        int lim_max = quantidade_sorteada;

        //Le array e acende a sequencia ja sorteada
        for (int i = 0; i <= lim_max; i++) {
            quantidade_sorteada = i;
            switch (valores_sorteados[quantidade_sorteada]) {
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
            //Mostra quadradados apagados entre uma sequencia e outra do for
            sleep(TIMER);
            renderiza_quadrados_apagados_3x3();
            sleep(TIMER);
        }
        aguarda = true; //Verificacao
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Sorteia um quadrado e acende o mesmo
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void acende_quadrado_sorteado_3x3() {
    //Verificacao
    ja_foi_sorteado_algum_valor = true;

    //Aumenta contador
    quantidade_sorteada++;

    //Sorteia um quadrado
    srand(time(NULL));
    valor_rand = rand() % 9;

    //Preenche o array com os valores sorteados
    if (valor_rand == 0)
        valores_sorteados[quantidade_sorteada] = 0;
    else if (valor_rand == 1)
        valores_sorteados[quantidade_sorteada] = 1;
    else if (valor_rand == 2)
        valores_sorteados[quantidade_sorteada] = 2;
    else if (valor_rand == 3)
        valores_sorteados[quantidade_sorteada] = 3;
    else if (valor_rand == 4)
        valores_sorteados[quantidade_sorteada] = 4;
    else if (valor_rand == 5)
        valores_sorteados[quantidade_sorteada] = 5;
    else if (valor_rand == 6)
        valores_sorteados[quantidade_sorteada] = 6;
    else if (valor_rand == 7)
        valores_sorteados[quantidade_sorteada] = 7;
    else if (valor_rand == 8)
        valores_sorteados[quantidade_sorteada] = 8;

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

    //Ativa quadrado sorteado
    switch (valor_rand) {
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
    aguarda = true; //Verificacao
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

