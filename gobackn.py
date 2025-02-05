import random
import time
WINDOW_SIZE = 4
TOTAL_FRAMES = 10
class GoBackN:
    def __init__(self):
        self.base = 0
        self.next_frame_to_send = 0
        self.acks = [False] * TOTAL_FRAMES
    def send_frame(self, frame):
        print(f"Sending frame: {frame}")
        time.sleep(0.1)  
        if random.random() < 0.1:
            print(f"Frame {frame} lost!")
            return False
        print(f"Frame {frame} sent successfully.")
        return True
    def receive_acks(self):
        for i in range(self.base, self.next_frame_to_send):
            if random.random() < 0.8:
                print(f"Acknowledgment received for frame: {i}")
                self.acks[i] = True
    def send(self):
        while self.base < TOTAL_FRAMES:
            while self.next_frame_to_send < self.base + WINDOW_SIZE and self.next_frame_to_send < TOTAL_FRAMES:
                if self.send_frame(self.next_frame_to_send):
                    self.next_frame_to_send += 1
            time.sleep(0.5) 
            self.receive_acks()
            while self.base < TOTAL_FRAMES and self.acks[self.base]:
                self.base += 1
            if self.base == self.next_frame_to_send:
                self.next_frame_to_send = self.base
def main():
    gbn = GoBackN()
    gbn.send()
if __name__ == "__main__":
    main()
