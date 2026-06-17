#!/usr/bin/env bash
set -euo pipefail

mkdir -p build

find c -name "*.c" | sort | while read -r arquivo; do
    nome="$(basename "$arquivo" .c)"
    gcc -Wall -Wextra -std=c11 "$arquivo" -o "build/$nome" -lm
    echo "build/$nome"
done
