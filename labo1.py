print('Laboratory exercises')
#adding ex1 forn Cami's branch
n = int(input("¿Cuántos números quieres sumar?: "))
total = 0


for i in range(n):
    num = float(input(f"Ingresa el número {i+1}: "))
    total += num

print(f"La suma de los {n} números es: {total}")
#dsgit push