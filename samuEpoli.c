/********************************************************************
    Poliane Brito de Oliveira & Samuel Soares Pereira Costa

    v1.0.0
    Descrição da estratégia:
********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR 50
#define PTAINHA 100
#define PCIOBA 150
#define PROBALO 200
#define CARGAMAX 10

typedef struct {
    int value;
    int boat; //há ou não barco
} Celula;

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
	barco.px=y;
    barco.py=x;
    /*============================================================
    //Ressalva//
    Os valores de X e Y estão inicialmente invertidos MAS a intenção 
    durante o desenvolvimento da lógica da movimentação do barco dentro das 
    dimensões do mapa é planejar a movimentação mentalizando o mapa 
    como um plano cartesiano, semelhante a uma batalha naval, 
    com X representando o deslocamento horizontal e Y representando o descocamento vertical.
    ============================================================*/
    if (barco.inicio==0){
        barco.mullet=0; 
        barco.snapper=0;
        barco.seabass=0;
        barco.qntPeixe=0;
    }
    barco.casaAtual=atual;
    return barco;
} //Salva/Atualiza os dados do boat a cada rodada

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
Barco readData(Barco barco, int h, int w, char* myId, Celula ***lerMapa) {
	char id[MAX_STR];
	int n, x, y;

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
        // fprintf(stderr, "To na posicao (%d,%d)\n", y, x); 
        //Considerando novamente um posicionamento semelhante a um plano cartesiano
	}
    *lerMapa=mapa;
    return barco;
}

void direcao(int decisao){
    if (decisao==0){
        printf("UP\n");
    }else if(decisao==1){
        printf("DOWN\n");
    }else if(decisao==2){
        printf("RIGHT\n");
    }else{
        printf("LEFT\n");
    }
}

// === FUNCAO RESPONSAVEL POR ESCOLHER O MELHOR MOVIMENTO PARA O BARCO ===
//O parametro acao indica o que eu tenho intencao de fazer:
//[0: pescar // 1: vender]
void movimentacao(int *direcoes, Barco barco, char* line, int h, int w, Celula **mapa, int acao, int casas){ 
    /* movimentacao no mar*/
    for (int i = 0; i < 4; i++){direcoes[i]=0;}
    //Buscar ate X casas de distancia - nao encontrando ...
    // int maxc=0;
    // if (h>w){maxc=h;}else{maxc=w;}
    // if (casas==maxc+1){
    //     //...mova-se pra onde tiver mais espaço
    //     printf("UP\n"); //teste - comentar
    // }

    //===Trecho retirado===
    //Analizar posicoes acima, abaixo, a direita e a esquerda
    // 0:cima  1:baixo    2:direita   3:esquerda
    //CONFERIR DIRECAO ACIMA
    int espaco=CARGAMAX-(barco.qntPeixe);
    if ((barco.py-casas)>=0){
        //0:cima
        int dir=0;
        int qtdPeixe=0;
        int cima = mapa[(barco.py)-casas][barco.px].value;
        if (cima==0){
            direcoes[dir]=0;
        }else if(cima==1){
            direcoes[dir]=1;
        }else if((cima>11) && (cima<20)){
            //tainha nessa direcao
            qtdPeixe=cima-11;
            //CONSIDERAR TB O TANTO Q EU POSSO PESCARf
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PTAINHA;
            }else{
                direcoes[dir]=espaco*PTAINHA;
            }
        }else if((cima>21) && (cima<30)){
            //cioba nessa direcao
            qtdPeixe=cima-21;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PCIOBA;
            }else{
                direcoes[dir]=espaco*PCIOBA;
            }
        }else if(cima>31){
            //ROBALO nessa direcao
            qtdPeixe=cima-31;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PROBALO;
            }else{
                direcoes[dir]=espaco*PROBALO;
            }
        }else{
            direcoes[dir]=0;
        }
        // fprintf(stderr, "Cima: %d", direcoes[dir]);
    }   
    //CONFERIR DIRECAO ABAIXO
    if ((barco.py+casas)<=(h-1)){
        //1:baixo
        int dir=1;
        int qtdPeixe=0;
        int baixo = mapa[(barco.py)+casas][barco.px].value;
        if (baixo==0){
            direcoes[dir]=0;
        }else if(baixo==1){
            direcoes[dir]=1;
        }else if((baixo>11) && (baixo<20)){
            //tainha nessa direcao
            qtdPeixe=baixo-11;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PTAINHA;
            }else{
                direcoes[dir]=espaco*PTAINHA;
            }
        }else if((baixo>21) && (baixo<30)){
            //cioba nessa direcao
            qtdPeixe=baixo-21;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PCIOBA;
            }else{
                direcoes[dir]=espaco*PCIOBA;
            }
        }else if(baixo>31){
            //ROBALO nessa direcao
            qtdPeixe=baixo-31;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PROBALO;
            }else{
                direcoes[dir]=espaco*PROBALO;
            }
        }else{
            direcoes[dir]=0;
        }
        // fprintf(stderr, "Baixo: %d", direcoes[dir]);
    }  
    //CONFERIR DIRECAO A DIREITA
    if ((barco.px+casas)<=(w-1)){
        //2:direita
        int dir=2;
        int qtdPeixe=0;
        int direita = mapa[barco.py][(barco.px)+casas].value;
        
        if (direita==0){
            direcoes[dir]=0;
        }else if(direita==1){
            direcoes[dir]=1;
        }else if((direita>11) && (direita<20)){
            //tainha nessa direcao
            qtdPeixe=direita-11;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PTAINHA;
            }else{
                direcoes[dir]=espaco*PTAINHA;
            }
        }else if((direita>21) && (direita<30)){
            //cioba nessa direcao
            qtdPeixe=direita-21;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PCIOBA;
            }else{
                direcoes[dir]=espaco*PCIOBA;
            }
        }else if(direita>31){
            //ROBALO nessa direcao
            qtdPeixe=direita-31;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PROBALO;
            }else{
                direcoes[dir]=espaco*PROBALO;
            }
        }else{
            direcoes[dir]=0;
        }
        // fprintf(stderr, "Direita: %d",direcoes[dir]);
    }   
    //CONFERIR DIRECAO A ESQUERDA
    if ((barco.px-casas)>=0){
        //3:esquerda
        int dir=3;
        int qtdPeixe=0;
        int esquerda = mapa[barco.py][(barco.px)-casas].value;
        if (esquerda==0){
            direcoes[dir]=0;
        }else if(esquerda==1){
            direcoes[dir]=1;
        }else if((esquerda>11) && (esquerda<20)){
            //tainha nessa direcao
            qtdPeixe=esquerda-11;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PTAINHA;
            }else{
                direcoes[dir]=espaco*PTAINHA;
            }
        }else if((esquerda>21) && (esquerda<30)){
            //cioba nessa direcao
            qtdPeixe=esquerda-21;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PCIOBA;
            }else{
                direcoes[dir]=espaco*PCIOBA;
            }
        }else if(esquerda>31){
            //ROBALO nessa direcao
            qtdPeixe=esquerda-31;
            if (espaco>qtdPeixe){
                direcoes[dir]=qtdPeixe*PROBALO;
            }else{
                direcoes[dir]=espaco*PROBALO;
            }
        }else{
            direcoes[dir]=0;
        }
        // fprintf(stderr, "Esquerda: %d",direcoes[dir]);
    }   
    for (int i = 0; i < 4; i++){
        fprintf(stderr, "%d: %d",i, direcoes[i]);
    }
            // cima(barco, mapa, casas, &direcoes, 0);
            // baixo(barco, mapa, casas, &direcoes, 1);
            // direita(barco, mapa, casas, &direcoes, 2);
            // esquerda(barco, mapa, casas, &direcoes, 3);
    
    // printf("UP\n"); //teste - comentar
    int decisao=0;
    if (acao==0){ //PESCA
        //Quero o maior valor pois quero pescar
        int max=0;
        for (int i = 0; i < 4; i++){
            if (direcoes[i]>max){
                max=direcoes[i];
                decisao=i;
            }
        }
        //Decidir posicao
        if (max==0){
            direcao(decisao);
            // movimentacao(direcoes, barco, line, h, w, mapa, acao, casas+1);
            fprintf(stderr, "EU VOU MUDAR DE CASA EIN");
        }else if(max==1){
            if (barco.qntPeixe>0){
                //Comando para direcao do porto
                direcao(decisao);
            }else{
                direcao(decisao);
                // movimentacao(direcoes, barco, line, h, w, mapa, acao, casas+1);
            }
        }else{
            //Comando para direcao do peixe mais valioso
            direcao(decisao);
        }
    }else{
        //Quero 1 para vender carga
        int porto=0;
        for (int i = 0; i < 4; i++){
            if (direcoes[i]==1){
                porto=1;
                decisao=i;
            }
        }
        //Decidir posicao
        if (porto==1){
            direcao(decisao);
        }else{
            direcao(decisao);
            // movimentacao(direcoes, barco, line, h, w, mapa, acao, casas+1);
        }
    }
    scanf("%s", line);
}

// === MAIN ===
// === INICIO DA PARTIDA === 
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
	fprintf(stderr, "Meu id = %s\n", myId); //Exemplo de erro enviado para o terminal

    Barco barco;
    Celula **mapa;
    int direcoes[4];
    
	// O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
	// o processo quando o jogo terminar.
	while (1) {
		// LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
		barco=readData(barco, h, w, myId, &mapa);
        // fprintf(stderr, "Tô em: %d\n", barco.casaAtual);
        
		// ABAIXO TODAS AS POSSIBILIDADES PARA ESCOLHER UMA AÇÃO A SER EXECUTADA
        if (barco.casaAtual==0){
            if (barco.qntPeixe<10){
                movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);
            }else{
                movimentacao(direcoes, barco, line, h, w, mapa, 1, 1);
            }
        }else if(barco.casaAtual==1){
            if (barco.inicio==0){
                barco.inicio=1;
                /* movimentacao como se estivesse no mar*/
                movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);
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
                    movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);
                }
            }
        }else{
            if (((barco.casaAtual>11) && (barco.casaAtual<20))||((barco.casaAtual>21) && (barco.casaAtual<30))||(barco.casaAtual>31)){
                fprintf(stderr, "NUMERO %d", barco.casaAtual);
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
                    /* movimentacao como se estivesse no mar*/
                    movimentacao(direcoes, barco, line, h, w, mapa, 1, 1);
                }
            }else{
                /* movimentacao como se estivesse no mar*/
                movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);
            }
        }
        //Fim do while
	}

	return 0;
}