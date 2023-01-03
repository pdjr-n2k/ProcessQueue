/**********************************************************************
 * ProcessQueue.h - ADT implementing a generic static queue with timmed
 * processing.
 * Copyright (C) 2022 Paul Reeve <pdjr@pdjr.eu>
 */

#ifndef PROCESS_QUEUE
#define PROCESS_QUEUE

template <typename T>
class ProcessQueue {
    public:
      const static int DEFAULT_QUEUE_SIZE = 10;
      const static long DEFAULT_PROCESS_INTERVAL = 4000;

      /****************************************************************
       * Create a new process queue capable of holding a maximum of
       * queueSize elements. If automated processing of the queue is
       * required then processInterval specifies the number of milli-
       * seconds between process ticks and processFunction specifies
       * a callback function that will be invoked if a head element is
       * available when the tick happens.
      */
      ProcessQueue(unsigned int queueSize = ProcessQueue::DEFAULT_QUEUE_SIZE, unsigned long processInterval = ProcessQueue::DEFAULT_PROCESS_INTERVAL, void (*processFunction)(T) = 0);

      void setProcessInterval(unsigned long millis);
      void setProcessFunction(void (*processFunction)(T));
      unsigned int getQueueSize();
      unsigned long getProcessInterval();

      bool isEmpty();
      bool isFull();

      bool enqueue(T item);
      void dequeue();
      T head();

      void process(bool force = false, bool retain = false);

    private:
      int queueSize;
      unsigned long processInterval;
      void (*processFunction)(T);

      T* queue;
      int front;
      int rear;
};

#endif

 
