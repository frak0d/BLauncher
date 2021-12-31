#include <string>
#include <cstdlib>
#include <iostream>
#include <filesystem>

#include "gui_main.cpp"

typedef std::string str;

bool KillerRunning = false;
str StopCommand  = R"FucK(Reg.exe add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\ClipSVC\Parameters" /v "ServiceDll" /t REG_EXPAND_SZ /d "%%SystemRoot%%\System32\ClipSVC.dll" /f)FucK";
str StartCommand = R"FucK(Reg.exe add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\ClipSVC\Parameters" /v "ServiceDll" /t REG_EXPAND_SZ /d "%%SystemRoot%%\System32\ClipSBC.dll" /f)FucK";

void print(const auto& ... args)
{
	(std::cout << ... << args);
}
void print2(const auto& ... args)
{
	(std::cout << ... << args) << std::endl;
}

str cmd2()
{
  
}

int status()
{
  str s = cmd2(R"FucK(powershell -Command "Get-WindowsErrorReporting")FucK");
  
  if   (s == "Enabled\r\n" ) return 1;
  elif (s == "Disabled\r\n") return 0;
  elif return 6;
}

void warning(int tme)
{
  print2("Toast !");
  /*notify(AppName='BLauncher v1.19',
           TitleText='Potential Crash Warning !',
           BodyText='It is Recomended to Save any Unsaved Progress within 30 Seconds.',
           ImagePath='./assets/warn.png')*/
}

void fix1f()
{
  if (status() == 1)
  {
    print("Enabling Crash Fix... ");
    cmd2(R"FucK(powershell -Command "Disable-WindowsErrorReporting")FucK");
    
    status() == 0 ? print2("Success");
                  : print2("Failed");
  }
  elif (status() == 0)
  {
    print("Disabling Crash Fix... ");
    cmd2(R"FucK(powershell -Command "Enable-WindowsErrorReporting")FucK");
    
    status() == 1 ? print2("Success");
                  : print2("Failed");
  }
  elif (status() == 6)
    print2("SOMETHING WENT WRONG...");
}

void fix2f()
{
  print2("Applying Store Fix....");
  try {
    cmd2('reg import "./assets/Fix_SVC.reg"')
    print2('\e[32mPLEASE RESTART YOUR PC FOR CHANGES TO TAKE EFFECT !')
  }
  catch (...) print2('\e[36mTRY RUNNING BLAUNCHER AS ADMINISTRATOR !')
}

void tamer(uint tame1, uint tame2)
{
  KillerRunning = true;
  print2("Time 1 =", tame1, "seconds");
  print2("Time 2 =", tame2, "seconds");
  time::sleep(tame1);
  
  while (true)
  {
    try :
      #cmd2("taskkill /f /im ClipSVC.exe");
      cmd2("taskkill /f /im RuntimeBroker.exe");
      print2("KILLED !");
    except :
      print2("\nOOPS SOMETHING WENT WRONG...");
      print2("TRY RUNNING BLAUNCHER AS ADMINISTRATOR !");

    time::sleep(tame2 - 30);
    if (self.notif_agree.isChecked())
      warning(self.notif_duration.value());
    time::sleep(30);
    print2("killing...!");
  }
}

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  
  Qwidget MainWindow;
  Ui::window ui;
  ui.setupUi(MainWindow);
  
  MainWindow.show();
  return app.exec();
}
