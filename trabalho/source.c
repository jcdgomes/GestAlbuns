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
#include <ctype.h>//touper
#include "header.h"
#include <locale.h>


// ********** Inicio funções **********

//Inicia lista vazia
listaAlbum criarListaAlbuns()
{
	return NULL;
}

//Inicia lista vazia
listaFaixa criarListaFaixas()
{
	return NULL;
}


/*
****************************************************************************
* Nome funcao  : inserirAlbum                                              *
* Descrição    : Inserir um novo album na lista                            *
* Parametros de entrada  (listaAlbuns, titulo Album, codigo Album)         *
* Parametros de saída    (listaAlbuns)                                     *
****************************************************************************
*/
listaAlbum inserirAlbum(listaAlbum lista, char titulo[30], int codigo)
{
	struct album *auxPtr;
	auxPtr = (struct album*)malloc(sizeof(struct album));
	if (auxPtr==NULL)return lista;			// Se nao alocar memoria retorma a lista intacta

	strcpy(auxPtr->titulo,titulo);
	auxPtr->codigo=codigo;
	auxPtr->numFaixas=0;
	auxPtr->anoEdicao=NULL;
	strcpy(auxPtr->autor,"");
	auxPtr->faixas = criarListaFaixas();	//Cria lista de faixas vazia
	auxPtr->seguinte = lista;
	return auxPtr;
}

/*
****************************************************************************
* Nome funcao  : removerAlbum                                               *
* Descrição    : remover um album da lista remove tambem todas as faixas   *
* Parametros de entrada  (listaAlbuns, codigo Album)                       *
* Parametros de saída    (listaAlbuns)                                     *
****************************************************************************
*/
listaAlbum removerAlbum(listaAlbum lista, int codigo)
{
	listaAlbum cabecaListaAlbum=lista;
	listaAlbum anteriorListaAlbum;
	listaAlbum auxListaAlbum=NULL;

	anteriorListaAlbum=auxListaAlbum=cabecaListaAlbum;

	// Vamos procurar o album
	while(auxListaAlbum!= NULL && auxListaAlbum->codigo!=codigo)
	{
		anteriorListaAlbum=auxListaAlbum;
		auxListaAlbum=auxListaAlbum->seguinte;
	}
	// Nao chegou ao fim por isso é para remover o que encontrou
	if(auxListaAlbum!=NULL)
	{
		// existem faixas, vamos remover
		if (auxListaAlbum->faixas!= NULL)
		{
			
			auxListaAlbum->faixas=apagaListaFaixas(auxListaAlbum->faixas);		
			/*
			// Percorrer lista de faixas
			listaFaixa auxListaFaixa=auxListaAlbum->faixas;
			while(auxListaFaixa!=NULL)
			{
				auxListaFaixa=auxListaAlbum->faixas;
				auxListaAlbum->faixas=auxListaFaixa->seguinte;
				// libertar memoria
				free(auxListaFaixa);
			}
			*/
		}
		// remove album se nao existirem faixas por remover
		if(auxListaAlbum->faixas==NULL)
		{
			anteriorListaAlbum->seguinte=auxListaAlbum->seguinte;
			// liberta memoria do album
			free(auxListaAlbum);
		}
	}
	return cabecaListaAlbum;
}

/*
****************************************************************************
* Nome funcao  : existeAlbum                                               *
* Descrição    : Função para verificar se um album existe                  *
* Parametros de entrada  (listaAlbuns, codigo Album)                       *
* Parametros de saída    (listaAlbuns)                                     *
****************************************************************************
*/
int existeAlbum(listaAlbum lst, int codigo)
{
	listaAlbum auxLista;
	auxLista = lst;
	while(auxLista!=NULL)
	{
		if(auxLista->codigo==codigo)
			return 1;					// indica que o codigo ja existe
		auxLista=auxLista->seguinte;
	}
	return 0;

}

/*
****************************************************************************
* Nome funcao  : getFaixasAlbum                                            *
* Descrição    : obter apontador para lista de faixas de um album          *
* Parametros de entrada  (listaAlbum, codigo Album)                        *
* Parametros de saída    (listaFaixa)                                      *
****************************************************************************
*/
// Retorna apontador para lista de faixas do album 'codigo' 
listaFaixa getFaixasAlbum(listaAlbum lst, int codigo)
{
	listaAlbum auxLista;
	auxLista=lst;
	if (lst==NULL)return NULL;	// Se a lista estiver vazia retorna NULL

	while((auxLista->codigo!=codigo)) // ou (strcmp(auxLista->titulo,titulo)!=0)
	{		
		auxLista=auxLista->seguinte;
		if(auxLista==NULL)return NULL;
	}
	return auxLista->faixas;
}

/*
****************************************************************************
* Nome funcao  : apagaListaFaixas                                          *
* Descrição    : remover faixas de um album  album da lista                *
* Parametros de entrada  (listaFaixa)                       *
* Parametros de saída    (listaFaixa)                                     *
****************************************************************************
*/
// Apagar todas faixas de um album 
listaFaixa apagaListaFaixas(listaFaixa lst)
{
	listaFaixa auxLista;
	auxLista=lst;
	if (lst==NULL)return NULL;	// Se a lista estiver vazia retorna NULL

	while((lst!=NULL))
	{		
		auxLista=lst;
		lst=lst->seguinte;
		free(auxLista);
	}
	return lst;
}

/*
****************************************************************************
* Nome funcao  : apagaFaixaAlbum                                          *
* Descrição    : remover faixa de um album  album da lista                *
* Parametros de entrada  (listaAlbuns, codigo Album)                       *
* Parametros de saída    (listaFaixa)                                     *
****************************************************************************
*/
// Apagar uma faixa de um album 
listaFaixa apagaFaixa(listaFaixa lst, int pos)
{
	listaFaixa auxLista;
	auxLista=lst;
	if (lst==NULL)return NULL;	// Se a lista estiver vazia retorna NULL

	while(lst!=NULL && pos!=lst->posicao)
	{		
		//auxLista=lst;
		//lst=lst->seguinte;
		//free(auxLista);
	}
	return lst;
}
/*
****************************************************************************
* Nome funcao  : *getAlbum                                                 *
* Descrição    : Retorna apontador para album 'codigo'                     *
* Parametros de entrada  (listaAlbuns, codigo)                             *
* Parametros de saída    (struct album)                                    *
****************************************************************************
*/
// Retorna apontador para album 'codigo' 
struct album *getAlbum(listaAlbum lst, int codigo)
{
	listaAlbum auxLista;
	auxLista=lst;
	if (lst==NULL)return NULL;	// Se a lista estiver vazia retorna NULL

	while((auxLista->codigo!=codigo)) // ou (strcmp(auxLista->titulo,titulo)!=0)
	{		
		auxLista=auxLista->seguinte;
		if(auxLista==NULL)return NULL;
	}
	return auxLista;
}

/*
****************************************************************************
* Nome funcao  : existeFaixa                                               *
* Descrição    : Verifica se a faixa 'tituloFaixa' existe                  *
* Parametros de entrada  (listaFaixa, char listaFaixa[30])                 *
* Parametros de saída    (0, 1)                                            *
****************************************************************************
*/
// Função para verificar se uma determinada faixa existe na lista de faixas
int existeFaixa(listaFaixa lst, char tituloFaixa[30])
{
	listaFaixa auxFaixa;
	auxFaixa = lst;
	while(auxFaixa!=NULL)
	{
		if(strcmp(auxFaixa->tituloFaixa,strdup(tituloFaixa))==0)
			return 1;// indica que o codigo ja existe
			auxFaixa=auxFaixa->seguinte;
	}
	return 0;

}

/*
****************************************************************************
* Nome funcao  :                                                           *
* Descrição    :                                                           *
* Parametros de entrada  (listaAlbuns, codigo Album)                       *
* Parametros de saída    (listaAlbuns)                                     *
****************************************************************************
*/
// Inserir faixa completa
// NAO TERMNADA
// Esta confuso, necessario alterar e inserir por partes
/*
int inserirFaixa(listaAlbum lst, int cod, char titulo_faixa[30], int posicao, int minutos, int segundos)
{
	struct faixa *auxfaixa;
	auxfaixa = (faixa*)malloc(sizeof(struct faixa));
	if (auxfaixa==NULL)
	{
		#ifdef SHOW_ERRORS
			printf("Nao foi possivel alocar memoria");
		#endif
			return 0;
	}
	// prencher lista temporaria com dados
	strcpy(auxfaixa->tituloFaixa,titulo_faixa);
	auxfaixa->numFaixa=posicao;
	auxfaixa->tempoFaixaMin=minutos;
	auxfaixa->tempoFaixaSeg=segundos;
	//auxfaixa->seguinte=NULL;

	listaFaixa tmpListaFaixa;
	tmpListaFaixa = procuraAlbum(lst, cod);
	// se for null ainda nao tem faixas
	if (tmpListaFaixa==NULL)
	{
		tmpListaFaixa=auxfaixa;
		tmpListaFaixa->seguinte=NULL;
		return 1;// Foi inserida
	}
	else
	{
		if(existeFaixa(tmpListaFaixa,titulo_faixa)==1)
		{
			printf("\nEssa faixa ja existe!\n");
			return 0;
		}
		// tem de ser melhorada
		while (tmpListaFaixa->numFaixa < posicao)
		{
			tmpListaFaixa=tmpListaFaixa->seguinte;

			if (tmpListaFaixa==NULL)
			{
				tmpListaFaixa=auxfaixa;
				tmpListaFaixa->seguinte=NULL;
				return 1;// foi inserida
			}
		}
	}
}
*/

/*
****************************************************************************
* Nome funcao  : inserirFaixaOrdenadamente                                 *
* Descrição    : inserirFaixaOrdenadamente                                 *
* Parametros de entrada  (........)                                        *
* Parametros de saída    (listaFaixa)                                      *
****************************************************************************
*/
// Inserir faixas num album
listaFaixa inserirFaixaOrdenadamente(listaFaixa lf, char titulo_faixa[30], int posicao, int minutos, int segundos)
{
	struct faixa *faixaAtual, *faixaAnterior, *novaFaixa;
	faixaAtual=lf;
	faixaAnterior=NULL;
	novaFaixa = (struct faixa *)malloc(sizeof(struct faixa));
	if (novaFaixa==NULL)
	{
		#ifdef SHOW_ERRORS
			printf("Nao foi possivel alocar memoria");
		#endif
		return lf;
	}
	// prencher lista temporaria com dados
	strcpy(novaFaixa->tituloFaixa,titulo_faixa);
	novaFaixa->posicao=posicao;
	novaFaixa->tempoFaixaMin=minutos;
	novaFaixa->tempoFaixaSeg=segundos;
	
	while(faixaAtual != NULL && posicao > faixaAtual->posicao)
	{
		faixaAnterior = faixaAtual;
		faixaAtual = faixaAtual->seguinte;
	}
	// Inserir na primeira posicao
	if(faixaAtual==lf)
	{
		novaFaixa->seguinte=faixaAtual;
		lf=novaFaixa;	
	}
	else
	{
		novaFaixa->seguinte = faixaAnterior->seguinte;
		faixaAnterior->seguinte= novaFaixa;
	}
	return lf;
}
	
/*
****************************************************************************
* Nome funcao  : imprimeFaixasAlbum                                        *
* Descrição    : imprimeFaixasAlbum                                        *
* Parametros de entrada  (listaAlbuns, codigo Album)                       *
* Parametros de saída    (void)                                            *
****************************************************************************
*/
void imprimeFaixasAlbum(listaAlbum lst_album, int cod_album)
{
	listaAlbum aux=lst_album;
	if(lst_album==NULL)
	{
		printf("Nao existem albuns !\n");
	}
	else
	{
		if(existeAlbum(lst_album, cod_album))
		{
			listaFaixa auxFaixas = getFaixasAlbum(lst_album,cod_album);
			printf("Lista de faixas do album: %d\n", cod_album);
			if(auxFaixas!=NULL)
			{
				while (auxFaixas!=NULL)
				{
					printf("\Posicao(%d) - Titulo: %s\n",auxFaixas->posicao, auxFaixas->tituloFaixa);
					auxFaixas=auxFaixas->seguinte;
				}
			}
			else
			{
				printf("\tEste album não tem  faixas associadas");
			}
		}
		else
		{
			printf("Esse album não existe!\n");
		}
	}
}
/*
****************************************************************************
* Nome funcao  : imprimeListaAlbuns                                               *
* Descrição    : remover um album da lista                                 *
* Parametros de entrada  (listaAlbuns, codigo Album)                       *
* Parametros de saída    (listaAlbuns)                                     *
****************************************************************************
*/
// Imprime a lista dos albuns existentes
void imprimeListaAlbuns(listaAlbum lst)
{
	listaAlbum aux=lst;
	int cnt=0;
	if(aux==NULL)
	{
		printf("Não existem albuns !\n");
	}
	else
	{
		printf("Listagem dos albuns existentes\n");
		//printf("|    Código     |                  Titulo                  |\n");
		while (aux!=NULL)
		{
			printf("Codigo: %.4d ----- Titulo:  %s\n", aux->codigo, aux->titulo);
			aux=aux->seguinte;
			cnt++;
		}
		printf("\nExistem %d albuns.\n", cnt);
	}
}

/*
****************************************************************************
* Nome funcao  : gravaAlbumBinario                                         *
* Descrição    : Grava a lista de listas em ficheiro                       *
* Parametros de entrada  (nomeFicheiro)                                    *
* Parametros de saída    (0-nok, 1-ok)                                     *
****************************************************************************
*/
// Gravacao de dados num ficheiro binario
int gravaDadosBinario(listaAlbum lst, char *nomeFicheiro) 
{
	FILE *ptr;
	listaAlbum aux;
	listaFaixa auxFaixa;
	aux=lst;
	ptr=fopen(nomeFicheiro,"wb");
	if (!ptr)
	{
		printf("Impossivel abrir ficheiro!\n");
		return 0;
	}
	while (aux!=NULL)
	{
		// Gravar o Album
		fwrite(aux, sizeof(struct album), 1 , ptr);

		// se tiver faixas gravamos as faixas
		if(aux->faixas!=NULL)
		{
			auxFaixa=aux->faixas;
			while (auxFaixa!=NULL)
			{
				fwrite(auxFaixa, sizeof(struct faixa), 1 , ptr);
				auxFaixa=auxFaixa->seguinte;
			}
			
		}
		aux=aux->seguinte;

	}		

	fclose(ptr);
	printf("Os dados foram gravados!\n");

	return 1;
}
/*
****************************************************************************
* Nome funcao  : carregaAlbumBinario                                       *
* Descrição    : Carregar os dados do ficheiro para a lista de albuns      *
* Parametros de entrada  (nomeFicheiro)                                    *
* Parametros de saída    (listaAlbum)                                     *
****************************************************************************
*/
// Leitura de dados num ficheiro binario
listaAlbum carregaDadosBinario(char *nomeFicheiro)
{

	//   fseek(ficheiro,(reg+1)*sizeof(struct aluno),SEEK_SET);
	//int fseek(FILE * stream, long int offset, int whence);
	FILE *ptr;
	struct album *auxAlbumPtr;
	listaAlbum listaAlbumCompleta=NULL;
	int i,j, cntAlbuns=0, cntFaixas=0;
	//return NULL;


	ptr=fopen(nomeFicheiro,"rb");
	if (!ptr)
	{
		printf("Impossivel abrir ficheiro!");
		return NULL;
	}
	fseek(ptr,0,SEEK_SET); // Não neccesita no inicio aponta para inicio do ficheiro
	//fseek(ptr,sizeof(struct album)*cnt,SEEK_SET);
	//fseek(ptr, sizeof(struct album), SEEK_END);
	// alocar novo bloco de memoria
	auxAlbumPtr = (struct album*)malloc(sizeof(struct album));
	if (auxAlbumPtr==NULL)
	{
		printf("Impossivel alocar memoria\nO programa vai terminar....\n");
		return NULL;			// Se nao alocar memoria retorma a lista vazia
	}
	while ( fread(auxAlbumPtr, sizeof (struct album), 1, ptr) == 1 ) /* ler tudo */
	{
		//printf("ptr: %d\n",*ptr);
		//printf("dados, %d      %s  ",auxAlbumPtr->codigo, auxAlbumPtr->titulo);

		if(listaAlbumCompleta==NULL)
		{
			listaAlbumCompleta = auxAlbumPtr;
			listaAlbumCompleta->seguinte=NULL;
		}
		else
		{
			auxAlbumPtr->seguinte=listaAlbumCompleta;
			listaAlbumCompleta = auxAlbumPtr;
		}
	   // Se existirem faixas, carregam-se
		if(listaAlbumCompleta->numFaixas>0)
		{
			struct faixa *auxFaixaPtr;
			listaFaixa tmpListaFaixas=NULL;
			// alocar novo bloco de memoria para faixas
			auxFaixaPtr = (struct faixa*)malloc(sizeof(struct faixa));
			if (auxFaixaPtr==NULL)
			{
				printf("Impossivel alocar memoria\nO programa vai terminar....\n");
				return NULL;			// Se nao alocar memoria retorma a lista vazia
			}
			for(j=1;j<=listaAlbumCompleta->numFaixas;j++)
			{
				if( fread(auxFaixaPtr, sizeof (struct faixa), 1, ptr) == 1 )
				{
					if(tmpListaFaixas==NULL)
					{
						// Inserir no inicio
						tmpListaFaixas = auxFaixaPtr;
						tmpListaFaixas->seguinte=NULL;
					}
					else
					{
						// Inserir 
						auxFaixaPtr->seguinte=tmpListaFaixas;
						tmpListaFaixas = auxFaixaPtr;
						
						//tmpListaFaixas->seguinte=auxFaixaPtr;
						//auxFaixaPtr->seguinte=NULL;

					}
					auxFaixaPtr = (struct faixa*)malloc(sizeof(struct faixa));
					if (auxFaixaPtr==NULL)
					{
						printf("Impossivel alocar memoria\nO programa vai terminar....\n");
						return NULL;			// Se nao alocar memoria retorma a lista vazia
					}
					cntFaixas++;
				}
			}
			listaAlbumCompleta->faixas=tmpListaFaixas;
		}
		// alocar novo bloco de memoria
		auxAlbumPtr = (struct album*)malloc(sizeof(struct album));
		if (auxAlbumPtr==NULL)
		{
			printf("Impossivel alocar memoria\nO programa vai terminar....\n");
			return NULL;			// Se nao alocar memoria retorma a lista vazia
		}

		cntAlbuns++;
	}
	printf("Foram carregados %d albuns com %d faixas.\n", cntAlbuns, cntFaixas);
	fclose(ptr);
	return listaAlbumCompleta;
}
