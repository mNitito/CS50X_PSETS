from cs50 import get_string, get_int

# prompt the user for the input
while (True):
    credit_number = get_int("Enter the number:")
    if (credit_number > 0):
        break


# calculate the checksum
str_num = str(credit_number)
card = 0

# for calclating the sum of odd cards
sum_even_cards = 0
for digit in str_num[::2]:
    card = int(digit) * 2
    tens = card // 10
    ones = card % 10
    sum_even_cards = sum_even_cards + (tens + ones)

# for calclating the sum of odd cards
sum_odd_cards = 0
for digit in str_num[1::2]:
    card = int(digit)
    sum_odd_cards = sum_odd_cards + card


check_sum = sum_even_cards + sum_odd_cards

# check the checksum
if ((sum_even_cards + sum_odd_cards) % 10 != 0):
    print("INVALID")

# check the type of the card
if (len(str_num) == 15 and (str_num.startswith('34') or str_num.startswith('37'))):
    print("AMEX")

elif ((len(str_num) == 13 or len(str_num) == 16) and (str_num.startswith('4'))):
    print("VISA")

elif (len(str_num) == 16 and (str_num.startswith('51') or str_num.startswith('52') or str_num.startswith('53') or str_num.startswith('54') or str_num.startswith('55'))):
    print("MASTERCARD")

else:
    print("INVALID")
