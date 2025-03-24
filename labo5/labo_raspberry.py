################################ LABORATORY 5 RASPBERRY ##################################### 
##################################### Ej 1 RASPBERRY ########################################
import serial

ser = serial.Serial("/dev/serial0", 115200, timeout=1)

print("Esperando datos UART...")

while True:
    data = ser.readline().decode('utf-8').strip()
    if data:
        print(f"Mensaje recibido: {data}")

##################################### Ej 2 RASPBERRY ########################################

import serial
import RPi.GPIO as GPIO

MOTOR1_ENA = 17  # Habilitación del Motor 1
MOTOR1_IN1 = 27  # Dirección del Motor 1

MOTOR2_ENB = 22  # Habilitación del Motor 2
MOTOR2_IN3 = 23  # Dirección del Motor 2

# Configurar GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(MOTOR1_ENA, GPIO.OUT)
GPIO.setup(MOTOR1_IN1, GPIO.OUT)
GPIO.setup(MOTOR2_ENB, GPIO.OUT)
GPIO.setup(MOTOR2_IN3, GPIO.OUT)

# Inicializar UART
ser = serial.Serial("/dev/serial0", 115200, timeout=1)

print("Esperando datos UART...")

while True:
    data = ser.readline().decode('utf-8').strip()
    
    if data:
        print(f"Mensaje recibido: {data}")
        
        if data == "motor1":
            # Activar Motor 1
            GPIO.output(MOTOR1_IN1, GPIO.HIGH)
            GPIO.output(MOTOR1_ENA, GPIO.HIGH)
            
            # Apagar Motor 2
            GPIO.output(MOTOR2_ENB, GPIO.LOW)

        elif data == "motor2":
            # Activar Motor 2
            GPIO.output(MOTOR2_IN3, GPIO.HIGH)
            GPIO.output(MOTOR2_ENB, GPIO.HIGH)
            
            # Apagar Motor 1
            GPIO.output(MOTOR1_ENA, GPIO.LOW)

        print(f"Motor 1: {'ON' if data == 'motor1' else 'OFF'}, Motor 2: {'ON' if data == 'motor2' else 'OFF'}")

##################################### Ej 3 RASPBERRY ########################################
import serial
import RPi.GPIO as GPIO

MOTOR1_ENA = 17  # PWM Motor 1
MOTOR1_IN1 = 27  # Dirección Motor 1
MOTOR2_ENB = 22  # PWM Motor 2
MOTOR2_IN3 = 23  # Dirección Motor 2

GPIO.setmode(GPIO.BCM)
GPIO.setup(MOTOR1_ENA, GPIO.OUT)
GPIO.setup(MOTOR1_IN1, GPIO.OUT)
GPIO.setup(MOTOR2_ENB, GPIO.OUT)
GPIO.setup(MOTOR2_IN3, GPIO.OUT)

# Configurar PWM
pwm_motor1 = GPIO.PWM(MOTOR1_ENA, 1000)  # 1000 Hz
pwm_motor2 = GPIO.PWM(MOTOR2_ENB, 1000)  # 1000 Hz

pwm_motor1.start(0)  # Inicia apagado
pwm_motor2.start(0)  # Inicia apagado

# Inicializar UART
ser = serial.Serial("/dev/serial0", 115200, timeout=1)

print("Esperando datos UART...")

while True:
    data = ser.readline().decode('utf-8').strip()
    
    if data:
        print(f"Mensaje recibido: {data}")
        
        if data == "motor1":
            # Encender ambos motores al 50%
            GPIO.output(MOTOR1_IN1, GPIO.HIGH)
            GPIO.output(MOTOR2_IN3, GPIO.HIGH)
            pwm_motor1.ChangeDutyCycle(50)
            pwm_motor2.ChangeDutyCycle(50)

        elif data == "motor2":
            # Apagar ambos motores
            pwm_motor1.ChangeDutyCycle(0)
            pwm_motor2.ChangeDutyCycle(0)
            GPIO.output(MOTOR1_IN1, GPIO.LOW)
            GPIO.output(MOTOR2_IN3, GPIO.LOW)

        print(f"Motor 1: {'ON' if data == 'motor1' else 'OFF'}, Motor 2: {'ON' if data == 'motor1' else 'OFF'}")

##################################### Ej 4 RASPBERRY ########################################
Ej 4 raspberry
de la tiva es el mismo que el ej1
import serial
import RPi.GPIO as GPIO
import time

# Definir pines de los motores
MOTOR1_ENA = 17  # PWM Motor 1
MOTOR1_IN1 = 27  # Dirección Motor 1
MOTOR2_ENB = 22  # PWM Motor 2
MOTOR2_IN3 = 23  # Dirección Motor 2

# Configurar GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(MOTOR1_ENA, GPIO.OUT)
GPIO.setup(MOTOR1_IN1, GPIO.OUT)
GPIO.setup(MOTOR2_ENB, GPIO.OUT)
GPIO.setup(MOTOR2_IN3, GPIO.OUT)

# Configurar PWM
pwm_motor1 = GPIO.PWM(MOTOR1_ENA, 1000)  # 1000 Hz
pwm_motor2 = GPIO.PWM(MOTOR2_ENB, 1000)  # 1000 Hz

pwm_motor1.start(0)  # Inicia apagado
pwm_motor2.start(0)  # Inicia apagado

# Inicializar UART
ser = serial.Serial("/dev/serial0", 115200, timeout=1)

# Leer Duty Cycle desde el archivo
def leer_duty_cycle():
    try:
        with open("duty_cycle.txt", "r") as file:
            value = file.readline().strip()
            return int(value)  # Convertir a número
    except:
        return 50  # Valor por defecto si hay error

print("Esperando datos UART...")

while True:
    data = ser.readline().decode('utf-8').strip()
    duty_cycle = leer_duty_cycle()  # Leer el valor actual del Duty Cycle

    if data:
        print(f"Mensaje recibido: {data}")
        
        if data == "motor1":
            # Encender ambos motores con el Duty Cycle actual
            GPIO.output(MOTOR1_IN1, GPIO.HIGH)
            GPIO.output(MOTOR2_IN3, GPIO.HIGH)
            pwm_motor1.ChangeDutyCycle(duty_cycle)
            pwm_motor2.ChangeDutyCycle(duty_cycle)

        elif data == "motor2":
            # Apagar ambos motores
            pwm_motor1.ChangeDutyCycle(0)
            pwm_motor2.ChangeDutyCycle(0)
            GPIO.output(MOTOR1_IN1, GPIO.LOW)
            GPIO.output(MOTOR2_IN3, GPIO.LOW)

        print(f"Motor 1: {'ON' if data == 'motor1' else 'OFF'}, Motor 2: {'ON' if data == 'motor1' else 'OFF'}")

##################################### Ej 5 RASPBERRY ########################################

import serial
import RPi.GPIO as GPIO
import time

# Configurar UART
ser = serial.Serial("/dev/serial0", 115200, timeout=1)

# Configurar GPIO
BUTTON_PIN = 24
GPIO.setmode(GPIO.BCM)
GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Botón con resistencia pull-up

print("Esperando pulsación de botón para enviar señal a la Tiva...")

try:
    while True:
        button_state = GPIO.input(BUTTON_PIN)
        if button_state == GPIO.LOW:  # Botón presionado (porque está a GND)
            ser.write(b"1\n")  # Envía la señal "1" a la Tiva
            print("Botón presionado. Enviando '1' a la Tiva.")
            time.sleep(0.5)  # Pequeña pausa para evitar rebotes
except KeyboardInterrupt:
    GPIO.cleanup()
    ser.close()