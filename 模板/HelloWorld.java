
//记住path变量设好之后要重新进入cmd!

/****************编程规范*******************/
//package名: 全小写，一般为名词(package shipping.objects)
//类名:首字母大写，每个单词首字母大写(class HelloWorld)
//接口名: 同类名：interface AccountBook
//方法名: 一般为动词，小写字57母开头，每个单词首字母大写(balanceAccount)
//变量名：一般为名词，其他同方法名(userAccount)
//常量名：全大写，单词之间用下划线隔开(HEAD_COUNT)

//强类型，分为Primitive和Referrence两种数据类型
//Primitive数据类型：byte(8:-128-127) short(16:-32768-32767) int(32:-2147483648-2147483647) long(64) 
//float(32位) double(64位，常量浮点数是double类型) char(Unicode,16位(0-65535)) boolean(true, false)
/*int:
十进制44:44
八进制(0开头)：0256 = 174
十六进制(0x开头)：0x3e6=998
*/
//可以用下划线进行数字分割,提高可读性！！！ 3.14_159_26   1234_5678_9012L

//Referrence数据类型:地址


//运算符 和 一二三元表达式 与C++相同，支持+=,-=,*=,/=,%
//+在字符串中有重载,可以进行字符串连接，同时可以把非字符串转换为字符串，如 “5”+5 = “55”
//instanceof 是一个运算符！！！


//if-else if-else\switch\for while loop和C++完全相同


public class HelloWorld{
	//main()是程序入口，有固定的书写格式
	//并不是每个类都要有main方法，大多数类没有main方法，而是由有main()方法的类调用
	//String[] args是命令行传进的参数
	public static void main(String args[]){
		System.out.println("Hello World");//调用System.out类中的方法
		System.out.println(args[0]);

		int x, y;
		float z = 1.234f;
		x = 10;
		z = (float)x;//强制类型转换

		//数据类型的<封装类>
		Integer intObj1 = new Integer(18);
		int obj1 = intObj1.intValue();
		System.out.println(obj1);
		System.out.println("LONG MAX:" + Long.MAX_VALUE);
		
		Boolean flag = "Hello" instanceof String; //true
		System.out.println(flag);
		
	}
}


//变量类型
//int total = 1234;
//double rate = 0.05;

/*声明
常量*/
//final int num1 = 100;
//final int num2 = 200;

//数组类型是Array对象，已经模板化，可以是基本数据类型，也可以是复杂对象
//int[] nums = new int[5];
//局部变量在栈内存，new建立的对象在堆内存，堆内存变量存在默认初始化值，会自动进行垃圾回收

//一维数组
//int[] arr = new int[5];
//int[] arr = new int[]{1, 2, 3, 4, 5};
//int[] arr = {1, 2, 3, 4};
//数组访问:
//for(int i = 0;i < arr.length; i++){
//	System.out.println(arr[i]);
//}
/*
支持迭代器foreach,用冒号表示遍历后面的对象放到前面的对象中
int[] tips = new int[]{1, 2, 3, 4, 5};
for(int ele:tips){
	System.out.println(ele);
}

*/
