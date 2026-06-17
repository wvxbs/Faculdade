#!/usr/bin/env sh

set -eu

entrada="${1:-casos}"
saida="out"
script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

if [ ! -d "$entrada" ]; then
    echo "Pasta de entrada nao encontrada: $entrada" >&2
    exit 1
fi

mkdir -p "$saida"
tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT INT TERM

for arquivo in "$entrada"/*; do
    [ -f "$arquivo" ] || continue

    nome=$(basename -- "$arquivo")
    cp "$arquivo" "$tmpdir/in"

    (
        cd "$tmpdir"
        swipl -q -s "$script_dir/huffman.pl"
    )

    cp "$tmpdir/out" "$saida/$nome"
    echo "Codificado: $arquivo -> $saida/$nome"
done
