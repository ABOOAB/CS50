import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")

        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")
    # print(new_cases)

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    old_cases = dict()

    for row in reader:
        state = row["state"]
        cases = int(row["cases"])

        if state not in old_cases:
            old_cases[state] = cases
            new_cases[state] = []
        else:
            day_cases = cases - old_cases[state]
            old_cases[state] = cases
            if len(new_cases[state]) >= 14:
                new_cases[state].pop(0)
            new_cases[state].append(day_cases)

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    print(states)
    for state in states:
        previous_avrg = round(sum(new_cases[state][:7]) / 7)
        print(previous_avrg)
        week_avrg = round(sum(new_cases[state][7:]) / 7)
        print(week_avrg)
        try:
            perc = (week_avrg - previous_avrg) / previous_avrg
            print(perc)
        except ZeroDivisionError:
            raise
        perc = round(perc * 100, 2)
        move = "increase"
        if perc < 0:
            move = "decrease"
            perc *= -1
        print(f"{states} had a 7-day average of {week_avrg} and an {move} of {perc}%.")


main()
