#include <string>
#include <windows.h>
#include <filesystem>

// Work In Progress //

selfDir = os.path.dirname(os.path.realpath(sys.argv[0]))
exePath = os.path.join(selfDir, 'lib\\notify.exe')

void  notify(BodyText, AppName="", AppPath="", TitleText="", ImagePath=""):
{
	if (AppPath == "")
		AppPath = sys.executable											# Get EXE Path

	if (AppName == "")
		AppName = AppPath[:AppPath.rfind('.')][AppPath.rfind('\\')+1:]		# Get EXE Name
	
	if (ImagePath != "")
		ImagePath = os.path.abspath(ImagePath)

	std::string cmd = R"JoKeR("{exePath}" "{AppName}" "{AppPath}" "{TitleText}" "{BodyText}" "{ImagePath}")JoKeR"; //.replace('\\','/')
	std::printf(cmd.c_str());
	std::system(cmd.c_str());
}
