class Main inherits IO {
   x : Int;
   main(): SELF_TYPE {
	out_string("Hello, World.\n")
   };
};

class A inherits Main {
	y : String;
	a() : Int { 0 };
	b() : String { "" };
	c() : B { new B };
};

class B inherits A {
	a() : Int { 1 };
};
