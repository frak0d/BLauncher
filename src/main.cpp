#include <tuple>
#include <string>
#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <filesystem>

#include "time.hpp"
#include "libs/nini.hpp"

#include <ui_main.h>

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

using std::printf;
#define elif else if
typedef std::string str;
namespace fs = std::filesystem;

bool KillerRunning = false;

void print(const auto& ... args)
{
    (std::cout << ... << args);
}
void print2(const auto& ... args)
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
    return {R,G,B};
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
    std::cout << cmd << std::endl;
    return false;
}

str cmd2(const str& cmd)
{
    return "work in progress";
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
        printf("Enabling Crash Fix... ");
        cmd2(R"FucK(powershell -Command "Disable-WindowsErrorReporting")FucK");
        
        status() == 0 ? printf("Success\n")
                      : printf("Failed\n");
    }
    elif (status() == 0)
    {
        printf("Disabling Crash Fix... ");
        cmd2(R"FucK(powershell -Command "Enable-WindowsErrorReporting")FucK");
        
        status() == 1 ? printf("Success\n")
                      : printf("Failed\n");
    }
    elif (status() == 6)
        printf("SOMETHING WENT WRONG...\n");
}

void fix2f()
{
    printf("Applying Store Fix....\n");
    try {
        cmd2(R"FucK(reg import "./assets/Fix_SVC.reg")FucK");
        printf("\x1b[32mPLEASE RESTART YOUR PC FOR CHANGES TO TAKE EFFECT !\n");
    }
    catch (...) {
        printf("\x1b[36mTRY RUNNING BLAUNCHER AS ADMINISTRATOR !\n");
    }
}

void tamer(uint tame1, uint tame2)
{
        KillerRunning = true;
        printf("Time 1 = %u seconds\n", tame1);
        printf("Time 2 = %u seconds\n", tame2);
        tim.sleep(tame1);

        while (true)
        {
                try {
                    cmd2("taskkill /f /im ClipSVC.exe");
                    cmd2("taskkill /f /im RuntimeBroker.exe");
                    printf("KILLED !\n");
                }
                catch (...) {
                    printf("\nOOPS SOMETHING WENT WRONG...\n");
                    printf("TRY RUNNING BLAUNCHER AS ADMINISTRATOR !\n");
                }
        }

        tim.sleep(tame2 - 30);
        //if (self.notif_agree.isChecked())
        //    warning(self.notif_duration.value());
        tim.sleep(30);
        printf("killing...!\n");
}

int main(int argc, char* argv[])
{
        QApplication app(argc, argv);
        Ui::window ui;
        QWidget win;
        ui.setupUi(&win);

        auto savef = [&]()
        {
            Ini::File cfg("settings.ini");

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
                print("\n\33[33mKiller is Already Active !");
            }
            else
            {
                print("\n\33[32mInitiating Startup....\n");
                auto tame1 = ui.slider1->value();
                auto tame2 = ui.slider2->value() * 60;

                try {
                    haxx_on();
                    cmd("explorer.exe shell:AppsFolder/Microsoft.MinecraftUWP_8wekyb3d8bbwe!App");
                    auto killer = std::thread(tamer, tame1, tame2);
                    killer.detach();
                }
                catch (...) {
                    print('OOPS SOMETHING WENT WRONG...');
                    print('TRY RUNNING BLAUNCHER AS ADMINISTRATOR !');
                }
            }
        };

        auto stopf = [&]()
        {
            if (KillerRunning)
            {
                print('\nStopping Killer....');
                try {
                    haxx_off();
                    print('\nKiller Stopped !');
                    print('\n\33[31mEXITING PROGRAM....');
                    tim.sleep(0.2);
                    std::exit(1);
                }
                catch (...) {
                    print('\n\33[33mOOPS SOMETHING WENT WRONG...');
                    print('\n\33[33mEXITING PROGRAM....');
                    tim.sleep(2);
                    std::exit(0);
                }
            }
            else
            {
                print('\n\33[31mEXITING PROGRAM....');
                tim.sleep(0.2);
                std::exit(1);
            }
        };

        auto expandf = [&]()
        {
            int TargetWidth = 0;

            if (win.width() == 460)
            {
                TargetWidth = 750;
                ui.optionb->setText("Options  <<");
            }
            else
            {
                TargetWidth = 460;
                ui.optionb->setText("Options  >>");
            }

            int time = 1;
            int fps = 60;
            int frames = fps*time;
            int fak = (TargetWidth - win.width()) / frames;

            for (int i=0 ; i < frames ; ++i)
            {
                tim.msleep(1000/fps);
                win.resize(win.width()+fak*i, win.height());
            }
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

        for (auto& entry : fs::directory_iterator("themes"))
        {
            if (entry.is_regular_file() && entry.path().string().ends_with(".blt"))
                ui.comboBox->addItem(entry.path().stem().string().c_str());
        }

        QObject::connect(ui.comboBox, &QComboBox::currentTextChanged, [&](const QString& ThemeName)
        {
            Ini::File theme;
            theme.load(("themes/"+ThemeName+".blt").toStdString());
            auto THEME = theme["THEME"];
            ui.auth_name->setText(THEME["AuthorName"].c_str());

            set_app_theme(app, THEME);
        });

        // Loading last used values
        if (fs::exists("settings.ini"))
        {
            Ini::File cfg; cfg.load("settings.ini");

            ui.slider1        -> setValue(str_to<int>(cfg["SLIDERS"]["S1"]));
            ui.slider2        -> setValue(str_to<int>(cfg["SLIDERS"]["S2"]));
            ui.notif_agree    -> setChecked(str_to<bool>(cfg["EXTRAS"]["NOTIF_AGREE"]));
            ui.notif_duration -> setValue(str_to<int>(cfg["EXTRAS"]["NOTIF_DURATION"]));
            ui.comboBox       -> setCurrentText(cfg["EXTRAS"]["CURRENT_THEME"].c_str());
        }

        win.show();
        return app.exec();
}