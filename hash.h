#ifndef HASH_H
#define HASH_H

#include <cmath>
#include <list>
#include <utility>
#include <ostream>
#include <cstring>

template<typename key, class hash, class is_equal>
class hset
    {
private:
    double A;

    hash hashing_fucntion;

    is_equal equal;

    size_t n;
    size_t n2;

    double dump;

    size_t h(const key& k){
        return  floor( n*modf((hashing_fucntion(k))%n2*A,&dump));

    }

    std::list<std::pair<key,int>> ** table;

    int collusion_counter;
public:

    int collusions(){
        return collusion_counter;
    }


    hset(int size_factor){
         A = (sqrt(5)-1)/2;
         n = 2;
         for(int i = 1; i<size_factor; ++i)
             n*=2;
         n2 = n*n;
         table = new std::list<std::pair<key,int>>*[n];
         collusion_counter = 0;
         for(int i = 0;i<n;++i )
             table[i] = nullptr;
    }

    void insert(const key& k){
        int ind = h(k);
        if(table[ind] == nullptr)
            table[ind] = new std::list<std::pair<key,int>> {{k,1}};
        else{
                 collusion_counter+=1;
                 auto it = table[ind]->begin();
                 auto en = table[ind]->end();
                 while(it != en){
                         if(equal((*it).first,k)){
                             ++(*it).second;
                             break;
                             }
                         else
                              ++it;
                     }
                 if (it==en)
                     table[ind]->push_back({k,1});
            }

    }

    bool contains(const key&k){
          int ind = h(k);
          if(table[ind] == nullptr)
             return false;
          else{

                  collusion_counter+=1;
                   auto it = table[ind]->begin();
                   auto en = table[ind]->end();
                   while(it != en){
                           if(equal((*it).first,k)){
                                    return true;
                               }
                           else
                                ++it;
                       }
                   if (it==en)
                       return false;
              }
    }

    int count(const key&k){
          int ind = h(k);
          if(table[ind] == nullptr)
             return 0;
          else{

                  collusion_counter+=1;
                   auto it = table[ind]->begin();
                   auto en = table[ind]->end();
                   while(it != en){
                           if(equal((*it).first,k)){
                                    return (*it).second;
                               }
                           else
                                ++it;
                       }
                   if (it==en)
                       return 0;
              }
    }

    bool erase(const key&k)
    {
              int ind = h(k);
              if(table[ind] == nullptr)
                 return false;
              else{

                      collusion_counter+=1;
                       auto it = table[ind]->begin();
                       auto en = table[ind]->end();
                       while(it != en){
                               if(equal((*it).first,k)){
                                        table[ind]->erase(it);
                                        if(table[ind]->size() == 0){
                                            delete table[ind];
                                            table[ind] = nullptr;
                                            }
                                        return true;
                                   }
                               else
                                    ++it;
                           }
                       if (it==en)
                           return 0;
                  }
        }


    ~hset(){
      delete[] table;
    }

    void print_to_stream(std::ostream& os){
        for(int i = 0; i< n; i++){
            os<<i<<"\t";
                if(table[i] != nullptr){
                    auto it = table[i]->begin();
                    os<<(*it).first<<" | "<<(*it).second;
                    ++it;
                    while(it != table[i]->end()){
                       os<<" -> "<<(*it).first<<" | "<<(*it).second;
                       ++it;
                    }
                    os<<" -|";

                    }
                else
                     os<<"NULL";
            os<<std::endl;
          }
    }


    };




void test_hash();

#endif // HASH_H
