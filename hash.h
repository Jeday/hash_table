#ifndef HASH_H
#define HASH_H

#include <cmath>
#include <list>
#include <utility>

template<typename key, class hash, class is_equal>
class hset
    {
private:
    double A;

    hash hashing_fucntion;

    is_equal equal;

    int n;

    double dump;

    int h(const key& k){

        int h = hashing_fucntion(k);
        return floor( n*modf(h*A,&dump));


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


    };


void test_hash();

#endif // HASH_H
