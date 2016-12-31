import math
import time

# list to hold primes we know
primes = [2]

def is_prime(s):
    """Function to find if a number is prime

    :param s: Integer to be tested
    :return: True for prime and False for not prime
    """

    # add new primes to this list
    global primes

    # if we already know s prime return True
    if s in primes:
        return True

    # quick check if s divisible by 2
    if s % 2 == 0:
        return False

    divisor = 3
    s_sqrt = math.sqrt(s)
    
    while divisor <= s_sqrt:
        if s % divisor == 0:
            return False
        divisor += 2

    primes.append(s)
    return True

def get_prime_factors(s):
    """Function to find the prime factors

    :param s: an integer we want to find the prime factors of
    :returns: set of prime factors
    """

    global primes 

    p_factors = set()

    # test known primes first
    while s > 1:
        #print(s)
        foundFactor = False 
        for p in primes:
            if s % p == 0:
                p_factors.add(p)
                s = s//p
                foundFactor = True
                break
        if not foundFactor: # not divisible by known primes
            p = primes[len(primes)-1]
            if p == 2:
                p += 1
            else:
                p += 2

            while p <= math.sqrt(s):
                if is_prime(p) and s % p == 0:
                    p_factors.add(p)
                    s = s//p
                    foundFactor = True
                    break
                p += 2
        if not foundFactor and is_prime(s):
            p_factors.add(s)
            break

    return p_factors

def primitive_roots(p):
    """Function to find primitive roots

    :param p: a prime p we want to find the primitive roots of
    :returns: tuple in the form (<first primitive root>, <# primitive roots>)
    """

    s = p-1

    # set of prime factors of s
    p_factors = get_prime_factors(s)
    
    first_primitive = -1
    prim_roots = set()
    powers = []

    # compute powers
    for pf in p_factors:
        powers.append(s//pf)

    # find first primitive root
    a = 2
    while a < p and first_primitive == -1:
        prim = True
        for pi in powers:
            if mod_exp(a, pi, p) == 1:
                prim = False
                break
        if prim:
            first_primitive = a
            prim_roots.add(a)
            break;
        a += 1

    # use totient function to get the number of primitive roots
    tot = totient(s, p_factors)
    
    return first_primitive, tot

def gcd(m,n):
    """Find gcd of two integers

    :param m: integer
    :param n: integer
    :returns: gcd of m and n
    """
    
    if m < n:
        return gcd(n,m)

    if m % n == 0:
        return n
    else:
        return gcd(n, m % n)


def coprime(p,q):
    """Determine if two integers are coprime

    :param p: integer
    :param q: integer
    :returns True if coprime and False if not
    """

    if gcd(p,q) == 1:
        return True
    else:
        return False

def totient(n, prime_factors=None):
    """Euler's totient function finds integers coprime with n in range [1,n)

    :param n: integer
    :param prime_factors: optional set of prime factors of n
    :returns number of integers coprime with n in range [1,n)
    """

    num_coprime = 0

    # Euler's product formula for calculating totient 
    if prime_factors != None:
        num_coprime = n
        for p in prime_factors:
            num_coprime *= (1 - 1/float(p))

    # Brute force
    else:
        for i in range(1, n):
            if coprime(n, i):
                num_coprime += 1

    return round(num_coprime)
  
def mod_exp (a, pi, p):
    """Computes a ** pi mod p
      
    :param a: base integer
    :param pi: exponent
    :param p: prime modulo
    :returns: result of a ** pi mod p
    """
    
    res = 1

    while pi != 0:
        if pi & 1: # exponent isn't a power of 2
            res = (res * a) % p
        pi //= 2
        a = (a * a) % p
    
    return res
 

    
            

    


        
