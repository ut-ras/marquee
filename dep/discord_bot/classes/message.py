
from typing import Optional

class Message:
    __text: str
    __length: int
    __font: str
    __size: int
    

    def __init__(self, text: str, font: Optional[str]=None, size: Optional[int]=None):
        self.__text = text
        self.__length = len(text)
        self.__font = "" if font == None else font
        self.__size = 0 if size == None else size

    @property
    def text(self) -> str:
        return self.__text

    @text.setter
    def text(self, text: str) -> None:
        self.__text = text
        self.__length = len(text)

    @property
    def length(self) -> int:
        return self.__length

    @property
    def font(self) -> str:
        return self.__font

    @font.setter
    def font(self, font: str) -> None:
        self.__font = font

    @property
    def size(self) -> int:
        return self.__size

    @size.setter
    def size(self, size: int) -> None:
        self.__size = size
