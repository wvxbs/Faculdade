#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

static void print_array(const char *label, int v[], int n) {
    printf("%s[", label);
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i + 1 < n) printf(", ");
    }
    printf("]\n");
}

static void copy_array(int dst[], int src[], int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static int maior(int v[], int n) {
    int m = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i] > m) m = v[i];
    }
    return m;
}

static int menor(int v[], int n) {
    int m = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i] < m) m = v[i];
    }
    return m;
}

static void inverter(int v[], int n) {
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        swap(&v[i], &v[j]);
    }
}

static int conta(int v[], int n, int x) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] == x) total++;
    }
    return total;
}

static int mais_recorrente(int v[], int n, int *freq) {
    int melhor = v[0];
    int melhor_freq = conta(v, n, melhor);

    for (int i = 1; i < n; i++) {
        int f = conta(v, n, v[i]);
        if (f > melhor_freq) {
            melhor = v[i];
            melhor_freq = f;
        }
    }

    *freq = melhor_freq;
    return melhor;
}

static void selection_sort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int im = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[im]) im = j;
        }
        swap(&v[i], &v[im]);
        print_array("  passo selection: ", v, n);
    }
}

static void insertion_sort(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int x = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > x) {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = x;
        print_array("  passo insertion: ", v, n);
    }
}

static void bubble_sort(int v[], int n) {
    for (int fim = n - 1; fim > 0; fim--) {
        for (int i = 0; i < fim; i++) {
            if (v[i] > v[i + 1]) {
                swap(&v[i], &v[i + 1]);
            }
        }
        print_array("  passo bubble:    ", v, n);
    }
}

static int partition(int v[], int ini, int fim) {
    int pivo = v[fim];
    int i = ini - 1;

    for (int j = ini; j < fim; j++) {
        if (v[j] <= pivo) {
            i++;
            swap(&v[i], &v[j]);
        }
    }

    swap(&v[i + 1], &v[fim]);
    return i + 1;
}

static void quick_sort_rec(int v[], int ini, int fim, int n) {
    if (ini >= fim) return;

    int p = partition(v, ini, fim);
    print_array("  passo quick:     ", v, n);
    quick_sort_rec(v, ini, p - 1, n);
    quick_sort_rec(v, p + 1, fim, n);
}

static void quick_sort(int v[], int n) {
    quick_sort_rec(v, 0, n - 1, n);
}

static void merge(int v[], int ini, int meio, int fim) {
    int n1 = meio - ini + 1;
    int n2 = fim - meio;
    int *a = malloc((size_t)n1 * sizeof(int));
    int *b = malloc((size_t)n2 * sizeof(int));

    for (int i = 0; i < n1; i++) a[i] = v[ini + i];
    for (int j = 0; j < n2; j++) b[j] = v[meio + 1 + j];

    int i = 0, j = 0, k = ini;
    while (i < n1 && j < n2) {
        if (a[i] <= b[j]) v[k++] = a[i++];
        else v[k++] = b[j++];
    }

    while (i < n1) v[k++] = a[i++];
    while (j < n2) v[k++] = b[j++];

    free(a);
    free(b);
}

static void merge_sort_rec(int v[], int ini, int fim, int n) {
    if (ini >= fim) return;

    int meio = (ini + fim) / 2;
    merge_sort_rec(v, ini, meio, n);
    merge_sort_rec(v, meio + 1, fim, n);
    merge(v, ini, meio, fim);
    print_array("  passo merge:     ", v, n);
}

static void merge_sort(int v[], int n) {
    merge_sort_rec(v, 0, n - 1, n);
}

static void run_sort_demo(const char *nome, void (*sort_fn)(int[], int), int base[], int n) {
    int v[N];
    copy_array(v, base, n);

    printf("\n=== %s ===\n", nome);
    print_array("entrada: ", v, n);
    sort_fn(v, n);
    print_array("saida:   ", v, n);
}

int main(void) {
    int base[N] = {7, 1, 3, 3, 9, 2, 1, 5, 3, 0};

    print_array("lista original: ", base, N);
    printf("maior: %d\n", maior(base, N));
    printf("menor: %d\n", menor(base, N));
    printf("ocorrencias de 3: %d\n", conta(base, N, 3));

    int freq = 0;
    int elem = mais_recorrente(base, N, &freq);
    printf("mais recorrente: %d aparece %d vezes\n", elem, freq);

    int inv[N];
    copy_array(inv, base, N);
    inverter(inv, N);
    print_array("invertida: ", inv, N);

    run_sort_demo("selection sort", selection_sort, base, N);
    run_sort_demo("insertion sort", insertion_sort, base, N);
    run_sort_demo("bubble sort", bubble_sort, base, N);
    run_sort_demo("quick sort", quick_sort, base, N);
    run_sort_demo("merge sort", merge_sort, base, N);

    return 0;
}
