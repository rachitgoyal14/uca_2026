function* calc(initialValue) {
    if (typeof initialValue !== "number" || Number.isNaN(initialValue)) {
        throw new Error("Initial value must be a valid number.");
    }

    let result = initialValue;

    while (true) {
        const input = yield result;

        // validate input object
        if (
            !input ||
            typeof input.operation !== "string" ||
            typeof input.value !== "number" ||
            Number.isNaN(input.value)
        ) {
            console.log("Invalid input");
            continue;
        }

        switch (input.operation) {
            case "add":
                result += input.value;
                break;

            case "subtract":
                result -= input.value;
                break;

            case "multiply":
                result *= input.value;
                break;

            case "divide":
                if (input.value === 0) {
                    console.log("Error: Cannot divide by zero");
                    continue;
                }
                result /= input.value;
                break;

            default:
                console.log("Invalid operation");
                continue;
        }
    }
}

const calculator = calc(50);


console.log(calculator.next().value); 

console.log(calculator.next({
    operation: "add",
    value: 30
}).value); 

console.log(calculator.next({
    operation: "multiply",
    value: 2
}).value); 

console.log(calculator.next({
    operation: "add",
    value: "30"
}).value);


console.log(calculator.next({
    operation: "multiply",
    value: 0
}).value); 

console.log(calculator.next({
    operation: "subtract",
    value: 10
}).value); 

console.log(calculator.next({
    operation: "divide",
    value: 0
}).value);

console.log(calculator.next({
    operation: "divide",
    value: 2
}).value); // -5