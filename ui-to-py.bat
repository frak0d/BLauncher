@echo OFF

::pyuic5 -g cpp -i 0 -x "./gui_main.ui" -o "./gui_main.cpp"
uic -g cpp "./gui_main.ui" -o "./gui_main.cpp"

pause
