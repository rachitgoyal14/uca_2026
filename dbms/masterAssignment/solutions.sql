-- Q1. List the name of every student along with their department name,
--     the courses they are enrolled in, and the grade obtained - for Fall2023 only.
--     Sort by department, then student name.

SELECT Student.name, Department.dept_name, Course.course_name, Enrollment.grade
FROM Student
JOIN Department ON Student.dept_id = Department.dept_id
JOIN Enrollment ON Student.student_id = Enrollment.student_id
JOIN Course ON Enrollment.course_id = Course.course_id
WHERE Enrollment.semester = 'Fall2023'
ORDER BY Department.dept_name, Student.name;


-- Q2. Find the names of all instructors, their department, and the total number
--     of distinct students who have ever taken any course they teach.
--     Instructors with zero students should still appear, with a count of 0.

SELECT Instructor.name, Department.dept_name, COUNT(DISTINCT Enrollment.student_id)
FROM Instructor
JOIN Department 
    ON Instructor.dept_id = Department.dept_id
JOIN Course
    ON Instructor.instructor_id = Course.instructor_id
LEFT JOIN Enrollment
    ON Course.course_id = Enrollment.course_id
GROUP BY Instructor.instructor_id;  



-- Q3. List every course along with its instructor's name, the room and day it is scheduled,
--     and the total number of students enrolled in it (any semester).




-- Q4. List the names of students who are enrolled in at least one course offered
--     by a different department than their own home department.
--     Show student name, home department, course name, and the course's department.

-- Q5. Find pairs of students who are enrolled in the same course in the same semester
--     but received different grades.
--     Show both student names, the course name, the semester, and both grades.
--     Avoid showing the same pair twice (e.g., don't show both "A-B" and "B-A").

-- Q6. List the titles of books whose author has written books catalogued under
--     more than one department.
--     Hint: this needs Book joined to itself, or a GROUP BY author HAVING
--     COUNT(DISTINCT dept_id) > 1, then joined back to fetch qualifying titles.

-- Q7. Find the names of instructors who teach more courses than the average number
--     of courses taught per instructor (computed across all instructors who teach
--     at least one course).

-- Q8. For each course, compute the "average grade point" of students enrolled in it,
--     using this mapping: A = 4, B = 3, C = 2.
--     Then list only the courses whose average grade point is higher than the overall
--     average grade point across all enrollments in the university.

-- Q9. Find the department(s) where the total fees collected (summing Fee_Payment.amount
--     from students who belong to that department) is more than 20% of the department's
--     budget.
--     Show department name, total collected, budget, and the percentage.

-- Q10. Find students who have issued a book but never made a Spring2024 fee payment.
--      Show student name, department, and how many books they've issued.

-- Q11. (Relational division) Find the student(s) who have enrolled in every single course
--      offered by their own home department.
--      Hint: for each student, there should be no course in their department that they
--      have not taken - this is a classic double-NOT-EXISTS pattern.

-- Q12. Find instructor(s) for whom every student who has ever taken one of their courses
--      received a grade of A or B only - i.e., no student of theirs has ever gotten a C
--      or lower.
--      Show instructor name and department.

-- Q13. Find students who currently have an outstanding (unreturned) book - return_date
--      IS NULL - and are also enrolled in a course scheduled in a room that some other
--      course also uses (a room shared by 2+ courses).
--      Show student name, book title, and the shared room number.