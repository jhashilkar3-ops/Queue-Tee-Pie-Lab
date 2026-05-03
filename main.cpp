#include <iostream>
#include "src/cutie.hpp"
#include "src/hello.hpp"

int main() {

  Puppy         puppy;
  Kitty         kitty;
  Otters        otters;

  QueueTees queue;


  std::cout << queue.size() << "\n";

  queue.enqueue(&puppy);
  queue.enqueue(&kitty);
  queue.enqueue(&otters);


  std::cout << queue.size() << "\n";


  Cutie* first = queue.dequeue();
  std::cout << first->get_description()
            << " (cuteness: " << first->get_cuteness_rating() << ")\n";


  Cutie* second = queue.dequeue();
  std::cout << second->get_description()
            << " (cuteness: " << second->get_cuteness_rating() << ")\n";


  Cutie* third = queue.dequeue();
  std::cout << third->get_description()
            << " (cuteness: " << third->get_cuteness_rating() << ")\n";

  return 0;
}