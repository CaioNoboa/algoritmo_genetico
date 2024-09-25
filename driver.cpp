#include <iostream>
#include <string>
#include <bitset>
#include <cmath>

using namespace std;

// Structs
struct InformacoesIniciais
{
  int tamanhoPopulacao;
  float taxaCrossover;
  float taxaMutacao;
  int numeroGeracoes;
};
typedef struct InformacoesIniciais InformacoesIniciais;

struct CoeficientesEquacao
{
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;
};
typedef struct CoeficientesEquacao CoeficientesEquacao;

struct Populacao
{
  int individuo;
  long long int resultadoEquacao;
  long long int moduloResultadoEquacao;
  int geracao;
};
typedef struct Populacao Populacao;

// Protótipo de funções
InformacoesIniciais obterInformacoesIniciais();
int obterTamanhoPopulacao();
float obterTaxaCrossover();
float obterTaxaMutacao();
int obterNumeroGeracoes();
void gerarPopulacaoInicial(Populacao[], int);
CoeficientesEquacao obterCoeficientesEquacao();
void obterResultadosEquacaoDosIndividuos(Populacao[], CoeficientesEquacao, int);
void ordenarPopulacao(Populacao[], int);
bool avaliarPopulacao(int);
void selecaoCruzamentoEMutacaoIndividuos(Populacao[], Populacao[], Populacao[], InformacoesIniciais);
void selecionarPopulacao(Populacao[], Populacao[], int);
void cruzamentoPopulacao(Populacao[], Populacao[], InformacoesIniciais);
void converterValoresNegativosEmPositivosPopulacaoSelecionada(Populacao[], int);
int retornarPrimeiraParcelaGenoma(int, int);
int retornarSegundaParcelaGenoma(int, int, int);
int retornarNovoIndividuoCruzamento(int, int, int);
void preencherRestanteNovaPopulacaoComGenitores(Populacao[], Populacao[], int);
void mutacaoPopulacao(Populacao[], InformacoesIniciais);

int main()
{
  Populacao populacao[1000];
  Populacao listaMelhoresIndividuos[1000]; // melhores individuos de cada geracao
  Populacao populacaoSelecionada[500];
  Populacao novaPopulacao[1000];
  Populacao melhorIndividuo;
  bool melhorIndividuoEncontrado = false;
  InformacoesIniciais informacoesIniciais = obterInformacoesIniciais();
  gerarPopulacaoInicial(populacao, informacoesIniciais.tamanhoPopulacao);
  CoeficientesEquacao coeficientesEquacao = obterCoeficientesEquacao();

  for (int i = 0; i < informacoesIniciais.numeroGeracoes; i++)
  {
    obterResultadosEquacaoDosIndividuos(populacao, coeficientesEquacao, informacoesIniciais.tamanhoPopulacao);
    ordenarPopulacao(populacao, informacoesIniciais.tamanhoPopulacao);
    bool avaliacaoPositivaPopulacao = avaliarPopulacao(populacao[0].resultadoEquacao);

    if (!avaliacaoPositivaPopulacao)
    {
      listaMelhoresIndividuos[i] = populacao[0];
      listaMelhoresIndividuos[i].geracao = i + 1;

      selecaoCruzamentoEMutacaoIndividuos(populacao, populacaoSelecionada, novaPopulacao, informacoesIniciais);

      // Atribuindo para populacao a nova populacao da geração
      for (int j = 0; j < informacoesIniciais.tamanhoPopulacao; j++)
      {
        populacao[j] = novaPopulacao[j];
      }
    }
    else
    {
      melhorIndividuo = populacao[0];
      melhorIndividuo.geracao = i + 1;
      melhorIndividuoEncontrado = true;
      break;
    }
  }

  if (melhorIndividuoEncontrado)
  {
    cout << "O melhor individuo foi encontrado na geracao " << melhorIndividuo.geracao << ", com valor " << melhorIndividuo.individuo << ", cujo valor da equacao foi: " << melhorIndividuo.resultadoEquacao << endl;
  }
  else
  {
    ordenarPopulacao(listaMelhoresIndividuos, informacoesIniciais.numeroGeracoes);
    cout << "Todas as geracoes foram percorridas sem encontrar um individuo que atendesse adequadamente os criterios de selecao." << endl;
    cout << "O melhor individuo encontrado foi na geracao " << listaMelhoresIndividuos[0].geracao << ", com valor " << listaMelhoresIndividuos[0].individuo << ", cujo valor da equacao foi: " << listaMelhoresIndividuos[0].resultadoEquacao << endl;
  }

  return 0;
}

InformacoesIniciais obterInformacoesIniciais()
{
  InformacoesIniciais informacoesIniciais;

  cout << "Ola, seja bem vindo ao programa de melhoramento genetico!" << endl;
  cout << "Iniciaremos nossa jornada com obtencao de alguns dados!" << endl;
  informacoesIniciais.tamanhoPopulacao = obterTamanhoPopulacao();
  informacoesIniciais.taxaCrossover = obterTaxaCrossover();
  informacoesIniciais.taxaMutacao = obterTaxaMutacao();
  informacoesIniciais.numeroGeracoes = obterNumeroGeracoes();

  return informacoesIniciais;
}

int obterTamanhoPopulacao()
{
  int valorInformado = 0;
  int tamanhoPopulacao = 0;
  bool valorInformadoCorretamente = false;

  cout << "O tamanho de uma populacao e um fator muito importante para qualquer melhoramento genetico. Quanto maior nossa populacao, maior sera a variabilidade genetica e, consequentemente, mais individuos com caracteristicas de interesse." << endl;
  cout << "Neste programa de melhoramento contamos com bases populacionais pre-determinadas, sao elas: 10, 100 e 1000 individuos. Por favor, informe qual dessas tres opcoes deseja:" << endl;

  while (!valorInformadoCorretamente)
  {
    cout << "Digite 1 para escolher uma populacao de 10 individuos;" << endl;
    cout << "Digite 2 para escolher uma populacao de 100 individuos;" << endl;
    cout << "Digite 3 para escolher uma populacao de 1000 individuos;" << endl;
    cin >> valorInformado;

    if (valorInformado > 0)
    {
      switch (valorInformado)
      {
      case 1:
        tamanhoPopulacao = 10;
        valorInformadoCorretamente = true;
        cout << "Otimo, o tamanho da populacao escolhido foi 10!" << endl;
        break;
      case 2:
        tamanhoPopulacao = 100;
        valorInformadoCorretamente = true;
        cout << "Otimo, o tamanho da populacao escolhido foi 100!" << endl;
        break;
      case 3:
        tamanhoPopulacao = 1000;
        valorInformadoCorretamente = true;
        cout << "Otimo, o tamanho da populacao escolhido foi 1000!" << endl;
        break;
      default:
        cout << "Desculpe, valor informado foi incorreto, me informe novamente o tamanho da populacao desejado:" << endl;
        break;
      }
    }
    else
    {
      cout << "Desculpe, valor informado foi incorreto, me informe novamente o tamanho da populacao desejado:" << endl;
    }
  }

  return tamanhoPopulacao;
}

float obterTaxaCrossover()
{
  float valorInformado = 0.0;
  float taxaCrossover = 0.0;
  bool valorInformadoCorretamente = false;

  while (!valorInformadoCorretamente)
  {
    cout << "A taxa de crossover deve estar entre 0 e 1, ou seja, maior que 0 e menor que 1. Utilize ponto '.' para o decimal" << endl;
    cin >> valorInformado;

    if (valorInformado > 0.0 && valorInformado < 1.0)
    {
      taxaCrossover = valorInformado;
      valorInformadoCorretamente = true;
      cout << "Otimo, a taxa de crossover escolhida foi: " << taxaCrossover << "!" << endl;
    }
    else
    {
      cout << "Desculpe, valor informado foi incorreto!" << endl;
    }
  }

  return taxaCrossover;
}

float obterTaxaMutacao()
{
  float valorInformado = 0.0;
  float taxaMutacao = 0.0;
  bool valorInformadoCorretamente = false;

  while (!valorInformadoCorretamente)
  {
    cout << "A taxa de mutacao deve estar entre 0 e 1, ou seja, maior que 0 e menor que 1. Utilize ponto '.' para o decimal" << endl;
    cin >> valorInformado;

    if (valorInformado > 0.0 && valorInformado < 1.0)
    {
      taxaMutacao = valorInformado;
      valorInformadoCorretamente = true;
      cout << "Otimo, a taxa de mutacao escolhida foi: " << taxaMutacao << "!" << endl;
    }
    else
    {
      cout << "Desculpe, valor informado foi incorreto!" << endl;
    }
  }

  return taxaMutacao;
}

int obterNumeroGeracoes()
{
  int valorInformado = 0;
  int numeroGeracoes = 0;
  bool valorInformadoCorretamente = false;

  while (!valorInformadoCorretamente)
  {
    cout << "Por favor, agora informe o numero de geracoes! O valor deve ser maior que zero e no maximo 1000." << endl;
    cin >> valorInformado;

    if (valorInformado > 0 && valorInformado <= 1000)
    {
      numeroGeracoes = valorInformado;
      valorInformadoCorretamente = true;
      cout << "Otimo, o numero de geracoes escolhida foi: " << numeroGeracoes << "!" << endl;
    }
    else
    {
      cout << "Desculpe, valor informado foi incorreto!" << endl;
    }
  }

  return numeroGeracoes;
}

void gerarPopulacaoInicial(Populacao listaPopulacao[], int tamanhoPopulacao)
{
  srand(time(0));

  for (int i = 0; i < tamanhoPopulacao; i++)
  {
    // Sorteando valores em um intervalo limitado
    listaPopulacao[i].individuo = -2000 + (rand() % 4001);
  }
}

CoeficientesEquacao obterCoeficientesEquacao()
{
  CoeficientesEquacao coeficientesEquacao;
  int valorInformado;
  cout << "A seguinte equacao sera utilizada para avaliar os individuos gerados: " << endl;
  cout << "a*x^5 + b*x^4 + c*x^3 + d*x^2 + e*x + f" << endl;

  cout << "Informe o valor de a, o valor deve ser diferente de zero: ";
  cin >> valorInformado;

  while (valorInformado == 0)
  {
    cout << "Valor para 'a' incorreto, digite novamente um valor diferente de zero: ";
    cin >> valorInformado;
  }

  coeficientesEquacao.a = valorInformado;

  cout << "Informe o valor de b: ";
  cin >> coeficientesEquacao.b;

  cout << "Informe o valor de c: ";
  cin >> coeficientesEquacao.c;

  cout << "Informe o valor de d: ";
  cin >> coeficientesEquacao.d;

  cout << "Informe o valor de e: ";
  cin >> coeficientesEquacao.e;

  cout << "Informe o valor de f: ";
  cin >> coeficientesEquacao.f;

  return coeficientesEquacao;
}

void obterResultadosEquacaoDosIndividuos(Populacao populacao[], CoeficientesEquacao coeficiente, int tamanhoPopulacao)
{
  for (int i = 0; i < tamanhoPopulacao; i++)
  {
    // Caso o individuo seja menor que -2000 ou maior que 2000, será substituído por um valor aleatório para não ultrapassar memória
    if (populacao[i].individuo < -2000 || populacao[i].individuo > 2000)
    {
      srand(time(0));
      populacao[i].individuo = -2000 + (rand() % 4001);
    }

    int x = populacao[i].individuo;
    populacao[i].resultadoEquacao = (coeficiente.a * pow(x, 5)) + (coeficiente.b * pow(x, 4)) + (coeficiente.c * pow(x, 3)) +
                                    (coeficiente.d * pow(x, 2)) + (coeficiente.e * x) + coeficiente.f;

    if (populacao[i].resultadoEquacao >= 0)
    {
      populacao[i].moduloResultadoEquacao = populacao[i].resultadoEquacao;
    }
    else
    {
      populacao[i].moduloResultadoEquacao = populacao[i].resultadoEquacao * -1;
    }
  }
}

void ordenarPopulacao(Populacao populacao[], int tamanhoPopulacao)
{
  bool foiFeitaAlteracaoDePosicao = true;
  Populacao populacaoTemporaria;

  while (foiFeitaAlteracaoDePosicao)
  {
    foiFeitaAlteracaoDePosicao = false;

    for (int i = 0; i < (tamanhoPopulacao - 1); i++)
    {
      // População é ordenada a partir do módulo do resultado da equação
      if (populacao[i].moduloResultadoEquacao > populacao[i + 1].moduloResultadoEquacao)
      {
        populacaoTemporaria = populacao[i];
        populacao[i] = populacao[i + 1];
        populacao[i + 1] = populacaoTemporaria;
        foiFeitaAlteracaoDePosicao = true;
      }
    }
  }
}

bool avaliarPopulacao(int resultadoEquacao)
{
  // Intervalo para aceite do indivíduo é entre -1 e 1
  return (resultadoEquacao >= -1 && resultadoEquacao <= 1);
}

void selecaoCruzamentoEMutacaoIndividuos(Populacao populacao[], Populacao populacaoSelecionada[], Populacao novaPopulacao[], InformacoesIniciais informacoesIniciais)
{
  selecionarPopulacao(populacao, populacaoSelecionada, informacoesIniciais.tamanhoPopulacao);
  cruzamentoPopulacao(novaPopulacao, populacaoSelecionada, informacoesIniciais);
  preencherRestanteNovaPopulacaoComGenitores(novaPopulacao, populacao, informacoesIniciais.tamanhoPopulacao);
  mutacaoPopulacao(novaPopulacao, informacoesIniciais);
}

void selecionarPopulacao(Populacao populacao[], Populacao populacaoSelecionada[], int tamanhoPopulacao)
{
  int metadePopulacao = (tamanhoPopulacao / 2);
  if (metadePopulacao % 2 != 0)
  {
    // Caso metade da população seja ímpar, será acrescido 1 indivíduo na população selecionada. Tal verificação e soma será feita em demais partes do código.
    metadePopulacao++;
  }

  for (int i = 0; i < metadePopulacao; i++)
  {
    populacaoSelecionada[i] = populacao[i];
  }
}

void cruzamentoPopulacao(Populacao novaPopulacao[], Populacao populacaoSelecionada[], InformacoesIniciais informacoesIniciais)
{
  int quantidadeBitsPrimeiraParcelaGenoma = informacoesIniciais.taxaCrossover * 32;
  int quantidadeBitsSegundaParcelaGenoma = 32 - quantidadeBitsPrimeiraParcelaGenoma;
  int metadePopulacao = (informacoesIniciais.tamanhoPopulacao / 2);
  if (metadePopulacao % 2 != 0)
  {
    metadePopulacao++;
  }

  converterValoresNegativosEmPositivosPopulacaoSelecionada(populacaoSelecionada, informacoesIniciais.tamanhoPopulacao);

  for (int i = 0; i < metadePopulacao; i += 2)
  {
    int primeiraParcelaPrimeiroValor = retornarPrimeiraParcelaGenoma(populacaoSelecionada[i].individuo, quantidadeBitsPrimeiraParcelaGenoma);
    int segundaParcelaPrimeiroValor = retornarSegundaParcelaGenoma(populacaoSelecionada[i].individuo, quantidadeBitsPrimeiraParcelaGenoma, quantidadeBitsSegundaParcelaGenoma);

    int primeiraParcelaSegundoValor = retornarPrimeiraParcelaGenoma(populacaoSelecionada[i + 1].individuo, quantidadeBitsPrimeiraParcelaGenoma);
    int segundaParcelaSegundoValor = retornarSegundaParcelaGenoma(populacaoSelecionada[i + 1].individuo, quantidadeBitsPrimeiraParcelaGenoma, quantidadeBitsSegundaParcelaGenoma);

    novaPopulacao[i].individuo = retornarNovoIndividuoCruzamento(primeiraParcelaPrimeiroValor, segundaParcelaSegundoValor, quantidadeBitsPrimeiraParcelaGenoma);
    novaPopulacao[i + 1].individuo = retornarNovoIndividuoCruzamento(primeiraParcelaSegundoValor, segundaParcelaPrimeiroValor, quantidadeBitsPrimeiraParcelaGenoma);
  }
}

void converterValoresNegativosEmPositivosPopulacaoSelecionada(Populacao populacaoSelecionada[], int tamanhoPopulacao)
{
  int metadePopulacao = (tamanhoPopulacao / 2);
  if (metadePopulacao % 2 != 0)
  {
    metadePopulacao++;
  }

  for (int i = 0; i < metadePopulacao; i++)
  {
    if (populacaoSelecionada[i].individuo < 0)
    {
      populacaoSelecionada[i].individuo = (populacaoSelecionada[i].individuo * (-1));
    }
  }
}

int retornarPrimeiraParcelaGenoma(int valor, int quantidadeBitsPrimeiraParcelaGenoma)
{
  return (valor >> quantidadeBitsPrimeiraParcelaGenoma);
}

int retornarSegundaParcelaGenoma(int valor, int quantidadeBitsPrimeiraParcelaGenoma, int quantidadeBitsSegundaParcelaGenoma)
{
  valor = valor << quantidadeBitsPrimeiraParcelaGenoma;

  if (valor < 0)
  {
    // Como o individuo possui valor negativo, converteremos o dígito de sinal para 0 por conta do deslocamento:
    int mascaraParaZerarBitDeSinal = ~(1 << (31));
    int valorComBitZerado = valor & mascaraParaZerarBitDeSinal;
    valor = valorComBitZerado >> quantidadeBitsPrimeiraParcelaGenoma;

    // Agora que o valor foi deslocado para a direita, retornaremos o 1 que havíamos mudado para 0:
    int mascaraParaRetornarValorBit = (1 << (quantidadeBitsSegundaParcelaGenoma - 1));
    valor = valor | mascaraParaRetornarValorBit;
  }
  else
  {
    // Para valores positivos basta fazer o deslocamento
    valor = valor >> quantidadeBitsPrimeiraParcelaGenoma;
  }

  return valor;
}

int retornarNovoIndividuoCruzamento(int primeiraParcelaGenoma, int segundaParcelaGenoma, int quantidadeBitsPrimeiraParcelaGenoma)
{
  int afastarPrimeiraParcela = primeiraParcelaGenoma << quantidadeBitsPrimeiraParcelaGenoma;
  return (afastarPrimeiraParcela + segundaParcelaGenoma);
}

void preencherRestanteNovaPopulacaoComGenitores(Populacao novaPopulacao[], Populacao populacao[], int tamanhoPopulacao)
{
  int metadePopulacao = (tamanhoPopulacao / 2);
  if (metadePopulacao % 2 != 0)
  {
    metadePopulacao++;
  }

  for (int i = metadePopulacao; i < tamanhoPopulacao; i++)
  {
    novaPopulacao[i] = populacao[i];
  }
}

void mutacaoPopulacao(Populacao novaPopulacao[], InformacoesIniciais informacoesIniciais)
{
  srand(time(0));
  int chanceDeMutacao = 0 + (rand() % 101);
  int taxaMutacaoPorcentagem = informacoesIniciais.taxaMutacao * 100;

  if (chanceDeMutacao <= taxaMutacaoPorcentagem)
  {
    // Limitando os bits que podem sofrer mutacao, para que não sejam gerados numeros muito maiores que 2000, os quais serão posteriormente substituidos por conta da equacao
    int posicaoBitQueSeraAlterado = 0 + (rand() % 11);
    int posicaoIndividuoQueSeraAlterado = 0 + (rand() % informacoesIniciais.tamanhoPopulacao);
    int mascaraParaRetornarValorBit = (1 << posicaoBitQueSeraAlterado);
    novaPopulacao[posicaoIndividuoQueSeraAlterado].individuo = novaPopulacao[posicaoIndividuoQueSeraAlterado].individuo ^ mascaraParaRetornarValorBit;
  }
}