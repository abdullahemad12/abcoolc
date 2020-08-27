class Main inherits IO {

   main(): Object {
	   (new A).method2(2)
   };

};


class A inherits IO
{
	method2(num : Int) : Int {  -- negate
      (let x : Int in
	 {
            x <- ~num;
			(new C).set_var(x);
	 }
      )
   };

};

class C {
	var : Int;
	set_var(num : Int) : Int {
		{
			var <- num;
		}
	};
};

