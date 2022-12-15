# ProcessQueue

ADT implementing an array based, fixed size, generic circular queue.

The queue implementation includes a method for registering a callback
function that can process a queue element and a process method for
passing the queue's head element to the callback and, perhaps, then
dequeueing it. Setting a process interval to throttle processing at an
appropriate rate allows the process method to be executed from the main
program loop() in a resource sensitive way.

The library was written to support the development of firmware for N2K
modules by easing the implementation of a message transmission scheme. 

## Constants

### ProcessQueue.DEFAULT_QUEUE_SIZE
Specifies the default queue size of 10 messages.

### ProcessQueue.DEFAULT_PROCESS_INTERVAL
Specifies the default process interval of 50ms.

## Constructors

### ProcessQueue<*type*> *processQueue*([*size*[, *processInterval*]])
```
ProcessQueue<N2kMsg> myQueue();
ProcessQueue<N2kMsg> myQueue(20);
ProcessQueue<N2kMsg> myQueue(0, 500);
ProcessQueue<N2kMsg> myQueue(20, 500);
```
Create a new ProcessQueue called *processQueue* capable of holding
a maximum of *size* elements of type *type* and with an automatic
process interval of *processInterval* milliseconds.

If *processInterval* is omitted, ```ProcessQueue.DEFAULT_QUEUE_SIZE```
is used as a default. If *size* is omitted, ```ProcessQueue.DEFAULT_QUEUE_SIZE```
is used as a default.

## Methods

### isEmpty();
```
bool empty = myQueue.isEmpty();
```
Returns ```true``` if the queue is empty, otherwise ```false```.

### isFull();
```
bool full = myQueue.isFull();
```
Returns ```true``` if the queue is full, otherwise ```false```.

### setProcessFunction(*function*);
```
void myProcessFunction(N2kMsg* msg) {
...
}

myQueue.setProcessFunction(myProcessFunction);
```
If you want to automatically process the queue then you must use this
method to specify a callback *function* which will be passed a pointer
to the current head element each time the process() method is invoked
and the queue is not empty.

### enqueue(*thing*)
```
N2kMsg message;
...
bool success = myQueue.enqueue(message);
```
Add *thing* to the end of the queue. Returns ```true``` on success, or
```false``` if the queue is full.

### dequeue();
```
myQueue.dequeue();
```
Remove an element at the front of the queue.

### front()
```
N2kMsg* element = myQueue.front()
```
Return a pointer to the element at the front of the queue or null if the
queue is empty.

### process([*force*[, *retain*]);
```
bool tookAction = myQueue.process();
bool tookAction = myQueue.process(*force*);
bool tookAction = myQueue.process(*force*, *retain*);
```
*force* and *retain* default to ```false```.

The method will take no action and immediately return to the caller (with
a return value of ```false```) if any of the following conditions pertain:
1. no callback function has been defined;
2. the queue is empty;
3. the previously configured process interval has not elapsed and *force*
   is unspecified or explicitly set ```false```. 

Otherwise, the callback function will be called with a pointer to the
element at the head of the queue as its only argument.  Subsequently, the
head element will be removed from the queue unless *retain* is explicitly
set ```true```. In any case, the method will return a value of ```true```.

If you always intend *force*ing the execution of this method, then
calling the constructor with *processInterval* set to 0UL might make
sense and will eliminate the requirement to always set *force* ```true```.
