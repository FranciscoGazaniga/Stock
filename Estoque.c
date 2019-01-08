//Programa��o referente ao estoque de uma Estoque.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define Max_Caracteres_Produto 20 //Define a quantidade de caracteres que podem ser inseridos na vari�vel.
#define Max_Caracteres_Descricao 200 //Define a quantidade de caracteres que podem ser inseridos na vari�vel.
#define Max_Produtos 100 // Define a quantidade de produtos que podem ser inseridos no estoque.
#define TRUE 1
#define FALSE 0

int tam = 0; //Vari�vel que conta a quantidade de itens alocados no vetor.
float maior;
float menor;
float media;
int n = 0; //Conta quantos produtos est�o no arquivo.
int tam_total = 0; //Quantidade de produtos salvos e n�o salvos no estoque.
int qtd_produtos = 0; //Soma as quantidades de todos os produtos no estoque.
float somapreco = 0; //Soma os pre�os de todos os produtos no estoque.
int excluiu;
int qtd_relatorio = 0; //Conta quantos produtos aparecem no relat�rio.
int excluido[Max_Produtos];
int transformar = 1; //Vari�vel que permite transformar os itens no arquivo em itens ativos.
int vazio; //Verifica se o estoque est� vazio.
int salvou_saiu = 0; //Verifica se a op��o de salvar ao sair foi selecionada.
int alteracao = 0; //Verifica se foi realizada alguma altera��o no estoque durante a se��o.
int ordenado = 0; //Verifica se o comando ordenar produtos foi selecionado.
int ordenado_codigo[Max_Produtos];
int ordenado_quantidade[Max_Produtos];
float ordenado_preco[Max_Produtos];
int ordenado_ativo[Max_Produtos];

//Declarando as fun��es para evitar Warnings do tipo "implicit function".
void leitura_dados();
void estatistica();
void gravar();
void relatorio();
void cadastro();
void excluir();
void buscar();
void ordenar();
void deletar();
int main();

//Estrutura dos produtos da Estoque.
struct TEstoque {
    char produto[Max_Caracteres_Produto]; //Armazena os nomes dos produtos, com uma capacidade de 20 caracteres para cada nome.
    char descricao[Max_Caracteres_Descricao]; //Armazena as descri��es dos produtos, com uma capacidade de 200 caracteres para cada descri��o.
    float preco; //Armazena o pre�o dos produtos.
    int quantidade; //Armazena as quantidades de produtos no estoque.
    int codigo; //Armazena os c�digos dos produtos.
    int ativo; //Define se os produtos ser�o ativos = TRUE ou inativos = FALSE no estoque.
} Estoque[Max_Produtos];

//Estrutura dos produtos ordenados.
struct TOrdenado{
    char produto[Max_Produtos];
    char descricao[Max_Produtos];
} Ordenado[Max_Produtos];

//Fun��o para ler os dados salvos no arquivo.
void leitura_dados(){
    FILE *dados;
    dados = fopen("dados.txt", "r");

    int cod_arq, qtd_produtos_arq;
    char prod_arq[Max_Caracteres_Produto];
    char desc_arq[Max_Caracteres_Descricao];
    float preco_arq;
    int contador = 0;

    n = 0;  //zera a contagem do que est� salvo no arquivo para n�o acumular sempre que o menu for acessado.

    if(dados == NULL){
        vazio = 0;
    }

    if(dados != NULL){
        //Enquanto n�o chegar ao fim do arquivo executa.
        while((fgetc(dados)) != EOF){
            while(fgetc(dados) != '|'){
                fscanf(dados, "%05d", &cod_arq);
                Estoque[contador].codigo = cod_arq;
            }

            while(fgetc(dados) != '|'){
                fscanf(dados, "%[^|]s", prod_arq);
                strcpy(Estoque[contador].produto, prod_arq); //L� a string armazenada no vetor e copia para a struct.
            }

            while(fgetc(dados) != '|'){
                fscanf(dados, "%[^|]s", desc_arq);
                strcpy(Estoque[contador].descricao, desc_arq);
            }

            while(fgetc(dados) != '|'){
                fscanf(dados, "%d", &qtd_produtos_arq);
                Estoque[contador].quantidade = qtd_produtos_arq;
            }

            while(fgetc(dados) != '\n'){
                fscanf(dados, "%f", &preco_arq);
                Estoque[contador].preco = preco_arq;
            }

            if((Estoque[contador].ativo != FALSE) || transformar == 1){
                Estoque[contador].ativo = TRUE;
                vazio++;
            }

            contador++;
            n++; //Conta quantos produtos tem no arquivo.
        }
   }
    fclose(dados);
}

//Fun��o que calcula quantos produtos existem no estoque, qual o maior, menor e a m�dia de pre�os dos produtos.
void estatistica(){
    int a = 0;

    printf("\n******************************\n");
    printf("*   BALAN�O E ESTAT�STICAS   *\n");
    printf("******************************\n");
    printf("\nQuantidade de produtos em estoque: %d\n", qtd_produtos);
    printf("Maior pre�o: R$ %0.2f\n", maior);
    printf("Menor pre�o: R$ %0.2f\n", menor);

    media = somapreco/qtd_relatorio;

    if(tam_total == 0){
        printf("M�dia de pre�os: R$ %0.2f\n", 0);
    }
    else {
        printf("M�dia de pre�os: R$ %0.2f\n", media);
    }
    printf("\n******************************\n");
}

//Fun��o respons�vel por gerar o arquivo dos produtos no estoque.
void gravar(){
    FILE *dados;
    dados = fopen("dados.txt", "w");

    int i;

    tam_total = n + tam; //soma a quantidade de produtos salvos em arquivo com a quantidade inserida durante a se��o.
    alteracao = 0;

    //Salva os produtos cadastrados no arquivo.
    for(i = 0; i < tam_total; i++){
        if(Estoque[i].ativo == TRUE){
            fprintf(dados, "   %05d| %s | %s | %d| %0.2f\n", Estoque[i].codigo, Estoque[i].produto, Estoque[i].descricao, Estoque[i].quantidade, Estoque[i].preco);
        }
    }

    fclose(dados);

    if(salvou_saiu == 0){
        system("cls");
        printf("\n************************************\n");
        printf("*  ALTERA��ES SALVAS COM SUCESSO!  *\n");
        printf("************************************\n");
        system("pause");
        tam = 0; //Necess�rio para dar inicio a um novo vetor de produtos, visto que o primeiro j� foi salvo e pode ser zerado.
        main();
    }else{
        system("cls");
        printf("\n************************************\n");
        printf("*  ALTERA��ES SALVAS COM SUCESSO!  *\n");
        printf("************************************\n");
        printf("\n  ******************************\n");
        printf("  * O PROGRAMA FOI FINALIZADO  *\n");
        printf("  ******************************\n");
        exit(1);
    }
}

//Fun��o para gerar relat�rio e estat�sticas do estoque.
void relatorio(void){
    system("cls");

    int a = 0;
    vazio = 0; // Zera para n�o acumular durante a se��o.
    qtd_relatorio = 0; //Zera para n�o acumular durante a se��o.
    qtd_produtos = 0; //Zera para n�o acumular durante a se��o.
    somapreco = 0;

    printf("\n******************************\n");
    printf("*         ESTOQUE            *\n");
    printf("******************************\n");
    printf("\n-------------------------------------------\n");

    maior = Estoque[0].preco;
    menor = Estoque[0].preco;
    tam_total = n + tam;

    if(ordenado == 0){
        for(int i = 0; i < tam_total; i++){
        //Condi��o que lista somente os produtos ativos no estoque.
            if(Estoque[i].ativo == TRUE){
                printf("\nC�digo: %05d\n", Estoque[i].codigo);
                printf("Produto: %s\n", Estoque[i].produto);
                printf("Descri��o: %s\n", Estoque[i].descricao);
                printf("Quantidade: %d un.\n", Estoque[i].quantidade);
                printf("Pre�o: R$ %0.2f\n", Estoque[i].preco);
                printf("\n-------------------------------------------\n");
                qtd_relatorio++;
                qtd_produtos = qtd_produtos + Estoque[i].quantidade; //Soma as quantidades de cada produto.
                somapreco = somapreco + Estoque[i].preco; //Soma os pre�os de cada produto.
                vazio++; //Verifica se o estoque est� vazio.

                //Compara iniciando pelo produto na posi��o zero e aloca o de maior valor na vari�vel maior.
                if(Estoque[i].preco > maior){
                        maior = Estoque[i].preco;
                }
                //Compara iniciando pelo produto na posi��o zero e aloca o de menor valor na vari�vel menor.
                if(Estoque[i].preco < menor){
                    menor = Estoque[i].preco;
                }
            }
        }

    }else{
        maior = ordenado_preco[0];
        menor = ordenado_preco[0];

        for(int i = 0; i < tam_total; i++){
        //Condi��o que lista somente os produtos ativos no estoque.
            if(ordenado_ativo[i] == TRUE){
                printf("\nC�digo: %05d\n", ordenado_codigo[i]);
                printf("Produto: %s\n", Ordenado[i].produto);
                printf("Descri��o: %s\n", Ordenado[i].descricao);
                printf("Quantidade: %d un.\n", ordenado_quantidade[i]);
                printf("Pre�o: R$ %0.2f\n", ordenado_preco[i]);
                printf("\n-------------------------------------------\n");
                qtd_relatorio++;
                qtd_produtos = qtd_produtos + ordenado_quantidade[i]; //Soma as quantidades de cada produto.
                somapreco = somapreco + ordenado_preco[i]; //Soma os pre�os de cada produto.
                vazio++; //Verifica se o estoque est� vazio.

                //Compara iniciando pelo produto na posi��o zero e aloca o de maior valor na vari�vel maior.
                if(ordenado_preco[i] > maior){
                        maior = ordenado_preco[i];
                }
                //Compara iniciando pelo produto na posi��o zero e aloca o de menor valor na vari�vel menor.
                if(ordenado_preco[i] < menor){
                    menor = ordenado_preco[i];
                }
            }
        }
        ordenado = 0; //retorna � ordem original.
    }

    if(vazio == 0){
        printf("\nN�o h� nenhum produto no estoque.\n");
        printf("\n-------------------------------------------\n");

        printf("\n1 - Voltar\n");
        scanf("%d", &a);

        //Loop necess�rio para reconhecer quando um comando inv�lido � digitado e avisar o usu�rio.
        while(a != 1){
            printf("\nVoc� digitou um comando inv�lido, favor digitar 1 para voltar.\n");
            scanf("%d", &a);
        }

        //Condi��o para voltar ao menu.
        if(a == 1){
            main();
        }
    }else{
        estatistica();

        printf("\n1 - Ordenar por C�digo");
        printf("\n2 - Voltar\n");
        scanf("%d", &a);

        //Loop necess�rio para reconhecer quando um comando inv�lido � digitado e avisar o usu�rio.
        while(a != 1 && a != 2){
            printf("\nVoc� digitou um comando inv�lido, favor digitar 1 para voltar.\n");
            scanf("%d", &a);
        }

        //Condi��o para voltar ao menu.
        if(a == 1){
           ordenar();
        } else if (a == 2){
            main();
        }
    }
}

//Fun��o para cadastrar produtos no estoque.
void cadastro(void){
    int i = 0;
    int j = 0;
    int a = 0; //vari�vel que determina a op��o � ser selecionada.
    j = j + tam; //respons�vel por dar continuidade na ordem dos itens mesmo quando sair e voltar para a fun��o cadastro.
    j = j + n; //soma o tamanho dos itens n�o salvos (j) com os salvos (n).

    do {
        system("cls"); //limpa a tela;

        tam_total = n + tam;

        printf("\n******************************\n");
        printf("*         CADASTRO           *\n");
        printf("******************************\n");

        printf("\nC�digo: ");
        scanf("%05d", &Estoque[j].codigo);
        fflush(stdin);

        //La�o para verificar se o c�digo registrado j� existe.
        for(i = 0; i < tam_total; i++){
            //Garante que a compara��o s� ser� realizada com produtos ativos.
            if(Estoque[i].ativo == TRUE){
                //Realiza a compara��o com todos os produtos no estoque.
                while(Estoque[j].codigo == Estoque[i].codigo){
                    printf("\nO c�digo digitado j� est� em uso.\n");
                    printf("Digite um novo c�digo: ");
                    scanf("%05d", &Estoque[j].codigo);
                    fflush(stdin);
                    printf("\n");
                    i = 0;
                }
            }
         }

        printf("Produto: ");
        gets(Estoque[j].produto);

        printf("Descri��o: ");
        gets(Estoque[j].descricao);

        printf("Quantidade no estoque: ");
        scanf("%d", &Estoque[j].quantidade);

        printf("Pre�o: R$ ");
        scanf("%f", &Estoque[j].preco);

        Estoque[j].ativo = TRUE; //Determina que estes produtos estar�o ativos no estoque.

        printf("\nProduto cadastrado.\n");
        printf("\n1 - Cadastrar novo Produto");
        printf("\n2 - Voltar\n");

        scanf("%d", &a);
        getchar();

        j++;
        tam++;
        alteracao++;
        n++;
    } while(a == 1);

    //Loop necess�rio para reconhecer quando um comando inv�lido � digitado e avisar o usu�rio.
    while(a != 1 && a != 2){
        printf("\nVoc� digitou um comando inv�lido, favor digitar 1 ou 2.\n");
        scanf("%d", &a);
    }

    //Op��es apresentadas ao usu�rio ap�s o cadastro. Voltar ao menu ou continuar cadastrando produtos.
    if(a == 1){
        cadastro();
    } else if (a == 2){
        main();
    }
}

//Fun��o para excluir produtos do estoque.
void excluir(void){
    int cod2 = 0;
    int inativo = 0;
    int a = 0;
    tam_total = n + tam;

    system("cls");
    printf("\n******************************\n");
    printf("*      EXCLUIR PRODUTO       *\n");
    printf("******************************\n");

    //Verifica quantos produtos est�o inativos no estoque.
    for(int i = 0; i < tam_total; i++){
        if(Estoque[i].ativo == FALSE){
            inativo++;
        }
    }

    //Se a quantidade de produtos inativos for igual a quantidade total do estoque, ent�o n�o h� produto algum no estoque.
    if(inativo == tam_total){
        printf("\n-------------------------------------------\n");
        printf("\nN�o h� nenhum produto no estoque.\n");
        printf("\n-------------------------------------------\n");
        system("pause");
        excluiu = 0; //Informado que nenhum produto foi excluido.
        main();
    }

    printf("\nDigite o c�digo do produto a ser excluido: ");
    scanf("%d", &cod2);

    //Verifica se o c�digo digitado corresponde � algum produto no estoque, e ainda, se este � ativo, se for, passa a ser inativo.
    for(int i = 0; i < tam_total; i++){
        if(Estoque[i].codigo == cod2 && Estoque[i].ativo == TRUE){
            Estoque[i].ativo = FALSE;
            excluido[i] = Estoque[i].codigo;
            excluiu = 1; //Informa ao sistema que um produto foi excluido.
            alteracao++; //Informa ao sistema que ocorreu uma altera��o no estoque.
        }
    }

    //Verifica se existe algum produto ativo no relat�rio.
    if(vazio == 0 && tam_total == 0){
        printf("\n-------------------------------------------\n");
        printf("\nN�o h� nenhum produto no estoque.\n");
        printf("\n-------------------------------------------\n");
        system("pause");
        main();
    }

    //Verifica se um produto foi excluido.
    if(excluiu == 1){
        printf("\n-------------------------------------------\n");
        printf("\nO produto %03d foi exclu�do com sucesso.\n", cod2);
        printf("\n-------------------------------------------\n");
        printf("\n1 - Continuar\n2 - Voltar para o menu.\n");
        excluiu = 0;
        alteracao++;
    }else if(excluiu == 0 || vazio == 0){
        printf("\n-------------------------------------------\n");
        printf("\nO produto buscado n�o consta no estoque.\n");
        printf("\n-------------------------------------------\n");
        printf("\n1 - Continuar\n2 - Voltar para o menu.\n");
    }

    scanf("%d", &a);

    if (a == 2){
        main();
    } else if (a == 1){
        excluir();
    }

    //Loop necess�rio para reconhecer quando um comando inv�lido � digitado e avisar o usu�rio.
    while(a != 1 && a != 2){
        printf("\nVoc� digitou um comando inv�lido, favor digitar 1 ou 2.\n");
        scanf("%d", &a);
    }

    excluiu = 0;
    main();
}

//Fun��o para buscar um produto no estoque.
void buscar(void){
    system("cls"); //limpa a tela;

    int busca_codigo;
    int tam_total = n + tam;
    int count = 0;
    int a;
    int inativo = 0;

    printf("\n******************************\n");
    printf("*     BUSCAR NO ESTOQUE      *\n");
    printf("******************************\n");

    //Verifica quantos produtos est�o inativos no estoque.
    for(int i = 0; i < tam_total; i++){
        if(Estoque[i].ativo == FALSE){
            inativo++;
        }
    }

    //Se a quantidade de produtos inativos for igual a quantidade total do estoque, ent�o n�o h� produto algum no estoque.
    if(inativo == tam_total){
        printf("\n-------------------------------------------\n");
        printf("\nN�o h� nenhum produto no estoque.\n");
        printf("\n-------------------------------------------\n");
        system("pause");
        excluiu = 0;
        main();
    }

    printf("\nDigite o c�digo do produto que voc� est� procurando: ");
    scanf("%05d", &busca_codigo);

    //Verifica se a busca digitada � igual ao c�digo de algum produto ativo no estoque.
    for(int i = 0; i < tam_total; i++){
        if(Estoque[i].ativo == TRUE){
            if(Estoque[i].codigo == busca_codigo){
                printf("\n-------------------------------------------\n");
                printf("\nC�digo: %05d\n", Estoque[i].codigo);
                printf("Produto: %s", Estoque[i].produto);
                printf("\nDescri��o: %s", Estoque[i].descricao);
                printf("\nQuantidade: %d\n", Estoque[i].quantidade);
                printf("Pre�o: %0.2f\n", Estoque[i].preco);
                printf("\n-------------------------------------------\n");
                break;
            }
            count++;
        }
    }

    //Verifica se o la�o passou por todos os produtos no estoque, caso tenha, a busca realizada n�o tem correspond�ncia.
    if(count == tam_total){
        printf("\n-------------------------------------------\n");
        printf("\nO c�digo inserido n�o corresponde � nenhum produto do estoque.\n");
        printf("\n-------------------------------------------\n");
    }

    printf("\n1 - Nova Busca");
    printf("\n2 - Voltar\n");
    scanf("%d", &a);

    //Loop necess�rio para reconhecer quando um comando inv�lido � digitado e avisar o usu�rio.
    while(a != 1 && a != 2){
        printf("\nVoc� digitou um comando inv�lido, favor digitar 1 ou 2.\n");
        scanf("%d", &a);
    }

    //Condi��es para voltar ao menu ou continuar procurando.
    if(a == 1){
        buscar();
    } else if (a == 2){
        main();
    }
}

//Fun��o para deixar em ordem os produtos do estoque.
void ordenar(void){
    int c = 0;

    for(int i = 0; i < tam_total; i++){
        for(int j = 0; j < tam_total; j++){
            //Conta quantas vezes o Estoque[i].codigo � maior do que o comparado, o resultado desta contagem ser� sua posi��o.
            if(Estoque[i].codigo > Estoque[j].codigo){
                c++;
            }
        }
        //Armazena nos vetores criados na posi��o contada os dados da Estoque.
        ordenado_codigo[c] = Estoque[i].codigo;
        strcpy(Ordenado[c].produto, Estoque[i].produto);
        strcpy(Ordenado[c].descricao, Estoque[i].descricao);
        ordenado_quantidade[c] = Estoque[i].quantidade;
        ordenado_preco[c] = Estoque[i].preco;
        ordenado_ativo[c] = Estoque[i].ativo;
        c = 0;
    }

    ordenado = 1; //Indica que a op��o de ordenar os itens foi selecionada.
    relatorio();
}

//Fun��o para excluir o estoque.
void deletar(void){
    int a=0;

    system("cls");

    tam_total = n + tam;

    printf("\n******************************\n");
    printf("*     EXCLUIR O ESTOQUE      *\n");
    printf("******************************\n");

    if(vazio == 0){
            printf("\n-------------------------------------------\n");
            printf("\nN�o h� nenhum produto no estoque.\n");
            printf("\n-------------------------------------------\n");
            system("pause");
            main();
    }

    printf("\nTem certeza de que deseja deletar o estoque atual?\n");
    printf("\n1- Sim");
    printf("\n2- N�o\n");
    scanf("%d", &a);

    if (a == 2){
        main();
    } else if (a == 1){
        for(int i = 0; i < tam_total; i++){
            Estoque[i].ativo = FALSE;
            excluiu = 1; //Informa ao sistema que um produto foi excluido mas ainda n�o foi salvo.
        }
        system("cls");
        alteracao = 1; //Informa ao sistema que foi feita uma altera��o no estoque.
        printf("\n******************************\n");
        printf("*     EXCLUIR O ESTOQUE      *\n");
        printf("******************************\n");
        printf("\n-------------------------------------------\n");
        printf("\nEstoque exclu�do com sucesso!\n");
        printf("\n-------------------------------------------\n");
        system("pause");
        main();
    }

    //Loop necess�rio para reconhecer quando um comando inv�lido � digitado e avisar o usu�rio.
    while(a != 1 && a != 2){
        printf("\nVoc� digitou um comando inv�lido, favor digitar 1 ou 2.\n");
        scanf("%d", &a);
    }
}

//Fun��o para sair do programa.
void sair(void){
    int a = 0;
    tam_total = n + tam;

    system("cls");

    //Verifica se algum produto foi inserido ou excluido no estoque.
    if(tam_total != n || alteracao != 0){
        printf("\n**************************\n");
        printf("*        SAINDO...       *\n");
        printf("**************************\n");
        printf("\nDeseja salvar as altera��es realizadas?\n");
        printf("\n1 - Sim\n");
        printf("2 - N�o\n");
        scanf("%d", &a);

        if (a == 2){
            system("cls");
            printf("\n******************************\n");
            printf("* O PROGRAMA FOI FINALIZADO  *\n");
            printf("******************************\n");
            exit(1);
        } else if (a == 1){
            system("cls");
            salvou_saiu++;
            gravar();
        }

        //Loop necess�rio para reconhecer quando um comando inv�lido � digitado e avisar o usu�rio.
        while(a != 1 && a != 2){
            printf("\nVoc� digitou um comando inv�lido, favor digitar 1 ou 2.\n");
            scanf("%d", &a);
        }
    }else{
        printf("\n******************************\n");
        printf("* O PROGRAMA FOI FINALIZADO  *\n");
        printf("******************************\n");
        exit(1);
    }
}

//Menu.
int main(){
    setlocale(LC_ALL, "Portuguese"); //Permite acentos e � nas strings.
    system("cls"); //Limpa a tela.

    int opcao;

    leitura_dados();
    transformar = 0;

    printf("\n*************************\n");
    printf("*       ESTOQUE         *\n");
    printf("*************************\n");

    printf("\n1 - Buscar Produto\n");
    printf("2 - Gerar Relat�rio do Estoque\n");
    printf("3 - Cadastrar Produto\n");
    printf("4 - Excluir Produto\n");
    printf("5 - Excluir Estoque\n");
    printf("6 - Salvar\n");
    printf("7 - Sair\n\n");

    scanf("%d", &opcao);

    //Loop necess�rio para reconhecer quando um comando inv�lido � digitado e avisar o usu�rio.
    while(opcao > 7){
        printf("\nVoc� digitou um comando inv�lido, favor escolher uma das op��es acima.\n");
        scanf("%d", &opcao);
    }

    switch(opcao){
        case 1:
            buscar();
            break;
        case 2:
            relatorio();
            break;
        case 3:
            n = 0; //Zera a contagem de produtos no arquivo para evitar ac�mulo.
            leitura_dados(); //Conta os produtos salvos.
            cadastro();
            break;
        case 4:
            excluir();
            break;
        case 5:
            deletar();
            break;
        case 6:
            transformar = 1; //Garante com que todos os itens no arquivo se tornem ativos.
            gravar();
            break;
        case 7:
            sair();
    }
}

