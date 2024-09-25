# Algoritmo Genético desenvolvido para a disciplina de Técnicas de Programação II do Centro Universitário Barão de Mauá

Aluno responsável pelo atual código:
- Caio Salvador Noboa - 2201926

## Introdução
O presente Algoritmo Genético contempla a seleção de indivíduos (números inteiros) a partir de uma equação como metáfora ao que é feito em um programa de melhoramento genético.
A partir de uma equação são selecionados indivíduos de uma população. Com manipulação de bits há o cruzamento entre indivíduos dessa população selecionada. Poderá ocorrer mutação, isto é, troca de bit alterando o valor numérico. Tais processos ocorrerão por determinada quantidade de gerações.
Caso haja em alguma geração um indivíduo que tenha características de interesse, o código irá parar e exibir tal indivíduo. Caso contrário, o código percorrerá todas as gerações e exibirá o indivíduo que mais chegou perto de possuir as características de interesse.

## Inicialização
Uma possível maneira de inicializar o código:
No prompt de comando, na pasta que contém o arquivo driver.cpp rode:
- `g++ driver.cpp -o algoritmoGenetico.exe`
- `./algoritmoGenetico.exe`

## Observações sobre o código
A seguinte equação é utilizada para avaliar os individuos gerados: `a*x^5 + b*x^4 + c*x^3 + d*x^2 + e*x + f`. O resultado da equação será utilizado para ordenar e selecionar indivíduos;

O presente código foi construído a partir de vetores estáticos;

Durante a seleção será constituída uma população selecionada com 50% de indivíduos da original (ou 50% mais 1 indivíduo caso metade da população seja ímpar);

A partir da população selecionada (50% da original (ou 50% mais 1)), haverá cruzamento. Dois indivíduos gerarão outros dois. Dessa forma, a nova população será constituída pelos originados do cruzamento e para voltar ao tamanho da população original, indivíduos da população selecionada são acrescentados à essa nova população;

Os bits que podem sofrer mutacao foram limitados para que apenas 11 bits (posicao 0 a 10) menos significativos possam ser alterados, para que não sejam gerados numeros muito maiores que 2000, os quais serão posteriormente substituidos por conta de limite de memória do resultado da equação;

O intervalo para aceite do indivíduo é que o resultado da equação esteja entre -1 e 1;

A população é ordenada a partir do módulo do resultado da equação, que indicará quão distante o indivíduo está de 0, que é a característica de interesse;

Antes da equação ser calculada será verificado o valor do indivíduo. Caso o individuo seja menor que -2000 ou maior que 2000, será substituído por um valor aleatório para não ultrapassar memória. Tal restrição também é aplicada no sorteio da população original;

Como o melhor indivíduo de cada geração é armazenado, o maior número aceito de gerações é 1000;

O tamanho da população é limitado a 10, 100 ou 1000 indivíduos.

## Casos de uso
### Primeiro caso
Informações:
Tamanho da população: 10;
Taxa de crossover: 0.8;
Taxa de mutação: 0.9;
Número de gerações: 50;
Coeficientes, a, b, c, d, e, f, respectivamente: 1, 2, 3, 4, 5, 6;
Resultado:
"Todas as geracoes foram percorridas sem encontrar um individuo que atendesse adequadamente os criterios de selecao.
O melhor individuo encontrado foi na geracao 5, com valor 1, cujo valor da equacao foi: 21"

### Segundo caso
Informações:
Tamanho da população: 100;
Taxa de crossover: 0.5;
Taxa de mutação: 0.5;
Número de gerações: 100;
Coeficientes, a, b, c, d, e, f, respectivamente: 1, 0, 0, 0, 0, 250;
Resultado:
"Todas as geracoes foram percorridas sem encontrar um individuo que atendesse adequadamente os criterios de selecao.
O melhor individuo encontrado foi na geracao 3, com valor -2, cujo valor da equacao foi: 218"

### Terceiro caso
Informações:
Tamanho da população: 1000;
Taxa de crossover: 0.4;
Taxa de mutação: 0.7;
Número de gerações: 250;
Coeficientes, a, b, c, d, e, f, respectivamente: 1, 2, 3, 4, 50, 100;
Resultado:
"Todas as geracoes foram percorridas sem encontrar um individuo que atendesse adequadamente os criterios de selecao.
O melhor individuo encontrado foi na geracao 159, com valor 0, cujo valor da equacao foi: 100"

### Quarto caso
Informações:
Tamanho da população: 1000;
Taxa de crossover: 0.7;
Taxa de mutação: 0.99;
Número de gerações: 1000;
Coeficientes, a, b, c, d, e, f, respectivamente: 1, 2, 3, 4, 5, -115;
Resultado:
"O melhor individuo foi encontrado na geracao 2, com valor 2, cujo valor da equacao foi: -1"
