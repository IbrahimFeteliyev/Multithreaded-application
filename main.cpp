#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <set>
#include <random>

std::set<int> items;

std::mutex mtx;

std::condition_variable cv;

bool done = false;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(1, 100);


void producer(int id) {
    for (int i = 0; i < 2; ++i) {
 
        int item = dis(gen);


        std::unique_lock<std::mutex> lock(mtx);

    
        std::cout << "Producer " << id << " produced " << item << "\n";
        items.insert(item);

   
        lock.unlock();

 
        cv.notify_one();


        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


void consumer(int id) {
    while (true) {
        
        std::unique_lock<std::mutex> lock(mtx);

       
        cv.wait(lock, []{return !items.empty() || done;});

       
        if (!items.empty()) {
           
            auto it = items.begin();
            std::advance(it, dis(gen) % items.size());
            int item = *it;
            items.erase(it);

           
            lock.unlock();

           
            std::cout << "Consumer " << id << " consumed " << item << "\n";

          
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } else {
          
            if (done) {
            
                lock.unlock();
                break;
            }
        }
    }
}

int main() {
    
    std::thread p1(producer, 1);
    std::thread p2(producer, 2);
    std::thread p3(producer, 3);

   
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);

    
    p1.join();
    p2.join();
    p3.join();

  
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
        cv.notify_all();
    }

   
    c1.join();
    c2.join();

    return 0;
}
