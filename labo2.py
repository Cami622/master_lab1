#laboratory 2, excercises
##EX1
Ejercicio 1
En la raspberry se llama button_2
import RPi.GPIO as GPIO
import time

LED = 16    
LED_2 = 12     
BUTTON = 18 

# Variable global para almacenar el estado
state = 0  

def setup():
    """ Configura los pines GPIO """
    GPIO.setmode(GPIO.BCM)  
    GPIO.setup(LED, GPIO.OUT)  
    GPIO.setup(LED_2, GPIO.OUT)  
    GPIO.setup(BUTTON, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def estado(valor):
    """ Cambia el estado del sistema cuando el botón es presionado """
    global state  # Indica que usamos la variable global
    state = (state + 1) % 4  # Actualiza el estado cíclicamente entre 0 y 3
    print(f"Nuevo estado: {state}")  # Muestra el estado en la consola

def estado_1():
    """ Alterna LEDs """
    GPIO.output(LED, GPIO.HIGH)
    GPIO.output(LED_2, GPIO.LOW)
    time.sleep(1)
    GPIO.output(LED, GPIO.LOW)
    GPIO.output(LED_2, GPIO.HIGH)
    time.sleep(1)

def estado_2():
    """ Parpadeo simultáneo """
    GPIO.output(LED, GPIO.HIGH)
    GPIO.output(LED_2, GPIO.HIGH)
    time.sleep(2)
    GPIO.output(LED, GPIO.LOW)
    GPIO.output(LED_2, GPIO.LOW)
    time.sleep(2)

def estado_3():
    """ Ambos LEDs encendidos """
    GPIO.output(LED, GPIO.HIGH)
    GPIO.output(LED_2, GPIO.HIGH)

def estado_4():
    """ Ambos LEDs apagados """
    GPIO.output(LED, GPIO.LOW)
    GPIO.output(LED_2, GPIO.LOW)

def loop():
    """ Bucle principal """
    try:
        while True:
            # Comprobar el estado del botón
            if GPIO.input(BUTTON) == GPIO.LOW:  # El botón está presionado
                estado(1)
                time.sleep(0.2)  # Espera para evitar múltiples detecciones debido al rebote
            if state == 0:
                estado_1()
            elif state == 1:
                estado_2()
            elif state == 2:
                estado_3()
            elif state == 3:
                estado_4()
            time.sleep(0.1)
    except KeyboardInterrupt:
        GPIO.cleanup()

if _name_ == "_main_":
    setup()
    loop()
#EXERCISE 2
Ejercicio 2
En la raspberry esta como ej2
import RPi.GPIO as GPIO
import time

button1 = 18  # Botón para incrementar
button2 = 6 # Botón para decrementar

LED_PINS = [16, 12, 19, 26]  # Pines de los LEDs

GPIO.setmode(GPIO.BCM)

# Configurar los pines de los LEDs
for pin in LED_PINS:
    GPIO.setup(pin, GPIO.OUT)

# Configurar los botones
GPIO.setup(button1, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(button2, GPIO.IN, pull_up_down=GPIO.PUD_UP)

i = 0  # Valor inicial

def display_binary(value):
    """Convierte el valor en binario y lo muestra en los LEDs."""
    binary = format(value, '04b')  # Convertir a binario de 4 bits
    for j, pin in enumerate(LED_PINS):
        GPIO.output(pin, int(binary[j]))

try:
    while True:
        if GPIO.input(button1) == GPIO.LOW:  # Botón 1 presionado
            if i < 15:  # Asegurarse de no exceder el límite superior
                i += 1
                display_binary(i)
                print(f"Binary: {format(i, '04b')}")
            time.sleep(0.2)  # Evitar rebotes y múltiples detecciones
        
        if GPIO.input(button2) == GPIO.LOW:  # Botón 2 presionado
            if i > 0:  # Asegurarse de no exceder el límite inferior
                i -= 1
                display_binary(i)
                print(f"Binary: {format(i, '04b')}")
            time.sleep(0.2)  # Evitar rebotes y múltiples detecciones

except KeyboardInterrupt:
    print("\nSaliendo...")
    GPIO.cleanup()  # Limpiar los pines GPIO