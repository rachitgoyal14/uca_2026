#!/bin/bash

# Create the data file if it doesn't already exist
if [ ! -f employees.txt ]; then
    cat > employees.txt << 'EOF'
Alice,Engineering,50,40
Bob,Marketing,35,38
Charlie,Engineering,60,45
David,HR,30,40
Eva,Engineering,55,35
EOF
fi

echo "=== Task 1: Basic Field Extraction ==="
awk -F',' '{ print $1, $2 }' employees.txt

echo ""
echo "=== Task 2: Filtering by Row (Pattern Matching) ==="
awk -F',' '$2 == "Engineering" { print }' employees.txt

echo ""
echo "=== Task 3: Basic Arithmetic (Calculating Total Pay) ==="
awk -F',' '{ pay = $3 * $4; print $1, "gross pay: $" pay }' employees.txt

echo ""
echo "=== Task 4: Using Built-in Variables (NR and NF) ==="
awk -F',' '{ print NR " (" NF " fields): " $0 }' employees.txt

echo ""
echo "=== Task 5: The Grand Finale (BEGIN, END, and Conditionals) ==="
awk -F',' '
BEGIN { total = 0 }
$2 == "Engineering" { total += $3 * $4 }
END { print "Total Engineering Payroll: $" total }
' employees.txt