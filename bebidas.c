#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>   // biblioteca BR
#define MAX_STRING 50 // Tamanho máximo string
#define MAX_BEBIDAS 100 //QTD máxima de bebidas

// Especificações de bebidas
typedef struct bebidas
{
    char nome[MAX_STRING];
    float preco;
    int status;
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

// Função para poder acrescentar algo no arquivo 
FILE *escreverFinalArquivo()
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

// Função para poder reescrever o arquivo
FILE *reescreverArquivo()
{
    FILE *arq;

    arq = fopen("baseDados.txt", "w"); 

    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo para escrita");
        return NULL;
    }

    return arq;
}

//Apenas para faciliar nossa vida. Na versão final excluimos
void criarCadastrosAutomaticos() {
    FILE *arq = fopen("baseDados.txt", "w"); // sobrescreve o arquivo
    if (arq == NULL) {
        printf("Erro ao criar arquivo de cadastros automáticos.\n");
        return;
    }

    // Escreve algumas bebidas de exemplo
    fprintf(arq, "1,AGUA,3.50,SEM GAS,CRYSTAL,100\n");
    fprintf(arq, "1,CERVEJA,8.90,ALCOOLICA,HEINEKEN,50\n");
    fprintf(arq, "1,REFRIGERANTE,6.00,REFRIGERANTE,COCA COLA,80\n");
    fprintf(arq, "1,SUCO,5.50,NATURAL,DELANE,40\n");
    fprintf(arq, "1,VINHO,49.90,ALCOOLICA,CONCHA Y TORO,25\n");

    fclose(arq);
    printf("Cadastros automáticos criados com sucesso!\n");
}



void cadastrarBebida() // verificar esse arq
{
    Bebida beb; // struct

    FILE *arq_escrita = escreverFinalArquivo();

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

        printf("Quantidade atual de latas/garrfas: ");
        scanf("%d", &beb.quantidadeGarrafas);

        // Limpa o buffer após o scanf
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        beb.status = 1;

        // Escrita no arquivo
        fprintf(arq_escrita, "%d,%s,%.2f,%s,%s,%d\n",
                beb.status, beb.nome, beb.preco, beb.tipo, beb.marca, beb.quantidadeGarrafas);

        printf("\n");

        printf("Deseja cadastrar mais algum produto (S/N) ? ");
        scanf(" %c", &escolha);
        escolha = toupper((unsigned char)escolha);
        printf("\n");
    }

    fclose(arq_escrita);
}

// Função para carregar as bebidas do arquivo para um array
int carregarBebidas(Bebida bebidas[], int max_bebidas)
{
    FILE *arq = lerArquivo();
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo para leitura.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(arq, "%d,%49[^,],%f,%49[^,],%49[^,],%d\n",
                  &bebidas[count].status,
                  bebidas[count].nome,
                  &bebidas[count].preco,
                  bebidas[count].tipo,
                  bebidas[count].marca,
                  &bebidas[count].quantidadeGarrafas) == 6)
    {
        count++;
        if (count >= max_bebidas)
            break;
    }

    fclose(arq);
    return count;
}

// Função para salvar todas as bebidas de volta no arquivo
void salvarBebidas(Bebida bebidas[], int num_bebidas)
{
    FILE *arq_escrita = reescreverArquivo();
    if (arq_escrita == NULL)
    {
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < num_bebidas; i++)
    {
        fprintf(arq_escrita, "%d,%s,%.2f,%s,%s,%d\n",
                bebidas[i].status,
                bebidas[i].nome,
                bebidas[i].preco,
                bebidas[i].tipo,
                bebidas[i].marca,
                bebidas[i].quantidadeGarrafas);
    }

    fclose(arq_escrita);
}

//Inativando bebidas
void inativarBebida() {
    Bebida bebidas[MAX_BEBIDAS];
    int num_bebidas = carregarBebidas(bebidas, MAX_BEBIDAS);

    if (num_bebidas == 0) {
        printf("Nenhuma bebida encontrada no arquivo.\n");
        return;
    }

    char nomeBusca[MAX_STRING];
    char escolha = 'S';
    char c;

    while (toupper(escolha) == 'S') {
        // Limpa buffer antes de ler o nome
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\nDigite o nome da bebida que deseja inutilizar: ");
        fgets(nomeBusca, sizeof(nomeBusca), stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

        // Converte para maiúsculas
        for (size_t i = 0; i < strlen(nomeBusca); i++)
            nomeBusca[i] = toupper((unsigned char)nomeBusca[i]);

        int encontrado = 0;

        for (int i = 0; i < num_bebidas; i++) {
            if (strcmp(bebidas[i].nome, nomeBusca) == 0) {
                encontrado = 1;
                if (bebidas[i].status == 0) {
                    printf("\n A bebida '%s' já está inativada.\n", bebidas[i].nome);
                } else {
                    bebidas[i].status = 0;
                    printf("\n Bebida '%s' inativada com sucesso!\n", bebidas[i].nome);
                }
                break;
            }
        }

        if (!encontrado) {
            printf("\n Bebida não encontrada. Tente novamente.\n");
        }

        printf("\nDeseja inativar outra bebida? (S/N): ");
        scanf(" %c", &escolha);
        escolha = toupper((unsigned char)escolha);
    }

    salvarBebidas(bebidas, num_bebidas);
    printf("\nAlterações salvas no arquivo com sucesso!\n\n");
}

//Ativando bebidas
void ativarBebida() {
    Bebida bebidas[MAX_BEBIDAS];
    int num_bebidas = carregarBebidas(bebidas, MAX_BEBIDAS);

    if (num_bebidas == 0) {
        printf("Nenhuma bebida encontrada no arquivo.\n");
        return;
    }

    char nomeBusca[MAX_STRING];
    char escolha = 'S';
    char c;

    while (toupper(escolha) == 'S') {
        // Limpa buffer antes de ler o nome
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\nDigite o nome da bebida que deseja ativar: ");
        fgets(nomeBusca, sizeof(nomeBusca), stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

        // Converte para maiúsculas
        for (size_t i = 0; i < strlen(nomeBusca); i++)
            nomeBusca[i] = toupper((unsigned char)nomeBusca[i]);

        int encontrado = 0;

        for (int i = 0; i < num_bebidas; i++) {
            if (strcmp(bebidas[i].nome, nomeBusca) == 0) {
                encontrado = 1;
                if (bebidas[i].status == 1) {
                    printf("\n A bebida '%s' já está ativada.\n", bebidas[i].nome);
                } else {
                    bebidas[i].status = 1;
                    printf("\n Bebida '%s' ativada com sucesso!\n", bebidas[i].nome);
                }
                break;
            }
        }

        if (!encontrado) {
            printf("\n Bebida não encontrada. Tente novamente.\n");
        }

        printf("\nDeseja ativar outra bebida? (S/N): ");
        scanf(" %c", &escolha);
        escolha = toupper((unsigned char)escolha);
    }

    salvarBebidas(bebidas, num_bebidas);
    printf("\nAlterações salvas no arquivo com sucesso!\n\n");
}


// Função de atualização completa da bebida
void atualizarBebida()
{
    Bebida bebidas[MAX_BEBIDAS];                             // máximo de bebida
    int num_bebidas = carregarBebidas(bebidas, MAX_BEBIDAS); // ANTES DE ATUALIZAR TERÁ QUE SALVAR TUDO QUE CONTINHA NO ARQUIVO

    if (num_bebidas == 0)
    {
        printf("Nenhuma bebida encontrada no arquivo.\n");
        return;
    }

    char nomeBusca[MAX_STRING];
    char c;

    // Limpa buffer
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    printf("Digite o nome da bebida que deseja atualizar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // Converte para maiúsculas
    for (size_t i = 0; i < strlen(nomeBusca); i++)
        nomeBusca[i] = toupper((unsigned char)nomeBusca[i]);

    int encontrado = 0;

    for (int i = 0; i < num_bebidas; i++)
    {
        if (strcmp(bebidas[i].nome, nomeBusca) == 0)
        {
            encontrado = 1;
            printf("\n--- Atualizando %s ---\n", bebidas[i].nome);

            char opcao;

            // TROCA O NOME
            printf("Deseja alterar o NOME? (S/N): ");
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            if (opcao == 'S')
            {
                printf("Novo nome: ");
                fgets(bebidas[i].nome, sizeof(bebidas[i].nome), stdin);
                bebidas[i].nome[strcspn(bebidas[i].nome, "\n")] = '\0';
                for (size_t j = 0; j < strlen(bebidas[i].nome); j++)
                    bebidas[i].nome[j] = toupper((unsigned char)bebidas[i].nome[j]);
            }

            // TROCAR O PREÇO
            printf("Deseja alterar o PREÇO? (S/N): ");
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
            if (opcao == 'S')
            {
                printf("Novo preço: ");
                scanf("%f", &bebidas[i].preco);
            }
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            // TROCAR O TIPO
            printf("Deseja alterar o TIPO? (S/N): ");
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            if (opcao == 'S')
            {
                printf("Novo tipo: ");
                fgets(bebidas[i].tipo, sizeof(bebidas[i].tipo), stdin);
                bebidas[i].tipo[strcspn(bebidas[i].tipo, "\n")] = '\0';
                for (size_t j = 0; j < strlen(bebidas[i].tipo); j++)
                    bebidas[i].tipo[j] = toupper((unsigned char)bebidas[i].tipo[j]);
            }

            // TROCAR A MARCA
            printf("Deseja alterar a MARCA? (S/N): ");
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            if (opcao == 'S')
            {
                printf("Nova marca: ");
                fgets(bebidas[i].marca, sizeof(bebidas[i].marca), stdin);
                bebidas[i].marca[strcspn(bebidas[i].marca, "\n")] = '\0';
                for (size_t j = 0; j < strlen(bebidas[i].marca); j++)
                    bebidas[i].marca[j] = toupper((unsigned char)bebidas[i].marca[j]);
            }

            // TROCAR A QUANTIDADE
            printf("Deseja alterar a QUANTIDADE? (S/N): ");
            scanf(" %c", &opcao);
            opcao = toupper(opcao);
            if (opcao == 'S')
            {
                printf("Nova quantidade: ");
                scanf("%d", &bebidas[i].quantidadeGarrafas);
            }

            printf("\nProduto atualizado com sucesso!\n");

            salvarBebidas(bebidas, num_bebidas);
            break;
        }
    }

    if (!encontrado)
        printf("\nBebida não encontrada.\n");
}

//listar bebidas
void listarBebidas() {
    Bebida bebidas[MAX_BEBIDAS];
    int num_bebidas = carregarBebidas(bebidas, MAX_BEBIDAS);

    if (num_bebidas == 0) {
        printf("\nNenhuma bebida cadastrada no momento.\n");
        return;
    }

    int opcao;
    printf("\n===== MENU DE LISTAGEM =====\n");
    printf("1. Mostrar TODAS as bebidas\n");
    printf("2. Mostrar apenas ATIVAS\n");
    printf("3. Mostrar apenas INATIVAS\n");
    printf("============================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    printf("\n===== LISTA DE BEBIDAS =====\n");

    int exibiu = 0;
    for (int i = 0; i < num_bebidas; i++) {
        int mostrar = 0;

        switch (opcao) {
            case 1: // todas
                mostrar = 1;
                break;
            case 2: // apenas ativas
                if (bebidas[i].status == 1) mostrar = 1;
                break;
            case 3: // apenas inativas
                if (bebidas[i].status == 0) mostrar = 1;
                break;
            default:
                printf("\nOpção inválida!\n");
                return;
        }

        if (mostrar) {
            exibiu = 1;
            printf("\n-------------------------------\n");
            printf("Nome: %s\n", bebidas[i].nome);
            printf("Preço: R$ %.2f\n", bebidas[i].preco);
            printf("Tipo: %s\n", bebidas[i].tipo);
            printf("Marca: %s\n", bebidas[i].marca);
            printf("Quantidade: %d\n", bebidas[i].quantidadeGarrafas);
            printf("Status: %s\n", bebidas[i].status == 1 ? "ATIVO" : "INATIVO");
        }
    }

    if (!exibiu) {
        printf("\nNenhuma bebida encontrada para o filtro escolhido.\n");
    }

    printf("\n===============================\n");
}


void menu()
{
    int decisao;

    do
    {
        printf("=== Gerencie seu PUB ===\n");
        printf("1) Cadastrar bebidas\n");
        printf("2) Atualizar bebida\n");
        printf("3) Inativar bebida\n");
        printf("4) Ativar bebidas\n");
        printf("5) Listar bebidas\n");
        printf("45) CADASTROS PRONTOS\n");
        printf("0) Sair\n");
        printf("Escolha: ");
        scanf("%d", &decisao);
        printf("\n");

        switch (decisao)
        {
        case 1:
            cadastrarBebida();
            break;
        case 2:
            atualizarBebida();
            break;
        case 3:
            inativarBebida();
            break;
        case 4:
            ativarBebida();
            break;
        case 5:
            listarBebidas();
            break;
        case 45: 
            criarCadastrosAutomaticos();
            break;
        case 0:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    } while (decisao != 0);
}

int main()
{
    // código em portugues
    setlocale(LC_ALL, "Portuguese");

    menu();
    return 0;
}