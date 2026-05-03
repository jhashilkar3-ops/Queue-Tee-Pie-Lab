#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include "../src/cutie.hpp"
#include "../src/hello.hpp"

TEST_CASE("A newly created queue is empty", "[queue][empty]") {
    QueueTees q;
    REQUIRE(q.isEmpty());
    REQUIRE(q.size() == 0);
    REQUIRE_FALSE(q.isFull());
}

TEST_CASE("Assignment example output scenario", "[queue]") {
    Puppy         puppy;
    Kitty         kitty;
    Otters        Otter;
    QueueTees     queue;

    REQUIRE(queue.size() == 0);

    queue.enqueue(&puppy);
    queue.enqueue(&kitty);
    queue.enqueue(&Otter);

    REQUIRE(queue.size() == 3);

    REQUIRE(queue.dequeue()->get_description() == "A fluffy little puppy");
    REQUIRE(queue.dequeue()->get_description() == "A tiny curious kitty");
    REQUIRE(queue.dequeue()->get_description() == "An Otter with huge eyes");

    REQUIRE(queue.size() == 0);
}

TEST_CASE("enqueue adds elements and updates size", "[queue][enqueue]") {
    Puppy p; Kitty k; Otters o;
    QueueTees q(3);

    SECTION("size increments with each enqueue") {
        q.enqueue(&p); REQUIRE(q.size() == 1);
        q.enqueue(&k); REQUIRE(q.size() == 2);
        q.enqueue(&o); REQUIRE(q.size() == 3);
    }

    SECTION("queue reports full at capacity") {
        q.enqueue(&p); q.enqueue(&k); q.enqueue(&o);
        REQUIRE(q.isFull());
    }

    SECTION("overflow enqueue leaves queue unchanged") {
        q.enqueue(&p); q.enqueue(&k); q.enqueue(&o);
        q.enqueue(&p);
        REQUIRE(q.size() == 3);
    }
}

TEST_CASE("dequeue removes front element (FIFO)", "[queue][dequeue]") {
    Puppy p; Kitty k; Otters o;
    QueueTees q;
    q.enqueue(&p); q.enqueue(&k); q.enqueue(&o);

    SECTION("first dequeue returns first enqueued") {
        REQUIRE(q.dequeue()->get_description() == "A fluffy little puppy");
    }

    SECTION("dequeue follows FIFO order") {
        REQUIRE(q.dequeue()->get_description() == "A fluffy little puppy");
        REQUIRE(q.dequeue()->get_description() == "A tiny curious kitty");
        REQUIRE(q.dequeue()->get_description() == "An Otter with huge eyes");
        REQUIRE(q.isEmpty());
    }

    SECTION("size decrements after each dequeue") {
        q.dequeue(); REQUIRE(q.size() == 2);
        q.dequeue(); REQUIRE(q.size() == 1);
    }
}

TEST_CASE("dequeue on empty queue returns nullptr", "[queue][dequeue][edge]") {
    QueueTees q;
    REQUIRE(q.dequeue() == nullptr);
    REQUIRE(q.isEmpty());
}

TEST_CASE("clear empties the queue", "[queue][clear]") {
    Puppy p; Kitty k;
    QueueTees q;
    q.enqueue(&p); q.enqueue(&k);
    q.clear();
    REQUIRE(q.isEmpty());
    REQUIRE(q.size() == 0);
}

TEST_CASE("Queue handles circular buffer wraparound", "[queue][circular]") {
    Puppy p; Kitty k; Otters o;
    QueueTees q(2);

    q.enqueue(&p);
    q.enqueue(&k);
    q.dequeue();
    q.enqueue(&o);

    REQUIRE(q.size() == 2);
    REQUIRE(q.dequeue()->get_description() == "A tiny curious kitty");
    REQUIRE(q.dequeue()->get_description() == "An Otter with huge eyes");
}