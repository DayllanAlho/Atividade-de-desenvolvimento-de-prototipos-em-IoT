#include <iostream>

using namespace std;
/* 1. Implemente a função 'converteSensor' que receberá 3 argumentos:
-uma medida;
-um valor mínimo; e
-um valor máximo.
A função retornará o valor percentual da medida (0 a 100) em função do intervalo entre os valores mínimo e máximo.
*/

int converteSensor(int medida, int minValor, int maxValor)
{
    int convertido = (medida - minValor) *100 /(maxValor - minValor);
    // O valor convertido é igual a (medida - minValor) multiplicado por 100 e dividido por (maxValor - minValor).
    return convertido;
}



/*2. Implemente a função 'leituraSensor' que não receberá argumentos.Esta função tem por objetivo simular a leitura de sensores (neste caso, sensores de distância). A função solicita e retorna um valor inteiro, entre o intervalo de mínimo e máximo (ver item 1), digitado pelo usuário (via teclado).
*/

int leituraSensor()
{
    int valor;

    cout << "Digite um valor entre 0 e 830: ";
    cin >> valor;
    
    if (valor < 0 && valor > 830)
    {
        // O valor digitado deve estar entre 0 e 830.
        cout << "Valor invalido, digite novamente: ";
        cin >> valor;
    }
    else
    // Se o valor digitado estiver entre 0 e 830, o programa continua.
    {
        return valor;
    }
}

/*3. Implemente a função 'armazenaVetor' que receberá 4 argumentos:
-o ponteiro do vetor que receberá a medida;
-o tamanho do vetor;
-a posição atual para armazenamento; e
-a medida para ser armazenada no vetor.
A função deve armazenar a medida no vetor, segundo posição indicada (posição atual) e retornar a próxima posição para armazenamento futuro.
*/

int armazenaVetor(int *vetor, int tamanho, int posicaoAtual, int medida)
{
    vetor[posicaoAtual] = medida;
    posicaoAtual++;
    return posicaoAtual;
// se a posição atual for menor que o tamanho do vetor, o programa continua.


    if (posicaoAtual < tamanho)
    {
        return posicaoAtual;
    }
    // Se a posição atual for maior que o tamanho do vetor, o programa retorna 0.
    else 
    {
        return 0;
    }
}


/*4. Implemente a função 'direcaoMenorCaminho' que receberá 2 argumentos:
(1) o ponteiro para um vetor; e
(2) o ponteiro para uma variável.
Esta função deve avaliar 4 valores do vetor, a partir do ponteiro (1) recebido. Os 4 valores representam as distâncias nos sentidos: Direta, Esquerda, Frente e Trás (esses valores foram inseridos com a função 'leituraSensor', convertidos com a função 'converteSensor' e armazenados no vetor com a função 'armazenaVetor'). Esta função retorna o sentido de maior distância, e com base no ponteiro (2) para a variável, nela armazena o valor da maior distância.
*/

int direcaoMenorCaminho(int *vetor, int *variavel)
{
    int maior = 0;

    // Se o valor da posição 0 do vetor for maior que o valor da variável, o programa retorna 0.
    if(vetor [0] > maior)
    {
        maior = vetor [0];
        *variavel = maior;
        return 0;
    }
    
    // Se o valor da posição 1 do vetor for maior que o valor da variável, o programa retorna 1.
    else if(vetor [1] > maior)
    {
        maior = vetor [1];
        *variavel = maior;
        return 1;
    }

    // Se o valor da posição 1 do vetor for maior que o valor da variável, o programa retorna 2.
    else if(vetor [2] > maior)
    {
        maior = vetor [2];
        *variavel = maior;
        return 2;
    }

    // Se o valor da posição 1 do vetor for maior que o valor da variável, o programa retorna 3.
    else if(vetor [3] > maior)
    {
        maior = vetor [3];
        *variavel = maior;
        return 3;
    }
}

/*5. Implemente a função 'leComando' que não receberá argumentos. Esta função pergunta ao usuário se ele deseja continuar o mapeamento. A função retorna o inteiro 1 (um) se a resposta for SIM ou 0 (zero) se a resposta for NÃO.
*/

int leComando()
{
    int comando;
    cout << "Deseja continuar o mapeamento? 1 para SIM e 0 para NAO: ";
    // O usuário terá que escrever 1 para SIM e 0 para NAO.
    cin >> comando;
    return comando;
}

/*6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", "Frente", "Tras"). Em outras palavras, o robô tem 4 sensores, um em cada ponto, e eles vão indicar para o robô em que direção ele deve se mover. A cada passo, ele verifica as distâncias aos objetos, de cada direção, e vai "mapeando" o terreno para uma movimentação futura, armazenando estas distancias em um vetor fornecido como parâmetro.
No final a função retorna a ultima posicao preenchida do vetor. Esta função deve também ir lendo os 4 sensores até que um comando de pare seja enviado. Para simular os sensores e os comandos de pare, use as funções já construídas nos ítens anteriores e em um looping contínuo até que um pedido de parada seja enviado pelo usuário. Complete a função com a chamada das funções já criadas

Complete a função com a chamada das funções já criadas*/

int dirige(int *v,int maxv){
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	int dirigindo = 1;		
	while(dirigindo){		
		int medida = leituraSensor();
        cout << "Medida: " << medida << endl;
        
        medida = converteSensor(medida, 0, 830);
        cout << "Medida convertida: " << medida << endl;

		posAtualVetor = armazenaVetor(vetorMov,maxVetor,posAtualVetor,medida);
        cout << "Posicao atual do vetor: " << posAtualVetor << endl;

        dirigindo = leComando();
        cout << "Comando: " << dirigindo << endl;
    }        
        return posAtualVetor;
		dirigindo = leComando();		
}


// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado 
// na maior distância a cada movimento
void percorre(int *v,int tamPercorrido){		
	int *vetorMov = v;
	int maiorDir = 0;
    int maiorEsq = 0;
    int maiorFrente = 0;
    int maiorTras = 0;
    int maior = 0;
    int posicao = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){
		char *direcao = direcaoMenorCaminho(&(vetorMov[i]),&maiorDir);
        // Se a direção for 0, o robô irá para a direita.
        char *esquerda = direcaoMenorCaminho(&(vetorMov[i+1]),&maiorEsq);
        // Se a direção for 1, o robô irá para a esquerda.
        char *frente = direcaoMenorCaminho(&(vetorMov[i+2]),&maiorFrente);
        // Se a direção for 2, o robô irá para a frente.
        char *tras = direcaoMenorCaminho(&(vetorMov[i+3]),&maiorTras);
        // Se a direção for 3, o robô irá para a trás.

		printf("Movimentando para %s distancia = %i\n",direcao,maiorDir);
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posAtualVet = 0;
	
	posAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posAtualVet);
	
	return 0;
}