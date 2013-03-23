#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP
#include <queue>

#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/thread/condition.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>


// Priority queue, with a wrapper for the container
class handler_priority_queue 
{
public:
	handler_priority_queue() : is_not_writing(true) {
	}

  void add(int priority, boost::function<void()> function)
  {
	 
#ifndef AOSNET_USE_THREAD_LOCKS
	 //Lock while we push onto the queue
	 boost::mutex::scoped_lock lock(m_mutex);
	 m_is_writing.wait(lock, boost::bind(&handler_priority_queue::is_not_writing, this));
#endif

	 is_not_writing = false;
     handlers_.push(queued_handler(priority, function));
	 is_not_writing = true;	

#ifdef AOSNET_USE_THREAD_LOCKS
	// Unlock and notify when we are done
	 lock.unlock();
	 m_is_writing.notify_one();
#endif
	 
  }

  void execute_all()
  {

    while (!handlers_.empty()  )
    {
      queued_handler handler = handlers_.top();
      handler.execute();
      handlers_.pop();
    }
	
  }

  // A generic wrapper class for handlers to allow the invocation to be hooked.
  template <typename Handler>
  class wrapped_handler
  {
  public:
    wrapped_handler(handler_priority_queue& q, int p, Handler h)
      : queue_(q), priority_(p), handler_(h)
    {
    }

    void operator()(){handler_();}

    template <typename Arg1>
    void operator()(Arg1 arg1){handler_(arg1);}

    template <typename Arg1, typename Arg2>
    void operator()(Arg1 arg1, Arg2 arg2){handler_(arg1, arg2);}

  //private:
    handler_priority_queue& queue_;
    int priority_;
    Handler handler_;
  };

  template <typename Handler>
  wrapped_handler<Handler> wrap(int priority, Handler handler)
  {
    return wrapped_handler<Handler>(*this, priority, handler);
  }

private:
  class queued_handler
  {
  public:
    queued_handler(int p, boost::function<void()> f)
      : priority_(p), function_(f)
    {
    }
    void execute(){
	//std::cout <<  "(" << priority_ << ")";	
		function_();
	
	}

    friend bool operator<(const queued_handler& a,
        const queued_handler& b){return a.priority_ < b.priority_;}

	private:
		int priority_;
		boost::function<void()> function_;
	};


	bool is_not_writing;
	boost::mutex m_mutex;
    boost::condition m_is_writing;

	std::priority_queue<queued_handler> handlers_;
};

// Custom invocation hook for wrapped handlers.
template <typename Function, typename Handler>
void asio_handler_invoke(Function f,
    handler_priority_queue::wrapped_handler<Handler>* h)
{
  h->queue_.add(h->priority_, f);
}
#endif