/*
* @Author: reinaldo
* @Date:   2014-09-16 23:26:37
* @Last Modified by:   Reinaldo Antonio Camargo Rauch
* @Last Modified time: 2014-09-17 01:47:53
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100000
#define SEARCH_REPEAT 1

/**
 * Struct da árvore AVL
 */
struct node {
    struct node *dir;
    struct node *esq;
    int value;
    int bal;
};

/**
 * Tipo t_node
 */
typedef struct node t_node;


/**
 * Array de inteiros para os números aleatórios
 */
int array[TAM], tamHeap;

/**
 * Variáveis para contagem de comparações
 */
int sequentialCount = 0, binCount = 0, binTreeCount = 0, avlCount = 0;

/**
 * Raiz da árvore AVL
 */
t_node *root_avl = NULL;

/**
 * Raiz da árvore binária
 */
t_node *root_bin_tree = NULL;

// Códigos da árvore AVL

/**
 * Rotação esquerda
 * @param p pivô da rotação
 */
void esquerda(t_node *p) {
    // Variáveis auxiliares
    t_node *q, *hold;

    q = p->dir;
    hold = q->esq;
    q->esq = p;
    p->dir = hold;
}

/**
 * Rotação direita
 * @param p pivô da rotação
 */
void direita(t_node *p) {
    t_node *q, *hold;

    q = p->esq;
    hold = q->dir;
    q->dir = p;
    p->esq = hold;

}

/**
 * Cria novo nó para ser adicionado na árvore
 * @param  value Valor a ser adicionado na árvore
 * @return       t_node criado
 */
t_node *create_node(int value){
    t_node *aux = (t_node*) malloc(sizeof(t_node));

    if(aux == NULL)
        return aux;

    aux->value = value;
    aux->dir = NULL;
    aux->esq = NULL;
    aux->bal = 0;

    return aux;
}

/**
 * Inserção na árvore AVL
 * @param key valor a ser inserido
 */
void balanced_insert(int key)
{

    t_node *pp = NULL,
        *p = root_avl,
        *pajovem = NULL,
        *ajovem = root_avl,
        *q,
        *filho;

    int imbal;

    /* Se árvore vazia */
    if (p == NULL) {
        /* Funcao para criacao de um novo no */
        root_avl = create_node(key);
        return;
    }

    /* Insere key e descobre ancestral mais jovem a ser desbalanceado */
    while (p != NULL) {
        if (key > p->value)
            q = p->dir;
        else
            q = p->esq;

        if (q != NULL)
            if (q->bal != 0) {
                pajovem = p;
                ajovem = q;
            }

        pp = p;
        p = q;
    }

    q = create_node(key);

    if (key < pp->value)
        pp->esq=q;
    else
        pp->dir=q;

    /* Balanceamento de todos os nós entre ajovem e q devem ser ajustados */
    if (key < ajovem->value)
        filho = ajovem->esq;
    else
        filho = ajovem->dir;

    p = filho;

    while (p != q) {
        if (key < p->value) {
            p->bal = 1;
            p = p->esq;
        } else {
            p->bal = -1;
            p = p->dir;
        }
    }

    if (key < ajovem->value)
        imbal = 1;
    else
        imbal = -1;

    /* Se não houve desbalanceamento */
    if (ajovem->bal == 0) {
        ajovem->bal=imbal;
        return;
    }

    /* Se não houve desbalanceamento */
    if (ajovem->bal != imbal) {
        ajovem->bal = 0;
        return;
    }

    /* Houve desbalanceamento */
    if (filho->bal == imbal) {
        p = filho;

        /* Faz rotação simples */
        if (imbal==1)

            direita(ajovem);
        else
            esquerda(ajovem);

        ajovem->bal=0;
        filho->bal=0;

    } else {

        /*Faz rotação dupla */
        if (imbal == 1) {

            p = filho->dir;
            esquerda(filho);
            ajovem->esq = p;
            direita(ajovem);

        } else {

            p = filho->esq;
            direita(filho);
            ajovem->dir = p;
            esquerda(ajovem);

        }

        if (p->bal == 0) {

            ajovem->bal = 0;
            filho->bal = 0;

        } else {

            if (p->bal == imbal) {

                ajovem->bal = - imbal;
                filho->bal = 0;

            } else {

                ajovem->bal = 0;
                filho->bal = imbal;

            }

        }

        p->bal = 0;
    }

    if (pajovem == NULL)  /* Ajusta ponteiro do pai do ancestral mais jovem */
        root_avl = p;
    else
        if (ajovem == pajovem->dir)
            pajovem->dir = p;
        else
            pajovem->esq = p;

}

// Funções da árvore binária

/**
 * Inserção na árvore binária
 * @param val valor a ser inserido na árvore
 */
void bin_tree_insert(int val) {

    t_node *here, *aux;

    aux = (t_node*) malloc(sizeof(t_node));

    if(aux == NULL) {
        puts("Erro ao alocar memória");
        return;
    }

    aux->value = val;
    aux->esq = NULL;
    aux->dir = NULL;

    here = root_bin_tree;

    if(here == NULL) {
        root_bin_tree = aux;
        return;
    }

    while(1) {
        if(val < here->value)
            if(here->esq == NULL) {
                here->esq = aux;
                return;
            } else
                here = here->esq;
        else
            if(here->dir == NULL) {
                here->dir = aux;
                return;
            } else
                here = here->dir;
    }

}

/**
 * Percurso em ordem na árvore binária
 * @param here nó atual
 */
void em_ordem(t_node *here) {

    if(here != NULL) {
        em_ordem(here->esq);
        printf("Value %d\n", here->value);
        em_ordem(here->dir);
    }

}

// Heapsort para ordenar

/**
 * Gera uma heap no vetor
 * @param i raiz da heap
 */
void heapify(i) {
    int l = 2 * i + 1,
        r = 2 * i + 2,
        m = 0,
        t = 0;

    if (l < tamHeap && array[l] > array[i])
        m = l;
    else
        m = i;

    if (r < tamHeap && array[r] > array[m])
        m = r;

    if (m != i) {
        t = array[i];
        array[i] = array[m];
        array[m] = t;

        heapify(m);
    }
}

/**
 * Algoritmo de ordenação heap sort
 */
void heapSort() {
    int i = 0, t = 0;
    tamHeap = TAM;
    for (i = ((TAM / 2) - 1); i >= 0; i--)
        heapify(i);

    for (i = (TAM - 1); i > 0; i--)
    {
        t = array[0];
        array[0] = array[i];
        array[i] = t;

        tamHeap--;
        heapify(0);
    }
}

/**
 * Gera os valores para o array
 */
void generateValues() {

    int i;

    for (i = 0; i < TAM; i++)
    {
        array[i] = rand();
    }

}

// Funções de busca

/**
 * Busca sequencial no array
 * @param  key valor a ser procurado
 * @return     retorna a posição no array
 */
int sequentialSearch(int key) {

    int i;

    for (i = 0; i < TAM; i++) {
        sequentialCount++;
        if(array[i] == key)
            return i;
    }

    return -1;

}

/**
 * Busca binária no vetor
 * @param  val valor a ser buscado
 * @return     retorna -1 se o valor não foi encontrado. Se sim, retorna seu
 *             índice no array
 */
int binSearch(int val) {

    int s = 0, e = (TAM - 1), r;

    while(s <= e) {
        r = (s + e) / 2;

        binCount++;
        if(val < array[r])
            e = r - 1;
        else
            if(val > array[r])
                s = r + 1;
            else {
                return r;
            }
    }

    return -1;

}

/**
 * Busca na árvore binária
 * @param  val  valor a ser procurado
 * @param  root raiz da árvore em que val será procurada
 * @return     NULL se não foi encontrado, t_node se sim
 */
t_node *search(int val, t_node *root, int *count) {

    t_node *here = root;

    while(here != NULL) {

        (*count)++;
        if(here->value > val) {
            here = here->dir;
        } else if(here->value < val) {
            here = here->esq;
        } else{
            return here;
        }

    }

    return NULL;
}

/**
 * Função main
 * @return 0 for success
 */
int main() {

    int searchKey, i, j, seqSum = 0, binSum = 0, binTreeSum = 0, avlSum = 0;

    srand(time(NULL));

    for (i = 0; i < SEARCH_REPEAT; i++) {

        sequentialCount = binCount = binTreeCount = avlCount = 0;

        generateValues();

        for (j = 0; j < TAM; j++) {
            balanced_insert(array[j]);
            bin_tree_insert(array[j]);
        }

        heapSort();

        searchKey = rand();

        // Busca sequencial
        sequentialSearch(searchKey);

        // Busca binária
        binSearch(searchKey);

        // Busca na árvore de busca binária
        search(searchKey, root_bin_tree, &binTreeCount);

        // Busca na árvore AVL
        search(searchKey, root_avl, &avlCount);

        seqSum += sequentialCount;
        binSum += binCount;
        binTreeSum += binTreeCount;
        avlSum += avlCount;

    }

    printf("Média de comparações com %d repetições e %d elementos: \n", SEARCH_REPEAT, TAM);
    printf("Busca sequêncial:        %10.2f, com %d comparações;\n", (float) seqSum / (float) SEARCH_REPEAT, seqSum);
    printf("Busca binária:           %10.2f, com %d comparações;\n", (float) binSum / (float) SEARCH_REPEAT, binSum);
    printf("Busca em árvore binária: %10.2f, com %d comparações;\n", (float) binTreeSum / (float) SEARCH_REPEAT, binTreeSum);
    printf("Busca em árvore AVL:     %10.2f, com %d comparações;\n", (float) avlSum / (float) SEARCH_REPEAT, avlSum);

    return 0;

}