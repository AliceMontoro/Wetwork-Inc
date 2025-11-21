#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"
#include "structs.h"

int main() {
    srand(time(NULL));
    char mapa[4][4];

    // 1. ALOCAÇÃO DINÂMICA
    Capanga *meus_capangas; 
    meus_capangas = alocar_capangas(TOTAL_CAPANGAS);

    limpar_tela();
    introducao();
    
    // 2. ARQUIVOS - Carregar Save
    printf("\nProcurando save local...\n");
    if(carregar_jogo(meus_capangas, TOTAL_CAPANGAS)) {
        // Carregado com sucesso
    }
    
    exibir_boot_sequence();
    
    printf("\n[Pressione Enter para entrar na memoria do Admin...]\n");
    getchar();

    limpar_tela();       
    prologo_historia(); 

    int rodando = 1;
    int missao_x, missao_y;
    
    while(rodando) {
        limpar_tela();
        printf("=== WETWORK INC. - PAINEL DE CONTROLE ===\n");
        printf("1. Buscar Nova Missao (Gerar Mapa)\n");
        printf("2. Treinar Equipe (Gastar XP)\n");
        printf("3. Ver Status da Equipe\n");
        printf("4. Salvar Progresso (Arquivos)\n");
        printf("5. Hackear Mainframe (Recursao + XP)\n");
        printf("6. Equipe Z\n"); 
        printf("0. Sair do Sistema\n");
        printf("Escolha: ");
        
        int opcao;
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                gerar_missao_mapa(mapa, &missao_x, &missao_y);
                limpar_tela();
                exibir_mapa(mapa);
                
                mostrar_status_capangas(meus_capangas);
                printf("\nQuem voce envia para o setor [%d,%d]? (1-3): ", missao_x, missao_y);
                int id_capanga;
                scanf("%d", &id_capanga);
                getchar();
                
                if(id_capanga >= 1 && id_capanga <= 3) {
                    resolver_missao(&meus_capangas[id_capanga-1], missao_x, missao_y);
                } else {
                    printf("Capanga invalido.\n");
                }
                pausar_tela();
                break;

            case 2:
                limpar_tela();
                mostrar_status_capangas(meus_capangas);
                printf("\nQuem vai treinar? (1-3): ");
                int id_treino;
                scanf("%d", &id_treino);
                getchar();
                if(id_treino >= 1 && id_treino <= 3) {
                    upar_atributo(&meus_capangas[id_treino-1]);
                }
                pausar_tela();
                break;

            case 3:
                limpar_tela();
                mostrar_status_capangas(meus_capangas);
                pausar_tela();
                break;

            case 4: // USO DE ARQUIVOS
                salvar_jogo(meus_capangas, TOTAL_CAPANGAS);
                pausar_tela();
                break;

            case 5: // USO DE RECURSÃO
                tentar_hackear_sistema(meus_capangas);
                break;

            case 6: // <--- NOVO CASO ADICIONADO
                menu_dialogo(meus_capangas);
                break;

            case 0:
                rodando = 0;
                printf("Deseja salvar antes de sair? (1-Sim / 0-Nao): ");
                int salvar;
                scanf("%d", &salvar);
                if(salvar == 1) salvar_jogo(meus_capangas, TOTAL_CAPANGAS);
                
                // IMPORTANTE: Liberar memória alocada
                free(meus_capangas);
                
                printf("Desligando terminal...\n");
                break;

            default:
                printf("Comando desconhecido.\n");
                pausar_tela();
        }
    }
    
    return 0;
}