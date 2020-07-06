class A {
	meth() : Int { 1 };
};
class Main inherits A {
	main() : Int { new Main@C.meth() };
};
