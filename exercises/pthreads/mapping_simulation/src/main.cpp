#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <numeric>
#include <mutex>

std::mutex mtx; // Mutex to protect shared data

void simulate_work(int thread_id, int num_threads, const std::vector<int>& durations, std::vector<int>& thread_work) {
    int total_duration = 0;
    for (int i = thread_id; i < durations.size(); i += num_threads) {
        std::this_thread::sleep_for(std::chrono::milliseconds(durations[i]));
        total_duration += durations[i];
    }
    
    // Protect the shared data with a mutex
    std::lock_guard<std::mutex> lock(mtx);
    thread_work[thread_id] = total_duration;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <num_workers>" << std::endl;
        return 1;
    }

    int num_workers = std::stoi(argv[1]);

    std::vector<int> durations;
    int duration;
    while (std::cin >> duration) {
        durations.push_back(duration);
    }

    int total_duration = std::accumulate(durations.begin(), durations.end(), 0);
    std::vector<int> thread_work(num_workers, 0);
    std::vector<std::thread> threads;

    // Estático por bloque
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_workers; ++i) {
        threads.emplace_back(simulate_work, i, num_workers, durations, std::ref(thread_work));
    }
    for (auto& thread : threads) {
        thread.join();
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    double block_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // Estático cíclico
    threads.clear();
    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_workers; ++i) {
        threads.emplace_back(simulate_work, i, num_workers, durations, std::ref(thread_work));
    }
    for (auto& thread : threads) {
        thread.join();
    }
    end_time = std::chrono::high_resolution_clock::now();
    double cyclic_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    // Dinámico
    threads.clear();
    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_workers; ++i) {
        threads.emplace_back(simulate_work, i, num_workers, durations, std::ref(thread_work));
    }
    for (auto& thread : threads) {
        thread.join();
    }
    end_time = std::chrono::high_resolution_clock::now();
    double dynamic_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    double serial_duration = static_cast<double>(total_duration);
    double block_speedup = serial_duration / block_duration;
    double cyclic_speedup = serial_duration / cyclic_duration;
    double dynamic_speedup = serial_duration / dynamic_duration;

    double block_efficiency = block_speedup / num_workers;
    double cyclic_efficiency = cyclic_speedup / num_workers;
    double dynamic_efficiency = dynamic_speedup / num_workers;

    std::cout << total_duration << "\t" << 0;
    for (int i = 0; i < num_workers; ++i) {
        std::cout << "\t" << i;
    }
    std::cout << "\tDuration\tSpeedup\tEfficiency" << std::endl;

    std::cout << "Block\t";
    for (int i = 0; i < num_workers; ++i) {
        std::cout << thread_work[i] << "\t";
    }
    std::cout << block_duration / 1000.0 << "\t" << block_speedup << "\t" << block_efficiency << std::endl;

    std::cout << "Cyclic\t";
    for (int i = 0; i < num_workers; ++i) {
        std::cout << thread_work[i] << "\t";
    }
    std::cout << cyclic_duration / 1000.0 << "\t" << cyclic_speedup << "\t" << cyclic_efficiency << std::endl;

    std::cout << "Dynamic\t";
    for (int i = 0; i < num_workers; ++i) {
        std::cout << thread_work[i] << "\t";
    }
    std::cout << dynamic_duration / 1000.0 << "\t" << dynamic_speedup << "\t" << dynamic_efficiency << std::endl;

    return 0;
}
