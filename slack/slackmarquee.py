#this script is meant to be run on a raspi, connected to the LED board over UART

# importing the requests library
import requests

#https://api.slack.com/methods/channels.history

# api-endpoint
URL = "https://slack.com/api/channels.history"

# parameters
token = "xoxp-7065433170-134502887458-284553027734-612eedd09632bb8c04f8d7cb765d59b1"
channel = ""
count = "10"
inclusive = "true"
unreads = "true"

# defining a params dict for the parameters to be sent to the API
PARAMS = {'token':token, 'channel':channel, 'count':count, 'inclusive':inclusive, 'unreads':unreads}

while(1):
    # sending get request and saving the response as response object
    r = requests.get(url = URL, params = PARAMS)

    # extracting data in json format - channel history last 10 messages
    data = r.json()

    # extract last message
    lastmessage = data['results'][0]['messages']['text']

    # printing the output
    print(lastmessage)

    #TODO send over UART to marquee
