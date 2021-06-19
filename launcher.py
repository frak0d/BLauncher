import os
import sys
import time

import configparser

from os import path, system as cmd
from subprocess import check_output as cmd2
from threading import Thread

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

import gui_main
import gui_extra


settings = configparser.ConfigParser()
ThemeInfo = configparser.ConfigParser()

if path.isfile('settings.ini'):
	settings.read('settings.ini')

#--------------------THEMING-----------------------#

if not path.isfile('theme.ini'):
	with open('theme.ini', 'w') as file :
		file.write(
'''[THEME]

# Vista/Windows/Fusion
themename = Fusion

# ALL VALUES ARE RGB :-
BgColor = (40,40,50)
BaseColor = (25,25,25)
ButtonColor = (50,50,200)
ButtonTextColor = (255,255,255)
SliderColor = (42,200,220)
LinkColor = (42,130,218)
TextColor = (255,255,255)
EditableTextColor = (255,255,255)
ToolTipBaseColor = (20,20,20)
ToolTipTextColor = (255,255,255)
''')

ThemeInfo.read('theme.ini')
THAMES = ThemeInfo['THEME']
ThemeName = THAMES['ThemeName']

BgColor = eval(THAMES['BgColor'])
BaseColor = eval(THAMES['BaseColor'])
ButtonColor = eval(THAMES['ButtonColor'])
ButtonTextColor = eval(THAMES['ButtonTextColor'])
SliderColor = eval(THAMES['SliderColor'])
LinkColor = eval(THAMES['LinkColor'])
TextColor = eval(THAMES['TextColor'])
EditableTextColor = eval(THAMES['EditableTextColor'])
ToolTipBaseColor = eval(THAMES['ToolTipBaseColor'])
ToolTipTextColor = eval(THAMES['ToolTipTextColor'])

#-------------------------------------------------------#

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


def notify(tme):
	print('Toast !')
	cmd('notify.exe "%s" "%s" "%s" "%s" "%s"' % (
		"Blauncher v1.18",														#AppName
		sys.executable,															#AppPath
		"Potential Crash Warning !",											#TitleText
		"It is Recomended to Save any Unsaved Progress within 30 Seconds.",		#BodyText
		os.path.abspath("./assets/warn.png")))									#ImagePath


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


def tamer(self, tame1, tame2):
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
		if self.extraui.notif_agree.isChecked() :
			notify(self.extraui.notif_duration.value())
		time.sleep(30)
		print('killing...!')


class ExtraWindow(QMainWindow, gui_extra.Ui_extra_window):
	def __init__(self):
		super(ExtraWindow, self).__init__()
		self.setupUi(self)							# Setting Extras Window

		
class MainWindow(QMainWindow, gui_main.Ui_window):
	def __init__(self):
		super(MainWindow, self).__init__()
		self.setupUi(self)							# Setting MainWindow
		
		self.extraui = ExtraWindow()				# Setting Extras Window
		
		self.spinbox1.valueChanged[float].connect(self.update_slider1)
		self.slider1.valueChanged[int].connect(self.update_spinbox1)
		self.spinbox2.valueChanged[float].connect(self.update_slider2)
		self.slider2.valueChanged[int].connect(self.update_spinbox2)

		self.startb.clicked.connect(lambda: self.startf())
		self.stopb.clicked.connect(lambda: self.stopf())
		self.optionb.clicked.connect(lambda: self.extraui.show())
		
		self.extraui.fix1b.clicked.connect(lambda: fix1f())
		self.extraui.fix2b.clicked.connect(lambda: fix2f())

		self.extraui.notif_agree.stateChanged.connect(lambda: self.savef())
		self.extraui.notif_duration.valueChanged.connect(lambda: self.savef())

		self.extraui.DISCORD.clicked.connect(lambda: cmd('start https://discord.gg/5pkSfFF'))
		self.extraui.YOUTUBE.clicked.connect(lambda: cmd('start https://youtube.com/TechArchives45?sub_confirmation=1'))

		if path.isfile('settings.ini'):					# Load last used values if exist

			s1_val = int(settings['SLIDERS']['S1'])			# Needed to do this due to some unknown bug,
			s2_val = int(settings['SLIDERS']['S2'])			# else i could have put the values directly.
			nf_ag = eval(settings['EXTRAS']['NF_AG'])
			nf_val = int(settings['EXTRAS']['NF_DUR'])

			self.slider1.setValue(s1_val)
			self.slider2.setValue(s2_val)
			self.extraui.notif_agree.setChecked(nf_ag)
			self.extraui.notif_duration.setValue(nf_val)

		self.show()

	def closeEvent(self, event):						# Will also close the Extras window
		self.extraui.close()						# when MainWindow is Closed :)
		event.accept()

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

	# save current values
	def savef(self):
		settings['SLIDERS'] = {'S1': self.slider1.value(), 'S2': self.slider2.value()}
		settings['EXTRAS'] = {'NF_AG': self.extraui.notif_agree.isChecked(), 'NF_DUR': self.extraui.notif_duration.value()}

		#print(settings['EXTRAS']['NF_AG'], settings['EXTRAS']['NF_DUR'])
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
			tame2 = self.slider2.value() * 60
			try :
				#cmd('net stop "ClipSVC"')
				cmd2(StartCommand)
				cmd('explorer.exe shell:AppsFolder\Microsoft.MinecraftUWP_8wekyb3d8bbwe!App')
				self.t1 = Thread(target=tamer, name='Killer', args=(self, tame1, tame2), daemon=True)
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
				#cmd('net start "ClipSVC"')
				print('\nKiller Stopped !')
				print('\n\33[31mEXITING PROGRAM....')
				time.sleep(0.2)
				sys.exit(1)
			
			except Exception :						# Exception excludes SystemExit and KeyboardInterrupt
				print('\n\33[33mOOPS SOMETHING WENT WRONG...')
				print('\n\33[33mEXITING PROGRAM....')
				time.sleep(2)
				sys.exit(0)
		
		else :
			print('\n\33[31mEXITING PROGRAM....')
			time.sleep(0.2)
			sys.exit(1)

if __name__ == '__main__':

	app = QApplication([])									# Creating Main Window
	app.setStyle(QStyleFactory.create(ThemeName))			# Setting Theme

	# Creating Dark Palette
	darkPalette = QPalette()
	darkPalette.setColor(QPalette.Window, QColor(int(BgColor[0]), int(BgColor[1]), int(BgColor[2])))
	darkPalette.setColor(QPalette.WindowText, QColor(int(TextColor[0]), int(TextColor[1]), int(TextColor[2])))
	darkPalette.setColor(QPalette.Base, QColor(int(BaseColor[0]), int(BaseColor[1]), int(BaseColor[2])))					# Background Color
	darkPalette.setColor(QPalette.Text, QColor(int(EditableTextColor[0]), int(EditableTextColor[1]), int(EditableTextColor[2])))
	darkPalette.setColor(QPalette.Button, QColor(int(ButtonColor[0]), int(ButtonColor[1]), int(ButtonColor[2])))			# Button Color
	darkPalette.setColor(QPalette.ButtonText, QColor(int(ButtonTextColor[0]), int(ButtonTextColor[1]), int(ButtonTextColor[2])))
	darkPalette.setColor(QPalette.Link, QColor(int(LinkColor[0]), int(LinkColor[1]), int(LinkColor[2])))
	darkPalette.setColor(QPalette.Highlight, QColor(int(SliderColor[0]), int(SliderColor[1]), int(SliderColor[2])))			# Slider Top Color
	
	app.setPalette(darkPalette)
	app.setStyleSheet("QToolTip {color: rgb(%d, %d, %d); background-color: rgb(%d, %d, %d); border: 1px solid grey;}" % (int(ToolTipTextColor[0]), int(ToolTipTextColor[1]), int(ToolTipTextColor[2]),
															     int(ToolTipBaseColor[0]), int(ToolTipBaseColor[1]), int(ToolTipBaseColor[2])))
	window = MainWindow()
	#window.show()
	sys.exit(app.exec_())		 # Starting Gui Loop
