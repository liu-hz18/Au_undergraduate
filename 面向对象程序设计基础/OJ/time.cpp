#include<iostream>
using namespace std;
//类名需要大写！！！
class Time{
private:
	int year,month,day,hour,min,second;
public:
	Time();
	void showtime();
};//记得类最后加分号！！！
Time::Time(){
	cin>>year>>month>>day>>hour>>min>>second;
}
void Time::showtime(){
	cout<<year<<' '<<month<<' '<<day<<' '<<hour<<' '<<min<<' '<<second;
}

int main(){
	Time t;
	t.showtime();
	return 0;
}