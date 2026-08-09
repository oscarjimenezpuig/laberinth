#include "laberinth.h"

struct Pair {
    unsigned int a : 4; 
    unsigned int b : 4;
};

struct Laberinth{
    unsigned int r,c;
    struct Pair* pair;
};

static struct Pair* pamal(unsigned int r,unsigned int c) {
    //consigue el espacio de memoria donde se guarda el laberinto
    unsigned int area=r*c;
    unsigned int pairs=(area%2)?(area+1)/2:area/2;
    struct Pair* p=malloc(sizeof(struct Pair)*pairs);
    if(p) {
        struct Pair* ptr=p;
        while(ptr!=p+(pairs)) *ptr++=(struct Pair){0,0};
    }
    return p;
}

static struct Pair* poget(struct Laberinth* l,unsigned int r,unsigned int c,char* h) {
    //devuelve puntero del laberinto de la posicion, en r devuelve a o b dependiendo de la habitacion
    if(r<l->r && c<l->c) {
        unsigned int pos=c+r*l->c;
        *h=(pos%2)?'b':'a';
        return l->pair+(pos/2);
    }
    return NULL;
}

static int movdir(struct Laberinth* l,Direction dir,int* r,int * c) {
    //desplaza las coordenadas siguiendo una direccion
    int pr=*r;
    int pc=*c;
    switch(dir) {
        case NORTH:
            pr-=1;
            break;
        case SOUTH:
            pr+=1;
            break;
        case EAST:
            pc+=1;
            break;
        case WEST:
            pc-=1;
            break;
    }
    if(pc>=0 && pc<l->c && pr>=0 && pr<l->r) {
        *r=pr;
        *c=pc;
        return 1;
    }
    return 0;
}

static int posocu(struct Laberinth* l,int r,int c) {
    //dice si una posicion esta ocupada
    char h;
    struct Pair* p=poget(l,r,c,&h);
    if(h=='a') return (p->a!=0);
    else return (p->b!=0);
}

static int habcon(struct Laberinth* l,Direction dir,int* r,int* c) {
    //saliendo de la posicion r,c miramos de conectar siguiendo la direccion dir
    int pr=*r;
    int pc=*c;
    if(movdir(l,dir,&pr,&pc)) {
        if(!posocu(l,pr,pc)) {
            char tip;
            struct Pair* pi=poget(l,*r,*c,&tip);
            if(tip=='a') pi->a|=dir;
            else pi->b|=dir;
            struct Pair* pf=poget(l,pr,pc,&tip);
            if(tip=='a') pf->a|=(8/dir);
            else pf->b|=(8/dir);
            *r=pr;
            *c=pc;
            return 1;
        }
    }
    return 0;
}

static void avcrom(struct Laberinth* l,int r,int c) {
    //funcion que va conectando habitaciones de manera recursiva
    Direction dir,dirini;
    dir=dirini=NORTH<<(rand()%4);
    do {
        if(habcon(l,dir,&r,&c)) {
            avcrom(l,r,c);
        }
        if(dir==SOUTH) dir=NORTH;
        else dir=dir<<1;
    }while(dir!=dirini);
}

struct Laberinth* lab_new(unsigned int rws,unsigned int cls) {
    struct Laberinth* l=NULL;
    struct Pair* p=pamal(rws,cls);
    if(p) {
        if((l=malloc(sizeof(struct Laberinth)))) {
            l->pair=p;
            l->r=rws;
            l->c=cls;
            avcrom(l,rand()%rws,rand()%cls);
        } else {
            free(p);
        }
    }
    return l;
}

void lab_del(struct Laberinth** l) {
    if(l && *l) {
        free((*l)->pair);
        free(*l);
        *l=NULL;
    }
}


unsigned int lab_get(struct Laberinth* l,unsigned int r,unsigned int c) {
    char tip;
    struct Pair* p=poget(l,r,c,&tip);
    return (tip=='a')?p->a:p->b;
}

