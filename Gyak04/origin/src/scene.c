#include "scene.h"

#include <GL/gl.h>
#include <math.h>

void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    draw_origin();
    draw_triangle();
    draw_sphere();
    draw_chessboard();
    draw_cylinder_cone_approximation();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
void draw_triangle(){
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0);
    glColor3f(0.5, 0.5, 0); 
    glVertex3f(0.5, 0, 0.5);
    glColor3f(0.5, 0, 0.5); 
    glVertex3f(0.5, 0.5, 0.5);
    glEnd();
}
void draw_sphere() {
    const int slices = 200;  // szélek száma az osztásonként
    const int stacks = 200;  // magasság száma az osztásonként
    const float radius = 0.2;  // a gömb sugara
    const float gray_color = 0.5;  // a szürke szín intenzitása

    // Kirajzoljuk a gömböt
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(gray_color, gray_color, gray_color);
    for (int i = 0; i <= stacks; ++i) {
        float lat0 = M_PI * (-0.5 + (float)(i - 1) / stacks);
        float z0 = radius * sin(lat0);
        float zr0 = radius * cos(lat0);

        float lat1 = M_PI * (-0.5 + (float)i / stacks);
        float z1 = radius * sin(lat1);
        float zr1 = radius * cos(lat1);

        for (int j = 0; j <= slices; ++j) {
            float lng = 2 * M_PI * (float)(j - 1) / slices;
            float x = cos(lng);
            float y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);

            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
    }
    glEnd();
}
void draw_chessboard() {
    int i, j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                glColor3f(1.0, 1.0, 1.0);
            } else {
                glColor3f(0.0, 0.0, 0.0);
            }

            glBegin(GL_QUADS);
            glVertex3f(i, j, 0.0);
            glVertex3f(i+1, j, 0.0);
            glVertex3f(i+1, j+1, 0.0);
            glVertex3f(i, j+1, 0.0);
            glEnd();
        }
    }
}
void draw_cylinder_cone_approximation()
{
    const float PI = 3.14159265358979323846f;
    const int SEGMENTS = 32;

    // Draw cylinder approximation with triangle strip
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = 2.0f * PI * i / SEGMENTS;
        float x = cosf(angle);
        float y = sinf(angle);
        float u = (float)i / SEGMENTS;

        glColor3f(0.5f, 0.5f, 0.5f);
        glNormal3f(x, y, 0.0f);
        glVertex3f(x, y, 0.0f);
        glNormal3f(x, y, 0.0f);
        glVertex3f(x, y, 1.0f);

        // Texture coordinates for cylinder approximation
        glTexCoord2f(u, 0.0f);
        glVertex3f(x, y, 0.0f);
        glTexCoord2f(u, 1.0f);
        glVertex3f(x, y, 1.0f);
    }
    glEnd();

    // Draw cone approximation with triangle fan
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.5f, 0.5f, 0.5f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = 2.0f * PI * i / SEGMENTS;
        float x = cosf(angle);
        float y = sinf(angle);

        // Texture coordinates for cone approximation
        float u = (float)i / SEGMENTS;
        glTexCoord2f(u, 1.0f);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.5f, 0.5f, 0.5f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    for (int i = 0; i <= SEGMENTS; i++) {
        float angle = 2.0f * PI * i / SEGMENTS;
        float x = cosf(angle);
        float y = sinf(angle);

        // Texture coordinates for cone approximation
        float u = (float)i / SEGMENTS;
        glTexCoord2f(u, 0.0f);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x, y, 1.0f);
    }
    glEnd();
}