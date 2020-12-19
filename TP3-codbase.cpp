// INF110 - TRABALHO PRÁTICO III
// PROGRAMA PARA LER, MODIFICAR E GRAVAR UMA IMAGEM NO FORMATO PNM
// AUTOR: DAVI DE PAULA OLIVEIRA

#include <iostream>
#include <fstream>
#include <cstring>

const int MAXALTURA  = 500; // ALTURA MÁXIMA
const int MAXLARGURA = 500; // LARGURA MÁXIMA

using namespace std;

void clarear(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]);
void escurecer(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]);
void negativo(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]);
void espelhar(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]);
void tonscinza(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]);
void sobel(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]);
void laplace(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]);
void roberts(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]);

int main() {

    // DECLARANDO AS VARIÁVEIS

    int resposta; // RESPOSTA QUE SERÁ DIGITADA
    unsigned char imagem[MAXALTURA][MAXLARGURA][3]; // A IMAGEM PROPRIAMENTE DITA
    int largura, altura; // DIMENSÕES DA IMAGEM
    char tipo[4]; // TIPO DA IMAGEM
    ifstream arqentrada; // ARQUIVO QUE CONTEM A IMAGEM ORIGINAL
    ofstream arqsaida; // ARQUIVO QUE CONTERÁ A IMAGEM GERADA
    char comentario[200], c; // AUXILIARES
    int i, j, k, valor; // AUXILIARES

    // INFORMANDO AS OPÇÕES
    cout << "TRABALHO III - TRATAMENTO E MANIPULACAO DE IMAGENS\n\n";
    cout << "1 - CLAREAR UMA IMAGEM\n";
    cout << "2 - ESCURECER UMA IMAGEM\n";
    cout << "3 - NEGATIVO DE UMA IMAGEM\n";
    cout << "4 - ESPELHAR UMA IMAGEM\n";
    cout << "5 - TRANSFORMAR UMA IMAGEM COLORIDA EM TONS DE CINZA\n";
    cout << "6 - APLICAR O FILTRO DE SOBEL EM UMA IMAGEM\n";
    cout << "7 - APLICAR O FILTRO DE LAPLACE EM UMA IMAGEM\n";
    cout << "8 - APLICAR O FILTRO DE ROBERTS EM UMA IMAGEM\n";
    cout << "0 - SAIR\n";

    cout << "\nINFORME A OPCAO:\n";

    cin >> resposta;

    while(resposta != 0) {

        // ABERTURA DO ARQUIVO

        char entradacompleta[50] = "fig-exemplo/", saidacompleta[50] = "fig-resultado/", entrada[20], saida[20];

        cout << "\nINFORME O NOME DO ARQUIVO PNM:\n";
        cin >> entrada;

        strcat(entradacompleta, entrada);
        strcat(entradacompleta, ".pnm");

        arqentrada.open(entradacompleta, ios::in); // ABRE O ARQUIVO PARA LEITURA
        if(!arqentrada) {
            cout << "\nNAO CONSEGUI ABRIR O ARQUIVO!" << endl;
            continue;
        }

        // LEITURA DO CABEÇALHO

        arqentrada >> tipo;	// LÊ O TIPO DE ARQUIVO
        arqentrada.get();	// LÊ E DESCARTA O \N DO FINAL DA 1A. LINHA

        if(strcmp(tipo,"P2") == 0) {
            cout << "\nIMAGEM EM TONS DE CINZA\n";
        } else if(strcmp(tipo,"P3") == 0) {
            cout << "\nIMAGEM COLORIDA\n";
        } else if(strcmp(tipo,"P5") == 0 || strcmp(tipo,"P6") == 0) {
            cout << "\nIMAGEM NO FORMATO RAW\n";
            cout << "DESCULPE, MAS NAO TRABALHO COM ESSE TIPO DE IMAGEM\n";
            arqentrada.close();
            continue;
        }

        while((c = arqentrada.get()) == '#') {   // ENQUANTO FOR COMENTÁRIO
            arqentrada.getline(comentario,200); // LÊ E DESCARTA A LINHA "INTEIRA"
        }

        arqentrada.putback(c); // DEVOLVE O CARACTERE LIDO PARA A ENTRADA, POIS COMO
        //  NÃO ERA COMENTÁRIO, ERA O PRIMEIRO DÍGITO DA LARGURA

        arqentrada >> largura >> altura; // LÊ O NÚMERO DE PIXELS DA HORIZONTAL E VERTICAL

        cout << "TAMANHO: " << largura << " X " << altura << endl;

        if(largura > MAXLARGURA) {
            cout << "DESCULPE, MAS AINDA NAO TRABALHO COM IMAGENS COM MAIS DE " << MAXLARGURA << " PIXELS DE LARGURA\n";
            arqentrada.close();
            continue;
        }

        if(largura > MAXALTURA) {
            cout << "DESCULPE, MAS AINDA NAO TRABALHO COM IMAGENS COM MAIS DE " << MAXALTURA << " PIXELS DE ALTURA\n";
            arqentrada.close();
            continue;
        }

        arqentrada >> valor; // VALOR MÁXIMO DO PIXEL (TEMOS QUE LER, MAS NÃO SERÁ USADO)

        // LEITURA DOS PIXELS DA IMAGEM

        if(strcmp(tipo,"P2") == 0) {
            for(i = 0; i < altura; i++) {
                for(j = 0; j < largura; j++) {
                    arqentrada >> valor;
                    imagem[i][j][0] = (unsigned char)valor;
                }
            }
        } else if (strcmp(tipo,"P3") == 0) {
            for(i = 0; i < altura; i++) {
                for(j = 0; j < largura; j++) {
                    for(k = 0; k < 3; k++) {
                        arqentrada >> valor;
                        imagem[i][j][k] = (unsigned char)valor;
                    }
                }
            }
        }

        arqentrada.close();

        // FIM DA LEITURA DA IMAGEM

        // INÍCIO DO TRATAMENTO DA IMAGEM

        if(resposta == 1) {
            clarear(imagem, largura, altura, tipo);
        } else if(resposta == 2) {
            escurecer(imagem, largura, altura, tipo);
        } else if(resposta == 3) {
            negativo(imagem, largura, altura, tipo);
        } else if(resposta == 4) {
            espelhar(imagem, largura, altura, tipo);
        } else if(resposta == 5) {
            if(strcmp(tipo,"P3") == 0) {
                tonscinza(imagem, largura, altura, tipo);
            } else {
                cout << "\nA IMAGEM ESCOLHIDA NAO E COLORIDA\n";
                continue;
            }
        } else if(resposta == 6) {
            sobel(imagem, largura, altura, tipo);
        } else if(resposta == 7) {
            laplace(imagem, largura, altura, tipo);
        } else if(resposta == 8) {
            roberts(imagem, largura, altura, tipo);
        }

        // FIM DO TRATAMENTO DA IMAGEM

        // INÍCIO DA GRAVACAO DA IMAGEM

        cout << "\nINFORME O NOME DO ARQUIVO PNM PARA SALVAR:\n";
        cin >> saida;

        strcat(saidacompleta, saida);
        strcat(saidacompleta, ".pnm");

        arqsaida.open(saidacompleta, ios::out); // ABRE O ARQUIVO PARA ESCRITA

        if(!arqsaida) {
            cout << "\nNAO CONSEGUI CRIAR O ARQUIVO!" << endl;
            continue;
        }

        arqsaida << tipo << endl; // TIPO
        arqsaida << "# INF110\n";// COMENTÁRIO
        arqsaida << largura << " " << altura << endl; // DIMENSÕES
        arqsaida << 255 << endl; // MAIOR VALOR

        if(strcmp(tipo,"P2") == 0) {
            for(i = 0; i < altura; i++) {
                for(j = 0; j < largura; j++) {
                    arqsaida << (int)imagem[i][j][0] << endl;	// PIXELS
                }
            }
        } else if (strcmp(tipo,"P3") == 0) {
            for(i = 0; i < altura; i++) {
                for(j = 0; j < largura; j++) {
                    for(k = 0; k < 3; k++) {
                        arqsaida << (int)imagem[i][j][k] << endl;	// PIXELS
                    }
                }
            }
        }

        arqsaida.close(); // FECHA O ARQUIVO

        cout << "\nTRATAMENTO REALIZADO COM SUCESSO!\n" << endl;

        // FIM DA GRAVACAO DA IMAGEM

        // INFORMANDO AS OPÇÕES

        cout << "1 - CLAREAR UMA IMAGEM\n";
        cout << "2 - ESCURECER UMA IMAGEM\n";
        cout << "3 - NEGATIVO DE UMA IMAGEM\n";
        cout << "4 - ESPELHAR UMA IMAGEM\n";
        cout << "5 - TRANSFORMAR UMA IMAGEM COLORIDA EM TONS DE CINZA\n";
        cout << "6 - APLICAR O FILTRO DE SOBEL EM UMA IMAGEM\n";
        cout << "7 - APLICAR O FILTRO DE LAPLACE EM UMA IMAGEM\n";
        cout << "8 - APLICAR O FILTRO DE ROBERTS EM UMA IMAGEM\n";
        cout << "0 - SAIR\n";

        cout << "\nINFORME A OPCAO:\n";

        cin >> resposta;

    }

    return 0;
}

void clarear(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]) {

    // TRATAMENTO DA IMAGEM

    int fator, i, j, k, valor;
    cout << "QUAL O FATOR DE CLAREAMENTO (1-100)? \n";
    cin >> fator;

    while(fator < 1 || fator > 100) {
        cout << "VALOR INVALIDO! QUAL O FATOR DE CLAREAMENTO (1-100)? \n";
        cin >> fator;
    }

    // CLAREIA A IMAGEM

    if(strcmp(tipo,"P2") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                valor = (int)imagem[i][j][0]; // PEGA O VALOR DO PIXEL
                valor += fator; // CLAREIA O PIXEL

                if(valor > 255) {  // SE DER UM VALOR MAIOR QUE 255
                    valor = 255; // DEIXA BRANCO
                }

                imagem[i][j][0] = (unsigned char)valor; // MODIFICA O PIXEL
            }
        }
    } else if (strcmp(tipo,"P3") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                for(k = 0; k < 3; k++) {
                    valor = (int)imagem[i][j][k]; // PEGA O VALOR DO PIXEL
                    valor += fator; // CLAREIA O PIXEL

                    if(valor > 255) {  // SE DER UM VALOR MAIOR QUE 255
                        valor = 255; // DEIXA BRANCO
                    }

                    imagem[i][j][k] = (unsigned char)valor; // MODIFICA O PIXEL
                }
            }
        }
    }

    // FIM DO TRATAMENTO DA IMAGEM
}

void escurecer(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]) {

    // TRATAMENTO DA IMAGEM

    int fator, i, j, k, valor;
    cout << "QUAL O FATOR DE ESCURECIMENTO (1-100)? \n";
    cin >> fator;

    while(fator < 1 || fator > 100) {
        cout << "VALOR INVALIDO! QUAL O FATOR DE ESCURECIMENTO (1-100)? \n";
        cin >> fator;
    }

    // ESCURECE A IMAGEM

    if(strcmp(tipo,"P2") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                valor = (int)imagem[i][j][0]; // PEGA O VALOR DO PIXEL
                valor -= fator; // ESCURECE O PIXEL

                if(valor < 0) {   // SE DER UM VALOR MENOR QUE 0
                    valor = 0; // DEIXA PRETO
                }

                imagem[i][j][0] = (unsigned char)valor; // MODIFICA O PIXEL
            }
        }
    } else if (strcmp(tipo,"P3") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                for(k = 0; k < 3; k++) {
                    valor = (int)imagem[i][j][k]; // PEGA O VALOR DO PIXEL
                    valor -= fator; // ESCURECE O PIXEL

                    if(valor < 0) {  // SE DER UM VALOR MENOR QUE 0
                        valor = 0; // DEIXA PRETO
                    }

                    imagem[i][j][k] = (unsigned char)valor; // MODIFICA O PIXEL
                }
            }
        }
    }

    // FIM DO TRATAMENTO DA IMAGEM
}

void negativo(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]) {

    // TRATAMENTO DA IMAGEM

    int i, j, k, valor;

    // NEGATIVO DA IMAGEM

    if(strcmp(tipo,"P2") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                valor = (int)imagem[i][j][0]; // PEGA O VALOR DO PIXEL
                valor = 255 - valor;
                imagem[i][j][0] = (unsigned char)valor; // MODIFICA O PIXEL
            }
        }
    } else if (strcmp(tipo,"P3") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                for(k = 0; k < 3; k++) {
                    valor = (int)imagem[i][j][k]; // PEGA O VALOR DO PIXEL
                    valor = 255 - valor;
                    imagem[i][j][k] = (unsigned char)valor; // MODIFICA O PIXEL
                }
            }
        }
    }

    // FIM DO TRATAMENTO DA IMAGEM
}

void espelhar(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]) {

    // TRATAMENTO DA IMAGEM

    int i, j, k, valor;

    // ESPELHANDO A IMAGEM

    if(strcmp(tipo,"P2") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura / 2; j++) {
                valor = (int)imagem[i][j][0]; // PEGA O VALOR DO PIXEL
                imagem[i][j][0] = imagem[i][largura - j - 1][0];
                imagem[i][largura - j - 1][0] = (unsigned char)valor; // MODIFICA O PIXEL
            }
        }
    } else if (strcmp(tipo,"P3") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura / 2; j++) {
                for(k = 0; k < 3; k++) {
                    valor = (int)imagem[i][j][k]; // PEGA O VALOR DO PIXEL
                    imagem[i][j][k] = imagem[i][largura - j - 1][k];
                    imagem[i][largura - j - 1][k] = (unsigned char)valor; // MODIFICA O PIXEL
                }
            }
        }
    }

    // FIM DO TRATAMENTO DA IMAGEM
}

void tonscinza(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]) {

    // TRATAMENTO DA IMAGEM

    int i, j, a, b, c, valor;

    // TRANSFORMANDO A IMAGEM COLORIDA EM TONS DE CINZA

    tipo[1] = '2';

    for(i = 0; i < altura; i++) {
        for(j = 0; j < largura; j++) {
            a = (int)imagem[i][j][0];
            b = (int)imagem[i][j][1];
            c = (int)imagem[i][j][2];
            imagem[i][j][0] = (unsigned char)((a + b + c) / 3);
        }
    }

    // FIM DO TRATAMENTO DA IMAGEM
}

void sobel(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]) {

    // TRATAMENTO DA IMAGEM

    int i, j, k, x, y, z;

    // APLICANDO O FILTRO DE SOBEL

    unsigned char clone[MAXALTURA + 2][MAXLARGURA + 2][3];

    // PREENCHENDO COM ZERO

    for(i = 0; i < altura + 2; i++) {
        for(j = 0; j < largura + 2; j++) {
            for(k = 0; k < 3; k++) {
                clone[i][j][k] = (unsigned char)0;
            }
        }
    }

    // COPIANDO A MATRIZ

    for(i = 1; i < altura + 1; i++) {
        for(j = 1; j < largura + 1; j++) {
            for(k = 0; k < 3; k++) {
                clone[i][j][k] = imagem[i - 1][j - 1][k];
            }
        }
    }

    if(strcmp(tipo,"P2") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                y = (int)clone[i][j][0] + (int)clone[i][j + 1][0] * 2 +
                    (int)clone[i][j + 2][0] - (int)clone[i + 2][j][0] -
                    (int)clone[i + 2][j + 1][0] * 2 - (int)clone[i + 2][j + 2][0];

                if(y < 0) {
                    y = 0;
                } else if (y > 255) {
                    y = 255;
                }

                x = (int)clone[i][j][0] - (int)clone[i][j + 2][0] +
                    (int)clone[i + 1][j][0] * 2 - (int)clone[i + 1][j + 2][0] * 2 +
                    (int)clone[i + 2][j][0] - (int)clone[i + 2][j + 2][0];

                if(x < 0) {
                    x = 0;
                } else if (x > 255) {
                    x = 255;
                }

                z = (x + y) / 2;

                imagem[i][j][0] = (unsigned char)z;
            }
        }
    } else if(strcmp(tipo,"P3") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                for(k = 0; k < 3; k++) {
                    y = (int)clone[i][j][k] + (int)clone[i][j + 1][k] * 2 +
                        (int)clone[i][j + 2][k] - (int)clone[i + 2][j][k] -
                        (int)clone[i + 2][j + 1][k] * 2 - (int)clone[i + 2][j + 2][k];

                    x = (int)clone[i][j][k] - (int)clone[i][j + 2][k] +
                        (int)clone[i + 1][j][k] * 2 - (int)clone[i + 1][j + 2][k] * 2 +
                        (int)clone[i + 2][j][k] - (int)clone[i + 2][j + 2][k];

                    if(y < 0) {
                        y = 0;
                    } else if (y > 255) {
                        y = 255;
                    }

                    if(x < 0) {
                        x = 0;
                    } else if (x > 255) {
                        x = 255;
                    }

                    z = (x + y) / 2;

                    imagem[i][j][k] = (unsigned char)z;
                }
            }
        }
    }

    // FIM DO TRATAMENTO DA IMAGEM
}

void laplace(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]) {

    // TRATAMENTO DA IMAGEM

    int i, j, k, valor;

    // APLICANDO O FILTRO DE LAPLACE

    unsigned char clone[MAXALTURA + 2][MAXLARGURA + 2][3];

    // PREENCHENDO COM ZERO

    for(i = 0; i < altura + 2; i++) {
        for(j = 0; j < largura + 2; j++) {
            for(k = 0; k < 3; k++) {
                clone[i][j][k] = (unsigned char)0;
            }
        }
    }

    // COPIANDO A MATRIZ

    for(i = 1; i < altura + 1; i++) {
        for(j = 1; j < largura + 1; j++) {
            for(k = 0; k < 3; k++) {
                clone[i][j][k] = imagem[i - 1][j - 1][k];
            }
        }
    }

    if(strcmp(tipo,"P2") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                valor = - (int)clone[i][j + 1][0] - (int)clone[i + 1][j][0] + (int)clone[i + 1][j + 1][0] * 4 -
                        (int)clone[i + 1][j + 2][0] - (int)clone[i + 2][j + 1][0];

                if(valor < 0) {
                    valor = 0;
                } else if (valor > 255) {
                    valor = 255;
                }

                imagem[i][j][0] = (unsigned char)valor;
            }
        }
    } else if(strcmp(tipo,"P3") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                for(k = 0; k < 3; k++) {
                    valor = - (int)clone[i][j + 1][k] - (int)clone[i + 1][j][k] + (int)clone[i + 1][j + 1][k] * 4 -
                            (int)clone[i + 1][j + 2][k] - (int)clone[i + 2][j + 1][k];

                    if(valor < 0) {
                        valor = 0;
                    } else if (valor > 255) {
                        valor = 255;
                    }

                    imagem[i][j][k] = (unsigned char)valor;
                }
            }
        }
    }

    // FIM DO TRATAMENTO DA IMAGEM
}

void roberts(unsigned char imagem[][MAXLARGURA][3], int largura, int altura, char tipo[]) {

    // TRATAMENTO DA IMAGEM

    int i, j, k, x, y, z;

    // APLICANDO O FILTRO DE ROBERTS

    unsigned char clone[MAXALTURA + 2][MAXLARGURA + 2][3];

    // PREENCHENDO COM ZERO

    for(i = 0; i < altura + 2; i++) {
        for(j = 0; j < largura + 2; j++) {
            for(k = 0; k < 3; k++) {
                clone[i][j][k] = (unsigned char)0;
            }
        }
    }

    // COPIANDO A MATRIZ

    for(i = 1; i < altura + 1; i++) {
        for(j = 1; j < largura + 1; j++) {
            for(k = 0; k < 3; k++) {
                clone[i][j][k] = imagem[i - 1][j - 1][k];
            }
        }
    }

    if(strcmp(tipo,"P2") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                y = (int)clone[i + 1][j + 1][0] - (int)clone[i + 2][j + 2][0];

                if(y < 0) {
                    y = 0;
                } else if (y > 255) {
                    y = 255;
                }

                x = (int)clone[i + 1][j + 2][0] - (int)clone[i + 2][j + 1][0];

                if(x < 0) {
                    x = 0;
                } else if (x > 255) {
                    x = 255;
                }

                z = (x + y) / 2;

                imagem[i][j][0] = (unsigned char)z;
            }
        }
    } else if(strcmp(tipo,"P3") == 0) {
        for(i = 0; i < altura; i++) {
            for(j = 0; j < largura; j++) {
                for(k = 0; k < 3; k++) {
                    y = (int)clone[i + 1][j + 1][k] - (int)clone[i + 2][j + 2][k];

                    if(y < 0) {
                        y = 0;
                    } else if (y > 255) {
                        y = 255;
                    }

                    x = (int)clone[i + 1][j + 2][k] - (int)clone[i + 2][j + 1][k];

                    if(x < 0) {
                        x = 0;
                    } else if (x > 255) {
                        x = 255;
                    }

                    z = (x + y) / 2;

                    imagem[i][j][k] = (unsigned char)z;
                }
            }
        }
    }

    // FIM DO TRATAMENTO DA IMAGEM
}
