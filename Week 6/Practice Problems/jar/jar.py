class Jar:
    def __init__(self, capacity=12):
        if capacity <= 0:
            raise ValueError ("Capacity value can't be negative")
        self._capacity = capacity
        self._n = 0

    def __str__(self):
        return "🍪" * self._n

    def deposit(self, n):
        if self._n + n > self.capacity:
            raise ValueError ("Number of cookies exceeds the jar caapacity")
        self._n += n

    def withdraw(self, n):
        if self._n < n:
            raise ValueError ("You tried to remove more cookies than the number of cookies in the cookie jar")
        self._n -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


my_jar = Jar()
my_jar.deposit(3)
my_jar.withdraw(5)
print(my_jar)