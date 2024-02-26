text = input("greetin: ")
text = text.lower()
if text.split()[0] == "hello" or text.split()[0] == "hello,":
    print("$0")

elif text[0] == "h":
    print("$20")
else:
    print("$100")
   