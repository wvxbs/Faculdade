def resolucao_sistema_gauss(A, b):
    n = len(A)
    matriz_aumentada = [A[i][:] + [b[i]] for i in range(n)]
    
    for k in range(n - 1):
        pivo = matriz_aumentada[k][k]
        if pivo == 0:
            raise ValueError("Pivô nulo encontrado.")
        
        for i in range(k + 1, n):
            fator = matriz_aumentada[i][k] / pivo
            for j in range(k, n + 1):
                matriz_aumentada[i][j] -= fator * matriz_aumentada[k][j]

    x = [0.0] * n
    for i in range(n - 1, -1, -1):
        soma = sum(matriz_aumentada[i][j] * x[j] for j in range(i + 1, n))
        x[i] = (matriz_aumentada[i][n] - soma) / matriz_aumentada[i][i]
        
    return x