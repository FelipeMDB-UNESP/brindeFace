#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


typedef struct letra{
    char conteudo;
    struct letra *prox;
}Letra;

typedef struct{
    Letra *ultimo;
    Letra *primeiro;

}Painel;

Letra *inserir_letra_no_painel(Painel *lista, Letra *l){

    if (lista == NULL || l == NULL){
        return NULL;
    }

    if (lista->primeiro == NULL){
        lista->primeiro = l;
        lista->ultimo = l;
    }
    else {
        lista->ultimo->prox = l;
        lista->ultimo = l;
    }

    return lista->primeiro;
}

void printar_painel(Painel *lista){
    
    if(lista == NULL || lista->primeiro == NULL){
        printf("Lista vazia");
    }
    else {
        Letra *aux = lista->primeiro;
        while(aux != NULL){
            printf(" %c", aux->conteudo);
            aux = aux->prox;
        }
    }
}

Painel *letras_padrao(Painel *lista){
    if(lista->primeiro == NULL){
        
        Letra *f = malloc(sizeof(Letra));
        Letra *a = malloc(sizeof(Letra));
        Letra *c = malloc(sizeof(Letra));
        Letra *e = malloc(sizeof(Letra));
        f->conteudo = 'F';
        a->conteudo = 'A';
        c->conteudo = 'C';
        e->conteudo = 'E';
        f->prox = a;
        a->prox = c;
        c->prox = e;
        e->prox = NULL;
        lista->primeiro = f;
        lista->ultimo = e;
    }else{
        printf("A lista deve estar vazia para se inserir as letras padrao");
    }

    return lista;
}

int calcular_premiados(Painel *painel){

    int qtd_premiados = 0;

    int loop = 0;
    char conjunto_anterior[4];
    char conjunto_atual[4];
    Letra *aux = painel->primeiro;
    do{
        if(loop < 4 ){

            conjunto_anterior[loop] = aux->conteudo;
            loop++;
            aux = aux->prox;
        }else if(loop > 3 && loop < 8){

            conjunto_atual[loop - 4] = aux->conteudo;
            loop++;
            aux = aux->prox;
        }else{

            if(conjunto_anterior[0] == conjunto_atual[3] 
            && conjunto_anterior[1] == conjunto_atual[2] 
            && conjunto_anterior[2] == conjunto_atual[1] 
            && conjunto_anterior[3] == conjunto_atual[0]){

                qtd_premiados =  qtd_premiados + 1;
            }
            loop = 4; 
            conjunto_anterior[0] = conjunto_atual[0]; 
            conjunto_anterior[1] = conjunto_atual[1]; 
            conjunto_anterior[2] = conjunto_atual[2]; 
            conjunto_anterior[3] = conjunto_atual[3];

        } 
    }while(aux != NULL || loop != 4);
    return qtd_premiados;
}



int main(){

    
    while (true){

        int qtd_participantes = 0;
        Painel *painel_de_letras = malloc(sizeof(Painel));
        letras_padrao(painel_de_letras);
        printf("Digite [0] para encerrar o programa\n");
        printf("Quantos participantes deseja inserir?\n");
        scanf(" %d", &qtd_participantes);
        if (qtd_participantes == 0){
            return 0;
        }
        else {
            for (int i = 0; i < qtd_participantes; i++) {
                char letras[50];
                Letra *l;
                printf("Digite as letras a serem inseridas no painel:\n");
                scanf(" %[^\n]", letras);

                char *letra = strtok(letras, " ");
                while (letra != NULL) {
                    l = malloc(sizeof(Letra));
                    l->conteudo = letra[0];
                    l->prox = NULL;
                    inserir_letra_no_painel(painel_de_letras, l);
                    letra = strtok(NULL, " ");
                }
                printf("\n--------------------\n");
                printar_painel(painel_de_letras);
                printf("\n--------------------\n");
            }

            int premiados = calcular_premiados(painel_de_letras);
            printf("Temos %d vencedor(es) de brindes\n\n", premiados);
            free(painel_de_letras);
        }
    }
}
