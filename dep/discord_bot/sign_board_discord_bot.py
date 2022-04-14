import os
from discord import (Bot, Intents)
from discord.ext import commands
from flask import Flask, Response, request

from constants import PORT, TOKEN
from classes.message import Message

app = Flask(__name__)
bot = Bot(intents=Intents.default())
global_message = Message(text="")

@app.route("/get_message", methods=["GET"])
def get_message() -> Response:
    return Response(
        status=200,
        content=global_message.__dict__
    )

@app.route("/post_message", methods=["POST"])
def send_message() -> Response:
    global_message.text = request.form["text"]
    global_message.font = request.form["font"]
    global_message.size = request.form["size"]
    return Response(status=200)

for filename in os.listdir("./cogs"):
    if filename.endswith(".py"):
        bot.load_extension(f"cogs.{filename[:-3]}")

bot.loop.create_task(app.run(host='0.0.0.0', port=PORT))

bot.run({TOKEN})