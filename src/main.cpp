#include <string>
#include <cstdlib>
#include <iostream>
#include <filesystem>

#include "time.hpp"
#include "libs/nini.hpp"

#include <ui_main.h>

using std::printf;
#define elif else if
typedef std::string str;
namespace fs = std::filesystem;

bool KillerRunning = false;

str StopCommand  = R"FucK(Reg.exe add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\ClipSVC\Parameters" /v "ServiceDll" /t REG_EXPAND_SZ /d "%%SystemRoot%%\System32\ClipSVC.dll" /f)FucK";
str StartCommand = R"FucK(Reg.exe add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\ClipSVC\Parameters" /v "ServiceDll" /t REG_EXPAND_SZ /d "%%SystemRoot%%\System32\ClipSBC.dll" /f)FucK";

/* C++20 not yet supported by qt creator
void print(const auto& ... args)
{
    (std::cout << ... << args);
}
void print2(const auto& ... args)
{
    (std::cout << ... << args) << std::endl;
}
*/

bool cmd(const str& cmd)
{
    std::cout << cmd << std::endl;
    return false;
}

str cmd2(const str& cmd)
{
    return "work in progress";
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
            puts("savef"); fflush(stdout);
        };

        auto startf = [&]()
        {
            puts("startf"); fflush(stdout);
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

        QObject::connect(ui.notif_agree, &QCheckBox::stateChanged, [&](int state){savef();});
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
        });
/*
        if path.isfile('settings.ini'):         # Load last used values if exist
            s1_val = int(settings['SLIDERS']['S1'])     # Needed to do this due to some unknown bug,
            s2_val = int(settings['SLIDERS']['S2'])     # else i could have put the values directly.
            nf_ag = eval(settings['EXTRAS']['NOTIF_AGREE'])
            nf_dur = int(settings['EXTRAS']['NOTIF_DURATION'])
            
            self.slider1.setValue(s1_val)
            self.slider2.setValue(s2_val)
            self.notif_agree.setChecked(nf_ag)
            self.notif_duration.setValue(nf_dur)
        
        self.comboBox.setCurrentText(cur_thm)*/

        win.show();
        return app.exec();
}
