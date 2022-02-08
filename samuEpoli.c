/********************************************************************
    Poliane Brito de Oliveira & Samuel Soares Pereira Costa

    v1.0.0
    Descrição da estratégia:
********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR 50

typedef struct {
    int value; 
    int boat; //há ou não barco
} Celula;
// //mapa do jogo
// typedef struct {
//     Celula** points; 
// } Mapa;

typedef struct meuBarco{
	int px;
	int py;
    int casaAtual;
    int inicio;
    int mullet; 
    int snapper;
    int seabass;
    int qntPeixe;
} Barco;

Barco atualizarBarco(Barco barco, int x, int y, int atual){
	barco.px=x;
    barco.py=y;
    if (barco.inicio==0){
        barco.mullet=0; 
        barco.snapper=0;
        barco.seabass=0;
        barco.qntPeixe=0;
    }
    barco.casaAtual=atual;
    return barco;
} //Salvar dados do bot para cada rodada

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
Barco readData(Barco barco, int h, int w, char* myId, Celula ***lerMapa) {
	char id[MAX_STR];
	int n, x, y;

    // int mapa[h][w];
    // int **mapa;
    // mapa=malloc(h*sizeof(int*));
    // for (int i = 0; i < h; i++){
    //     mapa[i]=malloc(w*sizeof(int));
    // }

    Celula **mapa;
    mapa=malloc(h*sizeof(Celula*));
    for (int i = 0; i < h; i++){
        mapa[i]=malloc(w*sizeof(Celula));
    }

	// lê os dados da área de pesca
	for (int i = 0; i < h; i++) {   
		for (int j = 0; j < w; j++) {
			// scanf("%i", &v); //Original
            scanf("%i", &mapa[i][j].value);
            mapa[i][j].boat=0;
		}
	}

	// lê os dados dos bots
	scanf(" BOTS %i", &n);
	// o " " antes de BOTS é necessário para ler o '\n' da linha anterior
	for (int i = 0; i < n; i++) {
		scanf("%s %i %i", id, &x, &y);
        int ret =strcmp(myId, id);
        if (ret==0){
            barco=atualizarBarco(barco, x, y, mapa[x][y].value);
        }else{
            mapa[x][y].boat=1;
            //outros bots
        }
        // for (int i = 0; i < h; i++) { 
        //     for (int j = 0; j < w; j++) {
        //         fprintf(stderr, "%i ", mapa[i][j]);
        //     }fprintf(stderr, "\n");
        // }
        // fprintf(stderr, "To na posicao (%d: %d)\n", y, x);
	}
    *lerMapa=mapa;
    return barco;
}


// === FUNCAO RESPONSAVEL POR ESCOLHER O MELHOR MOVIMENTO PARA O BARCO ===
//O parametro acao indica o que eu tenho intencao de fazer:
//[V = vender // P = pescar]
//[0: pescar // 1: vender]
void movimentacao(Barco barco, char* line, int h, int w, Celula **mapa){ 
    /* movimentacao no mar*/
    if (barco.py==0){
        printf("RIGHT\n");
    }else if (barco.py==w){
        printf("LEFT\n");
    }else if(barco.px==0){
        printf("DOWN\n");
    }else{
        printf("UP\n");
    }
    scanf("%s", line);
}


// === MAIN ===
int main() {
	char line[MAX_STR];   // dados temporários
	char myId[MAX_STR];   // identificador do bot em questão

	setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
	setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
	setbuf(stderr, NULL);

	// === INÍCIO DA PARTIDA ===
	int h, w;
	scanf("AREA %i %i", &h, &w);  // lê a dimensão da área de pesca: altura (h) x largura (w)
	scanf(" ID %s", myId);        // ...e o id do bot
	// obs: o " " antes de ID é necessário para ler o '\n' da linha anterior

	// Para "debugar", é possível enviar dados para a saída de erro padrão (stderr).
	// Esse dado não será enviado para o simulador, apenas para o terminal.
	// A linha seguinte é um exemplo. Pode removê-la se desejar.
	fprintf(stderr, "Meu id = %s\n", myId); //Exemplo de erro enviado para o terminal

    Barco barco;
    Celula **mapa;
    // mapa=malloc(h*sizeof(Celula*));
    // for (int i = 0; i < h; i++){
    //     mapa[i]=malloc(w*sizeof(Celula));
    // }
    
	// === PARTIDA === 
	// O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
	// o processo quando o jogo terminar.
	while (1) {
		// LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
		barco=readData(barco, h, w, myId, &mapa);
        // fprintf(stderr, "Tô em: %d\n", barco.casaAtual);
        
		// ABAIXO TODAS AS POSSIBILIDADES PARA ESCOLHER UMA AÇÃO A SER EXECUTADA
        if (barco.casaAtual==0){
            movimentacao(barco, line, h, w, mapa);
            // if (barco.py==0){
            //     printf("RIGHT\n");
            // }else if (barco.py==w){
            //     printf("LEFT\n");
            // }else if(barco.px==0){
            //     printf("DOWN\n");
            // }else{
            //     printf("UP\n");
            // }
            // scanf("%s", line);
        }else if(barco.casaAtual==1){
            if (barco.inicio==0){
                barco.inicio=1;
                // fprintf(stderr, "Mudou pra %d\n", barco.inicio);
                /* movimentacao como se estivesse no mar*/
                printf("UP\n");
                scanf("%s", line);
            }else{
                /* Vamo vender aqui*/
                if (barco.qntPeixe>0){
                    printf("SELL\n");
                    scanf("%s", line);
                    if (atoi(line)>0){
                        barco.mullet=0; 
                        barco.snapper=0;
                        barco.seabass=0;
                        barco.qntPeixe=0;
                    }
                }else{
                    printf("UP\n");
                    scanf("%s", line);
                }
            }
        }else{
            if (((barco.casaAtual>11) && (barco.casaAtual<20))||((barco.casaAtual>21) && (barco.casaAtual<30))||(barco.casaAtual>31)){
                // fprintf(stderr, "Ja to com %d\n", barco.qntPeixe);
                // fprintf(stderr, "tem %d T - ", barco.mullet);
                // fprintf(stderr, "tem %d C - ", barco.snapper);
                // fprintf(stderr, "tem %d R\n", barco.seabass);    
                if (barco.qntPeixe<10){
                    printf("FISH\n");
                    scanf("%s", line);
                    int ret=0;
                    ret=strcmp(line, "MULLET");
                    if (ret==0){
                        barco.mullet=barco.mullet+1;
                        fprintf(stderr, "Mais um sushi de tainha\n"); 
                    }else {
                        ret=strcmp(line, "SNAPPER");
                        if (ret==0){
                            barco.snapper=barco.snapper+1;
                            fprintf(stderr, "Mais um sushi de cioba\n"); 
                        }else{
                            ret=strcmp(line, "SEABASS");
                            if (ret==0){
                                barco.seabass=barco.seabass+1;
                                fprintf(stderr, "Mais um sushi de robalo\n"); 
                            }
                        }
                    }
                    ret=strcmp(line, "NONE"); 
                    if (ret!=0){
                        barco.qntPeixe=barco.mullet+barco.snapper+barco.seabass;
                    }
                }else{
                    fprintf(stderr, "Capacidade maxima\n"); 
                    // movimentacao(barco, line, h, w, mapa);
                    // scanf("%s", line);
                    /* movimentacao como se estivesse no mar*/
                    printf("UP\n");
                    scanf("%s", line);
                }
            }else{
                // char acao;
                // if (barco.qntPeixe==10){acao='V';}else{acao='P';}
                // movimentacao(barco, line, h, w, mapa, acao);
                /* movimentacao como se estivesse no mar*/
                printf("UP\n");
                scanf("%s", line);
            }
        }
        //Fim do while
	}

	return 0;
}