# Banker's Challenge
***
---
### [The Challenge](https://twitter.com/moshhamedani/status/1563558716787421185?s=20&t=y56VC9N_5jaGoz2oDAS9xg)
On August 27, 2022, Mosfegh Hamedani issued the following challenge:

>I want you to create a console-based application with a menu for opening a bank account, closing one, listing all accounts and their balances, depositing and withdrawing money. To close an account, withdraw or deposit, you should ask for the account number first.

### My Solution
To start the code, go to a command prompt and type: 
```sh
./BankersChallenge
```
Once the code starts, it presents a menu of options to open/close an account, deposit to/withdraw from and account, and print the value of each accounts.

### Planning
Below are the classes that I planned on using.  The Accounts class is the meat of the program, while BankAccount is a class which holds information specific to an individual bank account.  The Accounts class will instantiate a new BankAccount whenever it is asked to create() and new account.  

In order to interact with a user, one uses the CommandLine class.  This defines the commands presented to the user, and works with the Accounts class to do work.
- BankAccount
    - accountNumber - This can be created at instantiation
    - balance()
    - deposit()
    - withdraw()
- Accounts
    - create()
    - deposit()
    - withdraw()
    - close()
    - printResults()
    - This has a list to hold all open BankAccounts
- CommandLine
    - askAndDo()
        - This interprets the response and calls the appropriate method in Accounts.
    - cli is a struct that holds the string that defines the command, and it holds a pointer to a member method to do the task.  This function returns a string, and the method askAndDo() will print the result to the command line.
    - _defineCommands() is a protected member method to put all of the possible commands inside a list.
    - _parseInput() is a protected member which goes through the list of commands to see if it can find what the user entered.  If it does, then it will call the associated method and return the response.
