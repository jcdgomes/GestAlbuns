/*
****************************************************************
*  Nome    : Gestao de repositorio musical                     *
*  Autores : a5571, a7829, a7813                               *
*  Data    : 14/06/2013                                        *
*  Versão  : 1.0                                               *
****************************************************************
*/


#define SHOW_ERRORS  // Para debugging


// Definição da estrutura de faixas para o album
typedef struct faixa {
	char tituloFaixa[30];
	int posicao;
	int tempoFaixaMin;
	int tempoFaixaSeg;
	struct faixa *seguinte;
} *listaFaixa;

// Definição da estrutura do Album
typedef struct album {
	int codigo;
	char titulo[30];
	int anoEdicao;
	char autor[30];
	char genero[30];
	int numFaixas;
	int tempoTotal;
	listaFaixa faixas;
	struct album *seguinte;
} *listaAlbum;

/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+                           Assinatura das funcoes                          +
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

// Inicia lista de Albuns
listaAlbum criarListaAlbuns();

// Inicia lista de faixas
listaFaixa criarListaFaixas();

// Inserir um novo album na lista de albuns
listaAlbum inserirAlbum(listaAlbum lista, char titulo[30], int codigo);

// Remover Album existente da lista de albuns
listaAlbum removerAlbum(listaAlbum lista, int cod);

// Imprime a lista dos albuns existentes
void imprimeListaAlbuns(listaAlbum lst);

// Imprime todas as faixas de um album
void imprimeFaixasAlbum(listaAlbum lst_album, int cod_album);

// Inserir faixas num album
listaFaixa inserirFaixaOrdenadamente(listaFaixa lf, char titulo_faixa[30], int posicao, int minutos, int segundos);

// Função para verificar se uma determinada faixa existe na lista de faixas
int existeFaixa(listaFaixa l, char tituloFaixa[30]);

// Retorna apontador para album 'codigo' 
struct album *getAlbum(listaAlbum lst, int codigo);

// Retorna apontador para lista de faixas do album 'codigo' 
listaFaixa getFaixasAlbum(listaAlbum lst, int codigo);

// Apagar todas faixas de um album 
listaFaixa apagaListaFaixas(listaFaixa listaFaixas);

// Apagar uma faixa de um album 
listaFaixa apagaFaixa(listaFaixa listaFaixas, int pos);

// Função para verificar se um album existe
int existeAlbum(listaAlbum lst, int codigo);

// Gravacao em ficheiro binario
int gravaDadosBinario(listaAlbum lst, char *ficheiro);

// Leitura de dados num ficheiro binario
listaAlbum carregaDadosBinario(char *ficheiro);
