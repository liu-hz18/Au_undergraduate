
#include<iostream>
using namespace std;
class Vehicle{
public:
	Vehicle(){cout<<"vehicle Construct\n";}
	~Vehicle(){cout<<"vehicle Destroy\n";}
	virtual void run(){
		cout<<"vehicle run"<<endl;
	}
	virtual void stop(){
		cout<<"vehicle stop"<<endl;
	}
};
class Bicycle:virtual public Vehicle{
public:
	Bicycle(){cout<<"bicycle Construct\n";}
	~Bicycle(){cout<<"bicycle Destroy\n";}
	void run(){
		cout<<"bicycle run"<<endl;
	}
	void stop(){
		cout<<"bicycle stop"<<endl;
	}
};
class Motorcar:virtual public Vehicle{
public:
	Motorcar(){cout<<"motorcar Construct\n";}
	~Motorcar(){cout<<"motorcar Destroy\n";}
	void run(){
		cout<<"motorcar run"<<endl;
	}
	void stop(){
		cout<<"motorcar stop"<<endl;
	}
};

class Motorcycle:public Bicycle,public Motorcar{
public:
	Motorcycle(){cout<<"motorcycle Construct\n";}
	~Motorcycle(){cout<<"motorcycle Destroy\n";}
	void run(){
		cout<<"motorcycle run"<<endl;
	}
	void stop(){
		cout<<"motorcycle stop"<<endl;
	}
};
int main(){
	Vehicle vehicle;//vehicle Construct
	Bicycle bicycle;//vehicle Construct  bicycle Construct
	Motorcar motorcar;//vehicle Construct  motorcar Construct
	//虚继承
	Motorcycle motorcycle;//vehicle Construct  bicycle Construct  motorcar Construct  motorcycle Construct
	vehicle.run();vehicle.stop();
	bicycle.run();bicycle.stop();
	motorcar.run();motorcar.stop();
	motorcycle.run();motorcycle.stop();
	return 0;
}

