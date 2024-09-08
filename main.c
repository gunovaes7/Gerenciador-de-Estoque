#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct {
    char codigo[10];  // Mantém os zeros à esquerda
    char nome[50];
    int quantidade;
    float preco;
    char validade[11];
} produto;

produto estoque[MAX_PRODUTOS];
int total_produtos = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void adicionarProduto() {
    if (total_produtos >= MAX_PRODUTOS) {
        printf("Estoque cheio!\n");
        return;
    }

    produto novoProduto;

    printf("Codigo do produto: ");
    fgets(novoProduto.codigo, sizeof(novoProduto.codigo), stdin);
    novoProduto.codigo[strcspn(novoProduto.codigo, "\n")] = '\0';
    
    printf("Nome do produto: ");
    fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
    novoProduto.nome[strcspn(novoProduto.nome, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novoProduto.quantidade);
    limparBuffer();
    
    printf("Preco por kg: ");
    scanf("%f", &novoProduto.preco);  // Lê o preço como float, que permite 5.50
    limparBuffer();
    
    printf("Data de validade (dd/mm/aaaa): ");
    fgets(novoProduto.validade, sizeof(novoProduto.validade), stdin);
    novoProduto.validade[strcspn(novoProduto.validade, "\n")] = '\0';

    estoque[total_produtos] = novoProduto;
    total_produtos++;
    
    printf("\nProduto adicionado com sucesso!\n");
    printf("Detalhes do produto adicionado:\n");
    printf("Codigo: %s\n", novoProduto.codigo);
    printf("Nome: %s\n", novoProduto.nome);
    printf("Quantidade: %d kg\n", novoProduto.quantidade);
    printf("Preço por kg: R$%.2f\n", novoProduto.preco);  // Exibe o preço com duas casas decimais
    printf("Validade: %s\n", novoProduto.validade);
}

void removerProduto() {
    char codigo[10];
    printf("Digite o código do produto a ser removido: ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    for (int i = 0; i < total_produtos; i++) {
        if (strcmp(estoque[i].codigo, codigo) == 0) {
            for (int j = i; j < total_produtos - 1; j++) {
                estoque[j] = estoque[j + 1];
            }
            total_produtos--;
            printf("Produto removido com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

void listarProdutos() {
    if (total_produtos == 0) {
        printf("Estoque vazio!\n");
    } else {
        for (int i = 0; i < total_produtos; i++) {
            printf("Código: %s, Nome: %s, Quantidade: %d kg, Preço por kg: R$%.2f, Validade: %s\n", 
                estoque[i].codigo, estoque[i].nome, estoque[i].quantidade, estoque[i].preco, estoque[i].validade);
        }
    }
}

void salvarDados() {
    FILE *file = fopen("estoque.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < total_produtos; i++) {
        fprintf(file, "Código: %s\n", estoque[i].codigo);
        fprintf(file, "Nome: %s\n", estoque[i].nome);
        fprintf(file, "Quantidade: %d kg\n", estoque[i].quantidade);
        fprintf(file, "Preço por kg: %.2f\n", estoque[i].preco);
        fprintf(file, "Validade: %s\n\n", estoque[i].validade);
    }
    fclose(file);
}

void carregarDados() {
    FILE *file = fopen("estoque.txt", "r");
    if (file == NULL) {
        printf("Arquivo não encontrado ou formato inválido.\n");
        return;
    }

    while (!feof(file) && total_produtos < MAX_PRODUTOS) {
        fscanf(file, "Código: %[^\n]\n", estoque[total_produtos].codigo);
        fscanf(file, "Nome: %[^\n]\n", estoque[total_produtos].nome);
        fscanf(file, "Quantidade: %d kg\n", &estoque[total_produtos].quantidade);
        fscanf(file, "Preço por kg: %f\n", &estoque[total_produtos].preco);
        fscanf(file, "Validade: %[^\n]\n\n", estoque[total_produtos].validade);
        total_produtos++;
    }
    
    fclose(file);  // Certifique-se de fechar o arquivo
}

int main() {
    carregarDados();
    int opcao;

    do {
        printf("\n1. Adicionar Produto\n2. Remover Produto\n3. Listar Produtos\n4. Salvar e Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                adicionarProduto();
                break;
            case 2:
                removerProduto();
                break;
            case 3:
                listarProdutos();
                break;
            case 4:
                salvarDados();
                printf("Dados salvos. Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);

    return 0;
}
