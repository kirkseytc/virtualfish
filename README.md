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
cd virtualfish && sudo make install
```

## Usage
To use the program, run this command in your terminal.
```bash
virtualfish
```

When you run it you will be greeted with a screen with and outline.
Press the "esc" key to bring up the input field.
In this field you can run a few different commands, but the one you'll need to get started is simply, "fish".
When you type "fish" in this field, it will spawn a fish in the tank. 
You can run this as many times as you want until you reach the fish limit (which is set to 10).

When you want to quit the program, just type "quit" into the input field.

Note: if you type just "f", it equates to the fish command, and the same thing with "q" and quit. "exit" is also a valid alias for the quit command.

## Release Notes
Version 1-0-0:
    The basic version of this program with base features.

## Issues/Bugs
If you run into any major bugs, open an issue tracker and I'll try and get to it.
This was a little pet project, so I'm not planning on doing any code upkeep to keep it compatiable.
If anyone else wants to do that, be my guest and fork the repo.
