#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Brick
{
    float a;
    float b;
    float c;
};

struct Brick set_size();
float calc_volume(struct Brick b);
float calc_surface(struct Brick b);
bool square(struct Brick b);

int main()
{
    struct Brick b1;
    b1=set_size();
    printf("A=%f, B=%f, C=%f\n",b1.a,b1.b,b1.c);
    float volume;
    volume=calc_volume(b1);
    printf("Terfogat= %f\n",volume);
    float surface;
    surface= calc_surface(b1);
    printf("Felulet= %f\n",surface);
    bool squareis;
    squareis=square(b1);
    printf("Van negyzet alalu lapja= %d\n",squareis);
    return 0;
}

struct Brick set_size(){
    struct Brick b;
    char ch;
    int ok;
    do{
        ok=1;
        printf("Az A oldal hossz:");
        if((scanf("%f", &b.a) != 1) || b.a==0) {
           printf("error\n");
           ok=0;
           while (((ch=getchar())) != '\n');
            }
    }while(!ok);
    do{
        ok=1;
        printf("Az B oldal hossz:");
        if((scanf("%f", &b.b) != 1) || b.b==0) {
           printf("error\n");
           ok=0;
           while (((ch=getchar())) != '\n');
            }
    }while(!ok);
    do{
        ok=1;
        printf("A C oldal hossz:");
        if((scanf("%f", &b.c) != 1) || b.c==0) {
           printf("error\n");
           ok=0;
           while (((ch=getchar())) != '\n');
            }
    }while(!ok);
    return b;
}

float calc_volume(struct Brick b){
    float v;
    v=b.a*b.b*b.c;
return v;
}

float calc_surface(struct Brick b){
    float A;
    A= 2*(b.a*b.b+b.a*b.c+b.b*b.c);
return A;
}
bool square(struct Brick b){
    bool s=false;
    if(b.a==b.b || b.a==b.c || b.b==b.c){
        s=true;
    }
return s;
}
