## Akira - InsydeFlash patcher 🐱‍👤
⚠**CAUTION**⚠: _Owner_ Is _Not Responsible For Damage_ To Notebook Or Any Malfunction. This project is provided AS IS.

---
### About
I had a problem with my old notebook which is Alienware m17x R4 (👽) that there was no way to update BIOS with a dead battery, I tried many ways to work around this but in the end nothing worked. So I made this little patcher that allows you to update the BIOS with a dead battery, but please think twice before using it.

---
### How to use
Basically you run bios update .exe and wait until it says that your battery should be charged for 10% or more percent and then inject the compiled dll into InsydeFlash.exe. (For example: you can use Process Hacker to inject it). Then press OK and viola. It works.

#### More detailed how to use:
```
You can download the injector there: https://github.com/master131/ExtremeInjector/releases/

Download the latest version: https://github.com/cpz/akira/releases/

Launch bios updater, launch injector, add dll and choose InsydeFlash.exe 
(example: https://screensh.it/tsD63Tc8)

1. Press Inject
2. After a successful inject you can close the injector. And I would recommend to close everything else.
3. Press OK in InsydeFlash.
4. It will go into reboot if everything is ok, otherwise it will give you an error, you can make a screenshot and open issue and I'll look into it when I have free time.
```

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

