const users = [
    {name: "Alice", age: 53},
    {name: "Tim", age: 74},
    {name: "Divyansh", age: 74},
    {name: "Rachit", age: 74},
    {name: "Devyansh", age: 74},
    {name: "Madhav", age: 74},
    {name: "Kartik", age: 74},
    {name: "Deepak", age: 74}
];

function generateTable(data) {
    // map over the array to create an array of string rows, then join them
    const tableRows = data.map(user => {
        return `  <tr>
                    <td>${user.name}</td>
                    <td>${user.age}</td>
                </tr>`;
    }).join('\n');

    // wrap the rows inside the table tags using template literals
    return `<table>\n${tableRows}\n</table>`;
}

// inject into the HTML yo yo yo
document.getElementById('table-container').innerHTML = generateTable(users);