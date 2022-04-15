#include <tuple>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <sstream>
#include <iostream>
#include <filesystem>

#include "sleep.cpp"
#include "colors.cpp"
#include "libs/nini.hpp"

#include <ui_main.h>

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

using std::printf;
#define elif else if
using str = std::string;
using namespace std::literals;
namespace fs = std::filesystem;

bool KillerRunning = false;

void print(const auto& ... args)
{
    (std::cout << ... << args) << std::flush;
}
void println(const auto& ... args)
{
    (std::cout << ... << args) << std::endl;
}

template <typename T>
T str_to(const str& string)
{
    T temp;
    std::stringstream ss;
    ss << string;
    ss >> temp;
    return temp;
}

template <>
QColor str_to(const str& string)
{
    uint R,G,B;
    std::sscanf(string.c_str(), "(%u,%u,%u)", &R, &G, &B);
    return QColor(R,G,B);
}

void set_app_theme(QApplication& app, Ini::Section& theme)
{
    app.setStyle(QStyleFactory::create(theme["ThemeName"].c_str()));

    auto myPalette = QPalette();  // Create Dark Palette
    myPalette.setColor(QPalette::Window,     str_to<QColor>(theme["BgColor"]));
    myPalette.setColor(QPalette::WindowText, str_to<QColor>(theme["TextColor"]));
    myPalette.setColor(QPalette::Base,       str_to<QColor>(theme["BaseColor"]));
    myPalette.setColor(QPalette::Text,       str_to<QColor>(theme["EditableTextColor"]));
    myPalette.setColor(QPalette::Button,     str_to<QColor>(theme["ButtonColor"]));
    myPalette.setColor(QPalette::ButtonText, str_to<QColor>(theme["ButtonTextColor"]));
    myPalette.setColor(QPalette::Link,       str_to<QColor>(theme["LinkColor"]));
    myPalette.setColor(QPalette::Highlight,  str_to<QColor>(theme["SliderColor"]));
    app.setPalette(myPalette);
    
    char stylesheet[1024]  =  "";
    auto ToolTipBaseColor  =  str_to<QColor>(theme["ToolTipBaseColor"]);
    auto ToolTipTextColor  =  str_to<QColor>(theme["ToolTipTextColor"]);

    std::snprintf(stylesheet, sizeof(stylesheet), "QToolTip {color: rgb(%d, %d, %d); background-color: rgb(%d, %d, %d); border: 1px solid grey;}",
        ToolTipTextColor.red(), ToolTipTextColor.green(), ToolTipTextColor.blue(), ToolTipTextColor.red(), ToolTipTextColor.green(), ToolTipTextColor.blue());

    app.setStyleSheet(stylesheet);
}

bool cmd(const str& cmd)
{
	QProcess sp;
	sp.start(cmd.c_str(), QStringList());

	if (sp.waitForFinished())
		if (sp.exitStatus() == QProcess::NormalExit)
			return true;
	
	return false;
}

str cmd2(const str& cmd)
{
	QProcess sp;
	sp.start(cmd.c_str(), QStringList());
	
	if (sp.waitForFinished())
		return sp.readAll().toStdString();
	else
    	throw sp.errorString().toStdString();
}

void haxx_on()
{
    cmd(R"FucK(Reg.exe add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\ClipSVC\Parameters" /v "ServiceDll" /t REG_EXPAND_SZ /d "%%SystemRoot%%\System32\ClipSBC.dll" /f)FucK");
    cmd(R"FucK(net stop "ClipSVC")FucK");
}

void haxx_off()
{
    cmd(R"FucK(Reg.exe add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\ClipSVC\Parameters" /v "ServiceDll" /t REG_EXPAND_SZ /d "%%SystemRoot%%\System32\ClipSVC.dll" /f)FucK");
    cmd(R"FucK(net start "ClipSVC")FucK");
}

int status()
{
    str s = cmd2(R"FucK(powershell -Command "Get-WindowsErrorReporting")FucK");
    
    if   (s == "Enabled\r\n" ) return 1;
    elif (s == "Disabled\r\n") return 0;
    else return 6;
}

void warning(int time)
{
    printf("Toast !\n");
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
        cmd(R"FucK(powershell -Command "Disable-WindowsErrorReporting")FucK");
        
        status() == 0 ? println("Success")
                      : println("Failed");
    }
    elif (status() == 0)
    {
        print("Disabling Crash Fix... ");
        cmd(R"FucK(powershell -Command "Enable-WindowsErrorReporting")FucK");
        
        status() == 1 ? println("Success")
                      : println("Failed");
    }
    elif (status() == 6)
    {
        println("SOMETHING WENT WRONG...");
    }
    fflush(stdout);
}

void fix2f()
{
    println("Applying Store Fix....");
    try {
        cmd2(R"FucK(reg import "./assets/Fix_SVC.reg")FucK");
        println("PLEASE RESTART YOUR PC FOR CHANGES TO TAKE EFFECT !"_bldgrn);
    }
    catch (...) {
        println("TRY RUNNING BLAUNCHER AS ADMINISTRATOR !"_bldred);
    }
    fflush(stdout);
}

void tamer(uint tame1, uint tame2)
{
        KillerRunning = true;
        sleep_for(tame1, "s");

        while (true)
        {
            try {
                cmd2("taskkill /f /im ClipSVC.exe");
                cmd2("taskkill /f /im RuntimeBroker.exe");
                print("DEATH NOTE ISSUED SUCCESSFULLY !\n");
            }
            catch (...) {
                print("\nOOPS SOMETHING WENT WRONG...\n"_red);
                print("TRY RUNNING BLAUNCHER AS ADMINISTRATOR !\n"_bldred);
            }

            sleep_for(tame2-30, "s");
            //if (self.notif_agree.isChecked())
            //    warning(self.notif_duration.value());
            sleep_for(30, "s");
        }
}

int main(int argc, char* argv[])
{
        QApplication app(argc, argv);
        auto exe_path = QCoreApplication::applicationDirPath().toStdString();
        std::cout << "app path = " << exe_path << std::endl;
        Ui::window ui;
        QWidget win;
        ui.setupUi(&win);

        auto savef = [&]()
        {
            Ini::File cfg(exe_path+"/settings.ini");

            cfg["SLIDERS"]["S1"]            = std::to_string( ui.slider1        -> value()     );
            cfg["SLIDERS"]["S2"]            = std::to_string( ui.slider2        -> value()     );
            cfg["EXTRAS"]["NOTIF_AGREE"]    = std::to_string( ui.notif_agree    -> isChecked() );
            cfg["EXTRAS"]["NOTIF_DURATION"] = std::to_string( ui.notif_duration -> value()     );
            cfg["EXTRAS"]["CURRENT_THEME"]  = ui.comboBox -> currentText().toStdString();
        };

        auto startf = [&]()
        {
            if (KillerRunning)
            {
                print("\nKiller is Already Active !"_cyn);
            }
            else
            {
                print("\nInitiating Startup....\n"_grn);

                uint tame1 = ui.slider1->value() * 1;
                uint tame2 = ui.slider2->value() * 60;

                try {
                    haxx_on();
                    cmd("explorer.exe shell:AppsFolder/Microsoft.MinecraftUWP_8wekyb3d8bbwe!App");
                    auto killer = std::thread(tamer, tame1, tame2);
                    killer.detach();
                }
                catch (...) {
                    println("OOPS SOMETHING WENT WRONG..."_red);
                    println("TRY RUNNING BLAUNCHER AS ADMINISTRATOR !"_bldred);
                }
            }
        };

        auto stopf = [&]()
        {
            if (KillerRunning)
            {
                print("\nStopping Killer....\n");
                try {
                    haxx_off();
                    println("Killer Stopped !"_cyn);
                    println("EXITING PROGRAM...."_bldcyn);
                    sleep_for(0.2, "s");
                    std::exit(1);
                }
                catch (...) {
                    println("OOPS SOMETHING WENT WRONG..."_red);
                    println("EXITING PROGRAM...."_bldred);
                    sleep_for(2.0, "s");
                    std::exit(0);
                }
            }
            else
            {
                print("\nEXITING PROGRAM....\n"_bldcyn);
                sleep_for(0.2, "s");
                std::exit(1);
            }
        };

        auto expandf = [&]()
        {
            int TargetWidth;

            if (win.width() == win.minimumWidth())
            {
                TargetWidth = win.maximumWidth();
                ui.optionb->setText("Options  <<");
            }
            else
            {
                TargetWidth = win.minimumWidth();
                ui.optionb->setText("Options  >>");
          	}
            
            QPropertyAnimation animation(&win, "geometry");
            animation.setDuration(800);
            //animation.setStartValue(QRect(win.x(), win.y(), win.width(), win.height()));
            animation.setEndValue(QRect(win.x(), win.y(), TargetWidth, win.height()));
            animation.setEasingCurve(QEasingCurve::OutCubic);
            animation.start();
        };

        QObject::connect(ui.fix1b, &QPushButton::clicked, fix1f);
        QObject::connect(ui.fix2b, &QPushButton::clicked, fix2f);

        QObject::connect(ui.startb,  &QPushButton::clicked, startf);
        QObject::connect(ui.optionb, &QPushButton::clicked, expandf);

        QApplication::connect(&app, &QApplication::aboutToQuit, stopf);

        QObject::connect(ui.notif_agree, &QCheckBox::stateChanged, [&](int state){savef();});
        QObject::connect(ui.comboBox, QOverload<int>::of(&QComboBox::activated), [&](int index){savef();});
        QObject::connect(ui.notif_duration, QOverload<int>::of(&QSpinBox::valueChanged), [&](int value){savef();});

        QObject::connect(ui.DISCORD, &QPushButton::clicked, [](){cmd("start https://discord.gg/5pkSfFF");});
        QObject::connect(ui.YOUTUBE, &QPushButton::clicked, [](){cmd("start https://youtube.com/frakod?sub_confirmation=1");});

        QObject::connect(ui.slider1, &QSlider::valueChanged, [&](int value)
        {
            ui.spinbox1->setValue(value); savef();
        });

        QObject::connect(ui.slider2, &QSlider::valueChanged, [&](int value)
        {
            ui.spinbox2->setValue(value); savef();
        });

        QObject::connect(ui.spinbox1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [&](double value)
        {
            ui.slider1->setValue(value); savef();
        });

        QObject::connect(ui.spinbox2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [&](double value)
        {
            ui.slider2->setValue(value); savef();
        });

        for (auto& entry : fs::directory_iterator(exe_path+"/themes"))
        {
            if (entry.is_regular_file() && entry.path().string().ends_with(".blt"))
                ui.comboBox->addItem(entry.path().stem().string().c_str());
        }

        QObject::connect(ui.comboBox, &QComboBox::currentTextChanged, [&](const QString& ThemeName)
        {
            Ini::File theme;
            theme.load(exe_path+"/themes/"+ThemeName.toStdString()+".blt");
            auto THEME = theme["THEME"];
            ui.auth_name->setText(THEME["AuthorName"].c_str());

            set_app_theme(app, THEME);
        });

        // Loading last used values
        if (fs::exists(exe_path+"/settings.ini"))
        {
            Ini::File cfg; cfg.load(exe_path+"/settings.ini");

            ui.slider1        -> setValue(str_to<int>(cfg["SLIDERS"]["S1"]));
            ui.slider2        -> setValue(str_to<int>(cfg["SLIDERS"]["S2"]));
            ui.notif_agree    -> setChecked(str_to<bool>(cfg["EXTRAS"]["NOTIF_AGREE"]));
            ui.notif_duration -> setValue(str_to<int>(cfg["EXTRAS"]["NOTIF_DURATION"]));
            ui.comboBox       -> setCurrentText(cfg["EXTRAS"]["CURRENT_THEME"].c_str());
        }

        win.show();
        return app.exec();
}