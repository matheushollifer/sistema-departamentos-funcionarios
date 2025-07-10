#include <stdio.h>
#include <string.h>

#define MAX_DEPT 100
#define MAX_FUNC 100

typedef struct {
    int codigo;
    char nome[50];
    char sigla[10];
} Departamento;

typedef struct {
    int matricula;
    char nome[50];
    float salario;
    int codigoDept;
} Funcionario;

Departamento departamentos[MAX_DEPT];
Funcionario funcionarios[MAX_FUNC];
int qtdDept = 0, qtdFunc = 0;

// Função para buscar departamento pelo código
int buscaDept(int codigo) {
    for (int i = 0; i < qtdDept; i++) {
        if (departamentos[i].codigo == codigo)
            return i;
    }
    return -1;
}

// Função para buscar funcionário pela matrícula
int buscaFunc(int matricula) {
    for (int i = 0; i < qtdFunc; i++) {
        if (funcionarios[i].matricula == matricula)
            return i;
    }
    return -1;
}

void cadastrarDepartamento() {
    if (qtdDept == MAX_DEPT) {
        printf("Limite de departamentos atingido.\n");
        return;
    }
    int codigo;
    printf("Digite o código do departamento: ");
    scanf("%d", &codigo);
    if (buscaDept(codigo) != -1) {
        printf("Código já cadastrado.\n");
        return;
    }
    departamentos[qtdDept].codigo = codigo;
    printf("Digite o nome do departamento: ");
    scanf(" %[^\n]", departamentos[qtdDept].nome);
    printf("Digite a sigla do departamento: ");
    scanf(" %[^\n]", departamentos[qtdDept].sigla);
    qtdDept++;
    printf("Departamento cadastrado com sucesso!\n");
}

void cadastrarFuncionario() {
    if (qtdFunc == MAX_FUNC) {
        printf("Limite de funcionários atingido.\n");
        return;
    }
    int matricula;
    printf("Digite a matrícula do funcionário: ");
    scanf("%d", &matricula);
    if (buscaFunc(matricula) != -1) {
        printf("Matrícula já cadastrada.\n");
        return;
    }
    int codigoDept;
    printf("Digite o código do departamento: ");
    scanf("%d", &codigoDept);
    int idxDept = buscaDept(codigoDept);
    if (idxDept == -1) {
        printf("Departamento não cadastrado.\n");
        return;
    }
    funcionarios[qtdFunc].matricula = matricula;
    printf("Digite o nome do funcionário: ");
    scanf(" %[^\n]", funcionarios[qtdFunc].nome);
    printf("Digite o salário do funcionário: ");
    scanf("%f", &funcionarios[qtdFunc].salario);
    funcionarios[qtdFunc].codigoDept = codigoDept;
    qtdFunc++;
    printf("Funcionário cadastrado com sucesso!\n");
}

void consultaDepartamento() {
    int codigo;
    printf("Digite o código do departamento para consulta: ");
    scanf("%d", &codigo);
    int idx = buscaDept(codigo);
    if (idx == -1) {
        printf("Departamento não encontrado.\n");
    } else {
        printf("Código: %d\nNome: %s\nSigla: %s\n",
               departamentos[idx].codigo,
               departamentos[idx].nome,
               departamentos[idx].sigla);
    }
}

void consultaFuncionario() {
    int matricula;
    printf("Digite a matrícula do funcionário para consulta: ");
    scanf("%d", &matricula);
    int idxFunc = buscaFunc(matricula);
    if (idxFunc == -1) {
        printf("Funcionário não encontrado.\n");
    } else {
        int idxDept = buscaDept(funcionarios[idxFunc].codigoDept);
        printf("Matrícula: %d\nNome: %s\nSalário: %.2f\nDepartamento: %s\n",
               funcionarios[idxFunc].matricula,
               funcionarios[idxFunc].nome,
               funcionarios[idxFunc].salario,
               idxDept != -1 ? departamentos[idxDept].nome : "Desconhecido");
    }
}

void excluirFuncionario() {
    int matricula;
    printf("Digite a matrícula do funcionário para excluir: ");
    scanf("%d", &matricula);
    int idx = buscaFunc(matricula);
    if (idx == -1) {
        printf("Funcionário não encontrado.\n");
    } else {
        // Remove funcionário deslocando os demais
        for (int i = idx; i < qtdFunc - 1; i++) {
            funcionarios[i] = funcionarios[i + 1];
        }
        qtdFunc--;
        printf("Funcionário excluído com sucesso.\n");
    }
}

void listarDepartamentos() {
    if (qtdDept == 0) {
        printf("Nenhum departamento cadastrado.\n");
        return;
    }
    printf("Lista de Departamentos:\n");
    for (int i = 0; i < qtdDept; i++) {
        printf("Código: %d | Nome: %s | Sigla: %s\n",
               departamentos[i].codigo,
               departamentos[i].nome,
               departamentos[i].sigla);
    }
}

void listarFuncionarios() {
    if (qtdFunc == 0) {
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }
    printf("Lista de Funcionários:\n");
    for (int i = 0; i < qtdFunc; i++) {
        int idxDept = buscaDept(funcionarios[i].codigoDept);
        printf("Matrícula: %d | Nome: %s | Salário: %.2f | Departamento: %s\n",
               funcionarios[i].matricula,
               funcionarios[i].nome,
               funcionarios[i].salario,
               idxDept != -1 ? departamentos[idxDept].nome : "Desconhecido");
    }
}

int main() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1 – Cadastro de Departamento\n");
        printf("2 - Cadastro de Funcionário\n");
        printf("3 – Consulta de Departamento\n");
        printf("4 - Consulta de Funcionário\n");
        printf("5 – Excluir Funcionário\n");
        printf("6 - Listagem de Departamentos\n");
        printf("7 - Listagem de Funcionários\n");
        printf("8 - Fim\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarDepartamento(); break;
            case 2: cadastrarFuncionario(); break;
            case 3: consultaDepartamento(); break;
            case 4: consultaFuncionario(); break;
            case 5: excluirFuncionario(); break;
            case 6: listarDepartamentos(); break;
            case 7: listarFuncionarios(); break;
            case 8: printf("Encerrando programa.\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 8);

    return 0;
}
