# Discord Bot for the Marquee

This is the code for the discord bot that controls the marquee. It runs off of a Flask backend.

The current plan is to host both the discord bot and the Flask app off of a free web token on Heroku.

Necessary edits:
1. Change the '/get_message' method so that it sends the pixels instead of the entire message

List of possible edits:
1. FIFO of messages
2. If we go with the FIFO, add a method to remove messages from the fifo
3. Styles for the message class (ie. scrolling, static, etc)
