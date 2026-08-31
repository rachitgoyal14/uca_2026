import java.util.*;
import java.time.LocalDate;
import java.util.stream.Collectors;

public class Main {
    public static class Employee {
        private int employeeId;
        private String name;
        private String department;
        private double salary;
        private int age;
        private LocalDate joiningDate;
        private double rating;

        public Employee(int employeeId, String name, String department, double salary, int age, LocalDate joiningDate, double rating) {
            this.employeeId = employeeId;
            this.name = name;
            this.department = department;
            this.salary = salary;
            this.age = age;
            this.joiningDate = joiningDate;
            this.rating = rating;
        }

        public int getEmployeeId() {
            return employeeId;
        }

        public String getName() {
            return name;
        }

        public String getDepartment() {
            return department;
        }

        public double getSalary() {
            return salary;
        }

        public int getAge() {
            return age;
        }

        public LocalDate getJoiningDate() {
            return joiningDate;
        }

        public double getRating() {
            return rating;
        }

        @Override
        public String toString() {
            return employeeId + " | " + name + " | " + department + " | " + salary + " | " + age + " | " + joiningDate + " | " + rating;
        }
    }

    static List<Employee> employees = new ArrayList<>(List.of(
        new Employee(1, "Aarav",  "Engineering", 120000, 29, LocalDate.of(2021, 3, 15), 4.5),
        new Employee(2, "Anika",  "Sales",        95000, 34, LocalDate.of(2019, 7, 1),  3.8),
        new Employee(3, "Bhavya", "Engineering", 135000, 41, LocalDate.of(2015, 1, 10), 4.9),
        new Employee(4, "Chirag", "Marketing",    88000, 25, LocalDate.of(2022, 11, 5), 4.1),
        new Employee(5, "Aditi",  "Sales",       110000, 30, LocalDate.of(2020, 6, 20), 4.6),
        new Employee(6, "Aman",   "Engineering", 102000, 27, LocalDate.of(2021, 9, 12), 3.9),
        new Employee(7, "Divya",  "Marketing",    75000, 23, LocalDate.of(2023, 2, 1),  4.0),
        new Employee(8, "Aryan",  "Sales",       140000, 38, LocalDate.of(2016, 4, 18), 4.7)
    ));

    public static void printEmployees(List<Employee> list) {
        for (Employee e : list) {
            System.out.println(e);
        }
        System.out.println();
    }

    public static void main(String[] args) {

        System.out.println("sorted by salary ascending: ");
        employees.sort(Comparator.comparing(Employee::getSalary));
        printEmployees(employees);

        System.out.println("sorted by salary descending: ");
        employees.sort(Comparator.comparing(Employee::getSalary).reversed());
        printEmployees(employees);

        System.out.println("filtered employees: ");
        List<Employee> filteredEmployees = employees.stream()
            .filter(e -> e.getName().startsWith("A") && e.getSalary() > 100000)
            .sorted(Comparator.comparing(Employee::getSalary).reversed())
            .collect(Collectors.toList());

        printEmployees(filteredEmployees);

        System.out.println("sort by department, then name");
        List<Employee> departmentThenName = employees.stream().sorted(Comparator.comparing(Employee::getDepartment).thenComparing(Employee::getName)).collect(Collectors.toList());

        printEmployees(departmentThenName);

        System.out.println("first employee: ");
        System.out.println(departmentThenName.get(0));
    }
}