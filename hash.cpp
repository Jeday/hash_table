#include "hash.h"
#include <ctime>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

class eq{
public:
    bool operator()(const std::string& s1,const std::string& s2){
        return s1==s2;
    }
    };

void test_hash(){

    hset<std::string, std::hash<std::string>, eq> set(12);
    std::vector<std::string> rand_pool;
    std::unordered_multiset<std::string> std_set;
    for(int i = 0; i<1000; ++i){
            std::string p;
            char c;
            for(int j = 0; j<10;++j){
                    c  = rand()%256;
                    p+=c;
                }
            set.insert(p);
            std_set.insert(p);
        }


    double time_passed = 0;
    double std_time_passed = 0;
    int iterations = 0;
    while(time_passed < 0.01){
    iterations++;
    for(int i = 0; i<100; ++i){
            std::string p;
            char c;
            for(int j = 0; j<10;++j){
                    c  = rand()%256;
                    p+=c;
                }
           rand_pool.push_back(p);
        }
    bool t = true;
    time_t  start = clock();
    for(int i=0; i<rand_pool.size(); ++i){
            set.insert(rand_pool[i]);
        }
    for(int i=0; i<rand_pool.size()/2; ++i){
            t = t && set.contains(rand_pool[rand()%100]);
        }
    for(int i=0; i<rand_pool.size(); ++i){
            set.erase(rand_pool[i]);
        }
    start = clock() - start;
    if (!t)
        std::cout<<"insertion error"<<std::endl;
    time_passed += double(start)/CLOCKS_PER_SEC;

    time_t std_start = clock();

    for(int i=0; i<rand_pool.size(); ++i){
            std_set.insert(rand_pool[i]);
        }
    for(int i=0; i<rand_pool.size()/2; ++i){
             std_set.find(rand_pool[rand()%100]);
        }
    for(int i=0; i<rand_pool.size(); ++i){
            std_set.erase(rand_pool[i]);
        }

    std_start = clock() - std_start;
    std_time_passed += double(std_start)/CLOCKS_PER_SEC;

    }



    std::cout<<"my hash:"<<time_passed<<" sec\tvs std hash:"<<std_time_passed<<" sec with "<<iterations*100<<" inserts/deletes "<<std::endl;
}
