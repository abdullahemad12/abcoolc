class Main inherits IO {
   aa : A;
   a() : Object {
   	case aa of
   		x : B         => out_string("hello B\n");
   		x : A         => out_string("hello A\n");
   		x : Object    => out_string("hello Object\n");

   	esac
   };
   main(): Object {
	a()
   };
};


class A 
{

};
class B
{
};
