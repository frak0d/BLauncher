#include <tuple>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <sstream>
#include <ostream>
#include <iostream>
#include <filesystem>
#include <string_view>

#include "cmd.cpp"
#include "nini.cpp"
#include "print.cpp"
#include "sleep.cpp"
#include "colors.cpp"
#include "str2color.cpp"

#include <ui_main.h>

#include <QtGui/QIcon>
#include <QtGui/QPalette>
#include <QtCore/QString>
#include <QtWidgets/QStyleFactory>
#include <QtCore/QPropertyAnimation>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSystemTrayIcon>

#define elif else if
using namespace std::literals;
namespace fs = std::filesystem;

bool KillerRunning = false;
QSystemTrayIcon tray_icon{};

void set_app_theme(QApplication& app, Ini::Section& theme)
{
    app.setStyle(QStyleFactory::create(theme["ThemeName"]));

    auto myPalette = QPalette();  // Create Dark Palette
    myPalette.setColor(QPalette::Window,     QString_to_Qcolor(theme["BgColor"]));
    myPalette.setColor(QPalette::WindowText, QString_to_Qcolor(theme["TextColor"]));
    myPalette.setColor(QPalette::Base,       QString_to_Qcolor(theme["BaseColor"]));
    myPalette.setColor(QPalette::Text,       QString_to_Qcolor(theme["EditableTextColor"]));
    myPalette.setColor(QPalette::Button,     QString_to_Qcolor(theme["ButtonColor"]));
    myPalette.setColor(QPalette::ButtonText, QString_to_Qcolor(theme["ButtonTextColor"]));
    myPalette.setColor(QPalette::Link,       QString_to_Qcolor(theme["LinkColor"]));
    myPalette.setColor(QPalette::Highlight,  QString_to_Qcolor(theme["SliderColor"]));
    app.setPalette(myPalette);
    
    char stylesheet[1024]  =  "";
    auto ToolTipBaseColor  =  QString_to_Qcolor(theme["ToolTipBaseColor"]);
    auto ToolTipTextColor  =  QString_to_Qcolor(theme["ToolTipTextColor"]);

    std::snprintf(stylesheet, sizeof(stylesheet), "QToolTip {color: rgb(%d, %d, %d); background-color: rgb(%d, %d, %d); border: 1px solid grey;}",
        ToolTipTextColor.red(), ToolTipTextColor.green(), ToolTipTextColor.blue(), ToolTipTextColor.red(), ToolTipTextColor.green(), ToolTipTextColor.blue());

    app.setStyleSheet(stylesheet);
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
    auto s = cmd2(R"FucK(powershell -Command "Get-WindowsErrorReporting")FucK");
    std::cout << s.toStdString() << std::endl;
    
    if   (s == "Enabled\r\n" ) return 1;
    elif (s == "Disabled\r\n") return 0;
    else return 6;
}

void warning(int time_msec)
{
    println("Sent Toast Notification!"_cyn);

    tray_icon.showMessage("BLauncher: Potential Crash Warning !",
                          "It is Recomended to Save any Unsaved Progress within 30 Seconds.",
                          QIcon("./assets/warn.png"), time_msec);
}

void crash_fix()
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

void store_fix()
{
    println("Applying Store Fix....");
    try {
        cmd2(R"FucK(reg import "./assets/Fix_SVC.reg")FucK");
        println("PLEASE RESTART YOUR PC FOR CHANGES TO TAKE EFFECT !"_bldgrn);
    }
    catch (...) {
        println("TRY RUNNING BLAUNCHER AS ADMINISTRATOR !"_bldred);
    }
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
        auto exe_path = QCoreApplication::applicationDirPath();

        tray_icon.setIcon(QIcon("assets/logo.png"));
        tray_icon.setToolTip("BLauncher is Running!");
        tray_icon.show();
        
        Ui::window ui;
        QWidget win;
        ui.setupUi(&win);

        auto savef = [&]()
        {
            Ini::File cfg(exe_path+"/settings.ini");

            cfg["SLIDERS"]["S1"]            = QString(std::to_string( ui.slider1        -> value()      ).c_str());
            cfg["SLIDERS"]["S2"]            = QString(std::to_string( ui.slider2        -> value()      ).c_str());
            cfg["EXTRAS"]["NOTIF_AGREE"]    = QString(std::to_string( ui.notif_agree    -> isChecked()  ).c_str());
            cfg["EXTRAS"]["NOTIF_DURATION"] = QString(std::to_string( ui.notif_duration -> value()      ).c_str());
            cfg["EXTRAS"]["CURRENT_THEME"]  =                       ( ui.comboBox       -> currentText())         ;
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
            animation.setDuration(1000);
            animation.setStartValue(QRect(win.x(), win.y(), win.width(), win.height()));
            animation.setEndValue(QRect(win.x(), win.y(), TargetWidth, win.height()));
            animation.setEasingCurve(QEasingCurve::OutCubic);
            animation.start();
        };

        QObject::connect(ui.fix1b, &QPushButton::clicked, crash_fix);
        QObject::connect(ui.fix2b, &QPushButton::clicked, store_fix);

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

        for (auto& entry : fs::directory_iterator(exe_path.toStdString()+"/themes"))
        {
            if (entry.is_regular_file() && entry.path().string().ends_with(".blt"))
                ui.comboBox->addItem(entry.path().stem().string().c_str());
        }

        QObject::connect(ui.comboBox, &QComboBox::currentTextChanged, [&](const QString& ThemeName)
        {
            Ini::File theme;
            theme.load(exe_path+"/themes/"+ThemeName+".blt");
            auto THEME = theme["THEME"];
            ui.auth_name->setText(THEME["AuthorName"]);

            set_app_theme(app, THEME);
        });

        // Loading last used values
        if (fs::exists(exe_path.toStdString()+"/settings.ini"))
        {
            Ini::File cfg; cfg.load(exe_path+"/settings.ini");

            ui.slider1        -> setValue(cfg["SLIDERS"]["S1"].toInt());
            ui.slider2        -> setValue(cfg["SLIDERS"]["S2"].toInt());
            ui.notif_agree    -> setChecked(cfg["EXTRAS"]["NOTIF_AGREE"].toInt());
            ui.notif_duration -> setValue(cfg["EXTRAS"]["NOTIF_DURATION"].toInt());
            ui.comboBox       -> setCurrentText(cfg["EXTRAS"]["CURRENT_THEME"]);
        }

        win.show();
        return app.exec();
}
