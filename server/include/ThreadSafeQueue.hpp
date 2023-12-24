//
// Created by Xavier VINCENT on 18/12/2023.
//

#pragma once

#include "RTypeNetwork.hpp"

namespace Network
{
  /**
     * @brief A thread-safe queue implementation.
     *
     * This template class implements a thread-safe queue using std::queue.
     * It uses a mutex and a condition variable to ensure thread safety during
     * push and pop operations.
     *
     * @param T Type of the elements in the queue.
     */
  template<typename T>
  class ThreadSafeQueue {
  public:
    /**
         * @brief Pushes an element into the queue.
         *
         * This method locks the queue, pushes the element, and then unlocks it.
         * After pushing the element, it notifies one waiting thread, if any.
         *
         * @param value The value to be pushed into the queue.
         */
    void push(T value);

    /**
         * @brief Pops an element from the queue.
         *
         * This method waits for an element to be available if the queue is
         * empty. It locks the queue, pops the element, and then unlocks it.
         *
         * @return T The popped element from the queue.
         */
    T pop();

  protected:
  private:
    std::queue<T>
      queue;          ///< Standard queue used as the underlying data structure.
    std::mutex mutex; ///< Mutex for ensuring thread safety during push and
                      ///< pop operations.
    std::condition_variable cond; ///< Condition variable used to wait for
                                  ///< and notify about queue operations.
  };
} // namespace Network
