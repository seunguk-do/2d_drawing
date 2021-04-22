#define GL_SILENCE_DEPRECATION
#include <GL/freeglut.h>
//#include <OpenGL/gl.h>
#include <vector>
#include "objects/player.h"
#include "objects/enemy.h"
#include "objects/bullet.h"
#include "objects/item.h"
#include "aircraft.hpp"
#include "mode.h"
#include "graph.h"
#include "hit.h"
#include "view.h"

Player player = Player();
EnemyList enemy_list = EnemyList();
BulletList player_bullets = BulletList(PLAYER);
BulletList enemy_bullets = BulletList(ENEMY);
ItemList item_list = ItemList();
Gamemode mode = NORMAL;
LineRendering line_rendering = SHOWING;
float planet[5] = { 0.3f, 0.3f, 0.1f, 0.1f, 0.0f };
float planet2[5] = { 0.8f, 0.9f, 0.05f, 0.05f, 0.0f };

float plane[3] = { 0.5f, 0.15f, 130.0f };
bool plane_rotate = true;
Viewmode view = TPS;
int over = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glFrustum(-4.0, 4.0, -4.0, 4.0, 1.0, 10.0);
    /*
    player.x = 0.01;
    player.y = 0.01;
    player.width = 0.15;
    player.height = 0.18;
    */
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glColor3f(1.0, 1.0, 1.0);
    
    Position player_position = player.get_position();
    Position enemy_position = enemy_list.getEnemy().get_position();
    std::vector <Position> player_bullet_positions;
    std::vector <Position> enemy_bullet_positions;
    std::vector<Position> item_positions;

    float iii = -5;
    int i;

    switch (over) {
    case 0:
        glColor3f(0.0, 0.0, 0.0);
        
        if (line_rendering == SHOWING) { 
            glBegin(GL_LINES);
            while (iii <= 10) {
                glVertex3f(-5, -0.1, iii);
                glVertex3f(10, -0.1, iii);

                glVertex3f(iii, -0.1, -5);
                glVertex3f(iii, -0.1, 10);
                iii += 0.15;
            }
            glEnd();
        }

        // Planet #1
        glPushMatrix();
            glColor3f(0.5, 0.5, 0.0);
            glTranslatef(9, -2, 4);
            glutSolidSphere(1, 100, 100);

            glColor3f(0.5, 0.0, 0.0);
            glRotatef(planet[4], 0, 1, 0);
            glTranslatef(1.5, 0.0, 1.5);
            glScalef(0.3, 0.3, 0.3);
            glutSolidSphere(1, 100, 100);

            glColor3f(0.0, 0.5, 0.0);
            glRotatef(planet[4] * 2, 0, 1, 0);
            glTranslatef(1.5, 0.0, 1.5);
            glScalef(0.3, 0.3, 0.3);
            glutSolidSphere(1, 100, 100);
        glPopMatrix();

        // Planet #2
        glPushMatrix();
            glColor3f(0.5, 0.5, 0.0);
            glTranslatef(3.0, 1.5, 4.0);
            glutSolidSphere(0.6, 100, 100);

            glColor3f(0.0, 0.8, 0.4);
            glRotatef(planet2[4], 0, 1, 0);
            glTranslatef(1.0, 0.0, 1.0);
            glScalef(0.3, 0.3, 0.3);
            glutSolidSphere(1, 100, 100);

            glColor3f(0.5, 0.5, 0.5);
            glRotatef(planet[4] * 2, 0, 1, 0);
            glTranslatef(1.0, 0.0, 1.0);
            glScalef(0.3, 0.3, 0.3);
            glutSolidSphere(1, 100, 100);
        glPopMatrix();

        //player
        /*switch (player.getHP()) {
        case 3:
            glColor3f(0, 1.0, 0);
            break;
        case 2:
            glColor3f(1.0, 1.0, 0);
            break;
        case 1:
            glColor3f(1.0, 0, 0);
            break;
        }*/

        // Player
        glPushMatrix();
            glTranslatef(player_position.x, 0, player_position.y);
            glScalef(0.1, 0.1, 0.1);
            draw_aircraft();
        glPopMatrix();
       
        //player bullet
        //glColor3f(1.0f, 0.5f, 0.0f);

        /*player_bullet_positions = player_bullets.get_bullet_positions();
        for (i = 0; i < player_bullet_positions.size(); i++) {
            Position bullet_position = player_bullet_positions[i];
            Bullet(bullet_position.x, bullet_position.y, BULLET_RADIUS);
        }*/

        //enemy
        /*switch (enemy_list.getIndex()) {
        case 0:
            glColor3f(1.0, 0, 0);
            break;
        case 1:
            glColor3f(1.0, 0.5, 0);
            break;
        case 2:
            glColor3f(1.0, 1.0, 0);
            break;
        case 3:
            glColor3f(0, 1.0, 0);
            break;
        case 4:
            glColor3f(0, 0, 1.0);
            break;
        }*/

        // Enemy
        glPushMatrix();
            //glTranslatef(enemy_position.x, 0.0, 10.0);
        glTranslatef(enemy_position.x, 0.0, 5.0);
            glRotatef(180, 0, 1, 0);
            glScalef(0.1, 0.1, 0.1);
            draw_aircraft();
        glPopMatrix();

        //Rotatete();
        //Plane(-enemy_position.x, -enemy_position.y, 220 - plane[2]);
        //Origin();

        //enemy bullet
        //glColor3f(1.0f, 0.5f, 0.0f);
        /*enemy_bullet_positions = enemy_bullets.get_bullet_positions();
        for (i = 0; i < enemy_bullet_positions.size(); i++) {
            Position bullet_position = enemy_bullet_positions[i];
            Bullet(bullet_position.x, bullet_position.y, BULLET_RADIUS);
        }*/

        //item
        /*item_positions = item_list.get_item_positions();
        for (i = 0; i < item_positions.size(); i++) {
            glColor3f(1.0f, 1.0f, 0.0f);
            Position item_position = item_positions[i];
            Item(item_position.x, item_position.y, ITEM_LENGTH);
        }*/

        break;

    case 1: {
        glLoadIdentity();
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);             // W
        glVertex2f(0.3, 0.6);
        glVertex2f(0.325, 0.5);
        glVertex2f(0.35, 0.6);
        glVertex2f(0.375, 0.5);
        glVertex2f(0.4, 0.6);
        glEnd();

        glBegin(GL_LINE_STRIP);             // I
        glVertex2f(0.5, 0.6);
        glVertex2f(0.5, 0.5);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(0.475, 0.6);
        glVertex2f(0.525, 0.6);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(0.475, 0.5);
        glVertex2f(0.525, 0.5);
        glEnd();

        glBegin(GL_LINE_STRIP);             // N
        glVertex2f(0.6, 0.5);
        glVertex2f(0.6, 0.6);
        glVertex2f(0.675, 0.5);
        glVertex2f(0.675, 0.6);
        glEnd();
        break; }
    case 2: {
        glLoadIdentity();
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);             // L
        glVertex2f(0.25, 0.6);
        glVertex2f(0.25, 0.5);
        glVertex2f(0.325, 0.5);
        glEnd();

        glBegin(GL_LINE_LOOP);              // O
        glVertex2f(0.4, 0.6);
        glVertex2f(0.4, 0.5);
        glVertex2f(0.475, 0.5);
        glVertex2f(0.475, 0.6);
        glEnd();

        glBegin(GL_LINE_STRIP);             // S
        glVertex2f(0.625, 0.6);
        glVertex2f(0.55, 0.6);
        glVertex2f(0.55, 0.55);
        glVertex2f(0.625, 0.55);
        glVertex2f(0.625, 0.5);
        glVertex2f(0.55, 0.5);
        glEnd();

        glBegin(GL_LINE_STRIP);             // E
        glVertex2f(0.775, 0.6);
        glVertex2f(0.7, 0.6);
        glVertex2f(0.7, 0.5);
        glVertex2f(0.775, 0.5);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(0.7, 0.55);
        glVertex2f(0.775, 0.55);
        glEnd();
        break;
    }
    }
    glLoadIdentity();
    gluLookAt(player_position.x, 0.7, player_position.y - 2.0, player_position.x, -0.05, player_position.y + 1, 0, 1, 0);
    glTranslatef(0.0, 0.0, -1.0);
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5, 0.5, -0.5 * (GLfloat)h / (GLfloat)w, 0.5 * (GLfloat)h / (GLfloat)w, 0.5, 7.0);
    //glTranslatef(0, 0, -5.0);
    //glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
    case 'i':
        player.move_up(0.01);
        break;
    case 'm':
        player.move_down(0.01);
        break;
    case 'k':
        player.move_right(0.01);
        break;
    case 'j':
        player.move_left(0.01);
        break;
    case 'c':
        if (mode == ALLPASS) mode = NORMAL;
        else mode = ALLPASS;
        break;
    case 'f':
        if (mode == ALLFAIL) mode = NORMAL;
        else mode = ALLFAIL;
        break;
    case 'v':
        view_change();
        break;
    case 'r':
        if (line_rendering == SHOWING) line_rendering = HIDING;
        else line_rendering = SHOWING;
        break;
    case 32:  //space bar
        player.shoot();
        break;
    }
    glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y) {
    Position player_position = player.get_position();

    switch (key) {
    case GLUT_KEY_UP:
        player.move_up(0.05);
        break;
    case GLUT_KEY_DOWN:
        player.move_down(0.05);
        break;
    case GLUT_KEY_RIGHT:
        player.move_left(0.05);
        break;
    case GLUT_KEY_LEFT:
        player.move_right(0.05);
        break;
    }
    glutPostRedisplay();
}

void idle_func() {
    player_bullets.move_bullets();
    enemy_bullets.move_bullets();
    enemy_list.move();
    item_list.move_items();
    planet[4] += 0.5;
    planet2[4] += 1;

    if (plane_rotate == true)
        plane[2] -= 0.2;
    else
        plane[2] += 0.2;

    if (plane[2] > 120)
        plane_rotate = true;
    if (plane[2] < 100)
        plane_rotate = false;

    check_hit();
    check_get_item();

    glutPostRedisplay();
}

void timer_func(int a) {
    enemy_list.getEnemy().shoot();
    if (enemy_list.getIndex() != 0) { enemy_list.move_2(); }

    glutTimerFunc(700, timer_func, 1);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(500, 300);
    glutCreateWindow(argv[0]);
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialkeyboard);
    glutIdleFunc(idle_func);
    //glutTimerFunc(700, timer_func, 1);            // Enemy shoots every 500ms

    glutMainLoop();
    return 0;
}