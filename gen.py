import random as rand

lines = int(input("How many line?\n"))

file = open("input.txt","w+");

for i in range(lines):
    ran = rand.randint(1,1000)
    file.writelines(str(ran) + "\n")

file.close()

print("DONE")