import sys
import gc

class Node:
    def __init__(self, name):
        self.name = name
        self.link = None

    def __del__(self):
        print(f"{self.name} is being destroyed")


# STEP 1: Create Nodes
A = Node("A")
B = Node("B")

# STEP 2: Create Circular Reference
A.link = B
B.link = A

print("Cycle created:")
print("A ->", A.link.name)
print("B ->", B.link.name)

# STEP 3: Check Reference Counts
print("\nReference Counts:")
print("A:", sys.getrefcount(A))
print("B:", sys.getrefcount(B))

# Disable automatic garbage collection
gc.disable()

# Keep temporary references for investigation
tempA = A
tempB = B

# STEP 4: Delete Original References
del A
del B

print("\nOriginal references deleted.")

# Objects still exist because tempA/tempB still reference them
print("Objects still accessible through temporary references:")
print(tempA.name)
print(tempB.name)

# Remove final external references
del tempA
del tempB

print("\nNow objects are unreachable but still in memory due to cycle.")

# STEP 5: Investigate Garbage Collector
print("Unreachable objects before collection:", len(gc.garbage))

# STEP 6: Force Garbage Collection
collected = gc.collect()

print("\nGarbage Collector executed.")
print("Unreachable objects collected:", collected)

# Re-enable GC
gc.enable()