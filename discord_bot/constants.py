import os
from dotenv import load_dotenv

load_dotenv()
TOKEN = os.getenv("DISCORD_TOKEN")
PORT = os.environ.get("PORT", 5000)
URL = ""