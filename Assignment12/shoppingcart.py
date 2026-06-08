from typing import Protocol


class Item:
    def __init__(self, name, price):
        self.name  = name
        self.price = price


class PaymentMethod(Protocol):
    def pay(self, amount: float) -> bool:
        ...


class CashPayment:
    def __init__(self, given):
        self.given = given

    def pay(self, amount):
        if self.given >= amount:
            print(f"Paid Rs. {amount} in cash. Change: Rs. {self.given - amount}")
            return True
        else:
            print(f"Not enough cash! Short by Rs. {amount - self.given}")
            return False


class UPIPayment:
    def __init__(self, upi_id):
        self.upi_id = upi_id

    def pay(self, amount):
        print(f"Rs. {amount} collected via UPI ({self.upi_id})")
        return True


class WalletPayment:
    def __init__(self, balance):
        self.balance = balance

    def pay(self, amount):
        if self.balance >= amount:
            self.balance -= amount
            print(f"Rs. {amount} deducted from wallet. Remaining: Rs. {self.balance}")
            return True
        else:
            print(f"Wallet balance low! Need Rs. {amount - self.balance} more.")
            return False


class Checkout:
    def __init__(self, items: list, payment: PaymentMethod):
        self.items   = items
        self.payment = payment

    def get_total(self):
        total = 0
        for item in self.items:
            total += item.price
        return total

    def show_items(self):
        print("\nYour Order")
        for item in self.items:
            print(f"  {item.name} - Rs. {item.price}")
        print(f"  Total: Rs. {self.get_total()}")

    def process(self):
        self.show_items()
        total   = self.get_total()
        success = self.payment.pay(total)
        if success:
            print("Order confirmed! Thank you.")
        else:
            print("Order failed. Please try again.")


print("Welcome to Shop\n")

items = [
    Item("Pen",      10),
    Item("Notebook", 50),
    Item("Eraser",    5),
]

print("\nPaying with Cash")
Checkout(items, CashPayment(given=100)).process()

print("\nPaying with UPI")
Checkout(items, UPIPayment(upi_id="myshop@upi")).process()

print("\nPaying with Wallet (low balance)")
Checkout(items, WalletPayment(balance=30)).process()

print("\nPaying with Wallet (enough balance)")
Checkout(items, WalletPayment(balance=200)).process()