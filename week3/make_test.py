import struct

numbers = [2, 7, 500]

with open("test_data", "wb") as f:
    for num in numbers:
        f.write(struct.pack('<Q', num))

print("Binary file 'test_data' created.")