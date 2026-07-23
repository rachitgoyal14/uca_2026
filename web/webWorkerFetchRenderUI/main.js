// main.js
// Runs on the main thread. Delegates the API call to worker.js, then
// renders the result (or a "No users found" fallback) into #users.

function renderUsers(users) {
  const container = document.getElementById('users');
  container.innerHTML = '';

  const list = document.createElement('ul');

  users.forEach(user => {
    const name = `${user.firstName} ${user.lastName}`;

    // dummyjson.com/users doesn't include an active/inactive flag.
    // Placeholder derivation for demo purposes: swap this for a real
    // field (e.g. user.role === 'admin') once one is available.
    const status = user.id % 2 === 0 ? 'Active' : 'Inactive';

    const item = document.createElement('li');
    item.textContent = `${name} - ${status}`;
    list.appendChild(item);
  });

  container.appendChild(list);
}

function showNoUsersFound() {
  document.getElementById('users').textContent = 'No users found';
}

function fetchAndRenderUsers() {
  const worker = new Worker('worker.js');

  worker.onmessage = function (event) {
    const { success, data, error } = event.data;

    if (!success) {
      console.error(`Error: ${error}`);
      showNoUsersFound();
      worker.terminate();
      return;
    }

    renderUsers(data);
    worker.terminate(); // one-shot worker, clean up once done
  };

  worker.onerror = function (err) {
    console.error(`Worker failed to run: ${err.message}`);
    showNoUsersFound();
    worker.terminate();
  };

  worker.postMessage('start');
}

fetchAndRenderUsers();