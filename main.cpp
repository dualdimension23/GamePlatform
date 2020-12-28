#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include "game.h"
#include "player.h"
#include "gamekey.h"

struct Bucket {
    std::string name;
    Bucket() {};
    Bucket(std::string name): name { name } {};
    std::string getName() { return this->name; };

};

struct Entity {
    std::map<std::string, std::shared_ptr<Bucket>> buckets;
    void addBucket(Bucket bucket) {
        std::pair<std::string, std::shared_ptr<Bucket>> newPair = std::make_pair(bucket.getName(), std::make_shared<Bucket>(bucket));
        buckets.insert(newPair);
    }

    bool eraseBucket(Bucket bucket) {
        auto it { buckets.find(bucket.getName()) };
        if(it != buckets.end()) {
            buckets.erase(it);
            return true;
        } else
            return false;
    }
    void printBuckets() {
        for(const auto& i : buckets) {
            std::cout << i.first << '\n';
        }
        std::cout << '\n';
    }

    std::ostream& print(std::ostream& o) const {
       for (const auto& i : buckets) {
           o << i.first << '\n';
       }
       o << '\n';
       return o;
    }

    friend std::ostream& operator<<(std::ostream&, const Entity&);
};

std::ostream& operator<<(std::ostream& o, const Entity& e) {
    o << "Operator << called...\n";
    e.print(o);
    return o;
}
int main() {
    std::cout << "Start of the program\n";
    Bucket bucket1 {"Bucket 1"};
    Bucket bucket2 {"Bucket 2"};
    Bucket bucket3 {"Bucket 3"};
    Entity entity;
    entity.addBucket(bucket1);
    entity.addBucket(bucket2);
    entity.addBucket(bucket3);
    std::cout << entity;


}
