/***************************************************************************
Poliane Brito de Oliveira & Samuel Soares Pereira Costa

v1.0.0
Descrição da estratégia de movimentação: 

    Analisar inicialmente as 4 direções principais para decidir qual a mais 
vantajosa para a situação, caso nenhuma seja vantajosa aumentar a região de
busca e mudar de estratégia.  Serão  analizadas  as  aréas acima, abaixo, a 
direita e a esquerda do barco, para as áreas acima e a baixo suas dimensões
(LxA) serão correspondentes a L=(2*C)+1 e A=C,  já  as áreas à esquerda e à 
direita terão dimensões L=C e A=(2*C)+1,  considerando C igual ao numero de 
posiçõees  de  distancia  do  nosso barco que desejamos "olhar" para buscar 
alguma coisa.  Vale ressaltar que C será incrementado de um em um caso nada
seja encontrado dentro das 4 áreas.
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
	barco.px=y;
    barco.py=x;
    /*============================================================
    //Ressalva//
    Os  valores de X  e  Y estão inicialmente invertidos MAS a intenção 
    durante o desenvolvimento da lógica da movimentação do barco dentro
    das dimensões do mapa é planejar a movimentação mentalizando o mapa 
    como um plano cartesiano,  semelhante  a  uma  batalha naval, com X 
    representando  o  deslocamento  horizontal  e  Y  representando  o 
    descocamento vertical.
    ============================================================*/
    if (barco.inicio==0){
        barco.qntPeixe=0;
        barco.mullet=0; barco.snapper=0; barco.seabass=0;
    }
    barco.casaAtual=atual;
    return barco;
} //Salva/Atualiza os dados do boat a cada rodada

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
    
    if (decisao==0){//Up
        if (mapa[py-1][px].boat!=0){ //Tem barco lá 
            if (mapa[py-1][px].value==1){ printf("UP\n");/*É porto*/ 
            }else{ 
                if (((px+1<w)&&(boatD==0))||((px+1<w)&&(boatD!=0)&&(portoD==1))){printf("RIGHT\n"); //Se pertminito ir pra direita
                }else if(((px-1>=0)&&(boatE==0))||((px-1>=0)&&(boatE!=0)&&(portoE==1))){printf("LEFT\n"); //Se pertminito ir pra esquerda
                }else{printf("UP\n");}/*Perdi a jogada - estou cercado*/
        }}else{printf("UP\n");}

    }else if(decisao==1){
        if (mapa[py+1][px].boat!=0){ //Tem barco lá 
            if (mapa[py+1][px].value==1){ printf("DOWN\n");/*É porto*/ 
            }else{ 
                if (((px+1<w)&&(boatD==0))||((px+1<w)&&(boatD!=0)&&(portoD==1))){printf("RIGHT\n"); //Se pertminito ir pra direita
                }else if(((px-1>=0)&&(boatE==0))||((px-1>=0)&&(boatE!=0)&&(portoE==1))){printf("LEFT\n"); //Se pertminito ir pra esquerda
                }else{printf("DOWN\n");}/*Perdi a jogada - estou cercado*/
        }}else{printf("DOWN\n");}
    }else if(decisao==2){
        if (mapa[py][px+1].boat!=0){ //Tem barco lá 
            if (mapa[py][px+1].value==1){ printf("RIGHT\n");/*É porto*/ 
            }else{ 
                if (((py+1<h)&&(boatB==0))||((py+1<h)&&(boatB!=0)&&(portoB==1))){printf("DOWN\n"); //Se pertminito ir pra baixo
                }else if(((py-1>=0)&&(boatC==0))||((py-1>=0)&&(boatC!=0)&&(portoC==1))){printf("UP\n"); //Se pertminito ir pra cima
                }else{printf("RIGHT\n");}/*Perdi a jogada - estou cercado*/
        }}else{printf("RIGHT\n");}
    }else if(decisao==3){
        if (mapa[py][px-1].boat!=0){ //Tem barco lá 
            if (mapa[py][px-1].value==1){ printf("LEFT\n");/*É porto*/ 
            }else{ 
                if (((py+1<h)&&(boatB==0))||((py+1<h)&&(boatB!=0)&&(portoB==1))){printf("DOWN\n"); //Se pertminito ir pra baixo
                }else if(((py-1>=0)&&(boatC==0))||((py-1>=0)&&(boatC!=0)&&(portoC==1))){printf("UP\n"); //Se pertminito ir pra cima
                }else{printf("LEFT\n");}/*Perdi a jogada - estou cercado*/
        }}else{printf("LEFT\n");}}
}

/**********************************************************************************************************
=========== FUNCAO RESPONSAVEL POR ESCOLHER O MELHOR MOVIMENTO PARA O BARCO ESCANEANDO UMA AREA ===========
***********************************AÇÃO: [0: pescar // 1: vender]******************************************
***********************************************************************************************************/

void varrerArea(int *direcoes, Barco barco, int h, int w, Celula **mapa, int acao, int casas){
    fprintf(stderr, "CASAS\n: %d\n",casas);
    int portos[4]; int px=barco.px; int py=barco.py;
    for (int i = 0; i < 4; i++){direcoes[i]=0;}
    for (int i = 0; i < 4; i++){portos[i]=0;}

    int dmax=0; 
    int dc, db, de, dd=0; dc=py; db=h-py-1; de=px; dd=w-px-1;
    int maxvet[4]; maxvet[0]=dc; maxvet[1]=db; maxvet[2]=de; maxvet[3]=dd; 
    for (int i = 0; i < 4; i++){
        if (maxvet[i]>dmax){dmax=maxvet[i];}
    }

    if (((py)-casas)>=0){//CONFERIR AREA ACIMA
        int soma=0; int dir=0; int min=0; int max=w; int ymin=((py)-casas); int ymax=py; int valor=0;
        // if (((py)-casas)>0){ymin=((py)-casas);}
        for (int i = ymin; i < ymax; i++){
            if (((px)-casas)>0){min=((px)-casas);}
            if (((px)+casas)<w){max=((px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "AreaCima: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosCima: %d\n",portos[dir]);
    }else if((py)!=0){
        int soma=0; int dir=0; int min=0; int max=w; int ymin=0; int ymax=h; int valor=0;
        // if (((py)-casas)>0){ymin=((py)-casas);}
        // if (((py)+casas)<h){ymax=((py)+casas)+1;}//74703
        for (int i = (py)-1; i < (py); i++){
            if (((px)-casas)>0){min=((px)-casas);}
            if (((px)+casas)<w){max=((px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "AreaCima: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosCima: %d\n",portos[dir]);
    }

    if (((py)+casas)<=(h-1)){//CONFERIR AREA ABAIXO
        int soma=0; int dir=1; int min=0; int max=w; int ymin=py+1; int ymax=((py)+casas)+1; int valor=0;
        for (int i = ymin; i < ymax; i++){
            if (((px)-casas)>0){min=((px)-casas);}
            if (((px)+casas)<w){max=((px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "Areabaixo: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosBaixo: %d\n",portos[dir]);
    }else if((py)!=(h-1)){
        int soma=0; int dir=1; int min=0; int max=w; int valor=0;
        for (int i = ((py)+1); i < ((py)+2); i++){
            if (((px)-casas)>0){min=((px)-casas);}
            if (((px)+casas)<w){max=((px)+casas)+1;}
            for (int j = min; j < max; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "Areabaixo: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosBaixo: %d\n",portos[dir]);
    }

    if (((px)+casas)<=(w-1)){//CONFERIR AREA DIREITA
        int soma=0; int dir=2; int xmin=(px+1); int xmax=w; int ymin=0; int ymax=h; int valor=0;
        if (((py)-casas)>0){ymin=((py)-casas);}
        if (((py)+casas)<h){ymax=((py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            // if (((px)-casas)>0){xmin=((px)-casas);}
            if (((px)+casas)<w){xmax=((px)+casas)+1;}
            for (int j = xmin; j < xmax; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "Areadireita: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosDireita: %d\n",portos[dir]);
    }
    else if((px)!=(w-1)){
        int soma=0; int dir=1; int ymin=0; int ymax=h; int xmin=px+w-1; int xmax=w; int valor=0;
        if (((py)-casas)>0){ymin=((py)-casas);}
        if (((py)+casas)<h){ymax=((py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            if (((py)-casas)>0){ymin=((py)-casas);}
            if (((py)+casas)<h){ymax=((py)+casas)+1;}
            for (int j = xmin; j < xmax; j++){
                if (mapa[i][j].boat==0){ valor=(mapa[i][j].value);
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "Areabaixo: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosBaixo: %d\n",portos[dir]);
    }

    if (((px)-casas)>=0){//CONFERIR AREA ESQUERDA
        int soma=0; int dir=3; int xmin=0; int xmax=px; int ymin=0; int ymax=h; int valor=0;
        if (((py)-casas)>0){ymin=((py)-casas);}
        if (((py)+casas)<h){ymax=((py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            if (((px)-casas)>0){xmin=((px)-casas);}
            // if (((px)-casas)<w){xmax=((px)+casas)+1;}
            for (int j = xmin; j < xmax; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "AreaEsquerda: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosEsquerda: %d\n",portos[dir]);
    }else if((px)!=0){
        int soma=0; int dir=3; int xmin=px-1; int xmax=px; int ymin=0; int ymax=h; int valor=0;
        if (((py)-casas)>0){ymin=((py)-casas);}
        if (((py)+casas)<h){ymax=((py)+casas)+1;}
        for (int i = ymin; i < ymax; i++){
            // if (((px)-casas)>0){xmin=((px)-casas);}
            // if (((px)-casas)<w){xmax=((px)+casas)+1;}
            for (int j = xmin; j < xmax; j++){
                valor=(mapa[i][j].value);
                if (mapa[i][j].boat==0){ 
                    if ((valor!=11)&&(valor!=21)&&(valor!=31)&&(valor!=1)){soma=soma+valor;}
                }
                if (valor==1){portos[dir]=portos[dir]+1;}
            }
        }direcoes[dir]=soma;
        fprintf(stderr, "AreaEsquerda: %d\n",direcoes[dir]);
        fprintf(stderr, "PortosEsquerda: %d\n",portos[dir]);
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
                    fprintf(stderr, "\nErro");
                }else{varrerArea(direcoes, barco, h, w, mapa, acao, casas+1);}
            }
        }else{
            //Comando para direcao da area mais valiosa
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
        int porto=0;
        int maxporto=0;
        for (int i = 0; i < 4; i++){
            if (portos[i]>0){
                porto=porto+portos[i];
                // if (portos[i]>maxporto){
                //     maxporto=portos[i];
                // if (/* condition */){
                    
                // }
                
                    decisao=i;
                // }
            }
        }
        fprintf(stderr, "Porto: %d\n", porto);
        //Decidir posicao
        if (porto>0){
            fprintf(stderr, "A decisao de area eh: %d\n", decisao);
            direcao(decisao, barco, h, w, mapa);
        }else{
            if (casas==dmax){
                fprintf(stderr, "\nErro");
            }else{varrerArea(direcoes, barco, h, w, mapa, acao, casas+1);}
        }
    }
}

/**********************************************************************************************************
================== FUNCAO RESPONSAVEL POR ESCOLHER O MELHOR MOVIMENTO PARA O BARCO ========================
***********************************AÇÃO: [0: pescar // 1: vender]******************************************
***********************************************************************************************************/

void movimentacao(int *direcoes, Barco barco, char* line, int h, int w, Celula **mapa, int acao, int casas){ 
    for (int i = 0; i < 4; i++){direcoes[i]=0;}
    int espaco=CARGAMAX-(barco.qntPeixe); int px=barco.px; int py=barco.py;

    if ((py-casas)>=0){//CONFERIR DIRECAO ACIMA
        int qtdPeixe=0;
        int cima = mapa[py-casas][px].value;
        int cimabot = mapa[py-casas][px].boat;
        if (cimabot>0){if (cima==1){direcoes[CIMA]=1;}else{direcoes[CIMA]=0;}
        }else if (cima==0){direcoes[CIMA]=0;
        }else if(cima==1){direcoes[CIMA]=1;
        }else if((cima>11) && (cima<20)){//tainha nessa direcao
            qtdPeixe=cima-11;
            if (espaco>qtdPeixe){direcoes[CIMA]=qtdPeixe*PRECOTAINHA;
            }else{direcoes[CIMA]=espaco*PRECOTAINHA;}
        }else if((cima>21) && (cima<30)){//cioba nessa direcao
            qtdPeixe=cima-21;
            if (espaco>qtdPeixe){direcoes[CIMA]=qtdPeixe*PRECOCIOBA;
            }else{direcoes[CIMA]=espaco*PRECOCIOBA;}
        }else if(cima>31){//ROBALO nessa direcao
            qtdPeixe=cima-31;
            if (espaco>qtdPeixe){direcoes[CIMA]=qtdPeixe*PRECOPROBALO;
            }else{direcoes[CIMA]=espaco*PRECOPROBALO;}
        }else{
            direcoes[CIMA]=0;
        }
        // fprintf(stderr, "Cima: %d", direcoes[CIMA]);
    }   
    
    if ((py+casas)<=(h-1)){//CONFERIR DIRECAO ABAIXO
        int qtdPeixe=0;
        int baixo = mapa[py+casas][px].value;
        int baixobot = mapa[py+casas][px].boat;
        if (baixobot>0){if (baixo==1){direcoes[BAIXO]=1;}else{direcoes[BAIXO]=0;}
        }else if (baixo==0){direcoes[BAIXO]=0;
        }else if(baixo==1){direcoes[BAIXO]=1;
        }else if((baixo>11) && (baixo<20)){//tainha nessa direcao
            qtdPeixe=baixo-11;
            if (espaco>qtdPeixe){direcoes[BAIXO]=qtdPeixe*PRECOTAINHA;
            }else{direcoes[BAIXO]=espaco*PRECOTAINHA;}
        }else if((baixo>21) && (baixo<30)){//cioba nessa direcao
            qtdPeixe=baixo-21;
            if (espaco>qtdPeixe){direcoes[BAIXO]=qtdPeixe*PRECOCIOBA;
            }else{direcoes[BAIXO]=espaco*PRECOCIOBA;}
        }else if(baixo>31){//ROBALO nessa direcao
            qtdPeixe=baixo-31;
            if (espaco>qtdPeixe){direcoes[BAIXO]=qtdPeixe*PRECOPROBALO;
            }else{direcoes[BAIXO]=espaco*PRECOPROBALO;}
        }else{
            direcoes[BAIXO]=0;
        }
        // fprintf(stderr, "Baixo: %d", direcoes[BAIXO]);
    }  

    if ((px+casas)<=(w-1)){//CONFERIR DIRECAO A DIREITA
        int qtdPeixe=0;
        int direita = mapa[py][px+casas].value;
        int direitabot = mapa[py][px+casas].boat;
        if (direitabot>0){if (direita==1){direcoes[DIR]=1;}else{direcoes[DIR]=0;}
        }else if (direita==0){direcoes[DIR]=0;
        }else if(direita==1){direcoes[DIR]=1;
        }else if((direita>11) && (direita<20)){//tainha nessa direcao
            qtdPeixe=direita-11;
            if (espaco>qtdPeixe){direcoes[DIR]=qtdPeixe*PRECOTAINHA;
            }else{direcoes[DIR]=espaco*PRECOTAINHA;}
        }else if((direita>21) && (direita<30)){//cioba nessa direcao
            qtdPeixe=direita-21;
            if (espaco>qtdPeixe){direcoes[DIR]=qtdPeixe*PRECOCIOBA;
            }else{direcoes[DIR]=espaco*PRECOCIOBA;}
        }else if(direita>31){//ROBALO nessa direcao
            qtdPeixe=direita-31;
            if (espaco>qtdPeixe){direcoes[DIR]=qtdPeixe*PRECOPROBALO;
            }else{direcoes[DIR]=espaco*PRECOPROBALO;}
        }else{
            direcoes[DIR]=0;
        }
        // fprintf(stderr, "Direita: %d",direcoes[DIR]);
    }   

    if ((px-casas)>=0){//CONFERIR DIRECAO A ESQUERDA
        int qtdPeixe=0;
        int esquerda = mapa[py][px-casas].value;
        int esquerdabot = mapa[py][px-casas].boat;
        if (esquerdabot>0){if (esquerda==1){direcoes[ESQ]=1;}else{direcoes[ESQ]=0;}
        }else if (esquerda==0){direcoes[ESQ]=0;
        }else if(esquerda==1){direcoes[ESQ]=1;
        }else if((esquerda>11) && (esquerda<20)){//tainha nessa direcao
            qtdPeixe=esquerda-11;
            if (espaco>qtdPeixe){direcoes[ESQ]=qtdPeixe*PRECOTAINHA;
            }else{direcoes[ESQ]=espaco*PRECOTAINHA;}
        }else if((esquerda>21) && (esquerda<30)){//cioba nessa direcao
            qtdPeixe=esquerda-21;
            if (espaco>qtdPeixe){direcoes[ESQ]=qtdPeixe*PRECOCIOBA;
            }else{direcoes[ESQ]=espaco*PRECOCIOBA;}
        }else if(esquerda>31){//ROBALO nessa direcao
            qtdPeixe=esquerda-31;
            if (espaco>qtdPeixe){direcoes[ESQ]=qtdPeixe*PRECOPROBALO;
            }else{direcoes[ESQ]=espaco*PRECOPROBALO;}
        }else{
            direcoes[ESQ]=0;
        }
        // fprintf(stderr, "Esquerda: %d",direcoes[ESQ]);
    }   
    // for (int i = 0; i < 4; i++){fprintf(stderr, "%d: %d",i, direcoes[i]);}
    
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
            // Conferir diagonais´
            varrerArea(direcoes, barco, h, w, mapa, acao, casas);
        }else if(max==1){
            if (barco.qntPeixe>0){
                //Comando para direcao do porto
                direcao(decisao, barco, h, w, mapa);
            }else{
                varrerArea(direcoes, barco, h, w, mapa, acao, casas);
            }
        }else{
            //Comando para direcao do peixe mais valioso
            direcao(decisao, barco, h, w, mapa);
        }
    }else{//Vender carga
        int porto=0;
        for (int i = 0; i < 4; i++){
            if (direcoes[i]==1){porto=1; decisao=i;}
        }
        //Decidir posicao
        if (porto==1){direcao(decisao, barco, h, w, mapa);
        }else{varrerArea(direcoes, barco, h, w, mapa, acao, casas);}
    }
    scanf("%s", line);
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
	scanf("AREA %i %i", &h, &w);  // lê a dimensão da área de pesca: altura (h) x largura (w)
	scanf(" ID %s", myId);        // ...e o id do bot
	// obs: o " " antes de ID é necessário para ler o '\n' da linha anterior

    Barco barco; Celula **mapa; int direcoes[4]; //Dados do bot, de todas as casas do mapa e vetor utilizado para movimentação
    
	while (1) {
		// LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
		barco=readData(barco, h, w, myId, &mapa);  
        
		// ABAIXO TODAS AS POSSIBILIDADES PARA ESCOLHER UMA AÇÃO A SER EXECUTADA
        if (barco.casaAtual==0){
            if (barco.qntPeixe<10){movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);
            }else{                 movimentacao(direcoes, barco, line, h, w, mapa, 1, 1);}
        }else if(barco.casaAtual==1){
            if (barco.inicio==0){
                barco.inicio=1; movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);
            }else{
                if (barco.qntPeixe>0){
                    printf("SELL\n"); scanf("%s", line);
                    if (atoi(line)>0){ barco.qntPeixe=0; barco.mullet=0; barco.snapper=0;barco.seabass=0;} //Zerando apos vender
                }else{movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);}
            }
        }else{
            if (((barco.casaAtual>11) && (barco.casaAtual<20))||((barco.casaAtual>21) && (barco.casaAtual<30))||(barco.casaAtual>31)){
                // fprintf(stderr, "NUMERO %d (%d,%d)", valorCasa, barco.px, barco.py);
                if (barco.qntPeixe<10){
                    // fprintf(stderr, "TEM %d peixes\n", barco.qntPeixe); 
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
                    fprintf(stderr, "Capacidade maxima\n"); 
                    movimentacao(direcoes, barco, line, h, w, mapa, 1, 1);
                }
            }else{
                if (barco.qntPeixe<10){movimentacao(direcoes, barco, line, h, w, mapa, 0, 1);
                }else{movimentacao(direcoes, barco, line, h, w, mapa, 1, 1);}
            }
        } //Fim do while
	}return 0;
}