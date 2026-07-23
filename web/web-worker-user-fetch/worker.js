// worker.js
// Runs on a separate thread. Does the network work and hands the result
// (or an error) back to the main thread via postMessage.

self.onmessage = async function (event) {
  if (event.data !== 'start') return;

  try {
    const response = await fetch('https://dummyjson.com/users');

    if (!response.ok) {
      throw new Error(`Request failed with status ${response.status}`);
    }

    const body = await response.json();
    const users = body.users; // dummyjson.com wraps the array as { users, total, skip, limit }

    if (!Array.isArray(users) || users.length === 0) {
      self.postMessage({ success: false, error: 'No users returned from API' });
      return;
    }

    self.postMessage({ success: true, data: users });
  } catch (err) {
    // Covers network failures, JSON parse errors, and the throw above
    self.postMessage({ success: false, error: err.message });
  }
};