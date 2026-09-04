# Contrato de execução — Proposta de Projeto de IA, Parte 1

## Referências retidas

- Proposta: `/Users/wvxbs/Library/Mobile Documents/com~apple~CloudDocs/Documents/Ciências da Computação - Mackenzie/Inteligência Artificial/Proposta de Projeto - Parte 1/projetoDeIA_parte1_informacoesDaProposta_vFinal.docx`
  - SHA-256: `1d4f73662c1ec3040d2b8673c919a1d737d984970b683d255493cf224ea29a4b`
  - 4 páginas, 1 seção, A4 retrato, margens L/R 0,75", T/B 1,00".
- Rubrica: `/Users/wvxbs/Library/Mobile Documents/com~apple~CloudDocs/Documents/Ciências da Computação - Mackenzie/Inteligência Artificial/Proposta de Projeto - Parte 1/projetoDeIA_parte1_InformacoesDaProposta_rubrica.docx`
  - SHA-256: `5fff968ad5b495df5cc3daf82ff5003424658587cc178417c2332a2b0a4b5a64`
  - 4 páginas renderizadas, 3 seções; A4 retrato, A4 paisagem e A4 retrato; cabeçalhos e rodapés vinculados.
- Evidências visuais: `/private/tmp/ia-proposta-parte1/proposta-reference` e `/private/tmp/ia-proposta-parte1/rubrica-reference`.
- Evidências de estilos: `/private/tmp/ia-proposta-parte1/proposta-style.json` e `/private/tmp/ia-proposta-parte1/rubrica-style.json`.

## Sistema visual e estrutural

- Preservar integralmente logotipos, cabeçalhos, rodapés, numeração, dimensões, margens, quebras de seção, tabelas de orientação e rubrica.
- Tipografia predominante Arial, com formatação direta herdada dos parágrafos de origem; títulos e rótulos permanecem em negrito conforme a referência.
- Preservar a tabela de integrantes com 6 linhas e 2 colunas e o Quadro 1 com 11 linhas e 3 colunas.
- Na rubrica, preservar a matriz de 9 linhas e 7 colunas e a tabela de resultado da competência sem preenchimento.
- Expansão de paginação da proposta é permitida para acomodar as respostas, desde que não haja cortes, sobreposições ou alteração da geometria.

## Mapa de slots

### Proposta (`word/document.xml`)

- Tabela 0, linha 1: nome e RA de Gabriel Ferreira; linhas 2–5 permanecem vazias enquanto a composição do grupo é alinhada com o professor.
- Parágrafo iniciado por `Título provisório:`: substituir pelo título completo.
- Parágrafo iniciado por `Área/Tema relacionado(a):`: substituir pela área.
- Parágrafo iniciado por `ODS(s) associada(s)`: substituir por ODS e justificativa; remover as duas linhas de sublinhados seguintes.
- Parágrafo iniciado por `Tópico(s) de IA`: substituir pelos tópicos; remover as duas linhas de sublinhados seguintes.
- Sob `Contextualização`, `Objetivo`, `Motivação`, `Justificativa` e `Contribuições esperadas`: substituir somente o texto instrucional subsequente por respostas autorais; parágrafos adicionais podem clonar o mesmo padrão visual.
- `Pretende utilizar em outras disciplinas`: marcar Não; campos de disciplinas ficam como `Não se aplica`.
- `Esta proposta está relacionada ao TCC`: marcar Não; orientador como `Não se aplica`.
- Declaração de IA: marcar uso, identificar OpenAI Codex, marcar compreensão, produção de conteúdo e redação/formatação.

### Rubrica (`word/document.xml`)

- Tabela 0, linha 1: Gabriel Ferreira e RA; linhas 2–5 permanecem vazias.
- Parágrafo `Título provisório do Projeto:`: incluir o título.
- Matriz da rubrica, coluna `Nota`: preencher 20, 15, 10, 15, 15, 15 e 10; total 100.
- Não preencher `Parecer do Professor`, `Pontos Fortes`, `Aspectos a Melhorar` nem `Resultado da Competência`.

## Cobertura e preservação de pacote

- Parte editável: somente `word/document.xml` em cada DOCX.
- Partes preserve-only: estilos, numeração, tema, configurações, cabeçalhos, rodapés, imagens, relacionamentos, propriedades, `customXml`, fontes e demais itens do pacote.
- O conteúdo de cada parte preserve-only deve manter SHA-256 idêntico ao da referência.

## Gates de fidelidade

- Os dois arquivos-fonte devem continuar byte a byte inalterados nos caminhos e hashes registrados.
- Comparar renderizações de referência e finais e inspecionar 100% das páginas finais.
- Reexecutar auditorias de seção e estilo.
- Confirmar ausência de texto cortado, linhas órfãs, sobreposições, páginas em branco inesperadas e quebra da tabela paisagem da rubrica.
- Confirmar que os campos reservados ao professor continuam vazios.
