#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

typedef struct list_char {
	char info;
	struct list_char *prox;
} TListChar;

typedef struct list_arq {
	int cod;
	int cod_pai;
	int tp_fig;
	void *no_info;
	struct list_arq *prox;
} TListArq;

typedef struct triangulo {
	float base;
	float altura;
	float area;
} TTRI;

typedef struct retangulo {
	float l_menor;
	float l_maior;
	float area;
} TRET;

typedef struct trapezio {
	float b_menor;
	float b_maior;
	float altura;
	float area;
} TTRA;

typedef struct circulo {
	float raio;
	float area;
} TCIR;

typedef struct quadrado {
	float lado;
	float area;
} TQUA;

typedef struct info {
	int tipo;
	void *info;
} TNO;

typedef struct ag {
	int cod;
	TNO *no;
	struct ag *filho;
	struct ag *irmao;
} TAG;

enum figura {TRI, RET, TRA, CIR, QUA};

/*
(a) buscar figuras geometricas, por meio de um codigo unico
(b) imprimir informações relevantes, tanto da árvore, quanto das figuras, incluindo-se sua area
(c) inserir novas figuras
(d) retirar figuras, passando seus descendentes para outro pai
(e) destruir a arvore
(f) alterar as dimensoes de figuras
(g) transformar em arvore binaria de busca balanceada, baseando-se no codigo unico
(h) converter em arvore B, baseando-se no codigo unico
*/

// INI: FUNCOES REQUISITADAS

TAG * buscar_figura (int cod);
void imprimir_arvore (int cod);
void imprimir_figura (int cod);
void inserir_figura (TAG *ag, int cod, int cod_pai, int tp, void *info);
TAG * retirar_figura (TAG *ag, int cod);
void destruir_arvore (TAG *ag);
int alterar_figura (int cod, void *info);
TAG * converter_abb (TAG *ag);
TAG * converter_aB (TAG *ag);

// FIM: FUNCOES REQUISITADAS

int validar_arq(char *nome_arq);
TAG * criar_ag(char *nome_arq);
// void * inserir_final_lista (void *lista,  void info);
// void libera_lista (void *lista);
TListChar * inserir_final_lista (TListChar *lista, char info);
void libera_lista (TListChar *lista);
TListArq * ins_ord_list_arq (TListArq *r_arq, int cod, int c_pai, int t_fig, void *no_info);
void libera_lista_list_arq (TListArq *lista);
void setar_pais_filhos_ag (TAG **adj, int index);
void imprimir_ag (TAG *root);

int main (int argc, char* argv[]) {

	if (argv[1]) {
		if (validar_arq(argv[1])) {
			TAG *ag = criar_ag(argv[1]);
			imprimir_ag (ag); printf("\n");
		} else {
			printf("Arquivo inválido!\n");
			exit(2);
		}
	} else {
		printf("Cadê o arquivo de entrada?\n");
		printf("Digite no prompt: \"trabalho 'nome_do_arquivo_de_entrada'\" e depois tecle ENTER.\n");
 	    exit(1);
	}

	return 75;
}

int validar_arq(char *nome_arq) {
	return 1;
}

TAG * criar_ag (char *nome_arq) {

	int num_reg_arq = 0;
	TListArq *reg_arq = NULL;
	char *linha = (char *) malloc(200);
	FILE *fp = fopen (nome_arq, "r");

	while (fgets(linha,200,fp)) {

		enum figura tp_fig;
		TListChar *substring = NULL;
		// TListFloat *medidas = NULL;
		float *medidas, *medid_ender;
		int dim_med = 0;
		int i;
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

				substring = inserir_final_lista (substring, *aux_lin);
				if ((*aux_lin == '.') || (*aux_lin == ','))
					flag_sep = 1;
				else
					if (flag_sep)
						count_dec++;
					else
						count_int++;

			} else if (*aux_lin == '/') { // CODIGO e CODIGO_PAI

				int aux_cod = 0;
				TListChar *aux_substr = substring;
				while (aux_substr) {
					int pot10 = 1, info = 0;
					for (i=1; i < count_int; i++) pot10 *= 10;
					info = aux_substr->info - '0';
					aux_cod += info*pot10;
					count_int--;
					aux_substr = aux_substr->prox;
				}
				count_barra++;
				if (count_barra == 1) codigo  = aux_cod;
				if (count_barra == 2) cod_pai = aux_cod;
				libera_lista (substring); substring = NULL;
				count_int = 0;

			} else if (*aux_lin == ' ') { // NOME DA FIGURA e MEDIDAS DA FIGURA

				count_space++;

				if (count_space == 1) { // NOME DA FIGURA

					char fig[4]; fig[3] = '\0';
					TListChar *aux_substr = substring;
					for (i=0; aux_substr; aux_substr = aux_substr->prox) fig[i++] = aux_substr->info;
					if  (fig[0] == 'R') { tp_fig = RET; dim_med = 2;}
					if  (fig[0] == 'Q') { tp_fig = QUA; dim_med = 1;}
					if  (fig[0] == 'C') { tp_fig = CIR; dim_med = 1;}
					if ((fig[0] == 'T') && (fig[2] == 'I')) { tp_fig = TRI; dim_med = 2;}
					if ((fig[0] == 'T') && (fig[2] == 'A')) { tp_fig = TRA; dim_med = 3;}
					medidas = (float *) malloc (sizeof(float)*dim_med);
					medid_ender = medidas;
					libera_lista (substring); substring = NULL;
					count_int = 0;

				} else { // MEDIDAS DA FIGURA

					int aux_count = count_dec;
					float aux_med = 0.0;
					TListChar *aux_substr = substring;
					while (aux_substr) {
						if ((aux_substr->info == '.') || (aux_substr->info == ',')) {
							flag_sep = 1;
						} else {
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
							aux_med += info*pot10;
						}
						aux_substr = aux_substr->prox;
					}
					*medidas++ = aux_med;
					libera_lista (substring); substring = NULL;
					flag_sep = 0; count_dec = 0; count_int = 0;
				}

			} else if (*aux_lin == '\n') { // MEDIDAS DA FIGURA

				int aux_count = count_dec;
				float aux_med = 0;

				TListChar *aux_substr = substring;
				while (aux_substr) {
					if ((aux_substr->info == '.') || (aux_substr->info == ',')) {
						flag_sep = 1;
					} else {
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
						aux_med += info*pot10;
					}
					aux_substr = aux_substr->prox;
				}
				*medidas = aux_med;
/*
				float area = ((tp_fig == TRA) ? 0.0 : 1.0);
				for(i=0; i < dim_med; i++) { // area ainda nao entrou, por isso "dim_med-1"
					float info = medid_ender[i];
					if (tp_fig == RET) area *= info;           // 2 medidas
					if (tp_fig == QUA) area  = info*info;      // 1 medida
					if (tp_fig == CIR) area  = info*info*PI/2; // 1 medida
					if (tp_fig == TRI) area *= info;           // 2 medidas
					if (tp_fig == TRA) area = (((i+1 == 1 || i+1 == 2)) ? (area+info) : (area*info)); // 3 medidas
				}
				if (tp_fig == TRI || tp_fig == TRA) area /= 2.0;
*/
				void *no_info_v = NULL;
				if (tp_fig == RET) {
					TRET *no_info = (TRET *) malloc(sizeof(TRET));
					no_info->l_menor = medid_ender[0];
					no_info->l_maior = medid_ender[1];
					no_info->area    = no_info->l_menor * no_info->l_maior;
					no_info_v = no_info;
				} else if (tp_fig == QUA) {
					TQUA *no_info = (TQUA *) malloc(sizeof(TQUA));
					no_info->lado = medid_ender[0];
					no_info->area = no_info->lado * no_info->lado;
					no_info_v = no_info;
				} else if (tp_fig == CIR) {
					TCIR *no_info = (TCIR *) malloc(sizeof(TCIR));
					no_info->raio = medid_ender[0];
					no_info->area = no_info->raio * no_info->raio*PI/2;
					no_info_v = no_info;
				} else if (tp_fig == TRI) {
					TTRI *no_info = (TTRI *) malloc(sizeof(TTRI));
					no_info->base   = medid_ender[0];
					no_info->altura = medid_ender[1];
					no_info->area   = no_info->base * no_info->altura/2;
					no_info_v = no_info;
				} else if (tp_fig == TRA) {
					TTRA *no_info = (TTRA *) malloc(sizeof(TTRA));
					no_info->b_menor = medid_ender[0];
					no_info->b_maior = medid_ender[1];
					no_info->altura  = medid_ender[2];
					no_info->area    = (no_info->b_menor + no_info->b_maior) * no_info->altura/2;
					no_info_v = no_info;
				}

				libera_lista (substring); substring = NULL;
				flag_sep = 0; count_dec = 0; count_int = 0;

				reg_arq = ins_ord_list_arq (reg_arq, codigo, cod_pai, tp_fig, no_info_v);
				num_reg_arq++;

				break;
			}
			aux_lin++;
		}
	}

/*  	// CHECKPOINT
	TListArq *reg_arq_aux = reg_arq;
   	while (reg_arq_aux) {
		printf("Codigo: %d - Cod.Pai: %d - Cod.Fig: %d - Medidas: ", reg_arq_aux->cod, reg_arq_aux->cod_pai, reg_arq_aux->tp_fig);
		if (reg_arq_aux->tp_fig == RET) { TRET *no_info = (TRET *) reg_arq_aux->no_info; printf("Lado A: %.2f, Lado B: %.2f, Area: %.2f\n", no_info->l_menor, no_info->l_maior, no_info->area);}
		if (reg_arq_aux->tp_fig == QUA) { TQUA *no_info = (TQUA *) reg_arq_aux->no_info; printf("Lado: %.2f, Area: %.2f\n", no_info->lado, no_info->area);}
		if (reg_arq_aux->tp_fig == CIR) { TCIR *no_info = (TCIR *) reg_arq_aux->no_info; printf("Raio: %.2f, Area: %.2f\n", no_info->raio, no_info->area);}
		if (reg_arq_aux->tp_fig == TRI) { TTRI *no_info = (TTRI *) reg_arq_aux->no_info; printf("Base: %.2f, Altura: %.2f, Area: %.2f\n", no_info->base, no_info->altura, no_info->area);}
		if (reg_arq_aux->tp_fig == TRA) { TTRA *no_info = (TTRA *) reg_arq_aux->no_info; printf("Base A: %.2f, Base B: %.2f, Altura: %.2f, Area: %.2f\n", no_info->b_menor, no_info->b_maior, no_info->altura, no_info->area);}
		reg_arq_aux = reg_arq_aux->prox;
	}
*/
	// INI: CRIA ARVORE
	TAG *m_adj[num_reg_arq+1]; // = {NULL};
	int i;
	for(i=0; i < num_reg_arq+1; m_adj[i++] = NULL);

	TAG *ant_ag = NULL;
	int ant_pai = -1;
	TListArq *reg_arq_aux = reg_arq;
	while (reg_arq_aux) { // matriz (ou vetor) de adjacencias (ETAPA: setar os irmaos)

		TNO *new_no = (TNO *) malloc(sizeof(TNO));
		new_no->tipo = reg_arq_aux->tp_fig;
		new_no->info = reg_arq_aux->no_info;

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
/* CHECKPOINT
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
	libera_lista_list_arq (reg_arq);
	fclose (fp);
	return m_adj[0];
}

/*
void * inserir_final_lista (void *lista, void info) {

	void *novo = (void *) malloc(sizeof(void));
	novo->info = info;
	novo->prox = NULL;

	if (!lista)
		return novo;

	void *aux = lista;
	while (aux->prox)
		aux = aux->prox;
	aux->prox = novo;

	return lista;
}
*/

/*
void libera_lista (void *lista) {

	if (lista) {
		libera_lista (lista->prox);
		free (lista);
	}
}
*/

TListChar * inserir_final_lista (TListChar *lista, char info) {

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

void libera_lista (TListChar *lista) {

	if (lista) {
		libera_lista (lista->prox);
		free (lista);
	}
}

TListArq * ins_ord_list_arq (TListArq *r_arq, int cod, int c_pai, int t_fig, void *no_info) {

	if ((!r_arq) || (r_arq->cod_pai > c_pai)) {

		TListArq *novo = (TListArq *) malloc (sizeof(TListArq));
		novo->cod     = cod;
		novo->cod_pai = c_pai;
		novo->tp_fig  = t_fig;
		novo->no_info = no_info;
		novo->prox    = r_arq;
		return novo;
	}

	r_arq->prox = ins_ord_list_arq (r_arq->prox, cod, c_pai, t_fig, no_info);

	return r_arq;
}
void libera_lista_list_arq (TListArq *lista) {

	if (lista) {
		libera_lista_list_arq (lista->prox);
		free (lista);
	}
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

void imprimir_ag (TAG *root) {

	if (root) {
		printf ("%d > ", root->cod);
		imprimir_ag (root->filho);
		imprimir_ag (root->irmao);
	}
}
