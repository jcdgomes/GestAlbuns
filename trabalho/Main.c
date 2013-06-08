/*
****************************************************************
*  Nome    : Gestao de repositorio musical                     *
*  Autores : a5571, a7829, a7813                               *
*  Data    : 14/06/2013                                        *
*  Versãon : 1.0                                               *
****************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>	//touper
#include "header.h"
#include <locale.h>


int main()
{


	listaAlbum ListaAlbuns;
	listaFaixa pListaFaixas;
	struct album *auxAlbum=NULL;
	int opcao = -1;


	char album[30];
	char tituloFaixa[30];
	int cod_album, codigoFaixa, duracao, posicao;
	char continua, guardar;
	int minutos, segundos;

	char nomeFicheiro[30]={"bd_albuns.dat"};// Nome do ficheiro da BD

	// Para permitir acentuação
	setlocale(LC_ALL, "Portuguese");

	// cria a lista de albuns vazia
	ListaAlbuns = criarListaAlbuns();
	ListaAlbuns=carregaDadosBinario(nomeFicheiro);
	if(ListaAlbuns==NULL)
	{
       printf ("Ainda não existe Base de Dados.\n");
	}
	system("pause");

	do
	{
		system("cls");
		printf("**************************************************************************\n");
		printf("*                                                                        *\n");
		printf("*                   LOJA TRÓCÓDISCOTÓCÓMESMO                             *\n");
		printf("*                                                                        *\n");
		printf("**************************************************************************\n");
		printf("* MENU                                                                   *\n");
		printf("*                                                                        *\n");
		printf("* 1 - Criar novo album                                                   *\n");
		printf("* 2 - Remover album                                                      *\n");
        printf("* 3 - Editar album                                                       *\n");
		printf("* 4 - Associar faixas                                                    *\n");
		printf("* 5 - Desassociar faixas                                                 *\n");
		printf("* 6 - Consultar um album                                                 *\n");
		printf("* 7 - Listar Albuns existentes                                           *\n");
		printf("*                                                                        *\n");
		printf("* 0 - Sair                                                               *\n");
		printf("**************************************************************************\n");
		printf("\n\n-> Selecione uma opção: ");
		fflush(stdin);
		scanf("%d", &opcao);

		switch (opcao)
		{
		// Inserir um Album
		case 1: system("cls");
				printf("\n\nINSERSÃO DE ALBUNS\n");
				printf("-----------------------------------------------------------\n");
				do{					
					printf("Código: ");
					fflush(stdin);
					cod_album=0;
					scanf("%d", &cod_album);
					// Verificamos se o album ja existe e se o numero 
					if(!existeAlbum(ListaAlbuns, cod_album) && cod_album !=0 )
					{			
						printf("\nTitulo: ");
						fflush(stdin);
						scanf("%s", album);

						ListaAlbuns = inserirAlbum(ListaAlbuns, album, cod_album);
					}
					else
					{
						if (cod_album==0)
							printf("Inseriu um código invalido!\n");
						else
							printf("Atenção esse album já existe!...\n");
					}
					printf("\n\nDeseja Inserir novo album?(s/n) ");
					fflush(stdin);
					scanf("%c",&continua);
					//ListaAlbuns = inserirAlbum(ListaAlbuns,"Album 2", 100);
					
				}while(toupper(continua)=='S');// Permite maiusculas e minusculas
				gravaDadosBinario(ListaAlbuns, nomeFicheiro);
				system("pause");
				break;
		// Remover um Album
		case 2: system("cls");
				printf("\n\nREMOÇÂO DE ALBUNS\n");
				printf("-----------------------------------------------------------\n");
				do{					
					printf("Código: ");
					fflush(stdin);
					cod_album=0;
					scanf("%d", &cod_album);
					// Verificamos se o album ja existe e se o cod_album !=0 
					if(existeAlbum(ListaAlbuns, cod_album) && cod_album !=0 )
					{			
						ListaAlbuns = removerAlbum(ListaAlbuns, cod_album);
					}
					else
					{
						if (cod_album==0)
							printf("Inseriu um código invalido!\n");
						else
							printf("Atenção esse album não existe!...\n");
					}
					printf("\n\nDeseja remover novo album?(s/n) ");
					fflush(stdin);
					scanf("%c",&continua);
					
				}while(toupper(continua)=='S');// Permite maiusculas e minusculas
				gravaDadosBinario(ListaAlbuns, nomeFicheiro);
				system("pause");
				break;
		// Editar um Album
		case 3: system("cls");
				break;

		// Associar faixas a um album
		case 4: system("cls");
				printf("\n\nASSOCIAÇÂO DE FAIXAS\n");
				printf("-----------------------------------------------------------\n");
				do{
					cod_album=0; posicao=0; minutos=0;segundos=0;
					printf("Cod album: ");
					fflush(stdin);
					scanf("%d", &cod_album);
					// Verificamos se o album existe 
					if(existeAlbum(ListaAlbuns, cod_album) && cod_album != 0)  
					{	
						// Apontador para lista de faixas do album selecionado
						pListaFaixas = getFaixasAlbum(ListaAlbuns, cod_album);

						printf("\nTitulo faixa: ");
						scanf("%s", tituloFaixa);
						printf("\nPosicao: ");
						fflush(stdin);
						scanf("%s", &posicao);
						printf("\nMinutos: ");
						fflush(stdin);
						scanf("%d", &minutos);
						printf("\nSegundos: ");
						fflush(stdin);
						scanf("%d", &segundos);
						if(1==1)// fazer algumas validacoes
						{
							// apontador apara lista de faixas a inserir no album
							pListaFaixas=inserirFaixaOrdenadamente(pListaFaixas, tituloFaixa, posicao, minutos, segundos);
							// obtem apontador par album escolhido
							auxAlbum =  getAlbum(ListaAlbuns,cod_album);
							// Associa faixas ao album
							auxAlbum->faixas = pListaFaixas;
							//incrementa o numero de faixas do album
							auxAlbum->numFaixas = auxAlbum->numFaixas + 1;
						}
						else
						{
							printf("Dados incorretos..\n");
						}
					}
					else
					{
						if (cod_album==0)
							printf("Inseriu um código invalido!\n");
						else
							printf("Atenção esse album não existe!...\n");
					}
					printf("\n\nDeseja Inserir nova faixa?(s/n) ");
					fflush(stdin);
					scanf("%c",&continua);


					// 0001 é um código de ordenaçao das faixas na lista???
					//pListaFaixas=inserirFaixaOrdenadamente(pListaFaixas,0001, "Faixa 5", 5,2,23);

				}while(toupper(continua)=='S');// Permite maiusculas e minusculas
				gravaDadosBinario(ListaAlbuns, nomeFicheiro);
				break;

		// DesassociarFaixas (ListaAlbuns);				
		case 5:
				system("cls");
				printf("\n\nDESASSOCIAÇÂO DE FAIXAS\n");
				printf("-----------------------------------------------------------\n");
				do{
					cod_album=0; codigoFaixa=0; posicao=0; minutos=0;segundos=0;
					printf("Cod album: ");
					fflush(stdin);
					scanf("%d", &cod_album);
					// Verificamos se o album existe 
					if(existeAlbum(ListaAlbuns, cod_album) && cod_album != 0)  
					{	
						// Apontador para lista de faixas do album selecionado
						pListaFaixas = getFaixasAlbum(ListaAlbuns, cod_album);

						printf("\nCódigo faixa: ");
						scanf("%s", codigoFaixa);
						printf("\nPosicao: ");
						fflush(stdin);
						scanf("%s", &posicao);
						printf("\nMinutos: ");

						if(1==1)// fazer algumas validacoes
						{
							// obtem apontador par album escolhido
							auxAlbum =  getAlbum(ListaAlbuns,cod_album);
							// Associa faixas ao album
							auxAlbum->faixas = pListaFaixas;
							//incrementa o numero de faixas do album
							auxAlbum->numFaixas = auxAlbum->numFaixas + 1;
						}
						else
						{
							printf("Dados incorretos..\n");
						}
					}
					else
					{
						if (cod_album==0)
							printf("Inseriu um código invalido!\n");
						else
							printf("Atenção esse album não existe!...\n");
					}
					printf("\n\nDeseja Inserir nova faixa?(s/n) ");
					fflush(stdin);
					scanf("%c",&continua);

				}while(toupper(continua)=='S');// Permite maiusculas e minusculas
				gravaDadosBinario(ListaAlbuns, nomeFicheiro);
				break;

		// Consulta um  Album
		case 6:
				cod_album=0; 
				printf("Qual o album a imprimir as faixas: ");
				fflush(stdin);
				scanf("%d", &cod_album);
				// Verificamos se o album existe 
				if(existeAlbum(ListaAlbuns, cod_album) && cod_album != 0)  
				{	
					imprimeFaixasAlbum(ListaAlbuns,cod_album);
				}
				else
				{
					if (cod_album==0)
						printf("Inseriu um código invalido!\n");
					else
						printf("Atenção esse album não existe!...\n");
				}

				system("pause");
				break;

		// Listar albuns			
		case 7:			
				imprimeListaAlbuns(ListaAlbuns);
				system("Pause");
				break;


		default:
			break;
		}
	}while (opcao!=0);



	system("cls");
	printf("**************************************************************************\n");
	printf("*                                                                        *\n");
	printf("*                   LOJA TRoCoDISCoToCoMESMo                             *\n");
	printf("*                                                                        *\n");
	printf("**************************************************************************\n");
	printf("* Deseja guardar as alterações? (s/n)                                    *\n");
	printf("*                                                                        *\n");
	printf("**************************************************************************\n");
	printf("\n\n-> Opção: ");
	fflush(stdin);
	scanf("%d", &guardar);

	
	if(toupper(guardar)=='S');// Permite maiusculas e minusculas
	{
		gravaDadosBinario(ListaAlbuns, nomeFicheiro);

		//criar ficheiro 
		//escrita = fopen("bd_albuns", "a"); // em modo append para acrescentar no fim do ficheiro
		
		//if(escrita == NULL){
		//	printf("Não foi possível criar a Base de Dados!");
		//	return 1;
		//}else{
			/* vamos escrever os dados da lista ligada no ficheiro 
		
			// fechar o ficheiro 
			fclose(escrita);
			return 0;
		}
	}
	*/
		
}

}