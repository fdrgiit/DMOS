#Message Passing using Ports

The routines that were implemented are:
SEND. The send is a “blocking” asynchronous send that is: it places the message in the port and returns but blocks if port is full.
RECEIVE (with appropriate arguments). The receive is a “blocking” receive.

The implementation strategy was: a mutex semaphore, a producer semaphore and a consumer semaphore - per port. 
