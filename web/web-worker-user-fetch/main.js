// main.js
// Runs on the main thread. Delegates the API call to worker.js so the
// fetch never blocks the UI, then logs the results.

function displayUsers(users) {
  users.forEach(user => {
    const name = `${user.firstName} ${user.lastName}`;

    // dummyjson.com/users doesn't include an active/inactive flag.
    // Placeholder derivation for demo purposes: swap this for a real
    // field (e.g. user.role === 'admin') once one is available.
    const status = user.id % 2 === 0 ? 'Active' : 'Inactive';

    console.log(`${name} - ${status}`);
  });
}

function fetchAndDisplayUsers() {
  const worker = new Worker('worker.js');

  worker.onmessage = function (event) {
    const { success, data, error } = event.data;

    if (!success) {
      console.error(`Error: ${error}`);
      worker.terminate();
      return;
    }

    displayUsers(data);
    worker.terminate(); // one-shot worker, clean up once done
  };

  worker.onerror = function (err) {
    console.error(`Worker failed to run: ${err.message}`);
    worker.terminate();
  };

  worker.postMessage('start');
}

fetchAndDisplayUsers();