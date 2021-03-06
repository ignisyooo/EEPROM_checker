# -*- coding: utf-8 -*-

from os import read, replace
import sys
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QDate, QTime, QDateTime, Qt
import serial
import time

class Ui_MainWindow(object):

    ser = serial.Serial(
        parity = serial.PARITY_NONE,
        stopbits = serial.STOPBITS_ONE,
        bytesize = serial.EIGHTBITS,
        timeout = 1
    )

    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1024, 905)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.group_connection = QtWidgets.QGroupBox(self.centralwidget)
        self.group_connection.setGeometry(QtCore.QRect(30, 50, 441, 191))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.group_connection.setFont(font)
        self.group_connection.setObjectName("group_connection")
        self.label = QtWidgets.QLabel(self.group_connection)
        self.label.setGeometry(QtCore.QRect(10, 40, 181, 31))
        self.label.setObjectName("label")
        self.port_com = QtWidgets.QComboBox(self.group_connection)
        self.port_com.setGeometry(QtCore.QRect(190, 40, 111, 31))
        self.port_com.setObjectName("port_com")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.port_com.addItem("")
        self.connect_button = QtWidgets.QPushButton(self.group_connection)
        self.connect_button.setGeometry(QtCore.QRect(20, 120, 121, 41))
        self.connect_button.setObjectName("connect_button")
        self.status_connect = QtWidgets.QLabel(self.group_connection)
        self.status_connect.setGeometry(QtCore.QRect(280, 120, 131, 41))
        self.status_connect.setObjectName("status_connect")
        self.label_4 = QtWidgets.QLabel(self.group_connection)
        self.label_4.setGeometry(QtCore.QRect(200, 120, 71, 41))
        self.label_4.setObjectName("label_4")
        self.group_parameters = QtWidgets.QGroupBox(self.centralwidget)
        self.group_parameters.setGeometry(QtCore.QRect(30, 260, 441, 241))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.group_parameters.setFont(font)
        self.group_parameters.setObjectName("group_parameters")
        self.label_3 = QtWidgets.QLabel(self.group_parameters)
        self.label_3.setGeometry(QtCore.QRect(10, 40, 181, 31))
        self.label_3.setObjectName("label_3")
        self.label_5 = QtWidgets.QLabel(self.group_parameters)
        self.label_5.setGeometry(QtCore.QRect(10, 80, 181, 31))
        self.label_5.setObjectName("label_5")
        self.label_6 = QtWidgets.QLabel(self.group_parameters)
        self.label_6.setGeometry(QtCore.QRect(10, 120, 181, 31))
        self.label_6.setObjectName("label_6")
        self.memory_size = QtWidgets.QLineEdit(self.group_parameters)
        self.memory_size.setGeometry(QtCore.QRect(190, 40, 111, 31))
        self.memory_size.setText("")
        self.memory_size.setObjectName("memory_size")
        self.page_size = QtWidgets.QLineEdit(self.group_parameters)
        self.page_size.setGeometry(QtCore.QRect(190, 80, 111, 31))
        self.page_size.setText("")
        self.page_size.setObjectName("page_size")
        self.i2c_addr = QtWidgets.QLineEdit(self.group_parameters)
        self.i2c_addr.setGeometry(QtCore.QRect(190, 120, 111, 31))
        self.i2c_addr.setText("")
        self.i2c_addr.setObjectName("i2c_addr")
        self.send_button = QtWidgets.QPushButton(self.group_parameters)
        self.send_button.setGeometry(QtCore.QRect(20, 180, 171, 41))
        self.send_button.setObjectName("send_button")
        self.label_8 = QtWidgets.QLabel(self.group_parameters)
        self.label_8.setGeometry(QtCore.QRect(200, 180, 71, 41))
        self.label_8.setObjectName("label_8")
        self.status_send = QtWidgets.QLabel(self.group_parameters)
        self.status_send.setGeometry(QtCore.QRect(280, 180, 131, 41))
        self.status_send.setObjectName("status_send")
        self.group_log = QtWidgets.QGroupBox(self.centralwidget)
        self.group_log.setGeometry(QtCore.QRect(520, 50, 491, 561))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.group_log.setFont(font)
        self.group_log.setObjectName("group_log")
        self.log_window = QtWidgets.QTextEdit(self.group_log)
        self.log_window.setGeometry(QtCore.QRect(30, 40, 431, 441))
        self.log_window.setObjectName("log_window")
        font = QtGui.QFont()
        font.setFamily("Calibri")
        font.setPointSize(9)
        self.log_window.setFont(font)
        self.clear_logs = QtWidgets.QPushButton(self.group_log)
        self.clear_logs.setGeometry(QtCore.QRect(190, 500, 121, 41))
        self.clear_logs.setObjectName("clear_logs")
        self.save_logs = QtWidgets.QPushButton(self.group_log)
        self.save_logs.setGeometry(QtCore.QRect(40, 500, 121, 41))
        self.save_logs.setObjectName("save_logs")
        self.exit_button = QtWidgets.QPushButton(self.group_log)
        self.exit_button.setGeometry(QtCore.QRect(340, 500, 111, 41))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.exit_button.setFont(font)
        self.exit_button.setObjectName("exit_button")
        self.group_single = QtWidgets.QGroupBox(self.centralwidget)
        self.group_single.setGeometry(QtCore.QRect(30, 530, 441, 141))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.group_single.setFont(font)
        self.group_single.setObjectName("group_single")
        self.label_7 = QtWidgets.QLabel(self.group_single)
        self.label_7.setGeometry(QtCore.QRect(10, 40, 181, 31))
        self.label_7.setObjectName("label_7")
        self.test_pattern = QtWidgets.QLineEdit(self.group_single)
        self.test_pattern.setGeometry(QtCore.QRect(190, 40, 111, 31))
        self.test_pattern.setText("")
        self.test_pattern.setObjectName("test_pattern")
        self.start_single = QtWidgets.QPushButton(self.group_single)
        self.start_single.setGeometry(QtCore.QRect(310, 30, 121, 51))
        self.start_single.setObjectName("start_single")
        self.label_2 = QtWidgets.QLabel(self.group_single)
        self.label_2.setGeometry(QtCore.QRect(10, 110, 421, 16))
        font = QtGui.QFont()
        font.setFamily("Calibri")
        font.setPointSize(9)
        font.setItalic(True)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.group_mats = QtWidgets.QGroupBox(self.centralwidget)
        self.group_mats.setGeometry(QtCore.QRect(550, 640, 441, 191))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.group_mats.setFont(font)
        self.group_mats.setObjectName("group_mats")
        self.start_mats = QtWidgets.QPushButton(self.group_mats)
        self.start_mats.setGeometry(QtCore.QRect(310, 30, 121, 51))
        self.start_mats.setObjectName("start_mats")
        self.label_10 = QtWidgets.QLabel(self.group_mats)
        self.label_10.setGeometry(QtCore.QRect(10, 90, 421, 91))
        font = QtGui.QFont()
        font.setFamily("Calibri")
        font.setPointSize(9)
        font.setItalic(True)
        self.label_10.setFont(font)
        self.label_10.setWordWrap(True)
        self.label_10.setObjectName("label_10")
        self.label_12 = QtWidgets.QLabel(self.group_mats)
        self.label_12.setGeometry(QtCore.QRect(10, 50, 281, 41))
        font = QtGui.QFont()
        font.setFamily("Calibri")
        font.setPointSize(9)
        font.setItalic(True)
        self.label_12.setFont(font)
        self.label_12.setWordWrap(True)
        self.label_12.setObjectName("label_12")
        self.group_short = QtWidgets.QGroupBox(self.centralwidget)
        self.group_short.setGeometry(QtCore.QRect(30, 710, 441, 121))
        font = QtGui.QFont()
        font.setPointSize(11)
        self.group_short.setFont(font)
        self.group_short.setObjectName("group_short")
        self.start_short = QtWidgets.QPushButton(self.group_short)
        self.start_short.setGeometry(QtCore.QRect(310, 30, 121, 51))
        self.start_short.setObjectName("start_short")
        self.label_11 = QtWidgets.QLabel(self.group_short)
        self.label_11.setGeometry(QtCore.QRect(10, 40, 281, 81))
        font = QtGui.QFont()
        font.setFamily("Calibri")
        font.setPointSize(9)
        font.setItalic(True)
        self.label_11.setFont(font)
        self.label_11.setWordWrap(True)
        self.label_11.setObjectName("label_11")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1107, 26))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

        self.connect_button.clicked.connect(lambda: self.f_connect_button("Connected"))
        self.send_button.clicked.connect(lambda: self.f_send_param_button("Sent"))
        self.start_single.clicked.connect(self.single_test)
        self.start_mats.clicked.connect(self.mats_test)
        self.start_short.clicked.connect(self.short_test)
        self.save_logs.clicked.connect(self.f_save_button)
        self.clear_logs.clicked.connect(self.f_clear_button)
        self.exit_button.clicked.connect(lambda: sys.exit())

        self.insert_text("Select Port COM and press 'Connect' to continue", "")

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "EEPROM memory tester"))
        self.group_connection.setTitle(_translate("MainWindow", "Connection"))
        self.label.setText(_translate("MainWindow", "Port COM:"))
        self.port_com.setItemText(0, _translate("MainWindow", "COM1"))
        self.port_com.setItemText(1, _translate("MainWindow", "COM2"))
        self.port_com.setItemText(2, _translate("MainWindow", "COM3"))
        self.port_com.setItemText(3, _translate("MainWindow", "COM4"))
        self.port_com.setItemText(4, _translate("MainWindow", "COM5"))
        self.port_com.setItemText(5, _translate("MainWindow", "COM6"))
        self.port_com.setItemText(6, _translate("MainWindow", "COM7"))
        self.port_com.setItemText(7, _translate("MainWindow", "COM8"))
        self.port_com.setItemText(8, _translate("MainWindow", "COM9"))
        self.port_com.setItemText(9, _translate("MainWindow", "COM10"))
        self.port_com.setItemText(10, _translate("MainWindow", "COM11"))
        self.port_com.setItemText(11, _translate("MainWindow", "COM12"))
        self.connect_button.setText(_translate("MainWindow", "Connect"))
        self.status_connect.setText(_translate("MainWindow", "Not connected"))
        self.label_4.setText(_translate("MainWindow", "Status:"))
        self.group_parameters.setTitle(_translate("MainWindow", "Memory parameters"))
        self.label_3.setText(_translate("MainWindow", "Memory size [B]:"))
        self.label_5.setText(_translate("MainWindow", "Page size [b]:"))
        self.label_6.setText(_translate("MainWindow", "I2C Address [hex]:"))
        self.send_button.setText(_translate("MainWindow", "Send parameters"))
        self.label_8.setText(_translate("MainWindow", "Status:"))
        self.status_send.setText(_translate("MainWindow", "Not sent"))
        self.group_log.setTitle(_translate("MainWindow", "Logs"))
        self.clear_logs.setText(_translate("MainWindow", "Clear Logs"))
        self.save_logs.setText(_translate("MainWindow", "Save Logs"))
        self.exit_button.setText(_translate("MainWindow", "Exit"))
        self.group_single.setTitle(_translate("MainWindow", "Single test"))
        self.label_7.setText(_translate("MainWindow", "Test pattern [hex]:"))
        self.start_single.setText(_translate("MainWindow", "Start"))
        self.label_2.setText(_translate("MainWindow", "Writing and reading given value to address 0x00"))
        self.group_mats.setTitle(_translate("MainWindow", "Mats+ test"))
        self.start_mats.setText(_translate("MainWindow", "Start"))
        self.label_10.setText(_translate("MainWindow", "Step1: Write 0x00 to address 0 to n - 1\nStep2: From address 0 to n -1 : Read value (expected 0) - > write 0xFF\nStep3: From address n- 1 to 0: Read value (expected 0xFF) - >\n             write 0x00"))
        self.label_12.setText(_translate("MainWindow", "The test executes the 0xFF and 0x00 write sequences"))
        self.group_short.setTitle(_translate("MainWindow", "Short bit test"))
        self.start_short.setText(_translate("MainWindow", "Start"))
        self.label_11.setText(_translate("MainWindow", "The test write value 0x55 to all memory cells, and then check if there is any short circuit between bits\n"))


    def f_connect_button(self, text):
        if(self.conn_to_COM_port(115200)):
            # print info
            self.status_connect.setText(text)
            self.insert_text("Connected to Port ", self.port_com.currentText())
            self.log_window.insertPlainText("Select memory parameters and press 'Send parameters' to continue\n")

    def f_send_param_button(self, text):
        self.status_send.setText(text)

        # send config frame
        if len(self.page_size.text()) == 1:
            to_send = ('CONFIG_MA_' + self.i2c_addr.text() + '_MS_' + self.memory_size.text() + '_PS_0' + self.page_size.text() + '_END')
        else:
            to_send = ('CONFIG_MA_' + self.i2c_addr.text() + '_MS_' + self.memory_size.text() + '_PS_' + self.page_size.text() + '_END')
        b_to_send = bytes(to_send, 'utf-8')
        self.ser.write(b_to_send)
        # take info from Memory parameters
        # print(self.memory_size.text())
        # print(self.page_size.text())
        # print(self.i2c_addr.text())

        time.sleep(1)

        # print info
        self.read_incoming_data()

        time.sleep(1)

        # send test frame
        to_send = ('CONNECTION_xxxxxxxxxxxxxxxx_END')
        b_to_send = bytes(to_send, 'utf-8')
        self.ser.write(b_to_send)

        time.sleep(1)

        # print info
        self.read_incoming_data()
        # # print info
        # b_read_data = self.ser.read_until('\n\r')
        # read_data = b_read_data.decode("utf-8")
        # print(read_data)
        # self.insert_text(read_data, "")


    def f_save_button(self):
        # save text into log.txt
        log_file = open("EEPROM_memory_test_log.txt", "w")
        log_file.write(str(self.log_window.toPlainText()))
        log_file.close()
        self.insert_text("Logs have been saved in EEPROM_memory_test_log.txt file", "")

    def f_clear_button(self):
        self.log_window.clear()

    def single_test(self):
        self.insert_text("Single test started. Test pattern = ", self.test_pattern.text())

        # send single test frame
        to_send = ('SINGLE_TEST_' + self.test_pattern.text() + '_xxxxxxxxxx_END')
        b_to_send = bytes(to_send, 'utf-8')
        self.ser.write(b_to_send)

        time.sleep(1)

        # print info
        self.read_incoming_data()

    def mats_test(self):
        self.insert_text("Mats+ test started", "")

        # send mats test frame
        to_send = ('MATS_TEST_xxxxxxxxxxxxxxxxx_END')
        b_to_send = bytes(to_send, 'utf-8')
        self.ser.write(b_to_send)

        time.sleep(4)

        # print info
        self.read_incoming_data()

    def short_test(self):
        self.insert_text("Short bit test started", "")

        # send mats test frame
        to_send = ('SHORT_BIT_TEST_xxxxxxxxxxxx_END')
        b_to_send = bytes(to_send, 'utf-8')
        self.ser.write(b_to_send)

        time.sleep(1)
        
        # print info
        self.read_incoming_data()

    def insert_text(self, text1, text2):
        # insert current date into log window
        datetime = QDateTime.currentDateTime()
        self.log_window.insertPlainText("[")
        self.log_window.insertPlainText(datetime.toString())
        self.log_window.insertPlainText("] ")
        # insert text
        self.log_window.insertPlainText(text1)
        self.log_window.insertPlainText(text2)
        self.log_window.insertPlainText("\n")

    def conn_to_COM_port(self, baudrt):
        result = False
        try:
            self.ser.port = self.port_com.currentText()
            self.ser.baudrate = baudrt
            self.ser.open()
            result = True
        except:
            self.insert_text("This COM is not available, try another", "")
            result = False
        
        return result


    def read_incoming_data(self):
        b_read_data = self.ser.read_until('\n\r')
        print(b_read_data)
        read_data = b_read_data.decode("utf-8").replace('\n\r',' ')
        self.insert_text(read_data, "")

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())


    
