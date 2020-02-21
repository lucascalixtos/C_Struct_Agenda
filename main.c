//PROJETO FINAL ED1
//NOME: LUCAS CALIXTO SILVA     PRONTUÁRIO: 3002543
//NOME: DANTON IEVENES FERRAZ   PRONTUÁRIO: 3001717
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "agenda.h"

int main() {
    setlocale(LC_ALL,"");
    int x, y, i; //Variáveis auxiliares
    FUNC fu;
    Lista *li;
    li = crialista(); //Criação da lista
    FILE *arquivo; //Criação da variavel que vai salvar o arquivo
    if(arquivo = fopen("dados.txt","rb")!= NULL){
        recupera_arquivo(arquivo, li);
    }
    while(x!=0) {
        system("cls");
        x = menu(); //Função que chama o menu
        system("cls");
        if(x == 1) { //Inserir novo contato
            system("cls");
            fu = add_contato(); //Abre formulário de funcionário
            y = insere_lista_ordenada(li, fu); //Insere na lista e testa se funcionou
            if(y) {
                printf("\nInserido ordenamente com sucesso");
                system("pause");
                system("cls");
            } else {
                printf("\nNao foi possivel inserir ordenadamente");
            }
        } else if(x == 2) { //Exibe toda a lista de contatos
            printf("\n**********LISTA DE CONTATOS**********\n");
            consulta_lista(li, &fu); //Chama função responsável por exibir lista
            system("pause");
        } else if(x == 3) { //Exibir funcionario por id
            int id;
            printf("Digite o id do funcionario: ");
            scanf("%d",&id);
            y = consulta_lista_id(li, id, &fu); //Chama função responvável por procurar funcionário por id
            system("cls");
            //Exibe funcionário
            printf("\nNome: %s", fu.nome);
            printf("\nID: %d", fu.id);
            printf("\nEmpresa: %s", fu.empresa);
            printf("\nDepartamento: %s", fu.dep);
            printf("\nTelefone: %d", fu.tel);
            printf("\nCelular: %d", fu.cel);
            printf("\nEmail: %s\n", fu.email);
            system("pause");
            system("cls");
        } else if(x == 4){ //Procurar funcionário por nome
            char nome[50];
            printf("Digite o nome do funcionário: ");
            getchar();
            gets(nome);
            y = consulta_lista_nome(li, nome, &fu); //Chama função responsável por consultar o nome na lista
            system("cls");
            //Exibe o funcionário caso seja encontrado
            printf("\nNome: %s", fu.nome);
            printf("\nID: %d", fu.id);
            printf("\nEmpresa: %s", fu.empresa);
            printf("\nDepartamento: %s", fu.dep);
            printf("\nTelefone: %d", fu.tel);
            printf("\nCelular: %d", fu.cel);
            printf("\nEmail: %s\n", fu.email);
            system("pause");
            system("cls");
        } else if(x == 5) { //Edita um contato já existente
            int id;
            printf("Digite o id do funcionario: ");
            scanf("%d",&id);
            y = consulta_lista_id(li, id, &fu); //Chama função que consulta funcionario por id
            if(y) { //Caso encontre, exibe as informações do funcionário
                int opc;
                system("cls");
                printf("\nNome: %s", fu.nome);
                printf("\nID: %d", fu.id);
                printf("\nEmpresa: %s", fu.empresa);
                printf("\nDepartamento: %s", fu.dep);
                printf("\nTelefone: %d", fu.tel);
                printf("\nCelular: %d", fu.cel);
                printf("\nEmail: %s\n", fu.email);
                printf("Deseja editar? \n 1. SIM \n 2. NÃO \n OPÇÃO: ");
                scanf("%d",&opc); //Pergunta se o usuário deseja editar
                if(opc == 1) {
                    remove_lista(li, id); //Remove o funcionario
                    fu = add_contato(); //Abre formulário de funcionário
                    y = insere_lista_ordenada(li, fu); //Insere na lista e testa se funcionou
                    if(y){ //Caso funcione, exibe o texto abaixo
                        printf("\nEditado com sucesso");
                        system("pause");
                        system("cls");
                    }else{//Senão, exibe a mensagem abaixo
                        printf("\nNao foi possivel editar");
                        }
                    }
                }
            }else if(x == 6){ //Remover funcionario
                int id;
                printf("Digite o id do funcionario: ");
                scanf("%d",&id);
                y = consulta_lista_id(li, id, &fu); //Consulta se funcionario existe
                if(y) {//Caso exista
                    int opc;
                    //exibe dados do funcionario
                    system("cls");
                    printf("\nNome: %s", fu.nome);
                    printf("\nID: %d", fu.id);
                    printf("\nEmpresa: %s", fu.empresa);
                    printf("\nDepartamento: %s", fu.dep);
                    printf("\nTelefone: %d", fu.tel);
                    printf("\nCelular: %d", fu.cel);
                    printf("\nEmail: %s\n", fu.email);
                    printf("Deseja remover? \n 1. SIM \n 2. NÃO \n OPÇÃO: ");
                    scanf("%d",&opc); //Pergunta se deseja remover
                    if(opc == 1) {
                        remove_lista(li, id); //Remove o funcionario da lista
                        printf("Removido com sucessos\n");
                        system("pause");
                        system("cls");
                    }
                }else{
                    printf("Funcionario não encontrado:");
                }
        }
    }
    salva_arquivo(arquivo, li); //Salva o arquivo
    free(li);
    system("pause");
}
