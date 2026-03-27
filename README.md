# Simulador de Esteira Industrial (Produtor/Consumidor)

Este projeto implementa um simulador de uma esteira mecânica de fábrica utilizando **multithreading em C++**. O sistema resolve o problema clássico do **Buffer Limitado**, onde múltiplos processos de entrada (produtores) e saída (consumidores) interagem com um recurso compartilhado (a esteira) de forma sincronizada.

---

## Funcionalidades

**Múltiplas Entradas**

- 3 threads produtoras gerando produtos.
- Cada produto possui **ID único**.
- Qualidade do produto definida de forma **aleatória**.

**Múltiplas Saídas**

- 2 threads consumidoras.
- Cada consumidor classifica produtos em:
  - **Aprovados**
  - **Reprovados**

**Controle de Fluxo**

- A esteira possui **capacidade limitada de 10 itens**.
- Evita perda de dados ou transbordo do buffer.

**Sincronização**

- Uso de **semáforos POSIX** e **mutex** para controle de concorrência.
- Garante exclusão mútua e sincronização correta entre produtores e consumidores.

**Tempos Dinâmicos**

- Tempos de produção e processamento são gerados aleatoriamente para simular um ambiente real.

---

## Estrutura do Projeto

### 1. `Esteira.hpp` / `Esteira.cpp`

Implementa a classe `Esteira`, responsável por encapsular o **buffer compartilhado**.

**Componentes principais**

- `std::queue<Produto>`  
  Armazena os produtos na ordem de chegada (**FIFO**).

- `std::mutex`  
  Garante que apenas uma thread manipule a fila por vez.

- `sem_t espacos_vazios`  
  Controla o limite da esteira.  
  Bloqueia produtores quando o buffer está cheio.

- `sem_t itens_disponiveis`  
  Controla a disponibilidade de produtos.  
  Bloqueia consumidores quando o buffer está vazio.

---

### 2. `main.cpp`

Responsável pela criação das threads e execução da simulação.

**Threads produtoras (`thread_entrada`)**

- Geram produtos a cada **1.5s a 3.0s**.

**Threads consumidoras (`thread_saida`)**

- Processam produtos a cada **0.4s a 0.9s**.
- Garantem **vazão maior que a entrada**, evitando acúmulo excessivo.

**Aleatoriedade**

- Utilização de `std::default_random_engine` para:
  - gerar qualidade dos produtos
  - gerar tempos de produção e processamento

---

## Como Compilar e Executar

O projeto utiliza a biblioteca **pthread** para gerenciamento de threads em Linux.

### Compilação

```bash
g++ -o simulador_esteira main.cpp Esteira.cpp -pthread
