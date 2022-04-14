import requests
from discord import (ApplicationContext, Bot, Cog, Embed, commands)
from discord.commands import Option

from classes.message import Message
from constants import URL

class MessageCog(Cog):
    __bot: Bot

    def __init__(self, bot: Bot) -> None:
        self.__bot = bot

    @commands.slash_command(name="message")
    async def _message(
        self, 
        ctx: ApplicationContext,
        text: Option(str, "Message to be displayed on the screen", required=True),
        font: Option(str, "Font for the message", required=False, default=""),
        size: Option(int, "Size of the font", required=False, default=0)
    ) -> None:
        # send message to the web server
        response = requests.post(
            url=URL,
            form={
                "text" : text,
                "font" : font,
                "size" : size
            })
        embed = Embed(title="Post Request Response", description=response)
        await ctx.respond(embed=embed)

def setup(bot: Bot) -> None:
    bot.add_cog(MessageCog(bot))