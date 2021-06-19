from PyQt5 import QtWidgets, uic
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

from os import path, system as cmd
from subprocess import check_output as cmd2
from sys import exit as ender
from threading import Thread

from win10toast import ToastNotifier
import configparser
import time

toast = ToastNotifier()
settings = configparser.ConfigParser()

if path.isfile('settings.ini'):
	settings.read('settings.ini')

x = 0
cmd('mode 60,20')
print('\x1b[1;33m# NEVER BETRAY THE CONSOLE !')

StopCommand  = 'Reg.exe add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\ClipSVC\Parameters" /v "ServiceDll" /t REG_EXPAND_SZ /d "%%SystemRoot%%\System32\ClipSVC.dll" /f'
StartCommand = 'Reg.exe add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\ClipSVC\Parameters" /v "ServiceDll" /t REG_EXPAND_SZ /d "%%SystemRoot%%\System32\ClipSBC.dll" /f'


def status():
	s = cmd2('powershell -Command "Get-WindowsErrorReporting"')
	if s == b'Enabled\r\n' :
		return 1
	elif s == b'Disabled\r\n' :
		return 0
	else :
		return 6


def warning(tme):
	toast.show_toast("Potential Game Crash Warning",
			f"It is Recomended to Save any Unsaved Progress{tme}",
			icon_path="./assets/warn.ico",
			duration=5,threaded=True)


def fix1f():
	if status() == 1 :
		print('Enabling Crash Fix... ',end='')
		cmd2('powershell -Command "Disable-WindowsErrorReporting"')
		if status() == 0 :
			print('Success')
		else :
			print('Failed')

	elif status() == 0 :
		print('Disabling Crash Fix... ',end='')
		cmd2('powershell -Command "Enable-WindowsErrorReporting"')
		if status() == 1 :
			print('Success')
		else :
			print('Failed')

	elif status() == 6 :
		print('SOMETHING WENT WRONG...')


def fix2f():
	print('Applying Store Fix....')
	try :
		cmd2('reg import "./assets/Fix_SVC.reg"')
		print('\33[32mPLEASE RESTART YOUR PC FOR CHANGES TO TAKE EFFECT !')
	except :
		print('\33[36mTRY RUNNING BLAUNCHER AS ADMINISTRATOR !')


def tamer(tame1, tame2):
	global x
	x = 1
	print('Time 1 =', tame1, 'seconds')
	print('Time 2 =', tame2, 'seconds')
	time.sleep(tame1)
	while True :
		try :
			#cmd2("taskkill /f /im ClipSVC.exe")
			cmd2("taskkill /f /im RuntimeBroker.exe")
			print('KILLED !')
		except :
			print('\nOOPS SOMETHING WENT WRONG...')
			print('TRY RUNNING BLAUNCHER AS ADMINISTRATOR !')
		time.sleep(tame2 - 30)
		warning(' Within 30 Seconds.')
		time.sleep(30)
		print('killing...!')


class Ui(QtWidgets.QMainWindow):
	def __init__(self):
		super(Ui, self).__init__()
		uic.loadUi('msvcp_qt5.dll', self)					# Set .ui File

		self.spinbox1.valueChanged[float].connect(self.update_slider1)
		self.slider1.valueChanged[int].connect(self.update_spinbox1)
		self.spinbox2.valueChanged[float].connect(self.update_slider2)
		self.slider2.valueChanged[int].connect(self.update_spinbox2)

		self.startb.clicked.connect(lambda: self.startf())
		self.stopb.clicked.connect(lambda: self.stopf())

		self.fix1b.clicked.connect(lambda: fix1f())
		self.fix2b.clicked.connect(lambda: fix2f())

		if path.isfile('settings.ini'):						# Load last used values if exist
			self.slider1.setValue(int(settings['SLIDERS']['S1']))
			self.slider2.setValue(int(settings['SLIDERS']['S2']))

		self.show()

	def update_slider1(self, value):
		self.slider1.setValue(int(value))
		self.savef()

	def update_spinbox1(self, value):
		self.spinbox1.setValue(float(value))

	def update_slider2(self, value):
		self.slider2.setValue(int(value))
		self.savef()

	def update_spinbox2(self, value):
		self.spinbox2.setValue(float(value))

	def savef(self):								# save current slider values
		settings['SLIDERS'] = {'S1': self.slider1.value(), 'S2': self.slider2.value()}
		with open('settings.ini', 'w') as configfile :
			settings.write(configfile)
	
	def startf(self):
		if x == 1 :
			print('\n\33[33mKiller is Already Active !')
		else :
			print('\n\33[32mInitiating Startup....\n')
			global tame1
			tame1 = self.slider1.value()
			global tame2
			tame2 = (self.slider2.value()) * 60
			try :
				cmd2(StartCommand)
				cmd('explorer.exe shell:AppsFolder\Microsoft.MinecraftUWP_8wekyb3d8bbwe!App')
				self.t1 = Thread(target=tamer, name='Killer', args=(tame1, tame2), daemon=True)
				self.t1.start()
			except :
				print('OOPS SOMETHING WENT WRONG...')
				print('TRY RUNNING BLAUNCHER AS ADMINISTRATOR !')

	def stopf(self):
		global x
		if x == 1:
			print('\nStopping Killer....')
			try :
				cmd2(StopCommand)
				print('\nKiller Stopped !')
				print('\n\33[31mEXITING PROGRAM....')
				time.sleep(0.2)
				ender(1)
			
			except Exception :						# Exception excludes SystemExit and KeyboardInterrupt
				print('\n\33[33mOOPS SOMETHING WENT WRONG...')
				print('\n\33[33mEXITING PROGRAM....')
				time.sleep(2)
				ender(0)
		
		else :
			print('\n\33[31mEXITING PROGRAM....')
			time.sleep(0.2)
			ender(1)


if __name__ == '__main__':
	app = QtWidgets.QApplication([])						# Creating Main Window

	app.setStyle(QStyleFactory.create('Fusion'))					# Setting Theme

	# Creating Dark Palette
	darkPalette = QPalette()
	darkPalette.setColor(QPalette.Window, QColor(40, 40, 50))
	darkPalette.setColor(QPalette.WindowText, Qt.white)
	darkPalette.setColor(QPalette.Base, QColor(25, 25, 25))
	darkPalette.setColor(QPalette.AlternateBase, QColor(54, 54, 54))
	darkPalette.setColor(QPalette.ToolTipBase, Qt.white)
	darkPalette.setColor(QPalette.ToolTipText, Qt.white)
	darkPalette.setColor(QPalette.Text, Qt.white)
	darkPalette.setColor(QPalette.Button, QColor(50, 50, 200))			# Main Accent
	darkPalette.setColor(QPalette.ButtonText, Qt.white)
	darkPalette.setColor(QPalette.BrightText, Qt.red)
	darkPalette.setColor(QPalette.Link, QColor(42, 130, 218))
	darkPalette.setColor(QPalette.Highlight, QColor(42, 130, 218))			# Slider top
	darkPalette.setColor(QPalette.HighlightedText, Qt.black)

	app.setPalette(darkPalette)
	app.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid grey; }")

	window = Ui()
	app.exec_()									# Starting Gui Loop
