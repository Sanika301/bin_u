def is_prime(n, divisor=2):
    if n <= 1:
        return False
    if n == 2:
        return True
    if n % divisor == 0:
        return False
    if divisor * divisor > n:
        return True
    return is_prime(n, divisor + 1)

def generate_primes(limit, current=2, primes=[]):
    if current > limit:
        return primes
    if is_prime(current):
        primes.append(current)
    return generate_primes(limit, current + 1, primes)

# Example usage:
limit = int(input("Enter the limit for generating prime numbers: "))
print("Prime numbers up to", limit, "are:", generate_primes(limit))
