import tkinter as tk
import threading
import time
import math
import serial
import PySimpleGUI as sg

ser=serial.Serial(
    port='COM3',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)
sg.theme('Topanga')
com_list = ['COM1', 'COM2', 'COM3', 'COM4', 'COM5', 'COM6', 'COM7', 'COM8', 'COM9', 'COM10', 'COM11', 'COM12']
layout = [
    [sg.Text('EEPROM memory tester', font='15')],
    [sg.Text('Memory parameters:')],
    [sg.Text('Memory Address', size =(12, 1)), sg.InputText()],
    [sg.Text('Memory Size', size =(12, 1)), sg.InputText()],
    [sg.Text('Page Size', size =(12, 1)), sg.InputText()],
    #[sg.Text('Select Your COM to connect:')],
    #[sg.Listbox(com_list, size=(20,4), enable_events=False, key='_LIST_')],
    [sg.Submit(), sg.Cancel()]
]

window = sg.Window('EEPROM memory test', layout)
event, values = window.read()
window.close()

print(event, values[0], values[1], values[2])
dict_keys = ["mem_addr", "mem_size", "page_size"]
tuples_list = ((dict_keys[i], values[i]) for i in range(len(dict_keys)))
mem_data = dict(tuples_list)
print(mem_data)

to_send =('CONFIG_MA_' + mem_data['mem_addr'] + '_MS_' + mem_data['mem_size'] + '_PS_' + mem_data['page_size'] + '_END')
print(to_send)
b_to_send = bytes(to_send, 'utf-8')

ser.write(b_to_send)

