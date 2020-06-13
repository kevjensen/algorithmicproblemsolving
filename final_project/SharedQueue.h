#ifndef FINAL_PROJECT_SHAREDQUEUE_H
#define FINAL_PROJECT_SHAREDQUEUE_H

#include <mutex>
#include <queue>

template <typename T>
class SharedQueue {
public:
    void push(T task);
    enum class PopResponse {
        no_task, task, terminate
    };
    PopResponse pop(T &task);
    void terminate();
private:
    std::queue<T> tasks;
    std::mutex lock;
    bool terminate_flag = false;
};

template<typename T>
void SharedQueue<T>::push(T task) {
    std::lock_guard<std::mutex> l(lock);
    tasks.push(task);
}

template<typename T>
typename SharedQueue<T>::PopResponse SharedQueue<T>::pop(T &task) {
    std::lock_guard<std::mutex> l(lock);

    if (terminate_flag) {
        return PopResponse::terminate;
    }

    if (tasks.empty()) {
        return PopResponse::no_task;
    }

    // Tasks is non-empty, provide a job
    task = tasks.front();
    tasks.pop();

    return PopResponse::task;
}

template<typename T>
void SharedQueue<T>::terminate() {
    std::lock_guard<std::mutex> l(lock);
    terminate_flag = true;
}

#endif //FINAL_PROJECT_SHAREDQUEUE_H
