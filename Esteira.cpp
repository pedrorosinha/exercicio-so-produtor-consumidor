#include "Esteira.hpp"
#include <iostream>

Esteira::Esteira(int tam) : capacidade(tam) {
    sem_init(&espacos_vazios, 0, tam);
    sem_init(&itens_disponiveis, 0, 0);
}

Esteira::~Esteira() {
    sem_destroy(&espacos_vazios);
    sem_destroy(&itens_disponiveis);
}

void Esteira::inserir(Produto p, int id_entrada) {
    sem_wait(&espacos_vazios);
    
    std::lock_guard<std::mutex> lock(mtx);
    fila.push(p);
    std::cout << "[Entrada " << id_entrada << "] Inseriu item " << p.id 
              << (p.boaQualidade ? " (Boa Qualidade)" : " (Má Qualidade)") << std::endl;
    
    sem_post(&itens_disponiveis);
}

Produto Esteira::retirar(int id_saida) {
    sem_wait(&itens_disponiveis);
    
    mtx.lock();
    Produto p = fila.front();
    fila.pop();
    mtx.unlock();
    
    sem_post(&espacos_vazios);
    return p;
}