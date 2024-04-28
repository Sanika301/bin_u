from collections import Counter
import os

def get_command_history():
    # Get the path to the user's shell history file
    history_file = os.path.expanduser("~/.bash_history")
    # Read the contents of the history file
    with open(history_file, 'r') as file:
        commands = [line.strip() for line in file]
    return commands

def generate_command_frequency(commands):
    # Generate frequency list of all commands
    command_freq = Counter(commands)
    return command_freq

def main():
    # Get command history
    commands = get_command_history()
    # Generate command frequency list
    command_freq = generate_command_frequency(commands)
    # Get top 5 commands along with their counts
    top_commands = command_freq.most_common(5)
    # Print top 5 commands with counts
    print("Top 5 commands:")
    for command, count in top_commands:
        print(f"{command}: {count}")

if __name__ == "__main__":
    main()
