#include "listadeprodutos.h"

PLISTA criarLista(){
  PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
  int x;
  for (x=0;x<NUMTIPOS;x++){
    res->LISTADELISTAS[x]=(PONT) malloc(sizeof(REGISTRO));
    res->LISTADELISTAS[x]->id=-1;
    res->LISTADELISTAS[x]->quantidade=0;
    res->LISTADELISTAS[x]->valorUnitario=0;
    res->LISTADELISTAS[x]->proxProd=NULL;
  }
  return res;
}


int tamanho(PLISTA l){
  int tam = 0;
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      atual = atual->proxProd;
      tam++;
    }
  }
  return tam;
}

PONT buscarID(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual;
      atual = atual->proxProd;
    }
  }
  return NULL;
}

PONT buscarIDTipo(PLISTA l, int id, int tipo){
  if (tipo<0 || tipo>=NUMTIPOS) return NULL;
  PONT atual = l->LISTADELISTAS[tipo]->proxProd;
  while (atual) {
    if (atual->id == id) return atual;
    atual = atual->proxProd;
  }
  return NULL;
}

PONT buscarIDSecExc(PLISTA l, int id, PONT* ant){
  PONT i = buscarID(l,id);

  *ant = i;
  PONT atual = i->proxProd;
  while (atual!=NULL && atual->id != id ){
	  *ant = atual;
	  atual = atual->proxProd;
  }
  if (atual != NULL && atual->id == id) return atual;
  return NULL;
}

void exibirLog(PLISTA f){
  int numElementos = tamanho(f);
  printf("Log lista [elementos: %i]\n", numElementos);
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    printf("  #TIPO: %i -> ", x);
    atual = f->LISTADELISTAS[x]->proxProd;
    while (atual){
      printf(" [%i;%i;%i;$%i]", atual->id, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
      atual = atual->proxProd;
    }
    printf("\n");
  }
  printf("\n");
}

int consultarValorUnitario(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual->valorUnitario;
      atual = atual->proxProd;
    }
  }
  return 0;
}
int obtemTipo(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return x;
      atual = atual->proxProd;
    }
  }
  return 0;   
}



/*Funcao auxiliar para a busca de acordo com o valor unitario*/
PONT buscarValorSecExc(PLISTA l, int valor,int tipo,int qtde, PONT* ant){
  *ant = l->LISTADELISTAS[tipo];
  PONT atual = l->LISTADELISTAS[tipo]->proxProd;
  
  while (atual!=NULL && (atual->valorUnitario*atual->quantidade) < valor*qtde ){
    *ant = atual;
    atual = atual->proxProd;
  }
  if ((atual != NULL) && ((atual->valorUnitario*atual->quantidade) < valor*qtde)) return atual;
  return NULL;
  
}


bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){
    
  if (id<=0 || tipo<=0 || quantidade<=0 || valor<=0 || buscarIDTipo(l, id, tipo)||buscarID(l,id)) 
      return false;
	  

  /*PONT ant = NULL;
  PONT atual = l->LISTADELISTAS[tipo];

  while (atual != NULL && atual->quantidade*atual->valorUnitario< valor*quantidade) {
    ant = atual;
    atual = atual->proxProd;
  }*/
  PONT ant , novo;
	novo=buscarValorSecExc(l,valor,quantidade,&ant);
	if(i != NULL ) return false;
	novo=(PONT)malloc(sizeof(REGISTRO));
  

  PONT novo = (PONT) malloc(sizeof(REGISTRO));
  
  novo->id = id;
  novo->quantidade = quantidade;
  novo->valorUnitario = valor;

  novo->proxProd = atual->proxProd;

  if (ant == NULL) 
      l->LISTADELISTAS[tipo] = novo;
  else 
      ant->proxProd = novo;
  return true;
}



bool removerItensDeUmProduto(PLISTA l, int id, int quantidade){
  if (id<=0 ||quantidade<=0 ||buscarID(l,id)==NULL) 
      return false;
  PONT ant, i ,j , k;
  i = buscarIDSecExc(l,id,&ant);
  if (!i || quantidade <= 0) return false;

  int tipo = obtemTipo(l,id);

	j = (PONT)malloc(sizeof(REGISTRO));
	j->quantidade = (i->quantidade) - quantidade;
	j->id = id;
	j->valorUnitario = i->valorUnitario;

  excluirElemMatriz(&l,tipo,id);  

  /*if (ant==NULL) 
      l->LISTADELISTAS[tipo] = i->proxProd;
  else 
      ant->proxProd = i->proxProd;
  free(i);*/

	inserirNovoProduto(l,j->id,tipo,j->quantidade,j->valorUnitario);
 
  return true;
}

bool excluirElemMatriz(PLISTA* l, int tipo, int id){
  if (tipo<0 || tipo>=0 || id<0 || id >= 0) return false;
  PONT ant = NULL;
  PONT atual = l->LISTADELISTAS[tipo];

  buscarValorSecExc(&l,valor,tipo,int qtde, PONT* ant)
  
  if (atual == NULL || atual->id != id) return false;
  if (ant==NULL) l->LISTADELISTAS[tipo] = atual->proxProd;
  else ant->proxProd = atual->proxProd;
  free(atual);
  return true;
}


/* bool atualizarValorDoProduto(PLISTA l, int id, int valor){

  ARRUMAR 
  if (atual != NULL && atual->coluna == col) {
      if (val == 0) {
          if (ant==NULL) 
              m->A[tipo] = atual->proxProd;
          else 
              ant->proxProd = atual->proxProd;
          free(atual);
      }
      else atual->valor = val;
  

  return false;
}*/