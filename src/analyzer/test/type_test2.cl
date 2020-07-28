class Main
{
	main() : Int { if 1 then 1 else 2 fi};
	meth() : Int { if 1 = 2 then 1 else 4 fi };
	meth1() : B { if 1 < 2 then new C else new D fi};
	meth2() : A { if 1 < 2 then new C else new D fi };

	meth3() : String 
	{
		{
			1;
			new Main;
			new A; 
			new B; 
			"hello";
		}
	};
	meth4() : String 
	{
		{
			1;
			new Main;
			new A; 
			new B; 
			1;
		}
	};
		
	x : String <- "hello";
	let_meth() : A
	{
		{
			let x : Bool <- true in x;
			x <- "hello world";
			let x : Int <- 2, b : B <- new B, d : D <- new D in if x = 2 then b else d fi;
		}
	};
	let_meth1() : Int
	{
		{
			let x : Bool <- true in x;
			x <- "hello world";
			let x : Int <- 2, b : B <- new B, d : D <- new D in if x = 2 then x <- 2 else x <- 3 fi;
		}
	};
	let_meth3(x : Bool) : A
	{
		{
			x = true;
			let x : Bool <- true in x;
			x <- "hello world";
			let x : Int in x + 3;
			let x : Int <- 2, b : B <- new B, d : D <- new D in if x = 2 then new Main else d fi;
		}
	};				
};


class A {
	get_int() : Int { 1 };
	case_meth(x : A) : B 
	{
		case x.get_int() of 
			x : Int => x + 3;
			x : B => 4;
			y : C => y.case_meth(y);
		esac
	};
	
	case_meth1(x : A) : A 
	{
		case x.get_int() of 
			x : Int => {x <- x + 1; new B;};
			x : B => x;
			y : C => {y.case_meth(y); y;};
			y : D => y;
		esac
	};
};

class B inherits A
{
	loop_meth(x : Int, n : Int) : Int
	{
		let i : Int <- 0 in while(i <= n) loop x <- x + 1 pool
	};

	loop_meth1(x : Int, n : Int) : Object
	{
		let i : Int <- 0 in while(i <= n) loop x <- x + 1 pool
	};

	is_void_meth() : Bool
	{
		isvoid new C.loop_meth1(1, 2)
	};
	

	is_void_meth1() : Int
	{
		isvoid new C.loop_meth1(1, 2)
	};
	
	not_void() : Int
	{
		Not 3
	};

	not_meth(x : Bool) : Bool 
	{
		not x
	};

	compare_meth(x : Int, y : Int) : Int
	{
		if x < y then if x <= y then x else y fi else y fi
	};

	
	compare_meth(x : Int, y : Int) : Int
	{
		if x < y then if x <= y then (x <= y) + 1 else y fi else (y < x) + 2 fi
	};

	neg_meth(x : Int) : Int
	{
		~x
	};

	neg_meth2(x : Bool) : Bool
	{
		~x
	};

	arith(x : Int, y : Int, z : Int, w : String) : Int 
	{
		{
			x + w; 
			x + y; 
			x / w;
			w * y;
			z * x;
			y - x;
		}
	};

	zz : String; 
	ww : Bool; 
	equal(x : Int, y : Int, z : String, w : Bool) : Bool
	{
		{
			x = y;
			x = z;
			x = w;
			z = zz;
			z = w;
			w = ww;
		}
	};
};

class C inherits B
{
	x : B <- self;
	y : Int <- y;
};

class D inherits A 
{

};
