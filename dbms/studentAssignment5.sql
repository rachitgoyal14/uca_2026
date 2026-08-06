CREATE SCHEMA assignment5;
USE assignment5;

CREATE TABLE Department (
    dept_id     INT PRIMARY KEY,
    dept_name   VARCHAR(50) NOT NULL
);

CREATE TABLE Instructor (
    instructor_id   INT PRIMARY KEY,
    instructor_name VARCHAR(50) NOT NULL,
    dept_id         INT,
    salary          DECIMAL(10,2),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

CREATE TABLE Student (
    student_id  INT PRIMARY KEY,
    student_name VARCHAR(50) NOT NULL,
    dept_id     INT,
    dob         DATE,
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

CREATE TABLE Course (
    course_id     INT PRIMARY KEY,
    course_name   VARCHAR(50) NOT NULL,
    dept_id       INT,
    instructor_id INT,
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id),
    FOREIGN KEY (instructor_id) REFERENCES Instructor(instructor_id)
);

CREATE TABLE Enrollment (
    student_id  INT,
    course_id   INT,
    grade       CHAR(1),
    PRIMARY KEY (student_id, course_id),
    FOREIGN KEY (student_id) REFERENCES Student(student_id),
    FOREIGN KEY (course_id) REFERENCES Course(course_id)
);

INSERT INTO Department (dept_id, dept_name) VALUES
(1, 'CS'), (2, 'Electronics'), (3, 'Mechanical');

INSERT INTO Instructor (instructor_id, instructor_name, dept_id, salary) VALUES
(101, 'Dr. Rao', 1, 95000),
(102, 'Dr. Mehta', 2, 88000),
(103, 'Dr. Iyer', 1, 72000),
(104, 'Dr. Sen', 3, 60000);

INSERT INTO Student (student_id, student_name, dept_id, dob) VALUES
(1, 'Aarav', 1, '2003-05-14'),
(2, 'Diya', 1, '2003-08-22'),
(3, 'Kabir', 2, '2003-01-30'),
(4, 'Meera', 3, '2003-03-11'),
(5, 'Rohan', 1, '2003-07-19');

INSERT INTO Course (course_id, course_name, dept_id, instructor_id) VALUES
(201, 'DBMS', 1, 101),
(202, 'OS', 1, 103),
(203, 'Circuits', 2, 102),
(204, 'Thermo', 3, 104);

INSERT INTO Enrollment (student_id, course_id, grade) VALUES
(1, 201, 'A'), (1, 202, 'B'), (2, 201, 'A'), (3, 203, 'B'), (5, 201, 'C');

SELECT instructor_name 
FROM Instructor 
WHERE salary > 
(SELECT AVG(salary) FROM Instructor);


SELECT instructor_name 
FROM Instructor I1 
WHERE salary > (
	SELECT AVG(salary)
	 FROM Instructor I2 
	 WHERE I2.dept_id = I1.dept_id
 );
 
 
 SELECT student_name 
 FROM Student 
 WHERE dept_id IN 
 (SELECT dept_id FROM Department WHERE dept_name = 'CS');
 
 
 SELECT instructor_name 
 FROM Instructor 
 WHERE salary > ALL 
 (SELECT salary FROM Instructor WHERE dept_id = 1);
 
 SELECT instructor_name 
 FROM Instructor 
 WHERE salary > 
 ANY (SELECT salary FROM Instructor WHERE dept_id = 1);

SELECT student_name 
FROM Student 
WHERE dept_id = 1 

UNION 

SELECT instructor_name 
FROM Instructor 
WHERE dept_id = 1;



SELECT e1.student_id
FROM Enrollment e1
JOIN Enrollment e2 ON e1.student_id = e2.student_id
WHERE e1.course_id = 201 AND e2.course_id = 202;

SELECT s.student_name
FROM Student s
WHERE NOT EXISTS (
    SELECT 1
    FROM Enrollment e
    WHERE e.student_id = s.student_id
);