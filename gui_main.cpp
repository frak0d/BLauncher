/********************************************************************************
** Form generated from reading UI file 'gui_main.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtGui/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_window
{
public:
    QPushButton *startb;
    QGroupBox *groupBox;
    QSlider *slider1;
    QDoubleSpinBox *spinbox1;
    QLabel *label;
    QGroupBox *groupBox_3;
    QSlider *slider2;
    QDoubleSpinBox *spinbox2;
    QLabel *label_5;
    QGroupBox *groupBox_2;
    QPushButton *optionb;
    QLabel *BL_LOGO;
    QPushButton *fix2b;
    QPushButton *fix1b;
    QSpinBox *notif_duration;
    QPushButton *DISCORD;
    QLabel *label_2;
    QPushButton *YOUTUBE;
    QLabel *label_6;
    QCheckBox *notif_agree;
    QGroupBox *dev_info;
    QLabel *label_3;
    QLabel *label_8;
    QComboBox *comboBox;
    QLabel *label_9;
    QLabel *auth_name;
    QLabel *label_11;

    void setupUi(QWidget *window)
    {
        if (window->objectName().isEmpty())
            window->setObjectName(QString::fromUtf8("window"));
        window->resize(460, 335);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(window->sizePolicy().hasHeightForWidth());
        window->setSizePolicy(sizePolicy);
        window->setMinimumSize(QSize(460, 335));
        window->setMaximumSize(QSize(750, 335));
        QIcon icon;
        icon.addFile(QString::fromUtf8("assets/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        window->setWindowIcon(icon);
        startb = new QPushButton(window);
        startb->setObjectName(QString::fromUtf8("startb"));
        startb->setEnabled(true);
        startb->setGeometry(QRect(20, 25, 301, 81));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(startb->sizePolicy().hasHeightForWidth());
        startb->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Comic Sans MS"));
        font.setPointSize(25);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferAntialias);
        startb->setFont(font);
        startb->setMouseTracking(false);
        groupBox = new QGroupBox(window);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 170, 421, 68));
        slider1 = new QSlider(groupBox);
        slider1->setObjectName(QString::fromUtf8("slider1"));
        slider1->setGeometry(QRect(10, 38, 340, 21));
        slider1->setAutoFillBackground(false);
        slider1->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        slider1->setMinimum(1);
        slider1->setMaximum(100);
        slider1->setPageStep(10);
        slider1->setValue(40);
        slider1->setSliderPosition(40);
        slider1->setOrientation(Qt::Horizontal);
        slider1->setTickPosition(QSlider::NoTicks);
        slider1->setTickInterval(1);
        spinbox1 = new QDoubleSpinBox(groupBox);
        spinbox1->setObjectName(QString::fromUtf8("spinbox1"));
        spinbox1->setGeometry(QRect(360, 37, 50, 22));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setStyleStrategy(QFont::PreferAntialias);
        spinbox1->setFont(font1);
        spinbox1->setToolTipDuration(2);
        spinbox1->setAlignment(Qt::AlignCenter);
        spinbox1->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinbox1->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        spinbox1->setDecimals(0);
        spinbox1->setMinimum(1.000000000000000);
        spinbox1->setMaximum(100.000000000000000);
        spinbox1->setSingleStep(1.000000000000000);
        spinbox1->setStepType(QAbstractSpinBox::DefaultStepType);
        spinbox1->setValue(40.000000000000000);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(15, 7, 381, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Comic Sans MS"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setKerning(true);
        font2.setStyleStrategy(QFont::PreferAntialias);
        label->setFont(font2);
        groupBox_3 = new QGroupBox(window);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 250, 421, 68));
        slider2 = new QSlider(groupBox_3);
        slider2->setObjectName(QString::fromUtf8("slider2"));
        slider2->setGeometry(QRect(10, 38, 340, 21));
        slider2->setAutoFillBackground(false);
        slider2->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        slider2->setMinimum(1);
        slider2->setMaximum(30);
        slider2->setSingleStep(1);
        slider2->setPageStep(5);
        slider2->setValue(15);
        slider2->setSliderPosition(15);
        slider2->setOrientation(Qt::Horizontal);
        slider2->setTickPosition(QSlider::NoTicks);
        slider2->setTickInterval(1);
        spinbox2 = new QDoubleSpinBox(groupBox_3);
        spinbox2->setObjectName(QString::fromUtf8("spinbox2"));
        spinbox2->setGeometry(QRect(360, 37, 50, 22));
        spinbox2->setFont(font1);
        spinbox2->setToolTipDuration(2);
        spinbox2->setAlignment(Qt::AlignCenter);
        spinbox2->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinbox2->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        spinbox2->setDecimals(0);
        spinbox2->setMinimum(1.000000000000000);
        spinbox2->setMaximum(30.000000000000000);
        spinbox2->setSingleStep(1.000000000000000);
        spinbox2->setStepType(QAbstractSpinBox::DefaultStepType);
        spinbox2->setValue(15.000000000000000);
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(15, 7, 381, 31));
        label_5->setFont(font2);
        groupBox_2 = new QGroupBox(window);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(330, 17, 111, 134));
#if QT_CONFIG(tooltip)
        groupBox_2->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        groupBox_2->setStatusTip(QString::fromUtf8(""));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        groupBox_2->setWhatsThis(QString::fromUtf8(""));
#endif // QT_CONFIG(whatsthis)
        groupBox_2->setAutoFillBackground(false);
        groupBox_2->setTitle(QString::fromUtf8(""));
        groupBox_2->setAlignment(Qt::AlignCenter);
        groupBox_2->setFlat(false);
        optionb = new QPushButton(groupBox_2);
        optionb->setObjectName(QString::fromUtf8("optionb"));
        optionb->setGeometry(QRect(6, 94, 100, 35));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../../../.designer/backup/assets/configure.png"), QSize(), QIcon::Normal, QIcon::On);
        optionb->setIcon(icon1);
        optionb->setIconSize(QSize(16, 16));
        BL_LOGO = new QLabel(groupBox_2);
        BL_LOGO->setObjectName(QString::fromUtf8("BL_LOGO"));
        BL_LOGO->setGeometry(QRect(14, 8, 85, 85));
        BL_LOGO->setTextFormat(Qt::PlainText);
        BL_LOGO->setPixmap(QPixmap(QString::fromUtf8("assets/bl_logo.png")));
        BL_LOGO->setScaledContents(true);
        BL_LOGO->setAlignment(Qt::AlignCenter);
        fix2b = new QPushButton(window);
        fix2b->setObjectName(QString::fromUtf8("fix2b"));
        fix2b->setGeometry(QRect(600, 120, 125, 35));
        fix2b->setMouseTracking(false);
#if QT_CONFIG(statustip)
        fix2b->setStatusTip(QString::fromUtf8(""));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        fix2b->setWhatsThis(QString::fromUtf8(""));
#endif // QT_CONFIG(whatsthis)
        fix2b->setLayoutDirection(Qt::LeftToRight);
        fix2b->setAutoFillBackground(false);
        fix2b->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("assets/configure.png"), QSize(), QIcon::Normal, QIcon::On);
        fix2b->setIcon(icon2);
        fix2b->setIconSize(QSize(20, 20));
        fix2b->setFlat(false);
        fix1b = new QPushButton(window);
        fix1b->setObjectName(QString::fromUtf8("fix1b"));
        fix1b->setGeometry(QRect(465, 120, 125, 35));
        fix1b->setIcon(icon2);
        fix1b->setIconSize(QSize(16, 16));
        notif_duration = new QSpinBox(window);
        notif_duration->setObjectName(QString::fromUtf8("notif_duration"));
        notif_duration->setEnabled(false);
        notif_duration->setGeometry(QRect(676, 200, 42, 22));
        notif_duration->setMinimum(1);
        notif_duration->setMaximum(15);
        notif_duration->setValue(5);
        DISCORD = new QPushButton(window);
        DISCORD->setObjectName(QString::fromUtf8("DISCORD"));
        DISCORD->setGeometry(QRect(476, 290, 100, 33));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("assets/discord_join.png"), QSize(), QIcon::Normal, QIcon::On);
        DISCORD->setIcon(icon3);
        DISCORD->setIconSize(QSize(90, 35));
        DISCORD->setFlat(true);
        label_2 = new QLabel(window);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(false);
        label_2->setGeometry(QRect(460, 200, 201, 21));
        QFont font3;
        font3.setStrikeOut(true);
        label_2->setFont(font3);
        YOUTUBE = new QPushButton(window);
        YOUTUBE->setObjectName(QString::fromUtf8("YOUTUBE"));
        YOUTUBE->setGeometry(QRect(587, 290, 100, 33));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("assets/yt_sub.png"), QSize(), QIcon::Normal, QIcon::On);
        YOUTUBE->setIcon(icon4);
        YOUTUBE->setIconSize(QSize(90, 25));
        YOUTUBE->setFlat(true);
        label_6 = new QLabel(window);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(460, 230, 281, 51));
        label_6->setFrameShadow(QFrame::Plain);
        label_6->setTextFormat(Qt::PlainText);
        label_6->setWordWrap(true);
        label_6->setIndent(1);
        notif_agree = new QCheckBox(window);
        notif_agree->setObjectName(QString::fromUtf8("notif_agree"));
        notif_agree->setGeometry(QRect(460, 170, 271, 21));
        notif_agree->setIconSize(QSize(16, 16));
        notif_agree->setChecked(false);
        dev_info = new QGroupBox(window);
        dev_info->setObjectName(QString::fromUtf8("dev_info"));
        dev_info->setGeometry(QRect(463, 10, 125, 101));
#if QT_CONFIG(tooltip)
        dev_info->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        dev_info->setStatusTip(QString::fromUtf8(""));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        dev_info->setWhatsThis(QString::fromUtf8(""));
#endif // QT_CONFIG(whatsthis)
        dev_info->setAutoFillBackground(false);
        dev_info->setTitle(QString::fromUtf8(""));
        dev_info->setAlignment(Qt::AlignCenter);
        dev_info->setFlat(false);
        label_3 = new QLabel(dev_info);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 6, 125, 90));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Doppio One"));
        font4.setPointSize(13);
        font4.setBold(true);
        font4.setUnderline(false);
        font4.setWeight(75);
        font4.setKerning(true);
        font4.setStyleStrategy(QFont::PreferAntialias);
        label_3->setFont(font4);
        label_3->setMouseTracking(true);
        label_3->setText(QString::fromUtf8("<a href=\"https://techarchives.rf.gd\"><span style=\" color:#ffff00;\">BLauncher<br>v1.19</span></a>"));
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setWordWrap(true);
        label_3->setOpenExternalLinks(true);
        label_3->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        label_8 = new QLabel(window);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(600, 20, 111, 31));
        label_8->setFrameShadow(QFrame::Plain);
        label_8->setTextFormat(Qt::PlainText);
        label_8->setWordWrap(true);
        label_8->setIndent(1);
        comboBox = new QComboBox(window);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(600, 51, 121, 21));
        label_9 = new QLabel(window);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(600, 75, 51, 31));
        label_9->setFrameShadow(QFrame::Plain);
        label_9->setTextFormat(Qt::PlainText);
        label_9->setWordWrap(true);
        label_9->setIndent(1);
        auth_name = new QLabel(window);
        auth_name->setObjectName(QString::fromUtf8("auth_name"));
        auth_name->setGeometry(QRect(650, 75, 90, 31));
        auth_name->setFrameShadow(QFrame::Plain);
        auth_name->setTextFormat(Qt::PlainText);
        auth_name->setWordWrap(true);
        auth_name->setIndent(1);
        label_11 = new QLabel(window);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(50, 125, 241, 21));
        QFont font5;
        font5.setPointSize(9);
        label_11->setFont(font5);
        label_11->setAlignment(Qt::AlignCenter);
        groupBox->raise();
        startb->raise();
        groupBox_3->raise();
        groupBox_2->raise();
        fix2b->raise();
        fix1b->raise();
        notif_duration->raise();
        DISCORD->raise();
        label_2->raise();
        YOUTUBE->raise();
        label_6->raise();
        notif_agree->raise();
        dev_info->raise();
        label_8->raise();
        comboBox->raise();
        label_9->raise();
        auth_name->raise();
        label_11->raise();

        retranslateUi(window);

        QMetaObject::connectSlotsByName(window);
    } // setupUi

    void retranslateUi(QWidget *window)
    {
        window->setWindowTitle(QCoreApplication::translate("window", "BLauncher v1.19  - Minecraft Windows 10 Edition", nullptr));
#if QT_CONFIG(tooltip)
        startb->setToolTip(QCoreApplication::translate("window", "Activate Exploit and Launch Game.", nullptr));
#endif // QT_CONFIG(tooltip)
        startb->setText(QCoreApplication::translate("window", "Start Playing", nullptr));
#if QT_CONFIG(tooltip)
        groupBox->setToolTip(QCoreApplication::translate("window", "Keep adjusting this slider till you get desired results.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QString());
#if QT_CONFIG(tooltip)
        spinbox1->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("window", "Set Initial Kill Timer :-                  (seconds)", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_3->setToolTip(QCoreApplication::translate("window", "Decrease its value if your game becomes Trail while playing.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_3->setTitle(QString());
#if QT_CONFIG(tooltip)
        spinbox2->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("window", "Set Periodic Kill Timer :-                (minutes)", nullptr));
#if QT_CONFIG(tooltip)
        optionb->setToolTip(QCoreApplication::translate("window", "More Options !", nullptr));
#endif // QT_CONFIG(tooltip)
        optionb->setText(QCoreApplication::translate("window", "Options  >>", nullptr));
        BL_LOGO->setText(QString());
#if QT_CONFIG(tooltip)
        fix2b->setToolTip(QCoreApplication::translate("window", "Use this button if you are unable to Install any apps from Microsoft Store.", nullptr));
#endif // QT_CONFIG(tooltip)
        fix2b->setText(QCoreApplication::translate("window", "Store Fix", nullptr));
#if QT_CONFIG(tooltip)
        fix1b->setToolTip(QCoreApplication::translate("window", "Use this button if your game crashes while playing.", nullptr));
#endif // QT_CONFIG(tooltip)
        fix1b->setText(QCoreApplication::translate("window", "Crash Fix", nullptr));
#if QT_CONFIG(tooltip)
        DISCORD->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        DISCORD->setText(QString());
        label_2->setText(QCoreApplication::translate("window", "\342\200\242 Notification Duration  (seconds) :", nullptr));
#if QT_CONFIG(tooltip)
        YOUTUBE->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        YOUTUBE->setText(QString());
        label_6->setText(QCoreApplication::translate("window", "NOTE : You need to Turn off \"Focus Assist\" in windows settings to recieve in-game notifications.", nullptr));
#if QT_CONFIG(tooltip)
        notif_agree->setToolTip(QCoreApplication::translate("window", "You will recieve a Notification 30 seconds before any potential Crash may Occur.\n"
"Focus Assist may mute the notifications so make sure to turn off Focus Assist in Windows Settings :)", nullptr));
#endif // QT_CONFIG(tooltip)
        notif_agree->setText(QCoreApplication::translate("window", "Get Potential Crash Alert (via Notification)", nullptr));
#if QT_CONFIG(tooltip)
        label_3->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        label_8->setText(QCoreApplication::translate("window", "\342\200\242 Theme :", nullptr));
        label_9->setText(QCoreApplication::translate("window", "\342\200\242 Author :", nullptr));
        auth_name->setText(QString());
        label_11->setText(QCoreApplication::translate("window", "Read Instructions Before Use !", nullptr));
    } // retranslateUi

};

namespace Ui {
    class window: public Ui_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GUI_MAIN_H
