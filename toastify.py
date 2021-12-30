import os
import sys
from subprocess import Popen

selfDir = os.path.dirname(os.path.realpath(sys.argv[0]))
exePath = os.path.join(selfDir, 'lib\\notify.exe')

def notify(BodyText, AppName='', AppPath='', TitleText='', ImagePath=''):

	if AppPath == '' :
		AppPath = sys.executable											# Get EXE Path

	if AppName == '' :
		AppName = AppPath[:AppPath.rfind('.')][AppPath.rfind('\\')+1:]		# Get EXE Name
	
	if ImagePath != '' :
		ImagePath = os.path.abspath(ImagePath)

	cmd = f'"{exePath}" "{AppName}" "{AppPath}" "{TitleText}" "{BodyText}" "{ImagePath}"'.replace('\\','/')
	print(cmd)
	Popen(cmd, shell=True)

notify("hello")
