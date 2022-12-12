/**********************************************************************
 * ProcessQueue.h - ADT implementing a generic processing queue.
 * Copyright (C) 2022 Paul Reeve <pdjr@pdjr.eu>
 */



#ifndef N2K_PROCESS_QUEUE
#define N2K_PROCESS_QUEUE

template <class T> class ProcessQueue {
    public:
      const static int DEFAULT_QUEUE_SIZE = 10;
      const static long DEFAULT_PROCESS_INTERVAL = 4000;

      ProcessQueue(unsigned int queueSize = ProcessQueue::DEFAULT_QUEUE_SIZE, unsigned long processInterval = ProcessQueue::DEFAULT_PROCESS_INTERVAL);

      void setProcessFunction(void (*processFunction)(T));

      bool isEmpty();
      bool isFull();

      bool enqueue(T item);
      void process(bool force = false);

    private:
      int queueSize;
      unsigned long processInterval;
      void (*processFunction)(T);

      T* queue;
      int front;
      int rear;
}

#endif

 