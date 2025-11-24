# 🍺 Pub Management System

**Course:** Algorithms and Computer Programming II

**University:** UNICAMP

**Language:** C

## Video
<a href="https://www.youtube.com/watch?v=VaaXC4p83i0"
   target="_blank"
   rel="noopener noreferrer">
    <img width="848" height="423" alt="image" src="https://github.com/user-attachments/assets/8aa4b7b7-7c20-4571-9cd0-01bc80993ed2" />
</a>

## 📖 About the Project

This project was developed as the final assignment for the course Algorithms and Computer Programming II, taught at UNICAMP.

The objective of the system is to manage the main operations of a pub, including:

  * Registration and management of drinks and food
  
  * Order processing
  
  * Stock control
  
  * Sales report generation

The system was **implemented in C, using .txt files for data storage**, following the limits and requirements of the discipline.

I developed the project together with three classmates. **My responsibilities included**:

* Full implementation of the drink management module

* File handling functions (opening, reading, writing, rewriting)

## 🏗️ Architecture & File Structure

The project follows a modular structure to separate responsibilities:
* **Source Files (`.c`):** Contains the implementation logic.
* **Header Files (`.h`):** Contains function prototypes and struct definitions.
* **Data Persistence (`.txt`):** Uses text files as a database to store Records (Beverages, Food) and Transactions (Orders).

## 👨‍💻 My Contribution: Beverage Management & File I/O

I was responsible for the **Beverage Management Module** and the core **File Handling Layer**. Below is a detailed explanation of the logic implemented.

### 📁 File Handling Functions
To ensure code reuse and safer file operations, I created wrapper functions for standard C file operations. These functions handle error checking automatically.

* **`lerArquivo` (Read Mode `r`):** Opens files for reading data without modifying it. Used when loading data into memory or generating reports.

```c
FILE *lerArquivo(int a){
    FILE *arq;

    if (a == 1){
        arq = fopen("baseDados.txt", "r");

        if (arq == NULL){
            mensagem();
            return NULL;
        }
    }
    else {
        if (a == 2){
            arq = fopen("comidas.txt", "r");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }
        else{
            arq = fopen("pedidos.txt", "r");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }      
    }

    return arq;
}
```

* **`escreverFinalArquivo` (Append Mode `a`):** Opens files to add new records at the end. This is crucial for the "Register" functions, ensuring previous data is not lost.

```c
FILE *escreverFinalArquivo(int a){
    FILE *arq;

    if (a == 1){
        arq = fopen("baseDados.txt", "a");

        if (arq == NULL){
            mensagem();
            return NULL;
        }
    }
    else {
        if (a == 2){
            arq = fopen("comidas.txt", "a");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }
        else{
            arq = fopen("pedidos.txt", "a");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }
    }

    return arq;
}
```

* **`reescreverArquivo` (Write Mode `w`):** Opens files for rewriting. This is used during updates or status changes, where the entire list of products is saved back to the file from memory.
```c
FILE *reescreverArquivo(int a){
    FILE *arq;
    if (a == 1){
        arq = fopen("baseDados.txt", "w");

        if (arq == NULL){
            mensagem();
            return NULL;
        }
    }
    else {
        if (a == 2){
            arq = fopen("comidas.txt", "w");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }
        else{
            arq = fopen("pedidos.txt", "w");
            if (arq == NULL){
                mensagem();
                return NULL;
            }
        }
    }
 
    return arq;
}
```


### 🥤 Drink Functions

**cadastrarBebida() (Register Drink)**

* Adds new drinks to the system.

* Opens the drink file in append mode (a).

* Converts all text inputs to uppercase for standardization.

* Validates file opening.

* Saves each drink in the format: status,name,price,type,brand,quantity

```c
void cadastrarBebida()
{
    Bebida beb; // struct

    FILE *arq_escrita = escreverFinalArquivo(1);

    if (arq_escrita == NULL)
    {
        return;
    }

    char escolha = 'S', c;

    while (escolha == 'S')
    {
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        printf("Nome da bebida: ");
        fgets(beb.nome, sizeof(beb.nome), stdin);
        beb.nome[strcspn(beb.nome, "\n")] = '\0';

        printf("\n");

        printf("Preço: ");
        scanf("%f", &beb.preco);

        while ((c = getchar()) != '\n' && c != EOF)
            ;

        printf("\n");

        printf("Tipo da bebida: ");
        fgets(beb.tipo, sizeof(beb.tipo), stdin);
        beb.tipo[strcspn(beb.tipo, "\n")] = '\0';

        printf("\n");

        printf("Marca da bebida: ");
        fgets(beb.marca, sizeof(beb.marca), stdin);
        beb.marca[strcspn(beb.marca, "\n")] = '\0';

        printf("\n");

        printf("Quantidade atual de latas/garrafas: ");
        scanf("%d", &beb.quantidadeGarrafas);

        while ((c = getchar()) != '\n' && c != EOF)
            ;

        beb.status = 1;

        char *campoBebidas[] = {beb.nome, beb.tipo, beb.marca, NULL};
        converterCampos(campoBebidas);

        fprintf(arq_escrita, "%d,%s,%.2f,%s,%s,%d\n",
                beb.status, beb.nome, beb.preco, beb.tipo, beb.marca, beb.quantidadeGarrafas);

        printf("\n");

        printf("Deseja cadastrar mais algum produto (S/N)? ");
        scanf(" %c", &escolha);
        escolha = toupper((unsigned char)escolha);
        printf("\n");
    }

    fclose(arq_escrita);
}
```

**carregarBebidas() (Load Drinks)**

* Reads all drinks from the file and stores them in an array.

* Required for operations that rewrite the entire file.

* Returns the total number of drinks loaded.

```c
int carregarBebidas(Bebida bebidas[], int max_bebidas)
{
    FILE *arq = lerArquivo(1);
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo para leitura.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(arq, "%d,%49[^,],%f,%49[^,],%49[^,],%d",
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
```

**salvarBebidas() (Save Drinks)**

* Complements carregarBebidas().

* Rewrites the file with all drinks after updates.

* Ensures that any changes made by the user are preserved.

```c
void salvarBebidas(Bebida bebidas[], int num_bebidas)
{
    FILE *arq_escrita = reescreverArquivo(1);
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
```

**inativarBebida() (Deactivate Drink)**

* Marks a drink as inactive.

* Drinks cannot be deleted to preserve the integrity of older reports.

* Status values:

  * 1 → active

  * 0 → inactive

```c
void inativarBebida()
{
    Bebida bebidas[MAX_BEBIDAS];
    int num_bebidas = carregarBebidas(bebidas, MAX_BEBIDAS);

    if (num_bebidas == 0)
    {
        printf("Nenhuma bebida encontrada no arquivo.\n");
        return;
    }

    char nomeBusca[MAX_STRING];
    char escolha = 'S';
    char c;

    while (toupper(escolha) == 'S')
    {
        // Limpa buffer antes de ler o nome
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        printf("\nDigite o nome da bebida que deseja inutilizar: ");
        fgets(nomeBusca, sizeof(nomeBusca), stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

        // Converte para maiúsculas
        converteMaiuscula(nomeBusca);

        int encontrado = 0;

        for (int i = 0; i < num_bebidas; i++)
        {
            if (strcmp(bebidas[i].nome, nomeBusca) == 0)
            {
                encontrado = 1;
                if (bebidas[i].status == 0)
                {
                    printf("\n A bebida '%s' já está inativada.\n", bebidas[i].nome);
                }
                else
                {
                    bebidas[i].status = 0;
                    printf("\n Bebida '%s' inativada com sucesso!\n", bebidas[i].nome);
                }
                break;
            }
        }

        if (!encontrado)
        {
            printf("\n Bebida não encontrada. Tente novamente.\n");
        }

        printf("\nDeseja inativar outra bebida? (S/N): ");
        scanf(" %c", &escolha);
        escolha = toupper((unsigned char)escolha);
    }

    salvarBebidas(bebidas, num_bebidas);
    printf("\nAlterações salvas no arquivo com sucesso!\n\n");
}
```

**ativarBebida() (Activate Drink)**

* Reverses the action of inativarBebida().

* Reactivates a previously inactive drink.

```c
void ativarBebida()
{
    Bebida bebidas[MAX_BEBIDAS];
    int num_bebidas = carregarBebidas(bebidas, MAX_BEBIDAS);

    if (num_bebidas == 0)
    {
        printf("Nenhuma bebida encontrada no arquivo.\n");
        return;
    }

    char nomeBusca[MAX_STRING];
    char escolha = 'S';
    char c;

    while (toupper(escolha) == 'S')
    {
        // Limpa buffer antes de ler o nome
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        printf("\nDigite o nome da bebida que deseja ativar: ");
        fgets(nomeBusca, sizeof(nomeBusca), stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

        // Converte para maiúsculas
        converteMaiuscula(nomeBusca);

        int encontrado = 0;

        for (int i = 0; i < num_bebidas; i++)
        {
            if (strcmp(bebidas[i].nome, nomeBusca) == 0)
            {
                encontrado = 1;
                if (bebidas[i].status == 1)
                {
                    printf("\n A bebida '%s' já está ativada.\n", bebidas[i].nome);
                }
                else
                {
                    bebidas[i].status = 1;
                    printf("\n Bebida '%s' ativada com sucesso!\n", bebidas[i].nome);
                }
                break;
            }
        }

        if (!encontrado)
        {
            printf("\n Bebida não encontrada. Tente novamente.\n");
        }

        printf("\nDeseja ativar outra bebida? (S/N): ");
        scanf(" %c", &escolha);
        escolha = toupper((unsigned char)escolha);
    }

    salvarBebidas(bebidas, num_bebidas);
    printf("\nAlterações salvas no arquivo com sucesso!\n\n");
}
```

**atualizarBebida() (Update Drink)**

* Allows editing of any drink attribute:

  * Name

  * Price
  
  * Type
  
  * Brand
  
  * Quantity

* Loads all drinks, updates only the target one, and rewrites the file.

```c
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
    converteMaiuscula(nomeBusca);

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
                // getchar();
            }

            printf("\nProduto atualizado com sucesso!\n");

            salvarBebidas(bebidas, num_bebidas);
            break;
        }
    }

    if (!encontrado)
        printf("\nBebida não encontrada.\n");
}
```

**listarBebidas() (List Drinks)**

* Displays all drinks in the system.

* Users can filter by:
  
  * All drinks
  
  * Only active
  
  * Only inactive
 
```c
void listarBebidas()
{
    Bebida bebidas[MAX_BEBIDAS];
    int num_bebidas = carregarBebidas(bebidas, MAX_BEBIDAS);

    if (num_bebidas == 0)
    {
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
    for (int i = 0; i < num_bebidas; i++)
    {
        int mostrar = 0;

        switch (opcao)
        {
        case 1: // todas
            mostrar = 1;
            break;
        case 2: // apenas ativas
            if (bebidas[i].status == 1)
                mostrar = 1;
            break;
        case 3: // apenas inativas
            if (bebidas[i].status == 0)
                mostrar = 1;
            break;
        default:
            printf("\nOpção inválida!\n");
            return;
        }

        if (mostrar)
        {
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

    if (!exibiu)
    {
        printf("\nNenhuma bebida encontrada para o filtro escolhido.\n");
    }

    printf("\n===============================\n");
}
```
