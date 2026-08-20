CREATE DATABASE IF NOT EXISTS assignment7;
USE assignment7;

DROP TABLE IF EXISTS EnrollmentRequest;
DROP TABLE IF EXISTS Enrollment;
DROP TABLE IF EXISTS Course;
DROP TABLE IF EXISTS Student;
DROP TABLE IF EXISTS Instructor;
DROP TABLE IF EXISTS Department;

CREATE TABLE Department (
    dept_id   INT PRIMARY KEY,
    dept_name VARCHAR(50) NOT NULL
);

CREATE TABLE Instructor (
    instructor_id INT PRIMARY KEY,
    name          VARCHAR(50),
    dept_id       INT REFERENCES Department(dept_id),
    salary        DECIMAL(10,2)
);

CREATE TABLE Student (
    student_id  INT PRIMARY KEY,
    name        VARCHAR(50),
    dept_id     INT REFERENCES Department(dept_id),
    dob         DATE
);

CREATE TABLE Course (
    course_id     INT PRIMARY KEY,
    title         VARCHAR(50),
    dept_id       INT REFERENCES Department(dept_id),
    instructor_id INT REFERENCES Instructor(instructor_id)
);

CREATE TABLE Enrollment (
    student_id INT REFERENCES Student(student_id),
    course_id  INT REFERENCES Course(course_id),
    grade      CHAR(2),
    PRIMARY KEY (student_id, course_id)
);

-- A separate, unconstrained table used only for the NOT IN / NULL questions
CREATE TABLE EnrollmentRequest (
    request_id INT PRIMARY KEY,
    student_id INT,
    course_id  INT
);

INSERT INTO Department VALUES
(1,'CS'), (2,'Electronics'), (3,'Mechanical'), (4,'Civil');

INSERT INTO Instructor VALUES
(101,'Dr. Rao',1,95000), (102,'Dr. Mehta',2,88000),
(103,'Dr. Iyer',1,72000), (104,'Dr. Sen',3,60000);

INSERT INTO Student VALUES
(1,'Aarav',1,'2003-05-14'), (2,'Diya',1,'2003-08-22'),
(3,'Kabir',2,'2003-01-30'), (4,'Meera',3,'2003-03-11'),
(5,'Rohan',1,'2003-07-19'), (6,'Ishaan',4,'2003-09-01');

INSERT INTO Course VALUES
(201,'DBMS',1,101), (202,'OS',1,103), (203,'Circuits',2,102), (204,'Thermo',3,104);

-- Note the extra row (3,201,'B') — Kabir (dept 2) enrolled in DBMS (dept 1), a deliberate mismatch
INSERT INTO Enrollment VALUES
(1,201,'A'), (1,202,'B'), (2,201,'A'), (3,203,'B'), (5,201,'C'), (3,201,'B');

-- Note the deliberate NULL student_id in the last row
INSERT INTO EnrollmentRequest VALUES
(1,1,201), (2,2,201), (3,3,203), (4,5,201), (5,NULL,204);


-- using a correlated subquery that compares each instructor's salary to the average salary of instructors in every OTHER department 
-- (excluding their own), 
-- how many instructors qualify as earning above that value?

SELECT COUNT(*)
FROM Instructor i1
WHERE i1.salary > (
    SELECT AVG(i2.salary)
    FROM Instructor i2
    WHERE i2.dept_id != i1.dept_id
    );


SELECT name FROM Student
WHERE student_id NOT IN 
	(SELECT student_id FROM EnrollmentRequest);
    
SELECT name FROM Student S
WHERE NOT EXISTS (
    SELECT 1 FROM EnrollmentRequest ER WHERE ER.student_id = S.student_id
);

SELECT name FROM Instructor
WHERE salary > ALL (SELECT salary FROM Instructor WHERE dept_id = 3);


SELECT dept_id FROM Student
EXCEPT
SELECT dept_id FROM Instructor;


SELECT dept_id FROM Student
INTERSECT
SELECT dept_id FROM Instructor;


SELECT COUNT(*) FROM Enrollment E
WHERE (SELECT dept_id FROM Student WHERE student_id = E.student_id) <>
      (SELECT dept_id FROM Course WHERE course_id = E.course_id);
      
      
SELECT name, 'Student' AS role FROM Student WHERE dept_id = 1
UNION
SELECT name, 'Instructor' AS role FROM Instructor WHERE dept_id = 1
ORDER BY name;