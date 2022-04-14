from discord import (ApplicationContext, Bot, Cog, commands)

class AdminCog(Cog):
    __bot: Bot

    def __init__(self, bot: Bot) -> None:
        self.__bot = bot

    @commands.slash_command(name="load_extension", hidden=True)
    @commands.is_owner()
    async def _load_extension(self, ctx: ApplicationContext, extension: str) -> None:
        self.__bot.load_extension(f"cogs.{extension}")
        await ctx.respond(f"{extension} was loaded")

    @commands.slash_command(name="unload_extension", hidden=True)
    @commands.is_owner()
    async def _unload_extension(self, ctx: ApplicationContext, extension: str) -> None:
        self.__bot.unload_extension(f"cogs.{extension}")
        await ctx.respond(f"{extension} was unloaded")

    @commands.slash_command(name="reload_extension", hidden=True)
    @commands.is_owner()
    async def _reload_extension(self, ctx: ApplicationContext, extension: str) -> None:
        self.__bot.reload_extension(f"cogs.{extension}")
        await ctx.respond(f"{extension} was reloaded")

def setup(bot: Bot) -> None:
    bot.add_cog(AdminCog(bot))