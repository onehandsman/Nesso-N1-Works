import os, sys, io
import M5
from M5 import *

count = 0
count_label = None


def update_display():
    count_label.setText(str(count))


def setup():
    global count_label
    M5.begin()
    Widgets.setRotation(0)
    Widgets.fillScreen(0x000000)
    count_label = Widgets.Label(
        "0", 45, 80, 1.0, 0xFFFFFF, 0x000000, Widgets.FONTS.DejaVu40
    )
    update_display()


def loop():
    global count
    M5.update()

    if M5.Touch.getCount() > 0:
        detail = M5.Touch.getDetail(0)
        if detail[5]:
            count += 1
            update_display()

    if BtnA.wasPressed():
        count = 0
        update_display()


if __name__ == "__main__":
    try:
        setup()
        while True:
            loop()
    except (Exception, KeyboardInterrupt) as e:
        try:
            from utility import print_error_msg
            print_error_msg(e)
        except ImportError:
            print("please update to latest firmware")
