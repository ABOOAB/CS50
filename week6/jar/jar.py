class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return "🍪" * self._size

    def deposit(self, n):
        if n + self._size > self._capacity:
            raise ValueError
        self._size = self._size + n

    def withdraw(self, n):
        if self._size - n < 0:
            raise ValueError
        self._size = self._size - n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


def main():
    jar = Jar(10)
    jar.deposit(1)
    print(jar)
    jar.deposit(5)
    print(jar)
    jar.withdraw(4)
    print(jar)


if __name__ == "__main__":
    main()
