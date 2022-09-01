/*
 * CommandLine.cpp is used to connect command-line-arguments with Accounts
*/

#include <iostream>
#include <sstream>
#include <string>
#include <list>

#include "CommandLine.h"
#include "BankAccount.h"

CommandLine::CommandLine() {
    _accounts = new Accounts();
    _runningFlag = true;
	_cmdList = _defineCommands();
};

CommandLine::~CommandLine(){
    delete _accounts;

    std::list<cli *>::iterator ii;
    for (ii = _cmdList.begin(); ii != _cmdList.end(); ++ii) {
        cli *c = *ii;
        delete c;
    }
}


bool CommandLine::askAndDo() {
    _showMenu();
    std::string query;
    std::cin >> query;
    std::cout << _parseInput(query);
    return _runningFlag;
}

void CommandLine::_showMenu() {
    std::cout << std::endl
              << "O: open account, "
              << "D: deposit money, "
              << "W: make a withdraw, "
              << "C: close account, "
              << "P: print balances, "
              << "Q: quit"
              << std::endl;
}

std::string CommandLine::_upperCase(std::string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}

bool CommandLine::_checkAccountNumber(short account) {
    std::list<BankAccount *> a = _accounts->listAccounts();
    std::list<BankAccount *>::iterator ii;
    for (ii = a.begin(); ii != a.end(); ++ii) {
        BankAccount *accountInfo = *ii;
        if (account == accountInfo->getAccountNumber()) {return true;}
    }
    return false;
}

std::string CommandLine::_parseInput(std::string c) {
    std::list<cli *>::iterator ii;
	for (ii = _cmdList.begin(); ii != _cmdList.end(); ++ii) {
        cli *cmd = *ii;

		if (cmd->command == _upperCase(c)) {
			std::string response = (this->*cmd->action)(c);
            return response;
		}
		else if (c == "") {return "\n";}
	}
    std::stringstream ss;
	ss << "\tCommand '" << c << "' is not implemented." << std::endl;
	return ss.str();
}

short CommandLine::_getAccountNumber(void) {
    short aNum = 0;
    std::stringstream ss;
    ss << _printAccountInfo();
    if ( size(_accounts->listAccounts()) ) {
        ss << "Choose an account number (type c to cancel):  ";
        std::cout << ss.str();
        std::cin >> aNum;
        if ( !aNum ) {
            std::cin.clear();
            return 0;
        }
        while ( ! _checkAccountNumber(aNum) ) {
            std::cout << aNum << " is not a valid account number.  Type 'c' to cancel." << std::endl;
            std::cout << "Choose an account number:  ";
            std::cin >> aNum;
            if ( !aNum ) {
                std::cin.clear();
                return 0;
            }
        }
    }
    else {
        std::cout << "No accounts.  Use 'O' to open an account." << std::endl;
    }
    return aNum;
}

std::list<CommandLine::cli *> CommandLine::_defineCommands(void) {
	std::list<cli *> cmdList;

	cli *cOpen = new cli();
	cOpen->command = "O";
	cOpen->action = &CommandLine::_open;
	cmdList.push_back(cOpen);

	cli *cDeposit = new cli();
	cDeposit->command = "D";
	cDeposit->action = &CommandLine::_deposit;
	cmdList.push_back(cDeposit);

	cli *cWithdraw = new cli();
	cWithdraw->command = "W";
	cWithdraw->action = &CommandLine::_withdraw;
	cmdList.push_back(cWithdraw);

	cli *cClose = new cli();
	cClose->command = "C";
	cClose->action = &CommandLine::_close;
	cmdList.push_back(cClose);

	cli *cPrint = new cli();
	cPrint->command = "P";
	cPrint->action = &CommandLine::_printAccountInfo;
	cmdList.push_back(cPrint);

	cli *cQuit = new cli;
	cQuit->command = "Q";
	cQuit->action = &CommandLine::_quit;
	cmdList.push_back(cQuit);

    return cmdList;
}

std::string CommandLine::_open(std::string c) {
    std::stringstream ss;
    std::cout << "Enter an initial amount:  $";
    double cash;
    std::cin >> cash;
    if ( cash ) {
        short aNum;
        aNum = _accounts->create(cash);
        ss << "Opened account number " << aNum << " with  an initial deposit of $" << cash << std::endl;
    }
    else {
        ss << "Failed to open an account.  Must make an initial deposit." << std::endl;
    }
    return ss.str();
}

std::string CommandLine::_deposit(std::string c) {
    std::stringstream ss;
    short aNum = _getAccountNumber();
    if (aNum == 0) {
        return "";
    }
    std::cout << "Enter deposit amount:  $";
    double cash;
    std::cin >> cash;
    short e = _accounts->deposit(aNum, cash);
    if (e > 0) {
        return "";
    }
    ss << "Account " << aNum << " now has $" << _accounts->balance(aNum) << std::endl;
    return ss.str();
}

std::string CommandLine::_withdraw(std::string c) {
    short aNum = _getAccountNumber();
    if (aNum == 0) {
        return "";
    }
    std::cout << "Enter withdraw amount:  $";
    double cash;
    std::cin >> cash;
    short e = _accounts->withdraw(aNum, cash);
    if (e > 0) {
        return "";
    }
    std::stringstream ss;
    ss << "Account " << aNum << " now has $" << _accounts->balance(aNum) << std::endl;
    return ss.str();
}

std::string CommandLine::_close(std::string c) {
    short aNum = _getAccountNumber();
    if (aNum == 0) {
        return "";
    }
    short e = _accounts->close(aNum);
    if (e > 0) {return "";}
    std::stringstream ss;
    ss << "Closed account " << aNum << "." << std::endl;
    return ss.str();
}

std::string CommandLine::_printAccountInfo(std::string c) {
    return _printAccountInfo();
}
std::string CommandLine::_printAccountInfo(void) {
    std::stringstream ss;
    if ( size(_accounts->listAccounts()) ) {
        _accounts->printHeader(ss);
        _accounts->printInfo(ss);
    }
    else {
        ss << "No accounts.  Use 'O' to open an account." << std::endl;
    }
    return ss.str();
}

std::string CommandLine::_quit(std::string c) {
    _runningFlag = false;
	return "Quitting...\n";
}
