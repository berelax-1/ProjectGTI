#include <GL/glut.h>

// ==========================================================
// VARIABEL GLOBAL
// ==========================================================

// aspekRasio digunakan untuk menyesuaikan proyeksi dengan ukuran window
float aspekRasio;

// rotasiShowroom dipakai untuk animasi putaran pada mode isometric/orthographic
float rotasiShowroom = 0.0f;

// sudutRotasiX dan sudutRotasiY dipakai sebagai kontrol arah pandang kamera
// Nilai ini akan berubah saat user menekan tombol 1, 2, 3, atau 4
float sudutRotasiX = 0.0f;
float sudutRotasiY = 0.0f;

// saklarOrtho menentukan jenis proyeksi:
// true  = orthographic
// false = perspective
bool saklarOrtho = false;


// ==========================================================
// INISIALISASI
// Tahap awal untuk menyiapkan background, depth test, lighting,
// dan material permukaan objek.
// ==========================================================
void inisialisasi() {
    // ------------------------------------------------------
    // BACKGROUND
    // Mengatur warna latar belakang window menjadi biru cerah
    // agar menyerupai langit / suasana luar ruangan.
    // ------------------------------------------------------
    glClearColor(0.5f, 0.7f, 0.9f, 1.0f); 
    
    // ------------------------------------------------------
    // ALGORITMA RENDERING: DEPTH TEST
    // Depth test digunakan agar OpenGL dapat menentukan
    // objek mana yang berada di depan dan mana yang di belakang.
    // Tanpa depth test, objek bisa terlihat saling menimpa
    // secara tidak benar.
    // ------------------------------------------------------
    glEnable(GL_DEPTH_TEST);

    // ------------------------------------------------------
    // SHADING & LIGHTING
    // Mengaktifkan sistem pencahayaan bawaan OpenGL
    // (fixed-function pipeline).
    //
    // GL_LIGHTING : mengaktifkan perhitungan cahaya
    // GL_LIGHT0   : mengaktifkan satu sumber cahaya
    // ------------------------------------------------------
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // ------------------------------------------------------
    // KARAKTERISTIK PERMUKAAN
    // Mengaktifkan color material, sehingga warna yang diberikan
    // lewat glColor3f() akan ikut dianggap sebagai material objek.
    // Dengan ini, objek bisa tetap berwarna walaupun lighting aktif.
    // ------------------------------------------------------
    glEnable(GL_COLOR_MATERIAL);
    
    // ------------------------------------------------------
    // CAHAYA
    // Menentukan posisi sumber cahaya pada koordinat (5,10,5).
    // Nilai terakhir = 1.0f berarti cahaya bersifat positional,
    // bukan directional light.
    //
    // Efeknya: bagian mobil yang dekat sumber cahaya akan tampak
    // lebih terang, sedangkan sisi lain tampak lebih gelap.
    // ------------------------------------------------------
    GLfloat posisiCahaya[] = { 5.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, posisiCahaya);
}


// ==========================================================
// GEOMETRI LINGKUNGAN
// Fungsi ini menggambar lantai/aspek lingkungan sekitar.
// Di sini background bawah dibuat dari primitive cube.
// ==========================================================
void gambarBackground() {
    // ------------------------------------------------------
    // OBJEK 1: LANTAI / ASPAL
    // ------------------------------------------------------
    glPushMatrix();

    // KARAKTERISTIK PERMUKAAN:
    // Warna abu-abu untuk menyerupai aspal/jalan
    glColor3f(0.3f, 0.3f, 0.3f);

    // TRANSFORMASI GEOMETRI:
    // Menggeser objek ke bawah agar sejajar dengan ban mobil
    glTranslatef(0.0f, -0.48f, 0.0f);

    // Memperbesar cube agar berubah menjadi bidang lantai yang luas
    glScalef(15.0f, 0.1f, 15.0f);

    // GEOMETRI:
    // Primitive dasar berupa cube
    glutSolidCube(1.0f);

    glPopMatrix();
    
    // ------------------------------------------------------
    // OBJEK 2: GARIS MARKA / PANGGUNG
    // ------------------------------------------------------
    glPushMatrix();

    // KARAKTERISTIK PERMUKAAN:
    // Warna putih untuk dekorasi garis di lantai
    glColor3f(1.0f, 1.0f, 1.0f);

    // TRANSFORMASI:
    // Sedikit di atas lantai agar terlihat jelas
    glTranslatef(0.0f, -0.42f, 0.0f);

    // Membuat bentuk kotak tipis memanjang
    glScalef(8.0f, 0.02f, 2.0f);

    // GEOMETRI:
    glutSolidCube(1.0f);

    glPopMatrix();
}


// ==========================================================
// GEOMETRI MOBIL 3D
// Fungsi ini membentuk mobil dari gabungan beberapa primitive:
// cube untuk body dan kabin, torus untuk roda.
// ==========================================================
void gambarMobil3D() {

    // ------------------------------------------------------
    // BAGIAN 1: BADAN BAWAH MOBIL
    // ------------------------------------------------------
    glPushMatrix();

    // KARAKTERISTIK PERMUKAAN:
    // Warna biru sport untuk body mobil
    glColor3f(0.1f, 0.4f, 0.8f);

    // TRANSFORMASI:
    // Cube diperbesar agar membentuk badan mobil
    glScalef(2.0f, 0.5f, 1.0f);

    // GEOMETRI:
    glutSolidCube(1.0f);

    glPopMatrix();

    // ------------------------------------------------------
    // BAGIAN 2: KABIN / ATAP MOBIL
    // ------------------------------------------------------
    glPushMatrix();

    // TRANSFORMASI:
    // Kabin dipindahkan ke atas body dan sedikit ke kiri
    glTranslatef(-0.2f, 0.5f, 0.0f);

    // KARAKTERISTIK PERMUKAAN:
    // Warna cyan muda untuk memberi kesan kaca/kabin
    glColor3f(0.6f, 0.8f, 0.9f);

    // Membentuk ukuran kabin
    glScalef(1.0f, 0.5f, 0.8f);

    // GEOMETRI:
    glutSolidCube(1.0f);

    glPopMatrix();

    // ------------------------------------------------------
    // BAGIAN 3: EMPAT RODA
    // Primitive yang digunakan adalah torus
    // ------------------------------------------------------

    // KARAKTERISTIK PERMUKAAN:
    // Warna hitam untuk ban
    glColor3f(0.15f, 0.15f, 0.15f);
    
    // Ban depan kiri
    glPushMatrix(); 
    glTranslatef(0.6f, -0.25f, 0.55f); 
    glutSolidTorus(0.08f, 0.16f, 15, 20); 
    glPopMatrix();
    
    // Ban depan kanan
    glPushMatrix(); 
    glTranslatef(0.6f, -0.25f, -0.55f); 
    glutSolidTorus(0.08f, 0.16f, 15, 20); 
    glPopMatrix();
    
    // Ban belakang kiri
    glPushMatrix(); 
    glTranslatef(-0.6f, -0.25f, 0.55f); 
    glutSolidTorus(0.08f, 0.16f, 15, 20); 
    glPopMatrix();
    
    // Ban belakang kanan
    glPushMatrix(); 
    glTranslatef(-0.6f, -0.25f, -0.55f); 
    glutSolidTorus(0.08f, 0.16f, 15, 20); 
    glPopMatrix();
}


// ==========================================================
// DISPLAY
// Fungsi utama render frame.
// Di sinilah tahapan viewing, transformasi kamera,
// dan output akhir ke layar terjadi.
// ==========================================================
void display() {
    // ------------------------------------------------------
    // ALGORITMA RENDERING
    // Membersihkan color buffer dan depth buffer setiap frame
    // agar frame lama tidak menumpuk dengan frame baru.
    // ------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset matrix modelview ke identitas
    glLoadIdentity();

    // ------------------------------------------------------
    // KAMERA / VIEWING
    // Menggeser scene agar objek berada dalam jangkauan kamera.
    // Z = -12 artinya scene dijauhkan dari kamera.
    // Y = -1 membuat mobil sedikit turun agar komposisinya pas.
    // ------------------------------------------------------
    glTranslatef(0.0f, -1.0f, -12.0f);

    // ------------------------------------------------------
    // KAMERA / ORIENTASI PANDANG
    // Sudut rotasi diatur dari input keyboard:
    // - tombol 1 : 1 point perspective
    // - tombol 2 : 2 point perspective
    // - tombol 3 : 3 point perspective
    // - tombol 4 : isometric / orthographic
    // ------------------------------------------------------
    glRotatef(sudutRotasiX, 1.0f, 0.0f, 0.0f);
    glRotatef(sudutRotasiY, 0.0f, 1.0f, 0.0f);

    // ------------------------------------------------------
    // TAHAP RENDER OBJEK
    // Setelah kamera dan transformasi siap,
    // objek lingkungan dan mobil digambar.
    // ------------------------------------------------------
    gambarBackground();
    gambarMobil3D();

    // ------------------------------------------------------
    // OUTPUT RENDERING
    // Menggunakan double buffering agar animasi lebih halus
    // dan tidak terjadi flicker.
    // ------------------------------------------------------
    glutSwapBuffers();
}


// ==========================================================
// RESHAPE
// Fungsi ini dipanggil saat ukuran window berubah.
// Di sini ditentukan jenis proyeksi:
// - Orthographic jika saklarOrtho = true
// - Perspective jika saklarOrtho = false
// ==========================================================
void reshape(int w, int h) {
    if (h == 0) h = 1;

    // Menghitung aspek rasio window
    aspekRasio = (float)w / (float)h;

    // Menentukan area viewport
    glViewport(0, 0, w, h);

    // Pindah ke matrix projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(saklarOrtho == true){
        // --------------------------------------------------
        // PROYEKSI ORTHOGRAPHIC
        // Pada proyeksi orthographic, objek yang jauh
        // tidak terlihat mengecil.
        //
        // Cocok untuk tampilan teknik / isometrik.
        // --------------------------------------------------
        float ukuranLayar = 4.0f;

        if (w >= h) {
            glOrtho(-ukuranLayar * aspekRasio, ukuranLayar * aspekRasio,
                    -ukuranLayar, ukuranLayar,
                    -20.0f, 20.0f);
        } else {
            glOrtho(-ukuranLayar, ukuranLayar,
                    -ukuranLayar / aspekRasio, ukuranLayar / aspekRasio,
                    -20.0f, 20.0f);
        }
    } else {
        // --------------------------------------------------
        // PROYEKSI PERSPECTIVE
        // Pada perspective, objek yang jauh terlihat lebih kecil.
        // Ini menimbulkan kesan realistis seperti penglihatan manusia.
        //
        // 45.0f  = field of view
        // 0.1f   = near clipping plane
        // 100.0f = far clipping plane
        // --------------------------------------------------
        gluPerspective(45.0f, aspekRasio, 0.1f, 100.0f);
    }

    // Kembali ke matrix modelview
    glMatrixMode(GL_MODELVIEW);
}


// ==========================================================
// TIMER / ANIMASI
// Fungsi ini dipakai untuk menggerakkan rotasi showroom.
// Animasi hanya aktif saat mode orthographic/isometric.
// ==========================================================
void pewaktu(int value) {
    if(saklarOrtho == true){
        // Menambah sudut rotasi sedikit demi sedikit
        rotasiShowroom += 0.5f;

        // Jika lebih dari 360 derajat, kembali dari awal
        if(rotasiShowroom > 360.0f){
            rotasiShowroom -= 360.0f;
        } 
    }
   
    // Meminta OpenGL merender ulang frame berikutnya
    glutPostRedisplay();

    // Mengatur timer agar dipanggil lagi tiap 16 ms
    // (~60 FPS)
    glutTimerFunc(16, pewaktu, 0); 
}


// ==========================================================
// INPUT KEYBOARD
// Fungsi ini mengatur mode pandang berdasarkan tombol.
// ==========================================================
void ControlInput(unsigned char key, int x, int y){
    switch (key){
        case '1':
            // ----------------------------------------------
            // 1 POINT PERSPECTIVE
            // Pandangan lurus ke depan
            // Satu titik hilang
            // ----------------------------------------------
            sudutRotasiX = 0.0f;
            sudutRotasiY = 0.0f;
            saklarOrtho = false;
            break;

        case '2':
            // ----------------------------------------------
            // 2 POINT PERSPECTIVE
            // Objek diputar pada sumbu Y
            // Dua sisi objek terlihat
            // ----------------------------------------------
            sudutRotasiX = 0.0f;
            sudutRotasiY = 45.0f;
            saklarOrtho = false;
            break;

        case '3':
            // ----------------------------------------------
            // 3 POINT PERSPECTIVE
            // Objek diputar pada sumbu X dan Y
            // Memberi kesan lebih dramatis / dinamis
            // ----------------------------------------------
            sudutRotasiX = 45.0f;
            sudutRotasiY = 45.0f;
            saklarOrtho = false;
            break;

        case '4':
            // ----------------------------------------------
            // ISOMETRIC / ORTHOGRAPHIC
            // Menggunakan sudut khas isometrik:
            // X = 30 derajat, Y = -45 derajat
            // Serta animasi rotasi showroom
            // ----------------------------------------------
            sudutRotasiX = 30.0f;
            sudutRotasiY = -45.0f + rotasiShowroom;
            saklarOrtho = true;
            break;
    }

    // Meminta render ulang setelah input
    glutPostRedisplay();
}


// ==========================================================
// MAIN
// Titik awal program
// ==========================================================
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // GLUT_DOUBLE : double buffering
    // GLUT_RGB    : mode warna RGB
    // GLUT_DEPTH  : depth buffer aktif
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutCreateWindow("Fokus: Representasi 3D Mobil & Orthographic serta Perspektif");

    // Inisialisasi sistem rendering
    inisialisasi();

    // Registrasi callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, pewaktu, 0);
    glutKeyboardFunc(ControlInput);

    // Menjalankan loop utama
    glutMainLoop();

    return 0;
}
