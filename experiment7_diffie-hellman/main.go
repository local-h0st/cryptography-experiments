package main

import (
	"fmt"
	"math"
	"math/rand"
	"sync"
	"time"
)

type Control struct {
	wg             sync.WaitGroup
	ch             chan int64
	wgForPeersSync sync.WaitGroup
	p              int64
	alpha          int64
	digital        int
}

func randomInt(n int) int64 {
	rand.Seed(time.Now().UnixNano())
	min := int(math.Pow10(n - 1))
	max := int(math.Pow10(n)) - 1
	return int64(min + rand.Intn(max-min+1))
}

func exponentMod(a, b, m int64) int64 {
	res := int64(1)
	a = a % m
	for b > 0 {
		if b&1 == 1 {
			if res <= (math.MaxInt32-a)/a {
				res *= a
			} else {
				res = res * a % m
			}
		}
		if a <= (math.MaxInt32-a)/a {
			a *= a
		} else {
			a = a * a % m
		}
		b >>= 1
	}
	return res % m
}

func exponentMod_old(a, b, m int64) int64 {
	res := int64(1)
	a = a % m
	for b > 0 {
		if b&1 == 1 {
			res = (res * a) % m
		}
		a = (a * a) % m
		b >>= 1
	}
	return res
}

func generatePK(alpha, sk, p int64) int64 {
	return exponentMod(alpha, sk, p)
}

func generateKey(sk, pk, p int64) int64 {
	return exponentMod(pk, sk, p)
}

func peer(c *Control) {
	defer c.wg.Done()
	var send_flag bool
	var recv_PK int64
	sk := randomInt(c.digital)
	pk := generatePK(c.alpha, sk, c.p)

	// 一方发送一方接受
	select {
	case c.ch <- pk:
		send_flag = true
	default:
		// send choke.
		recv_PK = <-c.ch
	}
	c.wgForPeersSync.Done()
	// goroutine同步
	// 一方接受一方发送
	fmt.Println("waiting...")
	c.wgForPeersSync.Wait()
	if send_flag {
		recv_PK = <-c.ch
	} else {
		c.ch <- pk
	}

	fmt.Println(sk, recv_PK, generateKey(sk, recv_PK, c.p))
}

func main() {
	var c Control
	c.digital = 9
	c.alpha = 19
	c.p = 1307545881
	c.ch = make(chan int64)
	defer close(c.ch)
	c.wg.Add(2)
	c.wgForPeersSync.Add(2)
	go peer(&c)
	go peer(&c)
	c.wg.Wait()
}
