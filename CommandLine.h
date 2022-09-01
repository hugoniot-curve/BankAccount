/*
 * CommandLine.h is used to connect command-line-arguments with Accounts
*/

#pragma once

#include <iostream>
#include <list>

#include "Accounts.h"


class CommandLine {
public:
    CommandLine();
    ~CommandLine();

	struct cli {
		std::string command;
		std::string (CommandLine::*action)(std::string command);
	};

    bool askAndDo(void);

protected:
    Accounts *_accounts;
	std::list<cli *> _cmdList;
    bool _runningFlag;

	std::list<cli *> _defineCommands(void);
    void _showMenu(void);
	std::string _parseInput(std::string command);
    short _getAccountNumber(void);
    std::string _upperCase(std::string command);
    bool _checkAccountNumber(short account);

    std::string _open(std::string command);
    std::string _deposit(std::string command);
    std::string _withdraw(std::string command);
    std::string _close(std::string command);
    std::string _printAccountInfo(std::string command);
    std::string _printAccountInfo(void);
    std::string _quit(std::string command);
};
