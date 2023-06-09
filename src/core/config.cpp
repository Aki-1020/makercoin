#include "config.hpp"
#include "helpers.hpp"
#include "crypto.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <thread>
using namespace std;

json getConfig(int argc, char**argv) {
    cout<<"======================"<<endl;
    cout<<"      MakerCoin       "<<endl;
    cout<<"======================"<<endl;


    std::vector<std::string> args(argv, argv + argc);  
    // should read from config when available
    std::vector<string>::iterator it;
    bool testnet = false;
    bool local = false;
    bool rateLimiter = true;
    bool firewall = false;
    string customWallet = "";
    string customIp = "";
    string customName = randomString(25);
    string networkName = "mainnet";
    json hostSources = json::array();
    json checkpoints = json::array();
    json bannedHashes = json::array();
    int customPort = 3001;
    int threads = std::thread::hardware_concurrency();
    int thread_priority = 0;

    if (threads == 0) {
        threads = 1;
    }

    it = std::find(args.begin(), args.end(), "-t");
    if (it != args.end()) {
        threads = std::stoi(*++it);
    }

    it = std::find(args.begin(), args.end(), "--wallet");
    if (it++ != args.end()) {
        customWallet = string(*it);
    }

    it = std::find(args.begin(), args.end(), "--priority");
    if (it != args.end()) {
        thread_priority = std::stoi(*++it);
    }

    it = std::find(args.begin(), args.end(), "-ip");
    if (it++ != args.end()) {
        customIp = string(*it);
    }


    it = std::find(args.begin(), args.end(), "-n");
    if (it++ != args.end()) {
        customName = string(*it);
    }

    it = std::find(args.begin(), args.end(), "-p");
    if (it++ != args.end()) {
        customPort = std::stoi(*it);
    }

    it = std::find(args.begin(), args.end(), "--network-name");
    if (it++ != args.end()) {
        networkName = string(*it);
    }

    it = std::find(args.begin(), args.end(), "--host-source");
    if (it++ != args.end()) {
        hostSources.push_back(string(*it));
    }

    it = std::find(args.begin(), args.end(), "--testnet");
    if (it != args.end()) {
        networkName = "testnet";
        testnet = true;
        local = false;
    } 

    it = std::find(args.begin(), args.end(), "--local");
    if (it != args.end()) {
        networkName = "localnet";
        local = true;
        testnet = false;
    }

    if (networkName == "testnet") {
        //checkpoints.push_back({1, "0840EF092D16B7D2D31B6F8CBB855ACF36D73F5778A430B0CEDB93A6E33AF750"});
    }

    if (networkName == "mainnet") {
        //checkpoints.push_back({1, "0840EF092D16B7D2D31B6F8CBB855ACF36D73F5778A430B0CEDB93A6E33AF750"});
        //bannedHashes.push_back({143799,"60D84E0D3078F3FFD9E54133B450448F3F12B671028B0431F775A37A347FFACA"});
    }

    it = std::find(args.begin(), args.end(), "--disable-limiter");
    if (it != args.end()) {
        rateLimiter = false;
    }

    it = std::find(args.begin(), args.end(), "--firewall");
    if (it != args.end()) {
        firewall = true;
    }

    json config;
    config["rateLimiter"] = rateLimiter;
    config["threads"] = threads;
    config["wallet"] = customWallet;
    config["port"] = customPort;
    config["name"] = customName;
    config["networkName"] = networkName;
    config["firewall"] = firewall;
    config["checkpoints"] = checkpoints;
    config["bannedHashes"] = bannedHashes;
    config["ip"] = customIp;
    config["thread_priority"] = thread_priority;
    config["hostSources"] = hostSources;
    config["minHostVersion"] = "0.7.13-beta";
    config["showHeaderStats"] = true;

    if (local) {
        // do nothing
    } else if (testnet) {
        config["hostSources"].push_back("http://212.147.106.225:3002/peers");
    } else {
        config["hostSources"].push_back("http://212.147.106.225:3001/peers");
    }
    return config;
}
