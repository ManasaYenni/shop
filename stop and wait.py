
import random
import time
def sender(packet, max_retries=5):
    for attempt in range(max_retries):
        print(f"Sender: Sending packet {packet}")
        if receiver(packet):
            print(f"Sender: Received ACK for packet {packet}")
            return True
        else:
            print(f"Sender: No ACK received, retrying...")
            time.sleep(1)
    print(f"Sender: Failed to send packet {packet} after {max_retries} attempts.")
    return False
def receiver(packet):
    if random.random() > 0.3:
        print(f"Receiver: Packet {packet} received successfully")
        return True
    else:
        print(f"Receiver: Packet {packet} lost or corrupted")
        return False
n=int(input("Enter the number of packets to be transmitted: "))
for packet in range(1, n+1):
    sender(packet)
