import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.util.Arrays;


public class KarpRabin {
	/**
	 * I hate java
	 * @param offset
	 * @param inputStream
	 * @param findText
	 * @return
	 * @throws IOException
	 */
	public int KarpRabinsAlgorithm(int offset, InputStream inputStream,
			String string) throws IOException {
		long start=System.currentTimeMillis();
		System.out.format("  -[KarpRabin] searching string: %s\n", string);
		// geting all bytes
		byte[] stringBytes = string.getBytes(Charset.defaultCharset());
	
		HashCount = (int) Math.ceil((double) stringBytes.length / 8);
		SearchingResult = new long[HashCount];
		
		Rolling = generate(stringBytes);
		
		SearchingResult = Rolling.clone();
		
		inputStream.mark(0);
		
		inputStream.reset();
		
		inputStream.skip(offset++);
		
		while (inputStream.read(stringBytes, 0, stringBytes.length) == stringBytes.length) {
			inputStream.reset();
			inputStream.skip(offset);
			offset++;
			
			Rolling = generate(stringBytes);
			if (Arrays.equals(Rolling, SearchingResult)) {
				long stop=System.currentTimeMillis();
				System.out.format("     -return: %d   time: %f\n", offset-1, ((double)stop-start)/1000);
				return offset-1;
			}
		}
		System.out.format("     -return: 0\n");
		return 0;
	}
	
	private long[] generate(byte value[]) { 
		int length = value.length;
		long[] retval = new long[HashCount];
		long tmp = 0;
		int iter = 0;
		for (int i = 0; i < HashCount; i++) {
			if (length >= 8) {
				retval[i] = (value[iter++] << 56) | (value[iter++] << 48)
						| (value[iter++] << 40) | (value[iter++] << 32)
						| (value[iter++] << 24) | (value[iter++] << 16)
						| (value[iter++] << 8) | (value[iter++]);
			} else { 
				byte offset = 56;
				tmp = 0;
				for (int j = 0; j < length; j++) { 
					tmp |= value[iter + j] << offset;
					offset -= 8;
				}
				retval[i] = tmp;
			}
			length -= 8;
		}
		return retval;
	}
	
	public int HashCount(){
		return this.HashCount;
	}
	
	public void HashCount(int count){
		this.HashCount = count;
	}
	
	public long[] Rolling() {
		return this.Rolling;
	}
	
	public void Rolling(long[] value) {
		this.Rolling = value;
	}
	
	public long[] SearchingResult() {
		return this.SearchingResult;
	}
	
	public void SearchingResult(long[] value) {
		this.SearchingResult = value;
	}
	
	private long[] SearchingResult;
	private long[] Rolling;
	private int HashCount;
}

