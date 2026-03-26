#include "Esteira.hpp"
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include <iostream>

void thread_entrada(int id, Esteira& e) {
    std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count() + id);
    std::uniform_int_distribution<int> dist_tempo(1500, 3000);
    std::uniform_int_distribution<int> dist_qualidade(0, 1);

    int count = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(dist_tempo(gen)));
        
        Produto p = {(id * 100) + count++, dist_qualidade(gen) == 1};
        e.inserir(p, id);
    }
}

void thread_saida(int id, Esteira& e) {
    std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count() + id + 50);
    std::uniform_int_distribution<int> dist_tempo(400, 900);

    while (true) {
        Produto p = e.retirar(id);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(dist_tempo(gen)));
        
        std::cout << "\t\t[Saída " << id << "] Produto " << p.id 
                  << " classificado como: " << (p.boaQualidade ? "APROVADO" : "REPROVADO") << std::endl;
    }
}

int main() {
    Esteira minhaEsteira(10);
    std::vector<std::thread> operarios;

    for (int i = 1; i <= 3; ++i) 
        operarios.emplace_back(thread_entrada, i, std::ref(minhaEsteira));

    for (int i = 1; i <= 2; ++i) 
        operarios.emplace_back(thread_saida, i, std::ref(minhaEsteira));

    for (auto& t : operarios) t.join();

    return 0;
}