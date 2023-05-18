#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

#include <math.h>

#include <SDL2/SDL_image.h>

// Modell változói
    float truckX = 0.0f;
    float truckZ = 0.0f;
    float truckAngle = 0.0f;
    float truckSpeed = 0.0f;
    float truckAcceleration = 0.01f;
    float truckDeceleration = 0.02f;
    float truckMaxSpeed = 0.1f;
    float wheelAngle = 0.0f;
    float ambient_light[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 100.0f, 1.0f };

void init_scene(Scene* scene)
{
    load_model(&(scene->truck), "assets/models/truck.obj");
    scene->texture_id1 = load_texture("assets/textures/grass1.jpg");
    scene->texture_id2 = load_texture("assets/textures/truck4.jpg");
    scene->sky1 = load_texture("assets/textures/sky1.jpg");
    scene->sky2 = load_texture("assets/textures/sky2.jpg");
    scene->sky3 = load_texture("assets/textures/sky3.jpg");
    scene->sky4 = load_texture("assets/textures/sky4.jpg");
    scene->sky5 = load_texture("assets/textures/sky5.jpg");
    scene->sky6 = load_texture("assets/textures/sky6.jpg");
    scene->txt = load_texture("assets/textures/txt.jpg");

    glBindTexture(GL_TEXTURE_2D, scene->texture_id1);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id2);
    glBindTexture(GL_TEXTURE_2D, scene->sky1);
    glBindTexture(GL_TEXTURE_2D, scene->sky2);
    glBindTexture(GL_TEXTURE_2D, scene->sky3);
    glBindTexture(GL_TEXTURE_2D, scene->sky4);
    glBindTexture(GL_TEXTURE_2D, scene->sky5);
    glBindTexture(GL_TEXTURE_2D, scene->sky6);
    glBindTexture(GL_TEXTURE_2D, scene->txt);

    
    wheelAngle = 0.0f;

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    
}

void set_lighting()
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    
    
    

    if (keyState[SDL_SCANCODE_I]) {
        ambient_light[0] +=0.01f;
        ambient_light[1] +=0.01f;
        ambient_light[2] +=0.01f;
    }
    if (keyState[SDL_SCANCODE_O]) {
        ambient_light[0] -=0.01f;
        ambient_light[1] -=0.01f;
        ambient_light[2] -=0.01f;
    }

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{
    
}

void render_scene(const Scene* scene)
{
    glClearColor(0.0, 0.0, 1.0, 1.0);

    
    draw_ground(scene);
    draw_skybox(scene);
   
    set_material(&(scene->material));
    set_lighting();
    draw_origin();

    glBindTexture(GL_TEXTURE_2D, scene->texture_id2);
    glTranslatef(0.0,0.0,0.7);
    glRotatef(90.0, 1.0, 0.0, 0.0);

    updateTruck(&truckX, &truckZ, &truckAngle, &truckSpeed, &truckAcceleration, &truckDeceleration, &truckMaxSpeed);
    glTranslatef(truckX, 0.0f, truckZ);
    glRotatef(truckAngle * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);

    draw_model(&(scene->truck));
    
    show_manual(scene);
    shadow(0,0,2);
}

void draw_origin()
{
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

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

    glColor3f(1, 1, 1);

    glEnd();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
}
void draw_ground(Scene *scene){
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id1);

    // Háttér kirajzolása textúrával
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-100, -100, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(100, -100, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(100, 100, 0.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-100, 100, 0.0);
    glEnd();

    //glDeleteTextures(1, &grassTexture);

    // Textúra deaktiválása
    glDisable(GL_TEXTURE_2D);
}

void updateTruck(float* x, float* z, float* angle, float* speed, float* acceleration, float* deceleration, float* maxSpeed) {
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
        // Sebesség csökkentése a deceleration értékével
    if (!keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_DOWN]) {
        if (*speed > 0.0f) {
            *speed -= *deceleration;
        } else if (*speed < 0.0f) {
            *speed += *deceleration;
        }

        if (fabsf(*speed) < *deceleration) {
            *speed = 0.0f;
        }
    }

    // Kanyarodás billentyűzetről
    if (keyState[SDL_SCANCODE_LEFT]) {
        *angle += 0.2f * fabsf(*speed);  // Kis szögben kanyarodik
    }
    if (keyState[SDL_SCANCODE_RIGHT]) {
        *angle -= 0.2f * fabsf(*speed);  // Kis szögben kanyarodik
    }

    // Sebesség növelése az acceleration értékével
    if (keyState[SDL_SCANCODE_UP]) {
        if (*speed >= 0.0f) {
            *speed += *acceleration;
        } else {
            *speed += *deceleration;  // Fékezésből előre haladásra
        }

        if (*speed > *maxSpeed) {
            *speed = *maxSpeed;
        }
    }

    // Sebesség csökkentése az acceleration értékével
    if (keyState[SDL_SCANCODE_DOWN]) {
        if (*speed <= 0.0f) {
            *speed -= *acceleration;
        } else {
            *speed -= *deceleration;  // Fékezésből hátra haladásra
        }

        if (*speed < -(*maxSpeed)) {
            *speed = -(*maxSpeed);
        }
    }
    // Pozíció frissítése a sebesség és szög alapján
    float deltaX = *speed * sin(*angle);
    float deltaZ = *speed * cos(*angle);

    wheelAngle += truckSpeed * 10.0f;

    *x += deltaX;
    *z += deltaZ;
}
void draw_skybox(Scene *scene)
{
    glPushAttrib(GL_ENABLE_BIT);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, scene->sky2);  
    glBegin(GL_QUADS);

    // alsó oldal
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-100, -100, -100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(100, -100, -100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(100, 100, -100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-100, 100, -100);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, scene->sky1);
    glBegin(GL_QUADS);

    //felső
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-100, -100, 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-100, 100, 100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(100, 100, 100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(100, -100, 100);


    glEnd();
    glBindTexture(GL_TEXTURE_2D, scene->sky4);
    glBegin(GL_QUADS);


    // Harmadik oldal (right)
    
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-100, -100, 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-100, -100, -100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-100, 100, -100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-100, 100, 100);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, scene->sky6);
    glBegin(GL_QUADS);

    // Negyedik oldal (left)
    
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(100, -100, -100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(100, -100, 100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(100, 100, 100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(100, 100, -100);
    
    glEnd();
    glBindTexture(GL_TEXTURE_2D, scene->sky5);
    glBegin(GL_QUADS);

    // Ötödik oldal (back)
    
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-100, 100, -100);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(100, 100, -100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(100, 100, 100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-100, 100, 100);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, scene->sky3);

    glBegin(GL_QUADS);
    // Hatodik oldal (front)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-100, -100, -100);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(100, -100, -100);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(100, -100, 100);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-100, -100, 100);

    glEnd();
    
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glPopAttrib();
}
void show_manual(Scene *scene)
{
    static bool showManual = false; // Boolean változó a képernyőn való megjelenítés állapotának tárolására
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_M]) {
        // Az "m" gomb lenyomására a showManual értékét invertáljuk
        showManual = !showManual;
    }



    if (showManual) {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->txt);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    //glEnable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST); 
    }
    
}
void shadow(float x, float y, float radius) {
   int i;
	int triangleAmount = 200; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * M_PI;
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); 
    glTranslatef(0.0f, 0.0f, 0.69f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
    glPopMatrix();
}