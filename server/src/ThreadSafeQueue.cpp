//
// Created by Xavier VINCENT on 18/12/2023.
//

#include "RTypeNetwork.hpp"

template<typename T>
void Network::ThreadSafeQueue<T>::push(T value)
{
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(std::move(value));
    cond.notify_one();
}

template<typename T>
T Network::ThreadSafeQueue<T>::pop()
{
    std::unique_lock<std::mutex> lock(mutex);
    cond.wait(lock, [this]{ return !queue.empty(); });
    T value = std::move(queue.front());
    queue.pop();
    return value;
}

template class Network::ThreadSafeQueue<Message *>;
