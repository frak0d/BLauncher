# BLauncher v2.0 (Now in C++)

---

[Click Here for All Downloads](https://techarchives.rf.gd/home.html)

[Click Here for All Changelogs](https://techarchives.rf.gd/history.html)
---

### Build Requirements :-
- upx
- qt5
- meson
- boost.process

### Build Instructions :-
1. First install `msys2` and switch to CLANG32 mode.
2. Then Run Following Commands :-
	1. `pacman -Syu upx mingw-w64-clang-i686-clang mingw-w64-clang-i686-meson mingw-w64-clang-i686-qt5-static mingw-w64-clang-i686-boost`
	2. `git clone https://github.com/Tanishq-Banyal/BLauncher`
	3. `cd BLauncher && meson build -Dstatic=true`
	4. `ninja -C build install compress`
3. Build output should be in `build_output` folder.
