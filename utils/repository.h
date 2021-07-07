// repository.h
// marc, marc@gruita.ro

#pragma once
#include <vector>
#include <fstream>
#include <iostream>

template <typename T>
class FileRepository {
private:
    std::vector<T> data;
    std::string filename;

    void load() {
        std::ifstream in(filename);

        T t;
        while (in >> t) {
            data.push_back(t);
        }
    }
public:
    explicit FileRepository<T>(std::string filename): filename(std::move(filename)) {
        data = {};
        this->load();
    }

    T find(int id) {
        for (auto t: data) {
            if (t.getId() == id) return t;
        }
        throw std::runtime_error("didn't find it");
    }

    void add(T t) {
        for (auto _: data) {
            if (_ == t) throw std::runtime_error("existing already");
        }

        std::cout<<"added "<<t.toString();
        data.push_back(t);
    }

    void update(int id, T t) {}

    T remove(int id) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i].getId() == id) {
                T result{ data[i] };
                data.erase(i + data.begin());
                return result;
            }
        }
        throw std::runtime_error("not found for remove");
    }

    std::vector<T> getAll() { return data; }

    int size() { return data.size(); }
};