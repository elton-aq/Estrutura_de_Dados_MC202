#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dns.h"

int main() {
    int i, consultas, num_domin;
    char dominio[101], servidor[16];
    char dominio_user[101], servidor_user[16];
    char get[4], from[5];
    p_abb arvore;
    p_user users, usuario;

    scanf("%d", &consultas);
    scanf("%d", &num_domin);

    arvore = cria_avr();

    for(i=0; i<num_domin; i++) {
        scanf("%s %s", dominio, servidor);
        arvore = inserir_abb(arvore, dominio, servidor);
        arvore = mantem_preto_abb(arvore);
    }

    scanf("%d", &num_domin);

    users = cria_users();

    for(i=0; i<num_domin; i++) {
        scanf("%s %s %s %s", get, dominio_user, from, servidor_user);
        usuario = acha_user(users, servidor_user);
        if(usuario == NULL) {
            users = inserir_user(users, servidor_user, consultas);
            users = mantem_preto_user(users);
            usuario = acha_user(users, servidor_user);
        }
        if(usuario->buscas > 0) {       /*confere se o usuario ainda pode buscar por dominios*/
            busca(arvore, usuario, dominio_user);
        } else {
            printf("FORBIDDEN %s FROM %s\n", dominio_user, servidor_user);
            usuario->buscas -= 1;
        }
            
    }

    destroi_arvore(arvore);
    destroi_usuarios(users);

    return 0;
}

/*--------------------------- arvore de dominios ---------------------------*/

p_abb cria_avr() {
    return NULL;
}

int vermelho_abb(p_abb elemento) {
    if (elemento == NULL)
        return 0;
    return elemento->cor == VERMELHO;
}

int preto_abb(p_abb elemento) {
    if (elemento == NULL)
        return 1;
    return elemento->cor == PRETO;
}

p_abb inserir_abb(p_abb arvore, char dominio[], char servidor[]) {
    if (arvore == NULL) {
        p_abb novo;
        novo = malloc(sizeof(abb));
        novo->esq = novo->dir = NULL;
        strcpy(novo->dominio, dominio);
        strcpy(novo->servidor, servidor);
        novo->cor = VERMELHO;
        return novo;
    } else {
        if (strcmp(dominio, arvore->dominio) < 0) {
            arvore->esq = inserir_abb(arvore->esq, dominio, servidor);
        } else {
            arvore->dir = inserir_abb(arvore->dir, dominio, servidor);
        }
            
        if (vermelho_abb(arvore->dir) && preto_abb(arvore->esq))
            arvore = roda_esquerda_abb(arvore);
        if (vermelho_abb(arvore->esq) && vermelho_abb(arvore->esq->esq))
            arvore = roda_direita_abb(arvore);
        if (vermelho_abb(arvore->esq) && vermelho_abb(arvore->dir))
            sobe_vermelho_abb(arvore);
    }
    return arvore;
}

p_abb mantem_preto_abb(p_abb arvore) {
    arvore->cor = PRETO;
    return arvore;
}

p_abb roda_esquerda_abb(p_abb arvore) {
    p_abb filho = arvore->dir;
    arvore->dir = filho->esq;
    filho->esq = arvore;
    filho->cor = arvore->cor;
    arvore->cor = VERMELHO;
    return filho;
}

p_abb roda_direita_abb(p_abb arvore) {
    p_abb filho = arvore->esq;
    arvore->esq = filho->dir;
    filho->dir = arvore;
    filho->cor = arvore->cor;
    arvore->cor = VERMELHO;
    return filho;
}

void sobe_vermelho_abb(p_abb arvore) {
    arvore->cor = VERMELHO;
    arvore->esq->cor = PRETO;
    arvore->dir->cor = PRETO;
}

void destroi_arvore(p_abb arvore) {
    if(arvore->esq != NULL)
        destroi_arvore(arvore->esq);   
    if(arvore->dir != NULL)
        destroi_arvore(arvore->dir);
    free(arvore);    
}

/*--------------------------- arvore de usuarios ---------------------------*/

p_user cria_users() {
    return NULL;
}

int vermelho_user(p_user elemento) {
    if (elemento == NULL)
        return 0;
    return elemento->cor == VERMELHO;
}

int preto_user(p_user elemento) {
    if (elemento == NULL)
        return 1;
    return elemento->cor == PRETO;
}

p_user inserir_user(p_user arvore, char servidor[], int buscas) {
    if (arvore == NULL) {
        p_user novo;
        novo = malloc(sizeof(user));
        novo->esq = novo->dir = NULL;
        novo->buscas = buscas;
        strcpy(novo->servidor, servidor);
        novo->cor = VERMELHO;
        return novo;
    } else {
        if (strcmp(servidor, arvore->servidor) < 0)
            arvore->esq = inserir_user(arvore->esq, servidor, buscas);
        else
            arvore->dir = inserir_user(arvore->dir, servidor, buscas);

        if (vermelho_user(arvore->dir) && preto_user(arvore->esq))
            arvore = roda_esquerda_user(arvore);
        if (vermelho_user(arvore->esq) && vermelho_user(arvore->esq->esq))
            arvore = roda_direita_user(arvore);
        if (vermelho_user(arvore->esq) && vermelho_user(arvore->dir))
            sobe_vermelho_user(arvore);
    }
    return arvore;
}

p_user mantem_preto_user(p_user arvore) {
    arvore->cor = PRETO;
    return arvore;
}

p_user roda_esquerda_user(p_user arvore) {
    p_user filho = arvore->dir;
    arvore->dir = filho->esq;
    filho->esq = arvore;
    filho->cor = arvore->cor;
    arvore->cor = VERMELHO;
    return filho;
}

p_user roda_direita_user(p_user arvore) {
    p_user filho = arvore->esq;
    arvore->esq = filho->dir;
    filho->dir = arvore;
    filho->cor = arvore->cor;
    arvore->cor = VERMELHO;
    return filho;
}

void sobe_vermelho_user(p_user arvore) {
    arvore->cor = VERMELHO;
    arvore->esq->cor = PRETO;
    arvore->dir->cor = PRETO;
}

void destroi_usuarios(p_user usuario) {
    if(usuario->esq != NULL)
        destroi_usuarios(usuario->esq);   
    if(usuario->dir != NULL)
        destroi_usuarios(usuario->dir);
    free(usuario);    
}
 
/*-------------------------------------------------------------------------------------------------*/

p_user acha_user(p_user arvore, char servidor[]) {
    if (arvore == NULL) {
        return NULL;
    } else if(strcmp(arvore->servidor, servidor) == 0) {
        return arvore;
    } else {
        if(strcmp(servidor, arvore->servidor) < 0)
            return acha_user(arvore->esq, servidor);
        else
            return acha_user(arvore->dir, servidor);
    }
}

void busca(p_abb avr_dominios, p_user usuario, char dominio[]) {
    if (avr_dominios == NULL) {
        printf("NOTFOUND %s FROM %s\n", dominio, usuario->servidor);
        usuario->buscas -= 1;
    } else if(strcmp(avr_dominios->dominio, dominio) == 0) {
        printf("ACCEPTED %s FROM %s RESPOND %s\n", avr_dominios->dominio, usuario->servidor, avr_dominios->servidor);
        usuario->buscas -= 1;
    } else {
        if(strcmp(dominio, avr_dominios->dominio) < 0) {
            busca(avr_dominios->esq, usuario, dominio);
        } else {
            busca(avr_dominios->dir, usuario, dominio);
        }
    }
}