# ProcessQueue

Library implementing an array based, fixed size, generic circular queue.

## Constants

```ProcessQueue.DEFAULT_QUEUE_SIZE```
Specifies the default queue size of 10 messages.

```ProcessQueue.DEFAULT_PROCESS_INTERVAL```
Specifies the default process interval of 50ms.

## Constructors

```ProcessQueue<*type*> myQueue();```
Create a new queue capable of holding a maximum of DEFAULT_QUEUE_SIZE
elements of type *type* and with an automatic process interval of
DEFAULT_PROCESS_INTERVAL.

```ProcessQueue<*type*> myQueue(*size*);```
Create a new queue capable of holding a maximum of *size* elements of
type *type* and with an automatic process interval of
DEFAULT_PROCESS_INTERVAL.

```ProcessQueue<*type*> myQueue(0, *millis*);```
Create a new queue capable of holding a maximum of DEFAULT_QUEUE_SIZE
elements of type *type* and with an automatic process interval of
*millis* milliseconds.

```ProcessQueue<*type*> myQueue(*size*, *millis*);```
Create a new queue capable of holding a maximum of *size* elements of
type *type* and with an automatic process interval of *millis*
milliseconds. 

## Methods

```
myQueue.setProcessFunction(*function*);
```
If you want to automatically process the queue then you must use this
method to specify a callback *function* which will be passed any
available head element each time the process interval specified in the
constructor rolls over.

```
if myQueue.enqueue(*thing*) {
  // Success
} else {
  // Failure - the queue is full
}
```
Add *thing* to the end of the queue. Returns ```true``` on success, or
```false``` if the queue is full.

```
myQueue.dequeue();
```
Remove any element at the front of the queue.

```
*type** element = myQueue.front()```
N2kMessageQueue myQueue(10, 4000);```myQueue.oid loop(Functionueue.process();
}

allow```
If you want to automatically process the queue then you must use this
method to s the client application to add N2K messages to a
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
