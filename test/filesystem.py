from serial import Serial # type: ignore
from random import randint
import os

AUDIO_DIR = "./audio"

fileList = [f for f in os.listdir(AUDIO_DIR)]
print(fileList)

with Serial("COM5", 9600) as s:
    s.flush()

    fileIndex = min(int(input("File index: ")), len(fileList) - 1)

    read = 0

    with open(f"{AUDIO_DIR}/{fileList[fileIndex]}", "rb") as file:
        while (stream := file.read(1)):
            print(stream)
            s.write(stream)
            read += 1

            if read >= 16:
                s.readline()
                read = 0


