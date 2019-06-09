#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define PI 3.14159265358979323846

typedef struct list_char {
	char info;
	struct list_char *prox;
} TListChar;

typedef struct list_int {
	int info;
	struct list_int *prox;
} TListInt;

typedef struct list_float {
	float info;
	struct list_float *prox;
} TListFloat;

typedef struct list_arq {
	int cod;
	int cod_pai;
	int tp_fig;
	char nome_fig[4];
	void *no_info;
	float area;
	struct list_arq *prox;
} TListArq;

typedef struct triangulo {
	float base;
	float altura;
} TTRI;

typedef struct retangulo {
	float largura;
	float comprimento;
} TRET;

typedef struct trapezio {
	float base1;
	float base2;
	float altura;
} TTRA;

typedef struct circulo {
	float raio;
} TCIR;

typedef struct quadrado {
	float lado;
} TQUA;

typedef struct info {
	int tipo;
	char nome[4];
	void *info;
	float area;
} TNO;

typedef struct ag {
	int cod;
	TNO *no;
	struct ag *filho;
	struct ag *irmao;
} TAG;

typedef struct abb {
	int cod;
	
} TABB;

typedef struct ab {
	int cod;
	
} TAB;

enum figura {TRI=1, RET, TRA, CIR, QUA};

/*
(a) buscar figuras geometricas, por meio de um codigo unico
(b) imprimir informacoes relevantes, tanto da arvore, quanto das figuras, incluindo-se sua area
(c) inserir novas figuras
(d) retirar figuras, passando seus descendentes para outro pai
(e) destruir a arvore
(f) alterar as dimensoes de figuras
(g) transformar em arvore binaria de busca balanceada, baseando-se no codigo unico
(h) converter em arvore B, baseando-se no codigo unico
*/

// FUNCOES PARA CRIACAO DA ARVORE GENERICA A PARTIR DE UM ARQUIVO DE ENTRADA
TAG * criar_ag (char *nome_arq);
TListChar  * inserir_final_list_char  (TListChar  *lista, char  info);
TListInt   * inserir_final_list_int   (TListInt   *lista, int   info);
TListFloat * inserir_final_list_float (TListFloat *lista, float info);
TListArq   * inserir_orden_list_arq   (TListArq   *r_arq, int cod, int c_pai, int t_fig, char *n_fig, void *no_info, float area);
void liberar_list_char  (TListChar  *lista);
void liberar_list_int   (TListInt   *lista);
void liberar_list_float (TListFloat *lista);
void liberar_list_arq   (TListArq   *lista);
TListInt   * buscar_list_int (TListInt *lista, int info);
void setar_pais_filhos_ag (TAG **adj, int index);

// FUNCAO PARA EXIBICAO DO MENU
int iniciar_menu (TAG *arv_g);

// FUNCOES DE BUSCA
TAG * buscar_figura (int cod, TAG *ag);
TAG * buscar_figura_pai (int cod, TAG *ag, TAG *ag_pai);

// FUNCOES DE IMPRESSAO
void imprimir_info_figura (TAG *ag, TAG *ag_pai);
void imprimir_info_subarv_simples (TAG *ag);
void imprimir_info_subarv_verbose (TAG *ag);
void imprimir_info_subarv (TAG *ag, int *num_nodes, float *area_tot, int **num_fig, float **area_fig, int **cod_maior_area_fig, char ***nome_maior_area_fig, float **maior_area_fig, int **cod_menor_area_fig, char ***nome_menor_area_fig, float **menor_area_fig);

// FUNCOES DE INSERCAO, RETIRADA E DESTRUICAO
TAG * inserir_figura (TAG *ag, int cod, int cod_pai, int tp_f, float *med);
void retirar_figura  (TAG *ag, int cod_r, int cod_h);
void destruir_arvore (TAG *ag);

// FUNCOES DE CONVERSAO E IMPRESSAO DA ARVORE DE BUSCA BINARIA (ABB) E ARVORES B (AB)
void destruir_abb (TABB *abb);
void destruir_aB  (TAB *aB);
TABB * converter_abb (TAG *ag);
TAB  * converter_aB  (TAG *ag);
void imprimir_abb (TABB *abb);
void imprimir_aB  (TAB *aB);

int main (int argc, char* argv[]) {

	if (argv[1]) {
		TAG *ag = criar_ag(argv[1]); 
		if (ag)
			while (iniciar_menu(ag));
		else
			printf ("Não foi possível criar a árvore genérica! Verifique o log de erros.\n");
	} else {
		printf("Cadê o arquivo de entrada?\n");
		printf("Digite no prompt: \"trabalho 'nome_do_arquivo_de_entrada'\" e depois tecle ENTER.\n");
 	    exit(1);
	}

	return 75;
}

TAG * criar_ag (char *nome_arq) {

	int i;
	int num_reg_arq = 0;
	TListArq *reg_arq = NULL;
	char *linha = (char *) malloc(200);
	int cod_log_erro = 0, count_erro = 0;
	char **log_erro;
	FILE *fp = fopen (nome_arq, "r");

	log_erro = (char **) malloc (sizeof(char *)*1000);
	for (i=0; i < 1000; i++)
		log_erro[i] = (char *) malloc (sizeof(char)*300);
	
	while (fgets(linha,200,fp)) {

		enum figura tp_fig;
		char fig[20]; 
		TListChar  *substring = NULL;
		TListFloat *medidas   = NULL;
		int dim_med = 0;
		int codigo, cod_pai;
		int count_barra = 0, count_dec = 0;
		int count_space = 0, count_int = 0;
		int flag_sep = 0;
		char *aux_lin = linha;

		// Em ASCII: TAB 9, LF ('\n') 10, CR ('\r') 13, Space (' ') 32.
		// Tentativa de pegar ou ou outro erro de formatacao do arquivo de entrada.
		if ((aux_lin[0] == 9) || (aux_lin[0] == 10) || (aux_lin[0] == 13) || (aux_lin[0] == 32))
			break;

		// Como atraves de fputs(), o EOF eh na mesma linha do ultimo registro,
		// colocar '\n' para ficar igual aos demais registros.
		if (feof(fp)) {
			for (i=0; aux_lin[i] != '\0'; i++);
			aux_lin[i] = '\n';
			aux_lin[i+1] = '\0';
		}

		while (1) {

			if ((*aux_lin != '/') && (*aux_lin != ' ') && (*aux_lin != '\n')) {
				substring = inserir_final_list_char (substring, *aux_lin);
				if ((*aux_lin == '.') || (*aux_lin == ','))
					flag_sep = 1;
				else 
					if ((*aux_lin >= 48) && (*aux_lin <= 57)) // Apenas numeros ('0' a '9')
						if (flag_sep) count_dec++;
						else          count_int++;

			} else if (*aux_lin == '/') { // CODIGO e CODIGO_PAI
				int aux_cod = 0;
				TListChar *aux_substr = substring;
				while (aux_substr) {
					if ((aux_substr->info >= 48) && (aux_substr->info <= 57)) { // Apenas numeros ('0' a '9')
						int pot10 = 1, info = 0;
						for (i=1; i < count_int; i++) pot10 *= 10;
						info = aux_substr->info - '0';
						aux_cod += info*pot10;
						count_int--;
					} else {
						cod_log_erro = 10; // Caracteres nao permitidos
						break;
					}
					aux_substr = aux_substr->prox;
				}
				
				liberar_list_char (substring); substring = NULL;
				flag_sep = 0;
								
				if (cod_log_erro == 10) {
					sprintf(log_erro[count_erro], "Caracteres NÃO permitidos em %s", linha);
					count_erro++;
					break; // Segue para a proxima linha do arquivo
				} else {
					count_barra++;
					if (count_barra == 1) codigo  = aux_cod;
					if (count_barra == 2) cod_pai = aux_cod;
					count_int = 0;
				}
				
			} else if (*aux_lin == ' ') { // NOME DA FIGURA e MEDIDAS DA FIGURA
				count_space++;

				if (count_space == 1) { // NOME DA FIGURA

					TListChar *aux_substr = substring;
					for (i=0; aux_substr; aux_substr = aux_substr->prox) fig[i++] = aux_substr->info;
					fig[i] = '\0';
					if (i == 3) {
						     if ((fig[0] == 'R') && (fig[1] == 'E') && (fig[2] == 'T')) {tp_fig = RET; dim_med = 2;}
						else if ((fig[0] == 'Q') && (fig[1] == 'U') && (fig[2] == 'A')) {tp_fig = QUA; dim_med = 1;}
						else if ((fig[0] == 'C') && (fig[1] == 'I') && (fig[2] == 'R')) {tp_fig = CIR; dim_med = 1;}
						else if ((fig[0] == 'T') && (fig[1] == 'R') && (fig[2] == 'I')) {tp_fig = TRI; dim_med = 2;}
						else if ((fig[0] == 'T') && (fig[1] == 'R') && (fig[2] == 'A')) {tp_fig = TRA; dim_med = 3;}
						else cod_log_erro = 6;
					} else {
						cod_log_erro = 6;
					}
					liberar_list_char (substring); substring = NULL;
					count_int = 0;
					if (cod_log_erro == 6) {
						sprintf(log_erro[count_erro], "Cód. %d/Cód. Pai %d: Tipo de figura não permitido ('%s').\n", codigo, cod_pai, fig);
						count_erro++;
						break; // Segue para a proxima linha do arquivo
					}
					
				} else { // MEDIDAS DA FIGURA
					int aux_count = count_dec;
					float med = 0.0;
					TListChar *aux_substr = substring;
					while (aux_substr) {
						if ((aux_substr->info == '.') || (aux_substr->info == ',')) {
							flag_sep = 1;								
						} else if ((aux_substr->info >= 48) && (aux_substr->info <= 57)) { // Apenas numeros ('0' a '9')
							float pot10 = 1.0;
							int info = 0;
							if (flag_sep) {
								for (i=1; i < aux_count - count_dec + 1; i++) pot10 /= 10;
								count_dec--;
							} else {
								for (i=1; i < count_int; i++) pot10 *= 10;
								count_int--;
							}
							info = aux_substr->info - '0';
							med += info*pot10;
						} else {
							cod_log_erro = 10;
							break;
						}
						aux_substr = aux_substr->prox;
					}
					
					liberar_list_char (substring); substring = NULL;
					flag_sep = 0; count_dec = 0; count_int = 0;
									
					if (cod_log_erro == 10) {
						sprintf(log_erro[count_erro], "Caracteres NÃO permitidos em %s", linha);
						count_erro++;
						break; // Segue para a proxima linha do arquivo
					} else {
						medidas = inserir_final_list_float (medidas, med);
					}					
				}

			} else if (*aux_lin == '\n') { // MEDIDAS DA FIGURA e CALCULO DA AREA
				int aux_count = count_dec;
				float med = 0.0;
				TListChar *aux_substr = substring;
				while (aux_substr) {
					if ((aux_substr->info == '.') || (aux_substr->info == ',')) {
						flag_sep = 1;
					} else if ((aux_substr->info >= 48) && (aux_substr->info <= 57)) { // Apenas numeros ('0' a '9')
						float pot10 = 1.0;
						int info = 0;
						if (flag_sep) {
							for (i=1; i < aux_count - count_dec + 1; i++) pot10 /= 10;
							count_dec--;
						} else {
							for (i=1; i < count_int; i++) pot10 *= 10;
							count_int--;
						}
						info = aux_substr->info - '0';
						med += info*pot10;
					} else {
						cod_log_erro = 10;
						break;
					}
					aux_substr = aux_substr->prox;
				}
				
				if (cod_log_erro == 10) {
					sprintf(log_erro[count_erro], "Caracteres NÃO permitidos em %s", linha);
					count_erro++;
					liberar_list_char  (substring); substring = NULL;
					liberar_list_float (medidas);   medidas   = NULL;
					break; // Segue para a proxima linha do arquivo
				} else {
					medidas = inserir_final_list_float (medidas, med);
				}
								
				TListFloat *aux_med = NULL;
				float area = 0.0;
				void *no_info_v = NULL;
													
				aux_med = medidas;
				for (i=0; aux_med; aux_med = aux_med->prox) i++;
				if (i != dim_med) {
					
					cod_log_erro = 9;
					sprintf(log_erro[count_erro], "Cód. %d/Cód. Pai %d/Tipo %s: Quantidade de medidas incompatível com o tipo da figura (%d quando deveria ser %d).\n", codigo, cod_pai, fig, i, dim_med);
					count_erro++;
				
				} else {
					
					float measure[dim_med];
					aux_med = medidas;
					for (i=0; (i < dim_med) && aux_med; i++) {
						measure[i] = aux_med->info;
						aux_med = aux_med->prox;
					}
					
					if (tp_fig == RET) {
						TRET *no_info = (TRET *) malloc(sizeof(TRET));
						no_info->largura     = measure[0];
						no_info->comprimento = measure[1]; 
						area = no_info->largura * no_info->comprimento;
						no_info_v = no_info;
					} else if (tp_fig == QUA) {
						TQUA *no_info = (TQUA *) malloc(sizeof(TQUA));
						no_info->lado = measure[0];
						area = no_info->lado * no_info->lado;
						no_info_v = no_info;
					} else if (tp_fig == CIR) {
						TCIR *no_info = (TCIR *) malloc(sizeof(TCIR));
						no_info->raio = measure[0];
						area = no_info->raio * no_info->raio *PI/2;
						no_info_v = no_info;
					} else if (tp_fig == TRI) {
						TTRI *no_info = (TTRI *) malloc(sizeof(TTRI));
						no_info->base   = measure[0];
						no_info->altura = measure[1];
						area = no_info->base * no_info->altura/2;
						no_info_v = no_info;
					} else if (tp_fig == TRA) {
						TTRA *no_info = (TTRA *) malloc(sizeof(TTRA));
						no_info->base1  = measure[0];
						no_info->base2  = measure[1];
						no_info->altura = measure[2];
						area = (no_info->base1 + no_info->base2) * no_info->altura/2;
						no_info_v = no_info;
					}
					char nome_fig[4]; nome_fig[3] = '\0';
					for (i=0; i < 4; i++) nome_fig[i] = fig[i];
					reg_arq = inserir_orden_list_arq (reg_arq, codigo, cod_pai, tp_fig, nome_fig, no_info_v, area);
					num_reg_arq++;				
				}
				liberar_list_char  (substring); substring = NULL;
				liberar_list_float (medidas);   medidas   = NULL;
				flag_sep = 0; count_dec = 0; count_int = 0;

				break;
			}
			aux_lin++;
		}
	}
/*		
   	// CHECKPOINT
	TListArq *reg_arq_aux_check = reg_arq;
   	while (reg_arq_aux_check) {
		printf("Codigo: %d - Cod.Pai: %d - %s - Medidas: ", reg_arq_aux_check->cod, reg_arq_aux_check->cod_pai, reg_arq_aux_check->nome_fig);
		if (reg_arq_aux_check->tp_fig == RET) { TRET *no_info = (TRET *) reg_arq_aux_check->no_info; printf("Lado A: %.2f, Lado B: %.2f, Area: %.2f\n", no_info->largura, no_info->comprimento, reg_arq_aux_check->area);}
		if (reg_arq_aux_check->tp_fig == QUA) { TQUA *no_info = (TQUA *) reg_arq_aux_check->no_info; printf("Lado: %.2f, Area: %.2f\n", no_info->lado, reg_arq_aux_check->area);}
		if (reg_arq_aux_check->tp_fig == CIR) { TCIR *no_info = (TCIR *) reg_arq_aux_check->no_info; printf("Raio: %.2f, Area: %.2f\n", no_info->raio, reg_arq_aux_check->area);}
		if (reg_arq_aux_check->tp_fig == TRI) { TTRI *no_info = (TTRI *) reg_arq_aux_check->no_info; printf("Base: %.2f, Altura: %.2f, Area: %.2f\n", no_info->base, no_info->altura, reg_arq_aux_check->area);}
		if (reg_arq_aux_check->tp_fig == TRA) { TTRA *no_info = (TTRA *) reg_arq_aux_check->no_info; printf("Base A: %.2f, Base B: %.2f, Altura: %.2f, Area: %.2f\n", no_info->base1, no_info->base2, no_info->altura, reg_arq_aux_check->area);}
		reg_arq_aux_check = reg_arq_aux_check->prox;
	}
*/
	TListArq *reg_arq_aux = reg_arq;
	TListInt *cod_pai_list = NULL;
	char *temp_erro = (char *) malloc (sizeof(char)*300);
	for (i=0; reg_arq_aux; reg_arq_aux = reg_arq_aux->prox) {
		
		if ((reg_arq_aux->cod_pai != 0) && (i == 0)) {
			cod_log_erro = 1;
			sprintf(log_erro[count_erro], "Cód. %d/Cód. Pai %d/Tipo %s: Inexistência de RAIZ (o menor código do pai encontrado foi %d).\n", reg_arq_aux->cod, reg_arq_aux->cod_pai, reg_arq_aux->nome_fig, reg_arq_aux->cod_pai);
			count_erro++;
		}
		
		if (reg_arq_aux->cod_pai == 0) {
			
			if (i == 0)  {
				cod_pai_list = inserir_final_list_int (cod_pai_list, reg_arq_aux->cod_pai);
				sprintf(temp_erro, "Cód. %d/Cód. Pai %d/Tipo %s: Existência de mais de uma RAIZ (registros com código do pai igual 0).\n", reg_arq_aux->cod, reg_arq_aux->cod_pai, reg_arq_aux->nome_fig);
			} else if (i == 1) {
				cod_log_erro = 2;
				sprintf(log_erro[count_erro], temp_erro);
				count_erro++;
				sprintf(log_erro[count_erro], "Cód. %d/Cód. Pai %d/Tipo %s: Existência de mais de uma RAIZ (registros com código do pai igual 0).\n", reg_arq_aux->cod, reg_arq_aux->cod_pai, reg_arq_aux->nome_fig);
				count_erro++;
			} else if (i > 1) {
				sprintf(log_erro[count_erro], "Cód. %d/Cód. Pai %d/Tipo %s: Existência de mais de uma RAIZ (registros com código do pai igual 0).\n", reg_arq_aux->cod, reg_arq_aux->cod_pai, reg_arq_aux->nome_fig);
				count_erro++;
			}
		}
		
		if (reg_arq_aux->cod_pai == reg_arq_aux->cod) {
			cod_log_erro = 3;
			sprintf(log_erro[count_erro], "Cód. %d/Cód. Pai %d/Tipo %s: Auto-referenciamento (registros cujo código é igual ao código do pai).\n", reg_arq_aux->cod, reg_arq_aux->cod_pai, reg_arq_aux->nome_fig);
			count_erro++;
		} else {
			if (buscar_list_int (cod_pai_list, reg_arq_aux->cod)) {
				cod_log_erro = 4;
				sprintf(log_erro[count_erro], "Cód. %d/Cód. Pai %d/Tipo %s: Código repetido (mais de um registro com o mesmo código).\n", reg_arq_aux->cod, reg_arq_aux->cod_pai, reg_arq_aux->nome_fig);
				count_erro++;
			} else if (buscar_list_int (cod_pai_list, reg_arq_aux->cod_pai)) {
				cod_pai_list = inserir_final_list_int (cod_pai_list, reg_arq_aux->cod);
			} else {
				cod_log_erro = 5;
				sprintf(log_erro[count_erro], "Cód. %d/Cód. Pai %d/Tipo %s: Código pai inexistente.\n", reg_arq_aux->cod, reg_arq_aux->cod_pai, reg_arq_aux->nome_fig);
				count_erro++;
			}
		}
		i++;
	}
	free (temp_erro);
	free (cod_pai_list);
	
	if (cod_log_erro) {
		printf ("Erros encontrados no arquivo de entrada:\n");
		for (i=0; i < count_erro; i++)
			printf ("%s", log_erro[i]);
		return NULL;
	}
	
	// INI: CRIA ARVORE
	TAG *m_adj[num_reg_arq+1]; // = {NULL};
	for(i=0; i < num_reg_arq+1; m_adj[i++] = NULL);
	TAG *ant_ag = NULL;
	int ant_pai = -1;
	reg_arq_aux = reg_arq;
	while (reg_arq_aux) { // matriz (ou vetor) de adjacencias (ETAPA: setar os irmaos)

		TNO *new_no = (TNO *) malloc(sizeof(TNO));
		new_no->tipo = reg_arq_aux->tp_fig;
		for (i=0; i < 4; i++) new_no->nome[i] = reg_arq_aux->nome_fig[i]; // new_no->nome = reg_arq_aux->nome_fig;
		new_no->info = reg_arq_aux->no_info;
		new_no->area = reg_arq_aux->area;

		TAG *new_ag = (TAG *) malloc(sizeof(TAG));
		new_ag->cod = reg_arq_aux->cod;
		new_ag->no  = new_no;
		new_ag->filho = NULL;
		new_ag->irmao = NULL;

		if (reg_arq_aux->cod_pai == ant_pai)
			ant_ag->irmao = new_ag; // adiciona na lista de irmaos (filhos de um mesmo pai)
		else
			m_adj[reg_arq_aux->cod_pai] = new_ag; // faz o elemento da matriz (vetor) apontar para o 1o filho

		ant_ag      = new_ag;
		ant_pai     = reg_arq_aux->cod_pai;
		reg_arq_aux = reg_arq_aux->prox;
	}
/*	// CHECKPOINT
	int z;
	for(z=0; z < num_reg_arq+1; z++) {
		TAG *temp = m_adj[z];
		printf ("Pai %d:", z);
		if (!m_adj[z]) printf(" NULL");
		else for (; temp; temp = temp->irmao) printf(" %d", temp->cod);
		printf ("\n");
	}
*/
	setar_pais_filhos_ag (m_adj, 0); // matriz (ou vetor) de adjacencias (ETAPA: setar pais e filhos)
/*  // CHECKPOINT
	TAG *teste_1 = m_adj[1];
	while (teste_1) {
		if (teste_1->cod == 4) {
			printf ("Os filhos de %d: ", teste_1->cod);
			TAG *teste_2 = teste_1->filho;
			while (teste_2) {
				printf ("%d ", teste_2->cod);
				teste_2 = teste_2->irmao;
			}
		}
		teste_1 = teste_1->irmao;
	}
 */
	// FIM: CRIA ARVORE

	free (linha);
	liberar_list_arq (reg_arq);
	log_erro = (char **) malloc (sizeof(char *)*1000);
	for (i=0; i < count_erro; i++) free(log_erro[i]);
	free(log_erro);
	fclose (fp);
	
	return m_adj[0];
}

TListChar * inserir_final_list_char (TListChar *lista, char info) {

	TListChar *novo = (TListChar *) malloc(sizeof(TListChar));
	novo->info = info;
	novo->prox = NULL;

	if (!lista)
		return novo;

	TListChar *aux = lista;
	while (aux->prox)
		aux = aux->prox;
	aux->prox = novo;

	return lista;
}

TListInt * inserir_final_list_int (TListInt *lista, int info) {

	TListInt *novo = (TListInt *) malloc(sizeof(TListInt));
	novo->info = info;
	novo->prox = NULL;

	if (!lista)
		return novo;

	TListInt *aux = lista;
	while (aux->prox)
		aux = aux->prox;
	aux->prox = novo;

	return lista;
}

TListFloat * inserir_final_list_float (TListFloat *lista, float info) {

	TListFloat *novo = (TListFloat *) malloc(sizeof(TListFloat));
	novo->info = info;
	novo->prox = NULL;

	if (!lista)
		return novo;

	TListFloat *aux = lista;
	while (aux->prox)
		aux = aux->prox;
	aux->prox = novo;

	return lista;
}

TListArq * inserir_orden_list_arq (TListArq *r_arq, int cod, int c_pai, int t_fig, char *n_fig, void *no_info, float area) {

	if ((!r_arq) || (r_arq->cod_pai > c_pai)) {

		TListArq *novo = (TListArq *) malloc (sizeof(TListArq));
		novo->cod      = cod;
		novo->cod_pai  = c_pai;
		novo->tp_fig   = t_fig;
		int i;
		for (i=0; i < 4; i++) novo->nome_fig[i] = n_fig[i]; // novo->nome_fig = n_fig;
		novo->no_info  = no_info;
		novo->area     = area;
		novo->prox     = r_arq;
			
		return novo;
	}

	r_arq->prox = inserir_orden_list_arq (r_arq->prox, cod, c_pai, t_fig, n_fig, no_info, area);

	return r_arq;
}

void liberar_list_char (TListChar *lista) {

	if (lista) {
		liberar_list_char (lista->prox);
		free (lista);
	}
}

void liberar_list_int (TListInt *lista) {

	if (lista) {
		liberar_list_int (lista->prox);
		free (lista);
	}
}

void liberar_list_float (TListFloat *lista) {

	if (lista) {
		liberar_list_float (lista->prox);
		free (lista);
	}
}

void liberar_list_arq (TListArq *lista) {

	if (lista) {
		liberar_list_arq (lista->prox);
		free (lista);
	}
}

TListInt * buscar_list_int (TListInt *lista, int info) {

	if (!lista) return NULL;
	
	if (lista->info == info)
		return lista;
	else 
		return buscar_list_int (lista->prox, info);
}

void setar_pais_filhos_ag (TAG **adj, int index) {

	if (adj[index]) {
		TAG *ag = adj[index];
		while (ag) {
			ag->filho = adj[ag->cod];
			setar_pais_filhos_ag (adj, ag->cod);
			ag = ag->irmao;
		}
	}
}

int iniciar_menu (TAG *arv_g) {
	
	if (!arv_g) {
		printf ("Não foi possível montar a árvore. Verifique o log de erros.\n");
		return 0;	
	}		
	
	TAG  *result = NULL; 
	TAB  *arv_B  = NULL;
	TABB *arv_bb = NULL;
	char opt, opt_2;
	int resp_usu = 1;
	int i;
	int cod, cod_pai, cod_herd, tp_fig;
	float *medidas;
	system("cls");
	printf("Escolha uma das opções abaixo:\n\n");
	printf("a - Buscar figuras geométricas, por meio de um código único.\n");
    printf("b - Imprimir informações relevantes, tanto da árvore, quanto das figuras, incluindo-se sua área.\n");
    printf("c - Inserir novas figuras.\n");
    printf("d - Retirar figuras, passando seus descendentes para outro pai.\n");
    printf("e - Destruir a árvore.\n");
    printf("f - Alterar as dimensões de figuras.\n");
    printf("g - Transformar em árvore binária de busca balanceada, baseando-se no código único.\n");
	printf("h - Converter em árvore B, baseando-se no código único.\n");
	printf("Digite o número 0 para sair.\n");
	scanf (" %c", &opt);
    printf("\n");
	switch (opt){
        
		case 'a':
            printf("Digite o código da figura/nó: ");
			scanf (" %d", &cod);
            printf("\n\n");
			if(result = buscar_figura (cod, arv_g)) 
				imprimir_info_figura (result, buscar_figura_pai (cod, arv_g, NULL));
			else
				printf("Não existe uma figura/nó com o código informado!");
            system("pause");
            break;
        
		case 'b':
            printf("Digite qualquer coisa (ou apenas ENTER) para informações a partir da raiz.\n");
			printf("Digite 's' para informações de uma subarvore no modo simples.\n");
			printf("Digite 'v' para informações de uma subarvore no modo completo.\n");
			printf("Digite 'n' para informações de um nó em particular.\n");
			printf("A opção é: ");
			scanf (" %c", &opt);
            printf("\n\n");
			if ((opt == 's') || (opt == 'v') || (opt == 'n')) {
				printf("Digite o código da figura/nó: ");
				scanf (" %d", &cod);
				if (result = buscar_figura (cod, arv_g)) {
					if (opt == 's') imprimir_info_subarv_simples (result);
					if (opt == 'v') imprimir_info_subarv_verbose (result);
					if (opt == 'n') imprimir_info_figura (result, buscar_figura_pai (cod, arv_g, NULL));
				} else 
					printf("Não existe uma figura/nó com o código informado!");
			} else 
				imprimir_info_subarv_verbose (arv_g);
			system("pause");
            break;		
		
		case 'c':
			while (1) {
				printf("Digite um código único para identificar a figura na árvore: ");
				scanf (" %d", &cod);
				if (buscar_figura (cod, arv_g))
					printf("Esse código já existe!\n");
				else
					break;
			}
			while (1) {
				printf("Digite o código do pai do novo nó: ");
				scanf (" %d", &cod_pai);
				if (!buscar_figura (cod_pai, arv_g))
					printf("Esse código NÃO existe!\n");
				else
					break;
			}
			while (1) {
				float *aux_med;
				printf("Qual tipo de figura você quer inserir?\n");
				printf("1 - TRI\n");
				printf("2 - RET\n");
				printf("3 - TRA\n");
				printf("4 - CIR\n");
				printf("5 - QUA\n");
				printf("Tipo: ");
				scanf(" %d", &tp_fig);
				if (tp_fig == TRI) {
					medidas = (float *) malloc (sizeof(float)*2);
					aux_med = medidas;
					printf("Informe a base do triângulo: ");
					scanf(" %f", aux_med++);
					printf("\n");
					printf("Informe a altura do triângulo: ");
					scanf(" %f", aux_med);
					break;
				} else if (tp_fig == RET) {
					medidas = (float *) malloc (sizeof(float)*2);
					aux_med = medidas;
					printf("Informe o comprimento do retângulo: ");
					scanf(" %f", aux_med++);
					printf("\n");
					printf("Informe a largura do retângulo: ");
					scanf(" %f", aux_med);
					break;
				} else if (tp_fig == TRA) {
					medidas = (float *) malloc (sizeof(float)*3);
					aux_med = medidas;
					printf("Informe uma das bases do trapézio: ");
					scanf(" %f", aux_med++);
					printf("\n");
					printf("Informe a outra base do trapézio: ");
					scanf(" %f", aux_med++);
					printf("Informe a altura do trapézio: ");
					scanf(" %f", aux_med);
					break;
				} else if (tp_fig == CIR) {
					medidas = (float *) malloc (sizeof(float)*1);
					aux_med = medidas;
					printf("Informe o raio do círculo: ");
					scanf(" %f", aux_med);
					break;
				} else if (tp_fig == QUA) {
					medidas = (float *) malloc (sizeof(float)*1);
					aux_med = medidas;
					printf("Informe o lado do quadrado: ");
					scanf(" %f", aux_med);
					break;
				} else {
					printf("Opção inválida!");
				}
			}
			if (result = inserir_figura (arv_g, cod, cod_pai, tp_fig, medidas)) {
				printf("Figura inserida com sucesso!\n");
				imprimir_info_figura (result, buscar_figura_pai (cod, arv_g, NULL));
			} else {
				printf("Problemas na inserção da figura! Consulte o suporte.\n");
			}
			system("pause");
            break;
		
		case 'd':
			while (1) {
				printf("Digite o código da figura que você quer remover: ");
				scanf (" %d", &cod);
				if (buscar_figura (cod, arv_g))
					break;
				else
					printf("Esse código %d NÃO existe!\n", cod);
			}
			while (1) {
				printf("Agora digite o código da figura para a qual você quer passar os descendentes da figura a ser removida: ");
				scanf (" %d", &cod_herd);
				if (buscar_figura (cod_herd, arv_g)) {
					TAG *raiz_sub = buscar_figura (cod, arv_g);
					TAG *temp = raiz_sub->irmao;
					raiz_sub->irmao = NULL;
					if (buscar_figura (cod_herd, buscar_figura (cod, raiz_sub))) {
						raiz_sub->irmao = temp;
						printf("Código %d NÃO permitido, pois faz parte da subárvore cuja \"raiz\" é %d!\n", cod_herd, cod);
					} else {
						raiz_sub->irmao = temp;
						break;
					}
				} else
					printf("Esse código %d NÃO existe!\n", cod_herd);
			}
			retirar_figura (arv_g, cod, cod_herd);
			imprimir_info_subarv_simples (arv_g);
			system("pause");
            break;;
		
		case 'e':
			while (1) {
				printf("Confirma que quer destruir a árvore (s/N)?");
				scanf (" %c", &opt);
				if (opt == 's' || opt == 'S' || opt == 10 || opt == 13) {
					destruir_arvore (arv_g);
					arv_g = NULL;
					imprimir_info_subarv_simples (arv_g);
					break;
				} else if (opt == 'n' || opt == 'N') {
					printf("Okay! O seguro morreu de velho!");
					break;
				} else {
					printf("Opção inválida!");
				}
			}		
			system("pause");
            break;
		
		case 'f':
			while (1) {
				printf("Digite o código da figura que você quer alterar as dimensões: ");
				scanf (" %d", &cod);
				if (!(result = buscar_figura (cod, arv_g)))
					printf("Esse código NÃO existe!\n");
				else {
					float medida;
					if (result->no->tipo == TRI) {
						TTRI *info = (TTRI *) result->no->info;
						printf("A medida atual da base do triângulo é %.2f\n", info->base);
						printf("A medida atual da altura do triângulo é %.2f\n", info->altura);
						printf("Digite a nova base do triângulo ou ENTER para mantê-la: ");
						scanf(" %f", &medida); info->base = medida;
						printf("Digite a nova base do triângulo ou ENTER para mantê-la: ");
						scanf(" %f", &medida); info->altura = medida;
						result->no->area = info->base * info->altura/2;
					} else if (result->no->tipo == RET) {
						TRET *info = (TRET *) result->no->info;
						printf("A medida atual da largura do retângulo é %.2f\n", info->largura);
						printf("A medida atual do comprimento do retângulo é %.2f\n", info->comprimento);
						printf("Digite a nova largura do retângulo ou ENTER para mantê-la: ");
						scanf(" %f", &medida); info->largura = medida;
						printf("Digite a nova comprimento do retângulo ou ENTER para mantê-lo: "); 
						scanf(" %f", &medida); info->comprimento = medida;
						result->no->area = info->largura * info->comprimento;
					} else if (result->no->tipo == TRA) {
						TTRA *info = (TTRA *) result->no->info;
						printf("A medida atual de uma das bases do trapézio é %.2f\n", info->base1);
						printf("A medida atual da outra base do trapézio é %.2f\n", info->base2);
						printf("A medida atual da altura do trapézio é %.2f\n", info->altura);
						printf("Digite um novo valor para esta base ou ENTER para mantê-lo: ");
						scanf(" %f", &medida); info->base1 = medida;
						printf("Digite um novo valor para esta base ou ENTER para mantê-lo: ");
						scanf(" %f", &medida); info->base2 = medida;
						printf("Digite a nova altura do trapézio ou ENTER para mantê-la: ");
						scanf(" %f", &medida); info->altura = medida;
						result->no->area = (info->base1 + info->base2)*info->altura/2;
					} else if (result->no->tipo == CIR) {
						TCIR *info = (TCIR *) result->no->info;
						printf("A medida atual do raio do círculo é %.2f\n", info->raio);
						printf("Digite o novo raio do círculo ou ENTER para mantê-lo: ");
						scanf(" %f", &medida); info->raio = medida;
						result->no->area = info->raio * info->raio * PI/2;
					} else if (result->no->tipo == QUA) {
						TQUA *info = (TQUA *) result->no->info;
						printf("A medida atual do lado do quadrado é %.2f\n", info->lado);
						printf("Digite o novo lado do quadrado ou ENTER para mantê-lo: ");
						scanf(" %f", &medida); info->lado = medida;
						result->no->area = info->lado * info->lado;
					}
					printf("A figura modificada possui agora as seguintes informações:\n");
					imprimir_info_figura (result, buscar_figura_pai (cod, arv_g, NULL));
					break;
				}
			}
			system("pause");
            break;
		
		case 'g':
			destruir_abb (arv_bb);
			arv_bb = converter_abb (arv_g);
			imprimir_abb (arv_bb);
			system("pause");
            break;
		
		case 'h':
			destruir_aB (arv_B);
			arv_B = converter_aB (arv_g);
			imprimir_aB (arv_B);
			system("pause");
            break;
		
		case '0':
			resp_usu = 0;
			printf ("Até mais!\n");
			system("pause");
            break;
		
		default:
			printf("Opção inválida!\n");
            system("pause");
            break;
	}
	
	free (medidas);
	
	return resp_usu;
}


TAG * buscar_figura (int cod, TAG *ag) {
	
	TAG *aux = ag, *ret = NULL;
	if (!aux)
		return NULL;
	else
		if (aux->cod == cod)
			return aux;
		else 
			if (ret = buscar_figura (cod, aux->filho))
				return ret;
			else 
				return buscar_figura (cod, aux->irmao);
}

TAG * buscar_figura_pai (int cod, TAG *ag, TAG *ag_pai) {
	
	TAG *aux = ag, *ret = NULL;
	if (!aux)
		return NULL;
	else
		if (aux->cod == cod)
			return ag_pai;
		else 
			if (ret = buscar_figura_pai (cod, aux->filho, aux))
				return ret;
			else 
				return buscar_figura_pai (cod, aux->irmao, ag_pai);
}

void imprimir_info_figura (TAG *ag, TAG *ag_pai) {
	
	TAG *aux = NULL;
	int i;
	int num_fig[6];
	int tot_parent;
	float area_parent;
	char figura[4]; figura[3] = '\0';
	
	if (!ag) {
		printf ("NULL");
		return;
	}
	printf ("Código: %d\n", ag->cod);
	printf ("Figura: %s\n", ag->no->nome);
	printf ("Área: %.2f\n", ag->no->area);
	if (ag->no->tipo == TRI) {
		TTRI *info = (TTRI *) ag->no->info;
		printf ("Dimensões: Base %.2f e Altura %.2f\n", info->base, info->altura);
	} else if (ag->no->tipo == RET) {
		TRET *info = (TRET *) ag->no->info;
		printf ("Largura %.2f e Comprimento %.2f\n", info->largura, info->comprimento);
	} else if (ag->no->tipo == TRA) {
		TTRA *info = (TTRA *) ag->no->info;
		float b_menor, b_maior;
		if (info->base1 >= info->base2) {b_maior = info->base1; b_menor = info->base2;}
		else                            {b_maior = info->base2; b_menor = info->base1;}
		printf ("Base Menor %.2f, Base Maior %.2f e Altura %.2f\n", b_menor, b_maior, info->altura);
	} else if (ag->no->tipo == CIR) {
		TCIR *info = (TCIR *) ag->no->info;
		printf ("Raio %.2f\n", info->raio);
	} else if (ag->no->tipo == QUA) {
		TQUA *info = (TQUA *) ag->no->info;
		printf ("Lado %.2f\n", info->lado);
	}
	
	if (!ag_pai) {
		printf ("RAIZ! Não possui irmãos!\n");
	} else {
	
		for (i=0; i<6; i++) num_fig[i] = 0;
		tot_parent = 0;
		area_parent = 0.0;
		
		aux = ag_pai->filho;
		if (aux->irmao) printf ("*** Irmãos ***\n");
		else printf ("Não possui irmãos!\n");
		
		if (aux->irmao) {
			while (aux) {
				if (aux->cod != ag->cod) {
					num_fig[aux->no->tipo]++;
					area_parent += aux->no->area;
					tot_parent++;
					printf ("%d (%s)", aux->cod, aux->no->nome);
					if (aux->irmao) // se houver proximo irmao (o no atual NAO eh o ultimo)
						if (aux->irmao->cod != ag->cod) printf (" -> "); // se o proximo irmao NAO for eu mesmo 
						else if (aux->irmao->irmao) 	printf (" -> "); // se o proximo irmao for eu mesmo MAS ainda existe(m) irmão(s) após eu
				}
				aux = aux->irmao;
			}
			printf ("\n");
			printf ("Total de irmãos: %d\n", tot_parent);
			printf ("Área total dos irmãos: %.2f\n", area_parent);
			printf ("Dentre os irmãos, ao todo são: ");
			printf ("%d TRI, %d RET, %d TRA, %d CIR e %d QUA\n", num_fig[TRI], num_fig[RET], num_fig[TRA], num_fig[CIR], num_fig[QUA]);
		}
	}
	
	for (i=0; i<6; i++) num_fig[i] = 0;
	tot_parent = 0;
	area_parent = 0.0;
	
	aux = ag->filho;
	if (aux) printf ("*** Filhos ***\n");
	else printf ("Não possui filhos!\n");
	
	if (aux) {
		while (aux) {
			num_fig[aux->no->tipo]++;
			area_parent += aux->no->area;
			tot_parent++;
			printf ("%d (%s)", aux->cod, aux->no->nome);
			if (aux->irmao) printf (" -> ");
			aux = aux->irmao;
		}
		printf ("\n");	
		printf ("Total de filhos: %d\n", tot_parent);
		printf ("Área total dos filhos: %.2f\n", area_parent);
		printf ("Dentre os filhos, ao todo são: ");
		printf ("%d TRI, %d RET, %d TRA, %d CIR e %d QUA\n", num_fig[TRI], num_fig[RET], num_fig[TRA], num_fig[CIR], num_fig[QUA]);
	}
}

void imprimir_info_subarv_simples (TAG *ag) {
	
	TAG *aux = NULL;
	if (ag) {
		if (ag->filho) {
			printf ("Filho(s) de %d: ", ag->cod);
			aux = ag->filho;
			while (aux) {
				printf ("%d", aux->cod);
				if (aux->irmao) printf(" -> ");
				aux = aux->irmao;
			}
			printf("\n");
			aux = ag->filho;
			while (aux) {
				imprimir_info_subarv_simples (aux);
				aux = aux->irmao;
			}
		}
	} else
		printf ("Árvore não existe!\n");
}

void imprimir_info_subarv_verbose (TAG *ag) {
	
	if (!ag) {
		printf ("Árvore não existe!\n");
		return;
	}
	
	int i;
	int *n_tot_figs = (int *) malloc (sizeof(int));     
	float *tot_area = (float *) malloc (sizeof(float)); 
	int **num_fig = (int **) malloc (sizeof(int*));
	num_fig[0] = (int *) malloc (sizeof(int)*6);
	float **area_fig = (float **) malloc (sizeof(float*));
	area_fig[0] = (float *) malloc (sizeof(float)*6);
	int **cod_maior_area_fig = (int **) malloc (sizeof(int*));
	cod_maior_area_fig[0] = (int *) malloc (sizeof(int)*6);
	char ***nome_maior_area_fig = (char ***) malloc (sizeof(char**));
	nome_maior_area_fig[0] = (char **) malloc (sizeof(char *)*6);
	for (i=0; i < 6; i++) nome_maior_area_fig[0][i] = (char *) malloc (sizeof(char)*4);
	float **maior_area_fig = (float **) malloc (sizeof(float*));
	maior_area_fig[0] = (float *) malloc (sizeof(float)*6);
	int **cod_menor_area_fig = (int **) malloc (sizeof(int*));
	cod_menor_area_fig[0] = (int *) malloc (sizeof(int)*6);
	char ***nome_menor_area_fig = (char ***) malloc (sizeof(char**));
	nome_menor_area_fig[0] = (char **) malloc (sizeof(char *)*6);
	for (i=0; i < 6; i++) nome_menor_area_fig[0][i] = (char *) malloc (sizeof(char)*4);
	float **menor_area_fig = (float **) malloc (sizeof(float*));
	menor_area_fig[0] = (float *) malloc (sizeof(float)*6);
	float maior_area = 0.0, menor_area = FLT_MAX;
	int cod_maior_area = 0, cod_menor_area = 0;
	char fig_maior_area[4], fig_menor_area[4]; 
	char nome_fig[6][4] = {"","TRI","RET","TRA","CIR","QUA"};
	for (i=1; i<6; i++) nome_fig[i][3] = '\0';
	
	*n_tot_figs = 0;
	*tot_area = 0.0;
	for (i=0; i<6; i++) {
		num_fig[0][i] = 0; 
		area_fig[0][i] = 0.0;
		cod_maior_area_fig[0][i] = 0;
		cod_menor_area_fig[0][i] = 0;
		maior_area_fig[0][i] = 0.0;
		menor_area_fig[0][i] = FLT_MAX;
	}	

	printf ("LEGENDA: CÓDIGO (TIPO/ÁREA)\n");
	imprimir_info_subarv (ag, n_tot_figs, tot_area, num_fig, area_fig, cod_maior_area_fig, nome_maior_area_fig, maior_area_fig, cod_menor_area_fig, nome_menor_area_fig, menor_area_fig);

	for (i=1; i<6; i++) {		
		if (maior_area < maior_area_fig[0][i]) {		
			maior_area = maior_area_fig[0][i];
			cod_maior_area = cod_maior_area_fig[0][i];			
			int j;
			for (j=0; j<4; j++) fig_maior_area[j] = nome_maior_area_fig[0][i][j];
		}		
		if (menor_area > menor_area_fig[0][i]) {		
			menor_area = menor_area_fig[0][i];	
			cod_menor_area = cod_menor_area_fig[0][i];			
			int j;
			for (j=0; j<4; j++) fig_menor_area[j] = nome_menor_area_fig[0][i][j];		
		}		
	}
			
    printf ("TOTAL FIGs: %d ", *n_tot_figs);
	printf ("(");
	for (i=1; i<6; i++) {
		printf ("%d %s", num_fig[0][i], nome_fig[i]);
		if (i < 4) // num_fig - 2 
			printf (", ");
		else if (i == 4) // num_fig - 2 
			printf (" e ");			
	}
	printf (")\n");
	
	printf ("TOTAL AREA: %.2f ", *tot_area);
	printf ("(");
	for (i=1; i<6; i++) {
		printf ("%.2f %s", area_fig[0][i], nome_fig[i]);
		if (i < 4) // num_fig - 2 
			printf (", ");
		else if (i == 4) // num_fig - 2 
			printf (" e ");			
	}
	printf (")\n");

	printf ("MAIOR AREA: %.2f (da fig. %d, cujo tipo é %s)\n", maior_area, cod_maior_area, fig_maior_area);		
	printf ("MENOR AREA: %.2f (da fig. %d, cujo tipo é %s)\n", menor_area, cod_menor_area, fig_menor_area);		
	printf ("MAIOR AREA/TIPO:\n");
	for (i=1; i<6; i++)
		if (maior_area_fig[0][i] > 0.0)
			printf ("- %s: %.2f (fig. %d)\n", nome_maior_area_fig[0][i], maior_area_fig[0][i], cod_maior_area_fig[0][i]);
	printf ("MENOR AREA/TIPO:\n");
	for (i=1; i<6; i++)
		if (menor_area_fig[0][i] < FLT_MAX)	
			printf ("- %s: %.2f (fig. %d)\n", nome_menor_area_fig[0][i], menor_area_fig[0][i], cod_menor_area_fig[0][i]);
	
	free (n_tot_figs);
	free (tot_area);
	free (num_fig[0]);            free (num_fig);
	free (area_fig[0]);           free (area_fig); 
	free (cod_maior_area_fig[0]); free (cod_maior_area_fig);
	free (maior_area_fig[0]);     free (maior_area_fig);
	free (cod_menor_area_fig[0]); free (cod_menor_area_fig);
	free (menor_area_fig[0]);     free (menor_area_fig);

	for (i=0; i < 6; i++) free (nome_maior_area_fig[0][i]);
	free (nome_maior_area_fig[0]);
	free (nome_maior_area_fig);
	
	for (i=0; i < 6; i++) free (nome_menor_area_fig[0][i]);
	free (nome_menor_area_fig[0]);
	free (nome_menor_area_fig);	
}	

void imprimir_info_subarv (TAG *ag, int *num_nodes, float *area_tot, int **num_fig, float **area_fig, int **cod_maior_area_fig, char ***nome_maior_area_fig, float **maior_area_fig, int **cod_menor_area_fig, char ***nome_menor_area_fig, float **menor_area_fig) {
	
	int i;
	TAG *aux = NULL;
	if (ag) {
		(*num_nodes)++;
		(*area_tot) += ag->no->area;
		num_fig[0][ag->no->tipo]++;
		area_fig[0][ag->no->tipo] += ag->no->area;
		if (ag->no->area > maior_area_fig[0][ag->no->tipo]) {
			maior_area_fig[0][ag->no->tipo] = ag->no->area;
			cod_maior_area_fig[0][ag->no->tipo] = ag->cod;
			for (i=0; i<4; i++) nome_maior_area_fig[0][ag->no->tipo][i] = ag->no->nome[i];
		}
		if (ag->no->area < menor_area_fig[0][ag->no->tipo]) {
			menor_area_fig[0][ag->no->tipo] = ag->no->area;
			cod_menor_area_fig[0][ag->no->tipo] = ag->cod;
			for (i=0; i<4; i++) nome_menor_area_fig[0][ag->no->tipo][i] = ag->no->nome[i];
		}
				
		if (ag->filho) {
			printf ("Filho(s) de %d (%s/%.2f): ", ag->cod, ag->no->nome, ag->no->area);
			aux = ag->filho;
			while (aux) {
				printf ("%d (%s/%.2f)", aux->cod, aux->no->nome, aux->no->area);
				if (aux->irmao) printf(" -> ");
				aux = aux->irmao;
			}
			printf("\n");
			aux = ag->filho;
			while (aux) {
				imprimir_info_subarv (aux, num_nodes, area_tot, num_fig, area_fig, cod_maior_area_fig, nome_maior_area_fig, maior_area_fig, cod_menor_area_fig, nome_menor_area_fig, menor_area_fig);
				aux = aux->irmao;
			}
		}
	}
}

TAG * inserir_figura (TAG *ag, int cod, int cod_pai, int tp_f, float *med) {
	
	float area = 0.0;
	void *no_info_v = NULL;
	if (tp_f == RET) {
		TRET *no_info = (TRET *) malloc(sizeof(TRET));			
		no_info->largura     = med[0];			
		no_info->comprimento = med[1];			
		area = no_info->largura * no_info->comprimento;			
		no_info_v = no_info;			
	} else if (tp_f == QUA) {			
		TQUA *no_info = (TQUA *) malloc(sizeof(TQUA));			
		no_info->lado = med[0];			
		area = no_info->lado * no_info->lado;			
		no_info_v = no_info;			
	} else if (tp_f == CIR) {			
		TCIR *no_info = (TCIR *) malloc(sizeof(TCIR));			
		no_info->raio = med[0];			
		area = no_info->raio * no_info->raio*PI/2;			
		no_info_v = no_info;			
	} else if (tp_f == TRI) {			
		TTRI *no_info = (TTRI *) malloc(sizeof(TTRI));			
		no_info->base   = med[0];			
		no_info->altura = med[1];			
		area = no_info->base * no_info->altura/2;			
		no_info_v = no_info;			
	} else if (tp_f == TRA) {			
		TTRA *no_info = (TTRA *) malloc(sizeof(TTRA));			
		no_info->base1  = med[0];			
		no_info->base2  = med[1];			
		no_info->altura = med[2];			
		area = (no_info->base1 + no_info->base2) * no_info->altura/2;			
		no_info_v = no_info;			
	}				
	
	TNO *new_no = (TNO *) malloc(sizeof(TNO));
	new_no->tipo = tp_f;
	new_no->info = no_info_v;
	new_no->area = area;
	
	TAG *new_ag = (TAG *) malloc(sizeof(TAG));
	new_ag->cod = cod;
	new_ag->no  = new_no;
	new_ag->filho = NULL;
	new_ag->irmao = NULL;
		
	TAG *aux = buscar_figura (cod_pai, ag);
	
	aux = aux->filho;
	while (aux->irmao) aux = aux->irmao;
	aux->irmao = new_ag;
	
	return new_ag;
}
void retirar_figura (TAG *ag, int cod_r, int cod_h) {

	TAG *fig_retir   = buscar_figura (cod_r, ag);
	TAG *fig_herd    = buscar_figura (cod_h, ag);
	TAG *fig_ret_pai = buscar_figura_pai (cod_r, ag, NULL);
	
	TAG *aux = fig_ret_pai->filho;
	TAG *ant = aux;
	while (aux != fig_retir) {
		ant = aux;
		aux = aux->irmao;
	}
	
	// IRMAOS
	if (aux == ant) // 1o irmao: o pai deve apontar para o 2o irmao (incluindo NULL, se for filho unico)
		fig_ret_pai->filho = aux->irmao;
	else // 2o irmao em diante: o 'irmao' do irmao anterior tem de apontar para o irmao posterior (incluindo NULL, se for o ultimo irmao)
		ant->irmao = aux->irmao; 
	
	// FILHOS
	if (fig_herd->filho) { // herdeiro tem filhos: apontar 'irmao' do ultimo filho para 'filho' do no que sera removido
		aux = fig_herd->filho;
		while (aux->irmao) aux = aux->irmao;
		aux->irmao = fig_retir->filho;
	} else  // herdeiro NAO tem filhos: apontar 'filho' do herdeiro para 'filho' do no que sera removido
		fig_herd->filho = fig_retir->filho;
		
	free (fig_retir->no->info);
	free (fig_retir->no);
	free (fig_retir);
}

void destruir_arvore (TAG *ag) {

	if (ag) {
		
		if (ag->filho) {
			TAG *aux = ag->filho;
			while (aux) {
				TAG *temp = aux->irmao;
				destruir_arvore (aux);
				aux = temp;
			}
		}
/*
		if (ag->no->tipo == TRI) {TTRI *info = (TTRI *) ag->no->info; free (info);}
		if (ag->no->tipo == RET) {TRET *info = (TRET *) ag->no->info; free (info);}
		if (ag->no->tipo == TRA) {TTRA *info = (TTRA *) ag->no->info; free (info);}
		if (ag->no->tipo == CIR) {TCIR *info = (TCIR *) ag->no->info; free (info);}
		if (ag->no->tipo == QUA) {TQUA *info = (TQUA *) ag->no->info; free (info);}
*/	
		printf("Liberando %d...\n", ag->cod);
		free (ag->no->info);
		free (ag->no);
		free (ag);
	}
}

void destruir_abb (TABB *abb) {
}

void destruir_aB (TAB *aB) {
}

TABB * converter_abb (TAG *ag) {
}

TAB * converter_aB (TAG *ag) {
}

void imprimir_abb (TABB *abb) {
}

void imprimir_aB (TAB *aB) {
}
