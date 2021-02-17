# Madmax
The game using BFS algorithm which I wrote while creating a player for EDA-JOC

A brief discription is given below .In case of any doubt open P32575_en.pdf.


1  Game rules
This is a game for four players. Each player commands a group of cars in the dangerous roads of Wasteland. The goal is to get the highest possible score by collecting water bonuses and killing other players’ cars. However, gas bonuses also have to be collected in order to keep the cars running and tyres should be avoided to prevent collisions.


The game is played on a bidimensional cylindric universe. After unfolding, this universe can be seen as the result of setting side by side the same rectangle repeatedly along the vertical edge:


Figure 1: The cylindrical universe after unfolding.
This repeated rectangle is an n × m grid of cells, where n is the number of rows and m the number of columns. The leftmost upper cell is (0,0) and the rightmost lower cell is (n−1,m−1). Any pair (i, j) such that 0 ≤ i < n determines the position of a cell of the universe. Note that two positions (i,j) and (i,j′) such that (j − j′) mod  m = 0 actually refer to the same cell. In what follows we will refer to i and j as the row and the column of the position (i, j), respectively.


Each cell of this universe may be empty or may contain:

a tyre, or
a car (commanded by one of the players), or
a missile (previously shot by one of the cars), or
a water bonus, or
a gas bonus, or
a missile bonus.
Players can look up the content of any cell of the universe during the match.


Each player commands a number of cars which is a parameter of the game. Each car has a unique identifying number. The cars commanded by the same player have consecutive identifiers.

1.1  Moving and shooting
At each round a player can command any of its cars to move in a particular direction or to shoot a missile (but not the two at the same time).


In general, the movement of the elements on the universe follows the next rules:

Cars may move horizontally, vertically or in diagonal. More precisely, in one movement a car may increment its row by −1, 0 or 1, and its column by 0, 1 or 2.
By default, at each round a car moves horizontally one column, i.e., its row remains the same and its column increases by 1.
There is a window that the cars must remain within. This window is a rectangle of dimensions n × mW, where mW ≤ m, and is dynamic: it moves forward one column per round. Therefore, at round r, its leftmost upper corner is at position (0, r), and its rightmost lower corner is at position (n−1, r+mW−1). Moreover, a car moving with the default direction remains always within the window.
If a car is requested to move to a position not within the window, the command will be ignored and the car will move according to the default direction.

In the game viewer, the window is the part of the universe that will be shown. Since the window is taken as the system of reference for the visualization, it apparently does not move; similarly, cars moving by default apparently do not move either, etc.

Tyres and bonuses do not move.
Missiles move horizontally two columns per round.
Tyres, bonuses and missiles may be outside the window. Note that in this case, although they cannot be viewed, they still exist on the universe.
A car may shoot a missile if it has at least one in its stock (which is then consumed). There is an initial number of missiles in the stock of each car. This stock can be enlarged by means of missile bonuses. When a car shoots, the new missile automatically moves forward two columns from the car position, and then immediately after, the car also moves with the default direction.

1.2  Collisions in a cell
When a car and a bonus coincide in the same cell, the car consumes the bonus (increasing the number of available missiles if it is a missile bonus, the number of gas units if it is a gas bonus, or getting more score if it is a water bonus). Once a bonus is consumed, if possible it reappears on a random position outside the window. This random position is guaranteed to be previously empty and such that its surrounding square 5 × 5 is free from missiles or cars.

In the other possible cases of collision, when two elements coincide in the same cell both are destroyed. In particular, if one of the colliding elements is a missile shot by a car of player A and the other element is a car of a different player B, then A increases its score.

When a car is killed, it regenerates if possible after a number of rounds, on a random position of the window. This random position is guaranteed to be previously empty and such that its surrounding square 5 × 5 is free from missiles, cars or tyres. The number of available missiles is the same as before it died and the gas units are determined by initial_gas().

As a final consideration regarding collisions, when in a round a car (or a missile) moves from an initial cell to a final cell, in some cases it is considered that it also passes certain intermediate cells. More specifically:

When a car moves from cell (i, j) to cell (i+1, j+1), it also passes through cells (i+1,j) and (i, j+1). Similarly when it moves to cell (i−1, j+1).
When a car (or a missile) moves from cell (i, j) to cell (i, j+2), it also passes through cell (i, j+1).
When a car moves from cell (i, j) to cell (i+1, j+2), it also passes through cells (i,j+1), (i+1, j+1), (i+1, j) and (i, j+2). Similarly when it moves to (i−1, j+2).
In the other cases it does not pass through intermediate cells.
The exact order in which intermediate cells are visited can be looked up in the map dir2all defined in Utils.cc.

1.3  Order of execution of instructions
After the instructions of all players are collected, the following actions take place:

First missiles already shot are moved according to their rules.
Next a random order is determined among the players, and the instructions for their cars are executed following this order. Instructions given by the same player are executed in their original order. Invalid instructions (for example, moving outside the window limits) are ignored. If a car receives more than one instruction, only the first one will be taken into account. Cars that have not received any instruction will move by default, in increasing order of identifier.
After all instructions are executed, all cars that are alive have their gas units decremented by one. After that, any car with 0 gas units is killed.
If appropriate, dead cars and new bonuses (in this order) are regenerated.
1.4  Game parameters

A game is determined by following set of parameters. All of them are specified in the input file, but some of them will always have the same value:

number_players(): number of players in the game. Fixed to 4.
number_rounds(): number of rounds that will be played. Fixed to 300.
number_rows(): number of rows of the universe (and of the window). Variable in [15,20].
number_universe_columns(): number of columns of the universe. Variable in [60,100].
number_window_columns(): number of columns of the window. Variable in [30,40].
number_cars_per_player(): number of cars for each player. Fixed to 2.
number_cars(): total number of cars. Fixed to 8.
number_rounds_to_regenerate(): number of rounds to wait before a car can regenerate. Fixed to 30.
number_missile_bonuses(): number of missile bonuses in the game. Variable in [5,30].
number_water_bonuses(): number of water bonuses in the game. Variable in [20,150].
number_gas_bonuses(): number of gas bonuses in the game. Variable in [5,15].
bonus_missiles(): number of extra missiles obtained when consuming a missile bonus. Fixed to 5.
bonus_gas(): number of extra gas units obtained when consuming a gas bonus. Fixed to 30.
water_points(): number of extra points obtained when consuming a water bonus. Fixed to 10.
kill_points(): number of points obtained when killing a car of another player. Fixed to 30.
initial_gas(): number of gas units given to a car when it is regenerated. Fixed to 60.

All these parameters can be accessed by the players during the game.

2  Programming
The first thing you should do is to download the source code. This source code includes a C++ program that runs the matches and also an HTML5/Javascript viewer to watch them in a nice animated format. Also, a ”Demo” player is provided to make it easier to start coding your own player.

2.1  Running your first match
Here we will explain how to run the game under Linux, but a similar procedure should work as well under Windows, Mac, FreeBSD, OpenSolaris... The only requirements on your system are g++, make and a modern browser like Mozilla Firefox or Chromium.

To run your first match, follow the next steps:

Open a console and cd to the directory where you extracted the source code.
If, for example, you are using a 64-bit Linux version, run:
cp AIDummy.o.Linux64 AIDummy.o

If you use any other architecture, choose the right object you will find in the directory.

Run make all to build the game and all the players. Note that the Makefile will identify as a player any file matching the expression ”AI*.cc”.
The call to make should create an executable file called Game. This executable allows you to run a match as follows:
./Game Demo Demo Demo Demo -s 3424 < default.cnf > default.res

Here, we are starting a match with 4 instances of the player ”Demo” (included with the source code), with the game configuration defined in ”default.cnf”. The output of this match will be stored in ”default.res”. A random seed of 3424 will be used in this run.

To watch the match, open the viewer (viewer.html) with your browser and load the ”default.res” file.

Use


./Game --help
to see the list of parameters that you can use. Particularly useful is


./Game --list
to show all the available players.


If needed, remember you can run make clean to delete the executable and all object files and start over the build.

2.2  Adding your player
To create a player, copy the file AINull.cc (an empty player that is provided as a template) to a new file with the same name format (AIWhatever.cc).


Then, edit the file you just created and change the playername line to your own player name, as follows:

#define PLAYER_NAME Whatever
The name you choose for your player must be unique, non-offensive and less than 12 letters long. It will be used to define a new class PLAYER_NAME, which will be referred to below as your player class. The name will be shown as well when viewing the matches and on the website.


Now you can start implementing the method play(). This method will be called every round and is where your player should decide what to do, and do it. Of course, you can define auxiliary methods and variables inside your player class, but the entry point of your code will always be this play() method.


From your player class you can also call functions to access the board state, as defined in the Board class in Board.hh, and to command your units, as defined in the Action class in Action.hh. These functions are made available to your code using multiple inheritance via the class Player in Player.hh . The documentation on the available functions can be found in the aforementioned header files of each class. You can also examine the code of the “Demo” player in AIDemo.cc as an example of how to use these functions. Finally, it may be worth as well to have a look at the file Utils.hh for useful data structures.


Note that you should not modify the factory() method from your player class, nor the last line that adds your player to the list of available players.

2.3  Playing against the Dummy player
To test your strategy against the Dummy player, we provide the object file for it. This way you still will not have the source code of our Dummy, but you will be able to add it as a player and compete against it locally.


To add the Dummy player to the list of registered players, you will have to edit the Makefile file and set the variable DUMMY_OBJ to the appropriate value. Remember that object files contain binary instructions targeting a specific machine, so we cannot provide a single, generic file.
