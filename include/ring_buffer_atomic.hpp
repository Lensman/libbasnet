#pragma once

#include <boost/atomic.hpp>
/*
ORIGINAL IMPL : 
A wait-free ring buffer provides a mechanism for relaying objects from 
one single "producer" thread to one single "consumer" thread without any locks. 
The operations on this data structure are "wait-free" which means that each operation 
finishes within a constant number of steps. This makes this data structure suitable 
for use in hard real-time systems or for communication with interrupt/signal handlers. 


*/

//size_t wraps_at = std::numeric_limits<size_t>::max();


template<typename T, size_t capacity>
class ring_buffer_atomic {
public:
  ring_buffer_atomic() : head_(0), tail_(0) {}

	bool push(const T & value)
	{
		size_t head = head_.load(boost::memory_order_relaxed);
		size_t next_head = next(head);
		if ( next_head == tail_.load(boost::memory_order_acquire) )
			return false;
		ring_[head] = value;
		head_.store(next_head, boost::memory_order_release);
		return true;
	}
	size_t get_tail(){
		size_t tail = tail_.load(boost::memory_order_relaxed);
		return tail;
	}
	size_t get_head(){
		size_t head = head_.load(boost::memory_order_relaxed);
		return head;
	}
	size_t count(){
		size_t tail = tail_.load(boost::memory_order_relaxed);
		size_t head = head_.load(boost::memory_order_relaxed);
		if (head < tail){
			return head + ( capacity-tail );
		}else{
			return head - tail;
		}
	}
	bool pop(T & value)
	{
		size_t tail = tail_.load(boost::memory_order_relaxed);
		if ( tail == head_.load(boost::memory_order_acquire))
			return false;
		value = ring_[tail];
		tail_.store(next(tail), boost::memory_order_release);
		return true;
	}
private:
	size_t next(size_t current)
	{
		return (current + 1) % capacity; 
	}
	boost::atomic<size_t> head_, tail_;
	/* 
	 Conveniently use the buffer as padding for variables
	 to avoid locality penalties
	 */
	T ring_[capacity];

};