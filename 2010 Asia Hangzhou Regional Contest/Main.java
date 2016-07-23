import java.io.*;
import java.math.*;
import java.util.*;

public class Main{
	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		while (true) {
			BigInteger n = cin.nextBigInteger();
			BigInteger m = cin.nextBigInteger();
			
			if (n.compareTo(BigInteger.ZERO) == 0 && m.compareTo(BigInteger.ZERO) == 0) {
				break;
			}
			
			if (m.compareTo(n) >= 0) System.out.println(m.subtract(n));
			else{
				BigInteger answer = n.subtract(m), now;
				int k = 0;
				for (now = m; n.compareTo(now) >= 0; k++, now = now.multiply(BigInteger.valueOf(2)));
				{
					BigInteger rem = now.subtract(n), fpm = BigInteger.ONE;
					for (int i = 1; i <= k; i++) fpm = fpm.multiply(BigInteger.valueOf(2));
					
					BigInteger tmp = BigInteger.valueOf(k);
					for (int i = k; i >= 0; i--) {
						tmp = tmp.add(rem.divide(fpm));
						rem = rem.mod(fpm);
						fpm = fpm.divide(BigInteger.valueOf(2));
					}
					
					if (answer.compareTo(tmp) > 0) {
						answer = tmp;
					}
				}
				{
					now = now.divide(BigInteger.valueOf(2));
					BigInteger rem = n.subtract(now), fpm = BigInteger.ONE;
					for (int i = 1; i <= k - 1; i++) fpm = fpm.multiply(BigInteger.valueOf(2));
					
					BigInteger tmp = BigInteger.valueOf(k - 1);
					for (int i = k - 1; i >= 0; i--) {
						tmp = tmp.add(rem.divide(fpm));
						rem = rem.mod(fpm);
						fpm = fpm.divide(BigInteger.valueOf(2));
					}
					
					//System.out.printf("Fuck %d\n", tmp);
					if (answer.compareTo(tmp) > 0) {
						answer = tmp;
					}
				}
				System.out.println(answer);
			}
		}
	}
};
