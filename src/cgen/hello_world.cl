class Main inherits IO {
   a : A <- new A;
   main(): Object {
   {
   	a.hello();
   }

   };
};


class A inherits IO
{
	hello() : SELF_TYPE
	{
		out_string("parent method")
	};
};
class B inherits A
{
	hello() : SELF_TYPE
	{
		out_string("child_method")
	};
};
