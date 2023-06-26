import csv
from cs50 import SQL

def create_house(house, houses, head):
     
        houses.append({"house": house, "head": head})
				
def create_student(name, students):
	students.append({"student_name": name})
	
def create_relationship(name, house, students_houses):
	students_houses.append({"student_name": name, "house": house})

db = SQL("sqlite:///roster.db")

students = []
houses = []
students_houses = []

# script_path = os.path.dirname(os.path.abspath(__file__))
# csv_file_path = os.path.join(script_path, "students.csv")

with open("students.csv", "r") as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        name = row["student_name"]
        house = row["house"]
        head = row["head"]
        create_house(house, houses, head)
        create_student(name, students)
        create_relationship(name, house, students_houses)
	
for student in students:
	db.execute("INSERT INTO students_new (student_name) VALUES (?)", student["student_name"])
        
for relationship in students_houses:
	db.execute("INSERT INTO students_houses (student_name, house) VALUES (?,?)", relationship["student_name"], relationship["house"])
	
for house in houses:
	db.execute("INSERT INTO houses (house, head) VALUES (?,?)", house["house"], house["head"])