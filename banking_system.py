class BankAccount:
    def __init__(self, account_holder, balance=0.0):
        self.account_holder = account_holder
        self.balance = balance
        self.tax_rate = 0.02  # 2% tax on withdrawals

    def deposit(self, amount):
        if amount > 0:
            self.balance += amount
            print(f"Deposited: ${amount:.2f}")
        else:
            print("Deposit amount must be positive!")
        self.display_balance()

    def withdraw(self, amount):
        if amount <= 0:
            print("Withdrawal amount must be positive!")
            return
        
        tax = amount * self.tax_rate
        total_deduction = amount + tax

        if total_deduction > self.balance:
            print("Insufficient funds!")
        else:
            self.balance -= total_deduction
            print(f"Withdrawn: ${amount:.2f}")
            print(f"Tax Deducted: ${tax:.2f}")
        self.display_balance()

    def display_balance(self):
        print(f"Account Balance: ${self.balance:.2f}\n")


if __name__ == "__main__":
    my_account = BankAccount("Amit", 1000)
    my_account.display_balance()
    
    my_account.deposit(500)
    my_account.withdraw(200)
    my_account.withdraw(2000)  # Should show insufficient funds
