public class ResolucaoBissecao {

    public static double f(double x) {
        return (x * x) - 4.0;
    }

    public static double Bissecao(double A, double B, double E) {
        double erro = Math.abs(A - B) / 2.0;
        double M = 0.0;

        while (erro > E) {
            M = (A + B) / 2.0;

            if (f(A) * f(M) < 0) {
                B = M;
            } else {
                A = M;
            }
            erro = Math.abs(A - B) / 2.0;
        }

        M = (A + B) / 2.0;
        System.out.println("Erro calculado: " + erro);
        return M;
    }

    public static void main(String[] args) {
        double raizEncontrada = Bissecao(0.0, 3.0, 0.01);
        System.out.println("Raiz encontrada: " + raizEncontrada);
    }
}