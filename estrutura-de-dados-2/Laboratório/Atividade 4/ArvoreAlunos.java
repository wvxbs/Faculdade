import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class ArvoreAlunos {
    private No raiz;

    private static class No {
        private Aluno aluno;
        private No esquerdo;
        private No direito;

        private No(Aluno aluno) {
            this.aluno = aluno;
        }
    }

    public void inserir(Aluno aluno) {
        if (aluno == null) {
            throw new IllegalArgumentException("O aluno não pode ser nulo.");
        }
        raiz = inserir(raiz, aluno);
    }

    private No inserir(No atual, Aluno aluno) {
        if (atual == null) {
            return new No(aluno);
        }

        int ra = aluno.getRa();
        if (ra < atual.aluno.getRa()) {
            atual.esquerdo = inserir(atual.esquerdo, aluno);
        } else if (ra > atual.aluno.getRa()) {
            atual.direito = inserir(atual.direito, aluno);
        } else {
            throw new IllegalArgumentException("Já existe aluno com RA " + ra + ".");
        }
        return atual;
    }

    public Aluno buscarPorRA(int ra) {
        No atual = raiz;
        while (atual != null) {
            if (ra == atual.aluno.getRa()) {
                return atual.aluno;
            }
            atual = ra < atual.aluno.getRa() ? atual.esquerdo : atual.direito;
        }
        return null;
    }

    public List<Aluno> buscarPorNome(String parteDoNome) {
        List<Aluno> encontrados = new ArrayList<>();
        if (parteDoNome == null || parteDoNome.isBlank()) {
            return encontrados;
        }

        buscarPorNome(raiz, parteDoNome.toLowerCase(Locale.ROOT), encontrados);
        return encontrados;
    }

    private void buscarPorNome(No atual, String termo, List<Aluno> encontrados) {
        if (atual == null) {
            return;
        }

        buscarPorNome(atual.esquerdo, termo, encontrados);
        if (atual.aluno.getNome().toLowerCase(Locale.ROOT).contains(termo)) {
            encontrados.add(atual.aluno);
        }
        buscarPorNome(atual.direito, termo, encontrados);
    }

    public Aluno remover(int ra) {
        Aluno removido = buscarPorRA(ra);
        if (removido != null) {
            raiz = remover(raiz, ra);
        }
        return removido;
    }

    private No remover(No atual, int ra) {
        if (atual == null) {
            return null;
        }

        if (ra < atual.aluno.getRa()) {
            atual.esquerdo = remover(atual.esquerdo, ra);
        } else if (ra > atual.aluno.getRa()) {
            atual.direito = remover(atual.direito, ra);
        } else {
            if (atual.esquerdo == null) {
                return atual.direito;
            }
            if (atual.direito == null) {
                return atual.esquerdo;
            }

            No sucessor = menorNo(atual.direito);
            atual.aluno = sucessor.aluno;
            atual.direito = remover(atual.direito, sucessor.aluno.getRa());
        }
        return atual;
    }

    private No menorNo(No atual) {
        while (atual.esquerdo != null) {
            atual = atual.esquerdo;
        }
        return atual;
    }
}
