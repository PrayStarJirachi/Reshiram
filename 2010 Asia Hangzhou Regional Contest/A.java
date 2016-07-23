import java.util.*;
import java.io.*;
import java.math.*;

public class Main{
	
	final static int MAXN = 1000000;
	
	static Collection c = new HashSet();
	static BigInteger[] queue = new BigInteger[MAXN];
	static BigInteger[] d = new BigInteger[MAXN];
	
	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);
		
		while (true) {
			BigInteger n = cin.nextBigInteger();
			BigInteger m = cin.nextBigInteger();
		
			if (n.compareTo(BigInteger.ZERO) == 0 && m.compareTo(BigInteger.ZERO) == 0) {
				break;
			}
			
			if (m.compareTo(n) >= 0) {
				System.out.println(m.subtract(n));
			} else {
				c.clear();
				int left = 0, right = 0;
				BigInteger answer = n.subtract(m);
				queue[++right] = n;
				d[right] = BigInteger.ZERO;
				c.add(n);
				while (left < right) {
					left++;
					//System.out.println(left);
					if (d[left].add(queue[left].subtract(m).abs()).compareTo(answer) < 0) {
						answer = d[left].add(queue[left].subtract(m).abs());
					//	System.out.printf("%d %d\n", queue[left], d[left]);
					}
					if (queue[left].mod(BigInteger.valueOf(2)).compareTo(BigInteger.ZERO) == 0) {
						if (c.contains(queue[left].divide(BigInteger.valueOf(2))) == false) {
							right++;
							queue[right] = queue[left].divide(BigInteger.valueOf(2));
							d[right] = d[left].add(BigInteger.ONE);
							c.add(queue[right]);
							//System.out.println(queue[left].divide(BigInteger.valueOf(2)));
							//System.out.printf("Insert %d into the queue.\n", queue[right]);
						}
					} else {
						if (c.contains(queue[left].add(BigInteger.ONE)) == false) {
							right++;
							queue[right] = queue[left].add(BigInteger.ONE);
							d[right] = d[left].add(BigInteger.ONE);
							c.add(queue[right]);
							//System.out.println(queue[left].add(BigInteger.ONE).divide(BigInteger.valueOf(2)));
							//System.out.printf("Insert %d into the queue.\n", queue[right]);
						}
						if (c.contains(queue[left].subtract(BigInteger.ONE)) == false) {
							right++;
							queue[right] = queue[left].subtract(BigInteger.ONE);
							d[right] = d[left].add(BigInteger.ONE);
							c.add(queue[right]);
							//System.out.println(queue[left].subtract(BigInteger.ONE).divide(BigInteger.valueOf(2)));
							//System.out.printf("Insert %d into the queue.\n", queue[right]);
						}
					}
				}
				System.out.println(answer);
			}
		}
	}
};
