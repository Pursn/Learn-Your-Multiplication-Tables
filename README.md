# Learn-Your-Multiplication-Tables
Since my American elementary school failed me as a child, I never fully learned my multiplication tables. I have decided: why not practice C and learn my multiplication tables by making my very own program?

## Install the basic development tools needed to code in C.
### Fedora
```
sudo dnf install @development-tools
```

### Debian/Ubuntu
```
sudo apt install build-essential
```

### Brew/macOS Notes
This should work on macOS using Brew, IDK.

## Building
Download this repo by opening your terminal and running the following command.
```
git clone https://github.com/Pursn/Learn-Your-Multiplication-Tables.git
```
This will just copy all the files of this repo to your home directory or wherever your current directory is stated in your terminal prompt.

Go to the repo's directory by using this command:
```
cd Learn-Your-Multiplication-Tables
```

Building this project is super easy since every command needed will be in the Makefile. 

In the repo's directory, build the project by typing:
```
make install
```
To run it, you can type:
```
lymt
```
To remove the executable if you don't want it anymore or if you are recompiling, use this:
```
make clean
```
