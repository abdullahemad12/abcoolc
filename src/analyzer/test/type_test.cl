class Main inherits A
{
	meth1() : A { new SELF_TYPE };
	meth() : SELF_TYPE {
		new SELF_TYPE
	};

	bin : Bin <- new SELF_TYPE;
	s : A <- new SELF_TYPE;
	a : A <- new A;
	m : A <- new B;
	b : B <- new A; 
	x : Int <- 0;
	main() : Int { hello1() };
	fun1() : Int { z };
	fun2() : String { x };
	fun3() : A { a };
	setB() : Main {
		{
			b <- new Bin;
			b <- new A;
			b <- new Bin;
			self;
		}
	};
};
class A inherits IO
{
	meth() : Main { new SELF_TYPE };
	y : Int <- 0;
	hello() : Int { y };
	bin_meth(x : Int, y : String, n : Main, i : IO, bin : Bin) : SELF_TYPE {
		self
	}; 
};

class Bin inherits B
{

};
class C inherits Main 
{
};

class D inherits C
{

};

class E inherits C
{
	my_method(x : Int) : SELF_TYPE { self };
};

class F inherits E{
	my_method(x : Int) : SELF_TYPE { self };
};
class B inherits E {
	m : B <- new Main;
	my_method(x : Int, s : String) : SELF_TYPE
	{
		self
	};
};
