products = []

n = int(input("How many products do you want to enter? "))

for i in range(n):
    name = input("Enter product name: ")
    stock = int(input("Enter quantity in stock: "))

    product = {"name": name, "stock": stock}
    products.append(product)

print("\nProducts with stock less than 10:")
for item in products:
    if item["stock"] < 10:
        print(item["name"], "- Stock:", item["stock"])
