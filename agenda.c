#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "agenda.h"

struct elemento{
    FUNC dados;
    struct elementos *prox;
};
typedef struct elemento ELEM;

//Fun��o padr�o de cria��o de listas
Lista *crialista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

//Fun��o padr�o para apagar listas
void apagaLista(Lista *li){
    if(li != NULL){
        ELEM *no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

//Fun��o padr�o para verificar se lista esta vazia
int listaVazia(Lista *li){
    if(li == NULL){
        return 1;
    }
    if(*li == NULL){
        return 1;
    }
    return 0;
}

//Fun��o padr�o para inserir em lista ordenada
int insere_lista_ordenada(Lista *li, FUNC fu){
    if(li == NULL){
        return 0;
    }
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if(no == NULL){
        return 0;
    }
    no->dados = fu;
    if(listaVazia(li)){
        no->prox = (*li);
        *li = no;
        return 1;
    }else{
        ELEM *ant, *atual = *li;
        while(atual != NULL && atual->dados.id < fu.id){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = ant->prox;
            ant->prox = no;
        }
        return 1;
    }
}

//Fun��o padr�o para remover contato da lista
int remove_lista(Lista *li, int id){
    if(li == NULL){
        return 0;
    }
    ELEM *ant, *no = *li;
    while(no != NULL && no->dados.id != id){
        ant = no;
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }
    if(no == *li){
        *li = no->prox;
    }else{
        ant->prox = no->prox;
    }
    free(no);
    return 1;
}

//Fun��o padr�o de consulta por id
int consulta_lista_id(Lista *li, int id, FUNC *fu){
    if(li == NULL){
        return 0;
    }
    ELEM *no = *li;
    while(no != NULL && no->dados.id != id){
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }else{
        *fu = no->dados;
        return 1;
    }
}

//FUn��o de consulta por nome
int consulta_lista_nome(Lista *li, char nome[], FUNC *fu){
    if(li == NULL){ //Caso lista esteja vazia, retorna 0
        return 0;
    }
    ELEM *no = *li;
    while(no != NULL && strcmp(no->dados.nome, nome)!= 0){ //Faz compara��o do nome digitado pelo usuario, e os nomes existentes na lista
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }else{
        *fu = no->dados;
        return 1;
    }
}

//Faz consulta de todos usuarios cadastrados
void consulta_lista(Lista *li, FUNC *fu){
    if(li == NULL){ //Se a lista estiver vazia retorna mensagem abaixo
        printf("nenhum contato encontrado\n");
    }
    ELEM *no = *li;
    while(no != NULL){ //Enquanto houver contatos, a repeti��o continuar�
        *fu = no->dados;
        //Exibe todos contatos da lista
        printf("\nNome: %s", fu->nome);
        printf("\nID: %d", fu->id);
        printf("\nEmpresa: %s", fu->empresa);
        printf("\nDepartamento: %s", fu->dep);
        printf("\nTelefone: %d", fu->tel);
        printf("\nCelular: %d", fu->cel);
        printf("\nEmail: %s\n", fu->email);
        printf("\n");
        no = no->prox;

    }
    if(no == NULL){
        system("pause");
    }
}


int menu(){ // Menu simples, que retorna variavel de controle
    int x;
    printf("Selecione um das op��es abaixo: \n");
    printf("1 - Inserir novo contato\n");
    printf("2 - Exibir todos os contatos\n");
    printf("3 - Busca por identificador\n");
    printf("4 - Busca por nome\n");
    printf("5 - Editar contato\n");
    printf("6 - Remover contato\n");
    printf("0 - Sair\n");
    printf("Op��o:");
    scanf("%d",&x);
    return x;
}

FUNC add_contato(){ //Adicionar contatos a lista, e retorna logo ap�s prenchidos
    printf("\n******CADASTRAR******\n");
    FUNC fu;
    printf("\nDigite o nome do funcion�rio: ");
    getchar();
    gets(fu.nome);
    printf("\n");
    printf("Digite o id do funcion�rio: ");
    scanf("%d",&fu.id);
    printf("\nDigite a empresa do funcion�rio: ");
    getchar();
    gets(fu.empresa);
    printf("\nDigite o departamento do funcion�rio: ");
    gets(fu.dep);
    printf("\nDigite o telefone do funcion�rio: ");
    scanf("%d",&fu.tel);
    printf("\nDigite o celular do funcion�rio: ");
    scanf("%d",&fu.cel);
    printf("\nDigite o email do funcion�rio: ");
    getchar();
    gets(fu.email);
    return fu;
}

//fun��o padr�o para verificar tamanho da lista
int tamLista(Lista *li){
    if(li == NULL){
        return 0;
    }
    int acum = 0;
    ELEM *no = *li;
    while(no != NULL){
        acum++;
        no = no->prox;
    }
    return acum;
}

//Fun��o respons�vel por salvar dados em bin�rio
void salva_arquivo(FILE *arquivo, Lista *li){
    ELEM *no = *li;
    arquivo = fopen("dados.txt","wb");
    while(no != NULL){ //Repete enquanto a lista n�o chegar ao fim
       fwrite(&no->dados, sizeof(FUNC), 1, arquivo);
       no = no->prox;
    }
    fclose(arquivo);
}

//Fun��o respons�vel por recuperar todos os arquivos do arquivo binario
void recupera_arquivo(FILE *arquivo, Lista *li){
    FUNC fu;
    arquivo = fopen("dados.txt","rb"); //Abre o arquivo
    while(!feof(arquivo)){//repete enquanto o arquivo n�o chegar ao fim
        fread(&fu, sizeof(FUNC), 1, arquivo); //Le o arquivo e passa para a variavel fu
        insere_lista_ordenada(li, fu); //insere na lista
    }
    fclose(arquivo);//fecha o arquivo
}

