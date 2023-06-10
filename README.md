MakerCoin 
====================

Pandanite fork.

[Pandanite](http://www.bamboocrypto.io) is a minimalist implementation of a layer 1 cryptocurrency similar to Bitcoin. It is designed with utmost simplicity and user friendliness in mind and is written from the ground up in C++ — it isn't yet another re-packaging of existing open-source blockchain code (where's the fun in that?!). 

### Circulation
This coin is minted by miners who earn rewards. Mining payments occur using the *thwothirding* algorithm, which yields a total final circulation of ~99.1M:

- 50 Coin per block at Heights 1 to 666666-1
- 50\*(2/3) Coin per block from blocks 666666 to 2\*666666-1
- 50\*(2/3)^2 Coin per block from blocks 2\*666666 to 3\*666666-1

etc.
#### Comparison with halving
Block reward changes are more often and have less impact compared to halving:
<image src="img/reward.png" width=600/>

The payout curve is smoother in twothirding compared to halving:

<image src="img/circulation.png" width=600/>


### Getting Started
*Windows*: 
Windows is not currently supported as a build environment.

*Mac OSX* build pre-requirements
```
brew install leveldb
brew install cmake
pip3 install conan
```

*Ubuntu 18.04 LTS* install pre-requirements
```
sudo apt update
sudo apt-get -y install make cmake automake libtool python3-pip libleveldb-dev curl git
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.6 1
sudo pip3 install conan==1.59
```

*Ubuntu 20.04 LTS* install pre-requirements
```
sudo apt-get update
sudo apt-get -y install make cmake automake libtool python3-pip libleveldb-dev curl git
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.8 1
sudo pip3 install conan==1.59
```

*Ubuntu 22.04 LTS* install pre-requirements
```
sudo apt-get update
sudo apt-get -y install make cmake automake libtool python3-pip libleveldb-dev curl git
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3.10 1
sudo pip3 install conan==1.59
```

### Building
```
git clone https://github.com/Aki-1020/makercoin
cd makercoin
mkdir build
cd build
conan install .. --build=missing
cd ..
cmake .
```

*Ubuntu 18.04 Requires a code change to build server
in src/server/server.cpp change:
```
Line 10
#include <filesystem>
to
#include <experimental/filesystem>

Lines 50, 52, & 58
std::filesystem::...  
to 
std::experimental::filesystem::...
```


To compile the miner run the following command:
```
make miner
```
You will also need the keygen app to create a wallet for your miner:
```
make keygen
```

To compile the node server:
```
make server
```

To compile a simple CLI tool that lets you send PDN:
```
make cli
```
For a separate, interactive GUI wallet see ... soon

### Usage
Start by generating `keys.json`.

```
./bin/keygen
```
 ***Keep a copy of this file in a safe location*** -- it contains pub/private keys to the wallet that the miner will mint coins to. If you lose this file you lose your coins. We recommend keeping an extra copy on a unique thumbdrive (that you don't re-use) the moment you generate it.

To start mining:
```
./bin/miner
```

To host a node:
```
./bin/server
```

Some server running args:
```
-n (Custom Name, shows on peer list)
-p (Custom Port, default is 3000)
--testnet (Run in testnet mode, good for testing your mining setup)
```
Full list of arguments can be found here: https://github.com/Aki-1020/makercoin/blob/master/src/core/config.cpp

To send Coin to another address (run with --local flag if the server you want to use is listening on localhost):
```
./bin/cli
```
### Mining
Le miner a encore des bugs...
Pour le démarrer sur la même machine que le node:
```
mkdir miner
cd miner
mkdir data
../bin/keygen
../bin/miner --local
```


