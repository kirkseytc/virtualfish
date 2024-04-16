# Virtual Fish
A virtual fish tank in your terminal using the ncurses library.

## Install
To compile and install this program you need to make sure you have the ncurses-6.4 library installed.

If you already have it installed you can skip to step 3.

### 1. Downloading ncurses
Run this command from your terminal to download ncurses.
```bash
wget https://invisible-island.net/archives/ncurses/ncurses-6.4.tar.gz
```

### 2. Installing ncurses
In the same directory that you downloaded "ncurses-6.4.tar.gz", run this command to extract the tar.gz
```bash
tar -xzf ncurses-6.4.tar.gz
```
This will create a folder called "ncurses-6.4".

Change Directory (or cd) into the new folder with this command:
```bash
cd ncurses-6.4
```

Next run this command to set-up the make enviornment:
```bash
./configure
```

Next run this command to compile the library:
```bash
make
```

Finally run this command to install the library:
```bash
sudo make install
```

If you want to, at this point you can delete the tar.gz file along with the folder as well.

### 3. Installing virtualfish
Download the lastest release and unzip the folder.

Next change directiory into the folder and run the install command:
```bash
sudo make install
```

## Usage
To use the program, run this command in your terminal.
```bash
virtualfish
```

When the program runs you will be greated with an empty tank. Run some commands to bring life into it.

### Commands
To enter a command, press the esc key and type the command you want.

#### Fish
This command will spawn one fish.

Alias: f

#### Quit
This command will quit out the program

Aliases: q, exit

#### Max
This command will spawn in the max amount of fishes.

Alias: m

#### Clear
This command will remove all current fish.

Alias: c

#### Volcano
This command will enable the volcano in the corner.

Alias: v

## Release Notes
Version 1-0-0:
    The basic version of this program with base features.

Version 1-1-0:
    Added more commands and the volcano feature.

## Issues/Bugs
If you run into any major bugs, open an issue tracker and I'll try and get to it.
This was a little pet project, so I'm not planning on doing any code upkeep to keep it compatiable.
If anyone else wants to do that, be my guest and fork the repo.
