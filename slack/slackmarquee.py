#this script is meant to be run on a raspi, connected to the LED board over UART

# importing the requests library
import requests
import time
import wiringpi2 as wiringpi


# api-endpoint - get slack channel history
# https://api.slack.com/methods/groups.history
URL = "https://slack.com/api/groups.history"

# token for marquee slack app
token = ""
# channel id for marquee slack channel
marqueechannel = "G8B0PQMDE"

# parameters for message history
inclusive = "true"
unreads = "true"

#serial port
serial = 0

def main():
	init()
	lastmessage = getLastMessage()
	uartFromPi(lastmessage)
	time.sleep(1)
	wiringpi.serialClose(serial)


# setup stuff
def init():
	global serial
	serial = wiringpi.serialOpen('/dev/ttyAMA0', 9600)


# send string over uart from pi to marquee
def uartFromPi(message):
	 print(message)
	 wiringpi.serialPuts(serial, message)


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
