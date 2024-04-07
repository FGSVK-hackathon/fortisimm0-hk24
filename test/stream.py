from serial import Serial # type: ignore
from random import randint

def randTone():
    return (randint(600, 1500), randint(100, 1000))

with Serial("COM5", 9600) as s:
    for i in range(2):
        for i in range(4):
            f, dt = randTone()
            s.write(f.to_bytes(2, "big"))
            s.write(dt.to_bytes(2, "big"))
        s.readline()

