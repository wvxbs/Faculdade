"""
Algoritmos de ordenacao comuns em Python.

Todas as funcoes retornam uma nova lista ordenada e preservam a lista original.
No final do arquivo ha uma pequena demonstracao executavel.
"""

from __future__ import annotations

from typing import Iterable, List, Sequence, TypeVar


T = TypeVar("T")


def bubble_sort(items: Sequence[T]) -> List[T]:
    """Ordena comparando vizinhos e empurrando o maior para o fim."""
    arr = list(items)
    n = len(arr)

    for end in range(n - 1, 0, -1):
        swapped = False
        for i in range(end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                swapped = True
        if not swapped:
            break

    return arr


def selection_sort(items: Sequence[T]) -> List[T]:
    """Escolhe o menor elemento restante e coloca na proxima posicao."""
    arr = list(items)
    n = len(arr)

    for i in range(n - 1):
        min_index = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]

    return arr


def insertion_sort(items: Sequence[T]) -> List[T]:
    """Insere cada elemento na posicao correta dentro do prefixo ordenado."""
    arr = list(items)

    for i in range(1, len(arr)):
        current = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > current:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = current

    return arr


def merge_sort(items: Sequence[T]) -> List[T]:
    """Divide a lista ao meio, ordena as partes e intercala os resultados."""
    arr = list(items)
    if len(arr) <= 1:
        return arr

    middle = len(arr) // 2
    left = merge_sort(arr[:middle])
    right = merge_sort(arr[middle:])

    return _merge(left, right)


def _merge(left: Sequence[T], right: Sequence[T]) -> List[T]:
    merged: List[T] = []
    i = 0
    j = 0

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1

    merged.extend(left[i:])
    merged.extend(right[j:])
    return merged


def quick_sort(items: Sequence[T]) -> List[T]:
    """Escolhe um pivo e separa menores, iguais e maiores que ele."""
    arr = list(items)
    if len(arr) <= 1:
        return arr

    pivot = arr[len(arr) // 2]
    less = [value for value in arr if value < pivot]
    equal = [value for value in arr if value == pivot]
    greater = [value for value in arr if value > pivot]

    return quick_sort(less) + equal + quick_sort(greater)


def heap_sort(items: Sequence[T]) -> List[T]:
    """Transforma a lista em heap maximo e extrai o maior repetidamente."""
    arr = list(items)
    n = len(arr)

    for i in range(n // 2 - 1, -1, -1):
        _heapify(arr, n, i)

    for end in range(n - 1, 0, -1):
        arr[0], arr[end] = arr[end], arr[0]
        _heapify(arr, end, 0)

    return arr


def _heapify(arr: List[T], heap_size: int, root: int) -> None:
    largest = root
    left = 2 * root + 1
    right = 2 * root + 2

    if left < heap_size and arr[left] > arr[largest]:
        largest = left
    if right < heap_size and arr[right] > arr[largest]:
        largest = right

    if largest != root:
        arr[root], arr[largest] = arr[largest], arr[root]
        _heapify(arr, heap_size, largest)


def shell_sort(items: Sequence[T]) -> List[T]:
    """Generaliza insertion sort usando saltos que diminuem ate 1."""
    arr = list(items)
    gap = len(arr) // 2

    while gap > 0:
        for i in range(gap, len(arr)):
            current = arr[i]
            j = i
            while j >= gap and arr[j - gap] > current:
                arr[j] = arr[j - gap]
                j -= gap
            arr[j] = current
        gap //= 2

    return arr


def counting_sort(items: Iterable[int]) -> List[int]:
    """Ordena inteiros contando frequencias. Aceita valores negativos."""
    arr = list(items)
    if not arr:
        return []

    minimum = min(arr)
    maximum = max(arr)
    counts = [0] * (maximum - minimum + 1)

    for value in arr:
        counts[value - minimum] += 1

    sorted_arr: List[int] = []
    for offset, count in enumerate(counts):
        sorted_arr.extend([offset + minimum] * count)

    return sorted_arr


def radix_sort(items: Iterable[int]) -> List[int]:
    """Ordena inteiros por digitos. Separa negativos para manter a ordem."""
    arr = list(items)
    negatives = [-value for value in arr if value < 0]
    non_negatives = [value for value in arr if value >= 0]

    sorted_negatives = _radix_sort_non_negative(negatives)
    sorted_non_negatives = _radix_sort_non_negative(non_negatives)

    return [-value for value in reversed(sorted_negatives)] + sorted_non_negatives


def _radix_sort_non_negative(arr: List[int]) -> List[int]:
    if not arr:
        return []

    result = list(arr)
    exp = 1
    maximum = max(result)

    while maximum // exp > 0:
        buckets = [[] for _ in range(10)]
        for value in result:
            digit = (value // exp) % 10
            buckets[digit].append(value)
        result = [value for bucket in buckets for value in bucket]
        exp *= 10

    return result


def bucket_sort(items: Iterable[float], bucket_count: int = 10) -> List[float]:
    """Ordena numeros distribuindo em baldes e ordenando cada balde."""
    arr = list(items)
    if len(arr) <= 1:
        return arr
    if bucket_count <= 0:
        raise ValueError("bucket_count deve ser positivo")

    minimum = min(arr)
    maximum = max(arr)
    if minimum == maximum:
        return arr

    buckets: List[List[float]] = [[] for _ in range(bucket_count)]
    scale = (bucket_count - 1) / (maximum - minimum)

    for value in arr:
        index = int((value - minimum) * scale)
        buckets[index].append(value)

    result: List[float] = []
    for bucket in buckets:
        result.extend(insertion_sort(bucket))

    return result


SORTS = {
    "bubble": bubble_sort,
    "selection": selection_sort,
    "insertion": insertion_sort,
    "merge": merge_sort,
    "quick": quick_sort,
    "heap": heap_sort,
    "shell": shell_sort,
    "counting": counting_sort,
    "radix": radix_sort,
    "bucket": bucket_sort,
}


def demo() -> None:
    numbers = [8, -3, 5, 1, 9, 0, -3, 4]
    decimals = [0.42, 0.12, 0.89, 0.33, 0.72, 0.12]

    print("Original:", numbers)
    for name in ("bubble", "selection", "insertion", "merge", "quick", "heap", "shell"):
        print(f"{name:>9}:", SORTS[name](numbers))

    print(" counting:", counting_sort(numbers))
    print("    radix:", radix_sort(numbers))
    print("   bucket:", bucket_sort(decimals))


if __name__ == "__main__":
    demo()
