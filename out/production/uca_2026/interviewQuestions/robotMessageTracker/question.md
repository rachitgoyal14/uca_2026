# Robot Message Tracker

## Part I

A Robot is sending messages to the server, but the rain has malfunctioned
its transmitter, so it might send some duplicate messages. Write a program
which will filter out a duplicate message sent within the last 10 seconds.

```java
RobotMessageTracker logger = new RobotMessageTracker();
logger.shouldPrintMessage(1, "foo");   // print the Message
logger.shouldPrintMessage(2, "bar");   // print the Message
logger.shouldPrintMessage(3, "foo");   // Don't print the Message
logger.shouldPrintMessage(11, "foo");  // print the Message
```

```java
class RobotMessageTracker {

    public void shouldPrintMessage(long timeStamp, String message) {
        // complete this method.
    }
}
```

---

## Part II (Follow-up)

If there is a message that comes within a 10-second window of a duplicate,
don't print **any one** of them.

```java
RobotMessageTracker logger = new RobotMessageTracker();
logger.shouldPrintMessage(1, "foo");   // Don't print the Message, same message came at 3
logger.shouldPrintMessage(2, "bar");   // print the Message, there is no message in last and future 10 seconds
logger.shouldPrintMessage(3, "foo");   // Don't print the Message
logger.shouldPrintMessage(13, "foo");  // Don't print the Message
```

---

## Part III (Follow-up)

Your Part I solution keeps a hashmap that grows for as long as the service
runs, since it never removes an entry once a message has been seen. If this
service runs continuously and sees a very large number of distinct
messages over time, how would you bound the memory it uses?