def construirMatrizDeValores(n):
    x = []
    y = []
    
    for i in range(n):
        xi = float(input(f"Valor de x[{i}] = "))
        yi = float(input(f"Valor de F[{i}] = "))
    
        x.append(xi)
        y.append(yi)

    return x, y


def calcularInterpolacaoPolinomial(n, x, y, valor):
    if(n < 2 or n > 20):
        return False

    if len(set(x)) != n:
       return False

    px = 0

    for i in range(n):
        li = 1

        for j in range(n):
            if i != j:
                li *= (valor - x[j]) / (x[i] - x[j])

        px += y[i] * li
    
    return px


def main():
    n = int(input("Quantidade de pontos (2 a 20): "))
    
    x, y = construirMatrizDeValores(n)

    valor = float(input("Insira o valor de x a ser interpolado: "))
    
    resultado = calcularInterpolacaoPolinomial(n, x, y, valor)
   
    if resultado is not False:
       print(f"P({valor}) = {resultado}")
    else:
        print("Quantidade de pontos inválida, ou valores de x iguais")

main()
