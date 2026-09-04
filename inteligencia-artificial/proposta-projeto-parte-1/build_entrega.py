from __future__ import annotations

import hashlib
import shutil
import zipfile
from copy import deepcopy
from pathlib import Path

from lxml import etree


BASE = Path("/Users/wvxbs/Library/Mobile Documents/com~apple~CloudDocs/Documents/Ciências da Computação - Mackenzie/Inteligência Artificial/Proposta de Projeto - Parte 1")
OUT = Path("/Users/wvxbs/Documents/repos/Faculdade/inteligencia-artificial/proposta-projeto-parte-1/entrega")
TMP = Path("/private/tmp/ia-proposta-parte1/build")
PROPOSTA = BASE / "projetoDeIA_parte1_informacoesDaProposta_vFinal.docx"
RUBRICA = BASE / "projetoDeIA_parte1_InformacoesDaProposta_rubrica.docx"
PROPOSTA_OUT = TMP / "proposta_parte1_preenchida.docx"
RUBRICA_OUT = OUT / "rubrica_parte1_preenchida.docx"

EXPECTED = {
    PROPOSTA: "1d4f73662c1ec3040d2b8673c919a1d737d984970b683d255493cf224ea29a4b",
    RUBRICA: "5fff968ad5b495df5cc3daf82ff5003424658587cc178417c2332a2b0a4b5a64",
}

W = "http://schemas.openxmlformats.org/wordprocessingml/2006/main"
NS = {"w": W}
WT = f"{{{W}}}t"

TITLE = "FireWatch IA: previsão semanal de municípios brasileiros com alta concentração de focos de queimadas"
MEMBERS = [
    ("Gabriel Ferreira", "10442043"),
]


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()


def paragraph_text(p) -> str:
    return "".join(p.xpath(".//w:t/text()", namespaces=NS))


def new_run(text: str, source_run=None):
    r = etree.Element(f"{{{W}}}r")
    if source_run is not None:
        rpr = source_run.find(f"{{{W}}}rPr")
        if rpr is not None:
            r.append(deepcopy(rpr))
    t = etree.SubElement(r, WT)
    if text[:1].isspace() or text[-1:].isspace():
        t.set("{http://www.w3.org/XML/1998/namespace}space", "preserve")
    t.text = text
    return r


def set_paragraph_text(p, text: str, bold_prefix: str | None = None):
    source_run = p.find(f"{{{W}}}r")
    for child in list(p):
        if child.tag != f"{{{W}}}pPr":
            p.remove(child)
    if bold_prefix and text.startswith(bold_prefix):
        r1 = new_run(bold_prefix, source_run)
        rpr = r1.find(f"{{{W}}}rPr")
        if rpr is None:
            rpr = etree.Element(f"{{{W}}}rPr")
            r1.insert(0, rpr)
        if rpr.find(f"{{{W}}}b") is None:
            etree.SubElement(rpr, f"{{{W}}}b")
        p.append(r1)
        p.append(new_run(text[len(bold_prefix):], source_run))
    else:
        p.append(new_run(text, source_run))


def find_paragraph(root, startswith: str):
    matches = [p for p in root.xpath(".//w:body/w:p", namespaces=NS) if paragraph_text(p).strip().startswith(startswith)]
    if len(matches) != 1:
        raise ValueError(f"Expected one paragraph starting with {startswith!r}, found {len(matches)}")
    return matches[0]


def replace_after_heading(root, heading: str, paragraphs: list[str]):
    body_ps = root.xpath(".//w:body/w:p", namespaces=NS)
    idx = next(i for i, p in enumerate(body_ps) if paragraph_text(p).strip() == heading)
    target = body_ps[idx + 1]
    set_paragraph_text(target, paragraphs[0])
    cursor = target
    for text in paragraphs[1:]:
        clone = deepcopy(target)
        set_paragraph_text(clone, text)
        cursor.addnext(clone)
        cursor = clone


def set_cell_text(cell, text: str):
    ps = cell.xpath("./w:p", namespaces=NS)
    if not ps:
        ps = [etree.SubElement(cell, f"{{{W}}}p")]
    set_paragraph_text(ps[0], text)
    for p in ps[1:]:
        cell.remove(p)


def fill_members(root):
    table = root.xpath(".//w:body/w:tbl", namespaces=NS)[0]
    rows = table.xpath("./w:tr", namespaces=NS)
    for row, (name, ra) in zip(rows[1:], MEMBERS):
        cells = row.xpath("./w:tc", namespaces=NS)
        set_cell_text(cells[0], name)
        set_cell_text(cells[1], ra)


def patch_docx(source: Path, destination: Path, transform):
    destination.parent.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(source, "r") as zin:
        xml = zin.read("word/document.xml")
        root = etree.fromstring(xml)
        transform(root)
        new_xml = etree.tostring(root, xml_declaration=True, encoding="UTF-8", standalone="yes")
        with zipfile.ZipFile(destination, "w") as zout:
            for info in zin.infolist():
                data = new_xml if info.filename == "word/document.xml" else zin.read(info.filename)
                zout.writestr(info, data)


def transform_proposta(root):
    fill_members(root)

    p = find_paragraph(root, "Título provisório:")
    set_paragraph_text(p, f"Título provisório: {TITLE}", "Título provisório:")
    p = find_paragraph(root, "Área/Tema relacionado(a):")
    set_paragraph_text(p, "Área/Tema relacionado(a): Meio ambiente, prevenção de desastres e apoio à decisão pública.", "Área/Tema relacionado(a):")
    p = find_paragraph(root, "ODS(s) associada(s)")
    ods = ("ODS(s) associada(s) e justificativa(s): ODS 13 — Ação contra a mudança global do clima, pois o projeto busca antecipar períodos e locais com maior concentração de fogo e apoiar ações preventivas; e ODS 15 — Vida terrestre, por contribuir para a proteção de ecossistemas e da biodiversidade afetados por queimadas e incêndios florestais.")
    set_paragraph_text(p, ods, "ODS(s) associada(s) e justificativa(s):")
    p = find_paragraph(root, "Tópico(s) de IA")
    topics = ("Tópico(s) de IA que pretende abordar: aprendizado de máquina supervisionado para classificação, análise de séries temporais, engenharia de atributos espaço-temporais, comparação de modelos e Inteligência Artificial Explicável (XAI) com SHAP.")
    set_paragraph_text(p, topics, "Tópico(s) de IA que pretende abordar:")
    for p in list(root.xpath(".//w:body/w:p", namespaces=NS)):
        line = paragraph_text(p).strip()
        if line.startswith("___") and len(line) > 50:
            p.getparent().remove(p)

    replace_after_heading(root, "Contextualização", [
        ("Queimadas e incêndios florestais causam perda de vegetação e biodiversidade, emissão de gases e material particulado, prejuízos econômicos e riscos à saúde. A resposta preventiva depende de reconhecer, com antecedência, onde a concentração de focos tende a aumentar. O projeto delimita o problema ao território brasileiro e à previsão semanal por município."),
        ("Serão usados dados reais e públicos do Programa Queimadas do Instituto Nacional de Pesquisas Espaciais (INPE), disponíveis em arquivos CSV anuais e mensais no portal TerraBrasilis. Os registros de focos ativos serão agregados por município e semana entre 2019 e 2025. A variável-alvo indicará se o município estará entre os 10% com maior número de focos na semana seguinte, considerando o período avaliado."),
    ])
    replace_after_heading(root, "Objetivo", [
        ("Desenvolver e avaliar um modelo de IA capaz de estimar, para cada município brasileiro, a probabilidade de alta concentração de focos de queimadas na semana seguinte. A solução produzirá uma lista ordenada de municípios prioritários e explicações dos fatores que mais influenciaram cada previsão."),
        ("O desempenho será comparado a um baseline sazonal. A métrica principal será a área sob a curva precisão-revocação (PR-AUC), apropriada ao desbalanceamento da classe positiva; F1-score, revocação, precisão e calibração complementarão a avaliação."),
    ])
    replace_after_heading(root, "Motivação", [
        ("Antecipar áreas com maior probabilidade de concentração de focos pode apoiar a priorização de fiscalização, comunicação preventiva e alocação de recursos por órgãos públicos e equipes locais. Academicamente, o projeto permite estudar classificação desbalanceada, dependência temporal, explicabilidade e avaliação sem vazamento de dados em um problema ambiental brasileiro."),
        ("O valor esperado é de apoio à decisão, não de substituição de especialistas nem de sistemas oficiais. A interpretação deverá considerar que focos detectados por satélite não representam, isoladamente, a extensão ou a causa de um incêndio e podem refletir limitações de cobertura e detecção."),
    ])
    replace_after_heading(root, "Justificativa", [
        ("A fonte de dados foi escolhida por ser oficial, gratuita, atualizada e diretamente relacionada ao fenômeno estudado. Portal: https://terrabrasilis.dpi.inpe.br/queimadas/portal/dados-abertos/. Cada linha representa uma detecção georreferenciada; após limpeza de duplicidades e ausências, os registros serão agregados em município-semana. Serão derivados atributos de calendário, bioma e histórico recente, como contagens defasadas, médias móveis, tendência e sazonalidade. Somente informações disponíveis antes da semana prevista serão usadas, evitando vazamento temporal."),
        ("Serão comparados regressão logística, Random Forest e XGBoost, além do baseline sazonal. A regressão logística oferece referência interpretável; Random Forest e XGBoost capturam relações não lineares e interações entre histórico, sazonalidade e localização. O particionamento será temporal: 2019–2023 para treino, 2024 para validação e 2025 para teste final. Hiperparâmetros e limiar de decisão serão definidos apenas no conjunto de validação. SHAP será aplicado ao melhor modelo para explicações globais e locais."),
    ])
    replace_after_heading(root, "Contribuições esperadas", [
        ("Espera-se formalizar a previsão de concentração de focos como tarefa reprodutível de classificação espaço-temporal; construir uma base município-semana limpa e documentada; comparar três famílias de modelos com um baseline; estabelecer avaliação temporal com métricas adequadas ao desbalanceamento; e identificar, por SHAP, quais atributos mais influenciam as previsões."),
        ("Como artefato, será produzido um notebook reprodutível e um protótipo simples de mapa ou painel com ranking semanal dos municípios. O resultado será considerado útil se superar o baseline em PR-AUC e apresentar revocação compatível com o uso de triagem, com limitações, vieses regionais e incerteza explicitados. O escopo é viável no semestre porque usa dados já disponíveis, métodos consolidados e um protótipo de complexidade controlada."),
    ])

    set_paragraph_text(find_paragraph(root, "(    ) Sim      (   )  Não"), "(    ) Sim      ( X ) Não")
    for label in ["Nome Disciplina 1:", "Nome Disciplina 2:", "Nome Disciplina 3:"]:
        set_paragraph_text(find_paragraph(root, label), f"{label} Não se aplica.", label)
    set_paragraph_text(find_paragraph(root, "(    ) Sim      (    )  Não"), "(    ) Sim      ( X ) Não")
    p = find_paragraph(root, "Caso positivo, informe o nome do(a) professor(a) orientador(a):")
    set_paragraph_text(p, "Caso positivo, informe o nome do(a) professor(a) orientador(a): Não se aplica.", "Caso positivo, informe o nome do(a) professor(a) orientador(a):")

    set_paragraph_text(find_paragraph(root, "(      ) Não foi utilizada"), "(      ) Não foram utilizadas ferramentas de IA generativa nesta atividade.")
    set_paragraph_text(find_paragraph(root, "(      ) Foi utilizada"), "(  X  ) Foi utilizada, conforme abaixo.")
    underlines = [p for p in root.xpath(".//w:body/w:p", namespaces=NS) if paragraph_text(p).strip() == "___________________________"]
    set_paragraph_text(underlines[0], "OpenAI Codex")
    set_paragraph_text(underlines[1], "")
    checks = {
        "(      )  Compreender": "(  X  ) Compreender enunciado, conceito ou material da disciplina",
        "(      )  Diagnosticar": "(      ) Diagnosticar erro em algo que já havia produzido",
        "(      )  Produzir": "(  X  ) Produzir parte do conteúdo entregue",
        "(      )  Revisar": "(      ) Revisar ou reescrever conteúdo que já havia produzido",
        "(      )  Traduzir": "(  X  ) Traduzir, formatar ou redigir texto de apoio",
        "(      )  Outro": "(      ) Outro (Discriminar): não se aplica",
    }
    for prefix, value in checks.items():
        set_paragraph_text(find_paragraph(root, prefix), value)


def transform_rubrica(root):
    fill_members(root)
    p = find_paragraph(root, "Título provisório do Projeto:")
    set_paragraph_text(p, f"Título provisório do Projeto: {TITLE}", "Título provisório do Projeto:")
    table = root.xpath(".//w:body/w:tbl", namespaces=NS)[1]
    rows = table.xpath("./w:tr", namespaces=NS)
    notes = ["20", "15", "10", "15", "15", "15", "10"]
    for row, note in zip(rows[1:8], notes):
        cells = row.xpath("./w:tc", namespaces=NS)
        set_cell_text(cells[6], note)
    total_cells = rows[8].xpath("./w:tc", namespaces=NS)
    set_cell_text(total_cells[6], "100")


def verify_preserved_parts(source: Path, result: Path):
    with zipfile.ZipFile(source) as a, zipfile.ZipFile(result) as b:
        a_names, b_names = set(a.namelist()), set(b.namelist())
        if a_names != b_names:
            raise AssertionError(f"Package part set changed: {a_names ^ b_names}")
        for name in sorted(a_names - {"word/document.xml"}):
            if hashlib.sha256(a.read(name)).digest() != hashlib.sha256(b.read(name)).digest():
                raise AssertionError(f"Preserve-only package part changed: {name}")


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    TMP.mkdir(parents=True, exist_ok=True)
    for path, expected in EXPECTED.items():
        actual = sha256(path)
        if actual != expected:
            raise RuntimeError(f"Reference changed: {path} ({actual})")
    patch_docx(PROPOSTA, PROPOSTA_OUT, transform_proposta)
    patch_docx(RUBRICA, RUBRICA_OUT, transform_rubrica)
    verify_preserved_parts(PROPOSTA, PROPOSTA_OUT)
    verify_preserved_parts(RUBRICA, RUBRICA_OUT)
    print(PROPOSTA_OUT)
    print(RUBRICA_OUT)


if __name__ == "__main__":
    main()
