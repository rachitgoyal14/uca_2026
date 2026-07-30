# ON DELETE CASCADE in MySQL

## What is `ON DELETE CASCADE`?

`ON DELETE CASCADE` is a **foreign key option** in MySQL that automatically deletes related rows in a child table when a row in the parent table is deleted.

It maintains **referential integrity** by preventing orphan records.

---

## Parent and Child Tables

Consider this relationship:

```
Department (Parent Table)
        |
        | dept_id
        ↓
Course (Child Table)
```

A department can have many courses.

### Department Table

| dept_id | dept_name |
|---------|-----------|
| 1       | CS        |
| 2       | Electronics |
| 3       | Mechanical |

### Course Table

| course_id | course_name | dept_id |
|-----------|-------------|---------|
| 201       | DBMS        | 1       |
| 202       | OS          | 1       |
| 203       | Circuits    | 2       |

Here, `Course.dept_id` references `Department.dept_id`.

---

## Creating a Foreign Key with ON DELETE CASCADE

Example:

```sql
CREATE TABLE Course (
    course_id INT PRIMARY KEY,
    course_name VARCHAR(100),
    dept_id INT,

    FOREIGN KEY (dept_id)
    REFERENCES Department(dept_id)
    ON DELETE CASCADE
);
```

The important part is:

```sql
ON DELETE CASCADE
```

It tells MySQL:

> If a department is deleted, automatically delete all courses belonging to that department.

---

## Example

Delete the CS department:

```sql
DELETE FROM Department
WHERE dept_id = 1;
```

Before deletion:

### Department

| dept_id | dept_name |
|---------|-----------|
| 1       | CS        |
| 2       | Electronics |

### Course

| course_id | course_name | dept_id |
|-----------|-------------|---------|
| 201       | DBMS        | 1       |
| 202       | OS          | 1       |
| 203       | Circuits    | 2       |

---

After deletion:

### Department

| dept_id | dept_name |
|---------|-----------|
| 2       | Electronics |

### Course

| course_id | course_name | dept_id |
|-----------|-------------|---------|
| 203       | Circuits    | 2       |

The courses:

```
201 | DBMS | 1
202 | OS   | 1
```

are automatically removed.

---

# Without ON DELETE CASCADE

If the foreign key does not use cascade:

```sql
FOREIGN KEY (dept_id)
REFERENCES Department(dept_id)
```

Trying to delete a department that still has courses:

```sql
DELETE FROM Department
WHERE dept_id = 1;
```

will fail.

MySQL prevents the deletion because courses still depend on that department.

You would have to manually remove the courses first:

```sql
DELETE FROM Course
WHERE dept_id = 1;

DELETE FROM Department
WHERE dept_id = 1;
```

---

# Other DELETE Actions

## 1. ON DELETE CASCADE

Deletes dependent rows automatically.

Example:

```
Delete Department
        |
        ↓
Delete related Courses
```

---

## 2. ON DELETE SET NULL

Sets the foreign key value to NULL instead of deleting.

Example:

```sql
FOREIGN KEY (dept_id)
REFERENCES Department(dept_id)
ON DELETE SET NULL
```

Result:

Before:

| course_id | dept_id |
|-----------|---------|
| 201       | 1       |

After deleting department 1:

| course_id | dept_id |
|-----------|---------|
| 201       | NULL    |

---

## 3. Default Behavior (RESTRICT)

Without specifying an action:

```sql
FOREIGN KEY (dept_id)
REFERENCES Department(dept_id)
```

MySQL prevents deletion if related rows exist.

---

# Summary Table

| Option | What Happens |
|--------|--------------|
| `ON DELETE CASCADE` | Deletes related child rows automatically |
| `ON DELETE SET NULL` | Sets child foreign key to NULL |
| Default/RESTRICT | Prevents deletion if children exist |

---

# Key Points to Remember

- A **foreign key connects two tables**.
- The parent table contains the referenced key.
- The child table contains the foreign key.
- `ON DELETE CASCADE` automatically removes dependent records.
- It is useful when child records should not exist without the parent record.