import asyncio
import websockets
import RPi.GPIO as GPIO
import time

STEP_PIN = 21
DIR_PIN = 20
ENB_PIN = 26
PWM_FREQ = 1000  # Частота ШИМ
DUTY_CYCLE = 50  # Скважность ШИМ (в процентах)

MICROSTEPS = 1
SPR = 200 # Количество шагов на оборот
GEAR_RATIO = 40 # Передаточное число редуктора

GPIO.setwarnings(False)

GPIO.setmode(GPIO.BCM)
GPIO.setup(STEP_PIN, GPIO.OUT)
GPIO.setup(DIR_PIN, GPIO.OUT)
GPIO.setup(ENB_PIN, GPIO.OUT)

pwm = GPIO.PWM(STEP_PIN, PWM_FREQ)
#pwm.start(DUTY_CYCLE)

def deg2step(angle):

    GPIO.output(ENB_PIN, GPIO.LOW)
    time.sleep(0.000005)

    total_steps = int(angle * (SPR * GEAR_RATIO * MICROSTEPS) / 360)
    
    if angle >= 0:
        GPIO.output(DIR_PIN, GPIO.HIGH)
        time.sleep(0.000005)
        print("Вращение по часовой стрелке")
    else:
        GPIO.output(DIR_PIN, GPIO.LOW)
        time.sleep(0.000005)
        print('Вращение против часовой стрелке')
    print("Количество шагов:%d" % total_steps)
   
    pwm.start(DUTY_CYCLE)
    time.sleep(total_steps*(1/PWM_FREQ))
    GPIO.output(ENB_PIN, GPIO.HIGH)
    time.sleep(0.000005)
    pwm.stop()

async def receive_angle(websocket, path):
    angle = await websocket.recv()
    angle = float(angle)  # преобразуем угол в число
    print("Значение получено\nНачалось вращение на %d градусов" % angle)
    deg2step(angle)
    print("Двигатель повернут на {} градусов".format(angle))

    
     
try:
    start_server = websockets.serve(receive_angle, "172.20.10.2", 8764)
    asyncio.get_event_loop().run_until_complete(start_server)
    asyncio.get_event_loop().run_forever()
    
except KeyboardInterrupt:
    print("Прервано пользователем(^C)")
finally:
    pwm.stop()
    GPIO.cleanup()

