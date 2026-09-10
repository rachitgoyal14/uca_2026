function NewPromise(executorFunction) {
  var status = "pending"; // can be pending, fulfilled, or rejected
  var storedValue; // the value we resolved or rejected with
  var callbacks = []; // list of things to run once we know the result

  function resolve(result) {
    // once a promise is settled, it can't change again
    if (status !== "pending") {
      return;
    }

    // if someone resolves with another promise, wait for that one first
    if (result && typeof result.then === "function") {
      result.then(resolve, reject);
      return;
    }

    status = "fulfilled";
    storedValue = result;
    runCallbacks();
  }

  function reject(reason) {
    if (status !== "pending") {
      return;
    }

    status = "rejected";
    storedValue = reason;
    runCallbacks();
  }

  function runCallbacks() {
    // run asynchronously, just like real promises do
    setTimeout(function () {
      for (var i = 0; i < callbacks.length; i++) {
        handleCallback(callbacks[i]);
      }
      callbacks = [];
    }, 0);
  }

  function handleCallback(callback) {
    if (status === "fulfilled") {
      if (typeof callback.onSuccess === "function") {
        try {
          var returnedValue = callback.onSuccess(storedValue);
          callback.resolveNext(returnedValue);
        } catch (error) {
          callback.rejectNext(error);
        }
      } else {
        // no success handler was given, just pass the value along
        callback.resolveNext(storedValue);
      }
    } else if (status === "rejected") {
      if (typeof callback.onFailure === "function") {
        try {
          var returnedValue2 = callback.onFailure(storedValue);
          callback.resolveNext(returnedValue2);
        } catch (error) {
          callback.rejectNext(error);
        }
      } else {
        // no failure handler was given, pass the error along
        callback.rejectNext(storedValue);
      }
    }
  }

  this.then = function (onSuccess, onFailure) {
    // then() always returns a brand new promise so we can chain
    return new NewPromise(function (resolveNext, rejectNext) {
      var callback = {
        onSuccess: onSuccess,
        onFailure: onFailure,
        resolveNext: resolveNext,
        rejectNext: rejectNext
      };

      if (status === "pending") {
        callbacks.push(callback);
      } else {
        setTimeout(function () {
          handleCallback(callback);
        }, 0);
      }
    });
  };

  this.catch = function (onFailure) {
    return this.then(null, onFailure);
  };

  // run the executor function right away, and catch any errors it throws
  try {
    executorFunction(resolve, reject);
  } catch (error) {
    reject(error);
  }
}