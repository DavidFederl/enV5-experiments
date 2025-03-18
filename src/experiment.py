from elasticai.usbprotocol.user_remote_control import UserRemoteControl
from elasticai.usbprotocol.helper_utils import get_env5_port

from serial import Serial

from time import sleep

remote: UserRemoteControl

def init():
    global remote
    env5_serial = Serial(port=get_env5_port())
    print(f"Connected to {env5_serial}")
    remote = UserRemoteControl(device=env5_serial)

def experiement():
    global remote
    remote.mcu_leds(True, True, True)

    sleep(3.0)

    remote.mcu_leds(False, False, False)

if __name__=="__main__":
    init()
    experiement()
