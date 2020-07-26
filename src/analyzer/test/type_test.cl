class Main inherits A
{
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
	y : Int <- 0;
	hello() : Int { y };
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

};

class F inherits E
{

};
class B inherits A {
	m : B <- new Main;
};
