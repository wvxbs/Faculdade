# Atividade avaliativa — Pré-processamento em PLN (10 textos)

**Turma:** 07N (atividade individual por exceção)

**Nomes em ordem alfabética**

**Nome 1:** Gabriel Ferreira  **RA 1:** 10442043











## Orientações

Informe dez textos, um por característica solicitada. Abaixo estão registradas as saídas
do programa. Examine-as, responda às questões de cada texto e entregue este arquivo.
As saídas são produzidas pelo código; a interpretação deve ser realizada pelo estudante.

**Atenção:** a lista de stopwords e a identificação de emojis são simplificadas.
A remoção de pontuação pode alterar significado; neste código, números são preservados.

## Texto 01 — Maiúsculas e minúsculas

**Resultados obtidos na execução:**

- **Texto original:** `'Na SEMANA passada estudei IA, mas HOJE revisei PLN.'`
- **1. Normalização:** `'na semana passada estudei ia, mas hoje revisei pln.'`
- **2. Expansão:** `'na semana passada estudei ia, mas hoje revisei pln.'`
- **3. Limpeza:** `'na semana passada estudei ia mas hoje revisei pln'`
- **4. Tokens:** `['na', 'semana', 'passada', 'estudei', 'ia', 'mas', 'hoje', 'revisei', 'pln']`
- **5. Sem stopwords:** `['semana', 'passada', 'estudei', 'ia', 'mas', 'hoje', 'revisei', 'pln']`
- **6. Emojis:** `[]`
- **Número de tokens (antes → depois das stopwords):** 9 → 8

**Questão 1:** Quais diferenças apareceram entre a mensagem original e a versão normalizada?

**Resposta:**

As letras maiúsculas viraram minúsculas e os espaços foram padronizados; os acentos permaneceram. A limpeza retirou a vírgula e o ponto.

## Texto 02 — Gírias e abreviações

**Resultados obtidos na execução:**

- **Texto original:** `'vc viu a msg? pq eu n recebi nada hj, vlw!'`
- **1. Normalização:** `'vc viu a msg? pq eu n recebi nada hj, vlw!'`
- **2. Expansão:** `'você viu a mensagem? porque eu não recebi nada hoje, valeu!'`
- **3. Limpeza:** `'você viu a mensagem porque eu não recebi nada hoje valeu'`
- **4. Tokens:** `['você', 'viu', 'a', 'mensagem', 'porque', 'eu', 'não', 'recebi', 'nada', 'hoje', 'valeu']`
- **5. Sem stopwords:** `['você', 'viu', 'mensagem', 'porque', 'eu', 'não', 'recebi', 'nada', 'hoje', 'valeu']`
- **6. Emojis:** `[]`
- **Número de tokens (antes → depois das stopwords):** 11 → 10

**Questão 2:** Quais abreviações foram expandidas? Alguma deveria ter sido expandida e não foi?

**Resposta:**

vc → você, msg → mensagem, pq → porque, n → não, hj → hoje e vlw → valeu. Nenhuma das abreviações cadastradas neste texto ficou sem expansão.

## Texto 03 — Emojis e sentimento

**Resultados obtidos na execução:**

- **Texto original:** `'A explicação foi ótima 🤩, porém o exercício me deixou confuso 😕.'`
- **1. Normalização:** `'a explicação foi ótima 🤩, porém o exercício me deixou confuso 😕.'`
- **2. Expansão:** `'a explicação foi ótima 🤩, porém o exercício me deixou confuso 😕.'`
- **3. Limpeza:** `'a explicação foi ótima porém o exercício me deixou confuso'`
- **4. Tokens:** `['a', 'explicação', 'foi', 'ótima', 'porém', 'o', 'exercício', 'me', 'deixou', 'confuso']`
- **5. Sem stopwords:** `['explicação', 'ótima', 'porém', 'exercício', 'me', 'deixou', 'confuso']`
- **6. Emojis:** `['🤩', '😕']`
- **Número de tokens (antes → depois das stopwords):** 10 → 7

**Questão 3:** Quais emojis foram identificados? Que informação emocional pode se perder na limpeza?

**Resposta:**

Foram detectados 🤩 e 😕. A limpeza removeu os dois; sem eles, desaparecem pistas de entusiasmo e confusão que ajudam a interpretar o sentimento misto da frase.

## Texto 04 — URL e menção

**Resultados obtidos na execução:**

- **Texto original:** `'Consulte https://universidade.example/aula e avise @gabriel sobre o prazo.'`
- **1. Normalização:** `'consulte https://universidade.example/aula e avise @gabriel sobre o prazo.'`
- **2. Expansão:** `'consulte https://universidade.example/aula e avise @gabriel sobre o prazo.'`
- **3. Limpeza:** `'consulte e avise sobre o prazo'`
- **4. Tokens:** `['consulte', 'e', 'avise', 'sobre', 'o', 'prazo']`
- **5. Sem stopwords:** `['consulte', 'avise', 'sobre', 'prazo']`
- **6. Emojis:** `[]`
- **Número de tokens (antes → depois das stopwords):** 6 → 4

**Questão 4:** Quais informações da URL e da menção desapareceram? Isso seria sempre desejável?

**Resposta:**

O endereço e a menção @gabriel desapareceram por completo, inclusive a identificação do destino e da pessoa. Isso depende da tarefa: numa análise de redes ou de fontes, essas informações seriam úteis.

## Texto 05 — Hashtags e pontuação

**Resultados obtidos na execução:**

- **Texto original:** `'#AprendizadoDeMaquina: consegui terminar!!! E você???'`
- **1. Normalização:** `'#aprendizadodemaquina: consegui terminar!!! e você???'`
- **2. Expansão:** `'#aprendizadodemaquina: consegui terminar!!! e você???'`
- **3. Limpeza:** `'aprendizadodemaquina consegui terminar e você'`
- **4. Tokens:** `['aprendizadodemaquina', 'consegui', 'terminar', 'e', 'você']`
- **5. Sem stopwords:** `['aprendizadodemaquina', 'consegui', 'terminar', 'você']`
- **6. Emojis:** `[]`
- **Número de tokens (antes → depois das stopwords):** 5 → 4

**Questão 5:** Como as hashtags e a pontuação foram tratadas? A palavra da hashtag foi mantida?

**Resposta:**

A limpeza removeu #, dois-pontos, exclamações e interrogações. A palavra AprendizadoDeMaquina foi mantida como um token único; a intensidade da pontuação foi perdida.

## Texto 06 — Acentos e Unicode

**Resultados obtidos na execução:**

- **Texto original:** `'O café está ótimo; a ação da equipe foi rápida e eficiente.'`
- **1. Normalização:** `'o café está ótimo; a ação da equipe foi rápida e eficiente.'`
- **2. Expansão:** `'o café está ótimo; a ação da equipe foi rápida e eficiente.'`
- **3. Limpeza:** `'o café está ótimo a ação da equipe foi rápida e eficiente'`
- **4. Tokens:** `['o', 'café', 'está', 'ótimo', 'a', 'ação', 'da', 'equipe', 'foi', 'rápida', 'e', 'eficiente']`
- **5. Sem stopwords:** `['café', 'está', 'ótimo', 'ação', 'equipe', 'rápida', 'eficiente']`
- **6. Emojis:** `[]`
- **Número de tokens (antes → depois das stopwords):** 12 → 7

**Questão 6:** O que ocorreu com os acentos? Seria conveniente removê-los neste problema?

**Resposta:**

A normalização Unicode preservou café, está, ótimo, ação e rápida. Remover acentos aqui não traz vantagem clara e pode perder distinções de palavras em português.

## Texto 07 — Stopwords

**Resultados obtidos na execução:**

- **Texto original:** `'A professora apresentou o conteúdo para os alunos na sala de aula.'`
- **1. Normalização:** `'a professora apresentou o conteúdo para os alunos na sala de aula.'`
- **2. Expansão:** `'a professora apresentou o conteúdo para os alunos na sala de aula.'`
- **3. Limpeza:** `'a professora apresentou o conteúdo para os alunos na sala de aula'`
- **4. Tokens:** `['a', 'professora', 'apresentou', 'o', 'conteúdo', 'para', 'os', 'alunos', 'na', 'sala', 'de', 'aula']`
- **5. Sem stopwords:** `['professora', 'apresentou', 'conteúdo', 'alunos', 'sala', 'aula']`
- **6. Emojis:** `[]`
- **Número de tokens (antes → depois das stopwords):** 12 → 6

**Questão 7:** Quais stopwords foram removidas e quais permaneceram? Por quê?

**Resposta:**

A lista fixa removeu a, o, para, os, na, de e outras palavras nela incluídas. Professora, apresentou, conteúdo, alunos, sala e aula permaneceram; palavras como “dos” também seriam removidas, mas apenas se aparecessem.

## Texto 08 — Números e símbolos

**Resultados obtidos na execução:**

- **Texto original:** `'Comprei 3 livros por R$ 120,50; o desconto foi de 15%.'`
- **1. Normalização:** `'comprei 3 livros por r$ 120,50; o desconto foi de 15%.'`
- **2. Expansão:** `'comprei 3 livros por r$ 120,50; o desconto foi de 15%.'`
- **3. Limpeza:** `'comprei 3 livros por r 120 50 o desconto foi de 15'`
- **4. Tokens:** `['comprei', '3', 'livros', 'por', 'r', '120', '50', 'o', 'desconto', 'foi', 'de', '15']`
- **5. Sem stopwords:** `['comprei', '3', 'livros', 'r', '120', '50', 'desconto', '15']`
- **6. Emojis:** `[]`
- **Número de tokens (antes → depois das stopwords):** 12 → 8

**Questão 8:** Como os números e símbolos monetários/percentuais foram tratados?

**Resposta:**

Os números 3, 120, 50 e 15 foram preservados. A limpeza retirou $ e %, mas deixou o token “r”; também dividiu 120,50 em dois tokens. Perdeu-se o significado de moeda, valor decimal e porcentagem.

## Texto 09 — Negação e sentido

**Resultados obtidos na execução:**

- **Texto original:** `'Eu não recomendo o curso: a aula não foi clara.'`
- **1. Normalização:** `'eu não recomendo o curso: a aula não foi clara.'`
- **2. Expansão:** `'eu não recomendo o curso: a aula não foi clara.'`
- **3. Limpeza:** `'eu não recomendo o curso a aula não foi clara'`
- **4. Tokens:** `['eu', 'não', 'recomendo', 'o', 'curso', 'a', 'aula', 'não', 'foi', 'clara']`
- **5. Sem stopwords:** `['eu', 'não', 'recomendo', 'curso', 'aula', 'não', 'clara']`
- **6. Emojis:** `[]`
- **Número de tokens (antes → depois das stopwords):** 10 → 7

**Questão 9:** A palavra 'não' foi preservada? Que risco haveria em removê-la?

**Resposta:**

Sim. “não” permanece porque não está no conjunto STOPWORDS. Removê-la inverteria ou enfraqueceria a polaridade de “não recomendo” e “não foi clara”.

## Texto 10 — Texto misto

**Resultados obtidos na execução:**

- **Texto original:** `'MANO, vc leu a msg hj? 😅 Veja www.curso.example @turma #PLN!!!'`
- **1. Normalização:** `'mano, vc leu a msg hj? 😅 veja www.curso.example @turma #pln!!!'`
- **2. Expansão:** `'amigo, você leu a mensagem hoje? 😅 veja www.curso.example @turma #pln!!!'`
- **3. Limpeza:** `'amigo você leu a mensagem hoje veja pln'`
- **4. Tokens:** `['amigo', 'você', 'leu', 'a', 'mensagem', 'hoje', 'veja', 'pln']`
- **5. Sem stopwords:** `['amigo', 'você', 'leu', 'mensagem', 'hoje', 'veja', 'pln']`
- **6. Emojis:** `['😅']`
- **Número de tokens (antes → depois das stopwords):** 8 → 7

**Questão 10:** Quais etapas provocaram mudanças? Que informações relevantes foram perdidas?

**Resposta:**

A normalização mudou a caixa; a expansão substituiu MANO, vc, msg e hj após a conversão para minúsculas. A limpeza retirou 😅, URL, menção, # e pontuação. Perderam-se o tom do emoji, o endereço e a pessoa marcada.

## Questões finais

**11.** Compare dois dos textos e indique uma transformação que pode prejudicar uma tarefa de análise de sentimentos. Justifique.

**Resposta:**

No texto 03, a remoção dos emojis elimina pistas de emoções opostas. No texto 09, remover “não” faria uma crítica parecer positiva. Para análise de sentimentos, convém manter ambos.

**12.** Para utilizar BERTimbau, você removeria automaticamente stopwords, emojis e pontuação? Explique sua decisão.

**Resposta:**

Não automaticamente. BERTimbau usa o contexto e a tokenização do próprio modelo; stopwords, pontuação e emojis podem carregar sentido. Eu avaliaria qualquer limpeza em validação antes de aplicá-la.

**13.** Em qual etapa um vazamento de informações entre treino e teste poderia ocorrer ao ajustar transformações aprendidas dos dados (como TF-IDF)?

**Resposta:**

O vazamento ocorre se o vocabulário e os pesos IDF forem ajustados com todos os textos antes da divisão treino/teste. Primeiro divido os dados; depois ajusto o TF-IDF só no treino e transformo validação e teste com o mesmo ajuste.
