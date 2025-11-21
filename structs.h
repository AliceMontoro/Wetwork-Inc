#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_NIVEL 5
#define TOTAL_CAPANGAS 3

typedef struct {
    char nome[20];
    int carisma;
    int agilidade;
    int forca;
    int intelecto;
    int xp_disponivel; 
    int afinidade; 
} Capanga;

// Função que aloca memória dinamicamente e retorna o ponteiro
Capanga* alocar_capangas(int quantidade);

void inicializar_capangas(Capanga lista[]); 
void upar_atributo(Capanga *c);
void mostrar_status_capangas(Capanga lista[]);

#endif