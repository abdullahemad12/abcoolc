class Main inherits IO {
   a : A <- new A;
   b : A <- a;
   main(): SELF_TYPE {
   	if a = b then 
	out_string("Hello, World.\n")
	else 
	out_string("not_equal \n")
	fi
   };
};

class A 
{
};
