#laboratory 2, Excercise
#ej 1
#En la raspberry se llama button_2
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

if __name__ == "__main__":
    setup()
    loop()