package main

import (
	"fmt"
)

func findMultiplicativeGenerator(p uint) (uint, error) {
	phi := p - 1
	factors := primeFactors(phi)

	for i := uint(2); i < p; i++ {
		isGenerator := true
		for _, factor := range factors {
			if modularExponentiation(i, phi/factor, p) == 1 {
				isGenerator = false
				break
			}
		}

		if isGenerator {
			return i, nil
		}
	}

	return 0, fmt.Errorf("no multiplicative generator found for p=%d", p)
}

func primeFactors(n uint) []uint {
	var factors []uint

	for i := uint(2); i <= n; i++ {
		if n%i == 0 {
			factors = append(factors, i)
			n /= i
			i--
		}
	}

	return factors
}

func modularExponentiation(base, exponent, modulus uint) uint {
	result := uint(1)

	for exponent > 0 {
		if exponent%2 == 1 {
			result = (result * base) % modulus
		}
		base = (base * base) % modulus
		exponent = exponent / 2
	}

	return result
}

func main() {
	p := uint(1229)
	generator, err := findMultiplicativeGenerator(p)
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Printf("The multiplicative generator for GF(%d) is %d.n", p, generator)
	}
}
