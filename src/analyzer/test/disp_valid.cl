class A {
	meth() : Int { 1 };
};
class Main inherits A {
	main() : Int { self() };
};
