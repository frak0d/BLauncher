import os
import sys
import time

import configparser

from os import path, system as cmd
from subprocess import check_output as cmd2
from toastify import notify
from threading import Thread

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

import gui_main

settings = configparser.ConfigParser()
ThemeInfo = configparser.ConfigParser()

cur_thm = 'Lavender'

if path.isfile('settings.ini'):
	settings.read('settings.ini')
	cur_thm = str(settings['EXTRAS']['CURRENT_THEME'])


#--------------------THEMING-----------------------#

ThemeFolder = './themes/'
ThemeList = []
AuthorName = 'Unknown'

def RefreshThemeList():
	ThemeList.clear()
	# Scanning For .blt Files
	if os.path.exists(ThemeFolder):
		with os.scandir(ThemeFolder) as DirList:
			for inputt in DirList:
				if inputt.is_file() and inputt.name.endswith('.blt'):
					ThemeList.append(inputt.name[:-4])

RefreshThemeList()

def setTheme2(app, tname):
	global ThemeInfo
	ThemeFileName = ThemeFolder + tname + '.blt'

	if os.path.isfile(ThemeFileName):
		print('Setting Theme to '+ tname)
		ThemeInfo.read(ThemeFileName)
	else:
		ThemeInfo.read_string(
'''
[THEME]

AuthorName = Mr. Kat
themename = Fusion
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
		print('Theme Not Found, Setting Default Theme!')

	THAMES = ThemeInfo['THEME']
	ThemeName = THAMES['ThemeName']

	global AuthorName
	AuthorName = str(THAMES['AuthorName'])
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

	# Creating Dark Palette
	myPalette = QPalette()
	myPalette.setColor(QPalette.Window, QColor(int(BgColor[0]), int(BgColor[1]), int(BgColor[2])))
	myPalette.setColor(QPalette.WindowText, QColor(int(TextColor[0]), int(TextColor[1]), int(TextColor[2])))
	myPalette.setColor(QPalette.Base, QColor(int(BaseColor[0]), int(BaseColor[1]), int(BaseColor[2])))					# Background Color
	myPalette.setColor(QPalette.Text, QColor(int(EditableTextColor[0]), int(EditableTextColor[1]), int(EditableTextColor[2])))
	myPalette.setColor(QPalette.Button, QColor(int(ButtonColor[0]), int(ButtonColor[1]), int(ButtonColor[2])))			# Button Color
	myPalette.setColor(QPalette.ButtonText, QColor(int(ButtonTextColor[0]), int(ButtonTextColor[1]), int(ButtonTextColor[2])))
	myPalette.setColor(QPalette.Link, QColor(int(LinkColor[0]), int(LinkColor[1]), int(LinkColor[2])))
	myPalette.setColor(QPalette.Highlight, QColor(int(SliderColor[0]), int(SliderColor[1]), int(SliderColor[2])))			# Slider Top Color
	
	app.setStyle(QStyleFactory.create(ThemeName))
	app.setPalette(myPalette)
	app.setStyleSheet("QToolTip {color: rgb(%d, %d, %d); background-color: rgb(%d, %d, %d); border: 1px solid grey;}" % (int(ToolTipTextColor[0]), int(ToolTipTextColor[1]), int(ToolTipTextColor[2]),
																														 int(ToolTipBaseColor[0]), int(ToolTipBaseColor[1]), int(ToolTipBaseColor[2])))

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
	print('Toast !')
	notify( AppName='BLauncher v1.19',
			TitleText='Potential Crash Warning !',
			BodyText='It is Recomended to Save any Unsaved Progress within 30 Seconds.',
			ImagePath='./assets/warn.png')

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
		if self.notif_agree.isChecked() :
			warning(self.notif_duration.value())
		time.sleep(30)
		print('killing...!')


class MainWindow(QMainWindow, gui_main.Ui_window):
	def __init__(self):
		super(MainWindow, self).__init__()
		self.setupUi(self)							# Setting MainWindow
		
		self.spinbox1.valueChanged[float].connect(self.update_slider1)
		self.slider1.valueChanged[int].connect(self.update_spinbox1)
		self.spinbox2.valueChanged[float].connect(self.update_slider2)
		self.slider2.valueChanged[int].connect(self.update_spinbox2)

		self.startb.clicked.connect(lambda: self.startf())
		#self.stopb.clicked.connect(lambda: self.stopf())
		self.optionb.clicked.connect(lambda: self.resizeWindow())
		
		self.fix1b.clicked.connect(lambda: fix1f())
		self.fix2b.clicked.connect(lambda: fix2f())

		self.notif_agree.stateChanged.connect(lambda: self.savef())
		self.notif_duration.valueChanged.connect(lambda: self.savef())

		self.auth_name.setText(AuthorName)
		self.comboBox.addItems(ThemeList)
		self.comboBox.activated[str].connect(self.setTheme)

		self.DISCORD.clicked.connect(lambda: cmd('start https://discord.gg/5pkSfFF'))
		self.YOUTUBE.clicked.connect(lambda: cmd('start https://youtube.com/frakod?sub_confirmation=1'))

		if path.isfile('settings.ini'):					# Load last used values if exist
			s1_val = int(settings['SLIDERS']['S1'])			# Needed to do this due to some unknown bug,
			s2_val = int(settings['SLIDERS']['S2'])			# else i could have put the values directly.
			nf_ag = eval(settings['EXTRAS']['NOTIF_AGREE'])
			nf_dur = int(settings['EXTRAS']['NOTIF_DURATION'])
			
			self.slider1.setValue(s1_val)
			self.slider2.setValue(s2_val)
			self.notif_agree.setChecked(nf_ag)
			self.notif_duration.setValue(nf_dur)
		
		self.comboBox.setCurrentText(cur_thm)
		self.show()

	def closeEvent(self, event):						# Will also stop the killer
		self.stopf()
		#event.accept()

	def setTheme(self, tname):
		self.comboBox.clear()
		RefreshThemeList()
		self.comboBox.addItems(ThemeList)
		setTheme2(QApplication.instance(), tname)
		self.auth_name.setText(AuthorName)
		self.savef()

	def resizeWindow(self):
		WinPosX = self.geometry().x()
		WinPosY = self.geometry().y()
		WinWidth = self.width()
		WinHeight = self.height()

		if WinWidth == 460:
			TargetWidth = 750
			self.optionb.setText('Options  <<')
		else:
			TargetWidth = 460
			self.optionb.setText('Options  >>')

		self.animation = QPropertyAnimation(self, b'geometry')
		self.animation.setDuration(250)
		self.animation.setEndValue(QRect(WinPosX, WinPosY, TargetWidth, WinHeight))
		self.animation.start()

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
		settings['EXTRAS'] = {'NOTIF_AGREE': self.notif_agree.isChecked(),
							  'NOTIF_DURATION': self.notif_duration.value(),
							  'CURRENT_THEME': self.comboBox.currentText()}

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
	setTheme2(app, cur_thm)
	window = MainWindow()
	sys.exit(app.exec_())		 # Starting Gui Loop
