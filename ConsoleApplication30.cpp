#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename K, typename V>
struct KeyValuePair {
    K key;
    V value;
};

// Простий клас хеш-таблиці
template <typename K, typename V>
class HashTable {
public:
    HashTable(size_t size) : table_size_(size) {
        table_.resize(table_size_);
    }

    // Додавання елемента до хеш-таблиці
    void insert(const K& key, const V& value) {
        size_t index = hashFunction(key);
        table_[index].push_back({ key, value });
    }

    // Пошук елемента за ключем
    bool find(const K& key, V& value) {
        size_t index = hashFunction(key);
        for (const auto& pair : table_[index]) {
            if (pair.key == key) {
                value = pair.value;
                return true; // Знайдено
            }
        }
        return false; // Не знайдено
    }

    // Видалення елемента за ключем
    bool remove(const K& key) {
        size_t index = hashFunction(key);
        for (auto it = table_[index].begin(); it != table_[index].end(); ++it) {
            if (it->key == key) {
                table_[index].erase(it);
                return true; // Видалено
            }
        }
        return false; // Не знайдено
    }

private:
    size_t table_size_;
    vector<vector<KeyValuePair<K, V>>> table_;

    // Проста хеш-функція (можна вдосконалити)
    size_t hashFunction(const K& key) {
        return hash<K>{}(key) % table_size_;
    }
};

int main() {
    HashTable<int, string> hashTable(10);

    hashTable.insert(1, "Value1");
    hashTable.insert(2, "Value2");
    hashTable.insert(3, "Value3");

    string value;
    if (hashTable.find(2, value)) {
       cout << "Found: " << value << endl;
    }
    else {
        cout << "Not found" << endl;
    }

    if (hashTable.remove(1)) {
        cout << "Deleted" << endl;
    }
    else {
        cout << "Failed to delete" << endl;
    }

    return 0;
}
