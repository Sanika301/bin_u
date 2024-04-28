def count_word_frequencies(file_path):
    word_freq = {}
    with open(file_path, 'r') as file:
        for line in file:
            words = line.split()
            for word in words:
                word = word.strip(",.!?;:\"()[]")  # Remove punctuation
                word = word.lower()  # Convert word to lowercase
                if word:
                    word_freq[word] = word_freq.get(word, 0) + 1
    return word_freq

def main():
    file_path = input("Enter the path to the text file: ")
    word_freq = count_word_frequencies(file_path)
    print("Word frequencies in the file:")
    for word, freq in word_freq.items():
        print(f"{word}: {freq}")

if __name__ == "__main__":
    main()
