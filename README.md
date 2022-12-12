# ProcessQueue

Library implementing a transmit queue for NMEA 2000 messages as imlemented
by the NMEA2000 library.

A message can be added to a message queue at any time using the enqueue()
function.

Messages are removed from a message queue by the process() function which
passes any message at the head of the queue to a user supplied callback
function and removes it from the queue. Typically, the callback function
used by process() will act to transmit the dequeued message onto the
NMEA 2000 bus and processing interval can be specified such that the
rate of processing can be throttled to some meaning number of milliseconds.

## N2kMessageQueue.DEFAULT_QUEUE_SIZE
Specifies the default maximum queue size of 10 messages.

## N2kMessageQueue.DEFAULT_PROCESS_INTERVAL
Specifies the default process interval of 50ms.

## N2kMessageQueue(int queueSize = DEFAULT_QUEUE_SIZE, long processInterval = DEFAULT_PROCESS_INTERVAL);
Create a new message queue with the specified characteristics.

## setProcessCallback((void *processFunction)(tN2kMsg))
```
N2kMessageQueue myQueue(10, 4000);

void loop() {
  myQueue.process();
}

allows the client application to add N2K messages to a
transmission queue 


class N2kMessageQueue {
    public:
      const static int DEFAULT_MAX_QUEUE_SIZE = 10;
      const static long DEFAULT_PROCESS_INTERVAL = 4000;

      N2kMessageQueue(unsigned int queueSize = N2kMessageQueue::DEFAULT_MAX_QUEUE_SIZE, unsigned long processInterval = N2kMessageQueue::DEFAULT_PROCESS_INTERVAL);

      void setTransmitFunction(void (*transmitFunction)(tN2kMsg));

      bool isEmpty();
      bool isFull();

      bool enqueue(tN2kMsg message);
      void process(bool force = false);

    private:
      int queueSize;
      unsigned long processInterval;
      void (*transmitFunction)(tN2kMsg);

      tN2kMsg* queue;
      int front;
      int rear;
}
