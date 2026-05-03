#ifndef CUTIE_HPP
#define CUTIE_HPP

#include <string>
#include <iostream>
#include <stdexcept>

class Cutie {
private:
    std::string description;
    int cuteness_rating;

public:
    Cutie(std::string description, int cuteness_rating) {
        this->description     = description;
        this->cuteness_rating = cuteness_rating;
    }

    virtual std::string get_description()    = 0;
    virtual int         get_cuteness_rating() = 0;

    virtual ~Cutie() = default;
};

class Puppy : public Cutie {
public:
    Puppy() : Cutie("A fluffy little puppy", 10) {}
    std::string get_description()    override { return "A fluffy little puppy"; }
    int         get_cuteness_rating() override { return 10; }
};

class Kitty : public Cutie {
public:
    Kitty() : Cutie("A tiny curious kitty", 9) {}
    std::string get_description()    override { return "A tiny curious kitty"; }
    int         get_cuteness_rating() override { return 9; }
};

class Otters : public Cutie {
public:
    Otters() : Cutie("An Otter with huge eyes", 11) {}
    std::string get_description()    override { return "An Otter with huge eyes"; }
    int         get_cuteness_rating() override { return 11; }
};

class QueueTees {
public:
    explicit QueueTees(int capacity = 10)
        : capacity_(capacity), count_(0), front_(0), back_(0)
    {
        if (capacity < 1)
            throw std::invalid_argument("Capacity must be at least 1.");
        data_ = new Cutie*[capacity];
    }

    ~QueueTees() { delete[] data_; }

    QueueTees(const QueueTees&)            = delete;
    QueueTees& operator=(const QueueTees&) = delete;

    void enqueue(Cutie* item) {
        if (isFull()) {
            std::cout << "Queue is full! Could not enqueue: "
                      << item->get_description() << "\n";
            return;
        }
        data_[back_] = item;
        back_        = (back_ + 1) % capacity_;
        ++count_;
    }

    Cutie* dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty! Nothing to dequeue.\n";
            return nullptr;
        }
        Cutie* item = data_[front_];
        front_      = (front_ + 1) % capacity_;
        --count_;
        return item;
    }

    int  size()    const { return count_; }
    bool isEmpty() const { return count_ == 0; }
    bool isFull()  const { return count_ == capacity_; }

    void clear() {
        front_ = back_ = count_ = 0;
        std::cout << "Queue has been cleared.\n";
    }

private:
    Cutie** data_;
    int     capacity_;
    int     count_;
    int     front_;
    int     back_;
};

template <typename T>
class Queue {
public:
    explicit Queue(int capacity = 10)
        : capacity_(capacity), count_(0), front_(0), back_(0)
    {
        if (capacity < 1)
            throw std::invalid_argument("Capacity must be at least 1.");
        data_ = new T*[capacity];
    }

    ~Queue() { delete[] data_; }

    Queue(const Queue&)            = delete;
    Queue& operator=(const Queue&) = delete;

    void enqueue(T* item) {
        if (isFull()) {
            std::cout << "Queue is full! Could not enqueue item.\n";
            return;
        }
        data_[back_] = item;
        back_        = (back_ + 1) % capacity_;
        ++count_;
    }

    T* dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty! Nothing to dequeue.\n";
            return nullptr;
        }
        T* item = data_[front_];
        front_  = (front_ + 1) % capacity_;
        --count_;
        return item;
    }

    int  size()    const { return count_; }
    bool isEmpty() const { return count_ == 0; }
    bool isFull()  const { return count_ == capacity_; }

    void clear() {
        front_ = back_ = count_ = 0;
        std::cout << "Queue has been cleared.\n";
    }

private:
    T** data_;
    int capacity_;
    int count_;
    int front_;
    int back_;
};

#endif