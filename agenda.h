typedef struct func{ //Cria��o do struct funcionarip
    char nome[50];
    int id;
    char empresa[20];
    char dep[20];
    int tel;
    int cel;
    char email[50];
}FUNC;//Define tipo

typedef struct elemento* Lista;//Define tipo lista

int tamLista(Lista *li);//Checa tamanho da lista

Lista *criaLista();//Cria lista

void apagaLista(Lista *li);//Apaga a lista

int listaVazia(Lista *li);//Verifica se a lista esta vazia

int insere_lista_ordenada(Lista *li, FUNC fu);//Insere na lista ordernadamente

int remove_lista(Lista *li, int id);//Remove da lista

int consulta_lista_id(Lista *li, int id, FUNC *fu);//Faz consulta por id

int menu();//Exibe op��es do menu

FUNC add_contato();//Fun��o respons�vel por adicionar contato

void consulta_lista(Lista *li, FUNC *fu);//Fun��o respons�vel por exibir todos contatos da lista

int consulta_lista_nome(Lista *li, char nome[], FUNC *fu);//Faz consulta na lista por nome

void salva_arquivo(FILE *arquivo, Lista *li);//Salva arquivo

void recupera_arquivo(FILE *arquivo, Lista *li);//Recupera arquivos salvos

