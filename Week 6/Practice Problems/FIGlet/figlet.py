import sys
from pyfiglet import Figlet

# Generate ASCII art with a random font
def generate_random_font(text):
    figlet = Figlet()
    ascii_figlet = figlet.renderText(text)
    print("Output: ", ascii_figlet)

# Generate ASCII art with the specified font
def generate_text_with_specific_font(text, font):
        figlet = Figlet(font=font)
        ascii_figlet = figlet.renderText(text)
        print(ascii_figlet)

# Check if the specified font is valid
def validate_font(font):
    # Create an instance of Figlet
    figlet = Figlet()
    # Check if font exists in the available fonts
    if font in figlet.getFonts():
        text = input("Input: ")
        generate_text_with_specific_font(text, font)
    else:
        sys.exit(f"Error - Font '{font}' is not a valid font.")


def main():
    args = sys.argv[1:]
    num_args = len(args)

    # Check the number of arguments
    if num_args == 0:
        # No arguments, so print input text with random font
        figlet_input = input("Input: ")
        generate_random_font(figlet_input)
    elif num_args == 2 and args[0] in ['-f', '--font']:
        font = args[1]
        # Print input text with the specified font
        validate_font(font)
    else:
        # Invalid command-line arguments usage, so exit with an error message
        sys.exit("Invalid usage")

if __name__ == "__main__":
    main()