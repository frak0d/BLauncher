#include <tuple>
#include <queue>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstdint>
#include <sstream>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <string_view>

#include "cmd.cpp"
#include "nini.cpp"
#include "sleep.cpp"
#include "colors.cpp"
#include "str2color.cpp"

#include <ui_main.h>
#include <windows.h>

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Advapi32.lib")

#include <QtGui/QIcon>
#include <QtCore/QTimer>
#include <QtGui/QPalette>
#include <QtCore/QString>
#include <QtGui/QTextCursor>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QtWidgets/QSystemTrayIcon>
#include <QtCore/QPropertyAnimation>

#define elif else if
using namespace std::literals;
namespace fs = std::filesystem;

bool KillerRunning = false;
QSystemTrayIcon* tray_icon;
std::queue<QString> print_queue;

std::ostream& operator<< (std::ostream& out, const QString& str)
{
    return out << str.toStdString();
}

void print(const auto& ...args)
{
    std::stringstream ss;
    (ss << ... << args);
    print_queue.emplace(ss.str().c_str());
}

void println(const auto& ...args)
{
    std::stringstream ss;
    (ss << ... << args) << '\n';
    print_queue.emplace(ss.str().c_str());
};

void cwd2ExePath()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    auto exepath = std::string(buffer);
    auto dirpath = exepath.substr(0, exepath.find_last_of("\\/"));
    SetCurrentDirectoryA(dirpath.c_str());
}

bool iAmAdmin()
{
    bool IsElevated = false;
    HANDLE hToken = NULL;
    TOKEN_ELEVATION elevation;
    DWORD dwSize;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
        goto Cleanup; // if Failed, we treat as False

    if (!GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &dwSize))
        goto Cleanup; // if Failed, we treat as False

    IsElevated = elevation.TokenIsElevated;

Cleanup:
    if (hToken)
    {
        CloseHandle(hToken);
        hToken = NULL;
    }
    return IsElevated;
}

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
        ToolTipTextColor.red(), ToolTipTextColor.green(), ToolTipTextColor.blue(), ToolTipBaseColor.red(), ToolTipBaseColor.green(), ToolTipBaseColor.blue());
    
    app.setStyleSheet(stylesheet);
}

void set_app_theme_ex(QApplication& app, const QString& theme_name, QLabel* author_name=nullptr)
{
    Ini::File theme;
    theme.load("themes/"+theme_name+".blt");
    set_app_theme(app, theme["THEME"]);

    if (author_name)
        author_name->setText(theme["THEME"]["AuthorName"]);
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
    std::cout << s << std::endl;
    
    if   (s == "Enabled\r\n" ) return 1;
    elif (s == "Disabled\r\n") return 0;
    else return 6;
}

void warning(int time_msec)
{
    println("Sent Toast Notification!"_cyn);
    
    tray_icon->showMessage("BLauncher: Potential Crash Warning !",
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

void tamer(uint tame1, uint tame2, const Ui::window& ui)
{
    KillerRunning = true;
    sleep_for(tame1, "s");

    while (true)
    {
        try
        {
            cmd2("taskkill /f /im ClipSVC.exe");
            cmd2("taskkill /f /im RuntimeBroker.exe");
            print("DEATH NOTE ISSUED SUCCESSFULLY !\n");
        }
        catch (...)
        {
            print("\nOOPS SOMETHING WENT WRONG...\n"_red);
            print("TRY RUNNING BLAUNCHER AS ADMINISTRATOR !\n"_bldred);
        }

        sleep_for(tame2-30, "s");
        if (ui.notif_agree->isChecked())
            warning(ui.notif_duration->value());
        sleep_for(30, "s");
    }
}

void check_startup_conditions()
{
    if (!iAmAdmin())
    {
        MessageBox(NULL, L"Please Run this Program as Administrator!", L"Fatal Error", MB_OK);
        std::exit(100);
    }
    if (!fs::exists("themes"))
    {
        MessageBox(NULL, L"'themes' directory not found, can't launch GUI.", L"Fatal Error", MB_OK);
        std::exit(101);
    }
    if (fs::is_empty("themes"))
    {
        MessageBox(NULL, L"No valid theme found, can't launch GUI.", L"Fatal Error", MB_OK);
        std::exit(102);
    }
    if (!fs::exists("assets"))
    {
        MessageBox(NULL, L"'assets' directory not found, this will cause visual glitches or instability.", L"Warning", MB_OK);
    }
    if (!fs::exists("plugins/platforms/qwindows.dll"))
    {
        MessageBox(NULL, L"Qt 'windows' platform plugin not found, can't launch GUI.", L"Fatal Error", MB_OK);
        std::exit(103);
    }
    if (!fs::exists("plugins/imageformats/qico.dll"))
    {
        MessageBox(NULL, L"Qt 'ico' image format plugin not found, this may cause visual glitches or instability.", L"Warning", MB_OK);
    }
}

int main(int argc, char* argv[])
{
    cwd2ExePath();
    check_startup_conditions();
    QApplication app(argc, argv);

    QSystemTrayIcon tray_icon_obj{};
    tray_icon = &tray_icon_obj;
    tray_icon->setIcon(QIcon("assets/logo.ico"));
    tray_icon->setToolTip("BLauncher is Running!");
    tray_icon->show();
    std::atexit([]{tray_icon->~QSystemTrayIcon();});

    Ui::window ui;
    QWidget win;
    ui.setupUi(&win);

    auto print_handler = [&ui]()
    {
        while (!print_queue.empty())
        {
            ui.console->moveCursor(QTextCursor::End);
            ui.console->insertHtml(print_queue.front());
            print_queue.pop();
            ui.console->moveCursor(QTextCursor::End);
        }
    };

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, print_handler);
    timer.start(250/*ms*/);

    auto savef = [&]()
    {
        Ini::File cfg("settings.ini");

        cfg["SLIDERS"]["S1"]            = QString(std::to_string( ui.slider1        -> value()      ).c_str());
        cfg["SLIDERS"]["S2"]            = QString(std::to_string( ui.slider2        -> value()      ).c_str());
        cfg["EXTRAS"]["NOTIF_AGREE"]    = QString(std::to_string( ui.notif_agree    -> isChecked()  ).c_str());
        cfg["EXTRAS"]["NOTIF_DURATION"] = QString(std::to_string( ui.notif_duration -> value()      ).c_str());
        cfg["EXTRAS"]["CURRENT_THEME"]  =                       ( ui.comboBox       -> currentText())         ;
        cfg["WINDOW"]["H_EXPAND"]       = QString(std::to_string(win.width()  == win.maximumWidth() ).c_str());
        cfg["WINDOW"]["V_EXPAND"]       = QString(std::to_string(win.height() == win.maximumHeight()).c_str());
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
                auto killer = std::thread(tamer, tame1, tame2, ui);
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
        savef(); // save settings.ini before exiting

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

    auto expandf1 = [&]()
    {
        int TargetWidth1, TargetWidth2;

        if (win.width() == win.minimumWidth())
        {
            TargetWidth1 = win.maximumWidth();
            TargetWidth2 = ui.console->maximumWidth();
            ui.optionb->setText("Hide Options");
        }
        else
        {
            TargetWidth1 = win.minimumWidth();
            TargetWidth2 = ui.console->minimumWidth();
            ui.optionb->setText("Show Options");
        }

        // need to do it the pointer way to prevent animation
        // from going out of scope before it completes

        auto animation1 = new QPropertyAnimation(&win, "size");
        animation1->setDuration(500);
        animation1->setEndValue(QSize(TargetWidth1, win.height()));
        animation1->setEasingCurve(QEasingCurve::OutCubic);
        animation1->start(QAbstractAnimation::DeleteWhenStopped);

        auto animation2 = new QPropertyAnimation(ui.console, "size");
        animation2->setDuration(500);
        animation2->setEndValue(QSize(TargetWidth2, win.height()));
        animation2->setEasingCurve(QEasingCurve::OutCubic);
        animation2->start(QAbstractAnimation::DeleteWhenStopped);
    };

    auto expandf2 = [&]()
    {
        int TargetHeight;

        if (win.height() == win.minimumHeight())
        {
            TargetHeight = win.maximumHeight();
            ui.consoleb->setText("Hide Console");
        }
        else
        {
            TargetHeight = win.minimumHeight();
            ui.consoleb->setText("Show Console");
        }

        // need to do it the pointer way to prevent animation
        // from going out of scope before it completes

        auto animation = new QPropertyAnimation(&win, "size");
        animation->setDuration(400);
        animation->setEndValue(QSize(win.width(), TargetHeight));
        animation->setEasingCurve(QEasingCurve::OutCubic);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    };

    QObject::connect(ui.fix1b, &QPushButton::clicked, crash_fix);
    QObject::connect(ui.fix2b, &QPushButton::clicked, store_fix);

    QObject::connect(ui.startb,   &QPushButton::clicked, startf);
    QObject::connect(ui.optionb,  &QPushButton::clicked, expandf1);
    QObject::connect(ui.consoleb, &QPushButton::clicked, expandf2);

    QApplication::connect(&app, &QApplication::aboutToQuit, stopf);

    QObject::connect(ui.DISCORD, &QPushButton::clicked, [](){cmd("start https://discord.gg/5pkSfFF");});
    QObject::connect(ui.YOUTUBE, &QPushButton::clicked, [](){cmd("start https://youtube.com/frakod?sub_confirmation=1");});

    QObject::connect(ui.slider1, &QSlider::valueChanged, [&](int value)
    {
        ui.spinbox1->setValue(value);
    });

    QObject::connect(ui.slider2, &QSlider::valueChanged, [&](int value)
    {
        ui.spinbox2->setValue(value);
    });

    QObject::connect(ui.spinbox1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [&](double value)
    {
        ui.slider1->setValue(value);
    });

    QObject::connect(ui.spinbox2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [&](double value)
    {
        ui.slider2->setValue(value);
    });

    for (auto& entry : fs::directory_iterator("themes"))
    {
        if (entry.is_regular_file() && entry.path().string().ends_with(".blt"))
            ui.comboBox->addItem(entry.path().stem().string().c_str());
    }

    QObject::connect(ui.comboBox, &QComboBox::currentTextChanged, [&](const QString& ThemeName)
    {
        set_app_theme_ex(app, ThemeName, ui.auth_name);
    });

    // Loading last used values
    if (fs::exists("settings.ini"))
    {
        Ini::File cfg; cfg.load("settings.ini");

        ui.slider1        -> setValue(cfg["SLIDERS"]["S1"].toInt());
        ui.slider2        -> setValue(cfg["SLIDERS"]["S2"].toInt());
        ui.notif_agree    -> setChecked(cfg["EXTRAS"]["NOTIF_AGREE"].toInt());
        ui.notif_duration -> setValue(cfg["EXTRAS"]["NOTIF_DURATION"].toInt());
        ui.comboBox       -> setCurrentText(cfg["EXTRAS"]["CURRENT_THEME"]);

        if (cfg["WINDOW"]["H_EXPAND"].toInt())
        {
            win.resize(win.maximumWidth(), win.height());
            ui.console->resize(ui.console->maximumWidth(), ui.console->height());
            ui.optionb->setText("Hide Options");
        }
        if (cfg["WINDOW"]["V_EXPAND"].toInt())
        {
            win.resize(win.width(), win.maximumHeight());
            ui.consoleb->setText("Hide Console");
        }
    }

    set_app_theme_ex(app, ui.comboBox->currentText());
    win.show(); return app.exec();
}
