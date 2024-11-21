#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ALUNOS 50

struct Aluno
{
    char nome[100];
    float nota01, nota02, nota03, media;
    char situacao[15];
};

void InputNotasAlunos(struct Aluno alunos[], int *totalAlunos);
float MediaNotas(float nota01, float nota02, float nota03);
void Situacao(struct Aluno alunos[], int totalAlunos);
void RecebeNotas(float *nota);
void Destaque();
void Reprovados();
void Avaliacao();

struct Aluno alunos[MAX_ALUNOS];
int totalAlunos = 0;

int main()
{
    printf("Bem-vindo(a)!\nOs alunos ja realizaram as 3 provas de pontuacao de 0 a 100 pontos. Vamos ver como ficaram os resultados!!\n");

    InputNotasAlunos(alunos, &totalAlunos);

    // Calculando a média de cada aluno
    for (int i = 0; i < totalAlunos; i++)
    {
        alunos[i].media = MediaNotas(alunos[i].nota01, alunos[i].nota02, alunos[i].nota03);
    }

    // Calculando a situação de cada aluno
    Situacao(alunos, totalAlunos);

    // Exibindo os resultados
    for (int i = 0; i < totalAlunos; i++)
    {
        printf("Aluno(a) %s teve media de: %.2f\nPortanto, ele(a) esta %s\n\n", alunos[i].nome, alunos[i].media, alunos[i].situacao);
    }

    Destaque();

    Reprovados();

    Avaliacao();

    printf("Pressione qualquer tecla para encerrar...\n");
    getchar(); // Para capturar o caractere de nova linha
    getchar(); // Espera o usuário pressionar uma tecla
    return 0;
}

void InputNotasAlunos(struct Aluno alunos[], int *totalAlunos)
{
    char resp;
    while (*totalAlunos < MAX_ALUNOS)
    {
        printf("Qual o nome do Aluno(a)?\n");
        scanf("%s", alunos[*totalAlunos].nome);
        printf("Notas:\nProva 01:\n");
        RecebeNotas(&alunos[*totalAlunos].nota01);
        printf("Prova 02:\n");
        RecebeNotas(&alunos[*totalAlunos].nota02);
        printf("Prova 03:\n");
        RecebeNotas(&alunos[*totalAlunos].nota03);

        (*totalAlunos)++;

        printf("Ha mais alunos? (S - N): ");
        scanf(" %c", &resp);
        if (resp == 'N' || resp == 'n')
        {
            break;
        }
    }
}

float MediaNotas(float nota01, float nota02, float nota03)
{
    return (nota01 + nota02 + nota03) / 3.0;
}

void Situacao(struct Aluno alunos[], int totalAlunos)
{
    for (int i = 0; i < totalAlunos; i++)
    {
        if (alunos[i].media >= 65)
        {
            strcpy(alunos[i].situacao, "Aprovado(a)");
        }
        else if (alunos[i].media >= 40)
        {
            strcpy(alunos[i].situacao, "de recuperacao");
        }
        else
        {
            strcpy(alunos[i].situacao, "Reprovado(a)");
        }
    }
}
void RecebeNotas(float *nota)
{
    scanf("%f", nota);
    if (*nota < 0 || *nota > 100)
    {
        printf("Nota invalida! Programa encerrado.\n");
        exit(0);
    }
}
void Destaque()
{
    char alunoDestaqueNome[100];
    float alunoDestaqueMedia = 0;
    for (int x = 0; x < totalAlunos; x++)
    {
        if (alunos[x].media > alunoDestaqueMedia)
        {
            alunoDestaqueMedia = alunos[x].media;
            strcpy(alunoDestaqueNome, alunos[x].nome);
        }
    }
    printf("\nO(a) aluno(a) com maior nota foi %s com media de %.2f.\n", alunoDestaqueNome, alunoDestaqueMedia);
}

void Reprovados()
{
    char listaReprovados[MAX_ALUNOS][100];
    char listaAprovados[MAX_ALUNOS][100];
    int contadorReprovados = 0;
    int contadorAprovados = 0;

    for (int x = 0; x < totalAlunos; x++)
    {
        if (alunos[x].media < 65)
        {
            strcpy(listaReprovados[contadorReprovados], alunos[x].nome);
            contadorReprovados++;
        }
        else
        {
            strcpy(listaAprovados[contadorAprovados], alunos[x].nome);
            contadorAprovados++;
        }
    }

    printf("Foram aprovados %d\n", contadorAprovados);
    for (int x = 0; x < contadorAprovados; x++)
    {
        printf("%s \n", listaAprovados[x]);
    }

    printf("Foram reprovados %d\n", contadorReprovados);
    for (int x = 0; x < contadorReprovados; x++)
    {
        printf("%s \n", listaReprovados[x]);
    }
}
void Avaliacao()
{
    char resp;
    bool respCorreta = false;
    do
    {
        printf("Gostou da aplicacao? (S - N)\n");
        scanf(" %s", &resp);
        if(resp == 's' || resp == 'S')
        {
            respCorreta = true;
        } else 
        {
            respCorreta = false;
            printf("Tente novamente! \n");
        }
    } while(!respCorreta);
}
