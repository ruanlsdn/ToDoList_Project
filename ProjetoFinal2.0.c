#include <locale.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

//DECLARAÇÃO DE STRUCT
struct list {
	int id, dia, mes, ano, progresso;
	float nota;
	char descr[100], materia[100];
};

struct listArq {
	int idArq, diaArq, mesArq, anoArq, progressoArq;
	float notaArq;
	char descrArq[100], materiaArq[100];
};
//===============================================================================================

//DECLARAÇÃO DE FUNÇÕES
int leValidaOpcMenu();
char leValidaOpcCase();
char leValidaOpcCase2();
int leValidaOpcCase3();
int leValidaID();
int validaID(struct list dados[], int cont);
int leValidaDia();
int leValidaMes();
float leValidaNota();
void leValidaDescr(char *descr);
void leValidaMat(char *materia);
int leValidaProg();
int validaData(struct list dados[], int cont);
void listarAtividades (int cont, struct list dadosCrud[]);
void alteraEstado (int cont, struct list dados[]);
void apresentaResumo (int cont, struct list dados[]);
void recomendaAtividade(struct list dados[], int cont);
void incluirTXT (int cont, struct list dadosCrud[]);
void incluirBIN (int cont, struct list dadosCrud[]);
void gerarExcel(struct list dadosCrud[], int cont);
void listarArqTXT(struct list dadosCrud[], int cont, struct listArq dadosArq[]);
//===============================================================================================

//MENU
int leValidaOpcMenu() {
	int opc;
	printf ("\t\t\t-------TO DO LIST-------\n");
	printf ("\t\t\t1 - Adicionar Atividade\n");
	printf ("\t\t\t2 - Listar Atividades\n");
	printf ("\t\t\t3 - Alterar Estado de Atividade\n");
	printf ("\t\t\t4 - Apresenta Resumo\n");
	printf ("\t\t\t5 - Gravar Atividades em Arquivo\n");
	printf ("\t\t\t6 - Gerar Excel\n");
	printf ("\t\t\t7 - Listar Atividades do Arquivo\n");
	printf ("\t\t\t0 - Finalizar\n");
	do {
		printf ("\t\t\tDigite a opção de escolha: ");
		scanf ("%d", &opc);
		if (opc<0||opc>7) {
			printf ("\t\t\tOpção inválida!\n");
		}
	}	while (opc<0||opc>7);
	return opc;
}
//==========================================================================================

//ADICIONAR ATIVIDADE
char leValidaOpcCase() {
	char opc;
	do {
		printf ("Pressione 's' para nova atividade ou 'm' para voltar ao menu: ");
		opc = getche();
		opc = tolower (opc);
		if (opc!='s'&&opc!='m') {
			printf ("\nOpção inválida!\n");
		}
	} while (opc!='s'&&opc!='m');
	return opc;
}

char leValidaOpcCase2() {
	char opc;
	do {
		printf ("Pressione 'm' para voltar ao menu: ");
		opc = getche();
		opc = tolower (opc);
		if (opc!='m') {
			printf ("\nOpção inválida!\n");
		}
	} while (opc!='m');
	return opc;
}

int leValidaOpcCase3() {
	int opc;
	do {
		printf ("\t\t\t1 - ARQUIVO EM TXT\n");
		printf ("\t\t\t2 - ARQUIVO EM BIN\n\n");
		printf ("Informe o tipo de arquivo que deseja gerar: ");
		scanf ("%d", &opc);
		if (opc!=1&&opc!=2) {
			printf ("Opção inválida!\n");
		}
	} while (opc!=1&&opc!=2);
	return opc;
}

int leValidaID() {
	int id;
	do {
		printf ("Digite um código para esta atividade (permitido código até 100): ");
		scanf ("%d", &id);
		if (id>100||id<=0) {
			printf ("Código inválido!\n");
		}
	}	while (id>100||id<=0);
	return id;
}

int validaID(struct list dados[], int cont) {
	int i, flag=0;
	for (i=1; i<=cont; i++) {
		if (dados[i].id==dados[i-1].id) {
			printf ("Código já existente.\n");
			flag=1;
		}
	}
	return flag;
}

int leValidaDia() {
	int dia;
	do {
		printf ("Digite o dia (máximo até 31): ");
		scanf ("%d", &dia);
		if (dia>31||dia<=0) {
			printf ("Dia inválido!\n");
		}
	} while (dia>31||dia<=0);
	return dia;
}

int leValidaMes() {
	int mes;
	do {
		printf ("Digite o mês (máximo até 12): ");
		scanf ("%d", &mes);
		if (mes>12||mes<=0) {
			printf ("Mês inválido!\n");
		}
	} while (mes>12||mes<=0);
	return mes;
}

float leValidaNota() {
	float nota;
	do {
		printf ("Digite a pontuação dessa atividade: ");
		scanf ("%f", &nota);
		if (nota>10||nota<0) {
			printf ("Pontuação inválida!\n");
		}
	} while (nota>10||nota<0);
	return nota;
}

void leValidaDescr(char *descr) {
	do {
		printf ("Digite uma descrição para essa atividade: ");
		fflush(stdin);
		gets (descr);
		if (strcmp(descr,"")==0) {
			printf ("Descrição inválida!\n");
		}
	} while (strcmp(descr,"")==0);
}

void leValidaMat(char *materia) {
	do {
		printf ("Digite a disciplina dessa atividade: ");
		fflush(stdin);
		gets (materia);
		if (strcmp(materia,"")==0) {
			printf ("Disciplina inválida!\n");
		}
	} while (strcmp(materia,"")==0);
}

int validaData(struct list dados[], int cont) {
	int i, flag=0;
	for (i=0; i<=cont; i++) {
		if ((dados[i].dia>30&&dados[i].mes==4)||(dados[i].dia>30&&dados[i].mes==6)||(dados[i].dia>30&&dados[i].mes==9)||(dados[i].dia>30&&dados[i].mes==11)) {
			printf ("Data inválida!\n");
			flag=1;
		} else 	if (dados[i].dia>29&&dados[i].mes==2) {
			printf ("Data inválida!\n");
			flag=1;
		}
	}
	return flag;
}
//==================================================================================================

//LISTAR ATIVIDADES
void listarAtividades (int cont, struct list dadosCrud[]) {
	int cod, i, flag=0;
	printf ("Digite o código da atividade para uma pesquisa específica ou digite '0' para listar todas: ");
	scanf ("%d", &cod);
	for (i=0; i<cont; i++) {
		if (cod==dadosCrud[i].id) {
			printf ("========================================================================================\n");
			printf ("Código da atividade: %d\n", dadosCrud[i].id);
			printf ("Descrição da ativid0ade: %s\n", dadosCrud[i].descr);
			printf ("Disciplina da atividade: %s\n", dadosCrud[i].materia);
			printf ("Data de entrega da atividade: %d/%d/%d\n", dadosCrud[i].dia, dadosCrud[i].mes, dadosCrud[i].ano);
			printf ("Pontuação da atividade: %.2f\n", dadosCrud[i].nota);
			if (dadosCrud[i].progresso==0) {
				printf ("Estado da atividade: Não iniciada.\n");
			} else if (dadosCrud[i].progresso==1) {
				printf ("Estado da atividade: Iniciada.\n");
			} else {
				printf ("Estado da atividade: Finalizada.\n");
			}
			printf ("========================================================================================\n");
			flag=1;
		} else if (cod==0) {
			printf ("========================================================================================\n");
			printf ("Código da atividade: %d\n", dadosCrud[i].id);
			printf ("Descrição da atividade: %s\n", dadosCrud[i].descr);
			printf ("Disciplina da atividade: %s\n", dadosCrud[i].materia);
			printf ("Data de entrega da atividade: %d/%d/%d\n", dadosCrud[i].dia, dadosCrud[i].mes, dadosCrud[i].ano);
			printf ("Pontuação da atividade: %.2f\n", dadosCrud[i].nota);
			if (dadosCrud[i].progresso==0) {
				printf ("Estado da atividade: Não iniciada.\n");
			} else if (dadosCrud[i].progresso==1) {
				printf ("Estado da atividade: Iniciada.\n");
			} else {
				printf ("Estado da atividade: Finalizada.\n");
			}
			printf ("========================================================================================\n");
			flag=1;
		}
	}

	if (flag==0) {
		printf ("Código não encontrado ou nenhuma atividade cadastrada!\n");
	}
}
//==================================================================================================

//FUNÇÃO ESPECÍFICA DO CONTEXTO DE DADOS
void alteraEstado (int cont, struct list dados[]) {
	int cod, i, atv, flag=0;
	printf ("Digite o código da atividade que deseja alterar o estado: ");
	scanf ("%d", &cod);
	for (i=0; i<cont; i++) {
		if (cod==dados[i].id) {
			printf ("Digite '1' para 'Atividade iniciada.' ou '2' para 'Atividade finalizada.': ");
			scanf ("%d", &atv);
			switch (atv) {
				case 1:
					dados[i].progresso=1;
					printf ("Estado da atividade %d alterado para 'Atividade iniciada.\n'", dados[i].id);
					flag=1;
					break;
				case 2:
					dados[i].progresso=2;
					printf ("Estado da atividade %d alterado para 'Atividade finalizada.\n'", dados[i].id);
					flag=1;
					break;
			}
		}
	}
	if (flag==0) {
		printf ("Código não encontrado!\n");
	}
}

void apresentaResumo (int cont, struct list dados[]) {
	int i, contNI=0, contIn=0, contFi=0;
	for (i=0; i<cont; i++) {
		if (dados[i].progresso==0) {
			contNI++;
		} else if (dados[i].progresso==1) {
			contIn++;
		} else {
			contFi++;
		}
	}

	printf ("Você possui %d atividades não iniciadas, %d atividades iniciadas e %d atividades finalizadas.\n", contNI, contIn, contFi);
}

void recomendaAtividade(struct list dados[], int cont) {
	int dia, mes, ano=2020, i, cod, menorMes, menorDia, flag=0;
	menorDia=dados[0].dia;
	menorMes=dados[0].mes;
	cod=0;
	for (i=1; i<cont; i++) {
		if (dados[i].dia<=menorDia) {
			menorDia=dados[i].dia;
			cod=i;
		}
	}
	for (i=1; i<cont; i++) {
		if (dados[i].mes<=menorMes) {
			menorMes=dados[i].mes;
			cod=i;
		}
	}

	for (i=0; i<cont; i++) {
		if (dados[cod].progresso==0) {
			flag=1;
		}
	}

	if (flag==1) {
		printf ("Recomenda-se iniciar a Atividade %d, pois sua data de entrega está mais próxima (%d/%d/%d).\n", dados[cod].id, menorDia, menorMes, ano);
	}
}
//==================================================================================================

//FUNÇÕES REFERENTE AOS ARQUIVOS
void incluirTXT (int cont, struct list dadosCrud[]) {
	FILE *arq;
	int i;
	arq = fopen("IncluirTXT.txt", "w");
	if (arq==NULL) {
		printf ("Erro ao criar o arquivo\n");
		exit (1);
	} else {
		printf ("Arquivo em TXT criado com sucesso\n");
	}
	for (i=0; i<cont; i++) {
		//fprintf (arq, "========================================================================================\n");
		fprintf (arq, "%d\n", dadosCrud[i].id);
		fprintf (arq, "%s\n", dadosCrud[i].descr);
		fprintf (arq, "%s\n", dadosCrud[i].materia);
		//fprintf (arqExcel, "Data de entrega da atividade: %d/%d/%d\n", dadosCrud[cont-1].dia, dadosCrud[i].mes, dadosCrud[i].ano); DÚVIDA: COMO ELE CONSEGUE PEGAR A DATA CORRETA SE "i" não foi definido com nenhum valor?
		fprintf (arq, "%d %d %d\n", dadosCrud[i].dia, dadosCrud[i].mes, dadosCrud[i].ano);
		fprintf (arq, "%.2f\n", dadosCrud[i].nota);
		fprintf (arq, "%d\n", dadosCrud[i].progresso);
		fprintf (arq, "\n");
		//fprintf (arq, "========================================================================================\n");
	}
	fclose(arq);
}

void incluirBIN (int cont, struct list dadosCrud[]) {
	FILE *arq;
	arq = fopen("IncluirBIN.bin", "ab");
	if (arq==NULL) {
		printf ("Erro ao criar o arquivo\n");
		exit (1);
	} else {
		printf ("Arquivo em BIN criado com sucesso\n");
	}
	fwrite(&dadosCrud, sizeof(dadosCrud), 1, arq);
	fclose (arq);
}

void gerarExcel(struct list dadosCrud[], int cont) {
	FILE *arq, *arqExcel;
	int i;
	arq = fopen("IncluirBIN.bin", "rb");
	arqExcel = fopen("IncluirBIN.csv", "w");
	for (i=0; i<cont; i++) {
		fread(&dadosCrud, sizeof(dadosCrud),1, arq);
		fprintf (arqExcel, "Código da atividade: %d\n", dadosCrud[i].id);
		fprintf (arqExcel, "Descrição da atividade: %s\n", dadosCrud[i].descr);
		fprintf (arqExcel, "Disciplina da atividade: %s\n", dadosCrud[i].materia);
		//fprintf (arqExcel, "Data de entrega da atividade: %d/%d/%d\n", dadosCrud[cont-1].dia, dadosCrud[i].mes, dadosCrud[i].ano); DÚVIDA: COMO ELE CONSEGUE PEGAR A DATA CORRETA SE "i" não foi definido com nenhum valor?
		fprintf (arqExcel, "Data de entrega da atividade: %d/%d/%d\n", dadosCrud[i].dia, dadosCrud[i].mes, dadosCrud[i].ano);
		fprintf (arqExcel, "Pontuação da atividade: %.2f\n", dadosCrud[i].nota);
		if (dadosCrud[i].progresso==0) {
			fprintf (arqExcel, "Estado da atividade: Não iniciada.\n");
		} else if (dadosCrud[i].progresso==1) {
			fprintf (arqExcel, "Estado da atividade: Iniciada.\n");
		} else {
			fprintf (arqExcel, "Estado da atividade: Finalizada.\n");
		}
	}
	fclose(arq);
	fclose (arqExcel);
	system ("IncluirBIN.csv");
}

void listarArqTXT(struct list dadosCrud[], int cont, struct listArq dadosArq[]) {
	FILE *arq;
	int i=0, cod, flag=0;
	char textoArq[15];
	arq = fopen("IncluirTXT.txt", "r");
	if (arq==NULL) {
		printf ("Erro ao criar o arquivo\n");
		exit(1);
	}
	for (i=0; i<cont; i++) {
			fscanf (arq, "%d\n", &dadosArq[i].idArq);
			fgets (dadosArq[i].descrArq, 98, arq);
			fgets (dadosArq[i].materiaArq, 98, arq);
			fscanf (arq, "%d %d %d\n", &dadosArq[i].diaArq, &dadosArq[i].mesArq, &dadosArq[i].anoArq);
			fscanf (arq, "%f", &dadosArq[i].notaArq);
			fscanf (arq, "%d", &dadosArq[i].progressoArq);
	}
	fclose(arq);
	
	printf ("Digite o código da atividade para uma pesquisa específica ou digite '0' para listar todas: ");
	scanf ("%d", &cod);
	for (i=0; i<cont; i++) {
		if (cod==dadosArq[i].idArq) {
			printf ("========================================================================================\n");
			printf ("Código da atividade: %d\n", dadosArq[i].idArq);
			printf ("Descrição da atividade: %s", dadosArq[i].descrArq);
			printf ("Disciplina da atividade: %s", dadosArq[i].materiaArq);
			printf ("Data de entrega da atividade: %d/%d/%d\n", dadosArq[i].diaArq, dadosArq[i].mesArq, dadosArq[i].anoArq);
			printf ("Nota da atividade: %.2f\n", dadosArq[i].notaArq);
			if (dadosArq[i].progressoArq==0) {
				printf ("Estado da atividade: Não iniciada.\n");
			} else if (dadosArq[i].progressoArq==1) {
				printf ("Estado da atividade: Iniciada.\n");
			} else {
				printf ("Estado da atividade: Finalizada.\n");
			}
			printf ("========================================================================================\n");
			flag=1;
		} else if (cod==0) {
			printf ("========================================================================================\n");
			printf ("Código da atividade: %d\n", dadosArq[i].idArq);
			printf ("Descrição da atividade: %s", dadosArq[i].descrArq);
			printf ("Disciplina da atividade: %s", dadosArq[i].materiaArq);
			printf ("Data de entrega da atividade: %d/%d/%d\n", dadosArq[i].diaArq, dadosArq[i].mesArq, dadosArq[i].anoArq);
			printf ("Nota da atividade: %.2f\n", dadosArq[i].notaArq);
			if (dadosArq[i].progressoArq==0) {
				printf ("Estado da atividade: Não iniciada.\n");
			} else if (dadosArq[i].progressoArq==1) {
				printf ("Estado da atividade: Iniciada.\n");
			} else {
				printf ("Estado da atividade: Finalizada.\n");
			}
			printf ("========================================================================================\n");
			flag=1;
		}
	}
	if (flag==0) {
		printf ("Código não encontrado ou nenhuma atividade cadastrada no arquivo!\n");
	}
}
//=========================================================================================================================================================================================

//PRINCIPAL
main () {
	setlocale(LC_ALL, "");
	struct list dados[5];
	struct listArq dadosArq[5];
	int escMenu, cont=0, flag=0, escArq;
	char escCase;
	do {
		system ("cls");
		escMenu=leValidaOpcMenu();
		switch (escMenu) {
			case 1:
				do {
					system("cls");
					printf ("\t\t\tADICIONAR ATIVIDADE\n\n");
					do {
						dados[cont].id=leValidaID();
						if (cont>0) {
							flag = validaID(dados, cont);
						}
					} while (flag==1);
					leValidaDescr(dados[cont].descr);
					leValidaMat(dados[cont].materia);
					printf ("Digite a data de entrega: \n");
					do {
						dados[cont].dia=leValidaDia();
						dados[cont].mes=leValidaMes();
						flag= validaData(dados, cont);
					} while (flag==1);
					dados[cont].ano=2020;
					dados[cont].nota=leValidaNota();
					dados[cont].progresso=0;
					escCase = leValidaOpcCase();
					cont++;
				} while (escCase=='s'&&cont<5);
				break;
			case 2:
				do {
					system ("cls");
					printf ("\t\t\tLISTAR ATIVIDADES\n\n");
					listarAtividades (cont, dados);
					escCase = leValidaOpcCase();
				} while (escCase=='s');
				break;
			case 3:
				do {
					system ("cls");
					printf ("\t\t\tALTERAR ESTADO DE ATIVIDADE\n\n");
					alteraEstado (cont, dados);
					escCase = leValidaOpcCase();
				} while (escCase=='s');
				break;
			case 4:
				do {
					system ("cls");
					printf ("\t\t\tAPRESENTA RESUMO\n\n");
					apresentaResumo (cont, dados);
					if (cont>0) {
						recomendaAtividade(dados, cont);
					}
					escCase = leValidaOpcCase2();
				} while (escCase!='m');
				break;
			case 5:
				do {
					system ("cls");
					printf ("\t\t\tGERAÇÃO DE ARQUIVOS\n\n");
					escArq = leValidaOpcCase3();
					if (escArq==1) {
						incluirTXT (cont, dados);
					} else {
						incluirBIN (cont, dados);
					}
					escCase = leValidaOpcCase2();
				} while (escCase!='m');
				break;
			case 6:
				do {
					system ("cls");
					printf ("\t\t\tGERAR TABELA NO EXCEL\n\n");
					gerarExcel(dados, cont);
					printf ("Tabela gerada com sucesso.\n");
					escCase = leValidaOpcCase2();
				} while (escCase!='m');
				break;
			case 7:
				do {
					system ("cls");
					printf ("\t\t\tLISTAR ATIVIDADES DO ARQUIVO TXT\n\n");
					listarArqTXT(dados, cont, dadosArq);
					escCase = leValidaOpcCase();
				} while (escCase=='s');
				break;
		}
	} while (escCase=='m'&&escMenu!=0);
}
