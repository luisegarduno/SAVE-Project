import regex as re
import pandas as pd
import copy

# Load CSV's into seperate DataFrames
transactions = pd.read_csv('./OriginalDatasets/transactions.csv')
account_info = pd.read_csv('./OriginalDatasets/account_info.csv')

# Trim whitespace from headers
for a in transactions.columns: transactions.rename(columns={a: a.strip()}, inplace=True)
for b in account_info.columns: account_info.rename(columns={b: b.strip()}, inplace=True)

# Fix 'dob' format to import column datatype as 'DATE' in MySQL

# ----- Part 1/2: Append leading zero to months & days
account_info['dob'] = [re.sub(r'\b(\d)(?=/)', r'0\1',
                              str(x)) for x in account_info['dob']]

# ----- Part 2/2: sort to correct format (YYYY-MM-DD) 
account_info['dob']= [re.sub(r'(\d{1,2})/(\d{1,2})/(\d{4})', '\\3-\\1-\\2',
                             str(x)) for x in account_info['dob']]

# Remove 'US' ------------------------------------------------------
d = transactions.merchant_description
t2 = transactions[['merchant_description']].copy(deep=True)

for c in range(len(transactions)):
    if d[c][(len(d[c]) - 2):] == 'US':
        t2.merchant_description[c] = d[c][:-2]

transactions.drop(['merchant_description'], axis=1)
transactions['merchant_description'] = t2

# Create State Column ---------------------------------------------
transactions['merchant_state'] = ''
t3 = transactions[['merchant_state']].copy(deep=True)

for c in range(len(transactions)):
    t3.merchant_state[c] = transactions.merchant_description[c][(len(transactions.merchant_description[c]) - 2):]

transactions.drop(['merchant_state'], axis=1)
transactions['merchant_state'] = t3

# Export tables to new files.
transactions.to_csv('transactions.csv', index=False)
account_info.to_csv('account_info.csv', index=False)
