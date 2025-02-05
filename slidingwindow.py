import random
import time
def sliding_window_sender(total_packets):
    window_size = int(input("Enter the window size: "))
    next_packet = 0
    while next_packet < total_packets:
        window = list(range(next_packet, min(next_packet + window_size, total_packets)))
        print(f"\nCurrent window: {window}")
        for i in range(window_size):
            if next_packet < total_packets:
                print(f"Sender: Sending packet {next_packet}")
                if sliding_window_receiver(next_packet):
                    print(f"Sender: Acknowledgment received for packet {next_packet}")
                    next_packet += 1
                else:
                    print(f"Sender: Packet {next_packet} failed, retransmitting window")
                    break 
        time.sleep(1)
def sliding_window_receiver(packet):
    if random.random() > 0.3:
        print(f"Receiver: Packet {packet} received successfully")
        return True
    else:
        print(f"Receiver: Packet {packet} lost or corrupted")
        return False
total_packets =int(input("Enter the number of packets to be transferred: "))
sliding_window_sender(total_packets+1)
