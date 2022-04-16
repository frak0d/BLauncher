#pragma once


struct notify_params
{
    int TimeMsec{5000};
    QString IconPath{};
    QString TitleText{};
    QString BodyText; // required
};


int init_tray_icon = []()
{
     return 1;
}();

inline void notify(const notify_params& params)
{
    
}
