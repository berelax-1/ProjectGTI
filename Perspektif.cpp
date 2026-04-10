#include <GL/glut.h>

float aspekRasio = 1.0f;
float rotasiShowroom = 0.0f;
float sudutRotasiX = 0.0f;
float sudutRotasiY = 0.0f;
bool saklarOrtho = false;

void inisialisasi() {
    glClearColor(0.5f, 0.7f, 0.9f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat posisiCahaya[] = {5.0f, 10.0f, 5.0f, 1.0f};
    GLfloat ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, posisiCahaya);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
}

void gambarBackground() {
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.0f, -0.48f, 0.0f);
    glScalef(15.0f, 0.1f, 15.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, -0.42f, 0.0f);
    glScalef(8.0f, 0.02f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void gambarMobil3D() {
    // Badan bawah mobil
    glPushMatrix();
    glColor3f(0.1f, 0.4f, 0.8f);
    glScalef(2.0f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Kabin
    glPushMatrix();
    glTranslatef(-0.2f, 0.5f, 0.0f);
    glColor3f(0.6f, 0.8f, 0.9f);
    glScalef(1.0f, 0.5f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Roda
    glColor3f(0.15f, 0.15f, 0.15f);

    glPushMatrix();
    glTranslatef(0.6f, -0.25f, 0.55f);
    glutSolidTorus(0.08f, 0.16f, 15, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6f, -0.25f, -0.55f);
    glutSolidTorus(0.08f, 0.16f, 15, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6f, -0.25f, 0.55f);
    glutSolidTorus(0.08f, 0.16f, 15, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6f, -0.25f, -0.55f);
    glutSolidTorus(0.08f, 0.16f, 15, 20);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -1.0f, -12.0f);

    if (saklarOrtho) {
        glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(-45.0f + rotasiShowroom, 0.0f, 1.0f, 0.0f);
    } else {
        glRotatef(sudutRotasiX, 1.0f, 0.0f, 0.0f);
        glRotatef(sudutRotasiY, 0.0f, 1.0f, 0.0f);
    }

    gambarBackground();
    gambarMobil3D();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    aspekRasio = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (saklarOrtho) {
        float ukuranLayar = 4.0f;
        if (w >= h) {
            glOrtho(-ukuranLayar * aspekRasio, ukuranLayar * aspekRasio,
                    -ukuranLayar, ukuranLayar, -20.0f, 20.0f);
        } else {
            glOrtho(-ukuranLayar, ukuranLayar,
                    -ukuranLayar / aspekRasio, ukuranLayar / aspekRasio,
                    -20.0f, 20.0f);
        }
    } else {
        gluPerspective(45.0f, aspekRasio, 0.1f, 100.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void updateProyeksi() {
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    reshape(w, h);
}

void pewaktu(int value) {
    if (saklarOrtho) {
        rotasiShowroom += 0.5f;
        if (rotasiShowroom > 360.0f) {
            rotasiShowroom -= 360.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, pewaktu, 0);
}

void ControlInput(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            // 1-point perspective
            sudutRotasiX = 0.0f;
            sudutRotasiY = 0.0f;
            saklarOrtho = false;
            updateProyeksi();
            break;

        case '2':
            // 2-point perspective
            sudutRotasiX = 0.0f;
            sudutRotasiY = 45.0f;
            saklarOrtho = false;
            updateProyeksi();
            break;

        case '3':
            // 3-point perspective
            sudutRotasiX = 45.0f;
            sudutRotasiY = 45.0f;
            saklarOrtho = false;
            updateProyeksi();
            break;

        case '4':
            // Isometric / orthographic
            saklarOrtho = true;
            rotasiShowroom = 0.0f;
            updateProyeksi();
            break;

        case 27: // ESC
            exit(0);
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Representasi 3D Mobil - Orthographic dan Perspektif");

    inisialisasi();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(ControlInput);
    glutTimerFunc(0, pewaktu, 0);

    glutMainLoop();
    return 0;
}
