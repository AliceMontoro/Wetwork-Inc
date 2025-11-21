#include "structs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> // Necessário para malloc

// 1. Função que preenche os dados (usada tanto na alocação quanto reset)
void inicializar_capangas(Capanga lista[]) {
    // Leume: O tank (Força)
    strcpy(lista[0].nome, "Leume");
    lista[0].carisma = 1;
    lista[0].agilidade = 1;
    lista[0].forca = 2;
    lista[0].intelecto = 0;
    lista[0].xp_disponivel = 0;

    // Kchatrume: O diplomata (Carisma)
    strcpy(lista[1].nome, "Kchatrume");
    lista[1].carisma = 2;
    lista[1].agilidade = 1;
    lista[1].forca = 0;
    lista[1].intelecto = 1;
    lista[1].xp_disponivel = 0;

    // Recca: O especialista (Agilidade/Intelecto)
    strcpy(lista[2].nome, "Recca");
    lista[2].carisma = 0;
    lista[2].agilidade = 2;
    lista[2].forca = 1;
    lista[2].intelecto = 2;
    lista[2].xp_disponivel = 0;
}

// 2. Função que aloca memória e já chama a inicialização
Capanga* alocar_capangas(int quantidade) {
    // Alocação Dinâmica
    Capanga *lista = (Capanga*) malloc(quantidade * sizeof(Capanga));
    
    if(lista == NULL) {
        printf("Erro fatal: Memoria insuficiente.\n");
        exit(1);
    }

    // Reutiliza a função acima para não repetir código
    inicializar_capangas(lista);

    return lista;
}

void mostrar_status_capangas(Capanga lista[]) {
    printf("\n=== EQUIPE WETWORK ===\n");
    for(int i = 0; i < TOTAL_CAPANGAS; i++) {
        printf("%d. %-10s | CAR:%d AGI:%d FOR:%d INT:%d | XP: %d\n", 
               i+1, lista[i].nome, 
               lista[i].carisma, lista[i].agilidade, 
               lista[i].forca, lista[i].intelecto,
               lista[i].xp_disponivel);
    }
    printf("======================\n");
}

void upar_atributo(Capanga *c) {
    if (c->xp_disponivel <= 0) {
        printf("\n>> %s nao tem XP suficiente para treinar!\n", c->nome);
        return;
    }

    printf("\n--- TREINAMENTO DE %s ---\n", c->nome);
    printf("1. Carisma (%d/%d)\n", c->carisma, MAX_NIVEL);
    printf("2. Agilidade (%d/%d)\n", c->agilidade, MAX_NIVEL);
    printf("3. Forca (%d/%d)\n", c->forca, MAX_NIVEL);
    printf("4. Intelecto (%d/%d)\n", c->intelecto, MAX_NIVEL);
    printf("Escolha o atributo para evoluir: ");
    
    int opcao;
    scanf("%d", &opcao);
    getchar(); // Limpar buffer

    int *atributo = NULL;
    
    switch(opcao) {
        case 1: atributo = &c->carisma; break;
        case 2: atributo = &c->agilidade; break;
        case 3: atributo = &c->forca; break;
        case 4: atributo = &c->intelecto; break;
        default: printf("Opcao invalida.\n"); return;
    }

    if (*atributo >= MAX_NIVEL) {
        printf("\n>> Este atributo ja esta no maximo!\n");
    } else {
        (*atributo)++;
        c->xp_disponivel--;
        printf("\n>> SUCESSO! %s melhorou suas habilidades.\n", c->nome);
    }
}