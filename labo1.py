print('Laboratory exercises')
#adding ex1 forn Cami's branch
n = int(input("¿Cuántos números quieres sumar?: "))
total = 0


for i in range(n):
    num = float(input(f"Ingresa el número {i+1}: "))
    total += num

print(f"La suma de los {n} números es: {total}")
#dsgit push

#Excercise 2
def invert_number(n):
    return int(str(n)[::-1])

# Example
#num_input = 9565
#inverted = invert_number(num_input)
#print(inverted) 