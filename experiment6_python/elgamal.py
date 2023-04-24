import random

def generate_keys(p, g):
    sk = random.randint(1, p - 2)
    pk = pow(g, sk, p)
    return (sk, pk)

def encrypt(p, g, pk, plaintext):
    k = random.randint(1, p - 2)
    a = pow(g, k, p)
    b = (pow(pk, k, p) * plaintext) % p
    return (a, b)

def decrypt(p, x, ciphertext):
    a, b = ciphertext # gamma & delta, 直接ab更方便写
    plaintext = (b * pow(a, p-1-x, p)) % p
    return plaintext

def isprime(n):
    if n < 2:
        return False
    for i in range(2, int(n ** 0.5)+1):
        if n % i == 0:
            return False
    return True


def generate_large_prime(bit_length):
    while True:
        p = random.getrandbits(bit_length)
        if isprime(p):
            return p

def find_generator(p): # 按照定义来找
    for g in range(2, p):
        if pow(g, (p-1)//2, p) != 1 and pow(g, p-1, p) == 1:
            return g

p = generate_large_prime(16)
g = find_generator(p)
x, y = generate_keys(p, g)

print("p =", p)
print("g =", g)
print("私钥:", x)
print("公钥:", y)

input_str = input("请输入字符串：")
ascii_list = [ord(char) for char in input_str]
encrypt_list = [encrypt(p,g,y,i) for i in ascii_list]
print(encrypt_list)

print()
print("解密如下：")
decrypt_list = [decrypt(p,x,i) for i in encrypt_list]
string = ''.join([chr(char) for char in ascii_list])
print(string)
