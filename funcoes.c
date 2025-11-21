#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

// Correção para funcionar Sleep/sleep em Windows e Linux sem erros
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(x) Sleep(x * 1000)
#else
    #include <unistd.h>
    #define SLEEP_MS(x) sleep(x)
#endif

// ================= NARRATIVA E UI =================

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar_tela() {
    printf("\n[Pressione Enter...]");
    while (getchar() != '\n');
}

void introducao() {
    limpar_tela();
    printf("\n");
    printf(COR_AZUL "  //===========================\\\\\n");
    printf("  ||                           ||\n");
    printf("  ||        WETWORK INC.       ||\n");
    printf("  ||                           ||\n");
    printf("  \\\\===========================//\n");
    printf("\n" COR_RESET);
    SLEEP_MS(1);
}

void exibir_boot_sequence() {
    printf(COR_VERDE "> INICIALIZANDO SO DA ESTACAO...\n");
    SLEEP_MS(1);
    printf("> SINCRONIZANDO COM A REDE DE CONTRATOS...\n");
    SLEEP_MS(1);
    printf(COR_AMARELO "> AVISO: FUNDOS BAIXOS.\n" COR_RESET);
    printf(COR_AMARELO "> AVISO: ALOJAMENTOS INOPERANTES.\n" COR_RESET);
    SLEEP_MS(1);
}

void prologo_historia() {
    char escolha;
    printf("---------------------------------------------------\n");
    printf("Mais um dia em Todo Lugar.\n");
    printf("Voce e Keume, um mero trabalhador de uma guilda Intergalatica.\n");
    printf("Voce trabalha todos os dias enviando mercenarios para missoes em que a policia nao da importancia.\n");
    printf("Antes, voce era um deles, agora foi promovido, depois que uma Duna acabou decepando e Ingerindo uma de suas pernas.\n\n");
    printf("Voce ouve gritos e sente um cheiro forte de bebida. Henaume entra, bebado e furioso.\n");
    printf("'KeUmE!! Me Ve UmA miSsAo! As HaLbAnEsAs paSsArAm a MaO eM mIm E nO mEu dINhEirO!'\n");
    printf("'Voce nao vai ter nada aqui, suma antes que eu te de um tiro na bunda.'\n");
    printf("\nEle tenta agarrar seu pescoco.\n");
    
    while(1){
        printf(COR_VERMELHO "\n- ACAO RAPIDA -\n" COR_RESET);
        printf("X - Puxar a arma e atirar.\n");
        printf("Y - Jogar garrafa na cabeca dele.\n");
        printf("Insira: ");
        scanf(" %c", &escolha);
        getchar(); // Limpa o buffer do enter
        
        if(escolha == 'X' || escolha == 'x'){
            printf("\nVoce mata seu antigo colega.\n");
            printf("- A familia dele vai lembrar disso -\n");
            printf("\n'Enfim, vamos começar os trabalhos...'\n");
            break;
        } else if(escolha == 'Y' || escolha == 'y'){
            printf("\nVoce o nocauteia e o joga na rua.\n");
            printf("- Ele vai lembrar disso -\n");
            printf("'Enfim, vamos começar os trabalhos...'\n");
            break;
        } else {
            printf("Opcao invalida.\n");
        }
    }
    pausar_tela();
}

// ================= MAPA E ZONAS =================

void resetar_mapa(char mapa[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            mapa[i][j] = 'o';
        }
    }
}

void gerar_missao_mapa(char mapa[4][4], int *missao_x, int *missao_y) {
    resetar_mapa(mapa);
    // Gera coordenadas aleatórias de 0 a 3
    *missao_x = rand() % 4;
    *missao_y = rand() % 4;
    
    mapa[*missao_x][*missao_y] = '!';
}

void exibir_mapa(char mapa[4][4]) {
    printf("\n      --- RADAR DA CIDADE ---\n");
    printf("      Zona Perigosa (Norte) ^\n");
    
    for(int i = 0; i < 4; i++) {
        printf("      "); // Indentação
        for(int j = 0; j < 4; j++) {
            if(mapa[i][j] == '!') {
                printf(COR_VERMELHO "[!]" COR_RESET);
            } else {
                // Pinta diferente dependendo da zona (linhas 0-1 ou 2-3)
                if (i < 2) printf(COR_ROXO " o " COR_RESET); // Zona Perigosa
                else       printf(COR_AZUL " o " COR_RESET); // Zona Corporativa
            }
        }
        // Legenda lateral
        if(i == 1) printf("  <-- Bares e Becos");
        if(i == 2) printf("  <-- Escritorios");
        printf("\n");
    }
    printf("      Zona Corporativa (Sul) v\n\n");
}

// ================= RESOLUÇÃO DA MISSÃO =================

void resolver_missao(Capanga *escolhido, int mx, int my) {
    printf("\n================ RELATORIO DA MISSAO ================\n");
    printf("Local: Setor [%d,%d]\n", mx, my);
    
    int valor_atributo = 0;
    char nome_atributo[20];
    const char *descricao_evento;

    // --- BANCO DE DADOS DE TEXTOS ---
    const char *textos_forca[] = {
        "Uma gangue rival cercou o alvo em um beco sem saida.",
        "E necessario arrombar uma porta reforcada de aco.",
        "O alvo e um pugilista cibernetico descontrolado.",
        "Transporte de carga pesada sob fogo inimigo."
    };
    const char *textos_agilidade[] = {
        "O sistema de seguranca tem lasers de movimento.",
        "Uma perseguicao em alta velocidade pelos telhados.",
        "E preciso roubar o chip sem ser notado pelos guardas.",
        "Desarmar uma bomba com temporizador acelerado."
    };
    const char *textos_intelecto[] = {
        "Hackear o firewall da corporacao Arasaka.",
        "Decifrar um codigo criptografado antigo.",
        "Consertar um drone de combate avariado no campo.",
        "Investigacao forense em uma cena de crime limpa."
    };
    const char *textos_carisma[] = {
        "Convencer o seguranca a liberar a passagem.",
        "Negociar o preco de refens com sequestradores.",
        "Seduzir ou enganar um executivo para obter a senha.",
        "Interrogar um informante sem usar violencia."
    };

    int indice_texto = rand() % 4;

    if (mx <= 1) {
        printf(COR_ROXO "ZONA: BARES E BECOS (Violencia Urbana)\n" COR_RESET);
        if (rand() % 2 == 0) {
            strcpy(nome_atributo, "Forca");
            valor_atributo = escolhido->forca;
            descricao_evento = textos_forca[indice_texto];
        } else {
            strcpy(nome_atributo, "Agilidade");
            valor_atributo = escolhido->agilidade;
            descricao_evento = textos_agilidade[indice_texto];
        }
    } else {
        printf(COR_AZUL "ZONA: SETOR CORPORATIVO (Alta Tecnologia)\n" COR_RESET);
        if (rand() % 2 == 0) {
            strcpy(nome_atributo, "Intelecto");
            valor_atributo = escolhido->intelecto;
            descricao_evento = textos_intelecto[indice_texto];
        } else {
            strcpy(nome_atributo, "Carisma");
            valor_atributo = escolhido->carisma;
            descricao_evento = textos_carisma[indice_texto];
        }
    }

    // --- CÁLCULO DE DIFICULDADE HARDCORE ---
    
    // 1. Soma total dos atributos (O quão forte o personagem é no geral)
    int soma_atributos = escolhido->forca + escolhido->agilidade + 
                         escolhido->intelecto + escolhido->carisma;
    
    // 2. Scaling Rápido
    int dificuldade = (soma_atributos / 2) + 2 + (rand() % 4); 
    
    printf("\nSituacao: \"%s\"\n", descricao_evento);
    printf("Atributo Testado: %s\n", nome_atributo);
    printf("Seu Nivel: %d | Dificuldade: %d\n", valor_atributo, dificuldade);
    
    SLEEP_MS(1);
    printf("Executando...\n");
    SLEEP_MS(1);
    
    // --- RESOLUÇÃO COM FALHA CRÍTICA ---
    // Dado d6 (0 a 5)
    int dado = rand() % 6; 
    
    // Fator "Falha Crítica": Se tirar 0 no dado, falha automaticamente.
    if (dado == 0) {
        printf(COR_VERMELHO ">>> FALHA CRITICA (Azar) <<<\n" COR_RESET);
        printf("Rolagem de Sorte: 0 (Maldicao!)\n");
        printf("Mesmo com habilidade, o imprevisivel aconteceu.\n");
    } 
    else {
        int resultado_final = dado + valor_atributo;
        printf("Rolagem de Sorte (d6): %d + Atributo: %d = Total: %d\n", dado, valor_atributo, resultado_final);
        
        if (resultado_final >= dificuldade) {
            printf(COR_VERDE ">>> SUCESSO! <<<\n" COR_RESET);
            printf("Recompensa: +1 XP\n");
            escolhido->xp_disponivel++;
        } else {
            printf(COR_VERMELHO ">>> FALHA NA MISSAO <<<\n" COR_RESET);
            printf("O desafio era maior que a habilidade atual.\n");
        }
    }
    printf("=====================================================\n");
}

// ================= ARQUIVOS E SISTEMA =================

// Função auxiliar de recursão
int decifrar_codigo_recursivo(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * decifrar_codigo_recursivo(n - 1);
}

void salvar_jogo(Capanga *lista, int quantidade) {
    FILE *arquivo = fopen("savegame.dat", "wb"); // Write Binary
    if (arquivo == NULL) {
        printf(COR_VERMELHO "Erro ao abrir arquivo para salvar.\n" COR_RESET);
        return;
    }
    // Grava o bloco de memória inteiro dos capangas
    fwrite(lista, sizeof(Capanga), quantidade, arquivo);
    fclose(arquivo);
    printf(COR_VERDE "\n>> PROGRESSO SALVO NO DISCO RIGIDO. <<\n" COR_RESET);
}

int carregar_jogo(Capanga *lista, int quantidade) {
    FILE *arquivo = fopen("savegame.dat", "rb"); // Read Binary
    if (arquivo == NULL) {
        printf(COR_AMARELO "\n>> NENHUM SAVE ENCONTRADO. INICIANDO NOVO JOGO. <<\n" COR_RESET);
        return 0;
    }
    fread(lista, sizeof(Capanga), quantidade, arquivo);
    fclose(arquivo);
    printf(COR_VERDE "\n>> DADOS RECUPERADOS DO BACKUP. <<\n" COR_RESET);
    return 1;
}

void tentar_hackear_sistema(Capanga *equipe) {
    limpar_tela();
    printf("=== FIREWALL DE SEGURANCA NIVEL 5 ===\n");
    printf("O sistema pede o codigo fatorial de protecao.\n");
    
    int desafio = 5; // Fatorial de 5 é 120
    
    // A recursão acontece aqui:
    int resposta_correta = decifrar_codigo_recursivo(desafio);
    
    printf("Digite o codigo de acesso (Dica: Fatorial de %d): ", desafio);
    int tentativa;
    scanf("%d", &tentativa);
    getchar();

    if(tentativa == resposta_correta) {
        printf(COR_VERDE "\nACESSO CONCEDIDO. RECURSAO BEM SUCEDIDA.\n" COR_RESET);
        printf("Voce ganhou acesso aos logs do servidor... e hackeou contas bancarias.\n");
        
        printf(COR_AMARELO "\n>> RECOMPENSA: 2 PONTOS DE XP TRANSFERIDOS! <<\n" COR_RESET);
        printf("Para qual capanga deseja enviar os dados de experiencia?\n");
        
        mostrar_status_capangas(equipe);
        
        printf("Escolha o capanga (1-3): ");
        int id_escolhido;
        scanf("%d", &id_escolhido);
        getchar(); // Limpa buffer

        if (id_escolhido >= 1 && id_escolhido <= 3) {
            equipe[id_escolhido-1].xp_disponivel += 2;
            printf(COR_VERDE "XP transferido com sucesso para %s!\n" COR_RESET, equipe[id_escolhido-1].nome);
        } else {
            printf(COR_VERMELHO "Erro de transmissao: Capanga invalido. XP perdido na rede.\n" COR_RESET);
        }

    } else {
        printf(COR_VERMELHO "ACESSO NEGADO. PROTOCOLO DE DEFESA ATIVO.\n" COR_RESET);
    }
    pausar_tela();
}

// Em funcoes.c

void menu_dialogo(Capanga *equipe) {
    limpar_tela();
    printf("=== ACESSANDO ARQUIVOS PESSOAIS (HR) ===\n");
    
    // Mostra a lista para o jogador escolher
    mostrar_status_capangas(equipe);

    printf("\nSelecione o funcionario para ver o Dossie (1-3) ou 0 para voltar: ");
    int id;
    scanf("%d", &id);
    getchar();

    if (id == 0) return;

    if (id < 1 || id > 3) {
        printf(COR_VERMELHO "Erro: Arquivo nao encontrado.\n" COR_RESET);
        pausar_tela();
        return;
    }

    // Ajusta para índice do vetor (0 a 2)
    int index = id - 1;
    Capanga *c = &equipe[index];

    limpar_tela();
    printf("========================================\n");
    printf(COR_AMARELO "DOSSIE: %s\n" COR_RESET, c->nome);
    printf("========================================\n");
    
    // Exibe estatísticas atuais
    printf("Status Atual:\n");
    printf("FOR: %d | AGI: %d | INT: %d | CAR: %d\n", c->forca, c->agilidade, c->intelecto, c->carisma);
    printf("----------------------------------------\n");
    printf(COR_AZUL "HISTORICO E PERSONALIDADE:\n\n" COR_RESET);

    // Lógica de texto baseada no NOME original (ou posição fixa)
    // Como seus nomes são fixos na inicialização, podemos usar o índice.
    
    switch(index) {
        case 0: // Leume 
            printf("\"Eu bato em coisas. Se não quebrar, quebro de novo.\"\n\n");
            printf("Leume e um ex-operario de demolicao que foi demitido apos\n");
            printf("derrubar o predio errado. Ele nao e muito esperto e tem\n");
            printf("dificuldade com palavras grandes. Ele gosta de colecionar pedras que parecem rostos.\n");
            printf("Ele possui cabelos longos e claros, pele acizentada e se parece muito com um louva-deus.\n");
            break;

        case 1: // Kchatrume 
            printf("\"'Todo mundo tem um preco. O meu é uma mulher bonita.'\"\n\n");
            printf("Kchatrume ja foi um vendedor de carros flutuantes usados,\n");
            printf("mas depois de receber o dinheiro, colocava uma micro-bomba e explodia\n");
            printf("o automóvel. Evita combate fisico sempre que possivel para nao estragar o terno.\n");
            printf("Ele possue olhos amarelados, pele acizentada e uma boca preta, por conta do cigarro.\n");
            break;

        case 2: // Recca 
            printf("\"'Nao suporto gente mesquinha como os dessa equipe.'\"\n\n");
            printf("Nao natural de Todo Lugar.Recca viveu no subsolo conectada a rede neural por 15 anos.\n");
            printf("Ela e paranoica, odeia luz solar e consome quantidades perigosas\n");
            printf("de energetico. E a unica que sabe configurar o relogio do microondas da base.\n");
            printf("Ela tem a aparencia e o tamanho de uma lontra, fofinha e perigosa :}.\n");
            break;
            
        default:
            printf("Dados corrompidos. Nenhuma informacao disponivel.\n");
            break;
    }

    printf("\n========================================\n");
    pausar_tela();
}