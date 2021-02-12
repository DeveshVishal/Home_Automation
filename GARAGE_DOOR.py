import RPi.GPIO as GPIO 
import time

GPIO.setwarnings(False) 
def servo():
	GPIO.setup(25, GPIO.OUT)
	p = GPIO.PWM(25, 50) 
	p.start(0)
	try:
		p.ChangeDutyCycle(7.5) #turntowards90degree 
		time.sleep(15) # sleep 1 second 
		p.ChangeDutyCycle(2.5) #turntowards0degree 
		time.sleep(1) # sleep 1 second
	except KeyboardInterrupt: 
		p.stop()
		GPIO.cleanup() 
	TRIG = 17
	ECHO = 27 
	while(True):
		print ("Distance Measurement In Progress") 
		GPIO.setmode(GPIO.BCM) 
		GPIO.setup(TRIG,GPIO.OUT) 
		GPIO.setup(ECHO,GPIO.IN) 
		GPIO.output(TRIG, False)
		print ("Waiting For Sensor To Settle") 
		time.sleep(1)
		GPIO.output(TRIG, True) 
		time.sleep(0.00001) 
		GPIO.output(TRIG, False)
		while GPIO.input(ECHO)==0: 
			pulse_start = time.time()
		while GPIO.input(ECHO)==1: 
			pulse_end = time.time()
		pulse_duration = pulse_end - pulse_start

		distance = pulse_duration * 17150 distance = round(distance, 2)
		print ("Distance:",distance,"cm") if(distance<10):
		servo() 
		GPIO.cleanup()