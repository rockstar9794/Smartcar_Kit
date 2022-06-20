from getkey import getkey
import time
import RPi.GPIO as GPIO

left12,left16,right18,right22=(12,16,18,22)

  while True: 
    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)
    key = getkey()
      
    if key=='w':
        GPIO.setup(left16,GPIO.OUT)
        GPIO.setup(right22,GPIO.OUT)
        GPIO.output(left16, True)
        GPIO.output(right22, True)
        time.sleep(0.3)
          
    elif key=='d':
        GPIO.setup(left16,GPIO.OUT)
        GPIO.setup(right22,GPIO.OUT)
        GPIO.output(left16, True)
        GPIO.output(right22, False)
        time.sleep(0.3)
          
    elif key=='a':
        GPIO.setup(left16,GPIO.OUT)
        GPIO.setup(right22,GPIO.OUT)
        GPIO.output(left16, False)
        GPIO.output(right22, True)
        time.sleep(0.3)
          
    elif key=='s':
        GPIO.setup(left12,GPIO.OUT)
        GPIO.setup(left16,GPIO.OUT)
        GPIO.setup(right18,GPIO.OUT)
        GPIO.setup(right22,GPIO.OUT)
        GPIO.output(left12, True)
        GPIO.output(left16, False)
        GPIO.output(right18, True)
        GPIO.output(right22, False)
        time.sleep(0.3)
    GPIO.cleanup()  
