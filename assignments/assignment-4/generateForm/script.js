const data = [ 
  "First Name", 
  "Last Name", 
  "Email"
];

function generateForm(data) {
    // map over the array to generate a label and input for each item
    const formHTML = data.map(field => {
        return `  <label>${field}</label>\n  <input type="text">`;
    }).join('\n'); // join the array of strings into a single string
    
    return formHTML;
}

// inject into the html yooyo
document.getElementById('form-container').innerHTML = generateForm(data);