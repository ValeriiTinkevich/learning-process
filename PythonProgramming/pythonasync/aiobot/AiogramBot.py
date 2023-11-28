from aiogram import Bot, Dispatcher
from aiogram.filters import Command
from aiogram.types import Message
from dotenv import  load_dotenv
import os

load_dotenv()   

BOT_TOKEN = os.getenv('BOT_TOKEN')

