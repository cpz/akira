## Akira -- InsydeFlash patcher 🐱‍👤
⚠**CAUTION**⚠: _Owner_ Is _Not Responsible For Damage_ To Notebook Or Any Malfunction. This project provided AS IS.

---
### About
I had problem with my old notebook which is Alienware m17x R4 (👽) that there was no way to update BIOS with dead battery, I tried plenty ways to bypass this but nothing worked at the end. So, I made this little patcher which will allow you to update BIOS even with dead battery but please, think twice before using it.

---
### How to use
Basically, you run bios update .exe and wait till it says that your battery should be charger for 10% or more percent and then inject compiled dll in to InsydeFlash.exe. (For example: you can use ProcessHacker to inject it). Then press OK and viola. Its works.

---
### Building
To build akira you need:

-   Visual Studio 2022
-   [Premake 5.0](https://premake.github.io/download) in your PATH

To set up the build environment, run the following commands in a terminal:

```dos
git clone https://github.com/cpz/akira.git--recurse-submodules
cd akira
premake5 vs2022
```

Now, you will be able to open the solution, and simply build it in Visual Studio.

