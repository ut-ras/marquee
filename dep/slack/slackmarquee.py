#this script is meant to be run on a raspi, connected to the LED board over UART

# importing the requests library
import requests
import time
import serial
import ctypes


# api-endpoint - get slack channel history
# https://api.slack.com/methods/groups.history
URL = "https://slack.com/api/groups.history"

# token for marquee slack app
token = None

# channel id for marquee slack channel
marqueechannel = "G8B0PQMDE"

# parameters for message history
inclusive = "true"
unreads = "true"

#serial port
ser = None

def main():
	init()
	while 1:
	    lastmessage = getLastMessage()
	    uartFromPi(lastmessage)
	    time.sleep(30)


# setup stuff
def init():
	global ser, token	
	ser = serial.Serial(port='/dev/ttyACM0', baudrate=115200)
	print ser.portstr
	f = open("token", "r")
	token = f.read()


# send string over uart from pi to marquee
def uartFromPi(message):
	 ser.write("\n")
	 m = message.decode("utf-8")
	 m = m.encode()
	 while(len(m) < 25):
	     m = m+ " "
	 print(m)
	 ser.write(m+"\n")


# get a number of most recent messages from the channel
def getChannelHistory(count):
	# defining a params dict for the parameters to be sent to the API
	PARAMS = {'token':token, 'channel':marqueechannel, 'count':count, 'inclusive':inclusive, 'unreads':unreads}
	# sending get request and saving the response as response object
	r = requests.get(url = URL, params = PARAMS)
	# extracting data in json format - channel history, count = num messages
	data = r.json()
	return data


# extract last message from channel
def getLastMessage():
	data = getChannelHistory(1);
	lastmessage = data['messages'][0]['text']
	return lastmessage


if __name__ == "__main__":
	main()
