/***************************************************************************
Autores: Poliane Brito de Oliveira & Samuel Soares Pereira Costa
Projeto final de ITP v1.0.0

Descrição da estratégia de movimentação: 

  Serão analizadas as aréas acima, abaixo, a direita e a esquerda do barco, 
para as áreas acima e a  baixo suas dimensões (LxA) serão correspondentes a
L=(2*C)+1 e A=C,  já  as áreas à esquerda e à direita terão dimensões L=C e
A=(2*C)+1,  considerando C igual ao numero de  posiçõees  de  distancia  do
nosso barco que desejamos "olhar" para buscar alguma coisa.  Vale ressaltar
que C será incrementado de 1 em 1 caso nada seja encontrado nas 4 áreas.
***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR 50

#define PRECOTAINHA 100
#define PRECOCIOBA 150
#define PRECOPROBALO 200
#define CARGAMAX 10
#define CIMA 0
#define BAIXO 1
#define DIR 2
#define ESQ 3

typedef struct {
    int value; //Valor da posicao do mapa
    int boat; //há ou não barco
} Celula;

typedef struct meuBarco{
	int px; int py;
    int casaAtual;
    int inicio;
    int qntPeixe;
    int mullet; int snapper; int seabass; 
} Barco;

Barco atualizarBarco(Barco barco, int x, int y, int atual){
	barco.px=y; //Ressalva abaixo//
    barco.py=x; //Ressalva abaixo//
    if (barco.inicio==0){
        barco.qntPeixe=0;
        barco.mullet=0; barco.snapper=0; barco.seabass=0;
    }
    barco.casaAtual=atual;
    return barco;
} //Salva/Atualiza os dados do boat a cada rodada

/*============================================================
//Ressalva//
Os  valores de X  e  Y estão inicialmente invertidos MAS a intenção 
durante o desenvolvimento da lógica da movimentação do barco dentro
das dimensões do mapa é planejar a movimentação mentalizando o mapa 
como um plano cartesiano,  semelhante  a  uma  batalha naval, com X 
representando  o  deslocamento  horizontal  e  Y  representando  o 
descocamento vertical.
============================================================*/

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
        if (ret==0){barco=atualizarBarco(barco, x, y, mapa[x][y].value);
        }else{mapa[x][y].boat=1; /*outros bots*/}
	}
    *lerMapa=mapa;
    return barco;
}

// 0:cima  1:baixo    2:direita   3:esquerda
void direcao(int decisao, Barco barco, int h, int w, Celula **mapa){
    int px=barco.px; int py=barco.py;
    int boatC, boatB, boatE, boatD, portoC, portoB, portoE, portoD;
    if((py-1)>=0){ boatC=mapa[py-1][px].boat; portoC=mapa[py-1][px].value;}
    if((py+1)< h){ boatB=mapa[py+1][px].boat; portoB=mapa[py+1][px].value;}
    if((px+1)< w){ boatD=mapa[py][px+1].boat; portoD=mapa[py][px+1].value;}
    if((px-1)>=0){ boatE=mapa[py][px-1].boat; portoE=mapa[py][px-1].value;}
    //O codigo abaixo permite um desvio na direção caso a posição esteja ocupada (BUSY)
    
    if (decisao==0){//Up
        if (mapa[py-1][px].boat!=0){ //Tem barco lá 
            if (mapa[py-1][px].value==1){ printf("UP\n");/*É porto*/ 
            }else{
                if (((px+1<w)&&(boatD==0))||((px+1<w)&&(boatD!=0)&&(portoD==1))){printf("RIGHT\n"); //Se permitido ir pra direita
                }else if(((px-1>=0)&&(boatE==0))||((px-1>=0)&&(boatE!=0)&&(portoE==1))){printf("LEFT\n"); //Se permitido ir pra esquerda
                }else{printf("UP\n");}/*Perdi a jogada - estou cercado*/
        }}else{printf("UP\n");}
    }else if(decisao==1){
        if (mapa[py+1][px].boat!=0){ //Tem barco lá 
            if (mapa[py+1][px].value==1){ printf("DOWN\n");/*É porto*/ 
            }else{
                if (((px+1<w)&&(boatD==0))||((px+1<w)&&(boatD!=0)&&(portoD==1))){printf("RIGHT\n"); //Se permitido ir pra direita
                }else if(((px-1>=0)&&(boatE==0))||((px-1>=0)&&(boatE!=0)&&(portoE==1))){printf("LEFT\n"); //Se permitido ir pra esquerda
                }else{printf("DOWN\n");}/*Perdi a jogada - estou cercado*/
        }}else{printf("DOWN\n");}
    }else if(decisao==2){
        if (mapa[py][px+1].boat!=0){ //Tem barco lá 
            if (mapa[py][px+1].value==1){ printf("RIGHT\n");/*É porto*/ 
            }else{
                if (((py+1<h)&&(boatB==0))||((py+1<h)&&(boatB!=0)&&(portoB==1))){printf("DOWN\n"); //Se permitido ir pra baixo
                }else if(((py-1>=0)&&(boatC==0))||((py-1>=0)&&(boatC!=0)&&(portoC==1))){printf("UP\n"); //Se permitido ir pra cima
                }else{printf("RIGHT\n");}/*Perdi a jogada - estou cercado*/
        }}else{printf("RIGHT\n");}
    }else if(decisao==3){
        if (mapa[py][px-1].boat!=0){ //Tem barco lá 
            if (mapa[py][px-1].value==1){ printf("LEFT\n");/*É porto*/ 
            }else{
                if (((py+1<h)&&(boatB==0))||((py+1<h)&&(boatB!=0)&&(portoB==1))){printf("DOWN\n"); //Se permitido ir pra baixo
                }else if(((py-1>=0)&&(boatC==0))||((py-1>=0)&&(boatC!=0)&&(portoC==1))){printf("UP\n"); //Se permitido ir pra cima
                }else{printf("LEFT\n");}/*Perdi a jogada - estou cercado*/
        }}else{printf("LEFT\n");}}
}

/*##########################################################################################################
############################################################################################################
##########################################################################################################*/

int porto(Barco barco, Celula **mapa, int h, int w){
    int direcao=10; int min=100; //numeros altos para nao interferirem no resultado
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            if (mapa[i][j].value==1){
                int distancia=abs(i-barco.py)+abs(j-barco.px);
                if (distancia<min){
                    min=distancia;
                    if (i<barco.py){direcao=0;
                    }else if(i>barco.py){direcao=1;
                    }else if(j>barco.px){direcao=2;
                    }else {direcao=3;}
                }
            }
        }
    }
    return direcao;
}

/**********************************************************************************************************
=========== FUNCAO RESPONSAVEL POR ESCOLHER O MELHOR MOVIMENTO PARA O BARCO ESCANEANDO UMA AREA ===========
***********************************AÇÃO: [0: pescar // 1: vender]******************************************
***********************************************************************************************************/

void varrerAreas(int *direcoes, Barco barco, int h, int w, Celula **mapa, int acao, int casas){
    // fprintf(stderr, "CASAS\n: %d\n",casas);
    int portos[4]; int px=barco.px; int py=barco.py;
    for (int i = 0; i < 4; i++){direcoes[i]=0;} for (int i = 0; i < 4; i++){portos[i]=0;} //Zerar vetor

    int dmax=0; int dc, db, de, dd=0; dc=py; db=h-py-1; de=px; dd=w-px-1;
    int maxvet[4]; maxvet[0]=dc; maxvet[1]=db; maxvet[2]=de; maxvet[3]=dd; 
    for (int i = 0; i < 4; i++){if (maxvet[i]>dmax){dmax=maxvet[i];}} //Verificacao de erro no fim

    if (((py)-casas)>=0){//CONFERIR AREA ACIMA
        int soma=0; int min=0; int max=w; int ymin=((py)-casas); int ymax=py; int valor=0;
        for (int i = ymin; i < ymax; i++){
            if (((px)-casas)>0){min=((px)-casas);}
            if (((px)+casas)<w){max=((px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[CIMA]=portos[CIMA]+1;}
            }
        }direcoes[CIMA]=soma;
    }else if((py)!=0){
        int soma=0; int min=0; int max=w; int ymin=(py)-1; int ymax=(py); int valor=0;
        for (int i = ymin; i < ymax; i++){
            if (((px)-casas)>0){min=((px)-casas);}
            if (((px)+casas)<w){max=((px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[CIMA]=portos[CIMA]+1;}
            }
        }direcoes[CIMA]=soma;
    }

    if (((py)+casas)<=(h-1)){//CONFERIR AREA ABAIXO
        int soma=0; int min=0; int max=w; int ymin=py+1; int ymax=((py)+casas)+1; int valor=0;
        for (int i = ymin; i < ymax; i++){
            if (((px)-casas)>0){min=((px)-casas);}
            if (((px)+casas)<w){max=((px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[BAIXO]=portos[BAIXO]+1;}
            }
        }direcoes[BAIXO]=soma;
    }else if((py)!=(h-1)){
        int soma=0; int min=0; int max=w; int valor=0;
        for (int i = ((py)+1); i < ((py)+2); i++){
            if (((px)-casas)>0){min=((px)-casas);}
            if (((px)+casas)<w){max=((px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[BAIXO]=portos[BAIXO]+1;}
            }
        }direcoes[BAIXO]=soma;
    }

    if (((px)+casas)<=(w-1)){//CONFERIR AREA DIREITA
        int soma=0; int xmin=(px+1); int xmax=w; int ymin=0; int ymax=h; int valor=0;
        if (((py)-casas)>0){ymin=((py)-casas);}
        if (((py)+casas)<h){ymax=((py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            if (((px)+casas)<w){xmax=((px)+casas)+1;}
            for (int j = xmin; j < xmax; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[DIR]=portos[DIR]+1;}
            }
        }direcoes[DIR]=soma;
    }
    else if((px)!=(w-1)){
        int soma=0; int ymin=0; int ymax=h; int xmin=px+w-1; int xmax=w; int valor=0;
        if (((py)-casas)>0){ymin=((py)-casas);}
        if (((py)+casas)<h){ymax=((py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            if (((py)-casas)>0){ymin=((py)-casas);}
            if (((py)+casas)<h){ymax=((py)+casas)+1;}
            for (int j = xmin; j < xmax; j++){
                if (mapa[i][j].boat==0){ valor=(mapa[i][j].value);
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[DIR]=portos[DIR]+1;}
            }
        }direcoes[DIR]=soma;
    }

    if (((px)-casas)>=0){//CONFERIR AREA ESQUERDA
        int soma=0; int xmin=0; int xmax=px; int ymin=0; int ymax=h; int valor=0;
        if (((py)-casas)>0){ymin=((py)-casas);}
        if (((py)+casas)<h){ymax=((py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            if (((px)-casas)>0){xmin=((px)-casas);}
            for (int j = xmin; j < xmax; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[ESQ]=portos[ESQ]+1;}
            }
        }direcoes[ESQ]=soma;
    }else if((px)!=0){
        int soma=0; int xmin=px-1; int xmax=px; int ymin=0; int ymax=h; int valor=0;
        if (((py)-casas)>0){ymin=((py)-casas);}
        if (((py)+casas)<h){ymax=((py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            for (int j = xmin; j < xmax; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[ESQ]=portos[ESQ]+1;}
            }
        }direcoes[ESQ]=soma;
    }

    int decisao=0;
    if (acao==0){ //PESCA - Quero o maior valor pois quero pescar
        int max=0;
        for (int i = 0; i < 4; i++){
            if (direcoes[i]>max){
                max=direcoes[i];
                decisao=i;
            }
        }
        //Decidir posicao
        if (max==0){
            int porto=0;
            for (int i = 0; i < 4; i++){
                if (portos[i]==1){
                    porto=porto+1;
                    decisao=i;
                }
            }
            if ((porto>0)&&(barco.qntPeixe>0)){
                direcao(decisao, barco, h, w, mapa);
            }else{
                if (casas==dmax){
                    if (barco.py!=0){printf("UP\n");}else{printf("DOWN\n");}//Erro
                }else{varrerAreas(direcoes, barco, h, w, mapa, acao, casas+1);}
            }
        }else{
            //Conferir portos e ir para area mais valiosa
            if (barco.qntPeixe>0){
                int porto=0; max=0;
                for (int i = 0; i < 4; i++){
                    if (portos[i]==1){
                        porto=porto+1;
                        if (direcoes[i]>max){max=direcoes[i]; decisao=i;}
                    }
                }
            }
            direcao(decisao, barco, h, w, mapa);
        }
    }else{
        //Quero 1 para vender carga
        decisao=porto(barco, mapa, h, w);
        direcao(decisao, barco, h, w, mapa);
    }
}

/**********************************************************************************************************
================== FIM DA FUNCAO RESPONSAVEL POR ESCOLHER O MELHOR MOVIMENTO PARA O BARCO =================
***********************************************************************************************************
***********************************************************************************************************/

// === INICIO DA PARTIDA === 
int main() {
	char line[MAX_STR];   // dados temporários
	char myId[MAX_STR];   // identificador do bot em questão
	setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
	setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
	setbuf(stderr, NULL);

	// === INÍCIO DA PARTIDA ===
	int h, w;
	scanf("AREA %i %i", &h, &w);
	scanf(" ID %s", myId);
	//o espaço antes de ID é necessário para ler o \n da linha anterior

    Barco barco; Celula **mapa; int direcoes[4]; //Dados do bot, de todas as casas do mapa e vetor utilizado para movimentação
    
	while (1) {
		// LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
		barco=readData(barco, h, w, myId, &mapa);  
        
		// ABAIXO TODAS AS POSSIBILIDADES PARA ESCOLHER UMA AÇÃO A SER EXECUTADA
        if (barco.casaAtual==0){ //AÇÃO: [0: pescar // 1: vender]
            if (barco.qntPeixe<10){varrerAreas(direcoes, barco, h, w, mapa, 0, 1);
            }else{                 varrerAreas(direcoes, barco, h, w, mapa, 1, 1);}scanf("%s", line);
        }else if(barco.casaAtual==1){
            if (barco.inicio==0){
                barco.inicio=1; varrerAreas(direcoes, barco, h, w, mapa, 0, 1);scanf("%s", line);
            }else{
                if (barco.qntPeixe>0){
                    printf("SELL\n"); scanf("%s", line);
                    if (atoi(line)>0){ barco.qntPeixe=0; barco.mullet=0; barco.snapper=0;barco.seabass=0;} //Zerando apos vender
                }else{varrerAreas(direcoes, barco, h, w, mapa, 0, 1);scanf("%s", line);}
            }
        }else{
            if (((barco.casaAtual>11) && (barco.casaAtual<20))||((barco.casaAtual>21) && (barco.casaAtual<30))||(barco.casaAtual>31)){
                // fprintf(stderr, "NUMERO %d (%d,%d)", valorCasa, barco.px, barco.py);
                if (barco.qntPeixe<10){
                    printf("FISH\n"); scanf("%s", line); int ret=0;
                    ret=strcmp(line, "MULLET");
                    if (ret==0){barco.mullet=barco.mullet+1;
                    }else{ret=strcmp(line, "SNAPPER");
                        if (ret==0){barco.snapper=barco.snapper+1;
                        }else{ret=strcmp(line, "SEABASS");
                            if (ret==0){barco.seabass=barco.seabass+1;}
                        }
                    }
                    ret=strcmp(line, "NONE"); 
                    if (ret!=0){barco.qntPeixe=barco.mullet+barco.snapper+barco.seabass;} //Aumentando ao pescar
                }else{
                    // fprintf(stderr, "Capacidade maxima\n"); 
                    varrerAreas(direcoes, barco, h, w, mapa, 1, 1);
                    scanf("%s", line);
                }
            }else{
                if (barco.qntPeixe<10){varrerAreas(direcoes, barco, h, w, mapa, 0, 1);
                }else{varrerAreas(direcoes, barco, h, w, mapa, 1, 1);} scanf("%s", line);
            }
        } //Fim do while
	}return 0;
}