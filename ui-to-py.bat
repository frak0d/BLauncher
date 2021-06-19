@echo OFF

::pyuic5 -g cpp "./gui_qt6.ui" -o "./gui_qt6.hpp"
pyuic5  -i 0 "./gui_main.ui" -o "./gui_main.py" -x

::pyuic5 -g cpp "./gui_qt6.ui" -o "./gui_qt6.hpp"
pyuic5 -i 0 "./gui_extra.ui" -o "./gui_extra.py" -x

pause