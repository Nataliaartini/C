#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <time.h>

//structs

struct bebidas{
  int code;
  char nome [30];
  int volume;
  float preco;
  int estoque;
  int tipo; //0 = not alcooholic, 1 = alcooholic  
};

typedef struct bebidas Bebida;

struct treenode{
  Bebida bebida;
  struct treenode *left, *right;
};

typedef struct treenode Node;

struct tree{
  Node *root;
};

typedef struct tree DrinkTree;

//functions

void initTree(DrinkTree *t){
  t->root = NULL;
}

void mostraMenu(){
  printf("\n ?? BODEGAO DO JAO ?? \n");
  printf("Escolha uma das op��es abaixo:\n");
  printf("1 - Cadastrar bebida;\n2 - Listar bebidas;\n3 - Buscar bebida;\n4 - Excluir bebida;\n5 - Comprar bebida;\n6 - Vender bebida;\n7 - Sair\n?");
}

Node *searchCode(int code, Node *root){
  if(root == NULL || code == root->bebida.code) 
    return root;
  if(code < root->bebida.code) //if the code is smaller, we search in the left
    return searchCode(code,root->left);
  return searchCode(code, root->right);
}

void printSingleNode(Node *n){
  printf("C�digo: %d\nNome: %s\nVolume: %d\nPre�o: %.2f\nQuantidade em estoque: %d\nAlco�lica? ", n->bebida.code, n->bebida.nome, n->bebida.volume, 
  n->bebida.preco, n->bebida.estoque);

  if(n->bebida.tipo == 1) printf("Sim\n\n");
  else printf("N�o\n\n");
}

int validaDados(Bebida b , Node *root){
  int encontrouErro = 0;
  printf("\n");

  if(searchCode(b.code, root)){
    printf("� Par�a! se liga que voc� j� tem esse c�digo cadastrado!\n\n");
    printSingleNode(searchCode(b.code, root));  
    printf("\n");
    encontrouErro = 1;
  }
  if(b.volume < 0){
    printf("� N�o vou nem comentar essa viagem! O volume deve ser positivo...\n");
    encontrouErro = 1;
  }
  if(b.preco < 0){
    printf("� Oloco bicho, essa bebida � t�o ruim que tu vai pagar pro cara levar? O pre�o n�o pode ser um valor negativo!\n");
    encontrouErro = 1;
  }
  if(b.estoque<0){
    printf("� Ta querendo ganhar multa do le�o �? O estoque n�o pode ficar negativo!\n");
    encontrouErro = 1;
  }

  if(b.tipo != 1 && b.tipo != 0){
    printf("� N�o acha que est� muito cedo pra j� ter bebido? O tipo da bebida dever ser 1 ou 0!\n");
    encontrouErro = 1;
  }
  if(encontrouErro){
    printf("? O(s) dado(s) listado(s) acima est�o inv�lido(s). Tente novamente! ? \n");
    return encontrouErro;
  }
  else return encontrouErro;
}

Bebida recebeDados(){
  Bebida b;

  printf("\nC�digo:");
  scanf("%d", &b.code); 
  printf("Nome:");
  scanf("%s", b.nome);
  printf("Volume:");
  scanf("%d", &b.volume);
  printf("Pre�o:R$");
  scanf("%f", &b.preco);
  printf("Quantidade de Estoque:");
  scanf("%d", &b.estoque);
  printf("Digite 1 se a bebida � alco�lica e 0 se n�o:");
  scanf("%d", &b.tipo);
  return b;
}

Node *newNode(Bebida b){
  Node *n;
  n=(Node *)malloc(sizeof(Node));
  n->bebida = b;
  n->left = NULL;
  n->right = NULL;
  return n;
}

void cadastrarBebida(DrinkTree *t){
  printf("\n ? CADASTRO DE BEBIDA ? \nInsira os dados listados abaixo, isso � uma ordem!\n");
    
  Node *n, *aux, *previous;
  int dir;
  Bebida b = recebeDados();
  while(validaDados(b, t->root)){
    b = recebeDados();
  }
  n = newNode(b);
  if(t->root == NULL){ //the tree is empty, we save the root
    t->root = n;
    return;
  }
  else{ //finding the place in the tree to include
    aux=t->root; // come�a na raiz
	  dir=0;
    while (aux!=NULL){
      previous=aux;
      if (n->bebida.code < aux->bebida.code){ // new code is smaller, goes to left
        aux=aux->left;
        dir=0; // new node must be inserted as a son of left
      }
      else{
          aux=aux->right;  // else, the bigger goes to right
          dir=1; // new node must be inserted as a son of right
      }
    }
      if (dir) previous->right=n;
      else previous->left=n;
      return;
  }
}

void imprimeTree(Node *root){
  if (root==NULL) 
	{
		printf("\n");
	  return;
	}
	imprimeTree(root->left);
  printSingleNode(root);
	imprimeTree(root->right); 
}

void buscaBebida(Node *root){
  int code;
  Node *aux;
  printf("\n ? PROCURAR BEBIDA ? \n\n");
  printf("Digite o c�digo da bebida que deseja achar, voc� tem 3 desejos! Just kidding.\n?");
  scanf("%d", &code);
  aux = searchCode(code, root);
  if(aux == NULL) 
  printf("N�o achei essa bebida nos seu estoque! oops \n"); 
  else
  {
    printf("\n ? Aqui est�, chefe! ? \n\n");
    printSingleNode(aux);
  }
}

Node *maxChild(Node *root){
  Node *promoted;
  if (root->right->right == NULL)
  {
    promoted = root->right;
    root->right = promoted->left;
    promoted->left =NULL;
    return root;
  }
  return maxChild(root->right);
}

Node *deleteNode(Node *root, int code){
  Node *newRoot;
  if (root == NULL){
    printf("N�o achei essa bebida nos seu estoque! oops!\n");
    return root;
  }
  if (root->bebida.code == code) { //Se for folha;
    if (root->left == NULL && root->right == NULL){
      free(root);
      return NULL;
    } //SE TEM UM FILHO
      if (root->left == NULL || root->right == NULL) {
        newRoot = (root->left == NULL) ? root->right : root->left; //if tern�rio
        free(root);
        return newRoot;
      } 
        //SE TEM DOIS FILHOS
      if (root->left->right == NULL){
        newRoot = root->left;
        } 
      else {
        newRoot = maxChild(root->left);
        newRoot->left = root->left;
      }
      newRoot->right = root->right;
      free(root);
      return newRoot;
     } else {
        if (root->bebida.code < code) {
        root->right = deleteNode(root->right, code);
      } 
      else {
        root->left = deleteNode(root->left, code);
      }
    }
  return root;
}

void excluirBebida(DrinkTree *t){
  int code;
  Node *aux;
  printf("\n ? EXCLUIR BEBIDA ? \n\n");
  printf("TEM CERTEZA QUE DESEJA FAZER ISSO? N�O TER� VOLTA AMIG�O!!! qual o c�digo da bebida que queres excluir?\n?");
  scanf("%d", &code);
  t->root = deleteNode(t->root, code);
}

void comprarBebida(Node *root){
  int code;
  Node *aux;
  printf("\n ? COMPRAR BEBIDA ? \n\n");
  printf("Diz a� o c�digo da Bebidinha que tu comprou!\n?");
  scanf("%d", &code);
  aux = searchCode(code, root);
  if(aux == NULL) 
  printf("Rapaz, essa bebida n�o est� cadastrada, volte uma casa! \n");
  
  else{
    int qtd;
    printf("\n ? Cadastro Encontrado ? \n\n");
    printf("Quantas unidades desse licor dos deuses voc� comprou?\n?");
    scanf("%d", &qtd);
    aux->bebida.estoque = aux->bebida.estoque + qtd;
    printf("\n ? Compra realizada! Cadastro Atualizado! ?\n\n");
    printSingleNode(aux);
  }
}

void venderBebida(Node *root){
  int code, idade = 18, qtd, mes, dia, ano;
  Node *aux;
  printf("\n ? VENDER BEBIDA ? \n\n");
  printf("AEEE conseguiu fechar uma venda! Qual o c�digo do licor dos deuses voc� finalmente vendeu?\n?");
  scanf("%d", &code);
  aux = searchCode(code, root);
  if(aux == NULL)
  {
    printf("Rapaz, essa bebida n�o est� cadastrada, volte uma casa! \n");
    return;
  }

  printf("Digite a data de nascimento do cliente\n?");
  scanf("%d/%d/%d", &dia, &mes, &ano);

  struct tm *data_atual; 
  time_t segundos;
  time(&segundos); 
  data_atual = localtime(&segundos);
  
  if(aux->bebida.tipo == 1){
    if ((data_atual->tm_year+1900 - ano) < 18){
      printf("\n?Proibido vender bebidas alco�licas para menores de 18 anos seu man�!?\n\n");
      return;
    }
    
    if (data_atual->tm_year+1900 - ano == 18){
      if(data_atual->tm_mon+1 - mes < 0){
        printf("\n?Proibido vender bebidas alco�licas para menores de 18 anos seu man�!?\n\n");
        return;
      }
      if(data_atual->tm_mday-1 - dia < 0){
        printf("\n?Proibido vender bebidas alco�licas para menores de 18 anos seu man�!?\n\n");
        return;
      }
    }
  }

  printf("Quantidade de venda\n?");
  scanf("%d", &qtd);
  if(qtd > aux->bebida.estoque){
    printf("\n ? Sem estoque suficiente, irm�o! ?\n\n");
    return;
  }
  aux->bebida.estoque = aux->bebida.estoque - qtd;  
  printf("\n ? AEEE conseguiu fechar uma venda! ? \n\n");
}

void freeMemory(Node *root){
  if (root==NULL) return;
	freeMemory(root->left);
	freeMemory(root->right);
  free(root);  
}

//main

int main (){
  setlocale(LC_ALL, "Portuguese");
  DrinkTree t;
  initTree(&t);
  int opcao = 0;

  while(opcao != 7){ 
    mostraMenu();
    scanf("%d", &opcao);
      
    switch(opcao){
      case 1:
        cadastrarBebida(&t);
        break;   
      case 2:
        printf("\n ? BEBIDAS CADASTRADAS ? \n\n");
        imprimeTree(t.root);
        break;  
      case 3:
        buscaBebida(t.root);
        break;     
      case 4:
        excluirBebida(&t);
        break;     
      case 5:
        comprarBebida(t.root);
        break;      
      case 6:
        venderBebida(t.root);
        break;     
      case 7:
        freeMemory(t.root);
        break;
      default:
        printf(" ? Nem tem essa op��o seu maluco! Vacilou! Vou te dar mais uma chance, vai: ?\n");
        break;
     }
    }
  return 0;
}
