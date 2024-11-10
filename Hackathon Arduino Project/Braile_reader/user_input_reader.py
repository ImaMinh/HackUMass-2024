import serial
import time
import os

# Establish serial connection with the correct port and baud rate
ser = serial.Serial('COM6', 9600)  # Adjust 'COM6' to match your port

file_path = 'C:\\Users\\handu\\Codes\\Hackathon Arduino Project\\Braile_reader\\braille_doc.txt'
last_position = 0  # Track the last read position
last_mod_time = os.path.getmtime(file_path)  # Track the last modification time

try:
    while True:
        current_mod_time = os.path.getmtime(file_path)
        
        # If file was modified, reset reading position only if file was truncated
        if current_mod_time != last_mod_time:
            last_mod_time = current_mod_time
            current_size = os.path.getsize(file_path)
            if current_size < last_position:
                last_position = 0  # Reset only if file was truncated

        with open(file_path, 'r') as file:
            file.seek(last_position)  # Move to the last known read position
            
            # Read new characters
            new_chars = file.read()
            last_position = file.tell()  # Update the last read position

            # Check for quit signal and send new characters to Arduino
            for char in new_chars:
                print("char:", char)
                if char.isalpha():  # Only send letters
                    ser.write(char.upper().encode())  # Send uppercase
                    time.sleep(2)  # Wait between letters
                elif char == "~":  # Use '~' as quit signal
                    print("Quit signal received. Closing program. Thankyou!")
                    file.close()
                    with open(file_path, 'w') as f:
                        f.write('')  # Write an empty string to the file
                    ser.close()
                    exit(0)  
        
        time.sleep(1)  # Check for changes every second
finally:
    ser.close()
    exit(0)
    