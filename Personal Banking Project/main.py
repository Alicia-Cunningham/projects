#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Apr  9 16:00:46 2025

@author: aliciacunningham
"""
""" Class Based Banking System """

import json

class Transaction:
    def __init__(self, title, amount, type, note=""):
        self.title = title
        self.amount = amount
        self.type = type
        self.note=note
    
    def display_info(self):
        return f"Transaction:\n Expense: {self.title}\n Amount: {self.amount}\n Type: {self.type}\n Note: {self.note}"

class Bank:
    def __init__(self):
        self.wallet= []
    
    def add_transaction(self, transaction):
        self.wallet.append(transaction)
    
    def del_transaction(self, title):
        for trans in self.wallet:
            if trans.title == title:
                self.wallet.remove(trans)
                return f"{title} has beem removed!"
        return f"{title} was not found."
    
    def display(self):
        if not self.wallet:
            return f"No transactions available in your wallet."
        return f"\n".join([transaction.display_info() for transaction in self.wallet])
    
    def search_wallet(self, query):
        found = [trans for trans in self.wallet if query.lower() in trans.title.lower() or query.lower() in trans.type.lower()]
        if not found:
            return f"No Transactions!"
        return "\n".joint([transaction.display_info() for transaction in found])
    
    def save_file(self, filename="wallet.json"):
        data=[{'Expense': transaction.title, 'Amount': transaction.amount, 'Type': transaction.type, 'Note': transaction.note}for transaction in self.wallet]
        with open(filename, 'w') as file:
            json.dump(data, file)
    
    def load_file(self, filename="wallet.json"):
        try:
            with open(filename, "r") as file:
                data = json.load(file)
                self.wallet = [Transaction(trans['title'], trans['amount'], trans['type'], trans['note']) for trans in data]
        except FileNotFoundError:
            print("We don't have the file...")




def main():
    wallet = Bank()
    print("\n Welcome to ")
    print("\n==== Mobile Banking System ====")
    while True:
        print("\n___What can we do for you today?____")
        print("1. Add a Transaction")
        print("2. Remove a Transaction")
        print("3. Display all Transactions")
        print("4. Seacrh for a Transaction")
        print("5. Save Transaction to a file")
        print("6. Load Transactions from a file")
        print("7. Exit")
        choice = input("Please enter your choice (1-7): ")
        
        if choice == "1":
            title = input("Enter the title: ")
            amount=float(input("Enter Amount: "))
            type = input("Withdrawl or Deposit: ")
            transaction = Transaction(title, amount, type)
            wallet.add_transaction(transaction)
            print(f"{title} added successfully!")
        elif choice == "2":
            title = input("Enter the title: ")
            wallet.remove_transaction(title)
            print(f"{title} removed successfully!")
        elif choice == "3":
            print(wallet.display())
        elif choice == "4":
            query = input("Enter the title: ")
            print(wallet.search_wallet(query))
        elif choice == "5":
            wallet.save_file()
            print("Saved as JSON")
        elif choice == "6":
            wallet.load_file()
            print("Loaded JSON")
        elif choice == "7":
            print ("Exiting Program. Thank you for using \n======= Mobile Banking System =======")
            break
        else:
            print("Invalid Choice. Please Try Again")

if __name__ in "__main__":
    main()