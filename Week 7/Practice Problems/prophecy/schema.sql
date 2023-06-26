CREATE TABLE students_new (
    id INTEGER,
    student_name TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    id INTEGER,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE students_houses (
    id INTEGER,
    student_name TEXT,
    house TEXT,
    PRIMARY KEY(id)
); 