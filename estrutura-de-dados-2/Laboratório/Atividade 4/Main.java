import java.util.List;

public class Main {
    public static void main(String[] args) {
        ArvoreAlunos bst = new ArvoreAlunos();

        bst.inserir(new Aluno(500, "Carlos Silva", "Engenharia de Software"));
        bst.inserir(new Aluno(250, "Ana Santos", "Ciência da Computação"));
        bst.inserir(new Aluno(750, "Mariana Oliveira", "Sistemas de Informação"));
        bst.inserir(new Aluno(100, "João Pereira", "Engenharia de Software"));
        bst.inserir(new Aluno(600, "Pedro Carlos Almeida", "Matemática"));

        System.out.println("--- Buscando por RA 250 ---");
        Aluno a1 = bst.buscarPorRA(250);
        System.out.println(a1 != null ? a1 : "Aluno não encontrado.");

        System.out.println("\n--- Buscando por parte do nome: 'carlos' ---");
        List<Aluno> buscaNome = bst.buscarPorNome("carlos");
        for (Aluno aluno : buscaNome) {
            System.out.println(aluno);
        }

        System.out.println("\n--- Removendo o aluno de RA 500 ---");
        System.out.println(bst.remover(500));
        System.out.println("Busca pelo RA 500 após a remoção: " + bst.buscarPorRA(500));
    }
}
