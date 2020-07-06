class A {
	meth() : Int { 1 };
};
class Main inherits A {
	main() : Int { new Main@SELF_TYPE.meth() };

};
