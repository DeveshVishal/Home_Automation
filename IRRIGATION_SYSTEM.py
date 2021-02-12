import RPi.GPIO as GPIO 
import time
#GPIO SETUP
channel = 21 GPIO.setmode(GPIO.BCM)
GPIO.setup(channel, GPIO.IN)
GPIO.setwarnings(False)
GPIO.setup(24,GPIO.OUT) 
#GPIO.setup(27,GPIO.OUT)
def callback(channel):
	if GPIO.input(channel):
		print("Water NOT Detected!") GPIO.output(24,GPIO.LOW) time.sleep(1)
	else:
		print("Water Detected!") 
		GPIO.output(24,GPIO.HIGH) 
		time.sleep(1)
GPIO.add_event_detect(channel, GPIO.BOTH, bouncetime=300) # let us know when the pin goes HIGH or LOW
GPIO.add_event_callback(channel, callback) # assign function to GPIO PIN, Run function on change
# infinite loop 
while True:
	time.sleep(1)