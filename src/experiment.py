from elasticai.usbprotocol.user_remote_control import UserRemoteControl
from elasticai.usbprotocol.helper_utils import get_env5_port

from serial import Serial

from time import sleep

remote: UserRemoteControl

def init():
    global remote
    env5_serial = Serial(port=get_env5_port())
    print(env5_serial)
    remote = UserRemoteControl(device=env5_serial)

def experiement():
    global remote
    remote.mcu_leds(True, True, True)

    with open("fpga.bit","rb") as bit_file:
        fpga_config = bit_file.read()
        remote.send_data_to_flash(0, fpga_config)
    remote.fpga_power_on(True)

    remote.mcu_leds(False, False, False)

if __name__=="__main__":
    init()
    experiement()
