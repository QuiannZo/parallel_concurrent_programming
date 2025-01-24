#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <omp.h>

int main() {
    std::vector<double> numbers;
    double num;
    
    // Leer números flotantes de la entrada estándar.
    while (std::cin >> num) {
        numbers.push_back(num);
    }

    // Asegurarse de que haya al menos un número.
    if (numbers.empty()) {
        std::cerr << "No se ingresaron números." << std::endl;
        return 1;
    }

    // Calcular los datos concurrentemente utilizando omp.
    double min_val = std::numeric_limits<double>::max();
    double max_val = std::numeric_limits<double>::min();
    double sum = 0.0;
    double sum_squared = 0.0;

    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum) reduction(+:sum_squared)
    for (size_t i = 0; i < numbers.size(); i++) {
        double num = numbers[i];
        min_val = std::min(min_val, num);
        max_val = std::max(max_val, num);
        sum += num;
        sum_squared += num * num;
    }

    // promedio y la desviación estándar.
    double average = sum / numbers.size();
    double variance = (sum_squared / numbers.size()) - (average * average);
    double std_deviation = std::sqrt(variance);

    std::cout << "Mínimo: " << min_val << std::endl;
    std::cout << "Promedio: " << average << std::endl;
    std::cout << "Desviación Estándar: " << std_deviation << std::endl;
    std::cout << "Máximo: " << max_val << std::endl;

    return 0;
}
