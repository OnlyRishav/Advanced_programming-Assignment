
class Address:
    def __init__(self, street, city, zipCode):
        self.street = street
        self.city = city
        self.zipCode = zipCode

    def display(self):
        return f"{self.street}, {self.city} - {self.zipCode}"



class Student:
    def __init__(self, name, age, address):
        self.name = name
        self._age = None  # protected attribute
        self.age = age    # setter call (validation)
        self.address = address  # HAS-A relationship
        self.courses = []  # mutable list

   
    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, value):
        if value <= 0 or value > 120:
            raise ValueError("Invalid age")
        self._age = value

    def add_course(self, course):
        if not course:
            raise ValueError("Course cannot be empty")
        self.courses.append(course)


    def display(self):
        print(f"Name: {self.name}")
        print(f"Age: {self.age}")
        print(f"Address: {self.address.display()}")
        print(f"Courses: {self.courses}")


class ScholarshipStudent(Student):
    def __init__(self, name, age, address, scholarshipAmount):
        super().__init__(name, age, address)
        self.scholarshipAmount = scholarshipAmount

    @property
    def scholarshipAmount(self):
        return self._scholarshipAmount

    @scholarshipAmount.setter
    def scholarshipAmount(self, value):
        if value < 0:
            raise ValueError("Scholarship cannot be negative")
        self._scholarshipAmount = value

    def display(self):
        super().display()
        print(f"Scholarship: {self.scholarshipAmount}")


if __name__ == "__main__":

    addr = Address("GS Road", "Guwahati", "781005")


    s1 = Student("Rahul", 20, addr)


    s1.add_course("Math")
    s1.add_course("Physics")

    print("\n--- Student ---")
    s1.display()


    s2 = ScholarshipStudent("Amit", 22, addr, 5000)

    s2.add_course("AI")
    s2.add_course("ML")

    print("\n--- Scholarship Student ---")
    s2.display()


    try:
        s1.age = -5
    except ValueError as e:
        print("\nError:", e)