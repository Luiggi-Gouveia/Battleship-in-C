#include <stdio.h>
#include <stdlib.h>

int main()
{

    // TABULEIROS DOS JOGADORES (Matrizes 5x5 de caracteres)
    char tabuleiro1[5][5];
    char tabuleiro2[5][5];

    // COORDENADAS DOS NAVIOS (3 navios de 1 bloco para cada jogador)
    int navio1Linha[3];
    int navio1Coluna[3];

    int navio2Linha[3];
    int navio2Coluna[3];

    // VariÃ¡veis auxiliares para controle de laÃ§os e coordenadas
    int i, j, k;
    int linha, colunas;
    int posicaoOcupada;

    // Contadores de acertos (O primeiro a chegar a 3 vence)
    int acertos1 = 0;
    int acertos2 = 0;

    // Vetores de caracteres para guardar os nomes dos competidores
    char nome1[30];
    char nome2[30];

    // INICIALIZAÃ‡ÃƒO DOS TABULEIROS
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            tabuleiro1[i][j] = '.';
            tabuleiro2[i][j] = '.';
        }
    }

    // TELA INICIAL DO SISTEMA
    printf("=========================================\n");
    printf("         BATALHA NAVAL MULTIPLAYER       \n");
    printf("=========================================\n");

    /* =========================================================================
       CONSERTO #5: LIMITAÃ‡ÃƒO DE CARACTERES NAS STRINGS (MÃSCARA %29s)
       - Por que arrumamos: O 'scanf("%s")' antigo aceitava strings infinitas.
         Se o usuÃ¡rio digitasse nomes gigantes, ocorria um Buffer Overflow (estouro
         de buffer), corrompendo as variÃ¡veis vizinhas na memÃ³ria. AlÃ©m disso,
         limpamos o buffer com 'while(getchar())' caso o usuÃ¡rio digite alÃ©m da conta.
       =========================================================================
    */
    printf("\nNome do Jogador 1 (Max 29 letras): ");
    scanf("%29s", nome1);
    while (getchar() != '\n')
        ;

    printf("Nome do Jogador 2 (Max 29 letras): ");
    scanf("%29s", nome2);
    while (getchar() != '\n')
        ;

    // =========================================================================
    // FASE DE CONFIGURAÃ‡ÃƒO: JOGADOR 1 ESCONDE NAVIOS
    // =========================================================================
    system("cls");

    printf("=========================================\n");
    printf("      %s - Posicione seus navios\n", nome1);
    printf("=========================================\n");

    for (i = 0; i < 3; i++)
    {
        /* =========================================================================
           CONSERTO #1: LOOP INFINITO DE VALIDAÃ‡ÃƒO DE CONFIGURAÃ‡ÃƒO ('while(1)')
           - Por que arrumamos: No inÃ­cio, o jogo aceitava nÃºmeros fora do mapa
             (ex: -5 ou 99). O laÃ§o 'while(1)' garante que o programa fique preso
             aqui e sÃ³ saia via 'break' se o input estiver correto.
           =========================================================================
        */
        while (1)
        {
            printf("\nNAVIO %d\n", i + 1);
            printf("Linha (0-4): ");

            /* =========================================================================
               CONSERTO #3 (PARTE A): TESTE DE RETORNO DO SCANF NO CADASTRO
               - Por que arrumamos: Se o usuÃ¡rio digitasse letras ou strings contÃ­nuas
                 (como '-7-7-7-7'), o scanf falhava (retorno != 1), deixando lixo no buffer.
                 NÃ³s capturamos a falha, forÃ§amos o valor '-1' (invÃ¡lido) e limpamos a memÃ³ria.
               =========================================================================
            */
            if (scanf("%d", &navio1Linha[i]) != 1)
            {
                navio1Linha[i] = -1;
                while (getchar() != '\n')
                    ; // Triturador de lixo do buffer
            }

            printf("Coluna (0-4): ");
            if (scanf("%d", &navio1Coluna[i]) != 1)
            {
                navio1Coluna[i] = -1;
                while (getchar() != '\n')
                    ;
            }

            // Verifica se as coordenadas estÃ£o dentro das fronteiras fÃ­sicas (0 a 4)
            if (navio1Linha[i] >= 0 && navio1Linha[i] <= 4 &&
                navio1Coluna[i] >= 0 && navio1Coluna[i] <= 4)
            {

                /* =========================================================================
                   CONSERTO #4: RASTREIO HISTÃ“RICO CONTRA SOBREPOSIÃ‡ÃƒO DE NAVIOS
                   - Por que arrumamos: Se um jogador colocasse mais de um barco na mesma casa,
                     o mapa ficaria com menos alvos do que o necessÃ¡rio para vencer. Isso tornava
                     matematicamente impossÃ­vel atingir 3 acertos, travando o jogo no combate.
                     O laÃ§o 'k' varre o passado e impede a duplicidade.
                   =========================================================================
                */
                posicaoOcupada = 0;
                for (k = 0; k < i; k++)
                {
                    if (navio1Linha[i] == navio1Linha[k] &&
                        navio1Coluna[i] == navio1Coluna[k])
                    {
                        posicaoOcupada = 1;
                        break;
                    }
                }

                if (posicaoOcupada == 1)
                {
                    printf("\n[ERRO] Voce ja colocou um navio nesta posicao! Escolha outra.\n");
                }
                else
                {
                    break; // Tudo certo! Sai do loop de validaÃ§Ã£o
                }
            }
            else
            {
                printf("\n[ERRO] Posicao invalida! O mapa tatico so vai de 0 a 4.\n");
                while (getchar() != '\n')
                    ;
            }
        }
    }

    printf("\nNavios posicionados com sucesso!\n");
    /* =========================================================================
       CONSERTO #2: ADOÃ‡ÃƒO DO 'system("pause")' DO WINDOWS
       - Por que arrumamos: Usar 'getchar()' ou 'fflush(stdin)' gerava o bug do
         "efeito fantasma". O enter oculto pulava a leitura e o 'system("cls")'
         limpava a tela sem dar tempo para os jogadores lerem as mensagens de erro ou acerto.
       =========================================================================
    */
    system("pause");
    system("cls");

    // =========================================================================
    // FASE DE CONFIGURAÃ‡ÃƒO: JOGADOR 2 ESCONDE NAVIOS
    // =========================================================================
    printf("=========================================\n");
    printf("      %s - Posicione seus navios\n", nome2);
    printf("=========================================\n");

    for (i = 0; i < 3; i++)
    {
        while (1)
        {
            printf("\nNAVIO %d\n", i + 1);
            printf("Linha (0-4): ");
            if (scanf("%d", &navio2Linha[i]) != 1)
            {
                navio2Linha[i] = -1;
                while (getchar() != '\n')
                    ;
            }

            printf("Coluna (0-4): ");
            if (scanf("%d", &navio2Coluna[i]) != 1)
            {
                navio2Coluna[i] = -1;
                while (getchar() != '\n')
                    ;
            }

            if (navio2Linha[i] >= 0 && navio2Linha[i] <= 4 &&
                navio2Coluna[i] >= 0 && navio2Coluna[i] <= 4)
            {

                posicaoOcupada = 0;
                for (k = 0; k < i; k++)
                {
                    if (navio2Linha[i] == navio2Linha[k] &&
                        navio2Coluna[i] == navio2Coluna[k])
                    {
                        posicaoOcupada = 1;
                        break;
                    }
                }

                if (posicaoOcupada == 1)
                {
                    printf("\n[ERRO] Voce ja colocou um navio nesta posicao! Escolha outra.\n");
                }
                else
                {
                    break;
                }
            }
            else
            {
                printf("\n[ERRO] Posicao invalida! O mapa tatico so vai de 0 a 4.\n");
                while (getchar() != '\n')
                    ;
            }
        }
    }

    printf("\nNavios posicionados com sucesso!\n");
    system("pause");
    system("cls");

    // =========================================================================
    // LOOP PRINCIPAL DE COMBATE (SISTEMA DE TURNOS ANTIFALHAS)
    // =========================================================================
    while (acertos1 < 3 && acertos2 < 3)
    {

        // -------------------------------------
        // TURNO DO JOGADOR 1
        // -------------------------------------
        printf("=========================================\n");
        printf("            VEZ DE %s\n", nome1);
        printf("=========================================\n");

        printf("\nTABULEIRO INIMIGO\n\n");
        printf("   0 1 2 3 4\n");
        for (i = 0; i < 5; i++)
        {
            printf("%d  ", i);
            for (j = 0; j < 5; j++)
            {
                printf("%c ", tabuleiro2[i][j]);
            }
            printf("\n");
        }
        /* =========================================================================
           CONSERTO #3 (PARTE B): BLINDAGEM DE COMBATE CONTRA ATAQUE TROLL (-7-7-7-7)
           - Por que arrumamos: Se o usuÃ¡rio injetar strings massivas ou gerar um
             Integer Overflow (estouro de inteiro), o scanf falha retornando 0.
             NÃ³s forÃ§amos a linha a valer '-1' e limpamos o buffer imediatamente.
             O jogo avisa que a coordenada Ã© invÃ¡lida e nÃ£o entra em loop infinito.
           =========================================================================
        */
        printf("\nDigite a linha do ataque: ");
        if (scanf("%d", &linha) != 1)
        {
            linha = -1;
            while (getchar() != '\n')
                ; // Limpa tudo atÃ© achar a quebra de linha (ENTER)
        }

        printf("Digite a coluna do ataque: ");
        if (scanf("%d", &colunas) != 1)
        {
            colunas = -1;
            while (getchar() != '\n')
                ;
        }

        // TRAVA DE FRONTEIRAS JOGADOR 1
        if (linha < 0 || linha > 4 || colunas < 0 || colunas > 4)
        {
            printf("\nCoordenadas invalidas! Tiro perdido fora do mapa.\n");
            while (getchar() != '\n')
                ;
            system("pause");
        }
        else
        {
            int acertouNavio = 0;

            /* =========================================================================
               MÃ“DULO 6: INTERRUPÃ‡ÃƒO DE LAÃ‡O E PASSAGEM ALTERNADA DE TURNO (BREAK)
               - Por que Ã© estratÃ©gico: Assim que o sistema localiza qual dos 3 navios
                 foi atingido, ele encerra a busca imediatamente via 'break' para poupar
                 processamento, computa o acerto e forÃ§a a alternÃ¢ncia justa de turnos.
               =========================================================================
            */
            for (i = 0; i < 3; i++)
            {
                if (linha == navio2Linha[i] && colunas == navio2Coluna[i])
                {
                    if (tabuleiro2[linha][colunas] != 'X')
                    {
                        printf("\nBOOOOM! NAVIO ATINGIDO!\n");
                        tabuleiro2[linha][colunas] = 'X';
                        acertos1++;
                    }
                    else
                    {
                        printf("\nAtencao: Voce ja tinha acertado este navio antes!\n");
                    }
                    acertouNavio = 1;
                    break; // Interrompe o loop de busca na mesma hora
                }
            }

            if (acertouNavio == 0)
            {
                if (tabuleiro2[linha][colunas] != '~')
                {
                    printf("\nAgua! Nenhum navio encontrado.\n");
                    tabuleiro2[linha][colunas] = '~';
                }
                else
                {
                    printf("\nAtencao: Voce ja tinha atirado nesta coordenada antes!\n");
                }
            }

            while (getchar() != '\n')
                ;
            system("pause");
        }

        system("cls");

        if (acertos1 == 3)
        {
            break; // Quebra o laÃ§o se o jogador 1 jÃ¡ ganhou
        }

        // -------------------------------------
        // TURNO DO JOGADOR 2
        // -------------------------------------
        printf("=========================================\n");
        printf("            VEZ DE %s\n", nome2);
        printf("=========================================\n");

        printf("\nTABULEIRO INIMIGO\n\n");
        printf("   0 1 2 3 4\n");
        for (i = 0; i < 5; i++)
        {
            printf("%d  ", i);
            for (j = 0; j < 5; j++)
            {
                printf("%c ", tabuleiro1[i][j]);
            }
            printf("\n");
        }

        printf("\nDigite a linha do ataque: ");
        if (scanf("%d", &linha) != 1)
        {
            linha = -1;
            while (getchar() != '\n')
                ;
        }

        printf("Digite a coluna do ataque: ");
        if (scanf("%d", &colunas) != 1)
        {
            colunas = -1;
            while (getchar() != '\n')
                ;
        }

        // TRAVA DE FRONTEIRAS JOGADOR 2
        if (linha < 0 || linha > 4 || colunas < 0 || colunas > 4)
        {
            printf("\nCoordenadas invalidas! Tiro perdido fora do mapa.\n");
            while (getchar() != '\n')
                ;
            system("pause");
        }
        else
        {
            int acertouNavio = 0;

            /* =========================================================================
               MÃ“DULO 6: INTERRUPÃ‡ÃƒO DE LAÃ‡O E PASSAGEM ALTERNADA DE TURNO (BREAK)
               =========================================================================
            */
            for (i = 0; i < 3; i++)
            {
                if (linha == navio1Linha[i] && colunas == navio1Coluna[i])
                {
                    if (tabuleiro1[linha][colunas] != 'X')
                    {
                        printf("\nBOOOOM! NAVIO ATINGIDO!\n");
                        tabuleiro1[linha][colunas] = 'X';
                        acertos2++;
                    }
                    else
                    {
                        printf("\nAtencao: Voce ja tinha acertado este navio antes!\n");
                    }
                    acertouNavio = 1;
                    break; // Interrompe o loop de busca na mesma hora
                }
            }

            if (acertouNavio == 0)
            {
                if (tabuleiro1[linha][colunas] != '~')
                {
                    printf("\nAgua! Nenhum navio encontrado.\n");
                    tabuleiro1[linha][colunas] = '~';
                }
                else
                {
                    printf("\nAtencao: Voce ja tinha atirado nesta coordenada antes!\n");
                }
            }

            while (getchar() != '\n')
                ;
            system("pause");
        }

        system("cls");
    }

    // =========================================
    // TELA DE RESULTADO E ENCERRAMENTO FINAL
    // =========================================
    printf("=========================================\n");
    printf("              FIM DE JOGO               \n");
    printf("=========================================\n");

    if (acertos1 == 3)
    {
        printf("\nPARABENS %s! VOCE FOI O VENCEDOR DA BATALHA!\n", nome1);
    }
    else
    {
        printf("\nPARABENS %s! VOCE FOI O VENCEDOR DA BATALHA!\n", nome2);
    }

    printf("\nPLACAR FINAL:\n");
    printf("%s -> %d navios inimigos destruidos\n", nome1, acertos1);
    printf("%s -> %d navios inimigos destruidos\n", nome2, acertos2);

    printf("\n=========================================\n");
    printf("ALUNOS DESENVOLVEDORES:\n");
    printf("- Bruno Cesar Perillo da Silva\n");
    printf("- Gustavo Goncalves Paulo de Almeida\n");
    printf("- Luiggi Gouveia Bincoletto\n");
    printf("=========================================\n");

    /* CONSERTO EXTRA: RETENÃ‡ÃƒO DE TELA DE VITÃ“RIA NO .EXE
       - Por que colocamos: Quando executado direto pelo arquivo .exe, o Windows
         fechava a janela do terminal instantaneamente apÃ³s o Ãºltimo printf.
         Este 'system("pause")' segura a tela final para visualizaÃ§Ã£o do resultado.
    */
    printf("\n");
    system("pause");

    return 0;
}