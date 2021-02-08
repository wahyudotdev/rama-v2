import os
import json


class LoadConfig(object):
    def __init__(self):
        self.__location__ = os.path.realpath(
            os.path.join(os.getcwd(), os.path.dirname(__file__)))

        f = open(os.path.join(self.__location__, 'config.json'), 'r')
        config = json.loads(f.read())
        self.mqtt_host = config['mqtt_host']
        self.camera_host = config['camera_host']
        self.speed = config['speed']
        f.close()

    def saveSpeed(self, speed):
        f = open(os.path.join(self.__location__, 'config.json'))
        config = json.loads(f.read())
        f.close()
        f = open(os.path.join(self.__location__, 'config.json'), 'w+')
        config['speed'] = str(speed)
        json_string = json.dumps(config, indent=4, sort_keys=True,)
        f.write(json_string)
        f.close()