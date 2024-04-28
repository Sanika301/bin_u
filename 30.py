def display_pyramid(num_lines):
    max_width = num_lines * 2 - 1
    
    for i in range(1, num_lines + 1):
        spaces = ' ' * ((max_width - (i * 2 - 1)) // 2)
        stars = '*' * (i * 2 - 1)
        print(spaces + stars + spaces)

def main():
    num_lines = int(input("Enter the number of lines for the pyramid: "))
    display_pyramid(num_lines)

if __name__ == "__main__":
    main()
