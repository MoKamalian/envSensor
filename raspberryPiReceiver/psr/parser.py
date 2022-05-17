"""
Author: amir kamalian
Date:   11-May-2022
Description:  This is the program used to parse the incoming data from the master node via to the raspberry pi
              via serial communication.  The data transmitted should follow a certain; data values should be
              separated with commas and the first value should indicate the sensors name.  The data values themselves
              will have a "key:value" format.

              i.e.

              key:value,key:value,key:value... and so on
"""


class ENVParser:

    sensor_name = "sensorName"

    def __init__(self):
        self.finalArray = {}

    def data(self, data_value: str):
        """
        Accepts the data value to later be parsed.  data_value follows format above.
        :param data_value: the string value to be parsed
        :return: nil
        """
        self.data_value = data_value

    def parse(self) -> dict:
        """
        This method should be called after object hs been instantiated.  Other methods depend on data
        already parsed...
        :return: Dictionary of the parsed data.  This should include the environmental data values if the
        data transmitted was sent in the proper format.
        """
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
        """
        Use this method to retrieve the data values using the environmental keys...
        Use the following keys assuming data sent was formatted properly:
            - sensorName
            - temperature
            - pressure
            - illuminance
            - humidity
            - uva
            - uvb
            - uvIndex
        :param key: environmental key from list above
        :param dictionary: the finalArray the method will look through to find the value
        :return: float data value
        """
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

    def getList(self, keys: list[str]) -> int | list[int]:
        """
        Same method as above in terms of purpose but can accept multiple keys and return multiple
        values in an array.
            - sensorName
            - temperature
            - pressure
            - illuminance
            - humidity
            - uva
            - uvb
            - uvIndex
        :param keys: list of keys to search for use the valid keys from above
        :return: array of values quarried for keys list... values are listed in order of key list
        """
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



