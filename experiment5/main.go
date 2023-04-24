package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"rsa/tool"
	"strconv"
	"time"
)

func main() {
	rand.Seed(time.Now().UnixNano())
	var upper_limit int64 = 71112175
	p, q := tool.Return2LargestPrime(upper_limit)
	prime_pair := tool.NUM_PAIR{p, q} // 得到两个大质数
	n := prime_pair.P * prime_pair.Q  // 两个质数乘积n
	phi_n := tool.Phi2(prime_pair)    // 得到φ(n)
	var e int64
	for true {
		e = int64(rand.Intn(int(phi_n-1)) + 1)
		tmp_pair := tool.NUM_PAIR{e, phi_n}
		if tmp_pair.Gcd() == 1 {
			break
		}
	} // 随机生成一个e，满足(e,φ(n)) = 1
	d := tool.GetReverseOfMod(e, phi_n) // 计算d，其中 ed ≡ 1 (mod φ(n))

	pk := tool.KEY{e, n}
	sk := tool.KEY{d, n}

	// tool.RSAEncrypt(id, pk)
	// tool.RSADecryptSpeedUp(encrypted_data, sk, prime_pair)
	fmt.Println("input the string to encrypt:")
	input := bufio.NewScanner(os.Stdin)
	input.Scan()
	data := input.Text()
	// data := "hello this is redh3t testing rsa."
	ciper := "#"
	for _, r := range data {
		e := tool.RSAEncrypt(int64(r), pk)
		ciper = ciper + strconv.FormatInt(e, 10) + "#"
	}
	fmt.Println("CIPERTEXT is: ", ciper)

	// var test string = "4285253563253"
	// fmt.Println()
	// iiii, _ := strconv.ParseInt(test, 10, 64)
	// fmt.Println(iiii)
	// fmt.Println(string(97))

	var word string
	var result string
	for _, r := range ciper {
		if r == '#' {
			if word == "" {
			} else {
				i, e := strconv.ParseInt(word, 10, 64)
				if e != nil {
					fmt.Println(i)
					panic("invalid str to int")
				} else {
					result = result + string((tool.RSADecrypt(i, sk)))
				}
				word = ""
			}
		} else {
			word = word + string(r)
		}
	}
	fmt.Println(result)
}
