#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>   // biblioteca BR
#define MAX_STRING 50 // Tamanho máximo string

// PROTÓTIPOS DE FUNÇÃO - Em análise se vale a pena ser usado
/*FILE *lerArquivo();
FILE *escreverArquivo();
void cadastrarBebida(FILE *arq);
void menu();*/

// Especificações de bebidas
typedef struct bebidas
{
    char nome[MAX_STRING];
    float preco;
    char tipo[MAX_STRING]; // alcoolica, refrigerante, suco e etc
    char marca[MAX_STRING];
    int quantidadeGarrafas; // essa quantidade refere-se a garrafas e não a MLS, por isso é int
} Bebida;

// Função para poder ler o arquivo
FILE *lerArquivo()
{
    FILE *arq;

    // Pode ser necessário ajustar o caminho a depender de onde deixar o txt salvo
    arq = fopen("baseDados.txt", "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo para escrita");
        return NULL;
    }

    return arq;
}

// Função para poder escrever no arquivo
FILE *escreverArquivo()
{
    FILE *arq;

    // Pode ser necessário ajustar o caminho a depender de onde deixar o txt salvo
    arq = fopen("baseDados.txt", "a"); // Vamos usar A e não W, pois o W sobreescreve tudo

    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo para escrita");
        return NULL;
    }

    return arq;
}

void cadastrarBebida(FILE *arq)
{
    Bebida beb; // struct

    FILE *arq_escrita = escreverArquivo();

    if (arq_escrita == NULL)
    {
        return;
    }

    char escolha = 'S';
    char c;

    while (escolha == 'S')
    {
        // NOVO: Limpeza de buffer (se houver lixo do loop anterior ou do menu)
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        printf("Nome da bebida: ");
        fgets(beb.nome, sizeof(beb.nome), stdin);
        beb.nome[strcspn(beb.nome, "\n")] = '\0'; // Remove o \n do final

        // Converte para maiúsculas
        for (size_t i = 0; i < strlen(beb.nome); i++)
        {
            beb.nome[i] = toupper((unsigned char)beb.nome[i]);
        }

        printf("\n");

        printf("Preço: ");
        scanf("%f", &beb.preco);

        // Limpa o buffer após o scanf
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        printf("\n");

        printf("Tipo da bebida: ");
        fgets(beb.tipo, sizeof(beb.tipo), stdin);
        beb.tipo[strcspn(beb.tipo, "\n")] = '\0';

        // Converte para maiúsculas
        for (size_t i = 0; i < strlen(beb.tipo); i++)
        {
            beb.tipo[i] = toupper((unsigned char)beb.tipo[i]);
        }

        printf("\n");

        printf("Marca da bebida: ");
        fgets(beb.marca, sizeof(beb.marca), stdin);
        beb.marca[strcspn(beb.marca, "\n")] = '\0'; // Remove o \n do final

        // Converte para maiúsculas
        for (size_t i = 0; i < strlen(beb.marca); i++)
        {
            beb.marca[i] = toupper((unsigned char)beb.marca[i]);
        }

        printf("\n");

        printf("Quantidade atual da bebida: ");
        scanf("%d", &beb.quantidadeGarrafas);

        // Limpa o buffer após o scanf
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        // Escrita no arquivo
        fprintf(arq_escrita, "%s,%.2f,%s,%s,%d\n",
                beb.nome, beb.preco, beb.tipo, beb.marca, beb.quantidadeGarrafas);

        printf("\n");

        printf("Deseja cadastrar mais algum produto (S/N) ? ");
        scanf(" %c", &escolha);
        escolha = toupper((unsigned char)escolha);
    }

    fclose(arq_escrita);
}

void menu()
{
    int decisao;

    FILE *escrever = escreverArquivo();
    FILE *ler = lerArquivo();

    printf("Gerencie seu PUB \n");
    printf("O que deseja fazer \n");
    printf("1) Cadastrar bebidas \n");

    printf("Escolha: ");
    scanf("%d", &decisao);

    switch (decisao)
    {
    case 1:
        cadastrarBebida(escrever);
        break;

    default:
        break;
    }

    if (escrever != NULL)
        fclose(escrever);
    if (ler != NULL)
        fclose(ler);
}

int main()
{
    // código em portugues
    setlocale(LC_ALL, "Portuguese");

    menu();
    return 0;
}