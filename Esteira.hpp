#ifndef ESTEIRA_HPP
#define ESTEIRA_HPP

#include <queue>
#include <mutex>
#include <semaphore.h>

struct Produto {
    int id;
    bool boaQualidade;
};

class Esteira {
private:
    std::queue<Produto> fila;
    std::mutex mtx;
    sem_t espacos_vazios;
    sem_t itens_disponiveis;
    int capacidade;

public:
    Esteira(int tam);
    ~Esteira();

    void inserir(Produto p, int id_entrada);
    Produto retirar(int id_saida);
};

#endif