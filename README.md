# ProcessQueue

Library implementing an array based, fixed size, generic circular queue.

The queue implementation includes a method for registering a callback
function that can process a queue element and a process method for
dequeing the head element and passing it to the callback. Setting a
process interval to throttle processing to an appropriate rate and
executing the process method from within the main program loop()
allows automation of queue processing.

## Constants

```
ProcessQueue.DEFAULT_QUEUE_SIZE
```
Specifies the default queue size of 10 messages.

```
ProcessQueue.DEFAULT_PROCESS_INTERVAL
```
Specifies the default process interval of 50ms.

## Constructors

```
ProcessQueue<*type*> myQueue();
```
Create a new queue capable of holding a maximum of DEFAULT_QUEUE_SIZE
elements of type *type* and with an automatic process interval of
DEFAULT_PROCESS_INTERVAL.

```
ProcessQueue<*type*> myQueue(*size*);
```
Create a new queue capable of holding a maximum of *size* elements of
type *type* and with an automatic process interval of
DEFAULT_PROCESS_INTERVAL.

```
ProcessQueue<*type*> myQueue(0, *millis*);
```
Create a new queue capable of holding a maximum of DEFAULT_QUEUE_SIZE
elements of type *type* and with an automatic process interval of
*millis* milliseconds.

```
ProcessQueue<*type*> myQueue(*size*, *millis*);
```
Create a new queue capable of holding a maximum of *size* elements of
type *type* and with an automatic process interval of *millis*
milliseconds. 

## Methods

```
bool empty = myQueue.isEmpty();
```
Returns ```true``` if the queue is empty, otherwise ```false```.

```
bool full = myQueue.isFull();
```
Returns ```true``` if the queue is full, otherwise ```false```.

```
myQueue.setProcessFunction(*function*);
```
If you want to automatically process the queue then you must use this
method to specify a callback *function* which will be passed a pointer
to the current head element each time the process() method is invoked
and the queue is not empty.

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
Remove an element at the front of the queue.

```
*type*\* element = myQueue.front()
```
Return a pointer to the element at the front of the queue or null if the
queue is empty.

```
myQueue.process(*retain*)
```
If the queue is not empty, than calls the previously registered callback
function with a pointer to the element at the head of the queue. If
*retain* is false or omitted, then the head element is removed from the
queue.
