from pyfiglet import Figlet
figlet = Figlet()
import sys


f = sys.argv[2]
if len(sys.argv) != 3 and len(sys.argv) != 1:
    print("Invalid usage")
    sys.exit(1)
else :
    if len(sys.argv) == 3 :
        flag = False
        for name in figlet.getFonts() :
            if name == f :
                flag = True
        if flag == False or ( sys.argv[1] != "-f" and sys.argv[1] != "--font") :
            print("Invalid usage")
            sys.exit(1)
        else :
            figlet.getFonts()
            figlet.setFont(font = f)


    s = input("Input: ")
    print(figlet.renderText(s))



