#include <iostream>
#include <vector>
#include <bitset>
#include <functional>
#include <string>
#include <cstdio>

class BloomFilter {
private:
    std::vector<bool> bits;
    size_t size;
    std::vector<std::function<size_t(const std::string&)>> hash_functions;

public:
    BloomFilter(size_t size, size_t num_hashes) : size(size) {
        bits.resize(size, false);
        
        // Create num_hashes different hash functions
        for (size_t i = 0; i < num_hashes; ++i) {
            // Using different seeds for each hash function
            hash_functions.push_back([i, this](const std::string& item) {
                return std::hash<std::string>{}(item + std::to_string(i)) % this->size;
            });
        }
    }

    void add(const std::string& item) {
        for (auto& hash_fn : hash_functions) {
            size_t index = hash_fn(item);
            bits[index] = true;
        }
    }

    bool possibly_contains(const std::string& item) const {
        for (auto& hash_fn : hash_functions) {
            size_t index = hash_fn(item);
            if (!bits[index]) {
                return false;
            }
        }
        return true;
    }

    void clear() {
        std::fill(bits.begin(), bits.end(), false);
    }

    double estimated_false_positive_rate(size_t num_items) const {
        double k = hash_functions.size();
        double m = size;
        double n = num_items;
        return pow(1 - exp(-k * n / m), k);
    }
};

int main() {
    std::cout << "Bloom Filter Console Application\n";
    std::cout << "--------------------------------\n";

    size_t filter_size;
    size_t num_hashes;

    std::cout << "Enter Bloom filter size (bits): ";
    std::cin >> filter_size;
    std::cout << "Enter number of hash functions: ";
    std::cin >> num_hashes;

    BloomFilter bloom(filter_size, num_hashes);

    bool active = true; 
    while (active) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add item\n";
        std::cout << "2. Check item\n";
        std::cout << "3. Clear filter\n";
        std::cout << "4. Estimate false positive rate\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose option: ";

        int choice;
        choice = static_cast<int>(getchar());
        std::cin >> choice;

        switch(choice){
            case 1: {
                std::string item;
                std::cout << "Enter item to add: ";
                std::cin >> item;
                bloom.add(item);
                std::cout << "Item added to Bloom filter.\n";
                break;
            }
            case 2: {
                std::string item;
                std::cout << "Enter item to check: ";
                std::cin >> item;
                if (bloom.possibly_contains(item)) {
                    std::cout << "Item MAY be in the filter (could be a false positive).\n";
                }
                else {
                    std::cout << "Item is DEFINITELY NOT in the filter.\n";
                }
                break;
            }
            case 3: {
                bloom.clear();
                std::cout << "Bloom filter cleared.\n";
                break;
            }
            case 4: {
                size_t num_items;
                std::cout << "Enter estimated number of items in filter: ";
                std::cin >> num_items;
                double rate = bloom.estimated_false_positive_rate(num_items);
                std::cout << "Estimated false positive rate: " << rate * 100 << "%\n";
                break;
            }
            case 5: {
                active = false;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    return 0;
}