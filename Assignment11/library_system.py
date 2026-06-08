from abc import ABC, abstractmethod

class LibraryItem(ABC):
    total_items = 0

    def __init__(self, title, year):
        self.title = title
        self.year = year
        LibraryItem.total_items += 1

    @abstractmethod
    def displayInfo(self):
        pass


class Book(LibraryItem):
    def __init__(self, title, year=0, author="Unknown"):
        super().__init__(title, year)
        self.author = author

    def displayInfo(self):
        print("Book")
        print("Title:", self.title)
        print("Year:", self.year)
        print("Author:", self.author)


class DVD(LibraryItem):
    def __init__(self, title, year, duration, genre):
        super().__init__(title, year)
        self.duration = duration
        self.genre = genre

    def displayInfo(self):
        print("DVD")
        print("Title:", self.title)
        print("Year:", self.year)
        print("Duration:", self.duration)
        print("Genre:", self.genre)


if __name__ == "__main__":
    items = [
        Book("Java Basics", 2022, "James Gosling"),
        Book("Python Guide", author="Guido van Rossum"),
        DVD("Inception", 2010, 148, "Sci-Fi")
    ]

    for item in items:
        print()
        item.displayInfo()

    print("\nTotal Library Items:", LibraryItem.total_items)