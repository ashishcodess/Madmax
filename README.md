# Madmax
The game using BFS algorithm which I wrote while creating a player to compete in tournament of EDA-JOC.

In case of any doubt open P32575_en.pdf.

## Demo

![ezgif com-gif-maker](https://user-images.githubusercontent.com/78503778/120550329-03051280-c3f5-11eb-86d2-549ef4a351e4.gif)

## Running first match
Here is the explaination to run the game under Linux, but a similar procedure
should work as well under Windows, Mac, FreeBSD, OpenSolaris... The only
requirements on your system are g++, make and a modern browser like Mozilla
Firefox or Chromium.


I have not tried running the game in other operating systems but to run your first match in Linux, follow the next steps:

* Open a console and cd to the directory where you extracted the source
code.
* If, for example, you are using a 64-bit Linux version, run:
```bash
cp AIDummy.o.Linux64 AIDummy.o
```   
If you use any other architecture, choose the right object you will find in
the directory.

* Run ``` make all ```  to build the game and all the players. Note that the Makefile will identify as a player any file matching the expression "AI*.cc".
* If you want to run the game playing my player with default player:
```bash
./Game Nepal Dummy Dummy Dummy -s 3424 < default.cnf > default.res
``` 
* To watch the match, open the viewer (viewer.html) with your browser
and load the "default.res" file.
