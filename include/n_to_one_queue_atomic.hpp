/*
ORIGINAL IMPL : http://www.boost.org/doc/libs/1_53_0_beta1/doc/html/atomic/usage_examples.html
The purpose of the wait-free multi-producer queue is to allow an arbitrary 
number of producers to enqueue objects which are retrieved and processed in 
FIFO order by a single consumer. 

USAGE:

n_to_one_queue_atomic<int> q;

// insert elements
q.push(42);
q.push(2);

// pop elements
n_to_one_queue_atomic<int>::node * x = q.pop_all()
while(x) {
  X * tmp = x;
  x = x->next;
  // process tmp->data, probably delete it afterwards
  delete tmp;
}

*/

#include <boost/atomic.hpp>

template<typename T>
class n_to_one_queue_atomic {
public:
  struct node {
    T data;
    node * next;
  }
  void push(const T &data)
  {
    node * n = new node;
    n.data = data;
    node * stale_head = head_.load(boost::memory_order_relaxed);
    do {
      node->next = stale_head;
    } while (!head_.compare_exchange_weak(stale_head, node, boost::memory_order_release);
  }

  node * pop_all(void)
  {
    T * last = pop_all_reverse(), * first = 0;
    while(last) {
      T * tmp = last;
      last = last->next;
      tmp->next = first;
      first = tmp;
    }
    return first;
  }

  n_to_one_queue_atomic() : head_(0) {}

  // alternative interface if ordering is of no importance
  node * pop_all_reverse(void)
  {
    return head_.exchange(0, boost::memory_order_consume);
  }
private:
  boost::atomic<node *> head_;
}