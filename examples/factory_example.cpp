#include "../minimal-ti.h"
#include <iostream>
#include <unordered_map>
#include <functional>

struct Animal {
    virtual std::string talk() = 0;
};

struct Dog : public Animal {
    std::string talk() override {
        return "Woof!";
    }
};

struct Cat : public Animal {
    std::string talk() override {
        return "Meow!";
    }
};

struct Cow : public Animal {
    std::string talk() override {
        return "Moo!";
    }
};

struct AnimalFactory {
    std::unordered_map<std::string, std::function<std::unique_ptr<Animal>()>> registry;

    template<typename T>
    void registerAnimal() {
        static_assert(std::is_base_of_v<Animal, T>, "You can only register 'Animal' types");

        auto constructorFunction = []() -> std::unique_ptr<Animal> {
            return std::make_unique<T>();
        };
        registry[mti::GetTypeId<T>().name_str()] = constructorFunction;
    }

    std::unique_ptr<Animal> spawnAnimal(const std::string& structName) {
        return registry.at(structName)(); 
    }
};

int main() {
    AnimalFactory factory;

    factory.registerAnimal<Dog>();
    factory.registerAnimal<Cat>();
    factory.registerAnimal<Cow>();

    std::vector<std::unique_ptr<Animal>> farm;

    farm.emplace_back(factory.spawnAnimal("Cow"));
    farm.emplace_back(factory.spawnAnimal("Cat"));
    farm.emplace_back(factory.spawnAnimal("Dog"));
    
    bool success = true;

    success &= farm[0]->talk() == "Moo!";
    success &= farm[1]->talk() == "Meow!";
    success &= farm[2]->talk() == "Woof!";

    if (success) {
        std::cout << "Success!\n";
        return 0;
    }

    return 1;
}