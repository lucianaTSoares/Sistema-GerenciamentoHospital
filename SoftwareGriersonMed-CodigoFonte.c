#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_LOGIN 20 
#define MAX_SENHA 10

void TelaLogin(void){
    int opLogin;
    char cLogin[MAX_LOGIN],cSenha[MAX_SENHA];
    char login[MAX_LOGIN], senha[MAX_SENHA];
    int l=0,s=0;
    FILE *arquivoLog; //FILE referente � login e senha

    setlocale(LC_ALL, "Portuguese"); //Comando para que os caracteres especiais usados em pt-BR sejam leg�veis no decorrer das telas do programa. *Funciona apenas com a biblioteca locale.h

    do{
        printf("\n\t\t\t--TELA DE LOGIN--\n"); //Menu da tela de login
        printf("\nBem-vindo(a)!\nEscolha um item e seu numero correspondente para prosseguir.\n\n");
        printf("\n1- Login");
        printf("\n2- Cadastro de Usu�rio");
        printf("\n3- Finalizar o programa");
        printf("\n\nN�mero: ");
        scanf("%i",&opLogin);

        system("cls");

        switch(opLogin){
            case 1: //Login

                printf("* OBS: Usu�rio e Senha n�o devem possuir caracteres especiais e/ou espa�os! * \n");
                printf("\nUsu�rio: ");
                setbuf(stdin,NULL); //Limpar o buffer do teclado.
                gets(login);

                printf("Senha: ");
                setbuf(stdin,NULL);
                gets(senha);

                arquivoLog = fopen("login.txt","r");

                if (arquivoLog==NULL){ //Verifica��o se o arquivo "login.txt" existe para ocorrer a leitura de dados.
                    printf("\nN�o foi possivel abrir o arquivo.\n\nFINALIZANDO O PROGRAMA...\n");
                    getch();
                    exit(0);
                }

                while(fscanf(arquivoLog,"%s",cLogin)!=EOF){ /*Valida��o do login: � feito um fscanf em login.txt � procura da variavel cLogin
                                                           Caso o valor retorne 0 (significando que os valores de cLogin e login s�o iguais), a variavel 'l' ganhar� valor 1.*/
                    if(strcmp(cLogin,login) == 0){
                        l=1;
                    }
                }
                fclose(arquivoLog);

                arquivoLog = fopen("login.txt","r");

                while(fscanf(arquivoLog,"%s",cSenha)!=EOF){ /*Valida��o da senha. � feito um fscanf em login.txt � procura da variavel cSenha
                                                           Caso o valor retorne 0 (significando que os valores de cSenha e senha s�o iguais), a variavel 's' ganhar� valor. 1*/
                    if(strcmp(cSenha,senha) == 0){
                        s=1;
                    }
                }
                fclose(arquivoLog);

                if(l==1&&s==1){ //O acesso � conta ser� concedido caso l=1 e s=1.
                    system("cls");
                    return; //Comando para retornar � fun��o main.
                }

                else{
                    printf("\n--ACESSO NEGADO. USU�RIO E/OU SENHA INCORRETOS--\n");
                    printf("\nPressione qualquer tecla para retornar � tela de Login...");

                    getch();
                    system("cls");
                }
                break;

            case 2: //Cadastro de login e senha, para poder ser feito o login no aplicativo.

                printf("\n\t\t--CRIAR CONTA--\n");
                printf("\n* OBS: Usu�rio e Senha n�o devem possuir caracteres especiais e/ou espa�os! * \n");
                printf("\nUsu�rio (*at� 20 caracteres): ");
                setbuf(stdin,NULL);
                gets(cLogin);

                printf("Senha (*at� 10 caracteres): ");
                setbuf(stdin,NULL);
                gets(cSenha);

                arquivoLog = fopen("login.txt","a");
                fprintf(arquivoLog,"%s %s\n", cLogin, cSenha); //Armazenamento dos dados de login e senha cadastrados no arquivo login.txt.

                fclose(arquivoLog);

                printf("\nPressione qualquer tecla para retornar � tela de Login...");

                getch();
                system("cls");
                break;

            case 3: //Finaliza��o do programa.
                printf("\nFINALIZANDO O PROGRAMA...\n");
                exit(0);
                break;

            default: printf("Tente novamente. Digite os n�meros 1, 2 ou 3.\n"); //Caso o usu�rio n�o digite um desses 3 n�meros, essa mensagem aparecer� para o usu�rio.
        }
    }while(opLogin!=0); //Enquanto o usu�rio digitar um n�mero diferente de 0, haver� retorno para o menu principal da tela de login
    return;
}

void TelaRelatorio(void){
    int op_menu, op_cadastro, op_consulta,op_findiaria1,op_finmensal1,op_findiaria2,op_finmensal2;
    int dia, mes, ano;
    int numConsulta,valConsulta;
    int numPacientes1=0,total_pacientes1=0,numPacientes2=0,total_pacientes2=0,numPacientes3=0,total_pacientes3=0,unidP,consUnidP;
    int numAtendimentos1=0,total_Atendimentos1=0,numAtendimentos2=0,total_Atendimentos2=0,numAtendimentos3=0,total_Atendimentos3=0,unidA;
    float faturamento1,faturamento2,faturamento3, faturamento_total;

    FILE *arquivo; //FILE referente � Unidade 1
    FILE *arquivo2; //FILE referente � Unidade 2
    FILE *arquivo3; //FILE referente � Unidade 3

    setlocale(LC_ALL, "Portuguese"); //Comando para que os caracteres especiais usados em pt-BR sejam leg�veis no decorrer das telas do programa. *Funciona apenas com a biblioteca locale.h

    do{
        printf("\n\t\t--TELA DE RELAT�RIOS--\n"); //Menu da tela de Relat�rio.
        printf("\nEscolha uma op��o e seu n�mero correspondente para prosseguir\n");
        printf("\n1- Criar relat�rios");
        printf("\n2- Consultar relat�rios");
        printf("\n3- Voltar para a Tela de Menu");
        printf("\n4- Sair do programa");
        printf("\n\nN�mero: ");
        setbuf(stdin,NULL);

        scanf("%i",&op_menu);
        system("cls");

        switch(op_menu){
            case 1: //Menu para escolhe de cria��o de tipos de relat�rios.
                printf("Escolha um n�mero correspondente ao que deseja criar\n");
                printf("\n1- Faturamento total di�rio por Unidade");
                printf("\n2- Faturamento total mensal por Unidade");
                printf("\n3- Pacientes por Unidade");
                printf("\n4- Atendimentos por Unidade");
                printf("\n*Pressione qualquer outro n�mero diferente de 0 para voltar."); //Qualquer n�mero diferente de 0 redireciona o usu�rio para a tela principal de relat�rios
                printf("\n\nN�mero: ");
                setbuf(stdin,NULL);

                scanf("%i",&op_cadastro);

                system("cls");

                switch(op_cadastro){ 
                    case 1: //Faturamento total di�rio por Unidade/Total da rede (Cadastro)
                        printf("Escolha um n�mero correspondente �s Unidades: \n");
                        printf("\n1- Unidade I");
                        printf("\n2- Unidade II");
                        printf("\n3- Unidade III");
                        printf("\n*Pressione qualquer outro n�mero diferente de 0 para voltar .");
                        printf("\n\nNumero: ");
                        setbuf(stdin,NULL);

                        scanf("%i",&op_findiaria1);
                        system("cls");

                        switch(op_findiaria1){ 
                            case 1: //Faturamento total di�rio para a Unidade I (Cadastro)
                                printf("\nData de cria��o do relat�rio");
                                printf("\nDia: ");
                                scanf("%i",&dia);
                                printf("\nM�s: ");
                                scanf("%i",&mes);
                                printf("\nAno: ");
                                scanf("%i",&ano);
                                setbuf(stdin,NULL);

                                printf("\nN�mero de consultas di�rias: ");
                                setbuf(stdin,NULL);
                                scanf("%i",&numConsulta);

                                printf("\nValor total das consultas: R$");
                                setbuf(stdin,NULL);
                                scanf("%i",&valConsulta);

                                faturamento1= numConsulta*valConsulta; //Calculo para faturamento di�rio da unid 1.

                                printf("\n\nFATURAMENTO DI�RIO - UNIDADE I: R$%5.2f",faturamento1);
                                printf("\n\n");

                                arquivo = fopen("FaturamentoDiarioUnid1.txt","w");

                                if (arquivo==NULL){ //Verifica��o se o arquivo existe para ocorrer a escrita de dados.
                                    printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                    getch();
                                    return;
                                }

                                fprintf(arquivo, "%i %i %i %i %i %f\n",dia, mes, ano, numConsulta, valConsulta, faturamento1); //Escrita dos dados no arquivo texto da unid 1.

                                fclose(arquivo);

                                system("pause");
                                system("cls");
                                break; 

                            case 2: //Faturamento total di�rio para a Unidade II (Cadastro)
                                printf("\nData de cria��o ");
                                printf("\nDia: ");
                                scanf("%i",&dia);
                                printf("\nM�s: ");
                                scanf("%i",&mes);
                                printf("\nAno: ");
                                scanf("%i",&ano);
                                setbuf(stdin,NULL);

                                printf("\nN�mero de consultas di�rias: ");
                                setbuf(stdin,NULL);
                                scanf("%i",&numConsulta);

                                printf("\nValor total das consultas: R$");
                                setbuf(stdin,NULL);
                                scanf("%i",&valConsulta);

                                faturamento2= numConsulta*valConsulta; //Calculo para faturamento di�rio da unid 2.

                                printf("\n\nFATURAMENTO DI�RIO - UNIDADE II: R$%5.2f",faturamento2);
                                printf("\n\n");

                                arquivo2 = fopen("FaturamentoDiarioUnid2.txt","w");

                                if (arquivo2==NULL){ //Verifica��o se o arquivo existe para ocorrer a escrita de dados.
                                    printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                    getch();
                                    return;
                                }
                                fprintf(arquivo2, "%i %i %i %i %i %f\n",dia, mes, ano, numConsulta, valConsulta, faturamento2); //Escrita dos dados no arquivo texto da unid 2.

                                fclose(arquivo2);

                                system("pause");
                                system("cls");
                                break; //Unidade II (Cadastro)

                            case 3: //Faturamento total di�rio para a Unidade III (Cadastro)
                                printf("\nData de cria��o ");
                                printf("\nDia: ");
                                scanf("%i",&dia);
                                printf("\nM�s: ");
                                scanf("%i",&mes);
                                printf("\nAno: ");
                                scanf("%i",&ano);
                                setbuf(stdin,NULL);

                                printf("\nNumero de consultas di�rias: R$");
                                setbuf(stdin,NULL);
                                scanf("%i",&numConsulta);

                                printf("\nValor total das consultas: R$");
                                setbuf(stdin,NULL);
                                scanf("%i",&valConsulta);

                                faturamento3= numConsulta*valConsulta; //Calculo para faturamento di�rio da unid 3.

                                printf("\n\nFATURAMENTO DI�RIO - UNIDADE III: R$%5.2f",faturamento3);
                                printf("\n\n");

                                arquivo3 = fopen("FaturamentoDiarioUnid3.txt","w");

                                if (arquivo3==NULL){ //Verifica��o se o arquivo existe para ocorrer a escrita de dados.
                                    printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                    getch();
                                    return;
                                }
                                fprintf(arquivo3, "%i %i %i %i %i %f\n",dia, mes, ano, numConsulta, valConsulta, faturamento3); //Escrita dos dados no arquivo texto da unid 3.

                                fclose(arquivo3);

                                system("pause");
                                system("cls");
                                break; //Unidade III (Cadastro)

                            }
                        break; 


                    case 2: //Faturamento total mensal por unidade/Total da rede (Cadastro)
                        printf("Escolha um n�mero correspondente �s Unidades: \n");
                        printf("\n1- Unidade I");
                        printf("\n2- Unidade II");
                        printf("\n3- Unidade III");
                        printf("\n*Pressione qualquer outro n�mero diferente de 0 para voltar.");
                        printf("\n\nNumero: ");
                        setbuf(stdin,NULL);

                        scanf("%i",&op_finmensal1);
                        system("cls");

                        switch(op_finmensal1){
                            case 1: //Faturamento total mensal para a Unidade I (CADASTRO)
                                printf("\nData de cria��o do relat�rio");
                                printf("\nM�s: ");
                                scanf("%i",&mes);
                                printf("\nAno: ");
                                scanf("%i",&ano);
                                setbuf(stdin,NULL);

                                printf("\nN�mero de consultas mensais: ");
                                setbuf(stdin,NULL);
                                scanf("%i",&numConsulta);

                                printf("\nValor total das consultas no m�s: R$");
                                setbuf(stdin,NULL);
                                scanf("%i",&valConsulta);

                                faturamento1= numConsulta*valConsulta; //Calculo para faturamento mensal da unid 1.

                                printf("\n\nFATURAMENTO MENSAL - UNIDADE I: R$%5.2f",faturamento1);
                                printf("\n\n");

                                arquivo = fopen("FaturamentoMensalUnid1.txt","w");

                                if (arquivo==NULL){ //Verifica��o se o arquivo existe para ocorrer a escrita de dados.
                                    printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                    getch();
                                    return;
                                }
                                fprintf(arquivo, "%i %i %i %i %f\n",mes, ano, numConsulta, valConsulta, faturamento1); //Escrita dos dados no arquivo texto da unid 1.

                                fclose(arquivo);
                                system("pause");
                                system("cls");
                                break; //Unidade I MENSAL (CADASTRO)

                            case 2: //Faturamento total mensal para a Unidade II (CADASTRO)
                                printf("\nData de cria��o do relat�rio");
                                printf("\nM�s: ");
                                scanf("%i",&mes);
                                printf("\nAno: ");
                                scanf("%i",&ano);
                                setbuf(stdin,NULL);

                                printf("\nN�mero de consultas mensais: ");
                                setbuf(stdin,NULL);
                                scanf("%i",&numConsulta);

                                printf("\nValor total das consultas no m�s: R$");
                                setbuf(stdin,NULL);
                                scanf("%i",&valConsulta);

                                faturamento2= numConsulta*valConsulta; //Calculo para faturamento mensal da unid 2.

                                printf("\n\nFATURAMENTO MENSAL - UNIDADE II: R$%5.2f",faturamento2);
                                printf("\n\n");

                                arquivo2 = fopen("FaturamentoMensalUnid2.txt","w");

                                if (arquivo2==NULL){ //Verifica��o se o arquivo existe para ocorrer a escrita de dados.
                                    printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                    getch();
                                    return;
                                }

                                fprintf(arquivo2, "%i %i %i %i %f\n",mes, ano, numConsulta, valConsulta, faturamento2); //Escrita dos dados no arquivo texto da unid 2.

                                fclose(arquivo2);
                                system("pause");
                                system("cls");
                                break; //Unidade II MENSAL (CADASTRO)

                            case 3: //Faturamento total mensal para a Unidade III (CADASTRO)
                                printf("\nData de cria��o do relat�rio");
                                printf("\nM�s: ");
                                scanf("%i",&mes);
                                printf("\nAno: ");
                                scanf("%i",&ano);
                                setbuf(stdin,NULL);

                                printf("\nN�mero de consultas mensais: ");
                                setbuf(stdin,NULL);
                                scanf("%i",&numConsulta);

                                printf("\nValor total das consultas no m�s: R$");
                                setbuf(stdin,NULL);
                                scanf("%i",&valConsulta);

                                faturamento3= numConsulta*valConsulta; //Calculo para faturamento mensal da unid 3.

                                printf("\n\nFATURAMENTO MENSAL - UNIDADE III: R$%5.2f",faturamento3);
                                printf("\n\n");

                                arquivo3 = fopen("FaturamentoMensalUnid3.txt", "w");

                                if (arquivo3==NULL){ //Verifica��o se o arquivo existe para ocorrer a escrita de dados.
                                    printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                    getch();
                                    return;
                                }
                                fprintf(arquivo3, "%i %i %i %i %f\n",mes, ano, numConsulta, valConsulta, faturamento3); //Escrita dos dados no arquivo texto da unid 3.

                                fclose(arquivo3);
                                system("pause");
                                system("cls");
                                break; //Unidade III MENSAL (CADASTRO)
                        }
                        break; //Faturamento total mensal por unidade/Total da rede (Cadastro)

                    case 3: //Pacientes por Unidade
                        printf("Insira a Unidade (1, 2 ou 3): ");
                        scanf("%i",&unidP);
						
						//Comando if/else para dar valor �s vari�veis, de acordo com a Unidade da cl�nica
                        if(unidP==1){
                            printf("\nInsira a quantidade de Pacientes: ");
                            scanf("%i",&numPacientes1);

                            total_pacientes1=total_pacientes1+numPacientes1; //Calculo para relat�rio de quantidade de pacientes
                        }

                        else
							if(unidP==2){
	                           	printf("\nInsira a quantidade de Pacientes: ");
	                            scanf("%i",&numPacientes2);
	
	                            total_pacientes2=total_pacientes2+numPacientes2;
                        	}
							else
                        		if(unidP==3){
		                            printf("\nInsira a quantidade de Pacientes: ");
		                            scanf("%i",&numPacientes3);

                            		total_pacientes3=total_pacientes3+numPacientes3;
                       			}

                        printf("\n\n");
                        system("pause");
                        system("cls");
                        break;

                    case 4: //Atendimentos por Unidade
                        printf("Insira a Unidade (1, 2 ou 3): ");
                        scanf("%i",&unidA);
						
						//Comando if/else para dar valor �s vari�veis, de acordo com a Unidade da cl�nica
                        if(unidA==1){
                            printf("\nInsira a quantidade de Atendimentos: ");
                            scanf("%i",&numAtendimentos1);

                            total_Atendimentos1=total_Atendimentos1+numAtendimentos1; //Calculo para relat�rio de quantidade de atendimentos
                        }

                        if(unidA==2){
                            printf("\nInsira a quantidade de Atendimentos: ");
                            scanf("%i",&numAtendimentos2);

                            total_Atendimentos2=total_Atendimentos2+numAtendimentos2;
                        }

                        if(unidA==3){
                            printf("\nInsira a quantidade de Atendimentos: ");
                            scanf("%i",&numAtendimentos3);

                            total_Atendimentos3=total_Atendimentos3+numAtendimentos3;
                        }
                        printf("\n\n");
                        system("pause");
                        system("cls");
                        break;

                }
                break;

            case 2: //Consultar relat�rios (Menu)
                printf("Escolha um n�mero correspondente ao que deseja consultar\n");
                printf("\n1- Faturamento total di�rio por Unidade/Total da rede");
                printf("\n2- Faturamento total mensal por Unidade/Total da rede");
                printf("\n3- Pacientes por Unidade");
                printf("\n4- Unidade que mais atende");
                printf("\n*Pressione qualquer outro n�mero diferente de 0 para voltar.");
                printf("\n\nN�mero: ");
                setbuf(stdin,NULL);

                scanf("%i",&op_consulta);
                system("cls");

                switch(op_consulta){

                case 1: //Faturamento total di�rio por Unidade/Total da rede (Consulta)
                    printf("Escolha um n�mero correspondente �s Unidades: \n");
                    printf("\n1- Unidade I");
                    printf("\n2- Unidade II");
                    printf("\n3- Unidade III");
                    printf("\n4- Todas as Undades");
                    printf("\n*Pressione qualquer outro n�mero diferente de 0 para voltar.");
                    printf("\n\nNumero: ");
                    setbuf(stdin,NULL);

                    scanf("%i",&op_findiaria2);
                    system("cls");

                    switch(op_findiaria2){
                        case 1: //Faturamento total di�rio para a Unidade I (CONSULTA)
                            arquivo = fopen("FaturamentoDiarioUnid1.txt","r");
							
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo==NULL){ 
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo)){
                                fscanf(arquivo,"%i %i %i %i %i %f ",&dia, &mes, &ano,&numConsulta, &valConsulta, &faturamento1);

                                printf("\nData de cria��o (dia-m�s-ano): %i-%i-%i",dia, mes, ano);
                                printf("\nN�mero de consultas di�rias: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\nFATURAMENTO DI�RIO - UNIDADE I: R$%5.2f",faturamento1);
                                printf("\n\n*****\n");
                            }
                            fclose(arquivo);
                            system("pause");
                            system("cls");
                            break; 

                        case 2: //Faturamento total di�rio para a Unidade II (CONSULTA)
                            arquivo2 = fopen("FaturamentoDiarioUnid2.txt","r");
							
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo2==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo2)){
                                fscanf(arquivo2,"%i %i %i %i %i %f ",&dia, &mes, &ano, &numConsulta, &valConsulta, &faturamento2);

                                printf("\nData de cria��o (dia-m�s-ano): %i-%i-%i",dia, mes, ano);
                                printf("\nN�mero de consultas di�rias: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\nFATURAMENTO DI�RIO - UNIDADE II: R$%5.2f",faturamento2);
                                printf("\n\n*****\n");
                            }
                            fclose(arquivo2);
                            system("pause");
                            system("cls");
                            break; 

                        case 3: //Faturamento total di�rio para a Unidade III (CONSULTA)
                            arquivo3 = fopen("FaturamentoDiarioUnid3.txt","r");
							
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo3==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo3)){
                                fscanf(arquivo3, "%i %i %i %i %i %f ",&dia, &mes, &ano, &numConsulta, &valConsulta, &faturamento3); 

                                printf("\nData de cria��o (dia-m�s-ano): %i-%i-%i",dia, mes, ano);
                                printf("\nN�mero de consultas di�rias: %i ",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\nFATURAMENTO DI�RIO - UNIDADE III: R$%5.2f",faturamento3);
                                printf("\n\n*****\n");
                            }
                            fclose(arquivo3);
                            system("pause");
                            system("cls");
                            break;

                        case 4: //Faturamento total di�rio para todas as Unidades (CONSULTA)
                            arquivo = fopen("FaturamentoDiarioUnid1.txt","r");
							
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo)){
                                fscanf(arquivo,"%i %i %i %i %i %f ",&dia, &mes, &ano,&numConsulta, &valConsulta, &faturamento1);

                                printf("\nData de cria��o (dia-m�s-ano): %i-%i-%i",dia, mes, ano);
                                printf("\nN�mero de consultas di�rias: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\n*** FATURAMENTO DI�RIO - UNIDADE I: R$%5.2f ***",faturamento1);
                                printf("\n\n----\n");
                            }
                            fclose(arquivo);

                            arquivo2 = fopen("FaturamentoDiarioUnid2.txt","r");
							
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo2==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo2)){
                                fscanf(arquivo2,"%i %i %i %i %i %f ",&dia, &mes, &ano,&numConsulta, &valConsulta, &faturamento2);

                                printf("\nData de cria��o (dia-m�s-ano): %i-%i-%i",dia, mes, ano);
                                printf("\nN�mero de consultas di�rias: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\n*** FATURAMENTO DI�RIO - UNIDADE II: R$%5.2f ***",faturamento2);
                                printf("\n\n----\n");
                            }
                            fclose(arquivo2);

                            arquivo3 = fopen("FaturamentoDiarioUnid3.txt","r");
							
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo3==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo3)){
                                fscanf(arquivo3,"%i %i %i %i %i %f ",&dia, &mes, &ano,&numConsulta, &valConsulta, &faturamento3);

                                printf("\nData de cria��o (dia-m�s-ano): %i-%i-%i",dia, mes, ano);
                                printf("\nN�mero de consultas di�rias: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\n*** FATURAMENTO DI�RIO - UNIDADE III: R$%5.2f ***",faturamento3);
                                printf("\n\n----\n");
                            }
                            fclose(arquivo3);
							//C�lculo de soma, para somar o faturamento di�rio das 3 Unidades
                            faturamento_total=faturamento1+faturamento2+faturamento3; 
                            printf("\n\n*** FATURAMENTO TOTAL DI�RIO DA REDE: R$%5.2f ***",faturamento_total);
                            printf("\n\n");

                            system("pause");
                            system("cls");
                            break; 

                    } 
                    break;

                case 2: // Faturamento total mensal por unidade/Total da rede (CONSULTA)
                    printf("Escolha um n�mero correspondente �s Unidades: \n");
                    printf("\n1- Unidade I");
                    printf("\n2- Unidade II");
                    printf("\n3- Unidade III");
                    printf("\n4- Todas as Undades");
                    printf("\n*Pressione qualquer outro n�mero diferente de 0 para voltar.");
                    printf("\n\nNumero: ");
                    setbuf(stdin,NULL);

                    scanf("%i",&op_finmensal2);
                    system("cls");

                    switch(op_finmensal2){
                        case 1: //Faturamento total mensal para a Unidade I (CONSULTA)
                            arquivo = fopen("FaturamentoMensalUnid1.txt","r");
							
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo)){
                                fscanf(arquivo,"%i %i %i %i %f ",&mes, &ano,&numConsulta, &valConsulta, &faturamento1);

                                printf("\nData de cria��o (m�s-ano): %i-%i", mes, ano);
                                printf("\nN�mero de consultas mensais: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\nFATURAMENTO MENSAL - UNIDADE I: R$%5.2f",faturamento1);
                                printf("\n\n*****\n");
                            }
                            fclose(arquivo);
                            system("pause");
                            system("cls");
                            break; 

                        case 2: //Faturamento total mensal para a Unidade II (CONSULTA)
                            arquivo2 = fopen("FaturamentoMensalUnid2.txt","r");
							
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo2==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo2)){
                                fscanf(arquivo2,"%i %i %i %i %f ",&mes, &ano,&numConsulta, &valConsulta, &faturamento2);

                                printf("\nData de cria��o (m�s-ano): %i-%i", mes, ano);
                                printf("\nN�mero de consultas mensais: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\nFATURAMENTO MENSAL - UNIDADE II: R$%5.2f",faturamento2);
                                printf("\n\n*****\n");
                            }
                            fclose(arquivo2);
                            system("pause");
                            system("cls");
                            break; 

                        case 3: //Faturamento total mensal para a Unidade III (CONSULTA)
                            arquivo3 = fopen("FaturamentoMensalUnid3.txt","r");
							
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo3==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo3)){
                                fscanf(arquivo3,"%i %i %i %i %f ",&mes, &ano,&numConsulta, &valConsulta, &faturamento3);

                                printf("\nData de cria��o (m�s-ano): %i-%i", mes, ano);
                                printf("\nN�mero de consultas mensais: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\nFATURAMENTO MENSAL - UNIDADE III: R$%5.2f",faturamento3);
                                printf("\n\n*****\n");
                            }
                            fclose(arquivo3);
                            system("pause");
                            system("cls");
                            break; 

                        case 4: //Faturamento total mensal para todas as Unidades (CONSULTA)
                            arquivo = fopen("FaturamentoMensalUnid1.txt","r");
							
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo)){
                                fscanf(arquivo,"%i %i %i %i %f ",&mes, &ano,&numConsulta, &valConsulta, &faturamento1);
                                printf("\nData de cria��o (m�s-ano): %i-%i",mes, ano);
                                printf("\nN�mero de consultas mensais: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\n*** FATURAMENTO MENSAL - UNIDADE I: R$%5.2f ***",faturamento1);
                                printf("\n\n----\n");
                            }
                            fclose(arquivo);

                            arquivo2 = fopen("FaturamentoMensalUnid2.txt","r");
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo2==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo2)){
                                fscanf(arquivo2,"%i %i %i %i %f ",&mes, &ano,&numConsulta, &valConsulta, &faturamento2);
                                printf("\nData de cria��o (m�s-ano): %i-%i",mes, ano);
                                printf("\nN�mero de consultas mensais: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\n*** FATURAMENTO MENSAL - UNIDADE II: R$%5.2f ***",faturamento2);
                                printf("\n\n----\n");
                            }
                            fclose(arquivo2);
					
                            arquivo3 = fopen("FaturamentoMensalUnid3.txt","r");
							//Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                            if (arquivo3==NULL){
                                printf("\nN�o foi possivel abrir o arquivo. PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...\n");
                                getch();
                                return;
                            }
							//Procura de dados no arquivo texto enquanto nao se encontra o final do arquivo
                            while(!feof(arquivo3)){
                                fscanf(arquivo3,"%i %i %i %i %f ",&mes, &ano,&numConsulta, &valConsulta, &faturamento3);
                                printf("\nData de cria��o (m�s-ano): %i-%i",mes, ano);
                                printf("\nN�mero de consultas mensais: %i",numConsulta);
                                printf("\nValor total das consultas: R$%i",valConsulta);
                                printf("\n\n*** FATURAMENTO MENSAL - UNIDADE III: R$%5.2f ***",faturamento3);
                                printf("\n\n----\n");
                            }
                            fclose(arquivo3);
							//Opera��o para somar o faturamento mensal da rede
                            faturamento_total=faturamento1+faturamento2+faturamento3; 
                            printf("\n\n*** FATURAMENTO TOTAL MENSAL DA REDE: R$%5.2f ***",faturamento_total);
                            printf("\n\n");

                            system("pause");
                            system("cls");
                            break;

                    } 
                    break;

                case 3: //Pacientes por Unidade (Consulta)
                    printf("Insira a Unidade para consulta (1,2 ou 3): ");
                    scanf("%i",&consUnidP);
					//Comando if/else para que apare�a no relat�rio a qnt de pacientes, de acordo com a unidade escolhida
                    if (consUnidP==1){
                        printf("\nQuantidade de Paciente na Unidade 1: %i \n\n",total_pacientes1);
                    }
                    else
						if (consUnidP==2){
                       		printf("\nQuantidade de Paciente na Unidade 2: %i \n\n",total_pacientes2);
                   		}
                   		else
		                    if (consUnidP==3){
		                        printf("\nQuantidade de Paciente na Unidade 3: %i \n\n",total_pacientes3);
		                    }
                    printf("\n\n");
                    system("pause");
                    system("cls");
                    break;

                case 4: //Atendimentos por Unidade (Consulta)
                //Cadeis de if/else para comparar o total de atendimento das 3 unidades e aparecer no relat�rio qual unidade que mais atende
                
                    if ((total_Atendimentos1>total_Atendimentos2)&&(total_Atendimentos1>total_Atendimentos3)){
                        printf("\nUnidade 1 � a que mais atende, com %i Atendimentos!\n\n",total_Atendimentos1);
                    }
                    else
                        if((total_Atendimentos2>total_Atendimentos3)&&(total_Atendimentos2>total_Atendimentos1)){
                            printf("\nUnidade 2 � a que mais atende, com %i Atendimentos!\n\n",total_Atendimentos2);
                        }
                        else
                            if((total_Atendimentos3>total_Atendimentos1)&&(total_Atendimentos3>total_Atendimentos2)){
                                printf("\nUnidade 3 � a que mais atende, com %i Atendimentos!\n\n",total_Atendimentos3);
                            }
                            else
                                if(total_Atendimentos1==total_Atendimentos2 && total_Atendimentos1==total_Atendimentos3){
                                    printf("\nTodas as Unidades atendem na mesma quantidade: %i",total_Atendimentos1);
                                }
                                else
                                    if(total_Atendimentos1==total_Atendimentos3){
                                        printf("\nAs Unidades 1 e 3 atendem na mesma quantidade: %i",total_Atendimentos1);
                                    }
                                    else
                                        if (total_Atendimentos2==total_Atendimentos3){
                                            printf("\nAs Unidades 2 e 3 atendem na mesma quantidade: %i",total_Atendimentos2);
                                        }
                                        else{
                                            printf("\nAs Unidades 1 e 2 atendem na mesma quantidade: %i",total_Atendimentos1);
                                        }
                    printf("\n\n");
                    system("pause");
                    system("cls");
                    break;
                } 
                break;

            case 3:
                return; //Encerra a fun��o e retorna para a Tela de Menu, no int main
                break;

            case 4: //Sair do programa
                printf("\nFINALIZANDO O PROGRAMA...");
                exit (0);
                break; 

            default: printf("Tente novamente. Escolha o n�mero 1, 2, 3 ou 4.\n");
        }
    }while(op_menu!=0); //Enquanto o usuario digitar um n�mero diferente de 0, haver� redirecionameto para a tela principal do relat�rio
    return;
}

void TelaPacientes(void){
	int opcao, telefonePaciente;
	char nomePaciente[10], sobreNomePaciente[10], cpfPaciente[11],idade[2],  estadoCivil[10], planoSaude[10];
	
	FILE *arquivoPaciente; //FILE referente ao cadastro/lista de pacientes
	
	setlocale(LC_ALL, "Portuguese"); //Comando para que os caracteres especiais usados em pt-BR sejam leg�veis no decorrer das telas do programa. *Funciona apenas com a biblioteca locale.h
	
	do {
		printf("\n\t\t\t--Bem-Vindo(a) � TELA DE CADASTRO DE PACIENTES--\n");
        printf("\nMENU");
        printf("\n 1- Cadastro de pacientes");
        printf("\n 2- Listar pacientes cadastrados");
        printf("\n 3- Voltar � Tela de Menu");
        printf("\n 4- Sair do programa");
        
        printf("\n\nDigite uma op��o: ");
        scanf("%d", &opcao);
        system("cls");
        
        switch(opcao){
        	case 1: //Cadastro de pacientes
        		printf("\nDigite o Nome do paciente: ");
                setbuf(stdin,NULL); 
                gets(nomePaciente);
                
                printf("\nDigite o Sobrenome do paciente: ");
                setbuf(stdin,NULL);
                gets(sobreNomePaciente);
                
                printf("\nDigite o telefone: ");
                scanf("%d", &telefonePaciente);
                
                printf("\nCPF: ");
				scanf ("%s",&cpfPaciente);
				
				printf("\nEstado Civil: ");
				scanf ("%s",&estadoCivil);
				
				printf("\nPlano de Sa�de: ");
				scanf ("%s",&planoSaude);
				
				printf("\nIdade: ");
				scanf ("%s",&idade);

				arquivoPaciente = fopen("cadastropacientes.txt","a");
				//Verifica��o se o arquivo existe para ocorrer a escrita de dados.
				if(arquivoPaciente==NULL){
			        printf("Nao foi possivel abrir o arquivo");
			        exit(0);
			    }
				//Escritas de dados no arquivo texto
				fprintf(arquivoPaciente, "%s %s %s %s %s %s %d\n", nomePaciente, sobreNomePaciente, cpfPaciente, estadoCivil, planoSaude, idade, telefonePaciente);
				
				fclose(arquivoPaciente);
				
                system("pause");
                system("cls");
                break;
                
            case 2: //Lista de pacientes cadastrados
                arquivoPaciente = fopen("cadastropacientes.txt","r");
                //Verifica��o se o arquivo existe para ocorrer a leitura de dados.
                if(arquivoPaciente==NULL){
			        printf("Nao foi possivel abrir o arquivo");
			        exit(0);
			    }
			    printf("--DADOS DOS PACIENTES--\n");
			    //Enquanto nao foi fim do arquivo, ocorrer� o fscanf � a procura de dados
			    while(!feof(arquivoPaciente)){
			    	 fscanf(arquivoPaciente,"%s %s %s %s %s %s %d ", &nomePaciente, &sobreNomePaciente, &cpfPaciente, &estadoCivil, &planoSaude, &idade, &telefonePaciente);
				     printf("\nNome: %s %s \nCPF: %s  \nEstado Civil: %s \nPlano de Sa�de: %s \nIdade: %s \nTelefone: %d\n",nomePaciente, sobreNomePaciente, cpfPaciente, estadoCivil, planoSaude, idade, telefonePaciente);
				     printf("\n---------------------------------------\n");
			    }
                fclose(arquivoPaciente);
    
                system("pause");
                system("cls");
                break;
                
            case 3: //Encerra a fun��o e retorna para o Menu principal, em int main
            	return; 
            	system("cls");
            	break;
            	
            case 4: //Finaliza o programa
            	printf("\n\nFinalizando...\n\n");
	            system("pause");
	            exit(0);
            	break;
            	
            default:
                printf("Op��o inv�lida! Tente novamente digitando o n�mero 1, 2, 3 ou 4.\n\n");
		}
		
	}while(opcao!=0); //Enquanto o usu�rio digitar um n�mero diferente de 0, haver� retorno para a tela de menu de cadastro de pacientes
}

void TelaAgenda(void){
	char nome[10], sobreNome[10], data[10], horario[5], especialidade[40], cpf[11];
 	int opcao, telefone, unidade;
  	float valor;
  	FILE *arquivoAgenda; //FILE referente � agenda de pacientes
  	
  	setlocale(LC_ALL, "Portuguese"); //Comando para que os caracteres especiais usados em pt-BR sejam leg�veis no decorrer das telas do programa. *Funciona apenas com a biblioteca locale.h
  	
	do {
        printf("\n\t\t\t--Bem-Vindo(a) ao AGENDAMENTO DE CONSULTAS--\n");
        printf("\nMENU");
        printf("\n 1- Cadastro de consultas");
        printf("\n 2- Listar consultas agendadas");
        printf("\n 3- Voltar � Tela de Menu");
        printf("\n 4- Sair do programa");
        
        printf("\n\nDigite uma op��o: ");
        scanf("%d", &opcao);
        system("cls");

        switch(opcao){
        	case 1: //Agendamento de consulta
                printf("\nDigite o Nome: ");
                setbuf(stdin,NULL);
                gets(nome);
                
                printf("\nDigite o Sobrenome: ");
                setbuf(stdin,NULL);
                gets(sobreNome);
                
                printf("\nDigite o telefone: ");
                scanf("%d",&telefone);
                
                printf("\nCPF: ");
				scanf ("%s",&cpf);
				
                printf("\nDigite a Especialidade de atendimento: ");
				scanf ("%s",&especialidade);
				
				printf("\nData da consulta (formato dd/mm/yyyy): ");
				scanf ("%s",&data);
				
				printf("\nHor�rio da consulta (formato hh:mm): ");
				scanf ("%s",&horario);
				
				printf("\nValor da consulta: R$");
				scanf ("%f",&valor);
				
				printf("\nDigite a Unidade de atendimento (1,2 ou 3): ");
				scanf ("%d",&unidade);

                arquivoAgenda = fopen("cadastroAgenda.txt","a");
                //Verificar se o arquivo existe
                if(arquivoAgenda==NULL){
			        printf("Nao foi possivel abrir o arquivo");
			        exit(0);
			    }
			    //Escritas de dados no arquivo texto
                fprintf(arquivoAgenda, "%s %s %d %s %s %s %s %f %d\n", nome, sobreNome, telefone, especialidade, data, horario, cpf,valor, unidade);
                
                fclose(arquivoAgenda);
                
                system("pause");
                system("cls");
                break;
                
            case 2: //Listamento da agenda de consultas
            	arquivoAgenda = fopen("cadastroAgenda.txt","r");
            	//Verifica��o se o arquvo existe
            	if(arquivoAgenda==NULL){
			        printf("Nao foi possivel abrir o arquivo");
			        exit(0);
			    }
			    
			    printf("--AGENDAMENTOS--\n");
			    // enquanto nao for fim do arquivo, haver� procura de dados
                while(!feof(arquivoAgenda)){
			        fscanf(arquivoAgenda,"\n %s %s %d %s %s %s %s %f %d ", &nome, &sobreNome, &telefone, &especialidade, &data, &horario, &cpf, &valor, &unidade);
					printf("\nNome: %s %s \nTelefone: %d \nCPF: %s \nEspecialidade: %s \nData de consulta: %s \nHor�rio: %s \nUnidade de atendimento: %d \nValor da consulta: R$%5.2f\n", nome, sobreNome, telefone,cpf, especialidade, data, horario,unidade, valor);
			    	printf("\n---------------------------------------\n");
				}
				fclose(arquivoAgenda);
				
                system("pause");
                system("cls");
                break;
                
            case 3: //Encerra a fun��o e restorna para a tela de menu, em int main
            	return; 
            	system("cls");
            	break;
            	
            case 4: //Finaliza o programa
            	printf("\n\nFinalizando...\n\n");
                system("pause");
                exit(0);
            	break;
            	
            default:
                printf("Op��o inv�lida! Tente novamente digitando o n�mero 1, 2, 3 ou 4.\n\n");
        }
    }while(opcao!=0); //Enquanto o usu�rio digitar um n�mero diferente de 0, haver� retorno para a tela de menu da agenda de pacientes
}

int main(){
    int opMenu;
    setlocale(LC_ALL, "Portuguese"); //Comando para que os caracteres especiais usados em pt-BR sejam leg�veis no decorrer das telas do programa. *Funciona apenas com a biblioteca locale.h
	
	//Tela inicial do aplicativo
    printf("\n\t\t\t--BEM VINDO(A) AO SOFTWARE DA CL�NICA GRIERSONMED--\n");
    printf("\nPara come�ar, pressione qualquer tecla para ir � tela de login! ");

    getch();
    system("cls");
	
	//Chama a fun��o da tela de login para que o usuario fa�a login no sistema
    TelaLogin();

    do{
        printf("\n\t\t\t--TELA DE MENU--\n");
        printf("\nBem-Vindo(a) ao menu. Escolha um n�mero para prosseguir\n");
        printf("\n1- Cadastro/Lista de Pacientes");
        printf("\n2- Agenda de Pacientes");
        printf("\n3- Relat�rios");
        printf("\n4- Trocar de Usu�rio");
        printf("\n5- Sair do programa");
        printf("\n\nN�mero: ");
        scanf("%i",&opMenu);

        system("cls");

        switch(opMenu){
            case 1: //Chama a fun��o de cadastro/lista de pacientes
				TelaPacientes(); 
                break;

            case 2: //Chama a fun��o de agenda de pacientes
            	TelaAgenda(); 
                break;

            case 3: //Chama a fun��o de criar/consultar relat�rio
                TelaRelatorio(); 
                break;

            case 4: //Chama a fun��o da tela de login
                TelaLogin(); 
                break;

            case 5: //Finaliza o programa
                printf("\nFINALIZANDO O PROGRAMA...\n");
                exit(0);
                break;

            default: printf("Tente novamente. Digite os n�meros 1,2,3,4 ou 5.\n");
        }
    }while(opMenu!=0); //Enquanto o usu�rio digitar um n�mero diferente de 0, haver� retorno para a tela de menu do aplicativo
    return 0;
}

