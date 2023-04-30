package main

import (
	"fmt"
)

func main() {
	var frequency = make(map[rune]int)
	var encrypted_str string = "kfd ktbd fzm eubd kfd pzyiom mztx ku kzyg ur bzha kfthcm ur mfudm zhx mftnm zhx mdzythc pzq ur ezsszcdm zhx gthcm zhx pfa kfd mdz tm sutythc fuk zhx pfdkfdi ntcm fzld pthcm sok pztkz stk kfd uamkdim eitdx sdruid pd fzld uoi efzk rui mubd ur om zid uok ur sidzkf zhx zyy ur om zid rzk hu foiia mztx kfd ezindhkdi kfda kfzhgdx ftb boef rui kfzk"
	var count int
	// calc the freq
	// freq doesnt include ' '
	for i := 97; i <= 122; i++ {
		frequency[rune(i)] = 0
	}
	for _, r := range encrypted_str {
		if rune(r) != ' ' {
			frequency[rune(r)]++
			count++
		}
	}
	var line int
	for {
		line++
		var max int
		var k rune
		for key, val := range frequency {
			if val > max {
				k = key
				max = val
			}
		}
		if max == 0 {
			break
		}
		fmt.Println(line, string(k), "=>", 100*float32(max)/float32(count), "%")
		frequency[k] = 0 - frequency[k] // add '-' to mark
	}

	// replacement, which is isolated from above
	var replacement = make(map[rune]rune)
	replacement['z'] = 'a' // e 12.702% line 1
	replacement['d'] = 'e' // t 9.056%
	replacement['k'] = 't' // a 8.167%
	replacement['f'] = 'h' // o 7.507%
	replacement['m'] = 's' // i 6.966%
	replacement['u'] = 'o' // n 6.749%

	replacement['t'] = 'i' // s 6.327% line 7
	replacement['h'] = 'n' // h 6.094%
	replacement['i'] = 'r' // r 5.987%

	replacement['r'] = 'f' // d 4.253% line 10
	replacement['x'] = 'd' // l 4.025%

	replacement['o'] = 'u' // c 2.782% line 12
	replacement['p'] = 'w' // u 2.758%
	replacement['c'] = 'g' // m 2.406%
	replacement['s'] = 'b' // w 2.360%

	replacement['y'] = 'l' // f 2.228% line 16
	replacement['b'] = 'm' // g 2.015%
	replacement['e'] = 'c' // y 1.974%

	replacement['a'] = 'y' // p 1.929% line 19

	replacement['g'] = 'k' // b 1.492%
	replacement['n'] = 'p' // v 0.978%
	replacement['l'] = 'v' // k 0.772%
	replacement['q'] = 'x' // jxqz

	// output
	for _, r := range encrypted_str {
		v, ok := replacement[r]
		if ok {
			fmt.Print(string(v))
		} else {
			fmt.Print(string(r))
		}
	}
}

/*
t

h

e

a

n thep then

s hai has

w shovs shows

i os is

v hake have

l aff all

y/n hurrn hurry

b mut but

of pd重复出现，all pd all of

w before ke have before we have

n apd and

g boilinc boiling

m for soce of us  for some of us

k thanced thanked

c muph much

x jxqz均有可能，wax是单词
*/
