"""
Author: amir kamalian
Date:   11-May-2022
Description:  This is the program used to parse the incoming data from the master node via to the raspberry pi
              via serial communication.  The data transmitted should follow a certain; data values should be
              separated with commas and the first value should indicate the sensors name.  The data values themselves
              will have a "key:value" format.
"""


class ENVParser:

    sensor_name = "sensorName"

    def __init__(self, data_value: str):
        self.data_value = data_value
        self.finalArray = {}

    """
    Parser method itself.  The method assumes that the data being 
    received is already properly formatted.  
    """

    def parse(self) -> dict:
        temp = self.data_value.split(",")
        if len(temp) < 1:
            print("[invalid data format:no comma splitter or data too short]")
            return {}
        if temp[0].split(":")[0] != "sensorName":
            print("[invalid data format:exit code 0]")
            return {}
        else:
            if len(self.data_value.split(":")) < 1:
                print("[invalid data format:no colon separator or data too short]")
                return {}
            else:
                for key_values in temp:
                    hold = key_values.split(":")
                    self.finalArray[hold[0]] = hold[1]

        return self.finalArray

    def get(self, key: str, dictionary: dict):
        if len(dictionary) == 0:
            print("[empty dictionary:values may not have been parsed yet]")
            return 0.0
        elif str in dictionary.keys():
            if str == self.sensor_name:
                if str in dictionary:
                    return dictionary[str]
                else:
                    print("[invalid key error:key not present or misspelled]")
                    return ""
            else:
                return float(dictionary[key])
        else:
            print("[invalid key error:key not present or misspelled]")
            return 0.0

    def getList(self, keys: list):
        val_lst = []
        if len(self.finalArray) == 0:
            print("[empty dictionary:values may not have been parsed yet]")
            return 0
        else:
            for key in keys:
                if key not in self.finalArray:
                    print("[invalid key error:key not present or misspelled]")
                    val_lst.append(0)
                else:
                    val_lst.append(self.finalArray[key])
        return val_lst



