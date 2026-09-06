DROP DATABASE IF EXISTS university_db;
CREATE DATABASE university_db;
USE university_db;

-- ============================
-- TABLE: Department
-- ============================
CREATE TABLE Department (
    dept_id     INT PRIMARY KEY AUTO_INCREMENT,
    dept_name   VARCHAR(50) NOT NULL,
    building    VARCHAR(30),
    budget      DECIMAL(12,2)
);

INSERT INTO Department (dept_name, building, budget) VALUES
('CS', 'Building A', 500000),
('ECE', 'Building B', 400000),
('ME', 'Building C', 350000),
('MATH', 'Building D', 200000);

-- ============================
-- TABLE: Instructor
-- ============================
CREATE TABLE Instructor (
    instructor_id INT PRIMARY KEY AUTO_INCREMENT,
    name          VARCHAR(60) NOT NULL,
    dept_id       INT,
    salary        DECIMAL(10,2),
    hire_date     DATE,
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

INSERT INTO Instructor (name, dept_id, salary, hire_date) VALUES
('Dr. Arjun Mehta', 1, 95000, '2015-06-01'),
('Dr. Priya Nair',  1, 88000, '2018-03-15'),
('Dr. Rakesh Iyer', 2, 92000, '2012-08-20'),
('Dr. Sneha Kapoor',2, 79000, '2019-01-10'),
('Dr. Vikram Rao',  3, 85000, '2016-11-05'),
('Dr. Anjali Desai',3, 76000, '2020-07-01'),
('Dr. Manoj Pillai',4, 70000, '2014-02-18'),
('Dr. Kavita Menon',4, 72000, '2017-09-25');

-- ============================
-- TABLE: Student
-- ============================
CREATE TABLE Student (
    student_id     INT PRIMARY KEY AUTO_INCREMENT,
    name           VARCHAR(60) NOT NULL,
    dept_id        INT,
    admission_year INT,
    email          VARCHAR(80),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

INSERT INTO Student (name, dept_id, admission_year, email) VALUES
('Rahul Sharma',   1, 2022, 'rahul.s@univ.edu'),
('Sneha Patel',    1, 2022, 'sneha.p@univ.edu'),
('Amit Kumar',     1, 2023, 'amit.k@univ.edu'),
('Divya Reddy',    2, 2022, 'divya.r@univ.edu'),
('Karan Singh',    2, 2023, 'karan.s@univ.edu'),
('Neha Joshi',     2, 2022, 'neha.j@univ.edu'),
('Rohan Gupta',    3, 2022, 'rohan.g@univ.edu'),
('Priyanka Rao',   3, 2023, 'priyanka.r@univ.edu'),
('Suresh Nair',    4, 2022, 'suresh.n@univ.edu'),
('Ananya Iyer',    4, 2023, 'ananya.i@univ.edu'),
('Vikas Malhotra', 1, 2021, 'vikas.m@univ.edu'),
('Meera Krishnan', 3, 2021, 'meera.k@univ.edu');

-- ============================
-- TABLE: Course
-- ============================
CREATE TABLE Course (
    course_id     INT PRIMARY KEY AUTO_INCREMENT,
    course_name   VARCHAR(60) NOT NULL,
    dept_id       INT,
    credits       INT,
    instructor_id INT,
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id),
    FOREIGN KEY (instructor_id) REFERENCES Instructor(instructor_id)
);

INSERT INTO Course (course_name, dept_id, credits, instructor_id) VALUES
('Database Systems',     1, 4, 1),
('Data Structures',      1, 4, 2),
('Operating Systems',    1, 3, 1),
('Digital Electronics',  2, 4, 3),
('Signal Processing',    2, 3, 4),
('Thermodynamics',       3, 4, 5),
('Fluid Mechanics',      3, 3, 6),
('Linear Algebra',       4, 3, 7),
('Calculus II',          4, 4, 8),
('Discrete Mathematics', 4, 3, 7);

-- ============================
-- TABLE: Enrollment
-- ============================
CREATE TABLE Enrollment (
    enroll_id  INT PRIMARY KEY AUTO_INCREMENT,
    student_id INT,
    course_id  INT,
    semester   VARCHAR(20),
    grade      CHAR(1),
    FOREIGN KEY (student_id) REFERENCES Student(student_id),
    FOREIGN KEY (course_id)  REFERENCES Course(course_id)
);

INSERT INTO Enrollment (student_id, course_id, semester, grade) VALUES
(1, 1, 'Fall2023',   'A'),
(1, 2, 'Fall2023',   'B'),
(1, 9, 'Spring2024', 'A'),
(2, 1, 'Fall2023',   'B'),
(2, 3, 'Spring2024', 'C'),
(3, 2, 'Fall2023',   'A'),
(3, 1, 'Spring2024', 'B'),
(4, 4, 'Fall2023',   'A'),
(4, 5, 'Spring2024', 'B'),
(5, 4, 'Fall2023',   'C'),
(5, 8, 'Spring2024', 'B'),
(6, 5, 'Fall2023',   'A'),
(7, 6, 'Fall2023',   'B'),
(7, 7, 'Spring2024', 'A'),
(8, 6, 'Fall2023',   'C'),
(8, 9, 'Spring2024', 'B'),
(9, 8, 'Fall2023',   'A'),
(9, 10,'Spring2024', 'A'),
(10,9, 'Fall2023',   'B'),
(10,10,'Spring2024', 'C'),
(11,1, 'Fall2023',   'A'),
(11,3, 'Spring2024', 'A'),
(12,7, 'Fall2023',   'B'),
(12,6, 'Spring2024', 'A');

-- ============================
-- TABLE: Course_Schedule
-- ============================
CREATE TABLE Course_Schedule (
    schedule_id INT PRIMARY KEY AUTO_INCREMENT,
    course_id   INT,
    room_no     VARCHAR(10),
    day_of_week VARCHAR(10),
    start_time  TIME,
    FOREIGN KEY (course_id) REFERENCES Course(course_id)
);

INSERT INTO Course_Schedule (course_id, room_no, day_of_week, start_time) VALUES
(1, 'A101', 'Monday',    '09:00'),
(2, 'A102', 'Tuesday',   '10:00'),
(3, 'A101', 'Wednesday', '09:00'),
(4, 'B201', 'Monday',    '11:00'),
(5, 'B202', 'Thursday',  '10:00'),
(6, 'C301', 'Tuesday',   '09:00'),
(7, 'C302', 'Friday',    '11:00'),
(8, 'D401', 'Monday',    '10:00'),
(9, 'D402', 'Wednesday', '11:00'),
(10,'D401', 'Friday',    '09:00');

-- ============================
-- TABLE: Book
-- ============================
CREATE TABLE Book (
    book_id   INT PRIMARY KEY AUTO_INCREMENT,
    title     VARCHAR(80) NOT NULL,
    author    VARCHAR(60),
    dept_id   INT,
    price     DECIMAL(8,2),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

INSERT INTO Book (title, author, dept_id, price) VALUES
('Database System Concepts',        'Silberschatz', 1, 1200),
('Introduction to Algorithms',      'Cormen',       1, 1500),
('Operating System Concepts',       'Silberschatz', 1, 1100),
('Digital Design',                  'Morris Mano',  2, 900),
('Signals and Systems',             'Oppenheim',    2, 1000),
('Engineering Thermodynamics',      'Cengel',       3, 950),
('Fluid Mechanics',                 'Munson',       3, 1050),
('Linear Algebra and Its Applications','Strang',    4, 850),
('Calculus',                        'James Stewart',4, 1300),
('Discrete Mathematics',            'Rosen',        4, 1150);

-- ============================
-- TABLE: Book_Issue
-- ============================
CREATE TABLE Book_Issue (
    issue_id    INT PRIMARY KEY AUTO_INCREMENT,
    book_id     INT,
    student_id  INT,
    issue_date  DATE,
    return_date DATE NULL,
    FOREIGN KEY (book_id) REFERENCES Book(book_id),
    FOREIGN KEY (student_id) REFERENCES Student(student_id)
);

INSERT INTO Book_Issue (book_id, student_id, issue_date, return_date) VALUES
(1, 1, '2024-01-05', '2024-01-20'),
(2, 1, '2024-02-01', NULL),
(1, 2, '2024-01-10', '2024-01-25'),
(3, 3, '2024-01-15', '2024-02-01'),
(4, 4, '2024-01-06', '2024-01-22'),
(5, 5, '2024-02-05', NULL),
(6, 7, '2024-01-12', '2024-01-28'),
(7, 8, '2024-01-20', NULL),
(8, 9, '2024-01-08', '2024-01-25'),
(9, 10,'2024-02-10', '2024-02-25'),
(2, 11,'2024-01-18', '2024-02-02'),
(10,9, '2024-02-15', NULL),
(1, 11,'2024-03-01', NULL),
(6, 12,'2024-01-22', '2024-02-05'),
(9, 3, '2024-02-20', '2024-03-05');

-- ============================
-- TABLE: Fee_Payment
-- ============================
CREATE TABLE Fee_Payment (
    payment_id   INT PRIMARY KEY AUTO_INCREMENT,
    student_id   INT,
    amount       DECIMAL(10,2),
    payment_date DATE,
    semester     VARCHAR(20),
    FOREIGN KEY (student_id) REFERENCES Student(student_id)
);

INSERT INTO Fee_Payment (student_id, amount, payment_date, semester) VALUES
(1, 50000, '2023-08-01', 'Fall2023'),
(2, 50000, '2023-08-02', 'Fall2023'),
(3, 52000, '2023-08-05', 'Fall2023'),
(4, 48000, '2023-08-01', 'Fall2023'),
(5, 48000, '2023-08-03', 'Fall2023'),
(6, 48000, '2023-08-04', 'Fall2023'),
(7, 45000, '2023-08-02', 'Fall2023'),
(8, 45000, '2023-08-06', 'Fall2023'),
(9, 40000, '2023-08-01', 'Fall2023'),
(10,40000, '2023-08-05', 'Fall2023'),
(1, 50000, '2024-01-05', 'Spring2024'),
(4, 48000, '2024-01-06', 'Spring2024'),
(7, 45000, '2024-01-08', 'Spring2024'),
(9, 40000, '2024-01-10', 'Spring2024'),
(11,50000, '2023-08-01', 'Fall2023');