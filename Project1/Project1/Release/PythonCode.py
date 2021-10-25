import re
import string
from collections import Counter     #for counter function


def FrequencyList():
    grocery_dict = {}
    i = 0

    try:        
        my_file = open("CS210_Project_Three_Input_File.txt", "r")    #Opens original file
        content = my_file.read()                                     #Reads file
        content_list = content.split("\n")                           #Separates data into indexs and values
        for i in range(len(content_list)):                           #Populates dictionary until length of file fully read
            for index,value in enumerate(content_list):
                grocery_dict[index] = value                   

        print('\n')
        # using Counter() + items()
        grocery_dict = dict(Counter(content_list).items())           #Counts items in dictionary and consolidates multiples keys
        for key in grocery_dict:                                     #Prints list of all items sold with amount sold by key (product) and value (amount)
            print(key, ' ', grocery_dict[key])

    finally:
        my_file.close()                                              #Closes file


def FrequencyItem(item):
    grocery_dict = {}
    i = 0
    numberSold = 0

    try:        
        my_file = open("CS210_Project_Three_Input_File.txt", "r")    #Opens original file
        content = my_file.read()                                     #Reads file
        content_list = content.split("\n")                           #Separates data into indexs and values
        for i in range(len(content_list)):                           #Populates dictionary until length of file fully read
            for index,value in enumerate(content_list):
                grocery_dict[index] = value         
        
        print('\n')
        # using Counter() + items()
        grocery_dict = dict(Counter(content_list).items())           #Counts items in dictionary and consolidates multiples keys
        numberSold = grocery_dict.get(item, 0)

        return numberSold                                            #Returns searched value to C++ function

    finally:
        my_file.close()                                              #Closes file


def PrintReceipt():
    grocery_dict = {}

    try:        
        my_file = open("CS210_Project_Three_Input_File.txt", "r") #Opens original input file
        content = my_file.read()                                  #Reads file
        content_list = content.split("\n")                        #Separates data into indexs and values
        for i in range(len(content_list)):                        #Populates dictionary until length of file fully read
            for index,value in enumerate(content_list):
                grocery_dict[index] = value                   

        print('\n')
        grocery_dict = dict(Counter(content_list).items())        #Counts items in dictionary and consolidates multiples keys


    finally:
        my_file.close()                                           #Closes file when complete


    try:
        with open('frequency.dat', 'w') as freq:                  #Creates new file
            for key in grocery_dict:                              #Writes product (key) and amount (value)
                print(key, ' ', grocery_dict[key], file=freq)

    finally:
        freq.close()                                              #Closes file after writing
        print("Receipt Printed!")