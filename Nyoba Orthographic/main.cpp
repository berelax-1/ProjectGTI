#include <GL/glut.h>

// Variabel untuk memutar kamera secara perlahan (Ala pameran Showroom)
float rotasiShowroom = 0.0f;

void inisialisasi() {
    // 1. BACKGROUND: Warna latar belakang langit (Biru Cerah)
    glClearColor(0.5f, 0.7f, 0.9f, 1.0f); 
    
    // FOKUS REPRESENTASI 3D: Mengaktifkan kedalaman dan pencahayaan
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    // Penempatan cahaya agar warna biru mobil memantul dengan bagus
    GLfloat posisiCahaya[] = { 5.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, posisiCahaya);
}

// Lingkungan sekitar (Background Bawah)
void gambarBackground() {
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);      // Warna abu-abu aspal
    glTranslatef(0.0f, -0.48f, 0.0f); // Posisikan pas di telapak ban
    glScalef(15.0f, 0.1f, 15.0f);     // Skalakan jadi lantai luas
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Garis marka / dekorasi panggung putih
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, -0.42f, 0.0f);
    glScalef(8.0f, 0.02f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Objek Mobil 3D yang sudah diperbaiki
void gambarMobil3D() {
    // 1. Badan Bawah Mobil (WARNA BARU: Biru Sport)
    glPushMatrix();
    glColor3f(0.1f, 0.4f, 0.8f); // R, G, B untuk warna Biru
    glScalef(2.0f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // 2. Kabin/Atap Mobil (Warna kaca cyan/biru muda cerah)
    glPushMatrix();
    glTranslatef(-0.2f, 0.5f, 0.0f);
    glColor3f(0.6f, 0.8f, 0.9f); 
    glScalef(1.0f, 0.5f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // 3. Empat Roda (POSISI DAN BENTUK DIPERBAIKI)
    glColor3f(0.15f, 0.15f, 0.15f); // Warna hitam ban pekat
    
    
    // Ban Depan Kiri
    glPushMatrix(); 
    glTranslatef(0.6f, -0.25f, 0.55f); 
    glutSolidTorus(0.08f, 0.16f, 15, 20); 
    glPopMatrix();
    
    // Ban Depan Kanan
    glPushMatrix(); 
    glTranslatef(0.6f, -0.25f, -0.55f); 
    glutSolidTorus(0.08f, 0.16f, 15, 20); 
    glPopMatrix();
    
    // Ban Belakang Kiri
    glPushMatrix(); 
    glTranslatef(-0.6f, -0.25f, 0.55f); 
    glutSolidTorus(0.08f, 0.16f, 15, 20); 
    glPopMatrix();
    
    // Ban Belakang Kanan
    glPushMatrix(); 
    glTranslatef(-0.6f, -0.25f, -0.55f); 
    glutSolidTorus(0.08f, 0.16f, 15, 20); 
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, -0.5f, 0.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-45.0f + rotasiShowroom, 0.0f, 1.0f, 0.0f);

    gambarBackground();
    gambarMobil3D();

    glutSwapBuffers();
}

// Proyeksi Orthographic 
void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspekRasio = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Orthographic Viewing Volume
    float ukuranLayar = 4.0f; // Area zoom pandangan
    if (w >= h) {
        glOrtho(-ukuranLayar * aspekRasio, ukuranLayar * aspekRasio, -ukuranLayar, ukuranLayar, -20.0f, 20.0f);
    } else {
        glOrtho(-ukuranLayar, ukuranLayar, -ukuranLayar / aspekRasio, ukuranLayar / aspekRasio, -20.0f, 20.0f);
    }

    glMatrixMode(GL_MODELVIEW);
}

// Animasi pasif untuk memutar panggung
void timer(int value) {
    rotasiShowroom += 0.5f; // Kecepatan putaran 
    if (rotasiShowroom > 360.0f) rotasiShowroom -= 360.0f;
    
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Fokus: Representasi 3D Mobil & Orthographic");

    inisialisasi();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
