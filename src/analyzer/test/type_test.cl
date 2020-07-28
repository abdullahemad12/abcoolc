class Main inherits A
{
	meth1() : A { new SELF_TYPE };
	meth2() : SELF_TYPE {
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
	dispatch() : Int {
		new E.get_int()
	};
	
	dispatch2() : String {
		new E.get_int()
	};
	
};
class A inherits IO
{
	static_dispatch3() : Int {
		new B@E.parent_method(10, new Main, new Bin)
	};
	meth() : Main { new SELF_TYPE };
	y : Int <- 0;
	hello() : Int { y };
	bin_meth(x : Int, y : String, n : Main, i : IO, bin : Bin) : SELF_TYPE {
		self
	};
	bin_self_dispatch() : B {
		(new E).parent_method_self(10)
	};
	bin_self_dispatch1() : E {
		(new F).parent_method_self(10)
	};

	static_dispatch() : Int {
		(new B)@E.get_int()
	};

	static_dispatch1() : Int {
		(new B)@F.get_int()
	};

	static_dispatch2() : Int {
		(new A)@F.get_int()
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
	get_int() : Int { 1 };
	get_self() : SELF_TYPE { self };
	my_method(x : Int) : SELF_TYPE { self };
	parent_method(x : Int, a : A, b : B) : Int
	{
		x
	};
	parent_method_self_err(x : Int, a : A) : SELF_TYPE
	{
		new F
	};

	parent_method_self(x : Int) : SELF_TYPE
	{
		self
	};

	parent_method_self1 (x : Int) : SELF_TYPE
	{
		new SELF_TYPE
	};

	self_self_dispatch() : SELF_TYPE
	{
		new E@SELF_TYPE.parent_method_self1(1).parent_method_self1(1)
	};
	
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
	my_method1(m : String) : String
	{
		self.parent_method(1, new A, new Bin)
	};
	parent_method_self(x : Int) : Int {
		1
	};
};
