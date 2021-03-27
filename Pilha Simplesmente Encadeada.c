#include <stdio.h>
#include <stdlib.h>
#define TAM_STR 80

typedef char texto_t[TAM_STR];

typedef struct Contato_T
{
    int id;
} Contato;

Contato *criarContato()
{
    Contato *contato = (Contato *)malloc(sizeof(Contato));
    printf("Identificador: ");
    scanf("%d", &contato->id);
    printf("\n");
    return contato;
}

void mostrarContato(Contato *contato)
{
    printf("Identificador: %d\n\n", contato->id);
}

typedef Contato TipoItem;

typedef struct Celula_T
{
    TipoItem *item;
    struct Celula_T *proximo;
} Celula;

Celula *criarCelula(TipoItem *item, Celula *prox)
{
    Celula *celula = (Celula *)malloc(sizeof(Celula));

    if (celula != NULL)
    {
        celula->item = item;
        celula->proximo = prox;
    }
    return celula;
}

typedef struct Pilha_T
{
    Celula *primeiro;
    Celula *ultimo;
    int quantos;
} Pilha;

Pilha *criarPilha()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));

    if (pilha != NULL)
    {
        pilha->primeiro = pilha->ultimo = NULL;
        pilha->quantos = 0;
    }
    return pilha;
}

int estah_vazia(Pilha *pilha)
{
    if ((pilha == NULL) || (pilha->quantos == 0))
        return 1;

    return 0;
}

int item_ehIgual(TipoItem *item1, TipoItem *item2)
{
    if ((item1 != NULL) && (item2 != NULL) && (item1->id == item2->id))
        return 1;

    return 0;
}

int empilhar(Pilha *pilha, TipoItem *item)
{
    if (pilha == NULL)
        return 0;
    else
    {
        Celula *novo = criarCelula(item, pilha->primeiro);

        if (novo == NULL)
            return 0;

        pilha->primeiro = novo;

        if (estah_vazia(pilha) == 1)
            pilha->ultimo = novo;

        pilha->quantos++;

        return 1;
    }
}

TipoItem *desempilhar(Pilha *pilha)
{
    if ((pilha == NULL) || (estah_vazia(pilha) == 1))
        return NULL;

    Celula *aux = pilha->primeiro;

    pilha->primeiro = aux->proximo;
    aux->proximo = NULL;
  
    TipoItem *dado = aux->item;

    free(aux);
    pilha->quantos--;
    return dado;
}

int tamanho(Pilha *pilha)
{

    if (pilha == NULL)
        return 0;

    return pilha->quantos;
}

TipoItem **obterArray(Pilha *pilha)
{
    TipoItem **array = (TipoItem **)malloc(tamanho(pilha) * sizeof(TipoItem *));

    Celula *aux = pilha->primeiro;
    for (int i = 0; i < tamanho(pilha); i++)
    {
        array[i] = aux->item;
        aux = aux->proximo;
    }
    return array;
}

int menu()
{
    int opcao;

    printf("\n1. Adicionar\n");
    printf("2. Remover\n");
    printf("3. Listar todos\n");
    printf("4. Sair\n");
    printf("\nOpcao: ");

    scanf("%d", &opcao);
    fflush(stdin);
    return opcao;
}

int main()
{
    int opcao = 4;
    Pilha *pilha = criarPilha();
    Contato *contato;
    int id;

    do
    {
        opcao = menu();

        switch (opcao)
        {
        case 1: printf("\n### ADICIONAR ####\n"); contato = criarContato(); empilhar(pilha, contato); break;

        case 2: printf("\n### REMOVER ####\n"); contato = desempilhar(pilha);
        if (contato != NULL)
            {
                printf("*** Contato Excluido ***\n");
                mostrarContato(contato);
            }
            else
                printf("Excluir:: Sem contatos para excluir\n\n");
            break;

        case 3: printf("\n### LISTAR ####\n"); Contato **contatos = obterArray(pilha);
            for (int i = 0; i < tamanho(pilha); i++)
            {
                printf("**************************\n");
                mostrarContato(contatos[i]);
            }
            break;

        case 4: printf("\n### SAIR ####\n"); exit(1); break;
        }
        system("pause");
        system("cls");
    } 
    while (opcao != 4);

    return 0;
}