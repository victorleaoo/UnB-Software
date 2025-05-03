# This example requires the 'message_content' intent.

import discord

class MyClient(discord.Client):
    async def on_ready(self):
        print(f'Logged on as {self.user}!')

    async def on_message(self, message):
        print(f'Message from {message.author}: {message.content}')

intents = discord.Intents.default()
intents.message_content = True

client = MyClient(intents = discord.Intents.all())
client.run('MTE4NDk5NjEzNDQ5MDQ3NjU2NA.GXfIQ1.00m1UPsPGYg_SL5pZkbG8BAMgX_c1hzRFkcS0k')
