class Main inherits A
{
	x : Int <- 0;
	main() : Int { hello() };
};
class A inherits IO
{
	y : Int <- 0;
	hello() : Int { y };
};
