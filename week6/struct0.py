from cs50 import get_string
from student import Student

students = []
dorms = []

for i in range(3):
    name = get_string("Name: ")
    dorm = get_string("Dorm: ")
    s = Student(name, dorm)
    students.append(s)

for student in students:
    print(f"{student.name} lives in {student.dorm}")