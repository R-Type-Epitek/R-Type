//
// Created by Xavier VINCENT on 18/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network
{
    template<typename T>
    class ThreadSafeQueue {
        public:
            void push(T value);
            T pop();

        protected:
        private:
            std::queue<T> queue;
            std::mutex mutex;
            std::condition_variable cond;
    };
}
