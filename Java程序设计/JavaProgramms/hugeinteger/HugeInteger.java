package hugeinteger;

public class HugeInteger{
    String integer;

    public HugeInteger(String integer){
        this.integer = integer;
    }
    public void input(String integer){
        this.integer = integer;
    }
    public void output(){
        System.out.println(this.integer);
    }
    public void add(HugeInteger h){
        String[] num = { new StringBuffer(this.integer).reverse().toString(), new StringBuffer(h.integer).reverse().toString()};
        int[] len = { num[0].length(), num[1].length() };
        int maxlen = len[0] > len[1] ? len[0] : len[1];
        int[] result = new int[maxlen + 1];
        int j = len[0] > len[1] ? 0 : 1;
        for(int i = len[1-j]; i < len[j]; i++) 
            num[1-j] += "0";
        for(int i = 0; i < maxlen; i++) //Bit-wise Add
            result[i] = Integer.parseInt(num[0].charAt(i)+"") + Integer.parseInt(num[1].charAt(i)+"");
        for(int i = 0; i < maxlen; i++){ //Solve Overflow
            if(result[i] > 10){
                result[i] -= 10;
                result[i+1] += 1;
            }
        }
        StringBuffer str = new StringBuffer();
        for(int i = 0; i < maxlen; i++){
            str.append(String.valueOf(result[i]));
        }
        if(result[maxlen] != 0)str.append(String.valueOf(result[maxlen]));
        this.integer = str.reverse().toString();
    }
    public boolean isEqualTo(HugeInteger h){
        return integer.equals(h.integer);
    }
    public boolean isNotEqualTo(HugeInteger h){
        return !integer.equals(h.integer);
    }
    public boolean isGreaterThan(HugeInteger h){
        if(this.integer.length() > h.integer.length())return true;
        if(this.integer.length() < h.integer.length())return false;
        if(this.integer.compareTo(h.integer) > 0)return true;
        return false;
    }
    public boolean isLessThan(HugeInteger h){
        if(this.integer.length() > h.integer.length())return false;
        if(this.integer.length() < h.integer.length())return true;
        if(this.integer.compareTo(h.integer) < 0)return true;
        return false;
    }
    public boolean isGreaterThanOrEqualTo(HugeInteger h){
        return !this.isLessThan(h);
    }
    public boolean isLessThanOrEqualTo(HugeInteger h){
        return !this.isGreaterThan(h);
    }
}
