# Lista 02 - Guia de estudo dos algoritmos

Este material acompanha os codigos em C da pasta `c/`. A ideia aqui nao e substituir o codigo, mas te dar um mapa mental para bater o olho, entender o fluxo e depois rodar.

Organizacao:

- `c/gulosos`: exercicios 1 a 7.
- `c/programacao_dinamica`: exercicios 8 a 15.

Para compilar tudo:

```bash
bash compilar_todos.sh
```

Para abrir o menu dos exercicios:

```bash
./build/menu_lista02
```

O menu mostra a lista e executa o exercicio escolhido. Para abrir outro exercicio, rode o menu de novo.

## 1. Problema do troco - guloso

Arquivo: `c/gulosos/01_troco_guloso.c`

O problema pede a menor quantidade de notas e moedas para formar um valor. A estrategia gulosa funciona aqui porque o sistema de notas/moedas usado e bem comportado: sempre vale a pena pegar a maior nota ou moeda possivel antes das menores.

O primeiro detalhe importante e converter o dinheiro para centavos:

```c
int centavos_restantes = (int) round(valor * 100.0);
```

Isso evita erro tipo `0.10 + 0.20` virar algo como `0.30000000004`. Depois o codigo percorre as notas:

```c
int quantidade = centavos_restantes / notas[posicao];
centavos_restantes %= notas[posicao];
```

A divisao diz quantas notas daquele valor cabem. O resto (`%`) vira o valor que ainda falta decompor.

Exemplo:

```text
Valor: 576.73
```

O fluxo e: pega 5 notas de 100, sobra 76.73; pega 1 de 50, sobra 26.73; e assim por diante.

## 2. Problema dos selos

Arquivo: `c/gulosos/02_selos.c`

Temos selos de 3 e 5 centavos. Como queremos o menor numero de selos, o codigo tenta usar o maximo possivel de selos de 5:

```c
int selos_de_5 = taxa / 5;
```

Depois verifica se o restante pode ser preenchido com selos de 3:

```c
if (restante % 3 == 0) {
    int selos_de_3 = restante / 3;
}
```

Se nao der, reduz um selo de 5 e tenta de novo:

```c
selos_de_5--;
```

Exemplo:

```text
Taxa em centavos: 19
```

Comeca tentando 3 selos de 5, sobra 4, nao fecha com 3. Depois tenta 2 selos de 5, sobra 9, fecha com 3 selos de 3.

## 3. Arquivos digitais

Arquivo: `c/gulosos/03_arquivos_digitais.c`

Queremos copiar a maior quantidade de arquivos para um pendrive. Para maximizar quantidade, nao importa primeiro o valor total em MB, importa caber o maior numero de itens. Por isso o guloso ordena os arquivos do menor para o maior:

```c
qsort(tamanhos, quantidade_arquivos, sizeof(int), comparar_inteiros);
```

Depois vai somando enquanto couber:

```c
if (espaco_usado + tamanhos[posicao] <= capacidade) {
    espaco_usado += tamanhos[posicao];
    arquivos_copiados++;
}
```

Quando o menor arquivo restante ja nao cabe, nenhum dos maiores vai caber.

Exemplo:

```text
Quantidade de arquivos e capacidade: 5 10
Tamanhos dos arquivos: 8 1 4 2 3
```

Ordenado: `1, 2, 3, 4, 8`. Cabem `1 + 2 + 3 + 4 = 10`, entao copia 4 arquivos.

Complexidade: `O(n log n)`, por causa da ordenacao.

## 4. Menor numero de paradas em viagem

Arquivo: `c/gulosos/04_paradas_viagem.c`

A ideia e sempre ir o mais longe possivel antes de abastecer. Se voce parar antes sem necessidade, nao ganha nada: so aumenta o numero de paradas.

O trecho central procura o posto mais distante dentro da autonomia atual:

```c
while (proximo_posto < quantidade_postos &&
       postos[proximo_posto] <= posicao_atual + autonomia) {
    melhor_alcance = postos[proximo_posto];
    proximo_posto++;
}
```

Depois a viagem continua desse posto:

```c
posicao_atual = melhor_alcance;
paradas++;
```

Se nenhum posto novo for alcancado, a viagem e impossivel:

```c
if (melhor_alcance == posicao_atual) {
    return -1;
}
```

Exemplo:

```text
Quantidade de postos, autonomia e distancia destino: 4 100 350
Distancias dos postos: 80 150 240 300
```

Saindo do km 0, o mais longe que cabe e 80. Depois 150, depois 240, depois 300, e dali chega no destino.

Complexidade: `O(n)`.

## 5. Mochila fracionaria

Arquivo: `c/gulosos/05_mochila_fracionaria.c`

Como podemos pegar fracao de objeto, o criterio certo e o valor por peso:

```c
double densidade_a = objeto_a->valor / objeto_a->peso;
```

O codigo ordena da maior densidade para a menor. Depois, para cada objeto:

```c
if (objetos[posicao].peso <= capacidade) {
    objetos[posicao].fracao = 1.0;
    capacidade -= objetos[posicao].peso;
    valor_total += objetos[posicao].valor;
} else {
    objetos[posicao].fracao = capacidade / objetos[posicao].peso;
    valor_total += objetos[posicao].valor * objetos[posicao].fracao;
    capacidade = 0.0;
}
```

Ou seja: se couber inteiro, pega inteiro. Se nao couber, pega so a parte que falta para encher a mochila.

Exemplo da lista:

```text
Quantidade de objetos e capacidade: 5 50
Peso e valor do objeto 1: 40 840
Peso e valor do objeto 2: 30 600
Peso e valor do objeto 3: 20 400
Peso e valor do objeto 4: 10 100
Peso e valor do objeto 5: 20 30
```

O objeto 1 tem densidade `21`, o objeto 2 tem `20`, o objeto 3 tem `20`, o objeto 4 tem `10`, o objeto 5 tem `1.5`. O algoritmo pega os mais densos primeiro.

Complexidade: `O(n log n)`.

## 6. Dieta

Arquivo: `c/gulosos/06_dieta.c`

Este exercicio foi resolvido como uma mochila fracionaria: calorias sao o limite, proteinas sao o valor que queremos maximizar.

O criterio e proteina por caloria:

```c
double razao_a = alimento_a->proteinas / alimento_a->calorias;
```

Depois o fluxo e igual ao da mochila fracionaria:

```c
if (alimentos[posicao].calorias <= limite_calorias) {
    alimentos[posicao].fracao = 1.0;
} else {
    alimentos[posicao].fracao = limite_calorias / alimentos[posicao].calorias;
}
```

Exemplo:

```text
Quantidade de alimentos e limite de calorias: 4 500
Calorias e proteinas do alimento 1: 300 20
Calorias e proteinas do alimento 2: 200 18
Calorias e proteinas do alimento 3: 100 8
Calorias e proteinas do alimento 4: 400 35
```

O algoritmo favorece alimentos com mais proteina por caloria, ate bater o limite.

## 7. Selecao de atividades

Arquivo: `c/gulosos/07_selecao_atividades.c`

Queremos escolher o maior numero de atividades sem conflito. A escolha gulosa e pegar primeiro a atividade que termina mais cedo:

```c
qsort(atividades, quantidade, sizeof(Atividade), comparar_por_termino);
```

Depois escolhe a proxima que comeca depois que a ultima escolhida terminou:

```c
if (atividades[posicao].inicio >= ultimo_termino) {
    ultimo_termino = atividades[posicao].termino;
}
```

Por que isso funciona: terminar cedo deixa o maior espaco possivel para as atividades seguintes.

Exemplo:

```text
Quantidade de atividades: 6
Inicio e termino da atividade 1: 1 4
Inicio e termino da atividade 2: 3 5
Inicio e termino da atividade 3: 0 6
Inicio e termino da atividade 4: 5 7
Inicio e termino da atividade 5: 3 9
Inicio e termino da atividade 6: 5 9
```

Complexidade: `O(n log n)`.

## 8. Subindo escadas

Arquivo: `c/programacao_dinamica/08_subindo_escadas.c`

Para chegar no degrau `n`, voce pode vir de:

- `n - 1`, dando um passo de 1.
- `n - 2`, dando um passo de 2.

Por isso:

```c
formas[n] = formas[n - 1] + formas[n - 2]
```

No codigo, nao guardamos o vetor inteiro. So as duas ultimas respostas:

```c
int formas_penultimo = 1;
int formas_ultimo = 2;

for (int altura = 3; altura <= degraus; altura++) {
    int formas_atual = formas_penultimo + formas_ultimo;
    formas_penultimo = formas_ultimo;
    formas_ultimo = formas_atual;
}
```

Exemplo:

```text
Numero de degraus: 5
```

Resultado: `8`.

## 9. Quadrados perfeitos

Arquivo: `c/programacao_dinamica/09_quadrados_perfeitos.c`

Queremos o menor numero de quadrados que soma `n`. A tabela `minimo[valor]` guarda a melhor resposta para cada valor ate `n`.

Para cada `valor`, o codigo testa todos os quadrados que poderiam ser a ultima parcela:

```c
for (int base = 1; base * base <= valor; base++) {
    int quadrado = base * base;
    int candidato = minimo[valor - quadrado] + 1;
}
```

Exemplo para `13`:

- se usar `1`, sobra `12`.
- se usar `4`, sobra `9`.
- se usar `9`, sobra `4`.

Como `13 = 9 + 4`, a resposta e `2`.

Exemplo:

```text
Numero: 13
```

Complexidade: `O(n * sqrt(n))`.

## 10. LIS - subsequencia crescente mais longa

Arquivo: `c/programacao_dinamica/10_lis.c`

LIS e a maior subsequencia crescente, sem precisar ser contigua.

Exemplo:

```text
10 9 2 5 3 7
```

Uma LIS possivel e `2, 5, 7`, tamanho `3`.

### Versao recursiva

Em cada posicao, o codigo decide entre pegar ou nao pegar o elemento atual:

```c
int sem_atual = lis_recursiva_aux(..., posicao + 1, anterior);

if (anterior == -1 || sequencia[posicao] > sequencia[anterior]) {
    int com_atual = 1 + lis_recursiva_aux(..., posicao + 1, posicao);
}
```

Essa versao e boa para entender, mas recalcula muita coisa.

### Versao top-down

Usa memoizacao. O estado e:

```text
(posicao atual, indice do ultimo elemento escolhido)
```

Como `anterior` pode ser `-1`, o codigo desloca a coluna:

```c
int coluna_anterior = anterior + 1;
```

Assim `-1` vira coluna `0`.

### Versao bottom-up

Aqui `tamanho_lis[atual]` significa: maior LIS que termina exatamente no elemento `atual`.

```c
if (sequencia[anterior] < sequencia[atual] &&
    tamanho_lis[anterior] + 1 > tamanho_lis[atual]) {
    tamanho_lis[atual] = tamanho_lis[anterior] + 1;
}
```

Ou seja: se um elemento anterior e menor, ele pode vir antes do atual.

Exemplo para rodar:

```text
Quantidade de numeros: 6
Sequencia: 10 9 2 5 3 7
```

## 11. Troco com programacao dinamica

Arquivo: `c/programacao_dinamica/11_troco_pd.c`

Agora o conjunto de moedas pode ser qualquer um. Por isso o guloso nem sempre funciona. Exemplo: moedas `1, 5, 6`, troco `10`. Guloso pegaria `6 + 1 + 1 + 1 + 1`, mas o melhor e `5 + 5`.

### Versao recursiva

Para resolver `valor`, tenta usar cada moeda como primeira escolha:

```c
int candidato = 1 + troco_recursivo(moedas, quantidade_moedas, valor - moedas[posicao]);
```

### Versao top-down

Guarda a resposta de cada valor:

```c
if (memo[valor] != -1) {
    return memo[valor];
}
```

Assim `troco(7)`, por exemplo, nao e recalculado varias vezes.

### Versao bottom-up

Constroi do valor `1` ate o valor final:

```c
for (int total = 1; total <= valor; total++) {
    minimo[total] = INT_MAX / 2;
}
```

Para cada total, testa cada moeda:

```c
int candidato = minimo[total - moedas[posicao]] + 1;
```

Exemplo:

```text
Quantidade de moedas e valor do troco: 3 10
Valores das moedas: 1 5 6
```

Resultado correto: `2`.

## 12. Mochila 0/1

Arquivo: `c/programacao_dinamica/12_mochila_01.c`

Aqui nao pode pegar fracao. Cada item entra inteiro ou fica fora.

### Versao recursiva

O ultimo item considerado tem duas possibilidades:

```c
int sem_item = mochila01_recursiva(..., quantidade - 1, capacidade);
int com_item = valores[ultimo] +
               mochila01_recursiva(..., quantidade - 1, capacidade - pesos[ultimo]);
```

Se o item nao cabe, nao existe a escolha `com_item`:

```c
if (pesos[ultimo] > capacidade) {
    return mochila01_recursiva(...);
}
```

### Versao top-down

O estado e:

```text
(quantidade de itens considerados, capacidade restante)
```

O `memo[quantidade][capacidade]` guarda a melhor resposta desse estado.

### Versao bottom-up

A tabela `melhor[itens][limite]` significa:

```text
melhor valor usando os primeiros itens com capacidade limite
```

O trecho-chave compara colocar ou nao o item atual:

```c
melhor[itens][limite] = maior(com_item, sem_item);
```

Exemplo:

```text
Quantidade de itens e capacidade: 4 7
Peso e valor do item 1: 1 1
Peso e valor do item 2: 3 4
Peso e valor do item 3: 4 5
Peso e valor do item 4: 5 7
```

## 13. Multiplicacao de matrizes

Arquivo: `c/programacao_dinamica/13_multiplicacao_matrizes.c`

O problema nao e multiplicar as matrizes, mas escolher a melhor ordem de multiplicacao.

Se temos `A1 x A2 x A3 x A4`, podemos dividir a cadeia em varios pontos:

```text
(A1) x (A2 x A3 x A4)
(A1 x A2) x (A3 x A4)
(A1 x A2 x A3) x (A4)
```

O codigo testa todos os pontos de divisao:

```c
for (int divisao = inicio; divisao < fim; divisao++) {
    int custo = custo_esquerda + custo_direita + custo_multiplicar;
}
```

O custo de multiplicar duas partes usa as dimensoes:

```c
dimensoes[inicio - 1] * dimensoes[divisao] * dimensoes[fim]
```

### Bottom-up e parentizacao

A versao bottom-up tambem guarda onde foi o melhor corte:

```c
divisao[inicio][fim] = corte;
```

Depois `imprimir_parentizacao` usa essa tabela para reconstruir a ordem otima.

Exemplo da lista:

```text
Numero de matrizes: 4
Dimensoes p0 ate pn: 200 2 30 20 5
```

Resultado esperado:

```text
3400
(A1 x ((A2 x A3) x A4))
```

## 14. LCS - subsequencia comum maxima

Arquivo: `c/programacao_dinamica/14_lcs.c`

LCS procura a maior subsequencia que aparece em duas sequencias.

Exemplo:

```text
X = ATCTGAT
Y = TGCATTA
```

### Recursiva

Se os ultimos caracteres sao iguais, eles entram na resposta:

```c
if (texto_a[tamanho_a - 1] == texto_b[tamanho_b - 1]) {
    return 1 + lcs_recursiva(..., tamanho_a - 1, tamanho_b - 1);
}
```

Se sao diferentes, tenta remover um caractere de uma das strings:

```c
int remover_a = lcs_recursiva(..., tamanho_a - 1, tamanho_b);
int remover_b = lcs_recursiva(..., tamanho_a, tamanho_b - 1);
```

### Top-down

O estado e:

```text
(tamanho do prefixo de A, tamanho do prefixo de B)
```

`memo[tamanho_a][tamanho_b]` guarda a LCS desses prefixos.

### Bottom-up com reconstrucao

A tabela e preenchida comparando prefixos:

```c
if (texto_a[linha - 1] == texto_b[coluna - 1]) {
    tamanho_lcs[linha][coluna] = 1 + tamanho_lcs[linha - 1][coluna - 1];
}
```

Depois o codigo volta pela tabela para montar uma subsequencia:

```c
resposta[--posicao_resposta] = texto_a[linha - 1];
```

Observacao: pode existir mais de uma LCS correta. Entao a string impressa pode ser diferente da do enunciado, mas deve ter o mesmo tamanho maximo.

Exemplo:

```text
Primeira sequencia: ATCTGAT
Segunda sequencia: TGCATTA
```

## 15. Corte das hastes de aco

Arquivo: `c/programacao_dinamica/15_corte_hastes.c`

Temos uma haste de tamanho `n` e precos para cada tamanho. A pergunta e: cortar ou vender inteira? E se cortar, onde?

### Recursiva

O codigo tenta todos os tamanhos possiveis para o primeiro pedaco:

```c
for (int primeiro_corte = 1; primeiro_corte <= tamanho; primeiro_corte++) {
    int receita = precos[primeiro_corte] +
                  corte_haste_recursivo(precos, tamanho - primeiro_corte);
}
```

### Top-down

Guarda a melhor receita para cada tamanho:

```c
if (memo[tamanho] != -1) {
    return memo[tamanho];
}
```

### Bottom-up com cortes

Resolve hastes pequenas antes das maiores:

```c
for (int comprimento = 1; comprimento <= tamanho; comprimento++) {
    for (int corte = 1; corte <= comprimento; corte++) {
        int receita = precos[corte] + melhor_receita[comprimento - corte];
    }
}
```

Quando acha uma receita melhor, salva o primeiro corte:

```c
primeiro_corte[comprimento] = corte;
```

Depois `imprimir_cortes` usa isso para mostrar os pedacos escolhidos.

Exemplo:

```text
Tamanho da haste: 8
Precos de 1 ate 8: 1 5 8 9 10 17 17 20
```

Uma boa resposta e receita `22`, com cortes `2 6`.

## Para estudar sem se perder

Sugestao de ordem:

1. Rode o exercicio pelo menu.
2. Use exatamente a entrada do exemplo deste arquivo.
3. Abra o `.c` correspondente e procure o trecho-chave mostrado aqui.
4. Altere um numero pequeno da entrada e rode de novo.

Nos exercicios com tres versoes, compare as respostas. Elas devem bater. A diferenca e o caminho:

- Recursiva: mostra a ideia pura, mas fica lenta.
- Top-down: mesma ideia, com memoria.
- Bottom-up: monta a resposta do menor caso para o maior.

