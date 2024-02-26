import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")
with open('students.csv', 'r') as file:
    reader = csv.DictReader(file)

    names = [{"name": row["student_name"]} for row in reader]
    houses = [{"house": row["house"], "head" : row["head"]} for row in reader]
   


for name in names:
    db.execute("insert into new_students (student_name) values (?)", name["name"] )
for house in houses:
    db.execute("insert into houses (house, head) values (?, ?)", house["house"], house["head"])
for ass
