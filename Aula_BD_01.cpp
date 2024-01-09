#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>

// Definindo as categorias e senhoridades
enum Cargo { UX, DEV, GERENTE, CEO, TEAM_WORKS };
enum Senhoridade { JUNIOR, PLENO, SENIOR };

// Estrutura para representar um funcionário
struct Funcionario {
    int ID;
    std::string nome;
    Cargo cargo;
    double salario;
    int tempo_de_casa;
    Senhoridade senioridade;
};

// Função para gerar registros aleatórios
std::vector<Funcionario> gerar_registros() {
    std::vector<Funcionario> registros;
    registros.reserve(40000); // Reserva espaço para evitar a exceção de std::length_error

    std::srand(static_cast<unsigned int>(time(0))); // Seed para geração de números aleatórios

    for (int i = 0; i < 40000; ++i) {
        Funcionario funcionario;
        funcionario.ID = i + 1;
        funcionario.nome = "Funcionario" + std::to_string(i + 1);
        funcionario.cargo = static_cast<Cargo>(std::rand() % 5);
        funcionario.salario = (std::rand() % 5000 + 3000) * 1.0; // Salário entre 3000 e 8000
        funcionario.tempo_de_casa = std::rand() % 10;
        funcionario.senioridade = static_cast<Senhoridade>(std::rand() % 3);

        registros.push_back(funcionario);
    }

    return registros;
}

// Função para calcular o custo total da folha de pagamento
double calcular_custo_de_folha(const std::vector<Funcionario>& registros) {
    double custo_total = 0.0;
    for (const auto& funcionario : registros) {
        custo_total += funcionario.salario;
    }
    return custo_total;
}

// Função para demitir funcionários
std::vector<Funcionario> layoff(const std::vector<Funcionario>& registros) {
    std::vector<Funcionario> novos_registros;
    novos_registros.reserve(registros.size() - 12000);

    for (size_t i = 0; i < registros.size() - 12000; ++i) {
        novos_registros.push_back(registros[i]);
    }

    return novos_registros;
}

// Função para medir o tempo usando QueryPerformanceCounter
double medir_tempo_gerar_registros() {
    LARGE_INTEGER frequencia, inicio, fim;
    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);

    std::vector<Funcionario> registros = gerar_registros();

    QueryPerformanceCounter(&fim);

    return static_cast<double>(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart * 1000.0; // Convertendo para milissegundos
}

// Função para medir o tempo usando QueryPerformanceCounter
double medir_tempo_calcular_custo(const std::vector<Funcionario>& registros) {
    LARGE_INTEGER frequencia, inicio, fim;
    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);

    double custo = calcular_custo_de_folha(registros);

    QueryPerformanceCounter(&fim);

    return static_cast<double>(fim.QuadPart - inicio.QuadPart) / frequencia.QuadPart * 1000.0; // Convertendo para milissegundos
}

int main() {
    // Medindo o tempo de execução para gerar registros
    double duracao_gerar_registros = medir_tempo_gerar_registros();
    std::cout << "Tempo para gerar registros: " << std::fixed << std::setprecision(8) << duracao_gerar_registros << " milissegundos\n";

    // Gerando registros
    std::vector<Funcionario> registros = gerar_registros();

    // Calculando e imprimindo o custo inicial da folha de pagamento
    double custo_inicial = calcular_custo_de_folha(registros);
    double duracao_calcular_custo_inicial = medir_tempo_calcular_custo(registros);
    std::cout << "Custo inicial da folha de pagamento: R$ " << std::fixed << std::setprecision(2) << custo_inicial << "\n";
    std::cout << "Tempo para calcular o custo inicial: " << std::fixed << std::setprecision(8) << duracao_calcular_custo_inicial << " milissegundos\n";

    // Demitindo funcionários
    std::vector<Funcionario> registros_apos_layoff = layoff(registros);

    // Calculando e imprimindo o custo após o layoff
    double custo_apos_layoff = calcular_custo_de_folha(registros_apos_layoff);
    double duracao_calcular_custo_apos_layoff = medir_tempo_calcular_custo(registros_apos_layoff);
    std::cout << "Custo apos layoff: R$ " << std::fixed << std::setprecision(2) << custo_apos_layoff << "\n";
    std::cout << "Tempo para calcular o custo apos layoff: " << std::fixed << std::setprecision(8) << duracao_calcular_custo_apos_layoff << " milissegundos\n";

    return 0;
}
