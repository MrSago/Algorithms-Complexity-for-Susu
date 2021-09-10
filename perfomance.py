
from time import time_ns


def main():
    cnt = int(1e9)
    ops = cnt * 3
    i = 0

    print("Test started...",end='')
    start = time_ns()

    while i < cnt:
        i = i + 1

    stop = time_ns()
    print("\nDone!")

    t = (stop - start) * 1e-9
    print(f"time: {t} sec")
    print(f"ops: {ops}")
    print(f"perfomance: {ops // t} ops/sec")


if __name__ == "__main__":
    main()

