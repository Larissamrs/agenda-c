#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

/*Estrutura agenda */
typedef struct agenda
{
    	char nome[50];
        char contato[50];
        char email[50];
		char rua[50];
        char numero[11];
        char cep[10];
        char bairro[50]; 
        char cidade [50];
       
}agenda;

/*Varivaies globais*/
FILE *arq;
agenda pessoa;

/*Funcao menu, onde retorna alguma opcao*/
char menu()
{
    system("cls");
    printf("***************  Agenda de Contatos: ***************\n");
    printf("\n");
    printf("[1] - Adicionar contato\n");
    printf("[2] - Mostrar lisa de contatos\n");
    printf("[3] - Procurar contato pelo Nome\n");
    printf("[4] - Modificar contato\n");
    printf("[5] - Remover contato\n");
    printf("[0] - Sair\n");
    printf("\n");
    printf("> ");
    return (toupper(getche()));
}

/*Funcao que serve para verificar se no arquivo "banco.bin", j� existe nome do contato, retornando 1*/
int verifica(char nome[])
{
    fread(&pessoa,sizeof(agenda),1,arq);
    while(!feof(arq))
    {
        if (strcmp(pessoa.nome,nome) == 0)

        {
            fseek(arq,-sizeof(agenda),SEEK_CUR);
            return 1;
        }
        fread(&pessoa,sizeof(agenda),1,arq);
    }

    return 0;
}

/*Funcao que serve para verificar se no arquivo "banco.bin", j� existe telefone do contato, retornando 1*/
int verifica_num(int num)
{
    fread(&pessoa,sizeof(agenda),1,arq);
    while(!feof(arq))
    {
        if (pessoa.contato == num)
        {
            fseek(arq,-sizeof(agenda),SEEK_CUR);
            return 1;
        }
        fread(&pessoa,sizeof(agenda),1,arq);
    }
    return 0;
}

/*Funcao para add contatos na agenda*/
void adicionar_contato()
{
   int contador = 0;
   int opcao;
    
    arq = fopen("banco.bin","a+b");
    
    if(arq == NULL){
        printf("\nERRO AO ABRIR O ARQUIVO.\n");
        return;
    }else{
    
    printf("\n\nVoce deseja realizar quantos cadastros:");
    scanf("%d", &opcao);
    
    while( contador < opcao){
    
            
    system("cls");

    printf("\n********** NOVO CADASTRO **********");
    printf("\n\n");
    
    printf("\nINFORME O SEU NOME:");
    fflush(stdin);                                            // limpa o buffer do teclado.
    scanf("%[^\n]s", pessoa.nome);                        // %[^\n]s verifica toda a string digitada ate o \n.

    printf("\nINFORME O SEU NUMERO PARA CONTATO:");
    fflush(stdin);
    scanf("%[^\n]s", pessoa.contato);

    printf("\nINFORME O SEU EMAIL:");
    fflush(stdin);
    scanf("%[^\n]s", pessoa.email);

    printf("\nINFORME O NOME DA RUA:");
    fflush(stdin);
    scanf("%[^\n]s", pessoa.rua);

    printf("\nINFORME O NUMERO DA RESIDENCIA:");
    fflush(stdin);
    scanf("%[^\n]s", pessoa.numero);

    printf("\nINFORME O NUMERO DO CEP:");
    fflush(stdin);
    scanf("%[^\n]s", pessoa.cep);

    printf("\nINFOMRE O BAIRRO:");
    fflush(stdin);
    scanf("%[^\n]s", pessoa.bairro);

    printf("\nINFORME A CIDADE:");
    fflush(stdin);
    scanf("%[^\n]s", pessoa.cidade);
    
    fwrite(&pessoa, sizeof(struct agenda) ,1,arq);
    
    contador ++;
        }
        fclose(arq);
        }
        
}

/*Funcao para modificar contato*/
void modificar()
{
    	char nome[50];
        char contato1[50];
        char email1[50];
		char rua1[50];
        char numero1[11];
        char cep1[10];
        char bairro1[50]; 
        char cidade1[50];

    arq = fopen("banco.bin","r+b");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    printf("\n\n");
    printf("Digite nome do contato: ");
    fflush(stdin);
    gets(nome);

    if (verifica(nome) == 1)
    {
        printf("\nDigite um novo nome: ");
        fflush(stdin);
        gets(nome);
        strcpy(pessoa.nome,nome);
        
        printf("\nDigite o novo contato: ");
        fflush(stdin);
        gets(contato1);
        strcpy(pessoa.contato,contato1);
        
        printf("\nDigite o novo email: ");
        fflush(stdin);
        gets(email1);
        strcpy(pessoa.email,email1);
        
        printf("\nDigite o novo nome da rua: ");
        fflush(stdin);
        gets(rua1);
        strcpy(pessoa.rua,rua1);
        
        printf("\nDigite o novo numero da residencia: ");
        fflush(stdin);
        gets(numero1);
        strcpy(pessoa.numero,numero1);
        
        printf("\nDigite o novo numero do cep: ");
        fflush(stdin);
        gets(cep1);
        strcpy(pessoa.cep,rua1);
        
        printf("\nDigite o novo nome do bairro: ");
        fflush(stdin);
        gets(bairro1);
        strcpy(pessoa.bairro,rua1);
        
        printf("\nDigite o novo nome da cidade: ");
        fflush(stdin);
        gets(cidade1);
        strcpy(pessoa.cidade,rua1);
        
        
        fwrite(&pessoa,sizeof(agenda),1,arq);
    }

    else
    {
        printf("\nNome nao existe.\n");
    }

    fclose(arq);
}

/*Funcao para remover contato*/
void remover_contato()
{
    char nome[20];
    FILE *tmp;

    arq = fopen("banco.bin","r+b");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    tmp = fopen("banco.txt","a+b");

    printf("\n\n");
    printf("Digite nome do contato: ");
    fflush(stdin);
    gets(nome);

    fread(&pessoa,sizeof(agenda),1,arq);
    while (!feof(arq))
    {

        if (strcmp(pessoa.nome,nome) != 0) //compara o nome, para exceder
        {
           fwrite(&pessoa,sizeof(agenda),1,tmp); //grava no arquivo temp
        }
        fread(&pessoa,sizeof(agenda),1,arq); //l� arquivo

    }
    fclose(arq);
    fclose(tmp);

    system("del banco.bin");
    system("ren banco.txt banco.bin");
}

/*Procura contato pelo nome*/
void procura_nome()
{
    char busca[20];

    arq = fopen("banco.bin","r+b");
    
    
    if(arq == NULL){
        printf("\nERRO AO ABRIR O ARQUIVO.\n");
        return;
    }else{
    
    system("cls");
    printf("\n ---------- BUSCAR CONTATOS ---------- \n\n");
    
    printf("\n Digite o nome que voce deseja encontrar:");
    fflush(stdin);
    scanf("%[^\n]s", busca);
    
   while(fread(&pessoa, sizeof(struct agenda), 1, arq)== 1){
        
        if(strcmp(busca, pessoa.nome) == 0){
            
            printf("\nREGISTRO ENCONTRADO!\n");
         
            printf("\nDADOS DO REGISTRO:\n");
            printf("\nnome: %s", pessoa.nome);
            printf("\ncontato: %s", pessoa.contato);
            printf("\nemail: %s", pessoa.email);
            printf("\nrua: %s", pessoa.rua);
            printf("\nnumero da residencia: %s", pessoa.numero);
            printf("\ncep: %s", pessoa.cep);
            printf("\nbairro: %s", pessoa.bairro);
            printf("\ncidade: %s", pessoa.cidade);
            printf("\n\n-----------------------------------\n\n");
                 
    }
    if(strcmp(busca, pessoa.nome) == 1){
        printf("\nREGISTRO NAO ENCONTRADO\n");
    }
       
    }
    }
    
    system("pause");
    fclose(arq);
}


/*Lista contatos*/
void mostrar_lista()
{
    arq = fopen("banco.bin","r+b");

    if(arq == NULL){
        printf("\nERRO AO ABRIR O ARQUIVO.\n");
        
    }else{
        system("cls");
        printf("\n---------- LISTA DE CONTATOS ----------\n\n");
        
        while(fread(&pessoa, sizeof(struct agenda), 1, arq)== 1){
           
        printf("nome: %s", pessoa.nome);
        printf("\ncontato: %s", pessoa.contato);
        printf("\nemail: %s", pessoa.email);
        printf("\nrua: %s", pessoa.rua);
        printf("\nnumero da residencia: %s", pessoa.numero);
        printf("\ncep: %s", pessoa.cep);
        printf("\nbairro: %s", pessoa.bairro);
        printf("\ncidade: %s", pessoa.cidade);
        printf("\n\n-----------------------------------\n\n");             

    } 
    }
    system("pause");
    fclose(arq);
    
}

/*Funcao principal*/
int main()
{
    char op;

    do
    {
        op = menu();

        switch(op)
        {
            case '1': adicionar_contato(); break;
            case '2': mostrar_lista(); break;
            case '3': procura_nome(); break;
            case '4': modificar(); break;
            case '5': remover_contato(); break;
            case '0': return 0;
        }

        printf("\n");
        system("PAUSE");

    }while (op != '9');

    return 0;
}
