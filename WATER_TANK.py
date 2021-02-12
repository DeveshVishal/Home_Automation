import RPi.GPIO as GPIO 
import time
#GPIO SETUP
channel = 20 
GPIO.setmode(GPIO.BCM) 
GPIO.setup(channel, GPIO.IN) 
GPIO.setwarnings(False) 
GPIO.setup(22,GPIO.OUT) 
#GPIO.setup(27,GPIO.OUT)

def callback(channel):
	if GPIO.input(channel):
		GPIO.output(22,GPIO.HIGH) 
		print("Water Detected!") 
		time.sleep(1)
	else:
		GPIO.output(22,GPIO.LOW) 
		print("Water not Detected!") 
		time.sleep(1)

GPIO.add_event_detect(channel, GPIO.BOTH, bouncetime=300) # let us know when the pin goes HIGH or LOW
GPIO.add_event_callback(channel, callback) # assign function to GPIO PIN, Run function on change
# infinite loop 
while True:
	time.sleep(1)

if __name__ == '__main__':
	try:
		main()
		except KeyboardInterrupt:
		GPIO.cleanup()